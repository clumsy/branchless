#include "CuTest.h"
#define BRANCHLESS_IMPLEMENTATION
#include "../branchless.h"

void TestAbsInt(CuTest *tc) {
    CuAssertIntEquals(tc, 42, abs_int(42));
    CuAssertIntEquals(tc, 42, abs_int(-42));
}

void TestAbsLong(CuTest *tc) {
    CuAssertLongEquals(tc, 42, abs_long(42));
    CuAssertLongEquals(tc, 42, abs_long(-42));
}

void TestOppositeSignInt(CuTest *tc) {
    CuAssertFalse(tc, opposite_sign_int(42, 42));
    CuAssertTrue(tc, opposite_sign_int(-42, 42));
    CuAssertFalse(tc, opposite_sign_int(-42, -42));
}

void TestOppositeSignLong(CuTest *tc) {
    CuAssertFalse(tc, opposite_sign_long(42, 42));
    CuAssertTrue(tc, opposite_sign_long(-42, 42));
    CuAssertFalse(tc, opposite_sign_long(-42, -42));
}

void TestMinInt(CuTest *tc) {
    CuAssertIntEquals(tc,  42, min_int(42, 43));
    CuAssertIntEquals(tc, -42, min_int(-42, 42));
}

void TestMaxInt(CuTest *tc) {
    CuAssertIntEquals(tc, 42, max_int(42, 41));
    CuAssertIntEquals(tc, 42, max_int(-42, 42));
}

void TestMinLong(CuTest *tc) {
    CuAssertLongEquals(tc,  42, min_long(42, 43));
    CuAssertLongEquals(tc, -42, min_long(-42, 42));
}

void TestMaxLong(CuTest *tc) {
    CuAssertLongEquals(tc, 42, max_long(42, 41));
    CuAssertLongEquals(tc, 42, max_long(-42, 42));
}

/*-------------------------------------------------------------------------*
 * main
 *-------------------------------------------------------------------------*/

CuSuite* CuGetSuite(void) {
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestAbsInt);
    SUITE_ADD_TEST(suite, TestAbsLong);

    SUITE_ADD_TEST(suite, TestOppositeSignInt);
    SUITE_ADD_TEST(suite, TestOppositeSignLong);

    SUITE_ADD_TEST(suite, TestMinInt);
    SUITE_ADD_TEST(suite, TestMaxInt);

    SUITE_ADD_TEST(suite, TestMinLong);
    SUITE_ADD_TEST(suite, TestMaxLong);

    return suite;
}