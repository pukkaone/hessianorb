// $Id$
#include "testing/testing.h"
#include "hessian/Hessian1OutputStream.h"
#include <algorithm>

using namespace hessian;

SUITE(Hessian1OutputStream) {

struct Fixture
{
    Hessian1OutputStream output;
};

TEST_FIXTURE(Fixture, writeInt)
{
    Int value = 1;
    output << value;

    const char EXPECTED[] = "I\x00\x00\x00\x01";
    ASSERT_EQUAL(sizeof(EXPECTED) - 1, output.rdbuf()->pcount());
    ASSERT(std::equal(
            EXPECTED,
            EXPECTED + sizeof(EXPECTED) -1,
            output.rdbuf()->str()));
}

TEST_FIXTURE(Fixture, writeLong)
{
    Long value = 1LL;
    output << value;

    const char EXPECTED[] = "L\x00\x00\x00\x00\x00\x00\x00\x01";
    ASSERT_EQUAL(sizeof(EXPECTED) - 1, output.rdbuf()->pcount());
    ASSERT(std::equal(
            EXPECTED,
            EXPECTED + sizeof(EXPECTED) -1,
            output.rdbuf()->str()));
}

}//SUITE
