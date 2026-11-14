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

            //KeyboardState Evaluators
            inline EventDispatcher::Condition KeyPressed(InputDevice::Keyboard::Button key){

                return [key](const InputDevice::Event& event){

                    auto it = event.keyboard.buttons.find(key);
                    return it != event.keyboard.buttons.end() && it->second.state == InputDevice::InputState::Pressed;
                };
            }

            inline EventDispatcher::Condition KeyDown(InputDevice::Keyboard::Button key){

                return [key](const InputDevice::Event& event){

                    auto it = event.keyboard.buttons.find(key);

                    return it != event.keyboard.buttons.end() &&  (it->second.state == InputDevice::InputState::Pressed || it->second.state == InputDevice::InputState::Down);
                };
            }

            inline EventDispatcher::Condition KeyReleased(InputDevice::Keyboard::Button key){

                return [key](const InputDevice::Event& event){

                    auto it = event.keyboard.buttons.find(key);

                    return it != event.keyboard.buttons.end() && it->second.state == InputDevice::InputState::Released;
                };
            }

            inline EventDispatcher::Condition KeyUp(InputDevice::Keyboard::Button key){

                return [key](const InputDevice::Event& event){

                    auto it = event.keyboard.buttons.find(key);

                    return it != event.keyboard.buttons.end() &&  (it->second.state == InputDevice::InputState::Released || it->second.state == InputDevice::InputState::Up);                
                };
            }

            //MouseState Evaluators
            inline EventDispatcher::Condition MousePressed(InputDevice::Mouse::Button button){

                return [button](const InputDevice::Event& event){

                    auto it = event.mouse.buttons.find(button);
                    return it != event.mouse.buttons.end() && it->second.state == InputDevice::InputState::Pressed;
                };

            }

            inline EventDispatcher::Condition MouseDown(InputDevice::Mouse::Button button){

                return [button](const InputDevice::Event& event){

                    auto it = event.mouse.buttons.find(button);

                    return it != event.mouse.buttons.end() &&  (it->second.state == InputDevice::InputState::Pressed || it->second.state == InputDevice::InputState::Down);
                };

            }

            inline EventDispatcher::Condition MouseUp(InputDevice::Mouse::Button button){

                return [button](const InputDevice::Event& event){

                    auto it = event.mouse.buttons.find(button);
                    return it != event.mouse.buttons.end() && it->second.state == InputDevice::InputState::Up;
                };

            }

            inline EventDispatcher::Condition mouseReleased(InputDevice::Mouse::Button button){

                return [button](const InputDevice::Event& event){

                    auto it = event.mouse.buttons.find(button);

                    return it != event.mouse.buttons.end() && it->second.state == InputDevice::InputState::Released;
                };
            }

            inline EventDispatcher::Condition MouseClicked(InputDevice::Mouse::Button button){

                return [button](const InputDevice::Event& event){

                    auto it = event.mouse.buttons.find(button);

                    return it != event.mouse.buttons.end() && it->second.clicked;
                };
            }

            inline EventDispatcher::Condition MouseHeld(InputDevice::Mouse::Button button, Miliseconds holdtime){

                return [button, holdtime](const InputDevice::Event& event){

                    auto it = event.mouse.buttons.find(button);

                    return it != event.mouse.buttons.end() && 
                    (it->second.state == InputDevice::InputState::Pressed || it->second.state == InputDevice::InputState::Down) && 
                    it->second.heldDuration >= holdtime;
                };
            }
            
            inline EventDispatcher::Condition MouseMoved(){

                return [](const InputDevice::Event& event){

                    return event.mouse.delta.x != 0 || event.mouse.delta.y != 0;
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