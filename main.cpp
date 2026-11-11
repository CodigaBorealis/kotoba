#include <iostream>
#include <memory>
#include "Kotoba/Components/GraphicalComponents.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Renderer/Types.hpp"
#include "Kotoba/Scene/Scene.hpp"
#include "Kotoba/Window/Window.hpp"

int main(){
        
    Kotoba::Window window{{}};

    Kotoba::Renderer renderer{window};
    Kotoba::Scene scene{};

    auto entity = scene.create();
    auto entity2 = scene.create();
    auto entity3 = scene.create();

    Kotoba::Circle circle{100.0f};
    Kotoba::Color color{0,0,0,255};
    Kotoba::TransformComponent transform{{100, 100}, {1,1}, 0.f};

    Kotoba::Point point{{0,0}};
    Kotoba::Color color2{255, 0, 255, 255};

    Kotoba::Line line{{500,100},{100,1000}};
    Kotoba::Color color3{255, 0, 0, 255};

    scene.add<Kotoba::GeometryComponent>(entity, circle);
    scene.add<Kotoba::ColorComponent>(entity, color);
    scene.add<Kotoba::TransformComponent>(entity, transform);

    scene.add<Kotoba::GeometryComponent>(entity2, point);
    scene.add<Kotoba::ColorComponent>(entity2, color2);

    scene.add<Kotoba::GeometryComponent>(entity3, line);
    scene.add<Kotoba::ColorComponent>(entity3, color3);

    auto linePtr = scene.get<Kotoba::GeometryComponent>(entity);

    Kotoba::SceneExtractor extractor{};

    try{
        
        while(!window.shouldClose()){

            renderer.beginFrame();
            renderer.draw();
            renderer.endFrame();
            
            auto commands = extractor.collectCommands(scene);

            renderer.submitBatch(commands);
        }

    }catch(Kotoba::Exception& e){

        std::cout << e.what();
    }

    return 0;
}