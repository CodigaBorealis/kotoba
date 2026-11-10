#pragma once
#include "Types.hpp"

namespace Kotoba{
    /*
    *Represents error codes used throughout the Kotoba engine
    *Groups errors by category using distinct numerical ranges
    */
    enum class ErrorCode : u64{

        None = 0,
        // Window errors
        WindowAlreadyExists = 1000,
        WindowInitializationFailed,
        WindowNotInitialized,
        WindowInvalidState,
        // Resource errors
        ResourceNotFound = 2000,
        ResourceLoadFailed,
        ResourceInvalidFormat,
        // Initialization errors
        GraphicsInitializationFailed = 3000,
        AudioInitializationFailed,
        NullPointerException
        

    };
}