
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_group.hxx
//
//    Purpose:   Header class for dealing with GET_Pom_group objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_POM_GROUP_HXX
#define GET_POM_GROUP_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>
#include <GET_GroupMember.hxx>

//CPP Includes
#include <string>
#include <vector>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_POM_groupUnqPtr unique_ptr<GET_POM_group>
    #define GET_POM_groupShrPtr shared_ptr<GET_POM_group>
}

namespace get
{
    class GET_POM_user;
    class DLLEXPORT GET_POM_group : public GET_POM_object
    {
        private:
            string sGroupName; // The Group Name
            string sGroupFullName; // The Group Full Name

        public:
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   GET_POM_group ( const GET_DUMMY, const tag_t )
            //
            //   Purpose :   Constructor for the class GET_POM_group
            //
            //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
            //               tTag    - The Tag of this Teamcenter POM_group Object
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
            GET_POM_group ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   ~GET_POM_group()
            //
            //   Purpose :   Destructor for the class GET_POM_group
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
            virtual ~GET_POM_group();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getGroupName()
            //
            //   Purpose :   Method to get the Name of this Group
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The Name of this Group (string)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     11 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            string getGroupName();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getGroupFullName()
            //
            //   Purpose :   Method to get the Full Name of this Group
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The Full Name of this Group (string)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     11 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            string getGroupFullName();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getActiveGroupMembers()
            //
            //   Purpose :   Method to get the active group member in this group
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   A vector containing the active GET_GroupMember Smart Pointer
            //               Instances of this Group(vector<GET_GroupMemberUnqPtr>)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     29 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_GroupMemberUnqPtr> getActiveGroupMembers();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getAllGroupMembers()
            //
            //   Purpose :   Method to get all the group member in this group
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   A vector containing all the GET_GroupMember Smart Pointer Instances of this Group(vector<GET_GroupMemberUnqPtr>)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     29 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_GroupMemberUnqPtr> getAllGroupMembers();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   addGroupMember()
            //
            //   Purpose :   Method to add group member in the group
            //
            //   Inputs  :   userPtr - The GET_POM_user Smart Pointer Instance of the User to be added to this Group
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_GroupMember Smart Pointer instance of the new;y created Group Member(GET_GroupMemberUnqPtr)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     29 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            GET_GroupMemberUnqPtr addGroupMember ( const shared_ptr<GET_POM_user> );

             /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getInstance (tTag)
             //
             //   Purpose :   Method to get the instance of this class using tag_t
             //
             //   Inputs  :   tTag - tag of the POM_group
             //
             //   Outputs :   none
             //
             //   Return  :   The GET_POM_group Smart Pointer object is returned
             //
             //   History :
             //      Who                    Date                 Description
             //   TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_POM_groupUnqPtr getInstance ( const tag_t );

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
             //   Return  :   The GET_POM_group Smart Pointer object is returned
             //
             //   History:
             //      Who                    Date                 Description
             //   TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_POM_groupUnqPtr getInstance ( const string );
            
            
            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   find()
             //
             //    Purpose:   Method to find group with the given group name
             //
             //     Inputs:   String
             //
             //    Outputs:   none
             //
             //     Return:   The GET_Group Smart Pointer Instance of the found Group
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     3 Apr, 2017         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_POM_groupUnqPtr find ( const string );
    };
}

#endif // GET_POM_GROUP_HXX
