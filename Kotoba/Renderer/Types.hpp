#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Math/Vec.hpp"
#include <variant>

namespace Kotoba{

    struct TextComponent;
    struct TextureComponent;
    
    struct Color{

        constexpr Color() = default;

        constexpr Color(u8 r, u8 g, u8 b, u8 a)
            :
            r(r),
            g(g),
            b(b),
            a(a)
            {}
        operator ::Color() const;
        u8 r{255};
        u8 g{0};
        u8 b{0};
        u8 a{255};
    };

    struct Point{

        constexpr Point() = default;

        constexpr Point(Vec2i position)
            :
            position(position)
            {}

        Vec2i position{0, 0};
    };

    struct Line{

        constexpr Line() = default;

        constexpr Line(Vec2i start, Vec2i end)
            :
            start(start),
            end(end)
            {}

        Vec2i start{0, 0};
        Vec2i end{10, 10};
    };

    struct Circle{

        constexpr Circle() = default;

        constexpr Circle(f32 radius)
            :
            radius(radius)
            {}
            
        f32 radius{10};
    };

    struct Triangle{

        constexpr Triangle() = default;

        constexpr Triangle(Vec2i a, Vec2i b, Vec2i c)
            :
            a(a),
            b(b),
            c(c)
            {}

        Vec2i a{0, 0};
        Vec2i b{10, 0};
        Vec2i c{5, 10};
    };

    struct Rectangle{

        constexpr Rectangle() = default;

        constexpr Rectangle(Vec2i dimensions)
            :
            dimensions(dimensions)
            {}

        Vec2i dimensions{10, 10};
    };

    struct Ellipse{

        constexpr Ellipse() = default;

        constexpr Ellipse(f32 radiusH, f32 radiusV)
            :
            radiusH(radiusH),
            radiusV(radiusV)
            {}

        f32 radiusH{10};
        f32 radiusV{5};
    };

    struct Polygon{

        constexpr Polygon() = default;

        constexpr Polygon(i32 sides, f32 radius)
            :
            sides(sides),
            radius(radius)
            {}
            
        i32 sides{6};
        f32 radius{10};
    };

    using Drawable = std::variant<Point, Line, Circle, Triangle, Rectangle, Ellipse, Polygon, TextureComponent*, TextComponent*>;

    struct DrawCommand{

        Drawable drawable{};

        Vec2f position{0, 0};
        Vec2f scale{1, 1};
        f32 rotation{0};
        Color tint{255, 255, 255, 255};
        float outlineThickness{1};
        Color outlineColor{};
        bool outlineOnly{false};
    };
}