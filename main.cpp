#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Kotoba.hpp"
#include <iostream>

int main(){

        try{

        Kotoba::Engine engine{};

        engine.window().addFlags(Kotoba::Window::Flag::Resizable | Kotoba::Window::Flag::Fullscreen);
        auto& resourceManager = engine.resources();
        
        auto& scene = engine.scene();

        auto textureID = resourceManager.loadTexture("/home/xd/Pictures/wallhaven-dp81rj.png");
        auto musicID = resourceManager.loadMusic("/home/xd/Downloads/bgm.ogg");
        auto fontID = resourceManager.loadFont("/home/xd/Downloads/font.ttf");

        auto entity = scene.create();
        auto entity2 = scene.create();
        auto entity3 = scene.create();
        auto entity4 = scene.create();
        auto entity5 = scene.create();
        //something something
        Kotoba::Circle circle{100.0f};
        Kotoba::Color color{0,0,0,255};
        Kotoba::TransformComponent transform{{100, 100}, {1, 1}, 0.f};
        Kotoba::GeometryComponent rect{Kotoba::Rectangle{{1000,1000}}};
        Kotoba::AudioPlaybackComponent playback{Kotoba::PlaybackState::Playing, false, true};
        Kotoba::MusicComponent musicComp{musicID};
        Kotoba::AudioVolumeComponent volume{100};

        Kotoba::Point point{{0,0}};
        Kotoba::Color color2{255, 0, 255, 255};

        Kotoba::Color color3{255, 0, 0, 255};

        Kotoba::TextComponent text{"hello", 24, 1, fontID};
        Kotoba::Color color4{0,0,0, 255};

        scene.add<Kotoba::GeometryComponent>(entity, circle);
        scene.add<Kotoba::ColorComponent>(entity, color);

        scene.add<Kotoba::GeometryComponent>(entity2, point);
        scene.add<Kotoba::ColorComponent>(entity2, color2);

        scene.add<Kotoba::TextureComponent>(entity3, textureID);
        scene.add<Kotoba::ColorComponent>(entity3, color3);
        scene.add<Kotoba::TransformComponent>(entity3, transform);
        scene.add<Kotoba::GeometryComponent>(entity3, rect);

        scene.add<Kotoba::MusicComponent>(entity4, musicComp);
        scene.add<Kotoba::AudioPlaybackComponent>(entity4, playback);
        scene.add<Kotoba::AudioVolumeComponent>(entity4, volume);
        
        scene.add<Kotoba::TextComponent>(entity5, text);
        scene.add<Kotoba::ColorComponent>(entity5, color4);
        scene.add<Kotoba::TransformComponent>(entity5, transform);

        Kotoba::Seconds time{1};

        engine.run([&time, &engine](Kotoba::Seconds dt){

            std::cout << "Application has been running for: " << engine.clock().unscaledElapsedTime() << "\n";
        });

    }catch(Kotoba::Exception& e){

        std::cout << e.what();
        std::cout << "CODE:" <<  static_cast<Kotoba::u32>(e.getCode());
    }

    return 0;
}