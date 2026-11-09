#include "Kotoba/Input/Input.hpp"
#include "Kotoba/Core/Types.hpp"
#include <raylib.h>

namespace Kotoba{
    
    // Compile-time arrays of all supported buttons for iteration
    constexpr std::array MOUSE_BUTTONS{
        InputDevice::Mouse::Button::Left,
        InputDevice::Mouse::Button::Right,
        InputDevice::Mouse::Button::Middle,
        InputDevice::Mouse::Button::Side,
        InputDevice::Mouse::Button::Extra,
        InputDevice::Mouse::Button::Forward,
        InputDevice::Mouse::Button::Back
    };

    constexpr std::array KEYBOARD_BUTTONS{
        InputDevice::Keyboard::Button::Null,
        InputDevice::Keyboard::Button::Apostrophe,
        InputDevice::Keyboard::Button::Comma,
        InputDevice::Keyboard::Button::Minus,
        InputDevice::Keyboard::Button::Period,
        InputDevice::Keyboard::Button::Slash,
        InputDevice::Keyboard::Button::Zero,
        InputDevice::Keyboard::Button::One,
        InputDevice::Keyboard::Button::Two,
        InputDevice::Keyboard::Button::Three,
        InputDevice::Keyboard::Button::Four,
        InputDevice::Keyboard::Button::Five,
        InputDevice::Keyboard::Button::Six,
        InputDevice::Keyboard::Button::Seven,
        InputDevice::Keyboard::Button::Eight,
        InputDevice::Keyboard::Button::Nine,
        InputDevice::Keyboard::Button::Semicolon,
        InputDevice::Keyboard::Button::Equal,
        InputDevice::Keyboard::Button::A,
        InputDevice::Keyboard::Button::B,
        InputDevice::Keyboard::Button::C,
        InputDevice::Keyboard::Button::D,
        InputDevice::Keyboard::Button::E,
        InputDevice::Keyboard::Button::F,
        InputDevice::Keyboard::Button::G,
        InputDevice::Keyboard::Button::H,
        InputDevice::Keyboard::Button::I,
        InputDevice::Keyboard::Button::J,
        InputDevice::Keyboard::Button::K,
        InputDevice::Keyboard::Button::L,
        InputDevice::Keyboard::Button::M,
        InputDevice::Keyboard::Button::N,
        InputDevice::Keyboard::Button::O,
        InputDevice::Keyboard::Button::P,
        InputDevice::Keyboard::Button::Q,
        InputDevice::Keyboard::Button::R,
        InputDevice::Keyboard::Button::S,
        InputDevice::Keyboard::Button::T,
        InputDevice::Keyboard::Button::U,
        InputDevice::Keyboard::Button::V,
        InputDevice::Keyboard::Button::W,
        InputDevice::Keyboard::Button::X,
        InputDevice::Keyboard::Button::Y,
        InputDevice::Keyboard::Button::Z,
        InputDevice::Keyboard::Button::LeftBracket,
        InputDevice::Keyboard::Button::Backslash,
        InputDevice::Keyboard::Button::RightBracket,
        InputDevice::Keyboard::Button::Grave,
        InputDevice::Keyboard::Button::Space,
        InputDevice::Keyboard::Button::Escape,
        InputDevice::Keyboard::Button::Enter,
        InputDevice::Keyboard::Button::Tab,
        InputDevice::Keyboard::Button::Backspace,
        InputDevice::Keyboard::Button::Insert,
        InputDevice::Keyboard::Button::Delete,
        InputDevice::Keyboard::Button::Right,
        InputDevice::Keyboard::Button::Left,
        InputDevice::Keyboard::Button::Down,
        InputDevice::Keyboard::Button::Up,
        InputDevice::Keyboard::Button::PageUp,
        InputDevice::Keyboard::Button::PageDown,
        InputDevice::Keyboard::Button::Home,
        InputDevice::Keyboard::Button::End,
        InputDevice::Keyboard::Button::CapsLock,
        InputDevice::Keyboard::Button::ScrollLock,
        InputDevice::Keyboard::Button::NumLock,
        InputDevice::Keyboard::Button::PrintScreen,
        InputDevice::Keyboard::Button::Pause,
        InputDevice::Keyboard::Button::F1,
        InputDevice::Keyboard::Button::F2,
        InputDevice::Keyboard::Button::F3,
        InputDevice::Keyboard::Button::F4,
        InputDevice::Keyboard::Button::F5,
        InputDevice::Keyboard::Button::F6,
        InputDevice::Keyboard::Button::F7,
        InputDevice::Keyboard::Button::F8,
        InputDevice::Keyboard::Button::F9,
        InputDevice::Keyboard::Button::F10,
        InputDevice::Keyboard::Button::F11,
        InputDevice::Keyboard::Button::F12,
        InputDevice::Keyboard::Button::Keypad0,
        InputDevice::Keyboard::Button::Keypad1,
        InputDevice::Keyboard::Button::Keypad2,
        InputDevice::Keyboard::Button::Keypad3,
        InputDevice::Keyboard::Button::Keypad4,
        InputDevice::Keyboard::Button::Keypad5,
        InputDevice::Keyboard::Button::Keypad6,
        InputDevice::Keyboard::Button::Keypad7,
        InputDevice::Keyboard::Button::Keypad8,
        InputDevice::Keyboard::Button::Keypad9,
        InputDevice::Keyboard::Button::KeypadDecimal,
        InputDevice::Keyboard::Button::KeypadDivide,
        InputDevice::Keyboard::Button::KeypadMultiply,
        InputDevice::Keyboard::Button::KeypadSubtract,
        InputDevice::Keyboard::Button::KeypadAdd,
        InputDevice::Keyboard::Button::KeypadEnter,
        InputDevice::Keyboard::Button::KeypadEqual,
        InputDevice::Keyboard::Button::LeftShift,
        InputDevice::Keyboard::Button::LeftControl,
        InputDevice::Keyboard::Button::LeftAlt,
        InputDevice::Keyboard::Button::LeftSuper,
        InputDevice::Keyboard::Button::RightShift,
        InputDevice::Keyboard::Button::RightControl,
        InputDevice::Keyboard::Button::RightAlt,
        InputDevice::Keyboard::Button::RightSuper,
        InputDevice::Keyboard::Button::KeyboardMenu
    };

