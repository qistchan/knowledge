
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_UserSession.cxx
//
//    Purpose:   Header class for defining the basic behavior of Teamcenter UserSession Objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     21 Jun, 2017           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_UserSession.hxx>
#include <GET_TC_Types.hxx>

// Teamcenter Includes
#include <ce/ce.h>

#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <tccore/item.h>
#include <tccore/aom.h>
#include <tccore/tctype.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get_tc_common.GET_UserSession";

namespace get
{
    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   GET_UserSession ( GET_DUMMY, tTag )
     //
     //   Purpose :   Constructor for the class GET_UserSession
     //
     //   Inputs  :   enDummy - A dummy enum value ( GET_DUMMY )
     //               tTag - The tag of a UserSession Object ( tag_t )
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_UserSession::GET_UserSession ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_RuntimeBusinessObject ( enDummy, tTag )
    {
    	ResultCheck stat;

        tag_t tGroupTag   = NULLTAG;
        tag_t tRoleTag    = NULLTAG;
        tag_t tUserTag    = NULLTAG;
        tag_t tProjectTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_UserSession::GET_UserSession" );

        // Get the Group Entry from the UserSession Object
        stat = AOM_ask_value_tag ( _tag, GROUP_ARG, &tGroupTag );
        groupPtr = ( move ( GET_POM_group::getInstance ( tGroupTag ) ) );

        // Get the Role Entry from the UserSession Object
        stat = AOM_ask_value_tag ( _tag, ROLE_ARG, &tRoleTag );
        rolePtr = ( move ( GET_Role::getInstance ( tRoleTag ) ) );

        // Get the User Entry from the UserSession Object
        stat = AOM_ask_value_tag ( _tag, USER_ARG, &tUserTag );
        userPtr = ( move ( GET_POM_user::getInstance ( tUserTag ) ) );

        // Get the Project Entry from the UserSession Object
        stat = AOM_ask_value_tag ( _tag, PROJECT_ATTR, &tProjectTag );
        if ( tProjectTag != NULLTAG )
        {
            projectPtr = ( move ( GET_TC_Project::getInstance ( tProjectTag ) ) );
        }

        LOG_TRACE ( logger, "END : GET_UserSession::GET_UserSession" );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   ~GET_UserSession()
     //
     //   Purpose :   Destructor for the class GET_UserSession
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_UserSession::~GET_UserSession() {};

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance ( tTag )
     //
     //   Purpose :   Method to get the instance of this type using tag_t
     //
     //   Inputs  :   tTag - tag of the object
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_UserSession Smart Pointer Instance for the given tag
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_UserSessionUnqPtr GET_UserSession::getInstance ( const tag_t tTag )
    {
        return make_unique<GET_UserSession> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance (sUID)
     //
     //   Purpose :   Method to get the instance of this type using string UID
     //
     //   Inputs  :   sUID - UID as string
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_UserSession Smart Pointer Instance for the given UID
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_UserSessionUnqPtr GET_UserSession::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_UserSession::getInstance ( sUID )" );

        tag_t tObjectTag = GET_POM_object::getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_UserSession::getInstance ( sUID )" );

        return getInstance ( tObjectTag );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getUserSession()
	 //
	 //   Purpose :   Method to get current users UserSession
	 //
	 //   Inputs  :   none
	 //
	 //   Outputs :   none
	 //
	 //   Return  :   The GET_UserSession Smart Pointer Instance for the current UserSession
	 //
	 //   History :
	 //      Who                   Date                 Description
	 //  TCS Development Team     21 Jun, 2017         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_UserSessionUnqPtr GET_UserSession::getCurrentUserSession()
    {
    	GET_UserSessionUnqPtr userSessionUnqPtr;

    	ResultCheck stat;

    	tag_t tUserSession = NULLTAG;
    	
    	LOG_TRACE ( logger, "START : GET_UserSession::getCurrentUserSession()" );

    	stat = CE_current_user_session_tag	( &tUserSession );
    	if ( tUserSession != NULLTAG )
		{
    		userSessionUnqPtr = make_unique<GET_UserSession> ( GET_DUMMY::GET_DUMMY_VALUE, tUserSession );
		}

		LOG_TRACE ( logger, "END : GET_UserSession::getCurrentUserSession()" );

		return userSessionUnqPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getGroup()
     //
     //   Purpose :   Method to get Group object using UserSession
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_POM_group smart pointer object is returned
     //
     //   History:
     //      Who                    Date                 Description
     //   TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_POM_groupShrPtr GET_UserSession::getGroup()
    {
        return groupPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getRole()
     //
     //   Purpose :   Method to get Role object using UserSession
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_Role smart pointer object is returned
     //
     //   History:
     //      Who                    Date                 Description
     //   TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_RoleShrPtr GET_UserSession::getRole()
    {
        return rolePtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getUser()
     //
     //   Purpose :   Method to get User object using UserSession
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_POM_user smart pointer object is returned
     //
     //   History:
     //      Who                    Date                 Description
     //   TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_POM_userShrPtr GET_UserSession::getUser()
    {
        return userPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getProject()
     //
     //   Purpose :   Method to get Project object using UserSession
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_TC_Project smart pointer object is returned
     //
     //   History:
     //      Who                    Date                 Description
     //   TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_TC_ProjectShrPtr GET_UserSession::getProject()
    {
        return projectPtr;
    }
}
