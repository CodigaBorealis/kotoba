#pragma once
#include "Window/Window.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Audio/AudioPlayer.hpp"
#include "Scene/Scene.hpp"
#include <functional>
#include <memory>
namespace Kotoba{
    
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
        void run(const std::function<void(f32 dt)>& updateCallback = {});

        Window& window();
        ResourceManager& resources();
        Scene& scene();
        AudioPlayer& audio();

        private:

        struct Impl;

        std::unique_ptr<Impl> impl;
    };
}