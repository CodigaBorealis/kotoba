#pragma once
#include "Kotoba/Input/Types.hpp"

namespace Kotoba{

    /*
    *Represents a component that can listen for the state of the keyboard
    */

    struct KeyboardListener{

        InputDevice::KeyboardState state{};
    };

    /*
    *Represents a component that can listen for the state of the keyboard
    */

    struct MouseListener{

        InputDevice::MouseState state{};
    };
}