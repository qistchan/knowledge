
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ReleaseStatus.cxx
//
//    Purpose:  To add release status for the Items in TC
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016         Initial creation
//  TCS Development Team     18 Oct, 2017        Added method setEffectivity()
//
//   ============================================================================
// ENDFILEDOC   ***/

// Teamcenter Includes
#include <tc/tc.h>
#include <tccore/aom_prop.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <epm/epm.h>

// GE Includes
#include <GET_TC_Logger.hxx>
#include <GET_POM_object.hxx>
#include <GET_Exception.hxx>
#include <GET_ReleaseStatus.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>

const string logger = "get.get_tc_common.GET_ReleaseStatus";

namespace get
{
     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   GET_ReleaseStatus()
     //
     //   Purpose :   Constructor for the GET_ReleaseStatus class. Initializes
     //               the class with the given tag value
     //
     //   Inputs  :   tTag - The tag of the Release Status Object (tag_t)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //    Who                   Date                 Description
     //    TCS Dev Team          9 Mar, 2016          Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ReleaseStatus::GET_ReleaseStatus ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag )
    {
        statusName = getPropertyString ( NAME_ATTR );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   ~GET_ReleaseStatus()
     //
     //   Purpose :   Destructor for the GET_ReleaseStatus class.
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //    Who                   Date                 Description
     //    TCS Dev Team          9 Mar, 2016          Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ReleaseStatus::~GET_ReleaseStatus() {};

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getStatusName()
     //
     //   Purpose :   Method to get the Release Status Name of this Teamcenter
     //               Release Status Object
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The Release Status Name of this Object (string)
     //
     //   History :
     //    Who                   Date                 Description
     //    TCS Dev Team          9 Mar, 2016          Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
	string GET_ReleaseStatus::getStatusName()
	{
		return statusName;
	}

	/*STARTFUNCDOC ***
	//
	===========================================================================
    //   Function:   addStatus()
    //
    //   Purpose :   Method to add the Release Status Name of this Teamcenter
    //               Release Status Object
    //
	//   Inputs  :   iCount   - Number of objects to add release status(int)
	//               wso      - Workspace object(GET_WorkspaceObject*)
	//               retainDR - To retain date released(logical)
	//
	//   Outputs :   none
	//
	//   Return  :   none
	//
	//   History :
	//    Who                   Date                 Description
	//    TCS Dev Team          9 Mar, 2016          Initial creation
	//
	===========================================================================
	//ENDFUNCDOC   ***/
	void GET_ReleaseStatus::addStatus ( const vector<GET_WorkspaceObjectShrPtr> vWSO, const bool &bRetainDR )
	{
	    IFail *exception = NULL;

	    ResultCheck stat;

	    tag_t *wsoTags = NULL;

	    LOG_TRACE ( logger, "START : GET_ReleaseStatus::addStatus" );

	    try
	    {
	        vector<GET_POM_objectShrPtr> vPOMObjs ( vWSO.begin(), vWSO.end()  );
	        GET_vectorToArray ( vPOMObjs, &wsoTags );
	        stat = RELSTAT_add_release_status ( _tag, vPOMObjs.size(), wsoTags, ( bRetainDR ? TRUE : FALSE ) );
	    }
	    catch ( IFail &ex )
	    {
	        exception = &ex;
	    }

	    // Free the Memory
	    GET_free ( ( void ** ) wsoTags );

	    if ( exception != NULL )
	    {
	        throw exception;
	    }

	    LOG_TRACE ( logger, "END : GET_ReleaseStatus::addStatus" );
	}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   createStatus()
    //
    //   Purpose :   Method to create the Release Status Instance for this Teamcenter
    //               Release Status Object
    //
    //   Inputs  :   sStatusType - The type of the Release status to be created(string)
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_ReleaseStatus Smart Pointer instance of the newly create Status Object
    //
    //   History :
    //    Who                   Date                 Description
    //    TCS Dev Team          9 Mar, 2016          Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
	GET_ReleaseStatusUnqPtr GET_ReleaseStatus::createStatus ( string sStatusType )
	{
	    ResultCheck stat;

	    tag_t tReleaseTag = NULLTAG;

	    LOG_TRACE ( logger, "START : GET_ReleaseStatus::addStatus" );

	    stat = RELSTAT_create_release_status ( sStatusType.c_str(), &tReleaseTag );

	    LOG_TRACE ( logger, "END : GET_ReleaseStatus::addStatus" );

	    return make_unique<GET_ReleaseStatus> ( GET_DUMMY::GET_DUMMY_VALUE, tReleaseTag );
	}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance (tTag)
    //
    //   Purpose :   Method to get the instance of this class using tag_t
    //
    //   Inputs  :   tTag - tag of the Release Status
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_ReleaseStatus Smart Pointer object is returned
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     4 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
	GET_ReleaseStatusUnqPtr GET_ReleaseStatus::getInstance ( const tag_t tTag )
	{
	    LOG_TRACE ( logger, "START : GET_ReleaseStatus::getInstance(tTag)" );

	    if ( ! isDescendant ( tTag, RELEASESTATUS_CLASS ) )
	    {
	        string sMsg = string ( "The given tag is not an instance of the class " ) + RELEASESTATUS_CLASS;
	        THROW ( sMsg );
	    }

	    LOG_TRACE ( logger, "END : GET_ReleaseStatus::getInstance(tTag)\n" );

	    return make_unique<GET_ReleaseStatus> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
    //   Return  :   The GET_ReleaseStatus Smart Pointer object is returned
    //
    //   History:
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
	GET_ReleaseStatusUnqPtr GET_ReleaseStatus::getInstance ( const string sUID )
	{
	    LOG_TRACE ( logger, "START : GET_ReleaseStatus::getInstance(sUID)" );

	    tag_t tObjectTag = getTagFromUID ( sUID );
	    if ( tObjectTag == NULLTAG )
	    {
	        THROW ( sUID + " is not a valid Teamcenter UID" );
	    }

	    LOG_TRACE ( logger, "END : GET_ReleaseStatus::getInstance(sUID)" );

	    return getInstance ( tObjectTag );
	}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   find (string)
    //
    //   Purpose :   Method to get the instance of this class using tag_t
    //
    //   Inputs  :   string - Release Status name
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_ReleaseStatus Smart Pointer object is returned
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     07 Oct, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_ReleaseStatusUnqPtr GET_ReleaseStatus::find ( const string sRelStatusName )
    {
        ResultCheck stat;

        tag_t tRelStat = NULLTAG;

        LOG_TRACE ( logger, "START : GET_ReleaseStatus::find" );

        stat = EPM_find_status_type ( sRelStatusName.c_str(), &tRelStat );
        if ( tRelStat == NULLTAG )
        {
            string sMsg = string ( "The given release status is not found" );
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_ReleaseStatus::find" );

        return make_unique<GET_ReleaseStatus> ( GET_DUMMY::GET_DUMMY_VALUE, tRelStat );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   setEffectivity()
	 //
	 //   Purpose :   Method to set effectivity on Release Status object
	 //
	 //   Inputs  :   const string
	 //
	 //   Outputs :   None
	 //
	 //   Return  :   None
	 //
	 //   History :
	 //      Who                    Date                 Description
	 //  TCS Development Team     18 Oct, 2017         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
     GET_POM_objectUnqPtr GET_ReleaseStatus::setEffectivity ( const string sRangeDate )
     {
    	GET_POM_objectUnqPtr pomUnqPtr;

    	IFail *exception = NULL;

		ResultCheck stat;

		tag_t tEffectivity = NULLTAG;

		LOG_TRACE ( logger, "START : GET_WorkspaceObject::setEffectivity" );

		try
		{
			 stat = WSOM_eff_create_with_date_text ( _tag, NULLTAG, sRangeDate.c_str(), &tEffectivity );

			 if ( tEffectivity != NULLTAG )
			 {
				pomUnqPtr = GET_POM_object::getInstance ( tEffectivity );
				stat = AOM_save( _tag );
			 }
		 }
		 catch ( IFail &ex )
		 {
			 exception = &ex;
		 }

		 // Throw the exception if any, to the calling function
		 if ( exception != NULL )
		 {
			 throw exception;
		 }

		 return pomUnqPtr;
    }
}
