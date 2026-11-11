#include "Kotoba/ResourceManager/ResourceManager.hpp"
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Types.hpp"
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <set>
#include <utility>
#include <variant>
namespace Kotoba{

    struct ResourceManager::Impl{
        
        using Resource = std::variant<std::shared_ptr<Image>, std::shared_ptr<Texture>, std::shared_ptr<Font>, std::shared_ptr<Music>, std::shared_ptr<Sound>>;

        template<typename T>
                
        std::shared_ptr<T> get(ResourceID id) const{

            auto it = resources.find(id);

            if(it == resources.end()) return nullptr;

            if(auto resource = std::get_if<std::shared_ptr<T>>(&it->second)) return *resource;
                    
            throw ResourceException("This id belongs to a resource of a different type: " + std::to_string(id), ErrorCode::ResourceBadRequest);
        }

        template<typename T>

        ResourceID loadResource(const std::filesystem::path& file){

            auto normalized = file.lexically_normal().string();

            auto key = std::make_pair(normalized, std::type_index(typeid(T)));


            if(seenFiles.contains(key)) throw ResourceException("This file has already been loaded: " + normalized, ErrorCode::ResourceDuplicatedResource);

            auto resource = std::make_shared<T>(file);

            ResourceID id = ++lastID;

            resources.emplace(id, std::move(resource));
            seenFiles.emplace(std::move(key));

            return lastID;  
        }

        std::set<std::pair<std::string, std::type_index>> seenFiles{};
        std::unordered_map<ResourceID, Resource> resources{};

        ResourceID lastID{0};
    };

    ResourceID ResourceManager::loadImage(const std::filesystem::path& file){

        //Someone else manages actually veryfing that the paths are valid
        //Assume they are

        return impl->loadResource<Image>(file);
    }

    ResourceID ResourceManager::loadTexture(const std::filesystem::path& file){

        //Someone else manages actually veryfing that the paths are valid
        //Assume they are

        return impl->loadResource<Texture>(file);

    }

    ResourceID ResourceManager::loadFont(const std::filesystem::path& file){
        //Someone else manages actually veryfing that the paths are valid
        //Assume they are

        return impl->loadResource<Font>(file);

    }

    ResourceID ResourceManager::loadMusic(const std::filesystem::path& file){
        //Someone else manages actually veryfing that the paths are valid
        //Assume they are

        return impl->loadResource<Music>(file);

    }

    ResourceID ResourceManager::loadSound(const std::filesystem::path& file){
        //Someone else manages actually veryfing that the paths are valid
        //Assume they are

        return impl->loadResource<Sound>(file);

    }

    std::shared_ptr<Image> ResourceManager::getImage(ResourceID id) const{

        return impl->get<Image>(id);
    }

    std::shared_ptr<Texture> ResourceManager::getTexture(ResourceID id) const{

        return impl->get<Texture>(id);
    }

    std::shared_ptr<Font> ResourceManager::getFont(ResourceID id) const{

        return impl->get<Font>(id);
    }

    std::shared_ptr<Music> ResourceManager::getMusic(ResourceID id) const{

        return impl->get<Music>(id);
    }

    std::shared_ptr<Sound> ResourceManager::getSound(ResourceID id) const{

        return impl->get<Sound>(id);
    }
}