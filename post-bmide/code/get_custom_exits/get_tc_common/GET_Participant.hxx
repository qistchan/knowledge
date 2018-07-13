
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Participant.hxx
//
//    Purpose:   Class for dealing with GET_Participant objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_PARTICIPANT_HXX
#define GET_PARTICIPANT_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>
#include <GET_GroupMember.hxx>
#include <GET_ResourcePool.hxx>

//CPP Includes
#include <string>
#include <vector>

#include <sa/user.h>

// Smart Pointer Definition
namespace get
{
    #define GET_ParticipantUnqPtr unique_ptr<GET_Participant>
    #define GET_ParticipantShrPtr shared_ptr<GET_Participant>
}

namespace get
{
    class DLLEXPORT GET_Participant : public GET_POM_object
    {
        public:

    	    /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_Participant
			 //
			 //    Purpose:   Constructor for the class GET_Participant
			 //
			 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
			 //               tTag    - The Tag of this Teamcenter Participant Object
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
            GET_Participant ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_Participant
			 //
			 //    Purpose:   Destructor for the class GET_Participant
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
            virtual ~GET_Participant();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getParticipantType()
             //
             //    Purpose:   Method to get the Participant Type for this Participant
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Participant Type for this Participant (string)
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     06 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            string getParticipantType();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getAssignee()
			 //
			 //    Purpose:   Method to get assignee for Participant
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   GET_POM_objectPtr - Smart Pointer for GET_POM_object instance
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     06 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_POM_objectUnqPtr getAssignee();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   setAssignee()
			 //
			 //    Purpose:   Method to set assignee for Participant
			 //
			 //     Inputs:   pomObjectPtr - Smart Pointer for GET_POM_object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     06 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            void setAssignee ( const GET_POM_objectShrPtr );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getParticipantGroupMember()
             //
             //    Purpose:   Method to get the GroupMember of the assigned participant (can be null)
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   GET_GroupMemberUnqPtr - Smart Pointer for GET_GroupMember object
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     06 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_GroupMemberUnqPtr getParticipantGroupMember();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getParticipantResorcePool()
             //
             //    Purpose:   Method to get the ResourcePool of the assigned participant (can be null)
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   GET_ResourcePoolUnqPtr - Smart Pointer for GET_ResourcePool object
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     06 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_ResourcePoolUnqPtr getParticipantResorcePool();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance (tTag)
			 //
			 //    Purpose:   Method to get the instance of this class using tag_t
			 //
			 //     Inputs:    tTag - tag of the object
			 //
			 //    Outputs:   none
			 //
			 //     Return:    The GET_Participant -Smart Pointer Instance for the given tag
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ParticipantUnqPtr getInstance ( const tag_t );

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
			 //     Return:   The GET_Participant -Smart Pointer Instance for the given UID
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ParticipantUnqPtr getInstance ( const string );
   };
}

#endif // GET_PARTICIPANT_HXX
