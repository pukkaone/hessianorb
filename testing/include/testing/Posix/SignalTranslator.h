// $Id$
#ifndef TESTING_SIGNALTRANSLATOR_H
#define TESTING_SIGNALTRANSLATOR_H

#include <setjmp.h>
#include <signal.h>

namespace testing {

class SignalTranslator
{
public:
    SignalTranslator();
    ~SignalTranslator();

    static sigjmp_buf* s_jumpTarget;

private:
    sigjmp_buf m_currentJumpTarget;
    sigjmp_buf* m_oldJumpTarget;

    struct sigaction m_old_SIGFPE_action;
    struct sigaction m_old_SIGTRAP_action;
    struct sigaction m_old_SIGSEGV_action;
    struct sigaction m_old_SIGBUS_action;
    struct sigaction m_old_SIGABRT_action;
    struct sigaction m_old_SIGALRM_action;
};

#if !defined (__GNUC__)
    #define TESTING_EXTENSION
#else
    #define TESTING_EXTENSION __extension__
#endif

#define TESTING_THROW_SIGNALS \
	testing::SignalTranslator sig; \
	if (TESTING_EXTENSION sigsetjmp(*testing::SignalTranslator::s_jumpTarget, 1) != 0) \
        throw "Unhandled system exception"; 

}//namespace testing
#endif
