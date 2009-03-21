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
            EXPECTED + sizeof(EXPECTED) - 1,
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
            EXPECTED + sizeof(EXPECTED) - 1,
            output.rdbuf()->str()));
}

TEST_FIXTURE(Fixture, writeString)
{
    std::string value(
            "A"
            "\xD0\x80"
            "\xE8\x80\x80"
            "\xF4\x80\x80\x80"
            "B",
            11);
    output << value;

    const char EXPECTED[] =
            "S\x00\x05"
            "A"
            "\xD0\x80"
            "\xE8\x80\x80"
            "\xF4\x80\x80\x80"
            "B";
    ASSERT_EQUAL(sizeof(EXPECTED) - 1, output.rdbuf()->pcount());
    ASSERT(std::equal(
            EXPECTED,
            EXPECTED + sizeof(EXPECTED) - 1,
            output.rdbuf()->str()));
}

TEST_FIXTURE(Fixture, writeStringHuge)
{
    std::string value(65536, 'X');
    output << value;

    std::string expected =
            "s\xFF\xFF" +
            std::string(65535, 'X') +
            std::string("S\x00\x01X", 4);
    ASSERT_EQUAL(expected.size(), output.rdbuf()->pcount());
    ASSERT(std::equal(
            expected.begin(),
            expected.end(),
            output.rdbuf()->str()));
}

}//SUITE
