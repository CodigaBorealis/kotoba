#pragma once

#include "Types.hpp"
#include <vector>

namespace Kotoba{

    class Scene;

    class SceneExtractor{

        public:

        constexpr SceneExtractor() = default;

        std::vector<DrawCommand> collectCommands(Scene& scene);
        
    };      
}