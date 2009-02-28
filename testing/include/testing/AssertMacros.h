// $Id$
#ifndef TESTING_ASSERTMACROS_H 
#define TESTING_ASSERTMACROS_H

#include "testing/Checks.h"
#include "testing/TestFailedException.h"
#include "testing/TestDetails.h"
#include "testing/CurrentTest.h"

#ifdef ASSERT
    #error testing framework redefines ASSERT
#endif

#ifdef ASSERT_EQUAL
    #error testing framework redefines ASSERT_EQUAL
#endif

#ifdef ASSERT_CLOSE
    #error testing framework redefines ASSERT_CLOSE
#endif

#ifdef ASSERT_ARRAY_EQUAL
    #error testing framework redefines ASSERT_ARRAY_EQUAL
#endif

#ifdef ASSERT_ARRAY_CLOSE
    #error testing framework redefines ASSERT_ARRAY_CLOSE
#endif

#ifdef ASSERT_ARRAY2D_CLOSE
    #error testing framework redefines ASSERT_ARRAY2D_CLOSE
#endif

#define ASSERT(value) \
    do \
    { \
        try { \
            if (!testing::Check(value)) \
                testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(*testing::CurrentTest::Details(), __LINE__), #value); \
        } \
        catch (testing::TestFailedException&) { \
            throw; \
        } \
        catch (...) { \
            testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(*testing::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in ASSERT(" #value ")"); \
        } \
    } while (0)

#define ASSERT_EQUAL(expected, actual) \
    do \
    { \
        try { \
            testing::CheckEqual(*testing::CurrentTest::Results(), expected, actual, testing::TestDetails(*testing::CurrentTest::Details(), __LINE__)); \
        } \
        catch (testing::TestFailedException&) { \
            throw; \
        } \
        catch (...) { \
            testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(*testing::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in ASSERT_EQUAL(" #expected ", " #actual ")"); \
        } \
    } while (0)

#define ASSERT_CLOSE(expected, actual, tolerance) \
    do \
    { \
        try { \
            testing::CheckClose(*testing::CurrentTest::Results(), expected, actual, tolerance, testing::TestDetails(*testing::CurrentTest::Details(), __LINE__)); \
        } \
        catch (testing::TestFailedException&) { \
            throw; \
        } \
        catch (...) { \
            testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(*testing::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in ASSERT_CLOSE(" #expected ", " #actual ")"); \
        } \
    } while (0)

#define ASSERT_ARRAY_EQUAL(expected, actual, count) \
    do \
    { \
        try { \
            testing::CheckArrayEqual(*testing::CurrentTest::Results(), expected, actual, count, testing::TestDetails(*testing::CurrentTest::Details(), __LINE__)); \
        } \
        catch (testing::TestFailedException&) { \
            throw; \
        } \
        catch (...) { \
            testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(*testing::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in ASSERT_ARRAY_EQUAL(" #expected ", " #actual ")"); \
        } \
    } while (0)

#define ASSERT_ARRAY_CLOSE(expected, actual, count, tolerance) \
    do \
    { \
        try { \
            testing::CheckArrayClose(*testing::CurrentTest::Results(), expected, actual, count, tolerance, testing::TestDetails(*testing::CurrentTest::Details(), __LINE__)); \
        } \
        catch (testing::TestFailedException&) { \
            throw; \
        } \
        catch (...) { \
            testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(*testing::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in ASSERT_ARRAY_CLOSE(" #expected ", " #actual ")"); \
        } \
    } while (0)

#define ASSERT_THROW(expression, ExpectedExceptionType) \
    do \
    { \
        bool caught_ = false; \
        try { expression; } \
        catch (ExpectedExceptionType const&) { caught_ = true; } \
        catch (...) {} \
        if (!caught_) \
            testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(*testing::CurrentTest::Details(), __LINE__), "Expected exception: \"" #ExpectedExceptionType "\" not thrown"); \
    } while(0)

#endif
