// $Id$
#include "testing/Checks.h"
#include <cstring>

namespace testing {

namespace {

void CheckStringsEqual (
        TestResults& results,
        char const* expected,
        char const* actual, 
        TestDetails const& details)
{
    if (std::strcmp(expected, actual))
    {
        testing::MemoryOutStream stream;
        stream << "Expected " << expected << " but was " << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}

}//namespace

void CheckEqual(TestResults& results, char const* expected, char const* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}

void CheckEqual(TestResults& results, char* expected, char* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}

void CheckEqual(TestResults& results, char* expected, char const* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}

void CheckEqual(TestResults& results, char const* expected, char* actual,
                TestDetails const& details)
{
    CheckStringsEqual(results, expected, actual, details);
}

}//namespace testing
