
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_user.hxx
//
//    Purpose:   Header class for dealing with GET_POM_user objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     3 Mar, 2016           Initial creation
//  TCS Development Team     20 Jun, 2018          Added getAssignedProject()
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_POM_USER_HXX
#define GET_POM_USER_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>
#include <GET_Folder.hxx>
#include <GET_POM_group.hxx>
#include <GET_Person.hxx>
#include <GET_TC_Project.hxx>

//Teamcenter Includes
#include <sa/groupmember.h>
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_POM_userUnqPtr unique_ptr<GET_POM_user>
    #define GET_POM_userShrPtr shared_ptr<GET_POM_user>
}

namespace get
{
    class DLLEXPORT GET_POM_user : public GET_POM_object
    {
    	private:
    		string sUserName;
    		string sUserID;

        public:

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
    		GET_POM_user ( const GET_DUMMY, const tag_t );

    		/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_POM_user
			 //
			 //    Purpose:   Destructor for the class GET_POM_user
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
            virtual ~GET_POM_user();

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
            static GET_POM_userUnqPtr getCurrentLoggedInUser();

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
            bool isMemberOfGroup ( const GET_POM_groupShrPtr );

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
			string getName() const;

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
			string getID() const;

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
			bool isActive();

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
			GET_PersonUnqPtr getPerson();


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
			GET_FolderUnqPtr getHome();

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
			GET_POM_groupUnqPtr getDefaultGroup();

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
			GET_FolderUnqPtr getNewStuffFolder();

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
			 //  TCS Development Team     20 Jun, 2018         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			vector <GET_TC_ProjectUnqPtr> getAssignedProjects ( const bool, const bool );

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
			static GET_POM_userUnqPtr getInstance ( const tag_t );

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
		    static GET_POM_userUnqPtr getInstance ( const string );
    };
}

#endif // GET_POM_USER_HXX
