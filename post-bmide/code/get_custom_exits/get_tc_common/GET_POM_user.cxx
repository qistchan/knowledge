
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_user.cxx
//
//    Purpose:   Class for dealing with GET_POM_user objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     3 Mar, 2016         Initial creation
//  TCS Development Team     20 Jun, 2018        Added getAssignedProject()
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_POM_user.hxx>
#include <GET_POM_group.hxx>

//Teamcenter Includes
#include <tc/emh.h>
#include <sa/sa.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_POM_user";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_POM_user
	 //
	 //    Purpose:   Constructor for the class GET_POM_user
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag - The Tag of this Teamcenter POM user Object
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
    GET_POM_user::GET_POM_user ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag )
    {
    	char *pcUserName = NULL;
    	char *pcUserID = NULL;

    	ResultCheck stat;

    	stat = SA_ask_user_person_name2 ( tTag, &pcUserName );
    	sUserName = pcUserName;
    	MEM_free ( pcUserName );

    	stat = SA_ask_user_identifier2 ( tTag, &pcUserID );
        sUserID = pcUserID;
        MEM_free ( pcUserID );
    };

    GET_POM_user::~GET_POM_user() {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getInstance (tTag)
	 //
	 //    Purpose:   Method to get the instance of this class using tag_t
	 //
	 //     Inputs:   tTag - tag of the object
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_POM_user Smart Pointer Instance for the given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_POM_userUnqPtr GET_POM_user::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_POM_user::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, POM_USER_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + POM_USER_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_POM_user::getInstance(tTag)" );

		return make_unique<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
	}

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
     //     Return:   The GET_POM_user Smart Pointer Instance for the given UID
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_POM_userUnqPtr GET_POM_user::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_POM_user::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );
		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_POM_user::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getCurrentLoggedInUser()
	 //
	 //    Purpose:   Method to get the name of the logged in user
	 //
	 //     Inputs:   none
	 //   
	 //    Outputs:   none
	 //
	 //     Return:   GET_POM_userUnqPtr - GET_POM_user Smart Pointer object is returned
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     3 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_POM_userUnqPtr GET_POM_user::getCurrentLoggedInUser()
    {
        char *pcUserName = NULL;

        ResultCheck stat;

        tag_t tUserTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_POM_user::getCurrentLoggedInUser" );

        stat = POM_get_user ( &pcUserName, &tUserTag );

        LOG_TRACE ( logger, "END : GET_POM_user::getCurrentLoggedInUser" );

        MEM_free ( pcUserName );

        return make_unique<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tUserTag );
    }

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   isMemberOfGroup()
	 //
	 //    Purpose:   Method to identify user presence in the given group
	 //
	 //     Inputs:   groupPtr - The Input GET_POM_group Smart Pointer Instance
	 //   
	 //    Outputs:   none
	 //
	 //     Return:   boolean - True if user exists or False if user does exist in the given group
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     24 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    bool GET_POM_user::isMemberOfGroup ( const GET_POM_groupShrPtr groupPtr )
    {
        bool bIsMember = false;

        int iGrpMembersCnt = 0;

        ResultCheck stat;

        tag_t *ptGrpMembers = NULL;

        LOG_TRACE ( logger, "START : GET_POM_user::isMemberOfGroup" );

        stat = SA_find_groupmembers ( _tag, groupPtr->getTag(), &iGrpMembersCnt, &ptGrpMembers );
        if ( iGrpMembersCnt > 0 && ptGrpMembers != NULL )
        {
        	bIsMember = true;
        }

        MEM_free ( ptGrpMembers );

        LOG_TRACE ( logger, "END : GET_POM_user::isMemberOfGroup" );

        return  bIsMember;
    }

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getName()
	 //
	 //    Purpose:   Method to get the name of this user
	 //
	 //     Inputs:   none
	 //   
	 //    Outputs:   none
	 //
	 //     Return:   The Name of this User (string)
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     3 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	 string GET_POM_user::getName() const
	 {
		return sUserName;
	 }
	 
	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getID()
	 //
	 //    Purpose:   Method to get the ID of this User
	 //
	 //     Inputs:   none
	 //               
	 //    Outputs:   none
	 //
	 //     Return:   The ID of this User (string)
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     3 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/	 
	string GET_POM_user::getID() const
	{
        return sUserID;
	}
	 
	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   isActive()
	 //
	 //    Purpose:   Method to identify the active status of the user
	 //
	 //     Inputs:   none
	 //   
	 //    Outputs:   none
	 //
	 //     Return:   TRUE/FALSE - User Active/User Inactive(bool)
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     24 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	bool GET_POM_user::isActive()
	{
		int iStatus = 0;

		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_user::isActive" );

		stat = SA_get_user_status ( _tag, &iStatus );

		LOG_TRACE ( logger, "END : GET_POM_user::isActive" );

		return ( iStatus == 0 ? true : false );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getPerson()
	 //
	 //    Purpose:   Method to get Person instance of the user
	 //
	 //     Inputs:   none
	 //               
	 //    Outputs:   none
	 //
	 //     return:   GET_PersonUnqPtr - GET_Person Smart Pointer object is returned.
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     24 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_PersonUnqPtr GET_POM_user::getPerson()
	{
		ResultCheck stat;

		tag_t tPersonTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_POM_user::getPerson" );

		stat = SA_ask_user_person ( _tag, &tPersonTag );

		LOG_TRACE ( logger, "END : GET_POM_user::getPerson" );

        return make_unique<GET_Person> ( GET_DUMMY::GET_DUMMY_VALUE, tPersonTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getHome()
	 //
	 //    Purpose:   Method to get Home folder instance of the user
	 //
	 //     Inputs:   none
	 //   
	 //    Outputs:   none
	 //
	 //     Return:   The GET_Folder Smart Pointer instance of this User's Home Folder
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     3 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_FolderUnqPtr GET_POM_user::getHome()
	{
		ResultCheck stat;

		tag_t tHomeFolderTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_POM_user::getHome" );

		stat = SA_ask_user_home_folder ( _tag, &tHomeFolderTag );

		LOG_TRACE ( logger, "END : GET_POM_user::getHome" );

        return make_unique<GET_Folder> ( GET_DUMMY::GET_DUMMY_VALUE, tHomeFolderTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getDefaultGroupTag()
	 //
	 //    Purpose:   Method to get Group instance of the user
	 //
	 //     Inputs:   none
	 //               
	 //    Outputs:   none
	 //
     //     Return:   The GET_POM_group Smart Pointer instance of this User's Default Group
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     3 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_POM_groupUnqPtr GET_POM_user::getDefaultGroup()
	{
		ResultCheck stat;

		tag_t tGroupTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_POM_user::getDefaultGroup" );

		stat = POM_ask_user_default_group ( _tag, &tGroupTag );

		LOG_TRACE ( logger, "END : GET_POM_user::getDefaultGroup" );

		return make_unique<GET_POM_group> ( GET_DUMMY::GET_DUMMY_VALUE, tGroupTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getNewStuffFolder()
	 //
	 //    Purpose:   Method to get New Stuff folder instance of the user
	 //
	 //     Inputs:   none
	 //               
	 //    Outputs:   none
	 //
     //     Return:   The GET_Folder Smart Pointer instance of this User's Newstuff Folder
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     3 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_FolderUnqPtr GET_POM_user::getNewStuffFolder()
	{
		ResultCheck stat;

		tag_t tNSFolderTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_POM_user::getNewStuffFolder" );

		stat = SA_ask_user_newstuff_folder(_tag, &tNSFolderTag);

		LOG_TRACE ( logger, "END : GET_POM_user::getNewStuffFolder" );

	    return make_unique<GET_Folder> ( GET_DUMMY::GET_DUMMY_VALUE, tNSFolderTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getAssignedProject()
	 //
	 //    Purpose:   Method to get all projects assigned to user
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
     //     Return:   vector of GET_TC_ProjectUnqPtr  assigned
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  Development Team     20 June, 2018         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	vector <GET_TC_ProjectUnqPtr> GET_POM_user::getAssignedProjects ( const bool bIsActiveProj, const bool bIsPrivilegedProj )
	{
		bool bProgramsProj = false;

		int  iProjectCount = 0;

		tag_t *tProjectTags = NULL;

		vector <GET_TC_ProjectUnqPtr> vProjectUnqPtr;

		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_user::getAssignedProjects" );

		stat = PROJ_find_user_projects	( _tag, bIsActiveProj, bIsPrivilegedProj, bProgramsProj, &iProjectCount, &tProjectTags );
        for ( int iIndex = 0; iIndex < iProjectCount; iIndex++ )
		{
        	vProjectUnqPtr.push_back ( make_unique<GET_TC_Project> ( GET_DUMMY::GET_DUMMY_VALUE, tProjectTags[iIndex] ) );
		}

		MEM_free ( tProjectTags );

		LOG_TRACE ( logger, "END : GET_POM_user::getAssignedProject" );

		return vProjectUnqPtr;
	}
}