    constexpr ::MouseButton toRaylib(InputDevice::Mouse::Button button){

        switch (button){

                case InputDevice::Mouse::Button::Left: return MOUSE_BUTTON_LEFT;
                case InputDevice::Mouse::Button::Right: return MOUSE_BUTTON_RIGHT;
                case InputDevice::Mouse::Button::Middle: return MOUSE_BUTTON_MIDDLE;
                case InputDevice::Mouse::Button::Side: return MOUSE_BUTTON_SIDE;
                case InputDevice::Mouse::Button::Extra: return MOUSE_BUTTON_EXTRA;
                case InputDevice::Mouse::Button::Forward: return MOUSE_BUTTON_FORWARD;
                case InputDevice::Mouse::Button::Back: return MOUSE_BUTTON_BACK;
            }

            return MOUSE_BUTTON_LEFT;
        }

    constexpr ::KeyboardKey toRaylib(InputDevice::Keyboard::Button button){

        switch(button){

            case InputDevice::Keyboard::Button::Null: return KEY_NULL;
            // Punctuation
            case InputDevice::Keyboard::Button::Apostrophe: return KEY_APOSTROPHE;
            case InputDevice::Keyboard::Button::Comma: return KEY_COMMA;
            case InputDevice::Keyboard::Button::Minus: return KEY_MINUS;
            case InputDevice::Keyboard::Button::Period: return KEY_PERIOD;
            case InputDevice::Keyboard::Button::Slash: return KEY_SLASH;
            case InputDevice::Keyboard::Button::Semicolon: return KEY_SEMICOLON;
            case InputDevice::Keyboard::Button::Equal: return KEY_EQUAL;
            case InputDevice::Keyboard::Button::LeftBracket: return KEY_LEFT_BRACKET;
            case InputDevice::Keyboard::Button::Backslash: return KEY_BACKSLASH;
            case InputDevice::Keyboard::Button::RightBracket: return KEY_RIGHT_BRACKET;
            case InputDevice::Keyboard::Button::Grave: return KEY_GRAVE;
            // Numbers
            case InputDevice::Keyboard::Button::Zero: return KEY_ZERO;
            case InputDevice::Keyboard::Button::One: return KEY_ONE;
            case InputDevice::Keyboard::Button::Two: return KEY_TWO;
            case InputDevice::Keyboard::Button::Three: return KEY_THREE;
            case InputDevice::Keyboard::Button::Four: return KEY_FOUR;
            case InputDevice::Keyboard::Button::Five: return KEY_FIVE;
            case InputDevice::Keyboard::Button::Six: return KEY_SIX;
            case InputDevice::Keyboard::Button::Seven: return KEY_SEVEN;
            case InputDevice::Keyboard::Button::Eight: return KEY_EIGHT;
            case InputDevice::Keyboard::Button::Nine: return KEY_NINE;
            // Letters
            case InputDevice::Keyboard::Button::A: return KEY_A;
            case InputDevice::Keyboard::Button::B: return KEY_B;
            case InputDevice::Keyboard::Button::C: return KEY_C;
            case InputDevice::Keyboard::Button::D: return KEY_D;
            case InputDevice::Keyboard::Button::E: return KEY_E;
            case InputDevice::Keyboard::Button::F: return KEY_F;
            case InputDevice::Keyboard::Button::G: return KEY_G;
            case InputDevice::Keyboard::Button::H: return KEY_H;
            case InputDevice::Keyboard::Button::I: return KEY_I;
            case InputDevice::Keyboard::Button::J: return KEY_J;
            case InputDevice::Keyboard::Button::K: return KEY_K;
            case InputDevice::Keyboard::Button::L: return KEY_L;
            case InputDevice::Keyboard::Button::M: return KEY_M;
            case InputDevice::Keyboard::Button::N: return KEY_N;
            case InputDevice::Keyboard::Button::O: return KEY_O;
            case InputDevice::Keyboard::Button::P: return KEY_P;
            case InputDevice::Keyboard::Button::Q: return KEY_Q;
            case InputDevice::Keyboard::Button::R: return KEY_R;
            case InputDevice::Keyboard::Button::S: return KEY_S;
            case InputDevice::Keyboard::Button::T: return KEY_T;
            case InputDevice::Keyboard::Button::U: return KEY_U;
            case InputDevice::Keyboard::Button::V: return KEY_V;
            case InputDevice::Keyboard::Button::W: return KEY_W;
            case InputDevice::Keyboard::Button::X: return KEY_X;
            case InputDevice::Keyboard::Button::Y: return KEY_Y;
            case InputDevice::Keyboard::Button::Z: return KEY_Z;
            // Function and control keys
            case InputDevice::Keyboard::Button::Space: return KEY_SPACE;
            case InputDevice::Keyboard::Button::Escape: return KEY_ESCAPE;
            case InputDevice::Keyboard::Button::Enter: return KEY_ENTER;
            case InputDevice::Keyboard::Button::Tab: return KEY_TAB;
            case InputDevice::Keyboard::Button::Backspace: return KEY_BACKSPACE;
            case InputDevice::Keyboard::Button::Insert: return KEY_INSERT;
            case InputDevice::Keyboard::Button::Delete: return KEY_DELETE;
            case InputDevice::Keyboard::Button::Right: return KEY_RIGHT;
            case InputDevice::Keyboard::Button::Left: return KEY_LEFT;
            case InputDevice::Keyboard::Button::Down: return KEY_DOWN;
            case InputDevice::Keyboard::Button::Up: return KEY_UP;
            case InputDevice::Keyboard::Button::PageUp: return KEY_PAGE_UP;
            case InputDevice::Keyboard::Button::PageDown: return KEY_PAGE_DOWN;
            case InputDevice::Keyboard::Button::Home: return KEY_HOME;
            case InputDevice::Keyboard::Button::End: return KEY_END;
            case InputDevice::Keyboard::Button::CapsLock: return KEY_CAPS_LOCK;
            case InputDevice::Keyboard::Button::ScrollLock: return KEY_SCROLL_LOCK;
            case InputDevice::Keyboard::Button::NumLock: return KEY_NUM_LOCK;
            case InputDevice::Keyboard::Button::PrintScreen: return KEY_PRINT_SCREEN;
            case InputDevice::Keyboard::Button::Pause: return KEY_PAUSE;
            // Function keys
            case InputDevice::Keyboard::Button::F1: return KEY_F1;
            case InputDevice::Keyboard::Button::F2: return KEY_F2;
            case InputDevice::Keyboard::Button::F3: return KEY_F3;
            case InputDevice::Keyboard::Button::F4: return KEY_F4;
            case InputDevice::Keyboard::Button::F5: return KEY_F5;
            case InputDevice::Keyboard::Button::F6: return KEY_F6;
            case InputDevice::Keyboard::Button::F7: return KEY_F7;
            case InputDevice::Keyboard::Button::F8: return KEY_F8;
            case InputDevice::Keyboard::Button::F9: return KEY_F9;
            case InputDevice::Keyboard::Button::F10: return KEY_F10;
            case InputDevice::Keyboard::Button::F11: return KEY_F11;
            case InputDevice::Keyboard::Button::F12: return KEY_F12;
            // Keypad keys
            case InputDevice::Keyboard::Button::Keypad0: return KEY_KP_0;
            case InputDevice::Keyboard::Button::Keypad1: return KEY_KP_1;
            case InputDevice::Keyboard::Button::Keypad2: return KEY_KP_2;
            case InputDevice::Keyboard::Button::Keypad3: return KEY_KP_3;
            case InputDevice::Keyboard::Button::Keypad4: return KEY_KP_4;
            case InputDevice::Keyboard::Button::Keypad5: return KEY_KP_5;
            case InputDevice::Keyboard::Button::Keypad6: return KEY_KP_6;
            case InputDevice::Keyboard::Button::Keypad7: return KEY_KP_7;
            case InputDevice::Keyboard::Button::Keypad8: return KEY_KP_8;
            case InputDevice::Keyboard::Button::Keypad9: return KEY_KP_9;
            case InputDevice::Keyboard::Button::KeypadDecimal: return KEY_KP_DECIMAL;
            case InputDevice::Keyboard::Button::KeypadDivide: return KEY_KP_DIVIDE;
            case InputDevice::Keyboard::Button::KeypadMultiply: return KEY_KP_MULTIPLY;
            case InputDevice::Keyboard::Button::KeypadSubtract: return KEY_KP_SUBTRACT;
            case InputDevice::Keyboard::Button::KeypadAdd: return KEY_KP_ADD;
            case InputDevice::Keyboard::Button::KeypadEnter: return KEY_KP_ENTER;
            case InputDevice::Keyboard::Button::KeypadEqual: return KEY_KP_EQUAL;
            // Modifier keys
            case InputDevice::Keyboard::Button::LeftShift: return KEY_LEFT_SHIFT;
            case InputDevice::Keyboard::Button::LeftControl: return KEY_LEFT_CONTROL;
            case InputDevice::Keyboard::Button::LeftAlt: return KEY_LEFT_ALT;
            case InputDevice::Keyboard::Button::LeftSuper: return KEY_LEFT_SUPER;
            case InputDevice::Keyboard::Button::RightShift: return KEY_RIGHT_SHIFT;
            case InputDevice::Keyboard::Button::RightControl: return KEY_RIGHT_CONTROL;
            case InputDevice::Keyboard::Button::RightAlt: return KEY_RIGHT_ALT;
            case InputDevice::Keyboard::Button::RightSuper: return KEY_RIGHT_SUPER;
            case InputDevice::Keyboard::Button::KeyboardMenu: return KEY_KB_MENU;
        }

        return KEY_NULL;
    }

