#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Math/Rect.hpp"
#include "Kotoba/Math/Vec.hpp"
#include "Kotoba/Renderer/Types.hpp"
#include "Kotoba/Window/Window.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Components/GraphicalComponents.hpp"
#include <iterator>

namespace Kotoba{

    struct Renderer::Impl{

        Impl(Window& window)
            :
            window(window),
            baseResolution(window.getSize())
            {}

        Window& window;
        ::RenderTexture2D canvas{};
        std::vector<DrawCommand> queuedCommands{};
        Color clearColor{0, 255, 0, 255};
        Vec2f baseResolution{1280, 720};
        Vec2f renderTargetOffset{0, 0};
        f32 scale{1.0f};

    };

    Renderer::~Renderer(){

        if(impl->canvas.id != 0) ::UnloadRenderTexture(impl->canvas);
    }

    Renderer::Renderer(Window& window)
        :
        impl(std::make_unique<Impl>(window))
        {
            Vec2u size = window.getSize();
            impl->baseResolution = {static_cast<f32>(size.x), static_cast<f32>(size.y)};
            impl->canvas = ::LoadRenderTexture(static_cast<int>(size.x), static_cast<int>(size.y));
        }

    void Renderer::submit(DrawCommand command){

        impl->queuedCommands.push_back(std::move(command));
    }

    void Renderer::submitBatch(std::vector<DrawCommand> commands){

        impl->queuedCommands.reserve(impl->queuedCommands.size() + commands.size());

        std::move(commands.begin(), commands.end(), std::back_inserter(impl->queuedCommands));
    }

    void Renderer::beginFrame(){

        ::BeginTextureMode(impl->canvas);
        ::ClearBackground(impl->clearColor);
    }

    namespace{

        void drawCommand(const Point& cmd, const DrawCommand& data){


            ::DrawPixel(cmd.position.x, cmd.position.y, data.tint);
        }

        void drawCommand(const Line& cmd, const DrawCommand& data){

            ::DrawLine(cmd.start.x, cmd.start.y, cmd.end.x, cmd.end.y, data.tint);
        }

        void drawCommand(const Circle& cmd, const DrawCommand& data){

            if(data.outlineOnly){

                ::DrawCircleLines(data.position.x, data.position.y, cmd.radius, data.tint);

            }else{

                ::DrawCircle(data.position.x, data.position.y, cmd.radius, data.tint);
            }
        }

        void drawCommand(const Triangle& cmd, const DrawCommand& data){

            if(data.outlineOnly){

                ::DrawTriangleLines(cmd.a, cmd.b, cmd.c, data.tint);

            }else{

                ::DrawTriangle(cmd.a, cmd.b, cmd.c, data.tint);
            }
        }

        void drawCommand(const Rectangle& cmd, const DrawCommand& data){

            if(data.outlineOnly){

                ::DrawRectangleLines(data.position.x, data.position.y, cmd.dimensions.x, cmd.dimensions.y, data.tint);

            }else{

                ::DrawRectangle(data.position.x, data.position.y, cmd.dimensions.x, cmd.dimensions.y, data.tint);
            }
        }

        void drawCommand(const Ellipse& cmd, const DrawCommand& data){

            if(data.outlineOnly){

                ::DrawEllipseLines(data.position.x, data.position.y, cmd.radiusH, cmd.radiusV, data.tint);

            }else{

                ::DrawEllipse(data.position.x, data.position.y, cmd.radiusH, cmd.radiusV, data.tint);
            }
        }

        void drawCommand(const Polygon& cmd, const DrawCommand& data){

            if(data.outlineOnly){

                ::DrawPolyLines(data.position, cmd.sides, cmd.radius, data.rotation, data.tint);

            }else{

                ::DrawPoly(data.position, cmd.sides, cmd.radius, data.rotation, data.tint);
            }
        }

        void drawCommand(const Texture* cmd, const DrawCommand& data){

            if(!cmd) throw GraphicsException("Renderer expected a Texture pointer, got nullptr", ErrorCode::NullPointerException);

            ::DrawTextureEx(cmd->native(), data.position, data.rotation, data.scale.x, data.tint);
        }

        void drawCommand(const TextCommand cmd, const DrawCommand& data){

            if(!cmd.font) throw GraphicsException("Renderer expected a Font pointer, got nullptr", ErrorCode::NullPointerException);

            ::DrawTextEx(cmd.font->native(), cmd.text.c_str(), data.position, cmd.fontSize, cmd.spacing, data.tint);
        }
    }

    void Renderer::draw(){

        for(const auto& command : impl->queuedCommands){

            std::visit([&command](const auto& drawable){

                drawCommand(drawable, command);

            }, command.drawable);
        }

        impl->queuedCommands.clear();
    }

    void Renderer::endFrame(){

        ::EndTextureMode();

        
        ::BeginDrawing();
            
        ::ClearBackground(impl->clearColor);

        RectF source{0.0f, 0.0f, impl->baseResolution.x, -impl->baseResolution.y};//Canvas is flipped otherwise

        RectF dest{impl->renderTargetOffset.x,
             impl->renderTargetOffset.y,
            impl->baseResolution.x * impl->scale,
            impl->baseResolution.y * impl->scale
        };

        ::DrawTexturePro(impl->canvas.texture, source, dest, {0, 0}, 0.0f, {255, 255, 255, 255});

        ::EndDrawing();

        }

}