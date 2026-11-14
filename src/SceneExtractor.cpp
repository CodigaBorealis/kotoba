#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/Audio/Types.hpp"
#include "Kotoba/Components/AudioComponents.hpp"
#include "Kotoba/Input/Input.hpp"
#include "Kotoba/Input/Types.hpp"
#include "Kotoba/Renderer/SceneExtractor.hpp"
#include "Kotoba/ResourceManager/ResourceManager.hpp"
#include "Kotoba/Components/GraphicalComponents.hpp"
#include "Kotoba/Renderer/Types.hpp"
#include "Kotoba/Scene/Scene.hpp"
#include <variant>
#include <vector>

namespace Kotoba{

    std::vector<DrawCommand> SceneExtractor::collectDrawCommands(Scene& scene){
        
        std::vector<DrawCommand> result{};
        
        scene.forEachEntity([&](Scene::Entity entity) {

            bool hasGraphics{false};
            DrawCommand command{};

            if(auto* transform = scene.get<TransformComponent>(entity)){

                hasGraphics = true;
                command.position = transform->position;
                command.scale = transform->scale;
                command.rotation = transform->rotation;
            }

            if(auto* color = scene.get<ColorComponent>(entity)){

                hasGraphics = true;
                command.tint = color->data;
            }

            if(auto* geometry = scene.get<GeometryComponent>(entity)){

                hasGraphics = true;
                command.drawable = std::visit([](const auto& shape) -> Drawable{

                        return shape;

                    },geometry->data);
            }

            if(auto* texture = scene.get<TextureComponent>(entity)){

                hasGraphics = true;
                command.drawable = resources.getTexture(texture->resourceID);
            }

            if(auto* renderStyle = scene.get<RenderStyleComponent>(entity)){
            
                hasGraphics = true;
                if(renderStyle->style == RenderStyleComponent::RenderStyle::Outline){

                    command.outlineOnly = true;

                }else{

                    command.outlineOnly = false;
                    command.outlineColor = renderStyle->color;
                    command.outlineThickness = renderStyle->thickness;
                }
            }

            if(!hasGraphics) return;
            
            result.push_back(std::move(command));
        });

        return result;
    }
    
    std::vector<AudioCommand> SceneExtractor::collectAudioCommands(Scene& scene){

        std::vector<AudioCommand> result{};

        scene.forEachEntity([&](Scene::Entity entity){

            bool hasAudio{false};

            AudioCommand command{};

            if(auto* sound = scene.get<MusicComponent>(entity)){

                hasAudio = true;
                command.data = resources.getMusic(sound->resourceID);
            }

            if(auto* music = scene.get<SoundComponent>(entity)){

                hasAudio = true;
                command.data = resources.getSound(music->resourceID);
            }

            if(auto* playback = scene.get<AudioPlaybackComponent>(entity)){

                hasAudio = true;
                command.looping = playback->looping;
                command.state = playback->state;
                command.play = playback->shouldPlay;
            }

            if(auto* volume = scene.get<AudioVolumeComponent>(entity)){

                hasAudio = true;
                command.volume = volume->volume;
            }

            if(auto* pitch = scene.get<AudioPitchComponent>(entity)){

                hasAudio = true;
                command.pitch = pitch->pitch;
            }


            if(auto* pan = scene.get<AudioPanComponent>(entity)){

                    hasAudio = true;
                    command.pan = pan->pan;
            }

            if(!hasAudio) return;

            result.push_back(std::move(command));
        });

        return result;
    }

    std::vector<InputDevice::Event> SceneExtractor::collectInputCommands(Scene& scene){

        std::vector<InputDevice::Event> result{};

        return result;
    };
}