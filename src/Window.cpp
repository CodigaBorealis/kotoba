#include "Kotoba/Window/Window.hpp"
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Types.hpp"

namespace Kotoba{

    struct Window::Impl{

        std::filesystem::path icon{};
        std::string title{};
        bool requestedClose{false};
        u32 targetFPS{};
        Flag flags{Flag::None};

        static unsigned int toRaylibFlags(Window::Flag flags) {

            unsigned int result = 0;

            const auto has = [flags](Window::Flag flag) {

                return (static_cast<u32>(flags) & static_cast<u32>(flag)) != 0;
            };

            if(has(Window::Flag::Fullscreen)) result |= FLAG_FULLSCREEN_MODE;

            if(has(Window::Flag::Resizable)) result |= FLAG_WINDOW_RESIZABLE;

            if(has(Window::Flag::Undecorated)) result |= FLAG_WINDOW_UNDECORATED;

            if(has(Window::Flag::Hidden)) result |= FLAG_WINDOW_HIDDEN;

            if(has(Window::Flag::Minimized)) result |= FLAG_WINDOW_MINIMIZED;

            if(has(Window::Flag::Maximized)) result |= FLAG_WINDOW_MAXIMIZED;

            if(has(Window::Flag::Unfocused)) result |= FLAG_WINDOW_UNFOCUSED;

            if(has(Window::Flag::Topmost)) result |= FLAG_WINDOW_TOPMOST;

            if(has(Window::Flag::AlwaysRun)) result |= FLAG_WINDOW_ALWAYS_RUN;

            if(has(Window::Flag::Transparent)) result |= FLAG_WINDOW_TRANSPARENT;

            if(has(Window::Flag::HighDPI)) result |= FLAG_WINDOW_HIGHDPI;

            if(has(Window::Flag::VSync)) result |= FLAG_VSYNC_HINT;

            if(has(Window::Flag::MSAA4X)) result |= FLAG_MSAA_4X_HINT;

            if(has(Window::Flag::Interlaced)) result |= FLAG_INTERLACED_HINT;

            return result;
        }
    };

    Window::Window(const Config& config)
        :
        impl(std::make_unique<Impl>())
        {

        if(::IsWindowReady()) throw WindowException("Cannot create more than one window instance", ErrorCode::WindowAlreadyExists);

        setFlags(config.flags);

        ::InitWindow(config.dimensions.x, config.dimensions.y, nullptr);

        setTargetFPS(config.targetFPS);

        setTitle(config.title);

        setIcon(config.icon);

        ::SetExitKey(KEY_NULL);
    }
        
    Window::~Window(){

        if(::IsWindowReady()) ::CloseWindow();
        
    }

    bool Window::isOpen() const{

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return ::IsWindowReady() && !::WindowShouldClose() && !impl->requestedClose;
    }


    void Window::toggleFullscreen(){

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        ::ToggleFullscreen();
    }

    bool Window::isFullscreen() const{

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return ::IsWindowFullscreen();
    }


    void Window::toggleBorderless(){

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        ::ToggleBorderlessWindowed();
    }

        
    void Window::minimize(){

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        ::MinimizeWindow();
    }

    bool Window::isMinimized() const{

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return ::IsWindowMinimized();
    }


    void Window::maximize(){

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        ::MaximizeWindow();
    }

    bool Window::isMaximized() const{

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return ::IsWindowMaximized();
    }


    void Window::setIcon(std::filesystem::path file){

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        if(file.empty()) return;

        Image icon{file};

        ::SetWindowIcon(icon.native());
    }

    const std::filesystem::path& Window::getIcon() const{

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        
        return impl->icon;
    }


    bool Window::isFocused() const{
        
        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return ::IsWindowFocused();
    }


    void Window::close(){

        if(!::IsWindowReady()) throw WindowException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        impl->requestedClose = true;
    }


    void Window::setSize(const Vec<u32>& dimensions){
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        ::SetWindowSize(static_cast<int>(dimensions.x), static_cast<int>(dimensions.y));
    }

    Vec2u Window::getSize() const{
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return {static_cast<u32>(::GetScreenHeight()), static_cast<u32>(GetScreenWidth())};
    }

    bool Window::isResized() const{
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return ::IsWindowResized();
    }

    void Window::setTitle(std::string title){
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        impl->title = std::move(title);

        ::SetWindowTitle(impl->title.c_str());
    }

    const std::string& Window::getTitle() const{
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return impl->title;
    }


    void Window::setTargetFPS(u32 fps){
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        impl->targetFPS = fps;

        ::SetTargetFPS(static_cast<int>(impl->targetFPS));
    }

    u32 Window::getTargetFPS() const{
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return impl->targetFPS;
    }

    u32 Window::getFPS() const{
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return static_cast<u32>(::GetFPS());
    }

    void Window::setFlags(Flag flags){
        
        impl->flags = flags;

        ::SetConfigFlags(impl->toRaylibFlags(impl->flags));
    }

    void Window::addFlags(Flag flags){

        impl->flags = static_cast<Flag>(static_cast<u32>(impl->flags) | static_cast<u32>(flags));
    }

    void Window::removeFlags(Flag flags){

        impl->flags = static_cast<Flag>(static_cast<u32>(impl->flags) & ~static_cast<u32>(flags));
    }

    bool Window::hasFlag(Flag flag) const{

        const u32 current = static_cast<u32>(impl->flags);
        const u32 requested = static_cast<u32>(flag);

        return requested != 0 && (current & requested) == requested;
    }

    void Window::setPosition(const Vec<i32>& position){

        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        ::SetWindowPosition(static_cast<int>(position.x), static_cast<int>(position.y));
    }

    Vec2i Window::getPosition() const{

        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);

        return {::GetWindowPosition()};
    }

    bool Window::shouldClose() const{
        
        if(!IsWindowReady()) throw InitializationException("Window has not been initialized", ErrorCode::WindowNotInitialized);
 
        return impl->requestedClose || ::WindowShouldClose();
    }
}