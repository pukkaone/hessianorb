// $Id$
#ifndef TESTING_TESTMACROS_H
#define TESTING_TESTMACROS_H

#include "testing/Config.h"
#include "testing/ExecuteTest.h"
#include "testing/AssertException.h"
#include "testing/TestDetails.h"
#include "testing/MemoryOutStream.h"

#ifndef TESTING_POSIX
    #define TESTING_THROW_SIGNALS
#else
    #include "testing/Posix/SignalTranslator.h"
#endif

#ifdef TEST
    #error testing framework redefines TEST
#endif

#ifdef TEST_EX
    #error testing framework redefines TEST_EX
#endif

#ifdef TEST_FIXTURE_EX
    #error testing framework redefines TEST_FIXTURE_EX
#endif

#ifdef SUITE
    #error testing framework redefines SUITE
#endif

#define SUITE(Name)                                                         \
    namespace Suite##Name {                                                 \
        namespace testingSuite {                                            \
            inline char const* GetSuiteName ()                              \
            { return #Name; }                                               \
        }                                                                   \
    }                                                                       \
    namespace Suite##Name


#define TEST_EX(Name, List)                                                \
    class Test##Name: public testing::Test                                 \
    {                                                                      \
    public:                                                                \
        Test##Name(): testing::Test(#Name, testingSuite::GetSuiteName(), __FILE__, __LINE__) {}  \
    private:                                                               \
        virtual void RunImpl() const;                                      \
    } test##Name##Instance;                                                \
                                                                           \
    testing::ListAdder adder##Name (List, &test##Name##Instance);          \
                                                                           \
    void Test##Name::RunImpl() const


#define TEST(Name) TEST_EX(Name, testing::Test::GetTestList())


#define TEST_FIXTURE_EX(Fixture, Name, List)                                   \
    class Fixture##Name##Helper: public Fixture                                \
    {                                                                          \
    public:                                                                    \
        explicit Fixture##Name##Helper (testing::TestDetails const& details):  \
            m_details(details) \
        { }                                                                    \
        void RunImpl();                                                        \
        testing::TestDetails const& m_details;                                 \
    private:                                                                   \
        Fixture##Name##Helper(Fixture##Name##Helper const&);                   \
        Fixture##Name##Helper& operator=(Fixture##Name##Helper const&);        \
    };                                                                         \
                                                                               \
    class Test##Fixture##Name: public testing::Test                            \
    {                                                                          \
    public:                                                                    \
        Test##Fixture##Name ():                                                \
            testing::Test(#Name, testingSuite::GetSuiteName(), __FILE__, __LINE__) \
        { } \
    private:                                                                   \
        virtual void RunImpl() const;                                          \
    } test##Fixture##Name##Instance;                                           \
                                                                               \
    testing::ListAdder adder##Fixture##Name(List, &test##Fixture##Name##Instance); \
                                                                               \
    void Test##Fixture##Name::RunImpl() const                                  \
    {                                                                          \
        bool ctorOk = false;                                                   \
        try {                                                                  \
            Fixture##Name##Helper fixtureHelper(m_details);                    \
            ctorOk = true;                                                     \
            testing::ExecuteTest(fixtureHelper, m_details);                    \
        }                                                                      \
        catch (testing::TestFailedException const&) {                          \
        }                                                                      \
        catch (testing::AssertException const& e) {                            \
            testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(m_details.testName, m_details.suiteName, e.Filename(), e.LineNumber()), e.what()); \
        }                                                                      \
        catch (std::exception const& e) {                                      \
            testing::MemoryOutStream stream;                                   \
            stream << "Unhandled exception: " << e.what();                     \
            testing::CurrentTest::Results()->OnTestFailure(m_details, stream.GetText()); \
        }                                                                      \
        catch (...) {                                                          \
            if (ctorOk) {                                                      \
                testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(m_details, __LINE__),  \
                    "Unhandled exception while destroying fixture " #Fixture); \
            } else {                                                           \
                testing::CurrentTest::Results()->OnTestFailure(testing::TestDetails(m_details, __LINE__), \
                    "Unhandled exception while constructing fixture " #Fixture); \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    void Fixture##Name##Helper::RunImpl()

#define TEST_FIXTURE(Fixture, Name) TEST_FIXTURE_EX(Fixture, Name, testing::Test::GetTestList())

#endif
