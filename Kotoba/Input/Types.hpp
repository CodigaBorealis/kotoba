#pragma once
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Math/Vec.hpp"
#include <variant>
#include <unordered_map>
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

            Miliseconds heldDuration{0};
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
}