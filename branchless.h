#include <stdint.h>
#include <stdbool.h>

#ifndef BRANCHLESS_H
#define BRANCHLESS_H

/**
 * gets the sign of the number
 *
 * @param x number to check
 * @return 1 for positive number or zero, 0 for negative
 * @link http://www.coranac.com/documents/bittrick/#ssec-math-sign2
 */
int32_t positive_sign(int32_t x);

/**
 * gets the sign of the number
 *
 * @param x number to check
 * @return 0 for positive number or zero, -1 for negative
 * @link http://www.coranac.com/documents/bittrick/#ssec-math-sign2
 */
int32_t negative_sign(int32_t x);

/**
 * gets the sign of the number
 *
 * @param x number to check
 * @return 1 for positive number or zero, -1 for negative
 * @link http://www.coranac.com/documents/bittrick/#ssec-math-sign2
 */
int32_t sign_sign(int32_t x);

/**
 * gets the sign of the number
 *
 * @param x number to check
 * @return 1 for positive number, -1 for negative and 0 for zero
 * @link http://www.coranac.com/documents/bittrick/#ssec-math-sign3
 */
int32_t sign_sign_zero(int32_t x);

/**
 * checks if the value is a power of 2
 *
 * @param x value to check
 * @return true if value is a power of 2, false otherwise
 * @link http://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
 */
bool is_power_of_2_int32(int32_t x);
bool is_power_of_2_int64(int64_t x);

 /**
  * checks whether provided values have different signs
  *
  * @param x first value
  * @param y second value
  * @return true if opposite signs, false if same
  * @link http://graphics.stanford.edu/~seander/bithacks.html#DetectOppositeSigns
  * @author Manfred Weis
  */
bool opposite_sign_int32(int32_t x, int32_t y);
bool opposite_sign_int64(int64_t x, int64_t y);

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

inline int32_t negative_sign(int32_t x) {
    return x >> 31;
}

inline int32_t positive_sign(int32_t x) {
    return (x >> 31) + 1;
}

inline int32_t sign_sign(int32_t x) {
    return (x >> 31) | 1;
}

inline int32_t sign_sign_zero(int32_t x) {
    return (x >> 31) - (-x >> 31);
}

inline bool is_power_of_2_int32(int32_t x) {
    return x && !(x & (x - 1));
}

inline bool is_power_of_2_int64(int64_t x) {
    return x && !(x & (x - 1));
}

inline int32_t abs_int32(int32_t x) {
    int32_t mask = x >> 31;
    return (x + mask) ^ mask;
}

inline int64_t abs_int64(int64_t x) {
    int64_t mask = x >> 63;
    return (x + mask) ^ mask;
}

inline bool opposite_sign_int32(int32_t x, int32_t y) {
    return (x ^ y) < 0;
}

inline bool opposite_sign_int64(int64_t x, int64_t y) {
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
