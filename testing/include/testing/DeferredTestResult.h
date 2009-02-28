// $Id$
#ifndef TESTING_DEFERREDTESTRESULT_H
#define TESTING_DEFERREDTESTRESULT_H

#include <string>
#include <vector>

namespace testing {

struct DeferredTestResult
{
    DeferredTestResult();
    DeferredTestResult(char const* suite, char const* test);

    std::string suiteName;
    std::string testName;
    std::string failureFile;
    
    typedef std::pair<int, std::string> Failure;
    typedef std::vector<Failure> FailureVec;
    FailureVec failures;
    
    float timeElapsed;
    bool failed;
};

}//namespace testing
#endif
