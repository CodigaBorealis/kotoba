#pragma once
#include "Kotoba/Core/Concepts.hpp"
#include "Kotoba/Core/Raylib.hpp"

namespace Kotoba{

    template<Numerical T> struct Rect{

        /*
        *Default constructor
        *Initializes all components to their default values (zero)
        */

        constexpr Rect() = default;

        /*
        *@param x The horizontal position
        *@param y The vertical position
        *@param width The width of the rectangle
        *@param height The height of the rectangle
        *Constructs a Rect from its position and dimensions
        */

        constexpr Rect(T x, T y, T width, T height)
            :
            x(x),
            y(y),
            width(width),
            height(height)
            {}
        /*
        *@param rect A raylib Rectangle
        *Constructs a Rect from a raylib Rectangle
        */

       constexpr Rect(const ::Rectangle& rect)
            :
            x(rect.x),
            y(rect.y),
            width(rect.width),
            height(rect.height)
            {}
        /*
        *Converts the Rect into a raylib Rectangle
        *Returns a Rectangle with all components converted to float
        */
        constexpr operator ::Rectangle() const{

            return{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)};
        } 
        
        T x{};//vertical position
        T y{};//horizontal position
        T width{};//width
        T height{};//height
    };
    using RectI = Rect<i64>;
    using RectU = Rect<u64>;
    using RectF = Rect<f32>;
    using RectD = Rect<f64>;
}