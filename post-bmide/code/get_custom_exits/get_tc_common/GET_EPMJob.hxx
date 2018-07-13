
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_EPMJob.hxx
//
//    Purpose:   Class for dealing with Teamcenter EMP Job objects
//
//    History:
//      Who                          Date                 Description
//  TCS Development Team           18 Mar, 2016         Initial creation
//  Capgemini Development Team     29 Mar, 2017         Added new method declarations for createEPMProcess method
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_EPM_JOB_HXX
#define GET_EPM_JOB_HXX

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>

// C++ Includes
#include <string>
#include <vector>

// Teamcenter Includes
#include <epm/epm.h>
#include <epm/epm_task_template_itk.h>

// Smart Pointer Definition
namespace get
{
    #define GET_EPMJobUnqPtr unique_ptr<GET_EPMJob>
    #define GET_EPMJobShrPtr shared_ptr<GET_EPMJob>
}

namespace get
{
    class DLLEXPORT GET_EPMJob : public GET_WorkspaceObject
    {
        public:

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
            GET_EPMJob ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_EPMJob();

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
            bool isJobComplete();

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
            static GET_EPMJobUnqPtr getInstance ( const tag_t );

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
            static GET_EPMJobUnqPtr getInstance ( const string );
            
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   createEPMProcess ( const string, const string, const tag_t, vector<GET_POM_objectShrPtr>, const int )
            //
            //   Purpose :   Method to create a EPM Process
            //
            //   Inputs  :   sProcessTempName - Process template Name
            //               sProcessDesc - Process Description
            //               sProcessName - Name of the Process
            //               iAttachmentCount - Number of attachments
            //               vAttachment - Vector of Attachments to the process
            //               iAttachmentType - Attachment types like target or reference
            //
            //   Outputs :   none
            //
            //   Return  :   Tag of new process
            //
            //   History:
            //      Who                                Date                 Description
            //   Capgemini Development Team     29 May, 2017         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_EPMJobUnqPtr createEPMProcess ( const string, const string, const string, vector<GET_POM_objectShrPtr>&, const int );
    };
}

#endif // GET_EPM_JOB_HXX
