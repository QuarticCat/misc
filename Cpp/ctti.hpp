#include <string_view>

template<typename T>
constexpr std::string_view pretty_function() {
    return __PRETTY_FUNCTION__;
}

/// Return the name of the given type in compile-time.
///
/// Ref: https://blog.quarticcat.com/posts/cpp-ctti/
///
/// # Examples
///
/// ```
/// assert(type_name<int>() == "int");
/// ```
///
/// # Compatibility
///
/// - GCC / Clang
/// - C++17 or higher
template<typename T>
constexpr std::string_view type_name() {
#if defined(__clang__)
    constexpr const char PREFIX[] = "std::string_view pretty_function() [T = ";
    constexpr const char SUFFIX[] = "]";
#elif defined(__GNUC__)
    constexpr const char PREFIX[] = "constexpr std::string_view pretty_function() [with T = ";
    constexpr const char SUFFIX[] = "; std::string_view = std::basic_string_view<char>]";
#endif

    auto name = pretty_function<T>();
    name.remove_prefix(sizeof(PREFIX) - 1);
    name.remove_suffix(sizeof(SUFFIX) - 1);
    return name;
}

constexpr size_t fnv1a_hash(std::string_view str) {
    constexpr size_t FNV_BASIS = 14695981039346656037ull;
    constexpr size_t FNV_PRIME = 1099511628211ull;

    size_t hash = FNV_BASIS;
    for (char c: str) hash = (hash ^ c) * FNV_PRIME;
    return hash;
}

/// Return the hash of the given type in compile-time.
template<typename T>
constexpr size_t type_hash() {
    auto name = type_name<T>();
    return fnv1a_hash(name);
}
