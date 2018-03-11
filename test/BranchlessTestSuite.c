#include "CuTest.h"
#define BRANCHLESS_IMPLEMENTATION
#include "../branchless.h"

void TestSign2Way(CuTest *tc) {
    CuAssertIntEquals(tc, 1, positive_sign(42));
    CuAssertIntEquals(tc, 1, positive_sign(0));
    CuAssertIntEquals(tc, 0, positive_sign(-42));
    CuAssertIntEquals(tc, 0, negative_sign(42));
    CuAssertIntEquals(tc, 0, negative_sign(0));
    CuAssertIntEquals(tc, -1, negative_sign(-42));
    CuAssertIntEquals(tc, 1, sign_sign(42));
    CuAssertIntEquals(tc, 1, sign_sign(0));
    CuAssertIntEquals(tc, -1, sign_sign(-42));
}

void TestSign3Way(CuTest *tc) {
    CuAssertIntEquals(tc, 1, sign_sign_zero(42));
    CuAssertIntEquals(tc, -1, sign_sign_zero(-42));
    CuAssertIntEquals(tc, 0, sign_sign_zero(0));
}

void TestAbsInt32(CuTest *tc) {
    CuAssertIntEquals(tc, 42, abs_int32(42));
    CuAssertIntEquals(tc, 42, abs_int32(-42));
}

void TestAbsInt64(CuTest *tc) {
    CuAssertLongLongEquals(tc, 42, abs_int64(42));
    CuAssertLongLongEquals(tc, 42, abs_int64(-42));
}

void TestOppositeSignInt32(CuTest *tc) {
    CuAssertFalse(tc, opposite_sign_int32(42, 42));
    CuAssertTrue(tc, opposite_sign_int32(-42, 42));
    CuAssertFalse(tc, opposite_sign_int32(-42, -42));
}

void TestOppositeSignInt64(CuTest *tc) {
    CuAssertFalse(tc, opposite_sign_int64(42, 42));
    CuAssertTrue(tc, opposite_sign_int64(-42, 42));
    CuAssertFalse(tc, opposite_sign_int64(-42, -42));
}

void TestMinInt32(CuTest *tc) {
    CuAssertIntEquals(tc,  42, min_int32(42, 43));
    CuAssertIntEquals(tc, -42, min_int32(-42, 42));
}

void TestMaxInt32(CuTest *tc) {
    CuAssertIntEquals(tc, 42, max_int32(42, 41));
    CuAssertIntEquals(tc, 42, max_int32(-42, 42));
}

void TestMinInt64(CuTest *tc) {
    CuAssertLongLongEquals(tc,  42, min_int64(42, 43));
    CuAssertLongLongEquals(tc, -42, min_int64(-42, 42));
}

void TestMaxInt64(CuTest *tc) {
    CuAssertLongLongEquals(tc, 42, max_int64(42, 41));
    CuAssertLongLongEquals(tc, 42, max_int64(-42, 42));
}

void TestCountBitsInt32(CuTest *tc) {
    CuAssertIntEquals(tc, 16, count_bits_int32(0x55555555)); // 01010101 01010101 01010101 01010101
    CuAssertIntEquals(tc, 20, count_bits_int32(0xFFF000FF)); // 11111111 11110000 00000000 11111111
    CuAssertIntEquals(tc,  8, count_bits_int32(0x00000FF0)); // 00000000 00000000 00001111 11110000
}

void TestCountBitsInt64(CuTest *tc) {
    CuAssertLongLongEquals(tc, 32, count_bits_int64(0x5555555555555555)); // 01010101 01010101 01010101 01010101 01010101 01010101 01010101 01010101
    CuAssertLongLongEquals(tc, 36, count_bits_int64(0xFFF000FFF000FFF0)); // 11111111 11110000 00000000 11111111 11110000 00000000 11111111 11110000
    CuAssertLongLongEquals(tc, 16, count_bits_int64(0x00000FF000000FF0)); // 00000000 00000000 00001111 11110000 00000000 00000000 00001111 11110000
}

/*-------------------------------------------------------------------------*
 * main
 *-------------------------------------------------------------------------*/

CuSuite* CuGetSuite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestSign2Way);
    SUITE_ADD_TEST(suite, TestSign3Way);

    SUITE_ADD_TEST(suite, TestAbsInt32);
    SUITE_ADD_TEST(suite, TestAbsInt64);

    SUITE_ADD_TEST(suite, TestOppositeSignInt32);
    SUITE_ADD_TEST(suite, TestOppositeSignInt64);

    SUITE_ADD_TEST(suite, TestMinInt32);
    SUITE_ADD_TEST(suite, TestMaxInt32);

    SUITE_ADD_TEST(suite, TestMinInt64);
    SUITE_ADD_TEST(suite, TestMaxInt64);

    SUITE_ADD_TEST(suite, TestCountBitsInt32);
    SUITE_ADD_TEST(suite, TestCountBitsInt64);

    return suite;
}