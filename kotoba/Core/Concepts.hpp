#pragma once
#include "kotoba/Core/Types.hpp"
#include <type_traits>
#include <concepts>

namespace Kotoba{

    template<typename T>
    
    concept CharacterType =
    std::same_as<std::remove_cv_t<T>, char> ||
    std::same_as<std::remove_cv_t<T>, signed char> ||
    std::same_as<std::remove_cv_t<T>, unsigned char> ||
    std::same_as<std::remove_cv_t<T>, wchar_t> ||
    std::same_as<std::remove_cv_t<T>, char8_t> ||
    std::same_as<std::remove_cv_t<T>, char16_t> ||
    std::same_as<std::remove_cv_t<T>, char32_t>;

    template<typename T>
    concept SignedType =
    std::is_same_v<std::remove_cv_t<T>, i8> ||
    std::is_same_v<std::remove_cv_t<T>, i16> ||
    std::is_same_v<std::remove_cv_t<T>, i32> ||
    std::is_same_v<std::remove_cv_t<T>, i64>;

    template<typename T>
    concept UnsignedType =
    std::is_same_v<std::remove_cv_t<T>, u8> ||
    std::is_same_v<std::remove_cv_t<T>, u16> ||
    std::is_same_v<std::remove_cv_t<T>, u32> ||
    std::is_same_v<std::remove_cv_t<T>, u64>;

    template<typename T>
    concept FloatType =
    std::is_same_v<std::remove_cv_t<T>, f32> ||
    std::is_same_v<std::remove_cv_t<T>, f64>;

    template<typename T>
    concept Numerical = SignedType<T> || UnsignedType<T> || FloatType<T>;

}
