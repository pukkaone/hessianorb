// $Id$
#ifndef TESTING_TIMECONSTRAINT_H
#define TESTING_TIMECONSTRAINT_H

#include "testing/TimeHelpers.h"

namespace testing {

class TestResults;
class TestDetails;

class TimeConstraint
{
public:
    TimeConstraint(int ms, TestDetails const& details);
    ~TimeConstraint();

private:
    void operator=(TimeConstraint const&); 
    TimeConstraint(TimeConstraint const&);

    Timer m_timer;
    TestDetails const& m_details;
    int const m_maxMs;
};

#define TESTING_TIME_CONSTRAINT(ms) \
    testing::TimeConstraint testing__timeConstraint__(ms, testing::TestDetails(m_details, __LINE__))

#define TESTING_TIME_CONSTRAINT_EXEMPT() do { m_timeConstraintExempt = true; } while (0)

}//namespace testing
#endif
