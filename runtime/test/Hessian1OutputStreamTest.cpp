// $Id$
#include "testing/testing.h"
#include "hessian/Hessian1OutputStream.h"

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
    ASSERT_EQUAL(
            std::string("I\x00\x00\x00\x01", 5),
            output.rdbuf()->str());
}

TEST_FIXTURE(Fixture, writeLong)
{
    Long value = 1LL;
    output << value;
    ASSERT_EQUAL(
            std::string("L\x00\x00\x00\x00\x00\x00\x00\x01", 9),
            output.rdbuf()->str());
}

}//SUITE
