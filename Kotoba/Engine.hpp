#pragma once
#include <functional>
#include <memory>
#include "Kotoba/Window/Window.hpp"
#include "Kotoba/Core/Types.hpp"

namespace Kotoba{

    class ResourceManager;
    class Scene;
    class AudioPlayer;
    class Clock;
    
    struct EngineConfig{

        Window::Config windowConfig{};
    };

    class Engine{

        public:

        explicit Engine(const EngineConfig& config = {});
        ~Engine();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(Engine&&) = delete;
        //Lifecycle function
        void run(const std::function<void(Seconds dt)>& updateCallback = {});

        Window& window();
        ResourceManager& resources();
        Scene& scene();
        AudioPlayer& audio();
        Clock& clock();

        private:

        struct Impl;

        std::unique_ptr<Impl> impl;
    };
}