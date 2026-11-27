#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Input/Input.hpp"
#include <memory>
#include <vector>
#include <functional>

namespace Kotoba{

    class EventDispatcher{

        public:

        using Condition = std::function<bool(const InputDevice::Event&)>;

        using Action = std::function<void()>;

        EventDispatcher();
        ~EventDispatcher();

        void bind(Condition condition, Action action);

        void submit(InputDevice::Event event);
        void submitBatch(std::vector<InputDevice::Event> events);
        void dispatch();

        private:

        struct Impl;

        std::unique_ptr<Impl> impl;

    };

    namespace InputConditions{

        namespace Detail{

            inline const InputDevice::ButtonState* findButtonState(const InputDevice::Event& event, const InputDevice::InputSignal& signal){

                if(event.signal != signal) return nullptr;

                return &event.buttonState;
            }
        }

        inline EventDispatcher::Condition SignalPressed(InputDevice::InputSignal signal){

        return [signal = std::move(signal)](const InputDevice::Event& event){

            const auto* state = Detail::findButtonState(event, signal);

            return state && state->state == InputDevice::InputState::Pressed;
        };
    }

        inline EventDispatcher::Condition SignalDown(InputDevice::InputSignal signal){

            return [signal = std::move(signal)](const InputDevice::Event& event){

                const auto* state = Detail::findButtonState(event, signal);

                return state && (state->state == InputDevice::InputState::Pressed || state->state == InputDevice::InputState::Down);
            };
        }

        inline EventDispatcher::Condition SignalReleased(InputDevice::InputSignal signal){

            return [signal = std::move(signal)](const InputDevice::Event& event){
                
                const auto* state = Detail::findButtonState(event, signal);
                
                return state && state->state == InputDevice::InputState::Released;
            };
        }

        inline EventDispatcher::Condition SignalHeld(InputDevice::InputSignal signal, Seconds holdtime){

            return [signal = std::move(signal), holdtime](const InputDevice::Event& event){

                const auto* state = Detail::findButtonState(event, signal);

                return state && (state->state == InputDevice::InputState::Pressed || state->state == InputDevice::InputState::Down) && state->heldDuration >= holdtime;
            };
        }
            //Logical Combinators
            inline EventDispatcher::Condition And(EventDispatcher::Condition c1, EventDispatcher::Condition c2){

                return [c1, c2](const InputDevice::Event& event){

                    return c1(event) && c2(event);
                };
            }

            inline EventDispatcher::Condition Or(EventDispatcher::Condition c1, EventDispatcher::Condition c2){

                return [c1, c2](const InputDevice::Event& event){

                    return c1(event) || c2(event);
                };
            }

            inline EventDispatcher::Condition Not(EventDispatcher::Condition c){

                return [c](const InputDevice::Event& event){
                    
                    return !c(event);
                };
            }
        }
}