
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Role.cxx
//
//    Purpose:   Class for dealing with GET_Role objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#include <GET_TC_Logger.hxx>
#include <GET_Exception.hxx>
#include <GET_Role.hxx>

#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.ge_tc_common.GET_Role";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_Role
	 //
	 //    Purpose:   Constructor for the class GET_Role
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag - The Tag of this Teamcenter Role Object
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
	GET_Role::GET_Role ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_application_object ( enDummy, tTag )
	{
	    char *pcRoleDesc = NULL;
	    char *pcRoleName = NULL;

	    ResultCheck stat;

	    stat = SA_ask_role_name2 ( _tag, &pcRoleName );
	    sRoleName = pcRoleName;
        MEM_free ( pcRoleName );

        stat = SA_ask_role_description2 ( _tag, &pcRoleDesc );
        sRoleDesc = pcRoleDesc;
        MEM_free ( pcRoleDesc );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_Role
	 //
	 //    Purpose:   Destructor for the class GET_Role
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
	GET_Role::~GET_Role(){}

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
	 //     Return:   The GET_Role Smart Pointer Instance of the given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_RoleUnqPtr GET_Role::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_Role::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, ROLE_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + ROLE_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_Role::getInstance(tTag)\n" );

		return make_unique <GET_Role> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
	 //     Return:   The GET_Role Smart Pointer Instance of the given UID
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_RoleUnqPtr GET_Role::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_Role::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );
		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_Role::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getRoleName()
	 //
	 //    Purpose:   Method to get the Role Name
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The Role Name of this Role Object (string)
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     06 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    string GET_Role::getRoleName() const
    {
    	return sRoleName;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getRoleDescription()
	 //
	 //    Purpose:   Method to get the Role Description
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The Role Description of this Role Object
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     06 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	string GET_Role::getRoleDescription() const
	{
		return sRoleDesc;
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getCurrentLoggedInUserRole()
	 //
	 //    Purpose:   Method to get the current role as GET_Role object
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_Role Smart Pointer Instance of the currently logged-in role
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     06 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_RoleUnqPtr GET_Role::getCurrentLoggedInUserRole()
	{
		ResultCheck stat;

		tag_t tRoleTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_Role::getCurrentLoggedInUserRole" );

		stat = SA_ask_current_role ( &tRoleTag );

		LOG_TRACE ( logger, "END : GET_Role::getCurrentLoggedInUserRole" );

		return make_unique<GET_Role> ( GET_DUMMY::GET_DUMMY_VALUE, tRoleTag );
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
	 //  TCS Development Team     06 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_RoleUnqPtr GET_Role::find ( const string sRoleName )
	{
	    GET_RoleUnqPtr rolePtr;

		ResultCheck stat;

		tag_t tRoleTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_Role::find" );

		stat = SA_find_role2 ( sRoleName.c_str(), &tRoleTag );
		if ( tRoleTag != NULLTAG )
		{
		    rolePtr = make_unique<GET_Role> ( GET_DUMMY::GET_DUMMY_VALUE, tRoleTag );
		}

		LOG_TRACE(logger,"GET_Role::find - END\n");

		return rolePtr;
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   extent()
	 //
	 //    Purpose:   Method to get all the roles from the database
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   A vector containing all the GET_Role Smart Pointer Instances from the Teamcenter Database
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     06 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	vector<GET_RoleUnqPtr> GET_Role::extent()
	{
		int iRoleCount = 0;

		ResultCheck stat;

		tag_t *tRoleTags = NULL;

		vector<GET_RoleUnqPtr> vRoles;

		LOG_TRACE ( logger, "START : GET_Role::extent" );

		stat = SA_extent_role ( &iRoleCount, &tRoleTags );
		for ( int iIndex = 0; iIndex < iRoleCount; iIndex++ )
		{
		    vRoles.push_back ( make_unique<GET_Role> ( GET_DUMMY::GET_DUMMY_VALUE, tRoleTags[iIndex] ) );
		}

		MEM_free ( tRoleTags );

		LOG_TRACE ( logger, "END : GET_Role::extent" );

		return vRoles;
	}
}
