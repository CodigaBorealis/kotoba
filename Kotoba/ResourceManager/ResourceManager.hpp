#pragma once
#include "Kotoba/Core/Resources.hpp"
#include "Kotoba/Core/Types.hpp"
#include <memory>

namespace Kotoba{

    class ResourceManager{

        public:

        ResourceID loadImage(const std::filesystem::path& file);
        ResourceID loadTexture(const std::filesystem::path& file);
        ResourceID loadFont(const std::filesystem::path& file);
        ResourceID loadMusic(const std::filesystem::path& file);
        ResourceID loadSound(const std::filesystem::path& file);

        std::shared_ptr<Image> getImage(ResourceID id) const;
        std::shared_ptr<Texture> getTexture(ResourceID id) const;
        std::shared_ptr<Font>  getFont(ResourceID id) const;
        std::shared_ptr<Music> getMusic(ResourceID id) const;
        std::shared_ptr<Sound> getSound(ResourceID id) const;
        
        private:

        struct Impl;
        std::unique_ptr<Impl> impl;

    };
}