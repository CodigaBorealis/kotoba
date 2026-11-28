#include "Kotoba/Input/EventDispatcher.hpp"
#include "Kotoba/Input/Types.hpp"
#include <vector>

namespace Kotoba{

    struct EventDispatcher::Impl{

        struct Binding{

            Condition condition{};
            Action action{};
        };

        std::vector<Binding> bindings{};
        std::vector<InputDevice::Event> queue{};    

    };

    EventDispatcher::EventDispatcher()
        :
        impl(std::make_unique<Impl>())
        {}
    
    EventDispatcher::~EventDispatcher() = default;
    
    void EventDispatcher::bind(Condition condition, Action action){

        impl->bindings.push_back({std::move(condition), std::move(action)});
    }

    void EventDispatcher::submit(InputDevice::Event event){

        impl->queue.push_back(std::move(event));    
    }   

    void EventDispatcher::submitBatch(std::vector<InputDevice::Event> events){

        if(events.empty()) return;

        impl->queue.insert(impl->queue.end(), std::make_move_iterator(events.begin()), std::make_move_iterator(events.end()));

    }

    void EventDispatcher::dispatch(){

        std::vector<InputDevice::Event> events{};

        events.swap(impl->queue);

        for(const auto& event : events){

            for(const auto& binding : impl->bindings){

                if(binding.condition && binding.condition(event)){

                    if(!binding.action) return;

                    binding.action();
                }
            }
        }
    }

}