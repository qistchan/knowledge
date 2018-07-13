
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


#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

#include <GET_Item.hxx>
//#include <GET_Site.hxx>
//#include <GET_POM_object.hxx>


const string logger = "get_tc_common.test.TEST_GET_Item";
using namespace get;

class ItemTest: public ::testing::Test {


	virtual void TearDown() {

		}
		//
	    // GET_Item item;
};

int main(int argc, char **argv) {
	ITK_init_from_cpp(argc, argv);
	ITK_initialize_text_services(0);
	int retCode = ITK_auto_login();

	::testing::InitGoogleTest(&argc, argv);
	cout << "testing started.....";

	retCode = RUN_ALL_TESTS();

	cout << "testing end.....";
	ITK_exit_module(TRUE);

	return retCode;
}


TEST(ItemTest, NoIteminTC)
{
	//ItemPtr foundItem = Item::find("00000");
	//GET_Item* item = GET_Item::find ("054390");

	//GET_Item* item = NULL;
	//EXPECT_TRUE(NULL==item);
	//EXPECT_EQ(NULL,item);
}

TEST(ItemTest, IteminTC)
{
    //create one item in your TC with the id given below
	//GET_Item* item = GET_Item::find ("000035");

	//GET_Item* item = NULL;
	//EXPECT_TRUE(NULL!=item);
	//EXPECT_EQ(NULL,item);
}


int add(int a, int b)
{
	return(a+b);
}

TEST(add, postive)
{
	EXPECT_EQ(9,add(8,1));
}
