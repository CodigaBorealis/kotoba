#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Math/Vec.hpp"
#include "Kotoba/Core/Resources.hpp"
#include <utility>
#include <variant>

namespace Kotoba{

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

            constexpr Point(Vec<i32> position, Color color)
                :
                position(position),
                color(color)
                {}

            Color color{255, 255, 255, 255};
            Vec<i32> position{0, 0};
        };

        struct Line{

            constexpr Line() = default;
            
            constexpr Line(Vec<i32> start, Vec<i32> end, Color color)
                :
                start(start),
                end(end),
                color(color)
                {}

            Color color{255, 255, 255, 255};
            Vec<i32> start{0, 0};
            Vec<i32> end{10,10};
        };

        struct Circle{

            constexpr Circle() = default;
            
            constexpr Circle(Vec<i32> center, f32 radius, Color color, bool outlineOnly)
                :
                center(center),
                radius(radius),
                color(color),
                outlineOnly(outlineOnly)
                {}

            Color color{255, 255, 255, 255};
            Vec<i32> center{0,0};
            f32 radius{10};
            bool outlineOnly{false};
        };

        struct Triangle{

            constexpr Triangle() = default;

            constexpr Triangle(Vec<i32> a, Vec<i32> b, Vec<i32> c, Color color, bool outlineOnly)
                :
                a(a),
                b(b),
                c(c),
                color(color),
                outlineOnly(outlineOnly)
                {}

            Color color{255, 255, 255, 255};
            Vec<i32> a{0, 0};
            Vec<i32> b{10, 0};
            Vec<i32> c{5, 10};
            bool outlineOnly{false};
        };

        struct Rectangle{

            constexpr Rectangle() = default;

            constexpr Rectangle(Vec<i32> position, Vec<i32> dimensions, Color color, bool outlineOnly)
                :
                position(position),
                dimensions(dimensions),
                color(color),
                outlineOnly(outlineOnly)
                {}

            Color color{255, 255, 255, 255};
            Vec<i32> position{0,0};
            Vec<i32> dimensions{10, 10};
            bool outlineOnly{false};
        };

        struct Ellipse{

            constexpr Ellipse() = default;
            
            constexpr Ellipse(Vec<i32> center, f32 radiusH, f32 radiusV, Color color, bool outlineOnly)
                :
                center(center),
                radiusH(radiusH),
                radiusV(radiusV),
                color(color),
                outlineOnly(outlineOnly)
                {}

            Color color{255, 255, 255, 255};
            Vec<i32> center{0, 0};
            f32 radiusH{10};
            f32 radiusV{5};
            bool outlineOnly{false};
        };

        struct Polygon{

            constexpr Polygon() = default;

            constexpr Polygon(Vec<i32> center, u64 sides,  f32 radius, f32 rotation, Color color, bool outlineOnly)
                :
                center(center),
                sides(sides),
                radius(radius),
                rotation(rotation),
                color(color),
                outlineOnly(outlineOnly)
                {}

            Color color{255, 255, 255 ,255};
            Vec<i32> center{0, 0};
            i32 sides{6};
            f32 radius{10};
            f32 rotation{0};
            bool outlineOnly{false};
        };
        
        struct Tex{     

            constexpr Tex() = default;

            constexpr Tex(Texture* texture, Vec<i32> position, f32 rotation, f32 scale, Color tint)
                :
                texture(texture),
                position(position),
                rotation(rotation),
                scale(scale),
                tint(tint)
                {}

            const Texture* texture{};
            Color tint{255, 255, 255, 255};
            Vec<i32> position{0, 0};
            f32 rotation{0};
            f32 scale{1};
        };

        struct Txt{

            constexpr Txt() = default;

            constexpr Txt(Font* font, Vec<f32> position, std::string text, f32 fontSize, f32 spacing)
                :
                font(font),
                position(position),
                text(std::move(text)),
                fontSize(fontSize),
                spacing(spacing)
                {}

            std::string text{"Text"};
            const Font* font{};
            Color tint{255, 255, 255, 255};
            Vec<f32> position{0, 0};
            f32 fontSize{24};
            f32 spacing{1};

        };

    using DrawCommand = std::variant<Point, Line, Circle, Triangle, Rectangle, Ellipse, Polygon, Tex, Txt>;

}