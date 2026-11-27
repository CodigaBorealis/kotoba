#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Types.hpp"
#include <unordered_map>
#include <vector>

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
            Seconds heldTime{0};
        };

        using MouseButton = InputDevice::Mouse::Button;
        using KeyboardButton = InputDevice::Keyboard::Button;

        std::vector<InputDevice::Event> frameEvents{};

        template<typename IsDownFunction>

        InputDevice::ButtonState updateButton(ButtonTracker& tracker, IsDownFunction isDown, f32 deltaTime){

            constexpr Seconds CLICK_THRESHOLD{0.25};

            const bool down = isDown();

            InputDevice::ButtonState result{};

            if(down){

                if(!tracker.wasDown){

                    tracker.heldTime = Seconds{0};

                    result.state = InputDevice::InputState::Pressed;

                }else{

                    tracker.heldTime += Seconds{deltaTime};

                    result.state = InputDevice::InputState::Down;
                }

                result.heldDuration = Seconds{tracker.heldTime};
                result.clicked = false;

            }else{

                if(tracker.wasDown){

                    result.state = InputDevice::InputState::Released;

                    result.heldDuration = Seconds{tracker.heldTime};

                    result.clicked = tracker.heldTime <= CLICK_THRESHOLD;

                    tracker.heldTime = Seconds{0};

                }else{

                    result.state = InputDevice::InputState::Up;
                    result.heldDuration = Seconds{0};
                    result.clicked = false;
                }
            }

        tracker.wasDown = down;

        return result;
    }
        InputDevice::Event currentEvent{};
        std::unordered_map<InputDevice::Mouse::Button, ButtonTracker> mouseTrackers{};
        std::unordered_map<InputDevice::Keyboard::Button, ButtonTracker> keyboardTrackers{};
    };
}