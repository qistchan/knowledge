
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ReleaseStatus.hxx
//
//    Purpose:   Prototype for the functions dealing with release status.
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016           Initial creation
//  TCS Development Team     18 Oct, 2017           setEffectivity()
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_RELEASESTATUS_H_INCLUDED
#define GET_RELEASESTATUS_H_INCLUDED

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_POM_object.hxx>
#include <GET_WorkspaceObject.hxx>

//TC Includes
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_ReleaseStatusUnqPtr unique_ptr<GET_ReleaseStatus>
    #define GET_ReleaseStatusShrPtr shared_ptr<GET_ReleaseStatus>
}

namespace get
{
    class DLLEXPORT GET_ReleaseStatus : public GET_POM_object
    {
        public:
            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   GET_ReleaseStatus()
             //
             //   Purpose :   Constructor for the GET_ReleaseStatus class. Initializes
             //               the class with the given tag value
             //
             //   Inputs  :   tTag - The tag of the Release Status Object (tag_t)
             //
             //   Outputs :   none
             //
             //   Return  :   none
             //
             //   History :
             //    Who                   Date                 Description
             //    TCS Dev Team          9 Mar, 2016          Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_ReleaseStatus ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   ~GET_ReleaseStatus()
            //
            //   Purpose :   Destructor for the GET_ReleaseStatus class.
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //    Who                   Date                 Description
            //    TCS Dev Team          9 Mar, 2016          Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            virtual ~GET_ReleaseStatus();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getStatusName()
            //
            //   Purpose :   Method to get the Release Status Name of this Teamcenter
            //               Release Status Object
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The Release Status Name of this Object (string)
            //
            //   History :
            //    Who                   Date                 Description
            //    TCS Dev Team          9 Mar, 2016          Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
    	    string getStatusName();

    	    /*STARTFUNCDOC ***
    	    //
    	    ===========================================================================
    	    //   Function:   addStatus()
    	    //
    	    //   Purpose :   Method to add the Release Status Name of this Teamcenter
    	    //               Release Status Object
    	    //
    	    //   Inputs  :   iCount   - Number of objects to add release status(int)
    	    //               wso      - Workspace object(GET_WorkspaceObject*)
    	    //               retainDR - To retain date released(logical)
    	    //
    	    //   Outputs :   none
    	    //
    	    //   Return  :   none
    	    //
    	    //   History :
    	    //    Who                   Date                 Description
    	    //    TCS Dev Team          9 Mar, 2016          Initial creation
    	    //
    	    ===========================================================================
    	    //ENDFUNCDOC   ***/
    	    void addStatus ( const vector<GET_WorkspaceObjectShrPtr> vWSO, const bool &retainDR = true );

    	    /*STARTFUNCDOC ***
    	    //
    	    ===========================================================================
    	    //   Function:   createStatus()
    	    //
    	    //   Purpose :   Method to create the Release Status Instance for this Teamcenter
    	    //               Release Status Object
    	    //
    	    //   Inputs  :   sStatusType - The type of the Release status to be created(string)
    	    //
    	    //   Outputs :   none
    	    //
    	    //   Return  :   The GET_ReleaseStatus Smart Pointer instance of the newly create Status Object
    	    //
    	    //   History :
    	    //    Who                   Date                 Description
    	    //    TCS Dev Team          9 Mar, 2016          Initial creation
    	    //
    	    ===========================================================================
    	    //ENDFUNCDOC   ***/
    	    static GET_ReleaseStatusUnqPtr createStatus ( const string );

    	    /*STARTFUNCDOC ***
    	    //
    	    ===========================================================================
    	    //   Function:   getInstance (tTag)
    	    //
    	    //   Purpose :   Method to get the instance of this class using tag_t
    	    //
    	    //   Inputs  :   tTag - tag of the Release Status
    	    //
    	    //   Outputs :   none
    	    //
    	    //   Return  :   The GET_ReleaseStatus Smart Pointer object is returned
    	    //
    	    //   History :
    	    //      Who                    Date                 Description
    	    //   TCS Development Team     4 May, 2016         Initial creation
    	    //
    	    ===========================================================================
    	    //ENDFUNCDOC   ***/
    	    static GET_ReleaseStatusUnqPtr getInstance ( const tag_t );

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
    	    //   Return  :   The GET_ReleaseStatus Smart Pointer object is returned
    	    //
    	    //   History:
    	    //      Who                    Date                 Description
    	    //   TCS Development Team     11 Apr, 2016         Initial creation
    	    //
    	    ===========================================================================
    	    //ENDFUNCDOC   ***/
    	    static GET_ReleaseStatusUnqPtr getInstance ( const string );

    	    /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   find (string)
            //
            //   Purpose :   Method to get the instance of this class using tag_t
            //
            //   Inputs  :   string - Release Status name
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_ReleaseStatus Smart Pointer object is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     07 Oct, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_ReleaseStatusUnqPtr find ( const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   setEffectivity()
			 //
			 //   Purpose :   Method to set effectivity on Release Status object
			 //
			 //   Inputs  :   const string
			 //
			 //   Outputs :   None
			 //
			 //   Return  :   None
			 //
			 //   History :
			 //      Who                    Date                 Description
			 //  TCS Development Team     18 Oct, 2017         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
             GET_POM_objectUnqPtr setEffectivity ( const string );

        private:
            string statusName;
    };
}

#endif // GET_RELEASESTATUS_H_INCLUDED
