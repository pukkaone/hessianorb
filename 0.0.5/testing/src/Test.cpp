// $Id$
#include "testing/Config.h"
#include "testing/Test.h"
#include "testing/TestList.h"
#include "testing/TestResults.h"
#include "testing/MemoryOutStream.h"
#include "testing/ExecuteTest.h"

#ifdef TESTING_POSIX
    #include "testing/Posix/SignalTranslator.h"
#endif

namespace testing {

TestList& Test::GetTestList()
{
    static TestList s_list;
    return s_list;
}

Test::Test (char const* testName, char const* suiteName, char const* filename, int lineNumber)
    : m_details(testName, suiteName, filename, lineNumber)
    , next(0)
    , m_timeConstraintExempt(false)
{
}

Test::~Test()
{
}

void Test::Run()
{
	ExecuteTest(*this, m_details);
}

void Test::RunImpl() const
{
}

}//namespace testing
