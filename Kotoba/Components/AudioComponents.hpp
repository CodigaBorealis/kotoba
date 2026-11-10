#pragma once
#include "Kotoba/Core/Resources.hpp"
#include <variant>

namespace Kotoba{

    using AudioVariant = std::variant<Music*, Sound*>;

    struct AudioComponent{

        constexpr AudioComponent() = default;

        constexpr AudioComponent(AudioVariant data)
            :
            data(data)
            {}
            
        AudioVariant data{};
    };
}