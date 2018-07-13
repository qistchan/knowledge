
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ItemRevision.cxx
//
//    Purpose:   Class for dealing with itemRevision objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     18 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_sysapi.h>
#include <GET_Utils.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Item.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_TC_Attributes.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/item.h>
#include <tccore/tctype.h>
#include <epm/epm_toolkit_tc_utils.h>
#include <ps/ps.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_ItemRevision";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_ItemRevision
	 //
	 //    Purpose:   Constructor for the class GET_ItemRevision
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag    - The Tag of this Teamcenter Item Revision Object
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
    GET_ItemRevision::GET_ItemRevision ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag )
    {
        LOG_TRACE ( logger, "START : GET_ItemRevision::GET_ItemRevision" );

        // Get the Item Id
        sItemID = getPropString ( ITEM_ID_ATTR );

        // Get the Item Revision Id
        sRevID = getPropString ( ITEM_REVISION_ID_ATTR );

        LOG_TRACE ( logger, "END : GET_ItemRevision::GET_ItemRevision" );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_ItemRevision
	 //
	 //    Purpose:   Destructor for the class GET_ItemRevision
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
    GET_ItemRevision::~GET_ItemRevision() {};

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
     //     Return:   The GET_ItemRevision Smart Pointer object is returned
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_ItemRevision::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_ItemRevision::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, ITEMREVISION_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + ITEMREVISION_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_ItemRevision::getInstance(tTag)" );

        return make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance ( sUID )
     //
     //    Purpose:   Method to get the instance of this class using string UID
     //
     //     Inputs:   sUID - UID as string
     //
     //    Outputs:   none
     //
     //     Return:   The GET_ItemRevision Smart Pointer object is returned
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_ItemRevision::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_ItemRevision::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW(sUID + " is not a valid Teamcenter UID");
        }

        LOG_TRACE ( logger, "END : GET_ItemRevision::getInstance(sUID)" );

        return getInstance ( tObjectTag );

    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getItem()
     //
     //    Purpose:   Get item of this item revision
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   The GET_Item Smart Pointer object is returned
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     18 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemUnqPtr GET_ItemRevision::getItem()
    {
        GET_ItemUnqPtr itemPtr;

        ResultCheck stat;

        tag_t tTempTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_ItemRevision::getItem" );

         stat = ITEM_ask_item_of_rev ( _tag, &tTempTag );
         itemPtr = make_unique<GET_Item> ( GET_DUMMY::GET_DUMMY_VALUE, tTempTag );

        LOG_TRACE ( logger, "END : GET_ItemRevision::getItem" );

        return itemPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   find()
     //
     //    Purpose:   Find item revision by itemID and revID
     //
     //     Inputs:   sItemID - Item ID to search for (string)
     //               sRevID  - revID RevisionID to search for
     //
     //    Outputs:   none
     //
     //     Return:   The GET_ItemRevision Smart Pointer object is returned
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     18 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_ItemRevision::find ( const string sItemID, const string sRevID )
    {
        const char *cAttrNames[1] = { ITEM_ID_ATTR };
        const char *cAttrValues[1] = { sItemID.c_str() };

        int iItemRevCnt = 0;

        GET_ItemRevisionUnqPtr itemRevPtr;

        ResultCheck stat;

        tag_t *tItemRevs = NULL;

        LOG_TRACE ( logger,"START : GET_ItemRevision::find" );

        stat = ITEM_find_item_revs_by_key_attributes ( 1, cAttrNames, cAttrValues, sRevID.c_str(), &iItemRevCnt, &tItemRevs );

        if ( iItemRevCnt > 0 )
        {
            LOG_TRACE ( logger, "Item rev with given item id and rev id found\n" );
            itemRevPtr = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tItemRevs[0] );
        }
        else
        {
            LOG_TRACE ( logger, "Item Rev not found" );
        }

        MEM_free ( tItemRevs );

        LOG_TRACE ( logger,"END : GET_ItemRevision::find" );

        return itemRevPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getBVRs()
     //
     //    Purpose:   Get BVRs of this item revision
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   map - BVR Map (Key: View type | Value: GET_BOMViewRevisionUnqPtr object)
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     18 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    map<string, GET_BOMViewRevisionShrPtr> GET_ItemRevision::getBVRs()
    {
        int iCount = 0;

        map<string, GET_BOMViewRevisionShrPtr> mBvrMap;

        ResultCheck stat;

        tag_t *tBVRTags = NULL;

        LOG_TRACE ( logger, "START : GET_ItemRevision::getBVRs" );

        // Get the BVRs for the Item Revision
        stat = ITEM_rev_list_bom_view_revs ( _tag, &iCount, &tBVRTags );
        for ( int iIndex = 0; iIndex < iCount; iIndex++ )
        {
            GET_BOMViewRevisionShrPtr bvrPtr = make_shared<GET_BOMViewRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tBVRTags[iIndex] );

            // Get the BVR type
            string type = bvrPtr->getViewType();
            mBvrMap[type] = bvrPtr;
        }

        MEM_free ( tBVRTags );

        LOG_TRACE ( logger, "END : GET_ItemRevision::getBVRs" );

        return mBvrMap;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getParticipants()
     //
     //    Purpose:   Get the Assigned Participants for this Item Revision given the Participant Names
     //
     //     Inputs:   vParticipantNames - A vector of Participant Names whose assigned Participants are required
     //
     //    Outputs:   none
     //
     //     Return:   A Map with the Key as Participant Name and the GET_Participant Smart Pointer instance as value
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     09 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    map<string, vector<GET_ParticipantShrPtr> > GET_ItemRevision::getParticipants ( const vector<string> vParticipantNames )
    {
        GET_Exception *exception = NULL;

        map<string, vector<GET_ParticipantShrPtr> > mParticipantsMap;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_ItemRevision::getParticipants" );

        for ( size_t iIndex = 0; iIndex < vParticipantNames.size(); iIndex++ )
        {
            int iParticipantCount = 0;

            tag_t tParticipantTypeTag = NULLTAG;

            tag_t *ptParticipantsList = NULL;

            try
            {
                // Get the Participant Type
                stat = EPM_get_participanttype ( ( char * ) vParticipantNames[iIndex].c_str(), &tParticipantTypeTag );
                if ( tParticipantTypeTag == NULLTAG )
                {
                    THROW ( vParticipantNames[iIndex] + " is not a valid Teamcenter Participant Type" );
                }

                // Get the Participant List from the Item Revision
                stat = ITEM_rev_ask_participants ( _tag, tParticipantTypeTag, &iParticipantCount, &ptParticipantsList );
                if ( iParticipantCount > 0 )
                {
                    vector<GET_ParticipantShrPtr> vParticipantsVector;

                    for ( int iParticipantIndex = 0; iParticipantIndex < iParticipantCount; iParticipantIndex++ )
                    {
                        vParticipantsVector.push_back ( make_shared<GET_Participant> ( GET_DUMMY::GET_DUMMY_VALUE, ptParticipantsList[iParticipantIndex] ) );
                    }

                    // Store the vector of Participant as a value in a map with the Participant Type Name as the key
                    mParticipantsMap[vParticipantNames[iIndex]] = vParticipantsVector;
                }
            }
            catch ( GET_Exception *ex )
            {
                exception = ex;
            }

            // Free the Memory
            MEM_free ( ptParticipantsList );

            // Throw any exceptions caught to the calling method
            if ( exception != NULL )
            {
                throw exception;
            }
        }

        LOG_TRACE ( logger, "END : GET_ItemRevision::getParticipants" );

        return mParticipantsMap;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getAllParticipants()
     //
     //    Purpose:   Get the Assigned Participants for this Item Revision given the Participant Names
     //
     //     Inputs:   vParticipantNames - A vector of Participant Names whose assigned Participants are required
     //
     //    Outputs:   none
     //
     //     Return:   A Map with the Key as Participant Name and a vector of GET_Participant Smart Pointer instances as value
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     09 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    map<string, vector<GET_ParticipantShrPtr> > GET_ItemRevision::getAllParticipants()
    {
        map<string, vector<GET_ParticipantShrPtr> > mParticipantsMap;

        ResultCheck stat;

        vector<GET_POM_objectUnqPtr> vObjects;

        LOG_TRACE ( logger, "START : GET_ItemRevision::getAllParticipants" );

        vObjects = getPropTags ( PARTICIPANTS_ATTR );
        for ( size_t iIndex = 0; iIndex < vObjects.size(); iIndex++ )
        {
            GET_ParticipantShrPtr participantPtr = make_shared<GET_Participant> ( GET_DUMMY::GET_DUMMY_VALUE, vObjects[iIndex]->getTag() );
            string sParticipantType = participantPtr->getParticipantType();
            if ( mParticipantsMap.find ( sParticipantType ) == mParticipantsMap.end() )
            {
                vector<GET_ParticipantShrPtr> vParticipantsVector;

                mParticipantsMap[sParticipantType] = vParticipantsVector;
            }
            mParticipantsMap[sParticipantType].push_back ( participantPtr );
        }

        LOG_TRACE ( logger, "END : GET_ItemRevision::getAllParticipants" );

        return mParticipantsMap;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getBVR()
     //
     //    Purpose:   Get the given BVR of this item revision
     //
     //     Inputs:   sViewType- string View type for which the BVR to be returned (by default the value is "view")
     //
     //    Outputs:   none
     //
     //     Return:   GET_BOMViewRevision Smart Pointer object is returned.
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     18 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_BOMViewRevisionUnqPtr GET_ItemRevision::getBVR ( const string &sViewType )
    {
        map<string, GET_BOMViewRevisionShrPtr> mBvrMap;

        GET_BOMViewRevisionUnqPtr bvrPtr;

        LOG_TRACE ( logger, "START : GET_ItemRevision::getBVR" );

        // Get the BVRs created for the Item Revision
        mBvrMap = this->getBVRs();

        if ( mBvrMap.find ( sViewType ) != mBvrMap.end() )
        {
            bvrPtr = make_unique<GET_BOMViewRevision> ( GET_DUMMY::GET_DUMMY_VALUE, mBvrMap[sViewType]->getTag() );
        }

        LOG_TRACE ( logger, "START : GET_ItemRevision::getBVR" );

        return bvrPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getRevId()
     //
     //    Purpose:   Method to get the Item Revision ID of this ItemRevision
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   The Revision ID of this Item Revision (string)
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     18 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_ItemRevision::getRevId()
    {
        return sRevID;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getId()
     //
     //    Purpose:   Method to get the Item ID
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   The Item ID of this Item Revision (string)
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     18 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_ItemRevision::getId()
    {
        return sItemID;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   findByAttributes()
     //
     //    Purpose:   Find item revisions by given name and value pair of attributes
     //
     //     Inputs:   mAttributes   - map of name and value pair of attributes
     //               mRevId - Revision ID
     //
     //    Outputs:   none
     //
     //     Return:   Vector - vector of GET_ItemRevision Smart Pointer objects
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     21 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    vector<GET_ItemRevisionUnqPtr> GET_ItemRevision::findByAttributes ( const map<string, string> mAttributes, const string sRevID )
    {
        IFail *exception = NULL;

        int iNumAttributes = mAttributes.size();
        int iRevCount = 0;

        char **ppcAttributeNames = NULL;
        char **ppcAttributeValues = NULL;

        ResultCheck stat;

        vector<GET_ItemRevisionUnqPtr> vFoundItemRevs;
        vector<string> vAttKeys;
        vector<string> vAttValues;

        tag_t *tRevTags = NULL;

        LOG_TRACE ( logger, "START : GET_ItemRevision::findByAttributes" );

        try
        {
            map<string, string>::const_iterator itr;
            for ( itr = mAttributes.begin(); itr != mAttributes.end(); ++itr )
            {
                vAttKeys.push_back ( itr->first );
                vAttValues.push_back ( itr->second );
            }

            GET_vectorToArray ( vAttKeys, &ppcAttributeNames );
            GET_vectorToArray ( vAttValues, &ppcAttributeValues );

            stat = ITEM_find_item_revs_by_key_attributes ( iNumAttributes, ( const char** ) ppcAttributeNames, ( const char** ) ppcAttributeValues, sRevID.c_str(), &iRevCount, &tRevTags );
            for ( int iIndex = 0; iIndex < iRevCount; iIndex++ )
            {
                vFoundItemRevs.push_back ( make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tRevTags[iIndex] ) );
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        MEM_free ( tRevTags );
        GET_free_array ( vAttKeys.size(), ( void** ) ppcAttributeNames );
        GET_free_array ( vAttValues.size(), ( void** ) ppcAttributeValues );

        LOG_TRACE ( logger, "END : GET_ItemRevision::findByAttributes" );

        // Throw the exceptions caught, if any to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        return vFoundItemRevs;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:  setRevisionID()
     //
     //    Purpose:  Sets the Revision id for this ItemRevision
     //
     //     Inputs:  sNewId  - Revision ID to be set (string)
     //
     //    Outputs:  none
     //
     //     Return:  none
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     21 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_ItemRevision::setRevisionId ( const string sNewRevID )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_ItemRevision::setRevisionId" );

        stat = ITEM_set_rev_id ( _tag, sNewRevID.c_str() );
        save();
        sRevID = sNewRevID;

        LOG_TRACE ( logger, "END : GET_ItemRevision::setRevisionId" );

    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   revise()
     //
     //    Purpose:   revises item revision
     //
     //     Inputs:   sRevID - The new Revision ID to be set for the revise operation
     //
     //    Outputs:   none
     //
     //     Return:   GET_ItemrevisionUnqPtr - The new Item Revision Smart Pointer Object from the revise operation
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     22 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_ItemRevision::revise ( const string &sRevID )
    {
        GET_ItemRevisionUnqPtr itemRevPtr;

        ResultCheck stat;

        tag_t tNewRev = NULLTAG;

        LOG_TRACE ( logger, "START : GET_ItemRevision::revise" );

        stat = ITEM_copy_rev ( _tag, sRevID.c_str(), &tNewRev );
        itemRevPtr = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tNewRev );

        LOG_TRACE ( logger, "END : GET_ItemRevision::revise" );

        return itemRevPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   baseline()
     //
     //    Purpose:   Creates a baseline for this Item Revision
     //
     //     Inputs:   sBaselineRevId - The new Baseline Revision ID to be set. Optional,  if not provided will be auto-generated by the system (string)
     //               sBaselineDesc - The Description to be set for the Baseline Revision (string)
     //               sBaselineTemplateName - The Workflow Template to be used for the Baseline process (string)
     //               sJobName - The Baseline Job Name. If empty string is provided, the code will generate a Job name (string)
     //               sJobDesc - The Baseline Job Description (string)
     //
     //    Outputs:   none
     //
     //     Return:   GET_ItemrevisionUnqPtr - The new Baseline Item Revision Smart Pointer Object from the Baseline operation
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     08 Jul, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ItemRevisionUnqPtr GET_ItemRevision::baseline ( const string sBaselineRevId, const string sBaselineDesc, const string sBaselineTemplateName,
                                                        const string sJobName, const string sJobDesc )
    {
        GET_ItemRevisionUnqPtr itemRevPtr;

        int iDeepCopiedObjects = 0;

        ResultCheck stat;

        string sJobTempName = sJobName;

        tag_t tBaselineRev = NULLTAG;

        tag_t *ptDeepCopiedObjects = NULL;

        LOG_TRACE ( logger, "START : GET_ItemRevision::baseline" );

        // Construct the Job Name if its empty
        if ( sJobTempName.empty() )
        {
            sJobTempName = "Baseline_" + sItemID + "_" + sRevID + "." + sBaselineRevId;
        }

        // Create the Baseline revision for the current Item Revision instance
        stat = ITEM_baseline_rev ( _tag, sBaselineRevId.c_str(), sBaselineDesc.c_str(), sBaselineTemplateName.c_str(),
                                   sJobTempName.c_str(), sJobDesc.c_str(), &tBaselineRev, &iDeepCopiedObjects, &ptDeepCopiedObjects );

        // Free the Memory
        MEM_free ( ptDeepCopiedObjects );

        // Construct a Smart Pointer for the new Baseline Item Revision
        itemRevPtr = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tBaselineRev );

        LOG_TRACE ( logger, "END : GET_ItemRevision::baseline" );

        return itemRevPtr;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getBaseRev ()
	 //
	 //    Purpose:   Method to get the Base rev of given baselined revision
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_ItemRevision Smart Pointer of base rev is returned if instance is baselined rev else, NULLTAG is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     30 Sep, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ItemRevisionUnqPtr GET_ItemRevision::getBaseRev()
	{
		 GET_ItemRevisionUnqPtr itemRevPtr;

		 ResultCheck stat;

		 tag_t tBaseRevTag = NULLTAG;

		 LOG_TRACE ( logger, "START : GET_ItemRevision::getBaseRev" );

		 stat = ITEM_rev_find_base_rev ( _tag, &tBaseRevTag );

		 if ( tBaseRevTag != NULLTAG )
		 {
			 itemRevPtr = make_unique<GET_ItemRevision> ( GET_DUMMY::GET_DUMMY_VALUE, tBaseRevTag );
		 }

		 LOG_TRACE ( logger, "END : GET_ItemRevision::getBaseRev" );

		 return itemRevPtr;
	}
}
