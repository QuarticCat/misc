//! Get the name / hash of the given type in compile-time.
//!
//! Ref: https://blog.quarticcat.com/posts/cpp-ctti/
//!
//! # Examples
//!
//! ```
//! assert(type_name<int>() == "int");
//! assert(type_hash<int>() != type_hash<char>());
//! ```
//!
//! # Compatibility
//!
//! - GCC / Clang
//! - C++17 or higher

#pragma once

#include <string_view>

namespace detail {

constexpr uint64_t fnv1a_hash(std::string_view str) {
    uint64_t hash = 14695981039346656037ull;
    for (char c: str) hash = (hash ^ c) * 1099511628211ull;
    return hash;
}

}  // namespace detail

template<typename T>
constexpr std::string_view type_name() {
#if defined(__clang__)
    const char prefix[] = "std::string_view type_name() [T = ";
    const char suffix[] = "]";
#elif defined(__GNUC__)
    const char prefix[] = "constexpr std::string_view type_name() [with T = ";
    const char suffix[] = "; std::string_view = std::basic_string_view<char>]";
#endif

    std::string_view name = __PRETTY_FUNCTION__;
    name.remove_prefix(sizeof(prefix) - 1);
    name.remove_suffix(sizeof(suffix) - 1);
    return name;
}

template<typename T>
constexpr uint64_t type_hash() {
    auto name = type_name<T>();
    return detail::fnv1a_hash(name);
}
