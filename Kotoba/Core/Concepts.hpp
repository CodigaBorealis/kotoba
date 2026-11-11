#pragma once
#include <type_traits>
#include <concepts>
#include "Kotoba/Core/Types.hpp"

namespace Kotoba{

    template<typename T>
    /*
    *Checks whether a type is a character type
    *Accepts char, signed char, unsigned char, wchar_t, char8_t, char16_t and char32_t
    *Removes const and volatile qualifiers before checking the type
    */
    concept CharacterType =
    std::same_as<std::remove_cv_t<T>, char> ||
    std::same_as<std::remove_cv_t<T>, signed char> ||
    std::same_as<std::remove_cv_t<T>, unsigned char> ||
    std::same_as<std::remove_cv_t<T>, wchar_t> ||
    std::same_as<std::remove_cv_t<T>, char8_t> ||
    std::same_as<std::remove_cv_t<T>, char16_t> ||
    std::same_as<std::remove_cv_t<T>, char32_t>;
   /*
    *Checks whether a type is a signed integer type
    *Accepts i8, i16, i32 and i64
    *Removes const and volatile qualifiers before checking the type
    */
    template<typename T>
    concept SignedType =
    std::is_same_v<std::remove_cv_t<T>, i8> ||
    std::is_same_v<std::remove_cv_t<T>, i16> ||
    std::is_same_v<std::remove_cv_t<T>, i32> ||
    std::is_same_v<std::remove_cv_t<T>, i64>;
   /*
    *Checks whether a type is an unsigned integer type
    *Accepts u8, u16, u32 and u64
    *Removes const and volatile qualifiers before checking the type
    */
    template<typename T>
    concept UnsignedType =
    std::is_same_v<std::remove_cv_t<T>, u8> ||
    std::is_same_v<std::remove_cv_t<T>, u16> ||
    std::is_same_v<std::remove_cv_t<T>, u32> ||
    std::is_same_v<std::remove_cv_t<T>, u64>;
    /*
    *Checks whether a type is a floating-point type
    *Accepts f32 and f64
    *Removes const and volatile qualifiers before checking the type
    */
    template<typename T>
    concept FloatType =
    std::is_same_v<std::remove_cv_t<T>, f32> ||
    std::is_same_v<std::remove_cv_t<T>, f64>;
    /*
    *Checks whether a type is a numerical type
    *Accepts signed integer, unsigned integer and floating-point types
    *Combines SignedType, UnsignedType and FloatType
    */
    template<typename T>
    concept Numerical = SignedType<T> || UnsignedType<T> || FloatType<T>;


    template<typename T>

    inline constexpr bool IsComponent = false;

    template<typename T>

    concept ComponentType = IsComponent<T> && std::same_as<T, std::remove_cvref_t<T>> && std::is_destructible_v<T>;
}
