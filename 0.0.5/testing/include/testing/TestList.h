// $Id$
#ifndef TESTING_TESTLIST_H
#define TESTING_TESTLIST_H

namespace testing {

class Test;

class TestList
{
public:
    TestList();
    void Add(Test* test);

    Test* GetHead() const;

private:
    Test* m_head;
    Test* m_tail;
};

class ListAdder
{
public:
    ListAdder(TestList& list, Test* test);
};

}//namespace testing
#endif
