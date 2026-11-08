#pragma once
#include <exception>
#include <utility>
#include <string>
#include "Kotoba/Core/Types.hpp"
#include "Kotoba/Core/ErrorCode.hpp"

namespace Kotoba{

    /*
    * @param message The descriptive message associated with the exception
    * @param code The error code identifying the type of exception
    * Constructs an Exception with a message and an optional error code
    */

    class Exception : std::exception{

        public:

        /*
        * @param message The descriptive message associated with the exception
        * @param code The error code identifying the type of exception
        * Constructs an Exception and moves the provided message into its internal storage
        */

        Exception(std::string message, ErrorCode code = ErrorCode::None)
        :
        code(code),
        message(std::move(message))
        {}

        /*
        * Returns a null-terminated C-style string containing the exception message
        */

        const char* what() const noexcept override{

            return message.c_str();
        }

        /*
        * Returns the error code associated with the exception
        */

        ErrorCode getCode() const noexcept{

            return code;
        }

        protected:

        ErrorCode code{0};
        std::string message{};
    };

    class WindowException : public Exception{

        public:

        using Exception::Exception;
    };

    class ResourceException : public Exception{

        public:

        using Exception::Exception;
    };

    class InitializationException : public Exception{

        public:

        using Exception::Exception;
    };


}