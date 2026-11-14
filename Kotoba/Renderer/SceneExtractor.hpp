#pragma once

#include "Kotoba/Audio/Types.hpp"
#include "Kotoba/Input/Types.hpp"
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

        std::vector<DrawCommand> collectDrawCommands(Scene& scene);//Extracts rendering data from the entities inside a scene
        std::vector<AudioCommand> collectAudioCommands(Scene& scene);
        std::vector<InputDevice::Event> collectInputCommands(Scene& scene);
        
        private:
        
        ResourceManager& resources;
    };      
}   
