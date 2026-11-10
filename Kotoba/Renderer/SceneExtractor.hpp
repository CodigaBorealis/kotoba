#pragma once

#include "Types.hpp"
#include <vector>

namespace Kotoba{

    class Scene;

    class SceneExtractor{

        public:

        std::vector<DrawCommand> collectCommands(Scene& scene);

        private:
        
        usize drawableCount{};
    };
}