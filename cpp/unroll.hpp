//! Some unrolling utilities.

#pragma once

#include <cstddef>
#include <utility>

/// A warkaround before `IndentPragma` is available in clang-format.
///
/// Remember to add this config to .clang-format:
///
/// ```
/// StatementMacros:
///   - QC_UNROLL
/// ```
///
/// Note that Clang recognize `#pragma GCC unroll` but GCC doesn't recognize `#pragma unroll`.
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
#define QC_UNROLL _Pragma("GCC unroll")

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
    }(std::make_index_sequence<End - Start>{})));
}

template<size_t End>
void unroll(auto&& f) {
    unroll<0, End>(f);
}

/// # Examples
///
/// ```
/// expand<0, 32>([&]<auto... Is> { return std::array{a[Is]...}; });
/// // or expand<0, 32>(...);
/// // or expand<0, 32, 1>(...);
/// ```
///
/// # Compatibility
///
/// - C++20 or higher
template<size_t Start, size_t End, size_t Step = 1>
void expand(auto&& f) {
    ([&]<size_t... Is>(std::index_sequence<Is...>) {
        return f.template operator()<Is...>();
    }([]<size_t... Is>(std::index_sequence<Is...>) {
        return std::index_sequence<Start + Is * Step...>{};
    }(std::make_index_sequence<End - Start>{})));
}

template<size_t End>
void expand(auto&& f) {
    expand<0, End>(f);
}
