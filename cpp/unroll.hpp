//! Some unrolling utilities.
//!
//! # Compatibility
//!
//! - GCC / Clang
//! - C++20 or higher

#pragma once

#include <cstddef>
#include <utility>

#define DO_PRAGMA(x) _Pragma(#x)

/// # Examples
///
/// ```
/// UNROLL for (...) { ... }
/// ```
#define UNROLL      DO_PRAGMA(unroll)
#define UNROLL_N(n) DO_PRAGMA(unroll n)
#define NO_UNROLL   DO_PRAGMA(nounroll)
// TODO: support GCC

/// Sometimes the loop variable is required to be constexpr so pragma unroll doesn't work.
///
/// # Examples
///
/// ```
/// unroll<0, 32>([&]<auto I> { a[I] += b[I]; });
/// ```
template<size_t Start, size_t End, size_t Step = 1>
void unroll(auto&& f) {
    ([&]<size_t... Is>(std::index_sequence<Is...>) {
        (f.template operator()<Is>(), ...);
    }([]<size_t... Is>(std::index_sequence<Is...>) {
        return std::index_sequence<Start + Is * Step...>{};
    }(std::make_index_sequence<End - Start>{})));
}

/// # Examples
///
/// ```
/// EXPAND(32, u8x32{Is...})
/// ```
#define EXPAND(n, expr) \
    ([&]<size_t... Is>(std::index_sequence<Is...>) { return expr; }(std::make_index_sequence<n>{}))
