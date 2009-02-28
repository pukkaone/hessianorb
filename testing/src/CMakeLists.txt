# $Id$

if(WIN32)
    set(TESTING_PLATFORM_SOURCES
            Win32/TimeHelpers.cpp
    )
else(WIN32)
    set(TESTING_PLATFORM_SOURCES
            Posix/SignalTranslator.cpp
            Posix/TimeHelpers.cpp
    )
endif(WIN32)

add_library(testing
        AssertException.cpp
        CurrentTest.cpp
        DeferredTestReporter.cpp
        DeferredTestResult.cpp
        MemoryOutStream.cpp
        Test.cpp
        TestDetails.cpp
        TestList.cpp
        TestReporter.cpp
        TestReporterStdout.cpp
        TestResults.cpp
        TestRunner.cpp
        TimeConstraint.cpp
        XmlTestReporter.cpp
        ${TESTING_PLATFORM_SOURCES}       
)
