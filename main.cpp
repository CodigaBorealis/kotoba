#include <iostream>
#include "Kotoba/Components/GraphicalComponents.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Engine.hpp"
#include "Kotoba/Renderer/RenderOrchestrator.hpp"
#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Renderer/Types.hpp"
#include "Kotoba/ResourceManager/ResourceManager.hpp"
#include "Kotoba/Scene/Scene.hpp"

int main(){
    
    try{

        Kotoba::Engine engine{};

        auto& resourceManager = engine.resources();
        auto& scene = engine.scene();
        auto textureID = resourceManager.loadTexture("/home/xd/Pictures/aigis.png");

        auto entity = scene.create();
        auto entity2 = scene.create();
        auto entity3 = scene.create();

        Kotoba::Circle circle{100.0f};
        Kotoba::Color color{0,0,0,255};
        Kotoba::TransformComponent transform{{100, 100}, {1,1}, 0.f};

        Kotoba::Point point{{0,0}};
        Kotoba::Color color2{255, 0, 255, 255};

        Kotoba::Color color3{255, 0, 0, 255};

        scene.add<Kotoba::GeometryComponent>(entity, circle);
        scene.add<Kotoba::ColorComponent>(entity, color);
        scene.add<Kotoba::TransformComponent>(entity, transform);

        scene.add<Kotoba::GeometryComponent>(entity2, point);
        scene.add<Kotoba::ColorComponent>(entity2, color2);

        scene.add<Kotoba::TextureComponent>(entity3, textureID);
        scene.add<Kotoba::ColorComponent>(entity3, color3);

        engine.run();

    }catch(Kotoba::Exception& e){

        std::cout << e.what();
    }

    return 0;
}