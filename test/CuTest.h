#ifndef CUTEST_H

#include <setjmp.h>
#include <stdarg.h>
#include <time.h>
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CUTEST_VERSION  "CuTest 1.5"

/* INTERFACE */
char *CuStrAlloc(int size);
char *CuStrCopy(const char *old);

#define CU_ALLOC(TYPE)		((TYPE*) malloc(sizeof(TYPE)))

#define HUGE_STRING_LEN	8192
#define STRING_MAX		256
#define STRING_INC		256

typedef struct {
    int length;
    int size;
    char *buffer;
} CuString;

void CuStringInit(CuString *str);
CuString* CuStringNew(void);
void CuStringRead(CuString *str, const char *path);
void CuStringAppend(CuString *str, const char *text);
void CuStringAppendChar(CuString *str, char ch);
void CuStringAppendFormat(CuString *str, const char *format, ...);
void CuStringInsert(CuString *str, const char *text, int pos);
void CuStringResize(CuString *str, int newSize);
void CuStringDelete(CuString *str);

/* CuTest */

typedef struct CuTest CuTest;

typedef void (*TestFunction)(CuTest*);

struct CuTest {
    char *name;
    TestFunction function;
    int failed;
    int ran;
    const char *message;
    jmp_buf *jumpBuf;
    clock_t begin;
    clock_t end;
};

void CuTestInit(CuTest *t, const char *name, TestFunction function);
CuTest* CuTestNew(const char *name, TestFunction function);
void CuTestRun(CuTest *tc);
void CuTestDelete(CuTest *t);

/* Internal versions of assert functions -- use the public versions */
void CuFail_Line(CuTest *tc, const char *file, int line, const char *message2, const char *message);
void CuAssert_Line(CuTest *tc, const char *file, int line, const char *message, int condition);
void CuAssertStrEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               const char *expected, const char *actual);
void CuAssertIntEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               int expected, int actual);
void CuAssertLongEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                                long expected, long actual);
void CuAssertLongLongEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                                    long long expected, long long actual);
void CuAssertDblEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               double expected, double actual, double delta);
void CuAssertPtrEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               void *expected, void *actual);

/* public assert functions */

#define CuFail(tc, ms)                        CuFail_Line(  (tc), __FILE__, __LINE__, NULL, (ms))
#define CuAssert(tc, ms, cond)                CuAssert_Line((tc), __FILE__, __LINE__, (ms), (cond))
#define CuAssertTrue(tc, cond)                CuAssert_Line((tc), __FILE__, __LINE__, "assert failed", (cond))
#define CuAssertFalse(tc, cond)               CuAssert_Line((tc), __FILE__, __LINE__, "assert failed", !(cond))

#define CuAssertStrEquals(tc,ex,ac)             CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertStrEquals_Msg(tc,ms,ex,ac)      CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertIntEquals(tc,ex,ac)             CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertIntEquals_Msg(tc,ms,ex,ac)      CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertLongEquals(tc,ex,ac)            CuAssertLongEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertLongEquals_Msg(tc,ms,ex,ac)     CuAssertLongEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertLongLongEquals(tc,ex,ac)        CuAssertLongLongEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertLongLongEquals_Msg(tc,ms,ex,ac) CuAssertLongLongEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertDblEquals(tc,ex,ac,dl)          CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(dl))
#define CuAssertDblEquals_Msg(tc,ms,ex,ac,dl)   CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),(dl))
#define CuAssertPtrEquals(tc,ex,ac)             CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define CuAssertPtrEquals_Msg(tc,ms,ex,ac)      CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))

#define CuAssertPtrNotNull(tc,p)        CuAssert_Line((tc),__FILE__,__LINE__,"null pointer unexpected",(p != NULL))
#define CuAssertPtrNotNullMsg(tc,msg,p) CuAssert_Line((tc),__FILE__,__LINE__,(msg),(p != NULL))

/* CuSuite */

#define MAX_TEST_CASES	1024

#define SUITE_ADD_TEST(SUITE,TEST)	CuSuiteAdd(SUITE, CuTestNew(#TEST, TEST))

typedef struct {
    int count;
    CuTest *list[MAX_TEST_CASES];
    int failCount;
} CuSuite;

void CuSuiteInit(CuSuite *testSuite);
CuSuite* CuSuiteNew(void);
void CuSuiteDelete(CuSuite *testSuite);
void CuSuiteAdd(CuSuite *testSuite, CuTest *testCase);
void CuSuiteAddSuite(CuSuite *testSuite, CuSuite *testSuite2);
void CuSuiteRun(CuSuite *testSuite);
void CuSuiteSummary(CuSuite *testSuite, CuString *summary);
void CuSuiteDetails(CuSuite *testSuite, CuString *details);

#define CUTEST_H
#endif /* CUTEST_H */

#ifdef CUTEST_IMPLEMENTATION

