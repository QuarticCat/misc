#include <cassert>

/// Provide additional information to compiler.
///
/// Support GCC and Clang.
///
/// # Examples
///
/// These two functions generate the same assembly.
///
/// ```
/// int div2_optimized(int x) {
///     // round down, but x / 2 rounds toward 0
///     return x >> 1;
/// }
///
/// int div2_assume(int x) {
///     assume(x >= 0);
///     return x / 2;
/// }
/// ```
void assume(bool pred) {
    assert(pred);

#if defined(__clang__)
    __builtin_assume(pred);
#elif defined(__GNUC__)
    if (!pred) __builtin_unreachable();
#endif
}
