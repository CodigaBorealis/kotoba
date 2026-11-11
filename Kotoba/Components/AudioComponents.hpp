#pragma once
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Core/Concepts.hpp"
#include <variant>

namespace Kotoba{

    using AudioVariant = std::variant<Music*, Sound*>;

    /*
    *Represents a component that can use an audio resource
    */

    struct AudioComponent{

        constexpr AudioComponent() = default;

        constexpr AudioComponent(AudioVariant data)
            :
            data(data)
            {}
            
        AudioVariant data{};
    };            
    
    template<> inline constexpr bool IsComponent<AudioComponent> = true;

}