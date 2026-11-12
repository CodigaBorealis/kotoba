#pragma once
#include "Renderer.hpp"
#include "SceneExtractor.hpp"

namespace Kotoba{

    class Window;
    class ResourceManager;

    class RenderOrchestrator{

        public:

        constexpr RenderOrchestrator(Window& window, ResourceManager& resourceManager)
            :
            renderer(window),
            extractor(resourceManager)
            {}

        void render(Scene& scene);

        private:

        Renderer renderer;
        SceneExtractor extractor;
    };
}