#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Math/Rect.hpp"
#include "Kotoba/Math/Vec.hpp"
#include "Kotoba/Window/Window.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include <raylib.h>

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
        Vec2f baseResolution{};
        Vec2f renderTargetOffset{};
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

    void Renderer::beginFrame(){

        ::BeginTextureMode(impl->canvas);
        ::ClearBackground(impl->clearColor);
    }

    void Renderer::queue(Point point){

        impl->queuedCommands.push_back(std::move(point));

    }

    void Renderer::queue(Line line){

        impl->queuedCommands.push_back(std::move(line));

    }

    void Renderer::queue(Circle circle){

        impl->queuedCommands.push_back(std::move(circle));

    }

    void Renderer::queue(Triangle triangle){

        impl->queuedCommands.push_back(std::move(triangle));

    }

    void Renderer::queue(Rectangle rectangle){

        impl->queuedCommands.push_back(std::move(rectangle));

    }

    void Renderer::queue(Ellipse ellipse){

        impl->queuedCommands.push_back(std::move(ellipse));

    }

    void Renderer::queue(Polygon polygon){

        impl->queuedCommands.push_back(std::move(polygon));

    }

    void Renderer::queue(Tex texture){

        impl->queuedCommands.push_back(std::move(texture));

    }

    void Renderer::queue(Txt text){

        impl->queuedCommands.push_back(std::move(text));
    }

    namespace{

        void drawCommand(const Renderer::Point& cmd){

            ::DrawPixel(cmd.position.x, cmd.position.y, cmd.color);
        }

        void drawCommand(const Renderer::Line& cmd){

            ::DrawLine(cmd.start.x, cmd.start.y, cmd.end.x, cmd.end.y, cmd.color);
        }

        void drawCommand(const Renderer::Circle& cmd){

            if(cmd.outlineOnly){

                ::DrawCircleLines(cmd.center.x, cmd.center.y, cmd.radius, cmd.color);

            }else{

                ::DrawCircle(cmd.center.x, cmd.center.y, cmd.radius, cmd.color);
            }
        }

        void drawCommand(const Renderer::Triangle& cmd){

            if(cmd.outlineOnly){

                ::DrawTriangleLines(cmd.a, cmd.b, cmd.c, cmd.color);

            }else{

                ::DrawTriangle(cmd.a, cmd.b, cmd.c, cmd.color);
            }
        }

        void drawCommand(const Renderer::Rectangle& cmd){

            if(cmd.outlineOnly){

                ::DrawRectangleLines(cmd.position.x, cmd.position.y, cmd.dimensions.x, cmd.dimensions.y, cmd.color);

            }else{

                ::DrawRectangle(cmd.position.x, cmd.position.y, cmd.dimensions.x, cmd.dimensions.y, cmd.color);
            }
        }

        void drawCommand(const Renderer::Ellipse& cmd){

            if(cmd.outlineOnly){

                ::DrawEllipseLines(cmd.center.x, cmd.center.y, cmd.radiusH, cmd.radiusV, cmd.color);

            }else{

                ::DrawEllipse(cmd.center.x, cmd.center.y, cmd.radiusH, cmd.radiusV, cmd.color);
            }
        }

        void drawCommand(const Renderer::Polygon& cmd){

            if(cmd.outlineOnly){

                ::DrawPolyLines(cmd.center, cmd.sides, cmd.radius, cmd.rotation, cmd.color);

            }else{

                ::DrawPoly(cmd.center, cmd.sides, cmd.radius, cmd.rotation, cmd.color);
            }
        }

        void drawCommand(const Renderer::Tex& cmd){

            if(!cmd.texture) throw GraphicsException("Renderer expected a Texture pointer, got nullptr", ErrorCode::NullPointerException);

            ::DrawTextureEx(cmd.texture->native(), cmd.position, cmd.rotation, cmd.scale, cmd.tint);
        }

        void drawCommand(const Renderer::Txt& cmd){

            if(!cmd.font) throw GraphicsException("Renderer expected a Font pointer, got nullptr", ErrorCode::NullPointerException);

            ::DrawTextEx(cmd.font->native(), cmd.text.c_str(), cmd.position, cmd.fontSize, cmd.spacing, cmd.tint);
        }
    }

    void Renderer::draw(){

        for(const auto& command : impl->queuedCommands){

            std::visit([](const auto& cmd){

                drawCommand(cmd);

            }, command);
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