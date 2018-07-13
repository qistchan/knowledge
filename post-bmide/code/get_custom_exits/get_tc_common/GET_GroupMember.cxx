
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_GroupMember.cxx
//
//   Purpose :   Class to dealing with GroupMember objects
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016         Initial creation
//  TCS Development Team     27 Apr, 2017         Added method to find group members from group/role information
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_GroupMember.hxx>
#include <GET_POM_group.hxx>
#include <GET_Role.hxx>
#include <GET_POM_user.hxx>
#include <GET_TC_Logger.hxx>

//Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <pom/pom/pom.h>

const string logger = "get.get_tc_common.GET_GroupMember";

namespace get
{
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
    GET_GroupMember::GET_GroupMember ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag )
    {
        ResultCheck stat;

        tag_t tGroupTag = NULLTAG;
        tag_t tRoleTag = NULLTAG;
        tag_t tUserTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_GroupMember::GET_GroupMember" );

        // Get the Group Entry from the Group Member Object
        stat = SA_ask_groupmember_group ( _tag, &tGroupTag );
        groupPtr = make_shared<GET_POM_group> ( GET_DUMMY::GET_DUMMY_VALUE, tGroupTag );

        // Get the Role Entry from the Group Member Object
        stat = SA_ask_groupmember_role ( _tag, &tRoleTag );
        rolePtr = make_shared<GET_Role> ( GET_DUMMY::GET_DUMMY_VALUE, tRoleTag );

        // Get the User Entry from the Group Member Object
        stat = SA_ask_groupmember_user ( _tag, &tUserTag );
        userPtr = make_shared<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tUserTag );

        LOG_TRACE ( logger, "END : GET_GroupMember::GET_GroupMember" );
    }

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
    GET_GroupMember::~GET_GroupMember() {};

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
    GET_GroupMemberUnqPtr GET_GroupMember::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_GroupMember::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, GROUPMEMBER_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + GROUPMEMBER_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_GroupMember::getInstance(tTag)" );

        return make_unique<GET_GroupMember> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
    //   Return  :   The GET_GroupMember Smart Pointer object is returned
    //
    //   History:
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_GroupMemberUnqPtr GET_GroupMember::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_GroupMember::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_GroupMember::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }

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
    void GET_GroupMember::deleteInstance()
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_GroupMember::deleteInstance" );

        stat = POM_delete_member ( _tag );

        LOG_TRACE ( logger, "START : GET_GroupMember::deleteInstance" );
    }

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
    GET_POM_groupShrPtr GET_GroupMember::getGroup()
    {
        return groupPtr;
    }

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
    GET_RoleShrPtr GET_GroupMember::getRole()
    {
        return rolePtr;
    }

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
    GET_POM_userShrPtr GET_GroupMember::getUser()
    {
        return userPtr;
    }

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
   GET_GroupMemberUnqPtr GET_GroupMember::getCurrentGroupMember()
   {
       LOG_TRACE ( logger, "START : GET_GroupMember::getCurrentGroupMember" );

       ResultCheck stat;

       GET_GroupMemberUnqPtr gmPtr;

       tag_t tGrpMemberTag = NULLTAG;

       stat = SA_ask_current_groupmember ( &tGrpMemberTag );

       gmPtr = make_unique<GET_GroupMember> ( GET_DUMMY::GET_DUMMY_VALUE, tGrpMemberTag );

       LOG_TRACE ( logger, "END : GET_GroupMember::getCurrentGroupMember" );

       return gmPtr;
    }
    
    // ===========================================================================
     //   Function:   find()
     //
     //    Purpose:   Method to find group member with the given role/group information
     //
     //     Inputs:   String Group Name, String Role Name
     //
     //    Outputs:   Vector of Group member unique pointers
     //
     //     Return:   The GET_GroupMemeber Smart Pointer Instance of the found Role
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team      03 Apr, 2017        Initial creation
     //
    // ===========================================================================
     //ENDFUNCDOC   ***/
    vector<GET_GroupMemberUnqPtr> GET_GroupMember::find ( const string sGroupName, const string sRoleName )
    {
        GET_POM_groupUnqPtr getGroupUnqPtr;

        GET_RoleUnqPtr getRoleUnqPtr;

        int iNumMembers = 0;

        ResultCheck stat;

        vector<GET_GroupMemberUnqPtr> vFoundGrpMem;

        LOG_TRACE ( logger, "START : GET_GroupMember::find" );

        getGroupUnqPtr = GET_POM_group::find ( sGroupName );
        if ( getGroupUnqPtr.get() != NULL )
        {
            getRoleUnqPtr = GET_Role::find ( sRoleName );
            if ( getRoleUnqPtr.get() != NULL )
            {
                tag_t *tMemTags = NULL;

                stat = SA_find_groupmember_by_role ( getRoleUnqPtr->getTag(), getGroupUnqPtr->getTag(), &iNumMembers, &tMemTags );
                if ( iNumMembers > 0 && tMemTags != NULL )
                {
                    for ( int iIndex = 0; iIndex < iNumMembers; iIndex++ )
                    {
                        vFoundGrpMem.push_back ( make_unique<GET_GroupMember> ( GET_DUMMY::GET_DUMMY_VALUE, tMemTags[iIndex] ) );
                    }
                    MEM_free ( tMemTags );
                }
            }
        }

        LOG_TRACE ( logger, "GET_GroupMember::find - END\n" );

        return vFoundGrpMem;
    }
}
