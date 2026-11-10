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

        constexpr TransformComponent(Vec2i position, Vec2f scale, float rotation)
            :
            position(position),
            scale(scale),
            rotation(rotation)
            {}
        
        Vec2i position{0, 0};
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
}