#pragma once
#include <string>

namespace Kotoba::Utils{
   /*
    * @param s The string to convert
    * Converts all characters in the string to uppercase
    * Returns a new string containing the converted characters
    * Does not modify the original string
    */
    std::string toUpper(const std::string& s);

    /*
    * @param s The string to convert
    * Converts all characters in the string to lowercase
    * Returns a new string containing the converted characters
    * Does not modify the original string
    */
    std::string toLower(const std::string& s);

}