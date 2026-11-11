#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Components/GraphicalComponents.hpp"
#include "Kotoba/Renderer/Types.hpp"
#include "Kotoba/Scene/Scene.hpp"
#include <variant>
#include <vector>
#include <iostream>

namespace Kotoba{

    std::vector<DrawCommand> SceneExtractor::collectCommands(Scene& scene){
        
        std::vector<DrawCommand> result{};

        const auto& entities = scene.getEntities();
        
        for(u32 x = 0; x  < entities.size(); x ++){

            const auto& slot = entities[x];

            if(!slot.alive) continue;

            Scene::Entity entity{x, slot.generation};

            DrawCommand command{};

            if(auto* transform = scene.get<TransformComponent>(entity)){

                command.position = transform->position;
                command.scale = transform->scale;
                command.rotation = transform->rotation;
            }

            if(auto* color = scene.get<ColorComponent>(entity)){

                command.tint = color->data;
            }

            if(auto* geometry = scene.get<GeometryComponent>(entity)){

                command.drawable = std::visit([](const auto& shape) -> Drawable{
                    
                    return shape;
                    
                }, geometry->data);
            }

            if(auto* renderStyle = scene.get<RenderStyleComponent>(entity)){

                if(renderStyle->style == RenderStyleComponent::RenderStyle::Outline){

                    command.outlineOnly = true;

                }else{

                    command.outlineOnly = false;
                    command.outlineColor = renderStyle->color;
                    command.outlineThickness = renderStyle->thickness;
                }
            }

            result.push_back(std::move(command));
        }
        
        return result;
    }
}