
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
#include <GET_ItemRevision.hxx>
#include <GET_Participant.hxx>
#include <GET_BOMViewRevision.hxx>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
//#include <GET_Site.hxx>
//#include <GET_POM_object.hxx>

const string logger = "get_tc_common.test.TEST_GET_ItemRevision";
using namespace get;

class ItemRevisionTest: public ::testing::Test {


	virtual void TearDown() {

		}

};

int main(int argc, char **argv) {
	ITK_init_from_cpp(argc, argv);
	ITK_initialize_text_services(0);
	int status = ITK_auto_login();

	::testing::InitGoogleTest(&argc, argv);
	cout << "\ntesting started.....\n";

	int retCode = RUN_ALL_TESTS();

	try
	{
	    cout<<endl<<"Here 1";
	    GET_ItemRevisionUnqPtr itemRev = GET_ItemRevision::find ("ECR-123456", "A");
	    cout<<endl<<"Here 2";
	    map<string, vector<GET_ParticipantShrPtr> > mMap = itemRev->getAllParticipants();
	    cout<<endl<<"Here 3";
	    map<string, vector<GET_ParticipantShrPtr> >::iterator iter;
	    for ( iter = mMap.begin(); iter != mMap.end(); ++iter )
	    {
	        cout<<endl<<"The Key is : "<<iter->first.c_str()<<endl;
	    }
	}
	catch ( const IFail &ex )
	{
        cout<<endl<<"TC Exception !!! "<<ex.getMessage().c_str()<<endl;
	}
	catch ( GET_Exception *ex )
	{
	    cout<<endl<<"GET Exception !!! "<<ex->getErrorMessage().c_str()<<endl;
	}
	catch ( ... )
	{
	    cout<<endl<<"Unexpected Exception ..."<<endl;
	}

	cout << "\ntesting end.....\n";
	ITK_exit_module(TRUE);

	return retCode;
}

/*
 * This Test is used to create test data for running tests
 */
TEST(TestItemRevision, Initialization)
{
	//GET_Item::create("Item","999999", "gtest", "A","for testing" );
	//GET_Item* itemNew = GET_Item::find ("999999");
	//EXPECT_TRUE(NULL!=itemNew);
}

/*
 * This Test used to check operations find, getRevId, getId, getItem of Itemrevision
 */
TEST(TestItemRevision, ItemRevisionTest1)
{
	//GET_ItemRevision* pItemRevision = GET_ItemRevision::find ("999999", "A");
	//EXPECT_TRUE(NULL!=pItemRevision);

	//string revID = pItemRevision->getRevId();
	//EXPECT_STREQ("A",revID.c_str());

	//string itemIDFrmRev = pItemRevision->getId();
	//EXPECT_STREQ("999999",itemIDFrmRev.c_str());

	//GET_Item *testItem = pItemRevision->getItem();
    //EXPECT_TRUE(NULL!=testItem);

    //string itemIDFrmItem = testItem->getId();
    //EXPECT_STREQ(itemIDFrmRev.c_str(),itemIDFrmItem.c_str());
}

/*
 * This Test used to check revise and setRevisionId operation of ItemRevision
 */
TEST(TestItemRevision, ItemRevisionTest2)
{
	//GET_ItemRevision* pItemRevision = GET_ItemRevision::find ("999999", "A");
	//EXPECT_TRUE(NULL!=pItemRevision);

	//GET_ItemRevision *pItemRevObj = pItemRevision->revise("B");
	//EXPECT_TRUE(NULL!=pItemRevObj);

	//string revID = pItemRevObj->getRevId();
	//EXPECT_STREQ("B",revID.c_str());

	//pItemRevObj->setRevisionId("P");

	//string newRevID = pItemRevObj->getRevId();
	//EXPECT_STREQ("P",newRevID.c_str());
}

/*
 * This Test to check createBomViewRevision and getBVR() of ItemRevision
 */
TEST(TestItemRevision, ItemRevisionTest3)
{
	//GET_ItemRevision* pItemRevision = GET_ItemRevision::find ("999999", "A");
	//EXPECT_TRUE(NULL!=pItemRevision);

	//GET_BOMViewRevision *pBomRevObj = pItemRevision->createBomViewRevision("view");
	//EXPECT_TRUE(NULL!=pBomRevObj);

	//GET_BOMViewRevision *pBomRevObj1 = pItemRevision->getBVR();
	//EXPECT_TRUE(NULL!=pBomRevObj1);

	//string viewType = pBomRevObj1->getViewType();
	//EXPECT_STREQ("view",viewType.c_str());

	//string inputViewType = pBomRevObj->getViewType();
	//EXPECT_STREQ(viewType.c_str(), inputViewType.c_str());
}

/*
 * This Test is used to check findByAttributes
 */
TEST(TestItemRevision, ItemRevisionTest4)
{
	//map<string, string> mAttributes;
	//mAttributes ["item_id"] = "999999";

	//vector<GET_ItemRevision*> vFoundItemRevs;

	//vFoundItemRevs = GET_ItemRevision::findByAttributes (mAttributes, "A");
	//EXPECT_FALSE(vFoundItemRevs.empty());

	//GET_ItemRevision* pItemRevision =vFoundItemRevs[0];
	//EXPECT_TRUE(NULL!=pItemRevision);

	//string revID = pItemRevision->getRevId();
	//EXPECT_STREQ("A",revID.c_str());

	//string itemIDFrmRev = pItemRevision->getId();
	//EXPECT_STREQ("999999",itemIDFrmRev.c_str());
}

/*
 * This Test is used to delete test data
 */
TEST(TestItemRevision, finalBlock)
{
	//GET_Item* itemNew = GET_Item::find ("999999");
	//EXPECT_TRUE(NULL!=itemNew);

	//GET_Item::deleteItem(itemNew);

	//GET_Item* itemEx = GET_Item::find ("999999");
	//EXPECT_TRUE(NULL==itemEx);
}
