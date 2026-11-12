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
        
        using Resource = std::variant<std::unique_ptr<Image>, std::unique_ptr<Texture>, std::unique_ptr<Font>, std::unique_ptr<Music>, std::unique_ptr<Sound>>;

        template<typename T>
                
        const T* get(ResourceID id) const{

            auto it = resources.find(id);

            if(it == resources.end()) return nullptr;

            if(auto* resource = std::get_if<std::unique_ptr<T>>(&it->second)) return resource->get();
                    
            throw ResourceException("This id belongs to a resource of a different type: " + std::to_string(id), ErrorCode::ResourceBadRequest);
        }

        template<typename T>

        ResourceID loadResource(const std::filesystem::path& file){

            if(file.empty()) throw ResourceException("The path to a file cannot be empty", ErrorCode::ResourceLoadFailed);

            auto normalized = file.lexically_normal().string();

            auto key = std::make_pair(normalized, std::type_index(typeid(T)));


            if(seenFiles.contains(key)) throw ResourceException("This file has already been loaded: " + normalized, ErrorCode::ResourceDuplicatedResource);

            auto resource = std::make_unique<T>(file);

            ResourceID id = ++lastID;

            resources.emplace(id, std::move(resource));
            seenFiles.emplace(std::move(key));

            return lastID;  
        }

        std::set<std::pair<std::string, std::type_index>> seenFiles{};
        std::unordered_map<ResourceID, Resource> resources{};

        ResourceID lastID{0};
    };

    ResourceManager::ResourceManager()
        :
        impl(std::make_unique<Impl>())
        {}

    ResourceManager::~ResourceManager() = default;   
    
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

    const Image* ResourceManager::getImage(ResourceID id) const{

        return impl->get<Image>(id);
    }

    const Texture* ResourceManager::getTexture(ResourceID id) const{

        return impl->get<Texture>(id);
    }

    const Font* ResourceManager::getFont(ResourceID id) const{

        return impl->get<Font>(id);
    }

    const Music* ResourceManager::getMusic(ResourceID id) const{

        return impl->get<Music>(id);
    }

    const Sound* ResourceManager::getSound(ResourceID id) const{

        return impl->get<Sound>(id);
    }
}