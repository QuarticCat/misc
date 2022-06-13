//! C++ version of TurboHist, the fastest histogram construction.
//!
//! Ref: https://github.com/powturbo/Turbo-Histogram
//!
//! # Compatibility
//!
//! - GCC / Clang
//! - C++20 or higher (for [[likely]])

#pragma once

#include <cstddef>
#include <cstdint>

#include "unroll.hpp"

template<class Bin = uint32_t, size_t BufNum = 4>
void histogram(uint8_t* __restrict__ data, size_t len, uint8_t* __restrict__ hist) {
    Bin hist_buf[BufNum][256];

    auto it = data;
    for (; it < data + len; it += 64) {
        QC_UNROLL
        for (size_t i = 0; i < 4; ++i) {
            auto x = ((uint64_t*)it)[i * 2];
            auto y = ((uint64_t*)it)[i * 2 + 1];
            if (x != y) [[likely]] {
                QC_UNROLL
                for (size_t j = 0; j < 8; ++j) {
                    ++hist_buf[j % BufNum][(x >> (j * 8)) & 0xFF];
                    ++hist_buf[j % BufNum][(y >> (j * 8)) & 0xFF];
                }
            } else if ((x ^ (y << 8)) < (1 << 8)) {  // all bytes are equal
                ++hist_buf[i][x & 0xff];
            } else {
                QC_UNROLL
                for (size_t j = 0; j < 8; ++j) hist_buf[j % BufNum][(x >> (j * 8)) & 0xFF] += 2;
            }
        }
        __builtin_prefetch(it + 512);  // don't know why but it works
    }
    for (; it != data + len; ++it) ++hist_buf[0][*it];

    for (size_t i = 0; i < 256; ++i) {
        QC_UNROLL
        for (size_t j = 0; j < BufNum; ++j) hist[i] += hist_buf[j][i];
    }
}
