#pragma once
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Math/Vec.hpp"
#include "Kotoba/Renderer/Types.hpp"
#include <string>
#include <variant>

namespace Kotoba{

    struct ColorComponent{

        constexpr ColorComponent() = default;
        
        constexpr ColorComponent(Color data)
            :
            data(data)
            {}
            
        Color data{255, 255, 255, 255};
    };

    struct TransformComponent{

        constexpr TransformComponent() = default;

        constexpr TransformComponent(Vec2f position, Vec2f scale, float rotation)
            :
            position(position),
            scale(scale),
            rotation(rotation)
            {}
        
        Vec2f position{0, 0};
        Vec2f scale{1.0f, 1.0f};
        float rotation{0};
    };

    using GeometryVariant = std::variant<Point, Line, Circle, Rectangle, Ellipse, Polygon>;

    struct GeometryComponent{
    
        GeometryVariant data{};
    };

    struct TextureComponent{

        Texture* data{};
    };
    
    struct TextComponent{
        
        std::string text{"Text"};
        f32 fontSize{24};
        f32 spacing{1};
        Font* data{nullptr};
    };

    struct RenderStyleComponent{

        enum class RenderStyle{

            Fill,
            Outline
        };

        constexpr RenderStyleComponent() = default;

        constexpr RenderStyleComponent(RenderStyle style, Color color, float thickness = 1.0f)
            :
            style(style),
            color(color),
            thickness(thickness)
            {}

        RenderStyle style{RenderStyle::Fill};
        Color color{255, 255, 255, 255};
        float thickness{1.0f};
    };

    template<> inline constexpr bool IsComponent<ColorComponent> = true;
    template<> inline constexpr bool IsComponent<TransformComponent> = true;
    template<> inline constexpr bool IsComponent<GeometryComponent> = true;
    template<> inline constexpr bool IsComponent<TextureComponent> = true;
    template<> inline constexpr bool IsComponent<TextComponent> = true;
    template<> inline constexpr bool IsComponent<RenderStyleComponent> = true;


}