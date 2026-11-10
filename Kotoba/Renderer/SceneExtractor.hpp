#pragma once

#include "Types.hpp"
#include <vector>

namespace Kotoba{

    class Scene;

    class SceneExtractor{

        public:

        const std::vector<DrawCommand>& collectCommands(Scene& scene);
        
        private:

        std::vector<DrawCommand> commands{};
    };      
}