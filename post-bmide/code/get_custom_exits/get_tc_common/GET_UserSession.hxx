
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_UserSession.hxx
//
//    Purpose:   Header class for defining the basic behavior of all Teamcenter UserSession Objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     21 Jun, 2017           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_USERSESSION_HXX
#define GET_USERSESSION_HXX

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_RuntimeBusinessObject.hxx>
#include <GET_POM_object.hxx>
#include <GET_POM_group.hxx>
#include <GET_Role.hxx>
#include <GET_POM_user.hxx>
#include <GET_POM_application_object.hxx>
#include <GET_TC_Project.hxx>

// Teamcenter Includes

#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <fclasses/tc_date.h>

// Smart Pointer Definition
namespace get
{
    #define GET_UserSessionUnqPtr unique_ptr<GET_UserSession>
    #define GET_UserSessionShrPtr shared_ptr<GET_UserSession>
}

// Class Definition
namespace get
{
    class DLLEXPORT GET_UserSession : public GET_RuntimeBusinessObject
    {
        private:

                shared_ptr<GET_POM_group> groupPtr;
                shared_ptr<GET_Role> rolePtr;
                shared_ptr<GET_POM_user> userPtr;
                shared_ptr<GET_TC_Project> projectPtr;

        public:
            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   GET_UserSession (GET_DUMMY, tTag)
             //
             //   Purpose :   Constructor for the class GET_UserSession
             //
             //   Inputs  :   enDummy - A dummy enum value (GET_DUMMY)
             //               tTag - The tag of a Runtime Business Object (tag_t)
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
            GET_UserSession ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_UserSession();

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
            shared_ptr<GET_POM_group> getGroup();

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
            shared_ptr<GET_Role> getRole();

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
            shared_ptr<GET_POM_user> getUser();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getProject()
			 //
			 //   Purpose :   Method to get project using UserSession
			 //
			 //   Inputs  :   none
			 //
			 //   Outputs :   none
			 //
			 //   Return  :   The GET_POM_application_object smart pointer object for user Project is returned
			 //
			 //   History:
			 //      Who                    Date                 Description
			 //   TCS Development Team     21 Jun, 2017         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            shared_ptr<GET_TC_Project> getProject();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getUserSession
			 //
			 //   Purpose :   Method to get currently logged in user's UserSession
			 //
			 //   Inputs  :   none
			 //
			 //   Outputs :   none
			 //
			 //   Return  :   The GET_UserSession Smart Pointer for currently logged in user.
			 //
			 //   History :
			 //      Who                   Date                 Description
			 //  TCS Development Team     21 Jun, 2017         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_UserSessionUnqPtr getCurrentUserSession();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getInstance (tTag)
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
            static GET_UserSessionUnqPtr getInstance ( const tag_t );

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
            static GET_UserSessionUnqPtr getInstance ( const string );
    };
}

#endif // GET_USERSESSION_HXX
