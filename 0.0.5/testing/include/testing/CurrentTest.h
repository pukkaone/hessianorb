// $Id$
#ifndef TESTING_CURRENTTEST_H
#define TESTING_CURRENTTEST_H

namespace testing {

class TestResults;
class TestDetails;

namespace CurrentTest
{
	TestResults*& Results();
	const TestDetails*& Details();
}

}//namespace testing
#endif
