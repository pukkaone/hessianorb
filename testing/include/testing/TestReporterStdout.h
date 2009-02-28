// $Id$
#ifndef TESTING_TESTREPORTERSTDOUT_H
#define TESTING_TESTREPORTERSTDOUT_H

#include "testing/TestReporter.h"

namespace testing {

class TestReporterStdout: public TestReporter
{
private:
    virtual void ReportTestStart(TestDetails const& test);
    virtual void ReportFailure(TestDetails const& test, char const* failure);
    virtual void ReportTestFinish(TestDetails const& test, float secondsElapsed);
    virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);
};

}//namespace testing
#endif 
