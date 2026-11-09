#pragma once
#include <chrono>
#include <cstdint>

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

    //RGBA Color type
    struct Color{

        u8 r{255};
        u8 g{255};
        u8 b{255};
        u8 a{255};
    };
    //Time
    using Duration = std::chrono::duration<float>;
}