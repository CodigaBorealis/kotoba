#pragma once
#include <memory>
#include <string>
#include <filesystem>
#include "../Math/Vec.hpp"
#include "../Core/Types.hpp"

namespace Kotoba{
   /*
    * Represents a window managed by the Kotoba engine
    * Provides window configuration, state management and manipulation functionality
    * Uses a private implementation to hide internal platform-specific details
    * Window instances cannot be copied or moved
    * Only one instance can be alive at a time
    */

    class Window{

        public:

       /*
        * Defines the available window configuration flags
        * Flags can be combined using the bitwise OR operator
        * Each flag represents an independent window property
        */

        enum class Flag : u32{

            None = 0,// No window flags enabled
            Fullscreen = 1 << 0,// Creates the window in fullscreen mode
            Resizable = 1 << 1, // Allows the window to be resized by the user
            Undecorated = 1 << 2,// Removes the window decorations and title bar
            Hidden = 1 << 3, // Creates the window hidden
            Minimized = 1 << 4, // Creates the window minimized
            Maximized = 1 << 5,// Creates the window maximized
            Unfocused = 1 << 6,// Creates the window without focusing it
            Topmost = 1 << 7,// Keeps the window above other windows
            AlwaysRun = 1 << 8,// Continues running even when the window is not focused
            Transparent = 1 << 9,// Enables window transparency
            HighDPI = 1 << 10,// Enables high-DPI support
            VSync = 1 << 11,// Enables vertical synchronization
            MSAA4X = 1 << 12,// Enables 4x multisample anti-aliasing
            Interlaced = 1 << 13// Enables interlaced display mode
        };

       /*
        * Stores the configuration parameters used to create a Window
        * Provides default values for all configurable window properties
        */

        struct Config{

            std::filesystem::path icon{};// Filesystem path to the window icon
            std::string title{"Window"};// Window title displayed in the title bar
            Vec2i dimensions{1280, 720};// Initial window dimensions in pixels
            Vec2i position{0,0};// Initial window position on the screen
            u32 targetFPS{60};// Target framerate in frames per second
            Flag flags{Flag::None};// Window configuration flags
        };

        Window() = delete;
        explicit Window(const Config& config);
        
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        /*
        * Checks whether the window is currently open
        * Returns true if the window is open, otherwise false
        */

        bool isOpen() const;

        /*
        * Toggles the fullscreen state of the window
        * Switches between fullscreen and windowed mode
        */

        void toggleFullscreen();

        /*
        * Checks whether the window is currently in fullscreen mode
        * Returns true if fullscreen is enabled, otherwise false
        */

        bool isFullscreen() const;

        /*
        * Toggles the borderless state of the window
        * Switches between decorated and borderless window mode
        */

        void toggleBorderless();
        /*
        * Minimizes the window
        * Reduces the window to its minimized state
        */
        void minimize();
        /*
        * Checks whether the window is currently minimized
        * Returns true if the window is minimized, otherwise false
        */
        bool isMinimized() const;

        /*
        * Maximizes the window
        * Expands the window to its maximized state
        */

        void maximize();
        
        /*
        * Checks whether the window is currently maximized
        * Returns true if the window is maximized, otherwise false
        */
        
        bool isMaximized() const;

        /*
        * @param file The filesystem path to the icon image
        * Sets the window icon using the specified image file
        */

        void setIcon(std::filesystem::path file);

         /*
        * Returns the filesystem path of the current window icon
        * Returns a constant reference to the stored icon path
        */
        const std::filesystem::path& getIcon() const;

       /*
        * Checks whether the window currently has input focus
        * Returns true if the window is focused, otherwise false
        */

        bool isFocused() const;

        /*
        * Closes the window
        * Requests the window to enter its closed state
        */

        void close();

        /*
        * @param dimensions The new window dimensions
        * Changes the size of the window
        */

        void setSize(const Vec<u32>& dimensions);
        /*
        * Returns the current window dimensions
        * Returns a Vec2u containing the width and height in pixels
        */
        Vec2u getSize() const;

        /*
        * Checks whether the window has been resized
        * Returns true if the window dimensions have changed, otherwise false
        */

        bool isResized() const;

        /*
        * @param title The new window title
        * Changes the title displayed in the window title bar
        */

        void setTitle(std::string title);

        /*
        * Returns the current window title
        * Returns a constant reference to the stored title string
        */

        const std::string& getTitle() const;

         /*
        * @param fps The target framerate in frames per second
        * Sets the target frame rate of the window
        */

        void setTargetFPS(u32 fps);

        /*
        * Returns the target frame rate
        * Returns the configured target frames per second
        */

        u32 getTargetFPS() const;

        /*
        * Returns the current framerate
        * Returns the number of frames rendered per second
        */

        u32 getFPS() const;

        /*
        * @param flags The window flags to apply
        * Replaces the current window flags with the specified flags
        */

        void setFlags(Flag flags);

        /*
        * @param flags The window flags to enable
        * Adds the specified flags to the current window configuration
        */

        void addFlags(Flag flags);

        /*
        * @param flags The window flags to disable
        * Removes the specified flags from the current window configuration
        */

        void removeFlags(Flag flags);

        /*
        * @param flag The window flag to check
        * Checks whether the specified flag is currently enabled
        * Returns true if the flag is enabled, otherwise false
        */

        bool hasFlag(Flag flag) const;

        /*
        * @param position The new window position
        * Changes the position of the window on the screen
        */

        void setPosition(const Vec<i32>& position);

        /*
        * Returns the current window position
        * Returns a Vec2i containing the horizontal and vertical coordinates
        */

        Vec2i getPosition() const;
        
        /*
        * Checks whether the window should be closed
        * Returns true if a close request has been received, otherwise false
        */

        bool shouldClose() const;
        
        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    };

    /*
    * @param lhs The left-hand window flag
    * @param rhs The right-hand window flag
    * Combines two window flags using the bitwise OR operation
    * Returns a Window::Flag containing the combined flags
    */

    inline Window::Flag operator|(Window::Flag lhs, Window::Flag rhs){

        return static_cast<Window::Flag>(static_cast<u32>(lhs) | static_cast<u32>(rhs));
    }

    /*
    * @param lhs The left-hand window flag
    * @param rhs The right-hand window flag
    * Performs a bitwise AND operation between two window flags
    * Returns a Window::Flag containing only the flags enabled in both operands
    */

    inline Window::Flag operator&(Window::Flag lhs, Window::Flag rhs){

        return static_cast<Window::Flag>(static_cast<u32>(lhs) & static_cast<u32>(rhs));
    }

    /*
    * @param lhs The window flag variable to modify
    * @param rhs The window flags to add
    * Combines the right-hand flags with the left-hand flags using bitwise OR
    * Modifies lhs and returns a reference to it
    */
    
    inline Window::Flag& operator|=(Window::Flag& lhs,Window::Flag rhs){

        lhs = lhs | rhs;

        return lhs;
    }
}