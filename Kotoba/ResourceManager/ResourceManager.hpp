#pragma once
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Core/Types.hpp"
#include <memory>

namespace Kotoba{

    class ResourceManager{

        public:

        ResourceManager();
        ~ResourceManager();
        
        ResourceID loadImage(const std::filesystem::path& file);
        ResourceID loadTexture(const std::filesystem::path& file);
        ResourceID loadFont(const std::filesystem::path& file);
        ResourceID loadMusic(const std::filesystem::path& file);
        ResourceID loadSound(const std::filesystem::path& file);

         Image* getImage(ResourceID id) const;
         Texture* getTexture(ResourceID id) const;
         Font* getFont(ResourceID id) const;
         Music* getMusic(ResourceID id) const;
         Sound* getSound(ResourceID id) const;
        
        private:

        struct Impl;
        std::unique_ptr<Impl> impl;

    };
}