    void Input::Update(){

        InputDevice::Event nextEvent{};

        const float deltaTime = ::GetFrameTime();

        Vector2 mousePos = ::GetMousePosition();
        Vector2 mouseDelta = ::GetMouseDelta();
        nextEvent.mouse.position = {static_cast<i32>(mousePos.x), static_cast<i32>(mousePos.y)};
        nextEvent.mouse.delta = {static_cast<i32>(mouseDelta.x), static_cast<i32>(mouseDelta.y)};

        for(auto btn : MOUSE_BUTTONS){

            auto& tracker = mouseTrackers[btn];

            auto buttonState = updateButton(tracker, [btn](){

                    return ::IsMouseButtonDown(toRaylib(btn));

                },deltaTime);

            nextEvent.mouse.buttons[btn] = buttonState;
        }

        for(auto key : KEYBOARD_BUTTONS){

            auto& tracker = keyboardTrackers[key];

            auto buttonState = updateButton(tracker,[key](){

                return ::IsKeyDown(toRaylib(key));
                
            }, deltaTime);

            nextEvent.keyboard.buttons[key] = buttonState;
        }

        currentEvent = nextEvent;
    }

    const InputDevice::Event& Input::getEvent(){

        return currentEvent;
    }

    bool Input::isPressed(const InputDevice::InputSignal& inputQuery){

        return std::visit([](auto button) -> bool{

            using T = decltype(button);

            if constexpr(std::is_same_v<T, InputDevice::Mouse::Button>){

                return ::IsMouseButtonPressed(toRaylib(button));

            }

            else if constexpr(std::is_same_v<T, InputDevice::Keyboard::Button>){

                return ::IsKeyPressed(toRaylib(button));

            }

            return false;

        }, inputQuery);

    }

