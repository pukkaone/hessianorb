// $Id$
#include "testing/testing.h"
#include "hessian/HttpConnection.h"
#include "sample/SampleServiceProxy.h"
#include <limits>

#define List std::vector
using namespace sample;

SUITE(SampleServiceProxy) {

const std::string URL("http://localhost:8888/sample/remoting/SampleService");

const hessian::Long USER1_ID = 1;
const std::string USER1_FIRST_NAME("Bruce");
const std::string USER1_LAST_NAME("Banner");
const std::string USER1_POSTAL_CODE("A1A1A1");

const hessian::Long USER2_ID = 2;
const std::string USER2_FIRST_NAME("Johnny");
const std::string USER2_LAST_NAME("Storm");
const std::string USER2_POSTAL_CODE("B2B2B2");

const hessian::Long USER3_ID = 3;
const std::string USER3_FIRST_NAME("Reed");
const std::string USER3_LAST_NAME("Richards");
const std::string USER3_POSTAL_CODE("C3C3C3");

struct Fixture
{
    hessian::HttpConnection connection;
    SampleServiceProxy sampleService;

    Fixture ():
        connection(URL),
        sampleService(connection)
    { }
};

TEST_FIXTURE(Fixture, echoBinary)
{
    hessian::Binary original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    hessian::Binary value = sampleService.echoBinary(original);
    ASSERT(original == value);
}

TEST_FIXTURE(Fixture, echoBoolean)
{
    bool original = false;
    bool value = sampleService.echoBoolean(original);
    ASSERT_EQUAL(original, value);

    original = true;
    value = sampleService.echoBoolean(original);
    ASSERT_EQUAL(original, value);
}

TEST_FIXTURE(Fixture, echoBooleanList)
{
    List<bool> original;
    original.push_back(false);
    original.push_back(true);
    original.push_back(false);
    
    List<bool> value = sampleService.echoBooleanList(original);
    ASSERT(original == value);
}

TEST_FIXTURE(Fixture, echoChar)
{
    std::string value = sampleService.echoChar("Alpha");
    ASSERT_EQUAL("A", value);

    value = sampleService.echoChar("Bravo");
    ASSERT_EQUAL("B", value);
}

TEST_FIXTURE(Fixture, echoCharList)
{
    List<std::string> original;
    original.push_back("A");
    original.push_back("B");
    original.push_back("C");
    
    List<std::string> value = sampleService.echoCharList(original);
    ASSERT(original == value);
}

TEST_FIXTURE(Fixture, echoEnum)
{
    Season origValue = WINTER;
    Season value = sampleService.echoEnum(origValue);
    ASSERT_EQUAL(origValue, value);

    origValue = SPRING;
    value = sampleService.echoEnum(origValue);
    ASSERT_EQUAL(origValue, value);
}

TEST_FIXTURE(Fixture, echoEnumList)
{
    Season origValue = WINTER;

    List<Season> origValues;
    origValues.push_back(origValue);
    
    List<Season> values = sampleService.echoEnumList(origValues);
    ASSERT(origValues == values);
}

TEST_FIXTURE(Fixture, echoInt)
{
    hessian::Int original = 1;
    hessian::Int value = sampleService.echoInt(original);
    ASSERT_EQUAL(original, value);

    original = -1;
    value = sampleService.echoInt(original);
    ASSERT_EQUAL(original, value);

    original = std::numeric_limits<hessian::Int>::min();
    value = sampleService.echoInt(original);
    ASSERT_EQUAL(original, value);

    original = std::numeric_limits<hessian::Int>::max();
    value = sampleService.echoInt(original);
    ASSERT_EQUAL(original, value);
}

TEST_FIXTURE(Fixture, echoIntList)
{
    List<hessian::Int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);
    
    List<hessian::Int> value = sampleService.echoIntList(original);
    ASSERT(original == value);
}

TEST_FIXTURE(Fixture, echoString)
{
    std::string original("Alpha");
    std::string value = sampleService.echoString(original);
    ASSERT_EQUAL(original, value);

    original = "Bravo";
    value = sampleService.echoString(original);
    ASSERT_EQUAL(original, value);
}

TEST_FIXTURE(Fixture, echoStringList)
{
    List<std::string> original;
    original.push_back("Alpha");
    original.push_back("Bravo");
    original.push_back("Charlie");
    
    List<std::string> value = sampleService.echoStringList(original);
    ASSERT(original == value);
}

