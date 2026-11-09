#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Math/Vec.hpp"
#include <unordered_map>
#include <variant>

namespace Kotoba{

    namespace InputDevice{

        namespace Keyboard{
        
        enum class Button : i32{

            Null,
            Apostrophe,
            Comma,
            Minus,
            Period,
            Slash,
            Zero,
            One,
            Two,
            Three,
            Four,
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Semicolon,
            Equal,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            LeftBracket,
            Backslash,
            RightBracket,
            Grave,
            // Function and control keys
            Space,
            Escape,
            Enter,
            Tab,
            Backspace,
            Insert,
            Delete,
            Right,
            Left,
            Down,
            Up,
            PageUp,
            PageDown,
            Home,
            End,
            CapsLock,
            ScrollLock,
            NumLock,
            PrintScreen,
            Pause,
            // Function keys
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            // Keypad keys
            Keypad0,
            Keypad1,
            Keypad2,
            Keypad3,
            Keypad4,
            Keypad5,
            Keypad6,
            Keypad7,
            Keypad8,
            Keypad9,
            KeypadDecimal,
            KeypadDivide,
            KeypadMultiply,
            KeypadSubtract,
            KeypadAdd,
            KeypadEnter,
            KeypadEqual,
            // Modifier keys
            LeftShift,
            LeftControl,
            LeftAlt,
            LeftSuper,
            RightShift,
            RightControl,
            RightAlt,
            RightSuper,
            KeyboardMenu
        };
    };

    namespace Mouse{
    
        enum class Button : i32{

            Left,
            Right,
            Middle,
            Side,
            Extra,
            Forward,
            Back,
        };
    };
        enum class InputState{

            Pressed,
            Down,
            Up,
            Released
        };

        struct ButtonState{

            Duration heldDuration{0};
            InputState state{InputState::Up};
            bool clicked{false};
        };

        struct MouseState{

            std::unordered_map<InputDevice::Mouse::Button, ButtonState> buttons;
            Vec2i position{0, 0};
            Vec2i delta{0, 0};    
        };

        struct KeyboardState{

            std::unordered_map<InputDevice::Keyboard::Button, ButtonState> buttons{};

        };

        struct Event{

            MouseState mouse{};
            KeyboardState keyboard{};
        };

        using InputSignal = std::variant<Mouse::Button, Keyboard::Button>;
    };

    class Input{

        public:

        void Update();//Polls the frame
        const InputDevice::Event& getEvent();//Returns a snapshot with the information of everything that happened in the frame

        private:

        bool isPressed(const InputDevice::InputSignal& inputQuery);
        bool isDown(const InputDevice::InputSignal& inputQuery);
        bool isUp(const InputDevice::InputSignal& inputQuery);
        bool isReleased(const InputDevice::InputSignal& inputQuery);

        struct ButtonTracker{

            bool wasDown{false};
            Duration heldTime{0};
        };

        using MouseButton = InputDevice::Mouse::Button;
        using KeyboardButton = InputDevice::Keyboard::Button;

        std::unordered_map<MouseButton, ButtonTracker> mouseTrackers{};
        std::unordered_map<KeyboardButton, ButtonTracker> keyboardTrackers{};

        template<typename IsDownFunction>

        InputDevice::ButtonState updateButton(ButtonTracker& tracker, IsDownFunction isDown, float deltaTime){

            constexpr Duration CLICK_THRESHOLD{0.25};

            const bool down = isDown();

            InputDevice::ButtonState result{};

            if(down){

                if(!tracker.wasDown){

                    tracker.heldTime = Duration{0};

                    result.state = InputDevice::InputState::Pressed;

                }else{

                    tracker.heldTime += Duration{deltaTime};

                    result.state = InputDevice::InputState::Down;
                }

                result.heldDuration = Duration{tracker.heldTime};
                result.clicked = false;

            }else{

                if(tracker.wasDown){

                    result.state = InputDevice::InputState::Released;

                    result.heldDuration = Duration{tracker.heldTime};

                    result.clicked = tracker.heldTime <= CLICK_THRESHOLD;

                    tracker.heldTime = Duration{0};

                }else{

                    result.state = InputDevice::InputState::Up;
                    result.heldDuration = Duration{0};
                    result.clicked = false;
                }
            }

        tracker.wasDown = down;

        return result;
    }
        InputDevice::Event currentEvent;
    };
}