/* IMPLEMENTATION */
char *CuStrAlloc(int size) {
    char *newStr = (char*) malloc(sizeof(char) * size);
    return newStr;
}

char *CuStrCopy(const char *old) {
    int len = strlen(old);
    char *newStr = CuStrAlloc(len + 1);
    strcpy(newStr, old);
    return newStr;
}

void CuStringInit(CuString *str) {
    str->length = 0;
    str->size = STRING_MAX;
    str->buffer = (char*) malloc(sizeof(char) * str->size);
    str->buffer[0] = '\0';
}

CuString* CuStringNew(void) {
    CuString *str = (CuString*) malloc(sizeof(CuString));
    str->length = 0;
    str->size = STRING_MAX;
    str->buffer = (char*) malloc(sizeof(char) * str->size);
    str->buffer[0] = '\0';
    return str;
}

void CuStringRead(CuString *str, const char *path); // FIXME: check

void CuStringAppend(CuString *str, const char *text) {
    if (text == NULL) {
        text = "NULL";
    }
    int length = strlen(text);
    if (str->length + length + 1 >= str->size) {
        CuStringResize(str, str->length + length + 1 + STRING_INC);
    }
    str->length += length;
    strcat(str->buffer, text);
}

void CuStringAppendChar(CuString *str, char ch) {
    char text[2] = {ch, '\0'};
    CuStringAppend(str, text);
}

void CuStringAppendFormat(CuString *str, const char *format, ...) {
    va_list argp;
    char buf[HUGE_STRING_LEN];
    va_start(argp, format);
    vsprintf(buf, format, argp);
    va_end(argp);
    CuStringAppend(str, buf);
}

void CuStringInsert(CuString *str, const char *text, int pos) {
    int length = strlen(text);
    if (pos > str->length) {
        pos = str->length;
    }
    if (str->length + length + 1 >= str->size) {
        CuStringResize(str, str->length + length + 1 + STRING_INC);
    }
    memmove(str->buffer + pos + length, str->buffer + pos, (str->length - pos) + 1);
    str->length += length;
    memcpy(str->buffer + pos, text, length);
}

void CuStringResize(CuString *str, int newSize) {
    str->buffer = (char*) realloc(str->buffer, sizeof(char) * newSize);
    str->size = newSize;
}

void CuStringDelete(CuString *str) {
    if (!str) {
        return;
    }
    free(str->buffer);
    free(str);
}

void CuTestInit(CuTest *t, const char *name, TestFunction function) {
    t->name = CuStrCopy(name);
    t->failed = 0;
    t->ran = 0;
    t->message = NULL;
    t->function = function;
    t->jumpBuf = NULL;
}

CuTest* CuTestNew(const char *name, TestFunction function) {
    CuTest *tc = CU_ALLOC(CuTest);
    CuTestInit(tc, name, function);
    return tc;
}

void CuTestRun(CuTest *tc) {
    jmp_buf buf;
    tc->jumpBuf = &buf;
    if (setjmp(buf) == 0) {
        tc->ran = 1;
        tc->begin = clock();
        (tc->function)(tc);
        tc->end = clock();
    }
    tc->jumpBuf = 0;
}

void CuTestDelete(CuTest *t) {
    if (!t) {
        return;
    }
    free(t->name);
    free(t);
}

/* INTERNAL IMPLEMENTATION */
static void CuFailInternal(CuTest *tc, const char *file, int line, CuString *string) {
    char buf[HUGE_STRING_LEN];
    sprintf(buf, "%s:%d: ", file, line);
    CuStringInsert(string, buf, 0);
    tc->failed = 1;
    tc->message = string->buffer;
    if (tc->jumpBuf != 0) {
        longjmp(*(tc->jumpBuf), 0);
    }
}

void CuFail_Line(CuTest *tc, const char *file, int line, const char *message2, const char *message) {
    CuString string;
    CuStringInit(&string);
    if (message2 != NULL) {
        CuStringAppend(&string, message2);
        CuStringAppend(&string, ": ");
    }
    CuStringAppend(&string, message);
    CuFailInternal(tc, file, line, &string);
}

void CuAssert_Line(CuTest *tc, const char *file, int line, const char *message, int condition) {
    if (condition) {
        return;
    }
    CuFail_Line(tc, file, line, NULL, message);
}

void CuAssertStrEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               const char *expected, const char *actual) {
    CuString string;
    if ((expected == NULL && actual == NULL) ||
        (expected != NULL && actual != NULL && strcmp(expected, actual) == 0)) {
        return;
    }
    CuStringInit(&string);
    if (message != NULL) {
        CuStringAppend(&string, message);
        CuStringAppend(&string, ": ");
    }
    CuStringAppend(&string, "expected <");
    CuStringAppend(&string, expected);
    CuStringAppend(&string, "> but was <");
    CuStringAppend(&string, actual);
    CuStringAppend(&string, ">");
    CuFailInternal(tc, file, line, &string);
}

void CuAssertIntEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               int expected, int actual) {
    char buf[STRING_MAX];
    if (expected == actual) {
        return;
    }
    sprintf(buf, "expected <%d> but was <%d>", expected, actual);
    CuFail_Line(tc, file, line, message, buf);
}

void CuAssertLongEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                                long expected, long actual) {
    char buf[STRING_MAX];
    if (expected == actual) {
        return;
    }
    sprintf(buf, "expected <%ld> but was <%ld>", expected, actual);
    CuFail_Line(tc, file, line, message, buf);
}

void CuAssertLongLongEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                                    long long expected, long long actual) {
    char buf[STRING_MAX];
    if (expected == actual) {
        return;
    }
    sprintf(buf, "expected <%lld> but was <%lld>", expected, actual);
    CuFail_Line(tc, file, line, message, buf);
}

void CuAssertDblEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               double expected, double actual, double delta) {
    char buf[STRING_MAX];
    if (fabs(expected - actual) <= delta) {
        return;
    }
    sprintf(buf, "expected <%f> but was <%f>", expected, actual);
    CuFail_Line(tc, file, line, message, buf);
}

void CuAssertPtrEquals_LineMsg(CuTest *tc, const char *file, int line, const char *message,
                               void *expected, void *actual) {
    char buf[STRING_MAX];
    if (expected == actual) {
        return;
    }
    sprintf(buf, "expected pointer <0x%p> but was <0x%p>", expected, actual);
    CuFail_Line(tc, file, line, message, buf);
}

void CuSuiteInit(CuSuite *testSuite) {
    testSuite->count = 0;
    testSuite->failCount = 0;
    memset(testSuite->list, 0, sizeof(testSuite->list));
}

CuSuite* CuSuiteNew(void) {
    CuSuite *testSuite = CU_ALLOC(CuSuite);
    CuSuiteInit(testSuite);
    return testSuite;
}

void CuSuiteDelete(CuSuite *testSuite) {
    for (unsigned int n = 0; n < MAX_TEST_CASES; n++) {
        if (testSuite->list[n]) {
            CuTestDelete(testSuite->list[n]);
        }
    }
    free(testSuite);
}

void CuSuiteAdd(CuSuite *testSuite, CuTest *testCase) {
    assert(testSuite->count < MAX_TEST_CASES);
    testSuite->list[testSuite->count] = testCase;
    testSuite->count++;
}

void CuSuiteAddSuite(CuSuite *testSuite, CuSuite *testSuite2) {
    for (int i = 0; i < testSuite2->count; ++i) {
        CuTest *testCase = testSuite2->list[i];
        CuSuiteAdd(testSuite, testCase);
    }
}

void CuSuiteRun(CuSuite *testSuite) {
    for (int i = 0; i < testSuite->count; ++i) {
        CuTest *testCase = testSuite->list[i];
        CuTestRun(testCase);
        if (testCase->failed) {
            testSuite->failCount++;
        }
    }
}

void CuSuiteSummary(CuSuite *testSuite, CuString *summary) {
    char time[50];
    for (int i = 0; i < testSuite->count; ++i) {
        CuTest *testCase = testSuite->list[i];
        sprintf(time, "%f", (double)(testCase->end - testCase->begin) / (1000*CLOCKS_PER_SEC));
        CuStringAppend(summary, time);
        CuStringAppend(summary, testCase->failed ? "ms | FAILURE | " : "ms | SUCCESS | ");
        CuStringAppend(summary, testCase->name);
        CuStringAppend(summary, "\n");
    }
    CuStringAppend(summary, "-----\n");
}

void CuSuiteDetails(CuSuite *testSuite, CuString *details) {
    if (testSuite->failCount == 0) {
        int passCount = testSuite->count - testSuite->failCount;
        const char *testWord = passCount == 1 ? "test" : "tests";
        CuStringAppendFormat(details, "OK (%d %s)\n", passCount, testWord);
    } else {
        if (testSuite->failCount == 1) {
            CuStringAppend(details, "There was 1 failure:\n");
        } else {
            CuStringAppendFormat(details, "There were %d failures:\n", testSuite->failCount);
        }
        int failCount = 0;
        for (int i = 0; i < testSuite->count; ++i) {
            CuTest *testCase = testSuite->list[i];
            if (testCase->failed) {
                failCount++;
                CuStringAppendFormat(details, "%d) %s: %s\n", failCount, testCase->name, testCase->message);
            }
        }
        CuStringAppend(details, "\n!!!FAILURES!!!\n");
        CuStringAppendFormat(details, "Runs: %d ", testSuite->count);
        CuStringAppendFormat(details, "Passes: %d ", testSuite->count - testSuite->failCount);
        CuStringAppendFormat(details, "Fails: %d\n", testSuite->failCount);
    }
}

#endif //CUTEST_IMPLEMENTATION