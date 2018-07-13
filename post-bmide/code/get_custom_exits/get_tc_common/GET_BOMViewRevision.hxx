
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_BOMViewRevision.hxx
//
//    Purpose:   Header class for dealing with GET_BOMViewRevision objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     12 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_BOMVIEWREVISION_HXX
#define GET_BOMVIEWREVISION_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>
#include <GET_PSOccurrence.hxx>
#include <GET_BOMView.hxx>

// CPP Includes
#include <string>
#include <vector>
#include <set>

//Teamcenter Includes
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_BOMViewRevisionUnqPtr unique_ptr<GET_BOMViewRevision>
    #define GET_BOMViewRevisionShrPtr shared_ptr<GET_BOMViewRevision>
}

namespace get
{
    class GET_ItemRevision;
    class DLLEXPORT GET_BOMViewRevision: public GET_WorkspaceObject
    {
        public:
             /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   GET_BOMViewRevision ( const GET_DUMMY, const tag_t )
             //
             //   Purpose :   Constructor for the class GET_BOMViewRevision
             //
             //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
             //               tTag - The Tag of this Teamcenter BOMView Object
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
            GET_BOMViewRevision ( const GET_DUMMY, const tag_t tag );

             /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   ~GET_BOMViewRevision()
             //
             //   Purpose :   Destructor for the class GET_BOMViewRevision
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
            virtual ~GET_BOMViewRevision();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getBomView ()
            //
            //   Purpose :   Method to get the instance of GET_BOMView using GET_BOMViewRevision
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_BOMView Smart Pointer object is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            GET_BOMViewUnqPtr getBomView();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getOccurrences()
            //
            //   Purpose :   Method to get the instance of GET_PSOccurrence from the BVR
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   vector of GET_PSOccurrence is returned(vector<GET_PSOccurrence*>)
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_PSOccurrenceUnqPtr> getOccurrences();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getViewType()
            //
            //   Purpose :   Method to get bomview type
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   BOMView type of the object (string)
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            string getViewType();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getChildren()
            //
            //   Purpose :   Method to traverse and retrieve the Child Item Revision from all levels
            //
            //   Inputs  :   none
            //
            //   Outputs :   The GET_WorkspaceObject Smart Pointer Instances of the Child Objects at the required levels for BOM View Revision
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void getChildren ( vector<GET_WorkspaceObjectShrPtr>&, const int &iLevel = 0 );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   isPrecise()
            //
            //   Purpose :   Method to know the bom view revision is precise or not
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   returns precise status, true or false(logical)
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            bool isPrecise();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   setImprecise()
            //
            //   Purpose :   Method to set the bom view revision ImPrecise status
            //
            //   Inputs  :   bIsSaveRequired - bool to indicate whether save of BVR is required or not (Default is true)
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void setImprecise ( const bool &bIsSaveRequired = true );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   setPrecise()
            //
            //   Purpose :   Method to set the bom view revision Precise status
            //
            //   Inputs  :   bIsSaveRequired - bool to indicate whether save of BVR is required or not (Default is true)
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void setPrecise ( const bool &bIsSaveRequired = true );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:  createOccurrence(const int, GET_ItemRevisionShrPtr, const bool&)
            //
            //   Purpose :  Method to set the bom view revision precise status
            //
            //   Inputs  :  n_occurrences   - number of occurrences to create(const int)
            //              itemRev         - The GET_ItemRevision Smart Pointer Object for which occurrence is created
            //              bIsSaveRequired - bool flag to indicate whether to save the BVR after occurrence creation (Default is true)
            //
            //   Outputs :  none
            //
            //   Return  :  Created occurrence list of the item revision (vector<GET_PSOccurrence*>)
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_PSOccurrenceUnqPtr> createOccurrence ( const int, shared_ptr<GET_ItemRevision>, const bool &bIsSaveRequired = true );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:  createBomViewRevision()
             //
             //   Purpose :  create BOMView Revision with the given inputs
             //
             //   Inputs  :  parentRevisionPtr - The Item Revision Parent
             //              sViewType - view type string
             //              bPrecise  - boolean value for precise
             //              sBvr_name - bom view revision name
             //              sBvr_desc - bom view revision description
             //
             //   Outputs :  none
             //
             //   Return  :  GET_BOMViewRevisionUnqPtr - GET_BOMViewRevision Smart Pointer Object
             //
             //   History :
             //     Who                   Date                 Description
             //   TCS Development Team     24 Mar, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_BOMViewRevisionUnqPtr createBOMViewRevision ( const shared_ptr<GET_ItemRevision>, const string &sViewType = "view", const bool &bPrecise = "false",
                                                                     const string &sBvrName = "", const string &sBvrDesc = "" );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getInstance (tTag)
            //
            //   Purpose :   Method to get the instance of this class using tag_t
            //
            //   Inputs  :   tTag - tag of the BVR
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_BOMViewRevision Smart Pointer object is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_BOMViewRevisionUnqPtr getInstance ( const tag_t );

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
             //   Return  :   The GET_BOMViewRevision Smart Pointer object is returned
             //
             //   History:
             //      Who                    Date                 Description
             //   TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_BOMViewRevisionUnqPtr getInstance ( const string );
    };
}

#endif // BOMVIEWREVISION_HXX