TEST_FIXTURE(Fixture, echoUser)
{
    User origUser;
    origUser.id = USER1_ID;
    origUser.firstName = USER1_FIRST_NAME;
    origUser.lastName = USER1_LAST_NAME;
    origUser.homeAddress.postalCode = USER1_POSTAL_CODE;
    
    User user = sampleService.echoUser(origUser);
    ASSERT_EQUAL(USER1_ID, user.id);
    ASSERT_EQUAL(USER1_FIRST_NAME, user.firstName);
    ASSERT_EQUAL(USER1_LAST_NAME, user.lastName);
    ASSERT_EQUAL(USER1_POSTAL_CODE, user.homeAddress.postalCode);
}

TEST_FIXTURE(Fixture, echoUserList)
{
    User origUser;
    origUser.id = USER1_ID;
    origUser.firstName = USER1_FIRST_NAME;
    origUser.lastName = USER1_LAST_NAME;
    origUser.homeAddress.postalCode = USER1_POSTAL_CODE;

    List<User> origUsers;
    origUsers.push_back(origUser);
    
    List<User> users = sampleService.echoUserList(origUsers);

    List<User>::iterator pUser = users.begin();
    ASSERT_EQUAL(USER1_ID, pUser->id);
    ASSERT_EQUAL(USER1_FIRST_NAME, pUser->firstName);
    ASSERT_EQUAL(USER1_LAST_NAME, pUser->lastName);
    ASSERT_EQUAL(USER1_POSTAL_CODE, pUser->homeAddress.postalCode);
}

TEST_FIXTURE(Fixture, findUsers)
{
    List<User> users = sampleService.findUsers("", "");
    ASSERT_EQUAL(3, users.size());

    List<User>::iterator pUser = users.begin();
    ASSERT_EQUAL(USER1_ID, pUser->id);
    ASSERT_EQUAL(USER1_FIRST_NAME, pUser->firstName);
    ASSERT_EQUAL(USER1_LAST_NAME, pUser->lastName);
    ASSERT_EQUAL(USER1_POSTAL_CODE, pUser->homeAddress.postalCode);

    ++pUser;
    ASSERT_EQUAL(USER2_ID, pUser->id);
    ASSERT_EQUAL(USER2_FIRST_NAME, pUser->firstName);
    ASSERT_EQUAL(USER2_LAST_NAME, pUser->lastName);
    ASSERT_EQUAL(USER2_POSTAL_CODE, pUser->homeAddress.postalCode);

    ++pUser;
    ASSERT_EQUAL(USER3_ID, pUser->id);
    ASSERT_EQUAL(USER3_FIRST_NAME, pUser->firstName);
    ASSERT_EQUAL(USER3_LAST_NAME, pUser->lastName);
    ASSERT_EQUAL(USER3_POSTAL_CODE, pUser->homeAddress.postalCode);
}

TEST_FIXTURE(Fixture, findUsers1)
{
    List<User> users = sampleService.findUsers("Bruce", "");
    ASSERT_EQUAL(1, users.size());

    List<User>::iterator pUser = users.begin();
    ASSERT_EQUAL(USER1_ID, pUser->id);
    ASSERT_EQUAL(USER1_FIRST_NAME, pUser->firstName);
    ASSERT_EQUAL(USER1_LAST_NAME, pUser->lastName);
    ASSERT_EQUAL(USER1_POSTAL_CODE, pUser->homeAddress.postalCode);
}

TEST_FIXTURE(Fixture, getUser)
{
    User user;
   
    user = sampleService.getUser(1);
    ASSERT_EQUAL(USER1_ID, user.id);
    ASSERT_EQUAL(USER1_FIRST_NAME, user.firstName);
    ASSERT_EQUAL(USER1_LAST_NAME, user.lastName);
    ASSERT_EQUAL(USER1_POSTAL_CODE, user.homeAddress.postalCode);

    user = sampleService.getUser(2);
    ASSERT_EQUAL(USER2_ID, user.id);
    ASSERT_EQUAL(USER2_FIRST_NAME, user.firstName);
    ASSERT_EQUAL(USER2_LAST_NAME, user.lastName);
    ASSERT_EQUAL(USER2_POSTAL_CODE, user.homeAddress.postalCode);

    user = sampleService.getUser(3);
    ASSERT_EQUAL(USER3_ID, user.id);
    ASSERT_EQUAL(USER3_FIRST_NAME, user.firstName);
    ASSERT_EQUAL(USER3_LAST_NAME, user.lastName);
    ASSERT_EQUAL(USER3_POSTAL_CODE, user.homeAddress.postalCode);
}

}//SUITE
