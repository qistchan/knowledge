
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_EPMTask.hxx
//
//    Purpose:   Class for dealing with Teamcenter EPM Task objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Jul, 2016         Initial creation
//  TCS Development Team     16 May, 2017         Added declaration of getRootTask(),getDecision(), askReviewers() and defined a new structure reviewTaskResults.
//  TechM Development Team   20 May, 2017         Added askEPMJob function
//  TCS Development Team     17 Oct, 2017         Added declaration of getDecision()
//  TCS Development Team     04 Jun, 2018         Added askEPMResponsibleParty function
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_EPM_TASK_HXX
#define GET_EPM_TASK_HXX

#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <string>
#include <vector>
#include <epm/signoff.h>

#include <GET_WorkspaceObject.hxx>
#include <GET_POM_user.hxx>
#include <GET_TC_Types.hxx>
#include <GET_Date.hxx>

// Smart Pointer Definition
namespace get
{
    #define GET_EPMTaskUnqPtr unique_ptr<GET_EPMTask>
    #define GET_EPMTaskShrPtr shared_ptr<GET_EPMTask>
}

namespace get
{
    class GET_EPMJob;
    //Structure definition
	struct ReviewTaskResults
	{
		string sDecision;
		string sComments;
		GET_DateUnqPtr decisionDatePtr;
	};

    class DLLEXPORT GET_EPMTask : public GET_WorkspaceObject
    {
        public:

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
            GET_EPMTask ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_EPMTask();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   addAttachments()
            //
            //   Purpose :   Method to attachment to this Task
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
            void addAttachments ( const int, const vector<GET_POM_objectShrPtr> );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   removeAttachments()
            //
            //   Purpose :   Method to attachment to this Task
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
            void removeAttachments ( const vector<GET_POM_objectShrPtr> );

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
            vector<GET_POM_objectUnqPtr> askAttachments ( const int );

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

            void setTaskResult ( string sTaskValue );

            /*STARTFUNCDOC ***
			//
			===========================================================================
			//   Function:   askReviewers()
			//
			//   Purpose :   Method to get reviewers from review task
			//
			//   Inputs  :   none
			//
			//   Outputs :   none
			//
			//   Return  :   vector<GET_POM_userUnqPtr> - Unique pointers of users appointed as reviewer
			//
			//   History :
			//      Who                   Date                 Description
			//  TCS Development Team     19 May, 2017         Initial creation
			//
			===========================================================================
			//ENDFUNCDOC   ***/
			vector<GET_POM_userUnqPtr> askReviewers();

			/*STARTFUNCDOC ***
			//
			===========================================================================
			//   Function:   getDecision( reviewUserTag )
			//
			//   Purpose :   Method to get decision, comments and decision date of Review task after Review.
			//
			//   Inputs  :  GET_POM_userShrPtr userShrPtr - Reviewer of the perform-signoffs task
			//
			//   Outputs :  reviewTaskResults &a - Structure reviewTaskResults containing decision,
			//                                     decision_date and comments if any of the perform-signoffs task
			//
			//   Return  :   none
			//
			//   History :
			//      Who                   Date                 Description
			//  TCS Development Team     19 May, 2017         Initial creation
			//
			===========================================================================
			//ENDFUNCDOC   ***/
			void getDecision ( GET_POM_userShrPtr userShrPtr, ReviewTaskResults &a );
			
			/*STARTFUNCDOC ***
			//
			===========================================================================
			//   Function:   getDecision ( string )
			//
			//   Purpose :   Method to get decision of condition task
			//
			//   Inputs  :   none
			//
			//   Outputs :   string sDecision.
			//
			//   Return  :   none
			//
			//   History :
			//      Who                   Date                 Description
			//  TCS Development Team     17 Oct, 2017         Initial creation
			//
			===========================================================================
			//ENDFUNCDOC   ***/
			void getDecision ( string & );

			/*STARTFUNCDOC ***
			//
			===========================================================================
			//   Function:   getRootTask()
			//
			//   Purpose :   Method to get rootTask
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

			GET_EPMTaskUnqPtr getRootTask();

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
            static GET_EPMTaskUnqPtr getInstance ( const tag_t );

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
			//  Ganesh Ubale          7 Sep, 2017            Initial creation
			//
			===========================================================================
			//ENDFUNCDOC   ***/
			
			vector<GET_EPMTaskUnqPtr> getSubTasks ( );
			//vector<GET_EPMTaskUnqPtr> recurseWFTasks( GET_EPMTaskUnqPtr taskUnqPtr, vector<GET_EPMTaskUnqPtr> vTaskUnqPtrs );


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
            static GET_EPMTaskUnqPtr getInstance ( const string );

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
            unique_ptr<GET_EPMJob> askEPMJob();

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
            GET_POM_userUnqPtr askEPMResponsibleParty();
    };
}

#endif // GET_EPM_TASK_HXX
