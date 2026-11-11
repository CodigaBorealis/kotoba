#include "Kotoba/Renderer/Types.hpp"
#include "Kotoba/Core/Raylib.hpp"

namespace Kotoba{

     Color::operator ::Color() const{
        
        return ::Color{r, g, b, a};
    }
}