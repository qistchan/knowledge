
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_TC_Project.hxx
//
//    Purpose:   Header class for dealing with the GET_TC_Project
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team    21 Jun, 2017           Initial creation
//  TCS Development Team    20 Jun, 2018           Added assignProjectToItem()
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_TC_PROJECT_HXX
#define GET_TC_PROJECT_HXX

//GE  Incudes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

//CPP Includes
#include <string>
#include <vector>

#include <GET_POM_application_object.hxx>

// Teamcenter Includes
#include <tccore/aom_prop.h>
#include <tccore/project.h>
#include <tccore/releasestatus.h>


// Smart Pointer Definition
namespace get
{
    #define GET_TC_ProjectUnqPtr unique_ptr<GET_TC_Project>
    #define GET_TC_ProjectShrPtr shared_ptr<GET_TC_Project>
}

namespace get
{
    class DLLEXPORT GET_TC_Project : public GET_POM_application_object
    {
        private:
    	    bool bIsProjectActive;
    	    bool bIsProjectVisible;
    	    bool bIsProjectProgramSecured;

    	    string sProjectId;
            string sProjectName;
            string sProjectDesc;

        public:
            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   GET_TC_Project ( const GET_DUMMY, const tag_t )
             //
             //   Purpose :   Constructor for the class GET_TC_Project
             //
             //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
             //               tTag - The Tag of TC_Project Object
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
            GET_TC_Project ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   ~GET_TC_Project
             //
             //   Purpose :   Virtual Destructor
             //
             //   Inputs  :   none
             //
             //   Outputs :   none
             //
             //   Return  :   none
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     21 Jun, 2017         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            virtual ~GET_TC_Project();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   isProjectActive()
			 //
			 //   Purpose :   Method to check if project is active or not
			 //
			 //   Inputs  :   none
			 //
			 //   Outputs :   none
			 //
			 //   Return  :   boolean value is returned
			 //
			 //   History:
			 //      Who                    Date                 Description
			 //   TCS Development Team     21 Jun, 2017         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            bool isProjectActive();

            /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   isProjectVisible()
		     //
		     //   Purpose :   Method to check if project is visible or not
		     //
		     //   Inputs  :   none
		     //
		     //   Outputs :   none
		     //
		     //   Return  :   boolean value is returned
		     //
		     //   History:
		     //      Who                    Date                 Description
		     //   TCS Development Team     21 Jun, 2017         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
            bool isProjectVisible();

            /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   isProjectProgramSecured()
		     //
		     //   Purpose :   Method to check if Program-level security is used for project or not
		     //
		     //   Inputs  :   none
		     //
		     //   Outputs :   none
		     //
		     //   Return  :   boolean value is returned
		     //
		     //   History:
		     //      Who                    Date                 Description
		     //   TCS Development Team     21 Jun, 2017         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
            bool isProjectProgramSecured();

            /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   getProjectId()
		     //
		     //   Purpose :   Method to get project ID.
		     //
		     //   Inputs  :   none
		     //
		     //   Outputs :   none
		     //
		     //   Return  :   string is returned
		     //
		     //   History:
		     //      Who                    Date                 Description
		     //   TCS Development Team     21 Jun, 2017         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
            string getProjectId();

            /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   getProjectName()
		     //
		     //   Purpose :   Method to get Project name.
		     //
		     //   Inputs  :   none
		     //
		     //   Outputs :   none
		     //
		     //   Return  :   string is returned
		     //
		     //   History:
		     //      Who                    Date                 Description
		     //   TCS Development Team     21 Jun, 2017         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
            string getProjectName();

            /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   getProjectDesc()
		     //
		     //   Purpose :   Method to get Project Description
		     //
		     //   Inputs  :   none
		     //
		     //   Outputs :   none
		     //
		     //   Return  :   string is returned
		     //
		     //   History:
		     //      Who                    Date                 Description
		     //   TCS Development Team     21 Jun, 2017         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
            string getProjectDesc();

            /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   assignProjectToItem()
		     //
		     //   Purpose :   Method to assign Projects
		     //
		     //   Inputs  :   Project and Business Objects
		     //
		     //   Outputs :   none
		     //
		     //   Return  :   string is returned
		     //
		     //   History:
		     //      Who                    Date                 Description
		     //   TCS Development Team     20 Jun, 2018         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
             static void assignProjectToItem ( vector<GET_TC_ProjectShrPtr>, vector<GET_WorkspaceObjectShrPtr> );

             /*STARTFUNCDOC ***
              //
              ===========================================================================
              //   Function:   find()
              //
              //   Purpose :   Method to find project which matches the given project id
              //
              //   Inputs  :   sProjectID - Project ID to find (string)
              //
              //   Outputs :   none
              //
              //   Return  :   The GET_Project Smart Pointer Object matching the given Project ID(GET_TC_Project)
              //
              //   History :
              //      Who                   Date                 Description
              //  TCS Development Team     20 Jun, 2018         Initial creation
              //
              ===========================================================================
              //ENDFUNCDOC   ***/
              static GET_TC_ProjectUnqPtr find ( const string );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getInstance (tTag)
             //
             //   Purpose :   Method to get the instance of this class using tag_t
             //
             //   Inputs  :   tTag - tag of the object
             //
             //   Outputs :   none
             //
             //   Return  :   The GET_TC_Project Smart Pointer Instance for the given tag
             //
             //   History :
             //      Who                    Date                 Description
             //  TCS Development Team     21 Jun, 2017         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_TC_ProjectUnqPtr getInstance ( const tag_t );

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
             //   Return  :   The GET_TC_Project Smart Pointer Instance for the given UID
             //
             //     History:
             //      Who                    Date                 Description
             //  TCS Development Team     21 Jun, 2017         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_TC_ProjectUnqPtr getInstance ( const string );
    };
}

#endif // GET_TC_PROJECT_HXX
