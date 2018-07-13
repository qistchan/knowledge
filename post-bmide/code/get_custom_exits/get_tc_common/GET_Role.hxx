
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Role.hxx
//
//    Purpose:   Header class for dealing with GET_Role objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_ROLE_HXX
#define GET_ROLE_HXX

#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_application_object.hxx>

#include <sa/role.h>

// Smart Pointer Definition
namespace get
{
    #define GET_RoleUnqPtr unique_ptr<GET_Role>
    #define GET_RoleShrPtr shared_ptr<GET_Role>
}

namespace get
{
    class DLLEXPORT GET_Role : public GET_POM_application_object
    {
        private:
            string sRoleDesc;
            string sRoleName;

        public:

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
            GET_Role ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_Role();

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
			virtual string getRoleName() const;

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
			virtual string getRoleDescription() const;

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
			static GET_RoleUnqPtr getCurrentLoggedInUserRole();

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
			static GET_RoleUnqPtr find ( const string );

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
			static vector<GET_RoleUnqPtr> extent();

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
			static GET_RoleUnqPtr getInstance ( const tag_t );

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
			static GET_RoleUnqPtr getInstance ( const string );
    };
}

#endif // GET_ROLE_HXX
