
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_GroupMember.hxx
//
//   Purpose :   Header class for dealing with GET_GroupMember objects
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016           Initial creation
//  TCS Development Team     27 Apr, 2017           Added method to find group members from group/role information
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_GROUPMEMBER_HXX
#define GET_GROUPMEMBER_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>

//Teamcenter Includes
#include <sa/groupmember.h>
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_GroupMemberUnqPtr unique_ptr<GET_GroupMember>
    #define GET_GroupMemberShrPtr shared_ptr<GET_GroupMember>
}

namespace get
{
    class GET_POM_group;
    class GET_Role;
    class GET_POM_user;
    class GET_YESY;

    class DLLEXPORT GET_GroupMember : public GET_POM_object
    {
        private:

            shared_ptr<GET_POM_group> groupPtr;
            shared_ptr<GET_Role> rolePtr;
            shared_ptr<GET_POM_user> userPtr;

        public:

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   GET_GroupMember ( const GET_DUMMY, const tag_t )
            //
            //   Purpose :   Constructor for the class GET_GroupMember
            //
            //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
            //               tTag    - The Tag of this Teamcenter GroupMember Object
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
            GET_GroupMember ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   ~GET_GroupMember()
            //
            //   Purpose :   Destructor for the class GET_GroupMember
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
            virtual ~GET_GroupMember();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   deleteInstance()
            //
            //   Purpose :   Method to delete the instance of this class
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void deleteInstance();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getGroup()
            //
            //   Purpose :   Method to get Group object using group member
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_POM_group smart pointer object is returned
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            shared_ptr<GET_POM_group> getGroup();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getRole()
            //
            //   Purpose :   Method to get Role object using group member
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_Role smart pointer object is returned
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            shared_ptr<GET_Role> getRole();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getUser()
            //
            //   Purpose :   Method to get User object using group member
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_POM_user smart pointer object is returned
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            shared_ptr<GET_POM_user> getUser();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getInstance (tTag)
            //
            //   Purpose :   Method to get the instance of this class using tag_t
            //
            //   Inputs  :   tTag - tag of the GroupMember
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_GroupMember Smart Pointer object is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_GroupMemberUnqPtr getInstance ( const tag_t );

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
            //   Return  :   The GET_GroupMember Smart Pointer object is returned
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_GroupMemberUnqPtr getInstance ( const string );

           /*STARTFUNCDOC ***
           //
           ===========================================================================
           //   Function:   getCurrentGroupMember()
           //
           //   Purpose :   Method to get current logged in groupMember
           //
           //   Inputs  :   none
           //
           //   Outputs :   none
           //
           //   Return  :   The GET_GroupMember smart pointer object is returned
           //
           //   History:
           //      Who                    Date                 Description
           //   TCS Development Team     24 Aug, 2016         Initial creation
           //
           ===========================================================================
           //ENDFUNCDOC   ***/
            static GET_GroupMemberUnqPtr getCurrentGroupMember();
            
            // ===========================================================================
             //   Function:   find()
             //
             //    Purpose:   Method to find group member with the given role/group information
             //
             //     Inputs:   String Group Name, String Role Name
             //
             //    Outputs:   Vector of GroupMember unique pointers
             //
             //     Return:   The GET_GroupMemeber Smart Pointer Instance of the found Group/Role
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     03 Apr, 2017        Initial creation
             //
            // ===========================================================================
             //ENDFUNCDOC   ***/
            
            static vector<GET_GroupMemberUnqPtr> find ( const string , const string );
    };
}

#endif // GET_GROUPMEMBER_HXX
