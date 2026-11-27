#pragma once
#include "Kotoba/Input/Types.hpp"
#include <vector>

namespace Kotoba{

    /*
    *Represents a component that can react to a given set of inputs
    */

    struct InputListener{

        std::vector<InputDevice::InputSignal> watchedSignals{};
        std::vector<InputDevice::Event> eventQueue{};

        void emit(const InputDevice::Event& event){

            eventQueue.push_back(event);
        }
    };
}