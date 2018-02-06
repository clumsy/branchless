cmake_minimum_required(VERSION 3.8)
project(branchless)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES branchless.h)
set(TEST_FILES test/CuTest.h test/AllTests.c test/BranchlessTestSuite.c)

add_executable(AllTests ${SOURCE_FILES} ${TEST_FILES})
