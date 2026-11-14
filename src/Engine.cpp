#include "Kotoba/Engine.hpp"
#include "Kotoba/Components/AudioComponents.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include "Kotoba/Audio/AudioPlayer.hpp"
#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Scene/Scene.hpp"
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
        AudioPlayer audio;

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

    void Engine::run(const std::function<void(f32 dt)>& updateCallback){

        while(!impl->window.shouldClose()){

            f32 dt = ::GetFrameTime();

            impl->update();

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

    AudioPlayer& Engine::audio(){

        return impl->audio;
    }

}