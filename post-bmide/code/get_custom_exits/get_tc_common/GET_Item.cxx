
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Item.cxx
//
//    Purpose:   Class to dealing with item objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     9 Mar, 2016         Initial creation
//  TCS Development Team     9 May, 2018         Added getLatestReleasedRevision
//  TCS Development Team    20 Jun, 2018         Added method to get naming pattern
//  TCS Development Team     9 Jul, 2018         Added Memory free and removed unwanted lines in getLatestReleasedRevision()
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Item.hxx>
#include <GET_ItemRevision.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tccore/item.h>
#include <tccore/aom.h>
#include <tccore/tctype.h>
#include <ps/ps.h>
#include <base_utils/ResultCheck.hxx>

const string logger = "get.get_tc_common.GET_Item";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_Item ( const GET_DUMMY, const tag_t )
    //
    //   Purpose :   Constructor for the class GET_Item
    //
    //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
    //               tTag    - The Tag of this Teamcenter Item Object
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_Item::GET_Item ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag )
    {
        LOG_TRACE ( logger, "START : GET_Item::GET_Item" );

        sItemID = getPropString ( ITEM_ID_ATTR );

        LOG_TRACE ( logger, "END : GET_Item::GET_Item" );
    };

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_Item()
    //
    //   Purpose :   Destructor for the class GET_Item
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_Item::~GET_Item() {};

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance ( tTag )
     //
     //   Purpose :   Method to get the instance of this class using tag_t
     //
     //   Inputs  :   tTag - tag of the object
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_Item Smart Pointer object is returned(GET_ItemUnqPtr)
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemUnqPtr GET_Item::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_Item::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, ITEM_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + ITEM_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_Item::getInstance(tTag)\n" );

        return make_unique<GET_Item> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance ( sUID )
     //
     //   Purpose :   Method to get the instance of this class using string UID
     //
     //   Inputs  :   sUID - UID as string
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_Item Smart Pointer object is returned(GET_ItemUnqPtr)
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemUnqPtr GET_Item::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_Item::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_Item::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getRevisions()
     //
     //   Purpose :   Method to get all revisions for this item
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   Vector of ItemRevisions associated with item (vector<GET_ItemRevisionUnqPtr>)
     //
     //   History :
     //    Who                   Date                 Description
     //    TCS Dev Team          9 Mar, 2016          Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    vector<GET_ItemRevisionUnqPtr> GET_Item::getRevisions() const
    {
        int iRevCount = 0;

        ResultCheck stat;

        tag_t *ptRevList  = NULL;

        vector<GET_ItemRevisionUnqPtr> vItemRevisions;

        LOG_TRACE ( logger, "START : GET_Item::getRevisions" );

        stat = ITEM_list_all_revs ( _tag, &iRevCount, &ptRevList );
        for ( int iIndex = 0; iIndex < iRevCount; iIndex++ )
        {
            vItemRevisions.push_back ( make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, ptRevList[iIndex] ) );
        }
        MEM_free ( ptRevList );

        LOG_TRACE ( logger, "END : GET_Item::getRevisions" );

        return vItemRevisions;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   find()
     //
     //   Purpose :   Method to find an item which matches the given item id
     //
     //   Inputs  :   sItemID - Item ID to find (string)
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_Item Smart Pointer Object matching the given Item ID(GET_ItemUnqPtr)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     9 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemUnqPtr GET_Item::find ( const string sItemID )
    {
        GET_ItemUnqPtr itemPtr;

        int iCount = 0;

        ResultCheck stat;

        tag_t *ptItemTags = NULLTAG;

        LOG_TRACE ( logger, "START : GET_Item::find" );

        stat = ITEM_find ( sItemID.c_str(), &iCount, &ptItemTags );
        if ( iCount > 0 )
        {
            itemPtr = make_unique<GET_Item> ( GET_DUMMY::GET_DUMMY_VALUE, ptItemTags[0] );
        }
        MEM_free ( ptItemTags );

        LOG_TRACE ( logger, "END : GET_Item::getRevisions" );

        return itemPtr;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getId()
     //
     //   Purpose :   Method to get an itemID
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The Item id of this Item(string)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     23 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/

    string GET_Item::getId()
    {
        return sItemID;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   findRevision()
     //
     //   Purpose :   Method to find item revision within this item
     //
     //   Inputs  :   sRevID - Revision ID to be found within this Item (string)
     //
     //   Outputs :   none
     //
     //   Return  :   The Item Revision Smart Pointer Object for the given revision id(GET_ItemRevisionUnqPtr)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     23 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_Item::findRevision ( const string sRevID )
    {
        int iTagCount = 0;

        GET_ItemRevisionUnqPtr itemRevPtr;

        ResultCheck stat;

        tag_t *tTagList = NULL;

        LOG_TRACE ( logger, "START : GET_Item::findRevision" );

        stat = ITEM_find_revisions ( _tag, sRevID.c_str(), &iTagCount, &tTagList );
        if ( iTagCount > 0 )
        {
            itemRevPtr = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tTagList[0] );
        }
        MEM_free ( tTagList );

        LOG_TRACE ( logger, "END : GET_Item::findRevision" );

        return itemRevPtr;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   findRevisions()
     //
     //   Purpose :   Method to find item revisions matching the given revision id within this item
     //
     //   Inputs  :   sRevID - Revision ID to be matched within this Item (string)
     //
     //   Outputs :   none
     //
     //   Return  :   The Item Revision Smart Pointer instances for the matching Revision ids(vector<GET_ItemRevisonUnqPtr>)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     9 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     vector<GET_ItemRevisionUnqPtr> GET_Item::findRevisions ( const string sRevID )
     {
        int itagCount = 0;

        vector<GET_ItemRevisionUnqPtr> vItemRevs;

        ResultCheck stat;

        tag_t *tagList = NULL;

        LOG_TRACE ( logger, "START : GET_Item::findRevisions" );

        stat = ITEM_find_revisions ( _tag, sRevID.c_str(), &itagCount, &tagList );
        for ( int iCount = 0; iCount < itagCount; iCount++ )
        {
            vItemRevs.push_back ( make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tagList[iCount] ) );
        }
         MEM_free ( tagList );

         LOG_TRACE ( logger, "END : GET_Item::findRevisions" );

         return vItemRevs;
     }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getLatestRevision()
     //
     //   Purpose :   Method to get Latest Revision
     //
     //   Inputs  :   none
     //
     //   Outputs :   revTag - Revision tag found for the item (tag_t)
     //
     //   Return  :   The GET_Item smart pointer is returned(GET_ItemRevisionUnqPtr)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     9 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_Item::getLatestRevision() const
    {
        GET_ItemRevisionUnqPtr itemRevPtr;

        ResultCheck stat;

        tag_t latestRevTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_Item::getLatestRevision" );

        stat = ITEM_ask_latest_rev ( _tag, &latestRevTag );
        itemRevPtr = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, latestRevTag );

        LOG_TRACE ( logger, "END : GET_Item::getLatestRevision" );

        return itemRevPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getLatestReleasedRevision()
     //
     //   Purpose :   Method to get Latest Released Revision
     //
     //   Inputs  :   none
     //
     //   Outputs :   revTag - Revision tag found for the item (tag_t)
     //
     //   Return  :   The GET_ItemRevision smart pointer is returned(GET_ItemRevisionUnqPtr)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     9 May, 2018         Initial creation
     //  TCS Development Team     9 Jul, 2018         Added Memory free and removed unwanted lines
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_Item::getLatestReleasedRevision() const
    {
        GET_ItemRevisionUnqPtr itemRelRevPtr;

        int iRevCount   = 0;
        int n_statuses = 0;

		ResultCheck stat;

        tag_t *revTags = 0;
        tag_t *statuses = NULL;

        LOG_TRACE ( logger, "START : GET_Item::getLatestReleasedRevision" );

        stat = ITEM_list_all_revs ( _tag, &iRevCount, &revTags );
        LOG_TRACE ( logger, "Total number of Revision is--> " + iRevCount );

        for ( int inx=iRevCount; inx>0; inx-- )
        {
        	stat = AOM_ask_value_tags ( revTags[inx-1], RELEASE_STATUS_LIST_ATTR, &n_statuses, &statuses );
        	MEM_free ( statuses );
        	LOG_TRACE ( logger, "n_statuses is--> " + n_statuses );

        	if ( n_statuses == 0 )
        	{
        		// Working revision found, go to previous revision
        		LOG_TRACE ( logger, "Working revision found, go to previous revision" );
        		continue;
        	}

        	// Latest Released Revision found, break the loop
        	itemRelRevPtr = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, revTags[inx-1] );
        	break;
        }

    	MEM_free ( revTags );

        LOG_TRACE ( logger, "END : GET_Item::getLatestReleasedRevision" );

        return itemRelRevPtr;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:  getBomViews()
     //
     //   Purpose :  Method to get bomviews attached to this Item
     //
     //   Inputs  :  none
     //
     //   Outputs :  none
     //
     //   Return  :  map with View Name and GET_BOMView Smart Pointer Objects (map<string, GET_BomBViewUnqPtr)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     28 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    map<string, GET_BOMViewShrPtr> GET_Item::getBomViews()
    {
        int iCount = 0;

        map<string, GET_BOMViewShrPtr> mBvMap;

        ResultCheck stat;

        string sType = NULL;

        tag_t *tBVTags = NULLTAG;

        LOG_TRACE ( logger, "START : GET_Item::getBomViews" );

        stat = ITEM_list_bom_views ( _tag, &iCount, &tBVTags );
        for ( int iIndex = 0; iIndex < iCount; iIndex++ )
        {
            GET_BOMViewShrPtr bomViewPtr = make_shared<GET_BOMView> ( GET_DUMMY::GET_DUMMY_VALUE, tBVTags[iIndex] );

            sType = bomViewPtr->getViewType();
            mBvMap[sType] = bomViewPtr;
        }
        MEM_free ( tBVTags );

        LOG_TRACE ( logger, "END : GET_Item::getBomViews" );

        return mBvMap;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getBomView()
     //
     //   Purpose :   Method to get a given bom view from this Item
     //
     //   Inputs  :   sViewType - The View Type of the BOM View to be retrieved
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_BOMView Smart Pointer object is returned(GET_BOMViewUnqPtr)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     28 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_BOMViewUnqPtr GET_Item::getBomView ( const string sViewType )
    {
        map<string, GET_BOMViewShrPtr> mViewMap = this->getBomViews();

        GET_BOMViewUnqPtr bomViewPtr;

        LOG_TRACE ( logger, "START : GET_Item::getBomView" );

        if ( mViewMap.find ( sViewType ) != mViewMap.end() )
        {
            bomViewPtr = make_unique<GET_BOMView> ( GET_DUMMY::GET_DUMMY_VALUE, mViewMap[sViewType]->getTag() );
        }

        LOG_TRACE ( logger, "END : GET_Item::getBomView" );

        return bomViewPtr;
    }


    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getNRPatternNextValue()
    //
    //   Purpose :   Method to get naming pattern
    //
    //   Inputs  :   sViewType - The View Type of the BOM View to be retrieved
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_BOMView Smart Pointer object is returned(GET_BOMViewUnqPtr)
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     20 Jun, 2018         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string GET_Item::getNRPatternNextValue ( const string sTypeName, const string sPropName, tag_t tItemTag, const string sDatasetID, const string sPrefTypeName, const string sDefaultTypeName, tag_t tParentItemTag, const string sRuleSuffix, const string sBaseRevId, const string sPattern )
    {
    	ResultCheck stat;

    	char* pcItemId = NULL;

    	string sItemId = "";

    	LOG_TRACE ( logger, "START : GET_Item::getNRPatternNextValue" );

    	stat = NR_pattern_next_value ( sTypeName.c_str(), sPropName.c_str(), tItemTag, sDatasetID.c_str(), sPrefTypeName.c_str(), sDefaultTypeName.c_str(), tParentItemTag, sRuleSuffix.c_str(), sBaseRevId.c_str(), sPattern.c_str(), &pcItemId );
    	if ( pcItemId != NULL )
    	{
    		sItemId = pcItemId;
    	}
    	LOG_TRACE ( logger, "START : GET_Item::getNRPatternNextValue" );

    	return sItemId;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   create()
     //
     //   Purpose :   Method to create Item
     //
     //   Inputs  :   sItemType        - Item type for which item to be created(const string)
     //               sItemID          - Item ID(const string)
     //               sItemName        - Name of the item(const string)
     //               sRevID           - Revision ID of the item(const string)
     //               sItemDescription - Description of the item(const string)
     //
     //   Outputs :   none
     //
     //   Return  :   GET_Item - Item instance created (GET_ItemUnqPtr)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     14 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemUnqPtr GET_Item::create ( const string sItemType, const string sItemID, const string sItemName, const string sRevID, const string sItemDescription )
    {
        ResultCheck stat;

        string sItemRevisionType = sItemType + "Revision";

        tag_t tItemTag = NULLTAG;
        tag_t tItemBOtag = NULLTAG;
        tag_t tIRcreateInputTag = NULLTAG;
        tag_t tItemCreateInputTag =NULLTAG;
        tag_t tItemRevTag = NULLTAG;

        GET_ItemUnqPtr itemPtr;

        LOG_TRACE ( logger, "START : GET_Item::create" );

        stat = TCTYPE_find_type ( sItemRevisionType.c_str(), NULL, &tItemRevTag );
        if ( tItemRevTag == NULLTAG )
        {
            string sMsg = string ( "Given Type " ) + sItemRevisionType + " does not exist";
            THROW ( sMsg );
        }

        stat = TCTYPE_construct_create_input ( tItemRevTag, &tIRcreateInputTag );
        stat = AOM_set_value_string ( tIRcreateInputTag, ITEM_REVISION_ID_ATTR, sRevID.c_str() );
        stat = AOM_set_value_string ( tIRcreateInputTag, OBJECT_DESC_ATTR, sItemDescription.c_str() );

        stat = TCTYPE_find_type ( sItemType.c_str(), NULL, &tItemTag );
        if ( tItemTag == NULLTAG )
        {
            string sMsg = string ( "Given Type " ) + sItemType + " does not exist";
            THROW ( sMsg );
        }

        stat = TCTYPE_construct_create_input ( tItemTag, &tItemCreateInputTag );
        stat = AOM_set_value_string ( tItemCreateInputTag, ITEM_ID_ATTR, sItemID.c_str() );
        stat = AOM_set_value_string ( tItemCreateInputTag, OBJECT_NAME_ATTR, sItemName.c_str() );
        stat = AOM_set_value_string ( tItemCreateInputTag, OBJECT_DESC_ATTR, sItemDescription.c_str() );
        stat = AOM_set_value_tag ( tItemCreateInputTag, ITEM_REVISION_ATTR, tIRcreateInputTag );
        stat = TCTYPE_create_object ( tItemCreateInputTag, &tItemBOtag );
        itemPtr = make_unique<GET_Item> ( GET_DUMMY::GET_DUMMY_VALUE, tItemBOtag );
        itemPtr->save();

        LOG_TRACE ( logger, "END : GET_Item::create" );

        return itemPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getNewRevId()
     //
     //   Purpose :   Method to generate new revision id for the given item of given type
     //
     //   Inputs  :   tItemTag - The View Type of the BOM View to be retrieved
     //               tItemType - Tag of item type
     //
     //   Outputs :   none
     //
     //   Return  :   string - new revision id
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     03 Oct, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_Item::getNewRevId ( const tag_t tItemTag, const tag_t tItemType )
    {
        char *pId = NULL;

        logical mod;

        ResultCheck stat;

        string newRevId = "";

        LOG_TRACE ( logger, "START : GET_Item::getNewRevId" );

        stat = ITEM_new_revision_id ( tItemTag, tItemType, &mod, &pId );

        if ( pId != NULL )
        {
            newRevId = pId;
        }

        LOG_TRACE ( logger, "END : GET_Item::getNewRevId" );

        return newRevId;
    }
}
