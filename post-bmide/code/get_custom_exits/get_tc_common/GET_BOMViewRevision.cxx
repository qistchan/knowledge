
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_BOMViewRevision.cxx
 //
 //    Purpose:   Class for dealing with GET_BOMViewRevision objects
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     12 Apr, 2016         Initial creation
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_BOMViewRevision.hxx>
#include <GET_Item.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Utils.hxx>

// TC Includes
#include <fclasses/tc_basic.h>
#include <ps/ps.h>
#include <tc/emh.h>
#include <tccore/aom.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/item.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_BOMViewRevision";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_BOMViewRevision ( const GET_DUMMY, const tag_t )
    //
    //   Purpose :   Constructor for the class GET_BOMViewRevision
    //
    //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
    //               tTag - The Tag of this Teamcenter BOMView Object
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
    GET_BOMViewRevision::GET_BOMViewRevision ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {}
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_BOMViewRevision()
    //
    //    Purpose:   Destructor for the class GET_BOMViewRevision
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
    GET_BOMViewRevision::~GET_BOMViewRevision() {}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance (tTag)
    //
    //    Purpose:   Method to get the instance of this class using tag_t
    //
    //    Inputs:    tTag - tag of the BVR
    //
    //    Outputs:   none
    //
    //    Return:    The GET_BOMViewRevision Smart Pointer object is returned
    //
    //     History:
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_BOMViewRevisionUnqPtr GET_BOMViewRevision::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_BOMViewRevision::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, PSBOMVIEWREVISION_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + PSBOMVIEWREVISION_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::getInstance(tTag)" );

        return make_unique<GET_BOMViewRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance (sUID)
    //
    //   Purpose :   Method to get the instance of this class using string UID
    //
    //   Inputs  :   sUID - UID as string
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_BOMViewRevision Smart Pointer object is returned
    //
    //   History:
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_BOMViewRevisionUnqPtr GET_BOMViewRevision::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_BOMViewRevision::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::getInstance(sUID)" );

        return GET_BOMViewRevision::getInstance ( tObjectTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:  createBomViewRevision()
    //
    //   Purpose :  create BOMView Revision with the given inputs
    //
    //   Inputs  :  parentRevisionPtr - The Item Revision Parent
    //              sViewType - view type string
    //              bPrecise  - boolean value for precise
    //              sBvr_name - bom view revision name
    //              sBvr_desc - bom view revision description
    //
    //   Outputs :  none
    //
    //   Return  :  GET_BOMViewRevisionUnqPtr - GET_BOMViewRevision Smart Pointer Object
    //
    //   History :
    //     Who                   Date                 Description
    //   TCS Development Team     24 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_BOMViewRevisionUnqPtr GET_BOMViewRevision::createBOMViewRevision ( const GET_ItemRevisionShrPtr parentRevisionPtr, const string &sViewType, const bool &bPrecise, const string &sBvrName, const string &sBvrDesc )
    {
        GET_BOMViewRevisionUnqPtr bvrPtr;
        GET_BOMViewUnqPtr bomViewPtr;
        GET_ItemUnqPtr itemPtr;

        ResultCheck stat;

        tag_t tViewTypeTag = NULLTAG;
        tag_t tBvrTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::createBOMViewRevision" );

        itemPtr = parentRevisionPtr->getItem();
        bomViewPtr = itemPtr->getBomView ( sViewType );
        if ( bomViewPtr.get() == NULL )
        {
        	GET_ItemShrPtr itemShrPtr ( move ( itemPtr ) );
            // No BomView of this type under Item. create it ...
            bomViewPtr = GET_BOMView::createBOMView ( itemShrPtr, sViewType );
        }

        stat = PS_create_bvr ( bomViewPtr->getTag(), sBvrName.c_str(), sBvrDesc.c_str(), ( bPrecise == true ? TRUE : FALSE ), parentRevisionPtr->getTag(), &tBvrTag );

        bvrPtr = make_unique<GET_BOMViewRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tBvrTag );
        bvrPtr->saveInstance();
        parentRevisionPtr->saveInstance();

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::createBOMViewRevision" );

        return bvrPtr;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getBomView ()
    //
    //   Purpose :   Method to get the instance of GET_BOMView using GET_BOMViewRevision
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_BOMView Smart Pointer object is returned
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_BOMViewUnqPtr GET_BOMViewRevision::getBomView()
    {
        ResultCheck stat;

        tag_t tBOMViewTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::getBomView");

        stat = PS_ask_bom_view_of_bvr ( _tag, &tBOMViewTag );

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::getBomView");

        return make_unique<GET_BOMView> ( GET_DUMMY::GET_DUMMY_VALUE, tBOMViewTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getOccurrences()
    //
    //   Purpose :   Method to get the instance of GET_PSOccurrence from the BVR
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   vector of GET_PSOccurrence is returned(vector<GET_PSOccurrence*>)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_PSOccurrenceUnqPtr> GET_BOMViewRevision::getOccurrences()
    {
        int iOccCount = 0;

        ResultCheck stat;

        tag_t *occTags = NULL;

        vector<GET_PSOccurrenceUnqPtr> childOccs;

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::getOccurrence" );

        stat = PS_list_occurrences_of_bvr ( _tag, &iOccCount, &occTags );

        for ( int iIndex = 0; iIndex < iOccCount; iIndex++ )
        {
            childOccs.push_back ( make_unique<GET_PSOccurrence> ( GET_DUMMY::GET_DUMMY_VALUE, occTags[iIndex] ) );
        }

        // Free the Memory
        MEM_free ( occTags );

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::getOccurrence" );

        return childOccs;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getChildren ( vector<GET_WorkspaceObjectShrPtr>, const int )
    //
    //   Purpose :   Method to traverse and retrieve the Child Item Revision from all levels
    //
    //   Inputs  :   none
    //
    //   Outputs :   The GET_WorkspaceObject Smart Pointer Instances of the Child Objects at the required levels for BOM View Revision
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_BOMViewRevision::getChildren ( vector<GET_WorkspaceObjectShrPtr> &childObjects, const int &iLevel )
    {
        vector<GET_PSOccurrenceUnqPtr> childOccs = this->getOccurrences();

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::getChildren" );

        // Iterate the Child Item Revision
        for ( size_t iIndex = 0; iIndex < childOccs.size(); iIndex++ )
        {
            tag_t itemRevTag = childOccs[iIndex]->getWsObject()->getTag();

            // Cache the child Item Revsion
            GET_WorkspaceObjectShrPtr wsoShrPtr ( move ( childOccs[iIndex]->getWsObject() ) );
            childObjects.push_back ( wsoShrPtr );

            if ( iLevel == 0 )
            {
                /* Instantiate the GET_ItemRevision Class */
                GET_ItemRevisionUnqPtr itemRev = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, itemRevTag );

               /* Get BVR from ItemRevision */
                GET_BOMViewRevisionUnqPtr bvr = itemRev->getBVR();
                if ( bvr.get() == NULL )
                {
                    continue;
                }

                    /* Recuscively call the getChildren function to get sub level children */
                bvr->getChildren ( childObjects );
            }
        }

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::getChildren" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getViewType()
    //
    //   Purpose :   Method to get bomview type
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   BOMView type of the object (string)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string GET_BOMViewRevision::getViewType()
    {
        return this->getBomView()->getViewType();
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   isPrecise()
    //
    //   Purpose :   Method to know the bom view revision is precise or not
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   returns precise status, true or false(logical)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_BOMViewRevision::isPrecise()
    {
        logical lIsPrecise = FALSE;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::isPrecise" );

        stat = PS_ask_is_bvr_precise ( _tag, &lIsPrecise );

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::isPrecise" );

        return ( lIsPrecise == TRUE ? true : false );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setImprecise()
    //
    //   Purpose :   Method to set the bom view revision ImPrecise status
    //
    //   Inputs  :   bIsSaveRequired - bool to indicate whether save of BVR is required or not (Default is true)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_BOMViewRevision::setImprecise ( const bool &bIsSaveRequired )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::setImprecise");

        stat = PS_set_bvr_imprecise ( TRUE );
        if ( bIsSaveRequired )
        {
            save();
        }

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::setImprecise");
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setPrecise()
    //
    //   Purpose :   Method to set the bom view revision Precise status
    //
    //   Inputs  :   bIsSaveRequired - bool to indicate whether save of BVR is required or not (Default is true)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_BOMViewRevision::setPrecise ( const bool &bIsSaveRequired )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::setPrecise");

        stat = PS_set_bvr_precise ( TRUE );
        if ( bIsSaveRequired )
        {
            save();
        }

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::setPrecise");
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:  createOccurrence(const int, GET_ItemRevisionShrPtr, const bool&)
    //
    //   Purpose :  Method to set the bom view revision precise status
    //
    //   Inputs  :  n_occurrences   - number of occurrences to create(const int)
    //              itemRev         - The GET_ItemRevision Smart Pointer Object for which occurrence is created
    //              bIsSaveRequired - bool flag to indicate whether to save the BVR after occurrence creation (Default is true)
    //
    //   Outputs :  none
    //
    //   Return  :  Created occurrence list of the item revision (vector<GET_PSOccurrence*>)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_PSOccurrenceUnqPtr> GET_BOMViewRevision::createOccurrence ( const int iOccurrences, GET_ItemRevisionShrPtr itemRevPtr, const bool &bIsSaveRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        tag_t *ptOccurrences = NULL;

        vector<GET_PSOccurrenceUnqPtr> vChildOccList;

        LOG_TRACE ( logger, "START : GET_BOMViewRevision::createOccurrence");

        try
        {
            stat = PS_create_occurrences ( _tag, itemRevPtr->getTag(), NULLTAG, iOccurrences, &ptOccurrences );
            if( iOccurrences > 0 )
            {
                for ( int iIndex = 0; iIndex < iOccurrences; iIndex++ )
                {
                    vChildOccList.push_back ( make_unique<GET_PSOccurrence> ( GET_DUMMY::GET_DUMMY_VALUE, ptOccurrences[iIndex] ) );
                }
            }
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail& ex )
        {
            exception = &ex;
        }

        MEM_free ( ptOccurrences );

        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_BOMViewRevision::createOccurrence");

        return vChildOccList;
    }
}
