
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_BOMView.cxx
 //
 //    Purpose:   Class for dealing with GET_BOMView objects
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     25 Mar, 2016         Initial creation
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

#include <GET_BOMView.hxx>
#include <GET_BOMViewRevision.hxx>
#include <GET_Item.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <ps/ps.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_BOMView";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_BOMView
	 //
	 //    Purpose:   Constructor for the class GET_BOMView
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag - The Tag of this Teamcenter BOMView Object
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     02 May, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_BOMView::GET_BOMView ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_BOMView
	 //
	 //    Purpose:   Destructor for the class GET_BOMView
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     02 May, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_BOMView::~GET_BOMView() {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getInstance ( tTag )
	 //
	 //    Purpose:   Method to get the instance of this class using tag_t
	 //
	 //     Inputs:   tTag - tag of the object
	 //
	 //    Outputs:   none
	 //
	 //     Return:   GET_BOMViewUnqPtr - Smart Pointer for GET_BOMView instance is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_BOMViewUnqPtr GET_BOMView::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_BOMView::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, BOMVIEW_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + BOMVIEW_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_BOMView::getInstance(tTag)" );

		return make_unique<GET_BOMView> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getInstance (sUID)
	 //
	 //    Purpose:   Method to get the instance of this class using string UID
	 //
	 //     Inputs:   sUID - UID as string
	 //
	 //    Outputs:   none
	 //
	 //     Return:    GET_BOMViewUnqPtr - GSmart Pointer for GET_BOMView instance is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_BOMViewUnqPtr GET_BOMView::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_BOMView::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );

		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_BOMView::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   createBomView()
     //
     //    Purpose:   Method to create bomview
     //
     //     Inputs:   itemPtr     - The Parent GET_Item Smart Pointer for this BOM View
     //               sViewType   - ViewType of string to be provided
     //               sViewname   - view name
     //               sViewdesc   - view description
     //               bCreateBvrs - true or false to create bomview revisions
     //
     //    Outputs:   none
     //
     //     Return:   The newly created GET_BOMView Smart Pointer object is returned
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     28 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_BOMViewUnqPtr GET_BOMView::createBOMView ( GET_ItemShrPtr itemPtr, const string sViewType, const string &sViewname, const string &sViewdesc, const bool &bCreateBvrs, const bool &bPrecise )
    {
        GET_BOMViewUnqPtr bomViewPtr;

        tag_t tViewTypeTag = NULLTAG;
        tag_t tBomViewTag = NULLTAG;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Item::createBomView" );

        if ( ! sViewType.empty() )
        {
            stat = PS_find_view_type ( sViewType.c_str(), &tViewTypeTag );
            if ( tViewTypeTag == NULLTAG )
            {
                string sMsg = string ( "The give BOM View Type " ) + sViewType + " does not exist in Teamcenter";
                THROW ( sMsg );
            }
        }

        stat = PS_create_bom_view ( tViewTypeTag, sViewname.c_str(), sViewdesc.c_str(), itemPtr->getTag(), &tBomViewTag );
        bomViewPtr = make_unique<GET_BOMView> ( GET_DUMMY::GET_DUMMY_VALUE, tBomViewTag );
        bomViewPtr->save();
        itemPtr->save();

        if ( bCreateBvrs )
        {
            GET_ItemRevisionShrPtr latestRevShrPtr ( move ( itemPtr->getLatestRevision() ) );
            GET_BOMViewRevision::createBOMViewRevision ( latestRevShrPtr, sViewType, bPrecise, sViewname, sViewdesc );
        }

        LOG_TRACE ( logger, "END : GET_Item::createBomView" );

        return bomViewPtr;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getItem()
	 //
	 //    Purpose:   Method to get item from bomview
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   GET_ItemUnqPtr- Smart Pointer for GET_Item object
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     24 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ItemUnqPtr GET_BOMView::getItem()
    {
    	GET_ItemUnqPtr itemPtr;

    	ResultCheck stat;

    	tag_t tItemTag = NULLTAG;

    	LOG_TRACE ( logger, "START : GET_BOMView::getItem" );

    	stat = PS_ask_item_of_bom_view ( this->getTag(), &tItemTag );

    	if ( tItemTag != NULLTAG )
    	{
    	    itemPtr = make_unique<GET_Item> ( GET_DUMMY::GET_DUMMY_VALUE, tItemTag );
    	}

    	LOG_TRACE ( logger, "END : GET_BOMView::getItem" );

    	return itemPtr;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getViewType()
	 //
	 //    Purpose:   Method to get view type
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   string- View Type as string
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     24 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    string GET_BOMView::getViewType()
    {
    	char *pcTypeName = NULL;

    	ResultCheck stat;

    	tag_t tViewType = NULLTAG;

    	LOG_TRACE ( logger, "START : GET_BOMView::getViewType" );

    	stat = PS_ask_bom_view_type ( _tag, &tViewType );
    	stat = PS_ask_view_type_name ( tViewType, &pcTypeName );

    	string sTypeName ( pcTypeName );

    	MEM_free ( pcTypeName );

    	LOG_TRACE ( logger, "END : GET_BOMView::getViewType");

    	return sTypeName;
    }
}
