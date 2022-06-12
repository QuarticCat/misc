//! Some vector extension utilities.
//!
//! # Compatibility
//!
//! - GCC / Clang
//! - C++11 or higher

#pragma once

#include <cstdint>

using i8x16 = int8_t __attribute__((vector_size(16)));
using u8x16 = uint8_t __attribute__((vector_size(16)));
using i16x8 = int16_t __attribute__((vector_size(16)));
using u16x8 = uint16_t __attribute__((vector_size(16)));
using i32x4 = int32_t __attribute__((vector_size(16)));
using u32x4 = uint32_t __attribute__((vector_size(16)));
using i64x2 = int64_t __attribute__((vector_size(16)));
using u64x2 = uint64_t __attribute__((vector_size(16)));
using f32x4 = float __attribute__((vector_size(16)));
using f64x2 = double __attribute__((vector_size(16)));

using i8x32 = int8_t __attribute__((vector_size(32)));
using u8x32 = uint8_t __attribute__((vector_size(32)));
using i16x16 = int16_t __attribute__((vector_size(32)));
using u16x16 = uint16_t __attribute__((vector_size(32)));
using i32x8 = int32_t __attribute__((vector_size(32)));
using u32x8 = uint32_t __attribute__((vector_size(32)));
using i64x4 = int64_t __attribute__((vector_size(32)));
using u64x4 = uint64_t __attribute__((vector_size(32)));
using f32x8 = float __attribute__((vector_size(32)));
using f64x4 = double __attribute__((vector_size(32)));

using i8x64 = int8_t __attribute__((vector_size(64)));
using u8x64 = uint8_t __attribute__((vector_size(64)));
using i16x32 = int16_t __attribute__((vector_size(64)));
using u16x32 = uint16_t __attribute__((vector_size(64)));
using i32x16 = int32_t __attribute__((vector_size(64)));
using u32x16 = uint32_t __attribute__((vector_size(64)));
using i64x8 = int64_t __attribute__((vector_size(64)));
using u64x8 = uint64_t __attribute__((vector_size(64)));
using f32x16 = float __attribute__((vector_size(64)));
using f64x8 = double __attribute__((vector_size(64)));
