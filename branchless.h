#include <stdint.h>

#ifndef BRANCHLESS_H
#define BRANCHLESS_H

/**
 * @link http://graphics.stanford.edu/~seander/bithacks.html#DetectOppositeSigns
 * @author Manfred Weis
 */
int32_t opposite_sign_int32(int32_t x, int32_t y);
int64_t opposite_sign_int64(int64_t x, int64_t y);

/**
 * @link http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
 * @author Peter Kankowski
 */
int32_t abs_int32(int32_t x);
int64_t abs_int64(int64_t x);

/**
 * @link http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
 * @author Timothy B. Terriberry
 */
int32_t min_int32(int32_t x, int32_t y);
int32_t max_int32(int32_t x, int32_t y);
int64_t min_int64(int64_t x, int64_t y);
int64_t max_int64(int64_t x, int64_t y);

/**
 * @link http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
 * @author Don Clugston
 */
int32_t count_bits_int32(int32_t x);
int64_t count_bits_int64(int64_t x);

#endif //BRANCHLESS_H

#ifdef BRANCHLESS_IMPLEMENTATION

inline int32_t abs_int32(int32_t x) {
    int32_t mask = x >> 31;
    return (x + mask) ^ mask;
}

inline int64_t abs_int64(int64_t x) {
    int64_t mask = x >> 63;
    return (x + mask) ^ mask;
}

inline int32_t opposite_sign_int32(int32_t x, int32_t y) {
    return (x ^ y) < 0;
}

inline int64_t opposite_sign_int64(int64_t x, int64_t y) {
    return (x ^ y) < 0;
}

inline int32_t min_int32(int32_t x, int32_t y) {
    return y ^ ((x ^ y) & -(x < y));
}

inline int32_t max_int32(int32_t x, int32_t y) {
    return x ^ ((x ^ y) & -(x < y));
}

inline int64_t min_int64(int64_t x, int64_t y) {
    return y ^ ((x ^ y) & -(x < y));
}

inline int64_t max_int64(int64_t x, int64_t y) {
    return x ^ ((x ^ y) & -(x < y));
}

inline int32_t count_bits_int32(int32_t x) {
    x -= (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    return ((x + (x >> 4) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

inline int64_t count_bits_int64(int64_t x) {
    x -= (x >> 1) & 0x5555555555555555;
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    return ((x + (x >> 4) & 0x0F0F0F0F0F0F0F0F) * 0x0101010101010101) >> 56;
}

#endif //BRANCHLESS_IMPLEMENTATION
