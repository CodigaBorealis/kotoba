#pragma once
#include <algorithm>
#include <cmath>
#include "Kotoba/Core/Concepts.hpp"

struct Vector2;

namespace Kotoba{

    template <Numerical T> struct Vec{

        /*
        *Default constructor
        *Initializes both components to their default values (zero)
        */
        constexpr Vec() = default;

        /*
        *@param x The horizontal component
        *@param y The vertical component
        *Constructs a Vec from two numerical components
        */

        constexpr Vec(T x, T y)
            :
            x(x),
            y(y)
            {}
        /*
        *@param A raylib Vector2
        *Constructs a Vec<float> from a raylib vector2
        */

        Vec(const Vector2& vec);
        /*
        *Converts the Vec into a raylib Vector2
        *Returns a Vector2 with both components converted to float
        */

        operator ::Vector2() const;        

        /*
        *@param other The Vec to add
        *Adds two Vec components together
        *Returns the resulting Vec
        */

        constexpr Vec<T> operator+(const Vec<T>& other) const{

            return {x + other.x, y + other.y};
        }

        /*
        *@param other The Vec to subtract
        *Subtracts the components of another Vec
        *Returns the resulting Vec
        */

        constexpr Vec<T> operator-(const Vec<T>& other) const{

            return {x - other.x, y - other.y};
        }

        /*
        *@param scalar The scalar to multiply by
        *Multiplies both components by a scalar
        *Returns the resulting Vec
        */

        constexpr Vec<T> operator*(T scalar) const{

            return {x * scalar, y * scalar};
        }

        /*
        *@param scalar The scalar to divide by
        *Divides both components by a scalar
        *Returns the resulting Vec
        *Integer values are truncated
        */

        constexpr Vec<T> operator/(T scalar) const{
            
            return {x / scalar, y / scalar};
        }

        /*
        *@param other The Vec to add
        *Adds another Vec to the current Vec
        *Modifies both components and returns a reference to this Vec
        */

        constexpr Vec<T>& operator+=(const Vec& other){

            x += other.x;
            y += other.y;

            return *this;
        }

        /*
        *@param other The Vec to subtract
        *Subtracts another Vec from the current Vec
        *Modifies both components and returns a reference to this Vec
        */

        constexpr Vec<T>& operator-=(const Vec& other){

            x -= other.x;
            y -= other.y;

            return *this;
        }

        /*
        *@param scalar The scalar to multiply by
        *Multiplies both components by a scalar
        *Modifies the current Vec and returns a reference to it
        */

        constexpr Vec<T>& operator*=(T scalar){

            x *= scalar;
            y *= scalar;

            return *this;
        }

        /*
        *Calculates the magnitude (length) of the Vec
        *Returns the length as a double
        */

        double length() const{

        return std::hypot(static_cast<double>(x), static_cast<double>(y));
        
        }

        /*
        *Calculates the squared magnitude of the Vec
        *Returns the sum of the squared components
        *Avoids the square root calculation used by length()
        */

        constexpr T lengthSquared() const{

            return x * x + y * y;
        }

        /*
        *Normalizes the Vec to have a length of 1
        *Requires T to be a floating-point type
        *Returns a zero Vec if the original length is zero
        *Otherwise returns the normalized Vec
        */

        Vec<T> normalized() const requires std::is_floating_point_v<T>{

            double len = length();

            if(len == T{0}) return {T{0}, T{0}};

            return { x / len, y / len};
        };

        /*
        *@param a The first Vec
        *@param b The second Vec
        *Calculates the distance between two Vecs
        *Returns the distance as a double
        */

        static double distance(const Vec<T>& a, const Vec<T>& b){

            return (a - b).length();
        }

        /*
        *@param other The Vec to calculate the dot product with
        *Calculates the dot product between two Vecs
        *Returns the sum of the products of their corresponding components
        */

        constexpr T dot(const Vec<T>& other) const{

            return x * other.x + y * other.y;
        }

        /*
        *@param minX The minimum horizontal value
        *@param maxX The maximum horizontal value
        *@param minY The minimum vertical value
        *@param maxY The maximum vertical value
        *Clamps each component within its specified range
        *Returns a new Vec with the clamped components
        */

        Vec clamped(T minX, T maxX, T minY, T maxY) const{

            return {std::clamp(x, minX, maxX), std::clamp(y, minY, maxY)};
        }

        /*
        *@param a The starting Vec
        *@param b The ending Vec
        *@param t The interpolation factor
        *Performs linear interpolation between two Vecs
        *Returns a Vec interpolated between a and b
        *A t value of 0 returns a, while a value of 1 returns b
        */

        static Vec lerp(const Vec<T>& a, const Vec<T>& b, T t){

            return a + (b - a) * t;
        }

        /*
        *@param flipX Whether to mirror the horizontal component
        *@param flipY Whether to mirror the vertical component
        *Mirrors the Vec across the specified axes
        *Returns a new Vec with the selected components negated
        */

        Vec mirror(bool flipX, bool flipY) const{

            return {flipX ? -x : x, flipY ? -y : y};
        };

        T x{};//horizontal component
        T y{};//vertical component
    };

    using Vec2i = Vec<i64>;
    using Vec2u = Vec<u64>;
    using Vec2f = Vec<f32>;
    using Vec2d = Vec<f64>;
}