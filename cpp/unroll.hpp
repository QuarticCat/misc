//! Some unrolling utilities.

#pragma once

#include <cstddef>
#include <utility>

/// Remember to add this config to .clang-format:
///
/// ```
/// StatementMacros:
///   - QC_UNROLL
/// ```
///
/// # Examples
///
/// ```
/// QC_UNROLL
/// for (...) { ... }
/// ```
///
/// # Compatibility
///
/// - GCC / Clang
#if defined(__clang__)
    #define QC_UNROLL _Pragma("unroll")
#elif defined(__GNUC__)
    #define QC_UNROLL _Pragma("GCC ivdep")
#endif

/// Sometimes the loop variable is required to be constexpr so pragma unroll doesn't work.
///
/// # Examples
///
/// ```
/// unroll<32>([&]<auto I> { a[I] += b[I]; });
/// // or unroll<0, 32>(...);
/// // or unroll<0, 32, 1>(...);
/// ```
///
/// # Compatibility
///
/// - C++20 or higher
template<size_t Start, size_t End, size_t Step = 1>
void unroll(auto&& f) {
    ([&]<size_t... Is>(std::index_sequence<Is...>) {
        (f.template operator()<Is>(), ...);
    }([]<size_t... Is>(std::index_sequence<Is...>) {
        return std::index_sequence<Start + Is * Step...>{};
    }(std::make_index_sequence<(End - Start) / Step>{})));
}

template<size_t End>
void unroll(auto&& f) {
    unroll<0, End>(f);
}

/// # Examples
///
/// ```
/// expand<32>([&]<auto... Is> { return std::array{a[Is]...}; });
/// // or expand<0, 32>(...);
/// // or expand<0, 32, 1>(...);
/// ```
///
/// # Compatibility
///
/// - C++20 or higher
template<size_t Start, size_t End, size_t Step = 1>
auto expand(auto&& f) {
    return ([&]<size_t... Is>(std::index_sequence<Is...>) {
        return f.template operator()<Is...>();
    }([]<size_t... Is>(std::index_sequence<Is...>) {
        return std::index_sequence<Start + Is * Step...>{};
    }(std::make_index_sequence<(End - Start) / Step>{})));
}

template<size_t End>
auto expand(auto&& f) {
    return expand<0, End>(f);
}
