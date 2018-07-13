/**
 * @file  TEST_GET_Item.cxx
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
#include <GET_Role.hxx>


const string logger = "get_tc_common.test.TEST_GET_Role";
using namespace get;
using namespace std;



class TEST_GET_Role: public ::testing::Test {


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
	ITK_exit_module(TRUE);

	return retCode;
}


/*
 * This Test used to check all the operations of GET_Role
 */
TEST(TestGET_Role, GET_RoleTest1)
{
	/*const string sDBARole = "DBA";
	const string sDBADesc = "Database Administrator.";
	const string sCurrentLoggedInRole = "Designer";

	GET_Role *pRole = GET_Role::find(sDBARole);
	EXPECT_TRUE(NULL!=pRole);

	string sRoleName = "";
	sRoleName = pRole->getRoleName();
	EXPECT_FALSE(sRoleName.empty());

	EXPECT_STREQ(sRoleName.c_str(), sDBARole.c_str());

	string sRoleDesc = "";
	sRoleDesc = pRole->getRoleDescription();
	EXPECT_FALSE(sRoleDesc.empty());

	EXPECT_STREQ(sRoleDesc.c_str(), sDBADesc.c_str());

	GET_Role *pLoggedInUserRole = GET_Role::getCurrentLoggedInUserRole();
	EXPECT_TRUE(NULL!=pLoggedInUserRole);

	string sLoggedInUserRoleName = "";
	sLoggedInUserRoleName = pLoggedInUserRole->getRoleName();
	EXPECT_FALSE(sLoggedInUserRoleName.empty());

	EXPECT_STREQ(sLoggedInUserRoleName.c_str(), sCurrentLoggedInRole.c_str());

	vector<GET_Role*> vAllRoles =  GET_Role::extent();
	EXPECT_FALSE(vAllRoles.empty());*/

}




