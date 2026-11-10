#pragma once
#include "Kotoba/Core/Concepts.hpp"

struct Rectangle;

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

        Rect(const ::Rectangle& rect);
        /*
        *Converts the Rect into a raylib Rectangle
        *Returns a Rectangle with all components converted to float
        */
        operator ::Rectangle() const;
        
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