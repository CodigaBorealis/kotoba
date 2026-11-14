#include "Kotoba/Input/EventDispatcher.hpp"
#include <vector>

namespace Kotoba{

    struct EventDispatcher::Impl{

        struct Binding{

            Condition condition{};
            Action action{};
        };

        std::vector<Binding> bindings{};
        InputDevice::Event currentEvent{};
        bool hasEvent{false};
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

        impl->currentEvent = std::move(event);
        impl->hasEvent = true;
        
    }   

    void EventDispatcher::submitBatch(std::vector<InputDevice::Event> events){

        impl->currentEvent = std::move(events).back();
        impl->hasEvent = true;
    }

    void EventDispatcher::dispatch(){

        if(!impl->hasEvent) return;

        for(const auto& binding : impl->bindings){

            if(binding.condition(impl->currentEvent)){

                binding.action();
            }
        }

        impl->hasEvent = false;
    }

}