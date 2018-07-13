
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_EPMJob.hxx
//
//    Purpose:   Class for dealing with Teamcenter EMP Job objects
//
//    History:
//      Who                          Date                 Description
//  TCS Development Team           18 Mar, 2016         Initial creation
//  Capgemini Development Team     29 May, 2017         Added new method definition for createEPMProcess method
//  TCS Development Team           31 May, 2017         Modified the createEPMProcess method and corrected all errors
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_EPMJob.hxx>
#include <GET_TC_Utils.hxx>

// Teamcenter Includes
#include <epm/epm.h>
#include <epm/epm_task_template_itk.h>
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/aom.h>
#include <mld/journal/journal.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_EPMJob";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_EPMJob ( const GET_DUMMY, const tag_t )
    //
    //   Purpose :   Constructor for the class GET_EPMJob
    //
    //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
    //               tTag    - The Tag of this Teamcenter EPMJob Object
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
    GET_EPMJob::GET_EPMJob ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_EPMJob()
    //
    //   Purpose :   Destructor for the class GET_EPMJob
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
    GET_EPMJob::~GET_EPMJob() {}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   isJobComplete()
    //
    //   Purpose :   Method to find whether this current job is complete or not
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   Flag indicating the Job Completion Status (bool, true - complete, false - not-complete)
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     9 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_EPMJob::isJobComplete()
    {
        bool bVerdict = false;

        ResultCheck stat;

        try
        {
            char *psReviewTaskName = NULL;

            // get the job's current release level
            stat = EPM_ask_review_task_name ( _tag, psReviewTaskName );
            MEM_free ( psReviewTaskName );
        }
        catch ( const IFail& ex )
        {
            if ( ex.ifail() == CR_no_current_release_level )
            {
                bVerdict = true;
            }
            else
            {
                throw ex;
            }
        }

       return bVerdict;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance (tTag)
    //
    //   Purpose :   Method to get the instance of this class using tag_t
    //
    //   Inputs  :   tTag - tag of the EPMJob
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_EPMJob Smart Pointer object is returned
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_EPMJobUnqPtr GET_EPMJob::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_EPMJob::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, EPMJOB_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + EPMJOB_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_EPMJob::getInstance(tTag)\n" );

        return make_unique<GET_EPMJob> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
    //   Return  :   The GET_EPMJob Smart Pointer object is returned
    //
    //   History:
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_EPMJobUnqPtr GET_EPMJob::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_EPMJob::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_EPMJob::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }
    
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   createEPMProcess ( const string, const string, const tag_t, GET_POM_objectShrPtr, const int )
    //
    //   Purpose :   Method to create a EPM Process
    //
    //   Inputs  :   sProcessTempName - Process template Name
    //               sProcessDesc - Process Description
    //               sProcessName - Name of the Process
    //               vAttachment - Vector of Attachments to the process
    //               iAttachmentType - Attachment types like target or reference
    //
    //   Outputs :   none
    //
    //   Return  :   Tag of new process
    //
    //   History:
    //      Who                                Date                 Description
    //   Capgemini Development Team          29 May, 2017         Initial creation
    //   TCS Development Team                31 May, 2017         Modified the code and corrected all errors
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_EPMJobUnqPtr GET_EPMJob::createEPMProcess ( const string sProcessTempName, const string sProcessName, const string sProcessDesc, vector<GET_POM_objectShrPtr> &vAttachments, const int iAttachmentType )
    {
        IFail *exception = NULL;
        
        int *piAttachmentTypeList = NULL;

        tag_t tProcessTempTag = NULLTAG;
        tag_t tProcessTag = NULLTAG;

        tag_t *ptAttachmentList = NULLTAG;
        
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_EPMJob::createEPMProcess" );

        GET_vectorToArray ( vAttachments, &ptAttachmentList );
        piAttachmentTypeList = ( int* ) malloc ( vAttachments.size() * sizeof ( int ) );
        for ( size_t iIndex = 0; iIndex < vAttachments.size(); iIndex++ )
        {
            piAttachmentTypeList[iIndex] = iAttachmentType;
        }

        // Get Process Template Tag
        stat = EPM_find_process_template ( sProcessTempName.c_str(), &tProcessTempTag );
        if ( tProcessTempTag == NULLTAG )
        {
            THROW ( "Process Template with the name \"" + sProcessTempName + "\" not found in Teamcenter" );
        }
        // Create a new process with process name, description, process template tag
        stat = EPM_create_process ( sProcessName.c_str(), sProcessDesc.c_str(), tProcessTempTag, vAttachments.size(), ptAttachmentList, piAttachmentTypeList, &tProcessTag );

        // Free Memory
        if ( ptAttachmentList != NULL )
        {
            free ( ptAttachmentList );
            ptAttachmentList = NULL;
        }
        if ( piAttachmentTypeList != NULL )
        {
            free ( piAttachmentTypeList );
            piAttachmentTypeList = NULL;
        }

        LOG_TRACE ( logger, "END : GET_EPMJob::createEPMProcess" );

        return make_unique<GET_EPMJob> ( GET_DUMMY::GET_DUMMY_VALUE, tProcessTag );
    }
}