    bool Input::isDown(const InputDevice::InputSignal& inputQuery){

        return std::visit([](auto button) -> bool{

            using T = decltype(button);

            if constexpr(std::is_same_v<T, InputDevice::Mouse::Button>){

                return ::IsMouseButtonDown(toRaylib(button));

            }

            else if constexpr(std::is_same_v<T, InputDevice::Keyboard::Button>){

                return ::IsKeyDown(toRaylib(button));

            }

            return false;

        }, inputQuery);

    }

    bool Input::isUp(const InputDevice::InputSignal& inputQuery){

        return std::visit([](auto button) -> bool{

            using T = decltype(button);

            if constexpr(std::is_same_v<T, InputDevice::Mouse::Button>){

                return ::IsMouseButtonUp(toRaylib(button));

            }

            else if constexpr(std::is_same_v<T, InputDevice::Keyboard::Button>){

                return ::IsKeyUp(toRaylib(button));

            }

            return false;

        }, inputQuery);
    }

    bool Input::isReleased(const InputDevice::InputSignal& inputQuery){

        return std::visit([](auto button) -> bool{

            using T = decltype(button);

            if constexpr(std::is_same_v<T, InputDevice::Mouse::Button>){

                return ::IsMouseButtonReleased(toRaylib(button));

            }

            else if constexpr(std::is_same_v<T, InputDevice::Keyboard::Button>){

                return ::IsKeyReleased(toRaylib(button));

            }

            return false;

        }, inputQuery);
    }

};