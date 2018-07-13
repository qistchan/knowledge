
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_EPMTask.cxx
//
//    Purpose:   Class for dealing with Teamcenter EPM Task objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Jul, 2016         Initial creation
//  TCS Development Team     19 May, 2017         Added definition of getRootTask(), getDecision(), askReviewers() methods.
//  TechM Development Team   20 May, 2017         Added askEPMJob function
//  Ganesh Ubale             12 Sep, 2017         Modified function askReviewers() and  getDecision() to correct the validation for perform signoff task identification
//  TCS Development Team     11 Oct, 2017         Added getTaskResult function
//  TCS Development Team     17 Oct, 2017         Added getDecision function
//  TCS Development Team     04 Jun, 2018         Added askEPMResponsibleParty function
//
//   ============================================================================
// ENDFILEDOC   ***/

// Teamcenter Includes
#include <epm/epm.h>
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/aom.h>
#include <epm/signoff.h>
#include <mld/journal/journal.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_EPMTask.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>
#include <GET_EPMJob.hxx>

const string logger = "get.get_tc_common.GET_EPMTask";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_EPMTask ( const GET_DUMMY, const tag_t )
    //
    //   Purpose :   Constructor for the class GET_EPMTask
    //
    //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
    //               tTag    - The Tag of this Teamcenter EPMTask Object
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_EPMTask::GET_EPMTask ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_EPMTask()
    //
    //   Purpose :   Destructor for the class GET_EPMTask
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_EPMTask::~GET_EPMTask() {}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   addAttachments()
    //
    //   Purpose :   Method to add the given attachment to this Task
    //
    //   Inputs  :   iAttachmentType - Integer flag indicating whether the attachment type is target or reference
    //               vAttachObjects - A vector containing the GET_POM_object smart pointer representation of the to be attached tasks
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     11 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_EPMTask::addAttachments ( const int iAttachmentType, const vector<GET_POM_objectShrPtr> vAttachObjects )
    {
        IFail *exception = NULL;

        int *piAttachmentTypes = NULL;

        tag_t *ptAttachmentTags = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_EPMTask::addAttachments" );

        try
        {
            piAttachmentTypes = ( int * ) malloc ( sizeof ( int ) * vAttachObjects.size() );
            for ( int iIndex = 0; iIndex < vAttachObjects.size(); iIndex++ )
            {
                piAttachmentTypes[iIndex] = iAttachmentType;
            }
            // Get the tag array from the input vector
            GET_vectorToArray ( vAttachObjects, &ptAttachmentTags );
            // Add the attachment
            stat = EPM_add_attachments ( _tag, vAttachObjects.size(), ptAttachmentTags, piAttachmentTypes );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free ( ptAttachmentTags );
        GET_free ( piAttachmentTypes );

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_EPMTask::addAttachments" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   removeAttachments()
    //
    //   Purpose :   Method to remove the given attachment from this Task
    //
    //   Inputs  :   vAttachObjects - A vector containing the GET_POM_object smart pointer representation of the to be removed tasks
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     11 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_EPMTask::removeAttachments ( const vector<GET_POM_objectShrPtr> vAttachObjects )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        tag_t *ptAttachmentTags = NULL;

        LOG_TRACE ( logger, "START : GET_EPMTask::removeAttachments" );

        try
        {
            // Get the tag array from the input vector
            GET_vectorToArray ( vAttachObjects, &ptAttachmentTags );
            // Remove the attachment
            stat = EPM_remove_attachments ( _tag, vAttachObjects.size(), ptAttachmentTags );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free ( ptAttachmentTags );

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_EPMTask::removeAttachments" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   askAttachments()
    //
    //   Purpose :   Method to retrieve the attachments of the specified type from this Task
    //
    //   Inputs  :   iAttachmentType - Integer flag indicating whether the attachment type is target or reference
    //
    //   Outputs :   none
    //
    //   Return  :   A vector containing the GET_POM_object smart pointer representation of the Attachment Objects
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     11 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_POM_objectUnqPtr> GET_EPMTask::askAttachments ( const int iAttachmentType )
    {
        int iAttachObjCount = 0;

        ResultCheck stat;

        tag_t *ptAttachmentTags = NULL;

        vector<GET_POM_objectUnqPtr> vAttachObjects;

        LOG_TRACE ( logger, "START : GET_EPMTask::askAttachments" );

        // Retrieve the attachments
        stat = EPM_ask_attachments ( _tag, iAttachmentType, &iAttachObjCount, &ptAttachmentTags );
        // Convert the tag array into a vector
        GET_arrayToVector ( iAttachObjCount, ptAttachmentTags, vAttachObjects );

        // Free the Memory
        MEM_free ( ptAttachmentTags );

        LOG_TRACE ( logger, "END : GET_EPMTask::askAttachments" );

        return vAttachObjects;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setTaskResult()
    //
    //   Purpose :   Method to set the task result
    //
    //   Inputs  :   Task value
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team      03 Mar, 2017         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/

    void GET_EPMTask::setTaskResult ( string sTaskValue )
    {
        int istatus;

        LOG_TRACE ( logger, "START : GET_EPMTask::setTaskResult" );

        // Given condition task name found
        istatus = EPM_set_task_result ( _tag, sTaskValue.c_str() );

        LOG_TRACE ( logger, "END : GET_EPMTask::setTaskResult" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   askReviewers()
    //
    //   Purpose :   Method to get reviewers of perform Signoffs task
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   vector<GET_POM_userUnqPtr> - Returns vector of users appointed as reviewers.
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     19 May, 2017         Initial creation
    //  Ganesh Ubale             06 Sep, 2017         Modified to retrive the perform signoff task type to compare task type
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_POM_userUnqPtr> GET_EPMTask::askReviewers()
    {
        int iUserCount = 0;

        IFail *exception = NULL;

        ResultCheck stat;

        tag_t *tUserTags = NULL;

        vector<GET_POM_userUnqPtr> vPomUserUnqPtr;

        LOG_TRACE ( logger, "START : GET_EPMTask::askReviewers" );
        
        try
        {
	        if ( getType().compare ( PERFORM_SIGNOFF_TASK_TYPE ) == 0 )
	        {
	            stat = EPM_ask_task_reviewers_users ( _tag, &iUserCount, &tUserTags );
	
	            if ( ( iUserCount != 0 ) && ( tUserTags != NULL ) )
	            {
	                for ( int iInx = 0; iInx < iUserCount; iInx++ )
			        {
	        	        vPomUserUnqPtr.push_back ( make_unique<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tUserTags[iInx] ) );
			        }
	            }
	        }
        }
        catch ( IFail &ex )
        {
        	exception = &ex;
        }

        MEM_free ( tUserTags );

        // Throw any exceptions caught to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }
        
        LOG_TRACE ( logger, "END : GET_EPMTask::askReviewers" );
        
        return vPomUserUnqPtr;
    }
    
	/*STARTFUNCDOC ***
	//
	===========================================================================
	//   Function:   getDecision( reviewUserTag )
	//
	//   Purpose :   Method to get decision, comments and decision date of Perform Signoff task after review
	//
	//   Inputs  :   GET_POM_userShrPtr userShrPtr - Reviewer share pointer
	//                
	//   Outputs :   struct reviewTaskResults taskResults - Updates decision, comments and decision date of structure reviewTaskResults.
	//
	//   Return  :   none
	//
	//   History :
	//      Who                   Date                 Description
	//  TCS Development Team     19 May, 2017         Initial creation
	//  Ganesh Ubale             06 Sep, 2017         Corrected the validation for perform signoff task identification 
	//
	===========================================================================
	//ENDFUNCDOC   ***/
    void GET_EPMTask::getDecision ( GET_POM_userShrPtr userShrPtr, ReviewTaskResults &taskResults )
	{
		char *pcComments = NULL;

		date_t decisionDate = NULLDATE;

		EPM_signoff_decision_t decision;

		IFail *exception = NULL;

		ResultCheck stat;

		vector<GET_EPMTaskUnqPtr > vTasksUnqPtr;

		LOG_TRACE ( logger, "START : GET_EPMTask::getDecision" );

        try
        {
			if ( getType().compare ( PERFORM_SIGNOFF_TASK_TYPE ) == 0 )
	        {
			    stat = EPM_ask_decision ( _tag , userShrPtr->getTag(), &decision, &pcComments, &decisionDate );

			    if ( decision == EPM_approve_decision )
	            {
	                taskResults.sDecision = APPROVED_DECISION_ATTR;
	            }
	            else if ( decision == EPM_reject_decision )
	            {
	                taskResults.sDecision = REJECT_DECISION_ATTR;
	            }
	            else
	            {
	            	taskResults.sDecision = NO_DECISION_ATTR;
	            }

			    taskResults.sComments = pcComments;
			    taskResults.decisionDatePtr = GET_Date::getInstance ( decisionDate );
	        }
		}
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        MEM_free ( pcComments );

        // Throw any exceptions caught to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_EPMTask::getDecision" );
	}
	
    /*STARTFUNCDOC ***
	//
	===========================================================================
	//   Function:   getDecision ( string )
	//
	//   Purpose :   Method to get decision of condition task
	//
	//   Inputs  :   none
	//                
	//   Outputs :   string sDecision
	//
	//   Return  :   none
	//
	//   History :
	//      Who                   Date                 Description
	//  TCS Development Team     17 Oct, 2017         Initial creation 
	//
	===========================================================================
	//ENDFUNCDOC   ***/
    void GET_EPMTask::getDecision ( string &sDecision )
	{
    	char *pcResult = NULL;

    	IFail *exception = NULL;

    	ResultCheck stat;

    	LOG_TRACE ( logger, "START : GET_EPMTask::getDecision" );

        try
        {
			if ( getType().compare ( EPM_CONDITION_TASK ) == 0 )
	        {
			    stat = EPM_get_task_result ( _tag, &pcResult );
			}
		}
        catch ( IFail &ex )
        {
            exception = &ex;
        }
        // Throw any exceptions caught to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        if ( pcResult != NULL )
        {
        	sDecision = pcResult;
        	MEM_free ( pcResult );
        }

        LOG_TRACE ( logger, "END : GET_EPMTask::getDecision" );
	}
	
	/*STARTFUNCDOC ***
	//
	===========================================================================
	//   Function:   getRootTask()
	//
	//   Purpose :   Method to get initiator of workflow
	//
	//   Inputs  :   const tag_t tTag - Review User Tag
	//                
	//   Outputs :   none
	//
	//   Return  :   
	//
	//   History :
	//      Who                   Date                 Description
	//  TCS Development Team     19 May, 2017         Initial creation
	//
	===========================================================================
	//ENDFUNCDOC   ***/
	
	GET_EPMTaskUnqPtr GET_EPMTask::getRootTask()
	{
		GET_EPMTaskUnqPtr rootTaskUnqPtr;

		IFail *exception = NULL;

		ResultCheck stat;

		tag_t tTaskTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_EPMTask::getRootTask" );

		try
        {
			stat = EPM_ask_root_task ( _tag, &tTaskTag );
		}
        catch ( IFail &ex )
        {
            exception = &ex;
        }
		
		if ( tTaskTag != NULLTAG )
		{
			rootTaskUnqPtr =  make_unique<GET_EPMTask> ( GET_DUMMY::GET_DUMMY_VALUE, tTaskTag );
		}
		
		LOG_TRACE ( logger, "END : GET_EPMTask::getRootTask" );
		
		return rootTaskUnqPtr;
	}

	/*STARTFUNCDOC ***
	//
	===========================================================================
	//   Function:   getSubTask()
	//
	//   Purpose :   Method to get initiator of workflow
	//
	//   Inputs  :   const tag_t tTag - Root task Tag
	//                
	//   Outputs :   vector of 
	//
	//   Return  :   
	//
	//   History :
	//      Who                   Date                 Description
	//  Ganesh Ubale          12 Sep, 2017            Initial creation
	//
	===========================================================================
	//ENDFUNCDOC   ***/

	vector<GET_EPMTaskUnqPtr> GET_EPMTask::getSubTasks()
	{
		vector<GET_EPMTaskUnqPtr> subTaskUnqPtr;

		IFail *exception = NULL;
		
		int count;

		ResultCheck stat;

		tag_t *tSubTaskTags = NULL;

		LOG_TRACE ( logger, "START : GET_EPMTask::getSubTask" );

		try
		{
			stat = EPM_ask_sub_tasks ( _tag, &count, &tSubTaskTags );
			for ( size_t iIndex = 0; iIndex < count; iIndex++ )
			{
				subTaskUnqPtr.push_back ( make_unique<GET_EPMTask> ( GET_DUMMY::GET_DUMMY_VALUE, tSubTaskTags[iIndex] ) );
			}
		}
		catch ( IFail &ex )
		{
			exception = &ex;
		}

		if ( tSubTaskTags != NULL )
		{
			MEM_free ( tSubTaskTags );
		}
		if ( exception != NULL )
		{
			throw exception;
		}

		LOG_TRACE ( logger, "END : GET_EPMTask::getSubTask" );
		
		return subTaskUnqPtr;
	}
	
	/*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance (tTag)
    //
    //   Purpose :   Method to get the instance of this class using tag_t
    //
    //   Inputs  :   tTag - tag of the EPMTask
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_EPMTask Smart Pointer object is returned
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_EPMTaskUnqPtr GET_EPMTask::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_EPMTask::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, EPMTASK_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + EPMTASK_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_EPMTask::getInstance(tTag)" );

        return make_unique<GET_EPMTask> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
    //   Return  :   The GET_EPMTask Smart Pointer object is returned
    //
    //   History:
    //      Who                    Date                 Description
    //   TCS Development Team     11 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_EPMTaskUnqPtr GET_EPMTask::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_EPMTask::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_EPMTask::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   askEPMJob()
    //
    //   Purpose :   Method to get the EPMJob from EPMTask
    //
    //   Inputs  :   tTag - tag of the EPMTask
    //
    //   Outputs :   tEPMJobTag - tag of EPMJob
    //
    //   Return  :   The GET_EPMJobUnqPtr unique Pointer object is returned
    //
    //   History :
    //      Who                   Date                 Description
    //   TechM Development Team   20 May, 2017        Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    unique_ptr<GET_EPMJob> GET_EPMTask::askEPMJob()
    {
        ResultCheck stat;

        GET_EPMJobUnqPtr epmJobUnqPtr;

        tag_t tEPMJobTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_EPMTask::askEPMJob" );

        // Ask epm job tag
        stat = EPM_ask_job ( _tag, &tEPMJobTag );

        LOG_TRACE ( logger, "END : GET_EPMTask::askEPMJob" );

        //return unique pointer of epm job
        epmJobUnqPtr = make_unique<GET_EPMJob> ( GET_DUMMY::GET_DUMMY_VALUE, tEPMJobTag );

        return epmJobUnqPtr;
    }

    /*STARTFUNCDOC ***
	//
	===========================================================================
	//   Function:   askEPMResponsibleParty()
	//
	//   Purpose :   Method to get the Responsible Party from EPMTask
	//
	//   Inputs  :   tTag - tag of the EPMTask
	//
	//   Outputs :   tEPMJobTag - tag of responsible party
	//
	//   Return  :   The GET_POM_userUnqPtr unique Pointer object is returned
	//
	//   History :
	//      Who                   Date                 Description
	//   TechM Development Team   04 Jun, 2018        Initial creation
	//
	===========================================================================
	//ENDFUNCDOC   ***/
    GET_POM_userUnqPtr GET_EPMTask::askEPMResponsibleParty()
	{
		ResultCheck stat;

		GET_POM_userUnqPtr getUserUnqPtr;

		tag_t tResponsbilePartyTags = NULL;

		LOG_TRACE ( logger, "START : GET_EPMTask::askEPMResponsibleParty" );

		// Ask responsible party tag
		stat = EPM_ask_responsible_party ( _tag, &tResponsbilePartyTags );

		LOG_TRACE ( logger, "END : GET_EPMTask::askEPMResponsibleParty" );

		//return unique pointer of responsbile party
		getUserUnqPtr = make_unique<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tResponsbilePartyTags );

		return getUserUnqPtr;
	}

}
