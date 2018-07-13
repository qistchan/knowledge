
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_group.cxx
//
//    Purpose:   Class to dealing with GET_POM_group objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_GroupMember.hxx>
#include <GET_POM_group.hxx>
#include <GET_POM_user.hxx>

//Teamcenter Includes
#include <sa/sa.h>
#include <sa/user.h>
#include <sa/group.h>
#include <sa/groupmember.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_POM_group";

namespace get
{
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
    GET_POM_group::GET_POM_group ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag )
    {
        ResultCheck stat;

        char *pcGroupName = NULL;

        LOG_TRACE ( logger, "START : GET_POM_group::GET_POM_group" );

        // Get the Group Name
        stat = SA_ask_group_name2 ( tTag, &pcGroupName );
        sGroupName = pcGroupName;
        MEM_free ( pcGroupName );

        // Get the Full Group Name
        stat = SA_ask_group_full_name ( tTag, &pcGroupName );
        sGroupFullName = pcGroupName;
        MEM_free ( pcGroupName );

        LOG_TRACE ( logger, "END : GET_POM_group::GET_POM_group" );
    }

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
    GET_POM_group::~GET_POM_group() {};

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
    string GET_POM_group::getGroupName()
    {
        return sGroupName;
    }

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
    string GET_POM_group::getGroupFullName()
    {
        return sGroupFullName;
    }

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
    vector<GET_GroupMemberUnqPtr> GET_POM_group::getActiveGroupMembers()
    {
        int iMembers = 0;

        ResultCheck stat;

        tag_t *tGroupMemberTags = NULL;

        vector<GET_GroupMemberUnqPtr> vGroupMember;

        LOG_TRACE ( logger, "START : GET_POM_group::getActiveGroupMembers" );

        stat = SA_find_groupmembers_by_group ( _tag, &iMembers, &tGroupMemberTags );

        for ( int iCount = 0; iCount < iMembers; iCount++ )
        {
            vGroupMember.push_back ( make_unique<GET_GroupMember> ( GET_DUMMY::GET_DUMMY_VALUE, tGroupMemberTags[iCount] ) );
        }
        MEM_free ( tGroupMemberTags );

        LOG_TRACE ( logger, "END : GET_POM_group::getActiveGroupMembers" );

        return vGroupMember;
    }

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
    GET_GroupMemberUnqPtr GET_POM_group::addGroupMember ( const GET_POM_userShrPtr userPtr )
    {
        ResultCheck stat;

        tag_t tGroupMemberTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_POM_group::getActiveGroupMember" );

        stat = SA_create_groupmember ( _tag, userPtr->getTag(), TRUE, &tGroupMemberTag );

        LOG_TRACE ( logger, "END : GET_POM_group::getActiveGroupMember" );

        return make_unique<GET_GroupMember> ( GET_DUMMY::GET_DUMMY_VALUE, tGroupMemberTag );
    }

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
    vector<GET_GroupMemberUnqPtr> GET_POM_group::getAllGroupMembers()
    {
        int iMembers = 0;

        ResultCheck stat;

        tag_t *tGroupTags = NULLTAG;

        vector<GET_GroupMemberUnqPtr> vGroupMember;

        LOG_TRACE ( logger, "START : GET_POM_group::getAllGroupMembers" );

        stat = POM_list_group_members ( _tag, &iMembers, &tGroupTags );

        for ( int iCount = 0; iCount < iMembers; iCount++ )
        {
            vGroupMember.push_back ( make_unique<GET_GroupMember> ( GET_DUMMY::GET_DUMMY_VALUE, tGroupTags[iCount] ) );
        }
        MEM_free ( tGroupTags );

        LOG_TRACE ( logger, "END : GET_POM_group::getAllGroupMembers" );

        return vGroupMember;
     }

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
     GET_POM_groupUnqPtr GET_POM_group::getInstance ( const tag_t tTag )
     {
         LOG_TRACE ( logger, "START : GET_POM_group::getInstance(tTag)" );

         if ( ! isDescendant ( tTag, POM_GROUP_CLASS ) )
         {
             string sMsg = string ( "The given tag is not an instance of the class " ) + POM_GROUP_CLASS;
             THROW ( sMsg );
         }

         LOG_TRACE ( logger, "END : GET_POM_group::getInstance(tTag)" );

         return make_unique<GET_POM_group> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //   Return  :   The GET_POM_group Smart Pointer object is returned
     //
     //   History:
     //      Who                    Date                 Description
     //   TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     GET_POM_groupUnqPtr GET_POM_group::getInstance ( const string sUID )
     {
         LOG_TRACE ( logger, "START : GET_POM_group::getInstance(sUID)" );

         tag_t tObjectTag = getTagFromUID ( sUID );
         if ( tObjectTag == NULLTAG )
         {
             THROW ( sUID + " is not a valid Teamcenter UID" );
         }

         LOG_TRACE ( logger, "END : GET_POM_group::getInstance(sUID)" );

         return getInstance ( tObjectTag );
     }
     
     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   find()
     //
     //    Purpose:   Method to find role with the given role name
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   The GET_Role Smart Pointer Instance of the found Role
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     03 Apr, 2017       Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_POM_groupUnqPtr GET_POM_group::find ( const string sGrpName )
    {
        GET_POM_groupUnqPtr grpPtr;

        ResultCheck stat;

        tag_t tGrpTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_POM_group::find" );

        stat = SA_find_group ( sGrpName.c_str(), &tGrpTag );
        if ( tGrpTag != NULLTAG )
        {
            grpPtr = make_unique<GET_POM_group> ( GET_DUMMY::GET_DUMMY_VALUE, tGrpTag );
        }

        LOG_TRACE ( logger, "GET_POM_group::find - END\n" );

        return grpPtr;
    }
}
