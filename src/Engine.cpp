#include "Kotoba/Engine.hpp"
#include "Kotoba/Clock/Clock.hpp"
#include "Kotoba/Components/Components.hpp"
#include "Kotoba/Audio/AudioPlayer.hpp"
#include "Kotoba/Input/EventDispatcher.hpp"
#include "Kotoba/Input/Input.hpp"
#include "Kotoba/Input/Types.hpp"
#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Scene/Scene.hpp"
#include "Kotoba/ResourceManager/ResourceManager.hpp"
#include "Kotoba/Input/Input.hpp"
#include <variant>
#include <vector>
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
        Input input;
        EventDispatcher events;
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

        void pollInputAndDispatch(){

            input.update();

            std::vector<InputDevice::Event> frameEvents{};
            
            const auto& currentState = input.getEvent();

            activeScene.forEachEntity([&](Scene::Entity entity) {
                
                auto* comp = activeScene.get<InputComponent>(entity);

                if(!comp) return;

                if(!comp->eventQueue.empty()){

                    frameEvents.insert(frameEvents.end(), std::make_move_iterator(comp->eventQueue.begin()), std::make_move_iterator(comp->eventQueue.end()));

                    comp->eventQueue.clear();
                }
                
                for(const auto& signal : comp->watchedSignals){

                    InputDevice::ButtonState buttonState{};

                    if(input.isPressed(signal)){

                        buttonState.state = InputDevice::InputState::Pressed;

                    }else if(input.isReleased(signal)){

                        buttonState.state = InputDevice::InputState::Released;

                    }else if(input.isDown(signal)){

                        buttonState.state = InputDevice::InputState::Down;

                    }else{

                        buttonState.state = InputDevice::InputState::Up;
                    }

                    if(currentState.signal == signal){

                        buttonState.heldDuration = currentState.buttonState.heldDuration;
                        buttonState.clicked = currentState.buttonState.clicked;
                    }

                    InputDevice::Event event{};
                    event.signal = signal;
                    event.buttonState = buttonState;
                    event.mousePosition = currentState.mousePosition;
                    event.mouseDelta = currentState.mouseDelta;

                    frameEvents.push_back(std::move(event));
                }
            });

            events.submitBatch(std::move(frameEvents));
            events.dispatch();
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
            
            impl->pollInputAndDispatch();
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

    EventDispatcher& Engine::dispatcher(){

        return impl->events;
    }
}   