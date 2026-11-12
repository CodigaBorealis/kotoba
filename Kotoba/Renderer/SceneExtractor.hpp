#pragma once

#include "Types.hpp"
#include <vector>

namespace Kotoba{

    struct ResourceManager;

    class Scene;

    class SceneExtractor{

        public:

        constexpr SceneExtractor(ResourceManager& resources)
            :
            resources(resources)
            {}

        std::vector<DrawCommand> collectCommands(Scene& scene);//Extracts rendering data from the entities inside a scene
        ResourceManager& resources;
    };      
}