#include "Kotoba/Engine.hpp"
#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Renderer/SceneExtractor.hpp"
#include <raylib.h>

namespace Kotoba{

    struct Engine::Impl{

        explicit Impl(const EngineConfig& config)
            :
            window(config.windowConfig),
            renderer(window),
            extractor(resourceManager)
            {}

        Window window;
        ResourceManager resourceManager;
        Scene activeScene;
        Renderer renderer;
        SceneExtractor extractor;

        void render(){

            auto commands = extractor.collectCommands(activeScene);

            renderer.submitBatch(commands);

            renderer.beginFrame();
            renderer.draw();
            renderer.endFrame();
        }
    };

    Engine::Engine(const EngineConfig& config)
        :
        impl(std::make_unique<Impl>(config))
        {}

    Engine::~Engine() = default;

    void Engine::run(const std::function<void(float dt)>& updateCallback){

        while(!impl->window.shouldClose()){

            float dt = ::GetFrameTime();

            if(updateCallback) updateCallback(dt);

            impl->render();
        }
    }

    Window& Engine::window(){

        return impl->window;
    }

    ResourceManager& Engine::resources(){

        return impl->resourceManager;
    }

    Scene& Engine::scene(){

        return impl->activeScene;
    }

}