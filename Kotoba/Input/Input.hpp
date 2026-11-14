#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Types.hpp"
#include <unordered_map>

namespace Kotoba{

    class Input{

        public:

        void Update();//Polls the frame
        const InputDevice::Event& getEvent();//Returns a snapshot with the information of everything that happened in the frame

        private:

        bool isPressed(const InputDevice::InputSignal& inputQuery);//Returns true if the given input is pressed during the frame
        bool isDown(const InputDevice::InputSignal& inputQuery);//Returns true if the given input is down during the frame
        bool isUp(const InputDevice::InputSignal& inputQuery);//Returns true if the given input is up during the frame
        bool isReleased(const InputDevice::InputSignal& inputQuery);//Returns true if the given input is released during the frame

        struct ButtonTracker{

            bool wasDown{false};
            Miliseconds heldTime{0};
        };

        using MouseButton = InputDevice::Mouse::Button;
        using KeyboardButton = InputDevice::Keyboard::Button;

        std::unordered_map<MouseButton, ButtonTracker> mouseTrackers{};
        std::unordered_map<KeyboardButton, ButtonTracker> keyboardTrackers{};

        template<typename IsDownFunction>

        InputDevice::ButtonState updateButton(ButtonTracker& tracker, IsDownFunction isDown, f32 deltaTime){

            constexpr Miliseconds CLICK_THRESHOLD{0.25};

            const bool down = isDown();

            InputDevice::ButtonState result{};

            if(down){

                if(!tracker.wasDown){

                    tracker.heldTime = Miliseconds{0};

                    result.state = InputDevice::InputState::Pressed;

                }else{

                    tracker.heldTime += Miliseconds{deltaTime};

                    result.state = InputDevice::InputState::Down;
                }

                result.heldDuration = Miliseconds{tracker.heldTime};
                result.clicked = false;

            }else{

                if(tracker.wasDown){

                    result.state = InputDevice::InputState::Released;

                    result.heldDuration = Miliseconds{tracker.heldTime};

                    result.clicked = tracker.heldTime <= CLICK_THRESHOLD;

                    tracker.heldTime = Miliseconds{0};

                }else{

                    result.state = InputDevice::InputState::Up;
                    result.heldDuration = Miliseconds{0};
                    result.clicked = false;
                }
            }

        tracker.wasDown = down;

        return result;
    }
        InputDevice::Event currentEvent;
    };
}