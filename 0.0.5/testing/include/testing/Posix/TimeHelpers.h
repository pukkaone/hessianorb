// $Id$
#ifndef TESTING_TIMEHELPERS_H
#define TESTING_TIMEHELPERS_H

#include <sys/time.h>

namespace testing {

class Timer
{
public:
    Timer();
    void Start();
    int GetTimeInMs() const;    

private:
    struct timeval m_startTime;    
};


namespace TimeHelpers {
void SleepMs(int ms);
}//namespace TimeHelpers


}//namespace testing
#endif
