#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Renderer/Types.hpp"
#include "Kotoba/Scene/Scene.hpp"
#include <vector>

namespace Kotoba{

    Point generatePoint(const Scene::EntitySlot& entity){


    }

    Line generateLine(const Scene::EntitySlot& entity){

        
    }

    Line generateCircle(const Scene::EntitySlot& entity){

        
    }

    Line generateTriangle(const Scene::EntitySlot& entity){

        
    }

    Rectangle generateRectangle(const Scene::EntitySlot& entity){


    }

    Line generateEllipse(const Scene::EntitySlot& entity){

        
    }

    Line generatePolygon(const Scene::EntitySlot& entity){

        
    }


    Line generateTexture(const Scene::EntitySlot& entity){

        
    }


    Line generateText(const Scene::EntitySlot& entity){

        
    }

    std::vector<DrawCommand> SceneExtractor::collectCommands(Scene& scene){

        std::vector<DrawCommand> result{};

        const auto& entities = scene.getEntities();

        for(u32 x = 0; x  < entities.size(); x ++){

            const auto& slot = entities[x];

            if(!slot.alive) continue;

            Scene::Entity entity{x, slot.generation};

            //auto* transform = scene.get<TextureComponent>(entity);
            //auto* mesh = scene.get<TransformComponent>(entity);

            //if (!transform || !mesh) continue;
            //Impl
        }
    }
}