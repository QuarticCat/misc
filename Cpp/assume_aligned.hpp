//! A C++ wrapper of `__builtin_assume_aligned`.
//!
//! Note that `std::assume_aligned` is preferable since C++20.
//!
//! Ref: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
//!
//! # Examples
//!
//! ```
//! int* x_ = assume_aligned<32, 8>(x);
//! ```
//!
//! # Compatibility
//!
//! - GCC / Clang
//! - C++11 or higher

#pragma once

#include <cassert>
#include <cstddef>

template<size_t Alignment, size_t Offset = 0, class T>
T* assume_aligned(T* ptr) {
    assert(((size_t)ptr - Offset) % Alignment == 0);
    // Clang's __builtin_assume_aligned requires constant.
    // So Alignment and Offset must be template parameters.
    void* ret = __builtin_assume_aligned(ptr, Alignment, Offset);
    return static_cast<T*>(ret);
}
