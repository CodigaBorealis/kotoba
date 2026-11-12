#pragma once
#include <chrono>
#include <cstdint>
#include <cstddef>

struct Color;

namespace Kotoba{

    //Unsigned integer types
    using u8  = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    //Signed integer types
    using i8  = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    //Floating-point types
    using f32 = float;
    using f64 = double;

    //General-purpose types
    using usize = std::size_t;
    using isize = std::ptrdiff_t;
    struct Color{

        constexpr Color() = default;

        constexpr Color(u8 r, u8 g, u8 b, u8 a)
            :
            r(r),
            g(g),
            b(b),
            a(a)
            {}
        operator ::Color() const;
        u8 r{255};
        u8 g{0};
        u8 b{0};
        u8 a{255};
    };
    //Time
    using Miliseconds = std::chrono::duration<float>;
    //Resources
    using ResourceID = u64;
}