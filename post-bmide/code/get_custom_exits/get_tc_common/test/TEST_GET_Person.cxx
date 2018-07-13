/**
 * @file  TEST_GET_Person.cxx
 * @brief Unit test framework for item class
 */

#if _MSC_VER == 1700
#define _VARIADIC_MAX 10
#endif

#include <stdlib.h>
#include <iostream>

#include <gtest/gtest.h>

#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <tccore/item.h>


#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

#include <GET_Item.hxx>
#include <GET_POM_user.hxx>


const string logger = "get_tc_common.test.TEST_GET_Person";
using namespace get;
using namespace std;



class TEST_GET_Person: public ::testing::Test {


	virtual void TearDown() {

		}
};

int main(int argc, char **argv) {
	ITK_init_from_cpp(argc, argv);
	ITK_initialize_text_services(0);
	int retCode = ITK_auto_login();

	::testing::InitGoogleTest(&argc, argv);
	cout << "\ntesting started.....\n";

	retCode = RUN_ALL_TESTS();

	cout << "\ntesting end.....\n";
	ITK_exit_module( TRUE );

	return retCode;
}

/*
 * This Test is used to create test data for running tests
 */
TEST(TestGET_Person, Initialization)
{
	/*GET_Item::create("Item","999999", "gtest", "A","for testing" );
	GET_Item* itemNew = GET_Item::find ("999999");
	EXPECT_TRUE(NULL!=itemNew);
	GET_POM_user* pUser = itemNew->getOwningUser();*/
}

/*
 * This Test used to check all the operations of GET_Person
 */
TEST(TestGET_Person, GET_PersonTest1)
{
	/*GET_Item* itemNew = NULL;
	itemNew = GET_Item::find ("999999");
	EXPECT_TRUE(NULL!=itemNew);

	GET_POM_user* pUser = NULL;
	pUser = itemNew->getOwningUser();
	EXPECT_TRUE(NULL!=pUser);

	GET_POM_user* pLoggedInUser = NULL;
	pLoggedInUser = GET_POM_user::getCurrentLoggedInUser();
	EXPECT_TRUE(NULL!=pLoggedInUser);

	string sName ="";
	sName = pUser->getName();
	EXPECT_FALSE(sName.empty());

	string sLoggedInUserName = "";
	sLoggedInUserName = pLoggedInUser->getName();
	EXPECT_FALSE(sLoggedInUserName.empty());

	EXPECT_STREQ(sName.c_str(), sLoggedInUserName.c_str() );

	GET_Person *person = NULL;
	person = pUser->getPerson();
	EXPECT_TRUE(NULL!=person);

	GET_Person *loggedInPerson = NULL;
	loggedInPerson = pLoggedInUser->getPerson();
	EXPECT_TRUE(NULL!=loggedInPerson);

	string personName = "";
	personName = person->getName();
	EXPECT_FALSE(personName.empty());

	string loggedInPersonName = "";
	loggedInPersonName = loggedInPerson->getName();
	EXPECT_FALSE(loggedInPersonName.empty());

	EXPECT_STREQ(personName.c_str(), loggedInPersonName.c_str() );

	string loggedInPersonEmail = "";
	loggedInPersonEmail = loggedInPerson->getEmailId();
	EXPECT_TRUE(loggedInPersonEmail.empty());

	string personEmail = "";
	personEmail = person->getEmailId();
	EXPECT_TRUE(personEmail.empty());

	EXPECT_STREQ(personEmail.c_str(), loggedInPersonEmail.c_str() );*/

}

/*
 * This Test is used to delete test data
 */
TEST(TestGET_POM_user, finalBlock)
{
	/*GET_Item* itemNew = GET_Item::find ("999999");
	EXPECT_TRUE(NULL!=itemNew);

	GET_Item::deleteItem(itemNew);

	GET_Item* itemEx = GET_Item::find ("999999");
	EXPECT_TRUE(NULL==itemEx);*/
}



