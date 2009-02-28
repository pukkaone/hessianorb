// $Id$
#include "testing/TimeConstraint.h"
#include "testing/TestResults.h"
#include "testing/MemoryOutStream.h"
#include "testing/CurrentTest.h"

namespace testing {

TimeConstraint::TimeConstraint(int ms, TestDetails const& details)
	: m_details(details)
    , m_maxMs(ms)
{
    m_timer.Start();
}

TimeConstraint::~TimeConstraint()
{
    int const totalTimeInMs = m_timer.GetTimeInMs();
    if (totalTimeInMs > m_maxMs)
    {
        MemoryOutStream stream;
        stream << "Time constraint failed. Expected to run test under " << m_maxMs <<
                  "ms but took " << totalTimeInMs << "ms.";

		testing::CurrentTest::Results()->OnTestFailure(m_details, stream.GetText());
    }
}

}//namespace testing
