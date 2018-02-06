#ifndef BRANCHLESS_H
#define BRANCHLESS_H

static const int INT_MASK  = sizeof(int)  * CHAR_BIT - 1;
static const int LONG_MASK = sizeof(long) * CHAR_BIT - 1;

/**
 * @link http://graphics.stanford.edu/~seander/bithacks.html#DetectOppositeSigns
 * @author Manfred Weis
 */
int  opposite_sign_int(int x, int y);
long opposite_sign_long(long x, long y);

/**
 * @link http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
 * @author Peter Kankowski
 */
int  abs_int(int x);
long abs_long(long x);

/**
 * @link http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
 * @author Timothy B. Terriberry
 */
int  min_int(int x, int y);
int  max_int(int x, int y);
long min_long(long x, long y);
long max_long(long x, long y);

#endif //BRANCHLESS_H

#ifdef BRANCHLESS_IMPLEMENTATION

inline int abs_int(int x) {
    int mask = x >> INT_MASK;
    return (x + mask) ^ mask;
}

inline long abs_long(long x) {
    long mask = x >> LONG_MASK;
    return (x + mask) ^ mask;
}

inline int opposite_sign_int(int x, int y) {
    return (x ^ y) < 0;
}

inline long opposite_sign_long(long x, long y) {
    return (x ^ y) < 0;
}

inline int min_int(int x, int y) {
    return y ^ ((x ^ y) & -(x < y));
}

inline int max_int(int x, int y) {
    return x ^ ((x ^ y) & -(x < y));
}

inline long min_long(long x, long y) {
    return y ^ ((x ^ y) & -(x < y));
}

inline long max_long(long x, long y) {
    return x ^ ((x ^ y) & -(x < y));
}

#endif //BRANCHLESS_IMPLEMENTATION
