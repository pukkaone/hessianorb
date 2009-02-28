// $Id$
#include "testing/CurrentTest.h"

namespace testing {

TestResults*& CurrentTest::Results()
{
    static TestResults* testResults = 0;
    return testResults;
}

const TestDetails*& CurrentTest::Details()
{
    static const TestDetails* testDetails = 0;
    return testDetails;
}

}//namespace testing
