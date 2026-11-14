#include "Kotoba/Math/Vec.hpp"
#include "Kotoba/Core/Raylib.hpp"

namespace Kotoba{

   template <Numerical T>
   
    Vec<T>::Vec(const Vector2& vec)
        :
        x(static_cast<T>(vec.x)),
        y(static_cast<T>(vec.y))
        {}
        
    template Vec<f32>::Vec(const Vector2&);
    template Vec<f64>::Vec(const Vector2&);
    template Vec<i64>::Vec(const Vector2&);
    template Vec<u64>::Vec(const Vector2&);
    template Vec<i32>::Vec(const Vector2&);
    template Vec<u32>::Vec(const Vector2&);
    
    template <Numerical T>

    Vec<T>::operator ::Vector2() const{

            return{static_cast<f32>(x),static_cast<f32>(y)};
    }

    template Vec<f32>::operator ::Vector2() const;
    template Vec<f64>::operator ::Vector2() const;
    template Vec<i64>::operator ::Vector2() const;
    template Vec<i32>::operator ::Vector2() const;
    template Vec<u32>::operator ::Vector2() const;
    template Vec<u64>::operator ::Vector2() const;
}