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

         const Image* getImage(ResourceID id) const;
         const Texture* getTexture(ResourceID id) const;
         const Font* getFont(ResourceID id) const;
         const Music* getMusic(ResourceID id) const;
         const Sound* getSound(ResourceID id) const;
        
        private:

        struct Impl;
        std::unique_ptr<Impl> impl;

    };
}