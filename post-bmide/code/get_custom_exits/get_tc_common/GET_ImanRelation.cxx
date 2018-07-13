
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_ImanRelation.cxx
 //
 //    Purpose:   GET_ImanRelation class deals with ImanRelation relation between primary and secondary object.
 //               It performs some of the operations like creation, fetching of ImanRelation and fetching of secondary objects for ImanRelation
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     21 Mar, 2016         Initial creation
 //  TechM Development Team   20 May, 2017         Added findRelation function
 //   ============================================================================
 // ENDFILEDOC   ***/

#include <time.h>

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_ImanRelation.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tccore/grm.h>
#include <tccore/grm.h>
#include <sa/am.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_ImanRelation";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_ImanRelation
	 //
	 //    Purpose:   Constructor for the class GET_ImanRelation
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag    - The Tag of this Teamcenter ImanRelation Object
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
    GET_ImanRelation::GET_ImanRelation ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag ) {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_ImanRelation
	 //
	 //    Purpose:   Destructor for the class GET_ImanRelation
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
    GET_ImanRelation::~GET_ImanRelation() {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getInstance (tTag)
	 //
	 //    Purpose:   Method to get the instance of this class using tag_t
	 //
	 //     Inputs:   tTag - tag of the object
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_ImanRelation Smart Pointer object is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ImanRelationUnqPtr GET_ImanRelation::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_ImanRelation::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, IMANRELATION_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + IMANRELATION_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_ImanRelation::getInstance(tTag)" );

		return make_unique<GET_ImanRelation> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //     Return:   The GET_ImanRelation Smart Pointer object is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ImanRelationUnqPtr GET_ImanRelation::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_ImanRelation::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );

		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_ImanRelation::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   create()
	 //
	 //    Purpose:   Method to create Iman relation between given primary and secondary objects
	 //
	 //     Inputs:   primaryPtr    - Smart Pointer for Primary Object
	 //               secondaryPtr  - Smart Pointer for Secondary Object
	 //               sRelationType - Relation Name
	 //               userDataPtr   - Smart Pointer for userData
	 //
	 //    Outputs:   none
	 //
     //     Return:   The newly created GET_ImanRelation Smart Pointer object is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     25 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ImanRelationUnqPtr GET_ImanRelation::create ( const GET_POM_objectShrPtr primaryPtr, const GET_POM_objectShrPtr secondaryPtr,
                                                      const string sRelationType, const GET_POM_objectShrPtr userDataPtr )
    {
        GET_ImanRelationUnqPtr relationPtr;

    	ResultCheck stat;

    	tag_t tRelationTag = NULLTAG;
    	tag_t tRelationTypeTag = NULLTAG;
    	tag_t tDataTag = NULLTAG;

    	LOG_TRACE ( logger, "START : GET_ImanRelation::create" );

    	if ( primaryPtr.get() == NULL ||  secondaryPtr.get() == NULL ||  sRelationType.empty() )
		{
			THROW ( "The given inputs are not valid" );
		}

    	tDataTag = ( userDataPtr.get() != NULL ) ? userDataPtr->getTag() : NULLTAG;

    	tRelationTypeTag = getRelationType ( sRelationType );
    	if ( tRelationTypeTag == NULLTAG )
    	{
            THROW ( sRelationType + " is not a valid Teamcenter relation" );
    	}

    	stat = GRM_find_relation ( primaryPtr->getTag(), secondaryPtr->getTag(), tRelationTypeTag, &tRelationTag );
    	if ( tRelationTag != NULLTAG )
    	{
    		THROW ( sRelationType + " already exists between given primary and secondary objects" );
    	}

        stat = GRM_create_relation ( primaryPtr->getTag(), secondaryPtr->getTag(), tRelationTypeTag, tDataTag, &tRelationTag );

        relationPtr = make_unique<GET_ImanRelation> ( GET_DUMMY::GET_DUMMY_VALUE, tRelationTag );
        relationPtr->saveRelation();

    	LOG_TRACE ( logger, "END : GET_ImanRelation::create" );

        return relationPtr;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getRelationType()
	 //
	 //    Purpose:   Method to get the tag of the given relation type
	 //
	 //     Inputs:   sRelationType - The string Relation Name whose tag is required
	 //
	 //    Outputs:   none
	 //
	 //     Return:   Returns the tag of relation (tag_t)
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     25 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    tag_t GET_ImanRelation::getRelationType ( const string sRelationType )
    {
    	// Initialize
    	ResultCheck stat;

    	tag_t tRelationTypeTag = NULLTAG;

    	LOG_TRACE ( logger, "START : GET_ImanRelation::getRelationType" );

    	// Get tag of relation type
    	stat = GRM_find_relation_type ( sRelationType.c_str(), &tRelationTypeTag );

    	if ( tRelationTypeTag == NULLTAG )
    	{
    		string sMsg = sRelationType + " is not found";
    		LOG_TRACE ( logger, sMsg );
    	}

		LOG_TRACE ( logger, "END : GET_ImanRelation::getRelationType" );

        return tRelationTypeTag;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getPrimary()
	 //
	 //    Purpose:   Method to get the primary object for this relation object
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_POM_object Smart Pointer for the primary object
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     25 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_POM_objectUnqPtr GET_ImanRelation::getPrimary()
    {
    	ResultCheck stat;

    	tag_t tPrimaryTag = NULLTAG;

    	LOG_TRACE ( logger, "START : GET_ImanRelation::getPrimary" );

    	stat = GRM_ask_primary ( _tag, &tPrimaryTag );

    	LOG_TRACE ( logger, "END : GET_ImanRelation::getPrimary" );

    	return make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tPrimaryTag );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getSecondary()
	 //
     //    Purpose:   Method to get the secondary object for this relation object
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
     //     Return:   The GET_POM_object Smart Pointer for the secondary object
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     25 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_POM_objectUnqPtr GET_ImanRelation::getSecondary()
    {
    	ResultCheck stat;

    	tag_t tSecondaryTag = NULLTAG;

    	LOG_TRACE ( logger, "START : GET_ImanRelation::getSecondary" );

    	stat = GRM_ask_secondary ( _tag, &tSecondaryTag );

    	LOG_TRACE ( logger, "END : GET_ImanRelation::getSecondary" );

    	return make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tSecondaryTag );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   listRelatedObjects()
	 //
	 //    Purpose:   Method to get the all the primary/secondary objects for the provided object and relation.
	 //
	 //     Inputs:   objectPtr - The GET_POM_object Smart Pointer for the Object whose primaries/secondaries are required
	 //               sRelTypeStr - The Relation Name - Optional - need not be provided in which case all relations are returned
     //               bIsPrimaryRequired - Boolean to indicate whether primary (true) or secondary (false) objects are required
     //
	 //    Outputs:   none
	 //
	 //     Return:   A vector with the GET_POM_object Smart Pointer for the related primary Objects
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     25 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    vector<GET_POM_objectUnqPtr> GET_ImanRelation::listRelatedObjects ( const GET_POM_objectShrPtr objectPtr, const string &sRelTypeStr, const bool &bIsPrimaryRequired )
    {
        IFail *exception = NULL;

    	int iRelations = 0;

    	tag_t *ptRelationObjTags = NULL;

    	ResultCheck stat;

    	tag_t tRelationTypeTag = NULLTAG;

    	vector<GET_POM_objectUnqPtr> vOutput;

    	LOG_TRACE ( logger, "START : GET_ImanRelation::listRelatedObjects" );

        if ( ! sRelTypeStr.empty() )
        {
            tRelationTypeTag = GET_ImanRelation::getRelationType ( sRelTypeStr );
            if ( tRelationTypeTag == NULLTAG )
            {
                THROW ( sRelTypeStr + " is not a valid Teamcenter relation" );
            }
        }

        try
        {
            if ( bIsPrimaryRequired )
            {
                stat = GRM_list_primary_objects_only ( objectPtr->getTag(), tRelationTypeTag, &iRelations, &ptRelationObjTags );
            }
            else
            {
                stat = GRM_list_secondary_objects_only ( objectPtr->getTag(), tRelationTypeTag, &iRelations, &ptRelationObjTags );
            }
            for ( int iIndex = 0; iIndex < iRelations; iIndex++ )
            {
                vOutput.push_back ( make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, ptRelationObjTags[iIndex] ) );
            }
    	}
    	catch ( IFail &ex )
    	{
    	    exception = &ex;
    	}

    	// Free the Memory
    	if ( ptRelationObjTags )
    	{
    		MEM_free ( ptRelationObjTags );
    		ptRelationObjTags = NULL;
    	}

    	if ( exception != NULL )
    	{
    	    throw exception;
    	}

    	LOG_TRACE ( logger, "END : GET_ImanRelation::listRelatedObjects" );

    	return vOutput;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   listRelatedWsObjects()
	 //
	 //    Purpose:   Method to get the related WorkspaceObject primaries/secondaries for the given input object
	 //
	 //     Inputs:   secondaryPtr - The input GET_POM_object Smart Pointer Object whose primary/secondary WorkspaceObjects are required
     //               sRelTypeStr - The Relation Name - Optional - need not be provided in which case all relations are returned
	 //               sObjectType - The type of the related WorkspaceObject - Optional - need not be provided in which case all related Workspace Objects are returned
     //               bIsPrimaryRequired - Boolean to indicate whether primary (true) or secondary (false) objects are required
	 //
	 //    Outputs:   none
	 //
     //     Return:   A vector with the GET_WorkspaceObject Smart Pointer for the related primary/secondary Objects
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     25 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    vector<GET_WorkspaceObjectUnqPtr> GET_ImanRelation::listRelatedWsObjects ( const GET_POM_objectShrPtr secondaryPtr, const string &sRelTypeStr, const string& sObjectType, const bool &bIsPrimaryRequired  )
    {
    	vector<GET_WorkspaceObjectUnqPtr> vRelatedWsObjetcs;
    	vector<GET_POM_objectUnqPtr> vPOMObjects;

    	LOG_TRACE ( logger, "START : GET_ImanRelation::listRelatedWsObjects" );

    	vPOMObjects = listRelatedObjects ( secondaryPtr, sRelTypeStr, bIsPrimaryRequired );

    	for ( size_t iIndex = 0; iIndex < vPOMObjects.size(); iIndex++ )
    	{
    	    GET_WorkspaceObjectUnqPtr workspaceObjPtr;

    		// Make sure is a WsObject
    	    GET_POM_objectShrPtr pomObjSharedPtr ( move ( vPOMObjects[iIndex] ) );
    		if ( ! GET_WorkspaceObject::isWsObject ( pomObjSharedPtr ) )
    		{
    			continue;
    		}

    		workspaceObjPtr = make_unique<GET_WorkspaceObject> ( GET_DUMMY::GET_DUMMY_VALUE, pomObjSharedPtr->getTag() );
    		if ( ( ! sObjectType.empty() && workspaceObjPtr->getType().compare ( sObjectType ) == 0 ) || sObjectType.empty() )
    		{
    		    vRelatedWsObjetcs.push_back ( move ( workspaceObjPtr ) );
    		}
    	}

    	LOG_TRACE ( logger, "END : GET_ImanRelation::listRelatedWsObjects" );

    	return vRelatedWsObjetcs;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   saveRelation()
     //
     //    Purpose:   Method to save relation.
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_ImanRelation::saveRelation()
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_ImanRelation::deleteRelation" );

        stat = GRM_save_relation ( _tag );

        LOG_TRACE ( logger, "END : GET_ImanRelation::deleteRelation" );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   deleteRelation()
	 //
	 //    Purpose:   Method to delete relation.
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     25 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    void GET_ImanRelation::deleteRelation()
    {
	    ResultCheck stat;

	    LOG_TRACE ( logger, "START : GET_ImanRelation::deleteRelation" );

	    stat = GRM_delete_relation ( _tag );

	    LOG_TRACE ( logger, "END : GET_ImanRelation::deleteRelation" );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   findRelation()
	 //
	 //    Purpose:   Method to find Iman relation between given primary and secondary objects
	 //
	 //     Inputs:   primaryPtr    - Smart Pointer for Primary Object
	 //               secondaryPtr  - Smart Pointer for Secondary Object
	 //               sRelationType - Relation Name
	 //
	 //    Outputs:   None
	 //
	 //    Return:    GET_ImanRelation Smart Pointer object is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TechM Development Team     20 May, 2017        Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ImanRelationUnqPtr GET_ImanRelation::findRelation ( const GET_POM_objectShrPtr primaryPtr, const GET_POM_objectShrPtr secondaryPtr,
                                                      const string sRelationType )
    {
        GET_ImanRelationUnqPtr relationPtr;

    	ResultCheck stat;

    	tag_t tRelationTag = NULLTAG;
    	tag_t tRelationTypeTag = NULLTAG;


    	LOG_TRACE ( logger, "START : GET_ImanRelation::findRelation" );

    	if ( primaryPtr.get() == NULL ||  secondaryPtr.get() == NULL ||  sRelationType.empty() )
		{
			THROW ( "The given inputs are not valid" );
		}


    	tRelationTypeTag = getRelationType ( sRelationType );
    	if ( tRelationTypeTag == NULLTAG )
    	{
            THROW ( sRelationType + " is not a valid Teamcenter relation" );
    	}

    	stat = GRM_find_relation ( primaryPtr->getTag(), secondaryPtr->getTag(), tRelationTypeTag, &tRelationTag );
    	if ( tRelationTag != NULLTAG )
    	{
    		relationPtr = make_unique<GET_ImanRelation> ( GET_DUMMY::GET_DUMMY_VALUE, tRelationTag );
    	}

    	LOG_TRACE ( logger, "END : GET_ImanRelation::findRelation" );

        return relationPtr;
    }

}
