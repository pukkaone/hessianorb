// $Id$
#ifndef TESTING_TIMEHELPERS_H
#define TESTING_TIMEHELPERS_H

#include "../Config.h"


#ifdef TESTING_MINGW
    #ifndef __int64
        #define __int64 long long
    #endif
#endif

namespace testing {

class Timer
{
public:
    Timer();
	void Start();
	int GetTimeInMs() const;    

private:
    __int64 GetTime() const;

    void* m_threadHandle;

#if defined(_WIN64)
    unsigned __int64 m_processAffinityMask;
#else
    unsigned long m_processAffinityMask;
#endif

    __int64 m_startTime;
    __int64 m_frequency;
};


namespace TimeHelpers
{
void SleepMs (int ms);
}//namespace TimeHelpers


}//namespace testing
#endif
