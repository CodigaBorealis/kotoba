#include "Kotoba/Math/Rect.hpp"
#include "Kotoba/Core/Raylib.hpp"

namespace Kotoba{
    
    template<Numerical T>

    Rect<T>::Rect(const ::Rectangle& rect)
        :
        x(rect.x),
        y(rect.y),
        width(rect.width),
        height(rect.height)
        {}
        template Rect<f32>::Rect(const ::Rectangle&);
        template Rect<f64>::Rect(const ::Rectangle&);
        template Rect<i64>::Rect(const ::Rectangle&);
        template Rect<u64>::Rect(const ::Rectangle&);
        template Rect<i32>::Rect(const ::Rectangle&);
        template Rect<u32>::Rect(const ::Rectangle&);
        
    template <Numerical T>

    Rect<T>::operator ::Rectangle() const{

        return{static_cast<f32>(x), static_cast<f32>(y), static_cast<f32>(width), static_cast<f32>(height)};
    }

    template Rect<f32>::operator ::Rectangle() const;
    template Rect<f64>::operator ::Rectangle() const;
    template Rect<i64>::operator ::Rectangle() const;
    template Rect<u64>::operator ::Rectangle() const;
    template Rect<i32>::operator ::Rectangle() const;
    template Rect<u32>::operator ::Rectangle() const;
}