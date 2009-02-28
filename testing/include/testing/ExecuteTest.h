// $Id$
#ifndef TESTING_EXECUTE_TEST_H
#define TESTING_EXECUTE_TEST_H

#include "testing/TestDetails.h"
#include "testing/MemoryOutStream.h"
#include "testing/TestFailedException.h"
#include "testing/AssertException.h"
#include "testing/CurrentTest.h"

#ifdef TESTING_POSIX
    #include "Posix/SignalTranslator.h"
#endif

namespace testing {

template<typename T>
void ExecuteTest(T& testObject, TestDetails const& details)
{
    CurrentTest::Details() = &details;

    try {
#ifdef TESTING_POSIX
        TESTING_THROW_SIGNALS
#endif
        testObject.RunImpl();
    }
    catch (TestFailedException const&) {
        // do nothing
    }
    catch (AssertException const& e) {
        CurrentTest::Results()->OnTestFailure(
            TestDetails(details.testName, details.suiteName, e.Filename(), e.LineNumber()), e.what());
    }
    catch (std::exception const& e) {
        MemoryOutStream stream;
        stream << "Unhandled exception: " << e.what();
        CurrentTest::Results()->OnTestFailure(details, stream.GetText());
    }
    catch (...) {
        CurrentTest::Results()->OnTestFailure(details, "Unhandled exception: Crash!");
    }
}

}//namespace testing
#endif
