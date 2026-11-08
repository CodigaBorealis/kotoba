#include "Kotoba/Utils/Utils.hpp"
#include <algorithm>
#include <cctype>

namespace Kotoba::Utils{

    std::string toUpper(const std::string& s){

        std::string copy = s;

        std::transform(copy.begin(), copy.end(), copy.begin(), [](unsigned char c) {

                return static_cast<char>(std::toupper(c));
        });

        return copy;
    }

    std::string toLower(const std::string& s){

        std::string copy = s;

        std::transform(copy.begin(), copy.end(), copy.begin(), [](unsigned char c) {

                return static_cast<char>(std::tolower(c));
        });

        return copy;

    }
}