
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_TC_Project.cxx
 //
 //    Purpose:   Class for dealing with TC_Project objects
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     21 Jun, 2016         Initial creation
 //  TCS Development Team     20 Jun, 2018         Added assignProjectToItem()
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_POM_user.hxx>
#include <GET_POM_group.hxx>

//TC Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/tctype.h>
#include <tccore/workspaceobject.h>
#include <tccore/grm.h>
#include <cxpom/cxpom_errors.h>
#include <tccore/item.h>
#include <res/reservation.h>
#include <base_utils/ResultCheck.hxx>

#include <GET_TC_Project.hxx>

const string logger = "get.get_tc_common.TC_Project";

namespace get
{
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
    GET_TC_Project::GET_TC_Project ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_application_object ( enDummy, tTag )
    {
        LOG_TRACE ( logger, "START : GET_TC_Project::GET_TC_Project" );

        char *pcProjId   = NULL;
        char *pcProjName = NULL;
        char *pcProjDesc = NULL;

        ResultCheck stat;

        stat = AOM_ask_value_logical ( tTag, PROJECT_IS_ACTIVE_ATTR , &bIsProjectActive );

        stat = AOM_ask_value_logical ( tTag, PROJECT_IS_VISIBLE_ATTR , &bIsProjectVisible );

        stat = AOM_ask_value_logical ( tTag, PROJ_PROGRAM_SECURITY_ATTR , &bIsProjectProgramSecured );

        stat = AOM_ask_value_string	( tTag, PROJECT_ID_ATTR , &pcProjId );
        sProjectId = pcProjId;
        MEM_free ( pcProjId );

        stat = AOM_ask_value_string ( tTag, PROJECT_NAME_ATTR ,&pcProjName );
        sProjectName = pcProjName;
        MEM_free ( pcProjName );

        stat = AOM_ask_value_string ( tTag, PROJECT_DESC_ATTR ,&pcProjDesc );
        sProjectDesc = pcProjDesc;
        MEM_free ( pcProjDesc );

        LOG_TRACE ( logger, "END : GET_TC_Project::GET_TC_Project" );
    }

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
    GET_TC_ProjectUnqPtr GET_TC_Project::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_TC_Project::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, "TC_Project" ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + "TC_Project";
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_TC_Project::getInstance(tTag)" );

        return make_unique<GET_TC_Project> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //   Return  :   The GET_TC_Project Smart Pointer Instance for the given UID
     //
     //     History:
     //      Who                    Date                 Description
     //  TCS Development Team     21 Jun, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_TC_ProjectUnqPtr GET_TC_Project::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_TC_Project::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_TC_Project::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }

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
    GET_TC_Project::~GET_TC_Project(){}

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
    bool GET_TC_Project::isProjectActive()
    {
        return bIsProjectActive;
    }

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
    bool GET_TC_Project::isProjectVisible()
    {
       return bIsProjectVisible;
    }

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
    bool GET_TC_Project::isProjectProgramSecured()
    {
        return bIsProjectProgramSecured;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getProjectId()
     //
     //   Purpose :   Method to get project ID or not
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
    string GET_TC_Project::getProjectId()
    {
        return sProjectId;
    }

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
    string GET_TC_Project::getProjectName()
    {
        return sProjectName;
    }

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
    string GET_TC_Project::getProjectDesc()
    {
        return sProjectDesc;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   AssignProjectToItem()
    //
    //   Purpose :   Method to assign Projects
    //
    //   Inputs  :   none
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
    void GET_TC_Project::assignProjectToItem ( vector<GET_TC_ProjectShrPtr> vProjects, vector<GET_WorkspaceObjectShrPtr> vObjects )
    {
	    ResultCheck stat;
	    tag_t* tProjects = NULL;
	    tag_t* tObjects = NULL;

	    if ( vProjects.size() > 0 && vObjects.size() > 0 )
	    {
	        tProjects = ( tag_t * ) MEM_alloc ( sizeof ( tag_t ) * vProjects.size() );
	        tObjects = ( tag_t * ) MEM_alloc ( sizeof ( tag_t ) * vObjects.size() );

	        for ( int iInx = 0; iInx < vProjects.size(); iInx++ )
	        {
		        tProjects[iInx] = vProjects[iInx]->getTag();
		        tObjects[iInx] = vObjects[iInx]->getTag();
	        }

	        stat = PROJ_assign_objects ( vProjects.size(), tProjects, vObjects.size(), tObjects );
	    }
	    else
	    {
	    	string sMsg;

	    	if ( vProjects.size() > 0 )
		    {
			    sMsg = string ("The number of projects is zero.");
		    }
		    THROW ( sMsg );
	    }

	   if ( tProjects != NULL )
	   {
           MEM_free ( tProjects );
	   }
	   if ( tObjects != NULL )
	   {
           MEM_free ( tObjects );
	   }
    }

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
     GET_TC_ProjectUnqPtr GET_TC_Project::find ( const string sProjectID )
     {
         GET_TC_ProjectUnqPtr projUnqPtr;

         ResultCheck stat;

         tag_t tProjectTag = NULLTAG;

         LOG_TRACE ( logger, "START : GET_Item::find" );

         stat = PROJ_find ( sProjectID.c_str(), &tProjectTag);

         if ( tProjectTag != NULLTAG )
         {
     	    projUnqPtr = make_unique<GET_TC_Project> ( GET_DUMMY::GET_DUMMY_VALUE, tProjectTag );
         }
         else
         {
             string sMsg = "Cannot find the project for " + sProjectID;
             THROW ( sMsg );
         }
         LOG_TRACE ( logger, "END : GET_TC_Project::find" );

         return projUnqPtr;
     }

}
