#include "Kotoba/Engine.hpp"
#include "Kotoba/Clock/Clock.hpp"
#include "Kotoba/Components/Components.hpp"
#include "Kotoba/Audio/AudioPlayer.hpp"
#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Scene/Scene.hpp"
#include "Kotoba/ResourceManager/ResourceManager.hpp"

namespace Kotoba{
//Should order this better eventually
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
        AudioPlayer audio;
        Clock clock;

        void render(){

            renderer.beginFrame();

            auto commands = extractor.collectDrawCommands(activeScene);
            renderer.submitBatch(commands);

            renderer.draw();
            renderer.endFrame();
        }

        void update(){

            auto audioCommands= extractor.collectAudioCommands(activeScene); 

            audio.submitBatch(audioCommands);
            audio.execute();

            activeScene.forEachEntity([this](Scene::Entity entity){

                if(auto* playback = activeScene.get<AudioPlaybackComponent>(entity)){

                    if(playback->shouldPlay) playback->shouldPlay = false;
                }
            });
        }
    };

    Engine::Engine(const EngineConfig& config)
        :
        impl(std::make_unique<Impl>(config))
        {}

    Engine::~Engine() = default;

    void Engine::run(const std::function<void(Seconds dt)>& updateCallback){

        while(!impl->window.shouldClose()){

            impl->clock.tick();

            impl->update();

            if(updateCallback) updateCallback(impl->clock.deltaTime());

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

    AudioPlayer& Engine::audio(){

        return impl->audio;
    }

    Clock& Engine::clock(){

        return impl->clock;
    }

}