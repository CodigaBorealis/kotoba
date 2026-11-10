#include <iostream>
#include <memory>
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Scene/Scene.hpp"
#include "Kotoba/Window/Window.hpp"

int main(){
        
    Kotoba::Window window{{}};

    Kotoba::Renderer renderer{window};
    Kotoba::Scene scene{};

    auto entity = scene.create();

    Kotoba::Renderer::Line line{{0,0}, {1000, 1000}, {255, 0, 0, 255}};

    scene.add<Kotoba::Renderer::Line>(entity, line);

    auto* linePtr = scene.get<Kotoba::Renderer::Line>(entity);

    std::cout << "RED VALUE: " << static_cast<int>(linePtr->color.r);

    try{
        
        while(!window.shouldClose()){
            
            renderer.queue(Kotoba::Renderer::Line{{0,0}, {1000,1000},{255, 255, 255, 255}});

            renderer.beginFrame();
            renderer.draw();
            renderer.endFrame();
        }

    }catch(Kotoba::Exception& e){

        std::cout << e.what();
    }

    return 0;
}