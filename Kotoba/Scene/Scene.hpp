#pragma once
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Concepts.hpp"
#include <cstddef>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>
#include <limits>

namespace Kotoba{

    class Scene{

        public:

        struct EntitySlot{

            u64 generation{0};
            bool alive{false};
        };

        struct Entity{

            static constexpr u32 InvalidIndex = std::numeric_limits<u32>::max();

            u32 index{InvalidIndex};
            u64 generation{0};    
            bool operator==(const Entity&) const = default;

        };

        bool valid(Entity entity) const{

            if(entity.index >= Entity::InvalidIndex) return false;

            if(entity.index >= entities.size()) return false;

            const auto& slot = entities[entity.index];

            return slot.alive && slot.generation == entity.generation;
        }

        const std::vector<EntitySlot>& getEntities() const{

            return entities;
        }   
        
        void clear(){

            for(auto& [type, storage] : componentStorages){

                storage->clear();
            }

            freeEntities.clear();

            for(usize x = 0; x < entities.size(); x ++){

                auto& slot = entities[x];

                if(slot.alive) slot.generation ++;

                slot.alive = false;

                freeEntities.push_back(x);
            }
        }

        Scene() = default;

        Entity create(){

            u32 index;

            if(!freeEntities.empty()){

                index = freeEntities.back();
                freeEntities.pop_back();

            }else{

                if(entities.size() >= Entity::InvalidIndex) throw SceneException("Maximum entity capacity reached", ErrorCode::SceneEntityCreationFailed);

                index = static_cast<u32>(entities.size());
                entities.emplace_back();
            }

            auto& slot = entities[index];
            slot.alive = true;

            return Entity{index, slot.generation};
        }
        
        bool destroy(Entity entity){

            if(!valid(entity)) return false;

            for(auto& [type, storage] : componentStorages){

                storage->remove(entity.index);
            }

            auto& slot = entities[entity.index];

            slot.alive = false;
            slot.generation ++;

            freeEntities.push_back(entity.index);

            return true;
        }

        template<ComponentType T, typename... Args>

        T& add(Entity entity, Args&&... args){

            if(!valid(entity)) throw SceneException("Invalid entity", ErrorCode::SceneEntityCreationFailed);

            return getStorage<T>().add(entity.index, std::forward<Args>(args)...);
        }

        template<ComponentType T, typename... Args>

        T& emplace(Entity entity, Args&&... args){

            if(!valid(entity)) throw SceneException("Invalid entity", ErrorCode::SceneEntityCreationFailed);

            return getStorage<T>().emplace(entity.index, std::forward<Args>(args)...);
        }

        template<ComponentType T>

        T* get(Entity entity){

            if(!valid(entity)) return nullptr;

            auto it = componentStorages.find(typeid(T));

            if(it == componentStorages.end()) return nullptr;

            auto& storage = static_cast<ComponentStorage<T>&>(*it->second);

            return storage.get(entity.index);
        }

        template<ComponentType T>

        const T* get(Entity entity) const{


            if(!valid(entity)) return nullptr;

            auto it = componentStorages.find(typeid(T));

            if(it == componentStorages.end()) return nullptr;

            auto& storage = static_cast<const ComponentStorage<T>&>(*it->second);

            return storage.get(entity.index);
        }

        template<ComponentType T>

        bool remove(Entity entity){

            if(!valid(entity)) return false;

            auto it = componentStorages.find(typeid(T));

            if(it == componentStorages.end()) return false;

            return it->second->remove(entity.index);
            
        }

        template<ComponentType T>

        bool has(Entity entity) const{

            return get<T>(entity) != nullptr;
        }

        private:

        struct IComponentStorage{

            virtual ~IComponentStorage() = default;

            virtual bool remove(u32 entity) = 0;
            virtual void clear() = 0;
        };

        template<typename T> struct ComponentStorage : IComponentStorage{

            std::unordered_map<u32, T> components{};
        // Returns the existing component or constructs a new one.

            template<typename... Args>
            T& add(u32 entity, Args&&... args){

                return components.try_emplace(entity, std::forward<Args>(args)...).first->second;
            }
        // Constructs a component only if one doesn't already exist.
            template<typename... Args>

            T& emplace(u32 entity, Args&&... args){

                auto [it, inserted] = components.try_emplace(entity, std::forward<Args>(args)...);

                if(!inserted) throw SceneException("Component already exists for entity: " + std::to_string(entity), ErrorCode::SceneComponentAlreadyExists);

                return it->second;
            }

            T* get(u32 entity){

                auto it = components.find(entity);

                if(it == components.end()) return nullptr;

                return &it->second;
            }

            const T* get(u32 entity) const{

                auto it = components.find(entity);

                if(it == components.end()) return nullptr;

                return &it->second;
            };

            bool remove(u32 entity) override{

                return components.erase(entity) != 0;
            }

            void clear() override{

                components.clear();
            }
        };

        template<typename T>

        ComponentStorage<T>& getStorage(){

            const std::type_index type = typeid(T);

            auto it = componentStorages.find(type);

            if(it == componentStorages.end()){

                auto storage = std::make_unique<ComponentStorage<T>>();

                auto* ptr = storage.get();

                componentStorages.emplace(type, std::move(storage));

                return *ptr;
            }

            return static_cast<ComponentStorage<T>&>(*it->second);
        }
        
        std::vector<EntitySlot> entities{};
        std::vector<u32> freeEntities{};
        std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentStorages{};
    };
}