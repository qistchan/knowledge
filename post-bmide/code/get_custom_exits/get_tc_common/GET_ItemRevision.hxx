
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ItemRevision.hxx
//
//    Purpose:   Class for dealing with itemRevision objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     18 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_ITEM_REVISION_HXX
#define GET_ITEM_REVISION_HXX

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>
#include <GET_BOMViewRevision.hxx>
#include <GET_Dataset.hxx>
#include <GET_Participant.hxx>

//CPP Includes
#include <sstream>
#include <string>
#include <vector>
#include <map>

// Smart Pointer Definition
namespace get
{
    #define GET_ItemRevisionUnqPtr unique_ptr<GET_ItemRevision>
    #define GET_ItemRevisionShrPtr shared_ptr<GET_ItemRevision>
}

namespace get
{
    class GET_Item;
    //class GET_BOMViewRevision;
    class DLLEXPORT GET_ItemRevision : public GET_WorkspaceObject
    {
        private:
            string sItemID;
            string sRevID;

        public:

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_ItemRevision
			 //
			 //    Purpose:   Constructor for the class GET_ItemRevision
			 //
			 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
			 //               tTag    - The Tag of this Teamcenter Item Revision Object
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
            GET_ItemRevision ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_ItemRevision
			 //
			 //    Purpose:   Destructor for the class GET_ItemRevision
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
            virtual ~GET_ItemRevision();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getItem()
			 //
			 //    Purpose:   Get item of this item revision
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_Item Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     18 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            unique_ptr<GET_Item> getItem();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   find()
			 //
			 //    Purpose:   Find item revision by itemID and revID
			 //
			 //     Inputs:   sItemID - Item ID to search for (string)
			 //               sRevID  - revID RevisionID to search for
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_ItemRevision Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     18 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ItemRevisionUnqPtr find ( const string, const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getBVRs()
			 //
			 //    Purpose:   Get BVRs of this item revision
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   map - BVR Map (Key: View type | Value: GET_BOMViewRevisionUnqPtr object)
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     18 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            map<string, GET_BOMViewRevisionShrPtr> getBVRs();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getBVR()
			 //
			 //    Purpose:   Get the given BVR of this item revision
			 //
			 //     Inputs:   sViewType- string View type for which the BVR to be returned (by default the value is "view")
			 //
			 //    Outputs:   none
			 //
			 //     Return:   GET_BOMViewRevision Smart Pointer object is returned.
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     18 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_BOMViewRevisionUnqPtr getBVR ( const string &sViewType = "view" );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getParticipants()
             //
             //    Purpose:   Get the Assigned Participants for this Item Revision given the Participant Names
             //
             //     Inputs:   vParticipantNames - A vector of Participant Names whose assigned Participants are required
             //
             //    Outputs:   none
             //
             //     Return:   A Map with the Key as Participant Name and the GET_Participant Smart Pointer instance as value
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     09 May, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            map<string, vector<GET_ParticipantShrPtr> > getParticipants ( const vector<string> vParticipantNames );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getAllParticipants()
             //
             //    Purpose:   Get All the Assigned Participants for this Item Revision
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   A Map with the Key as Participant Name and a vector of GET_Participant Smart Pointer instances as value
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     09 May, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            map<string, vector<GET_ParticipantShrPtr> > getAllParticipants();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getRevId()
			 //
			 //    Purpose:   Method to get the Item Revision ID of this ItemRevision
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The Revision ID of this Item Revision (string)
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     18 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            string getRevId();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getId()
			 //
			 //    Purpose:   Method to get the Item ID
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The Item ID of this Item Revision (string)
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     18 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            string getId();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:  findByAttributes()
			 //
			 //    Purpose:   Find item revisions by given name and value pair of attributes
			 //
			 //     Inputs:   mAttributes - map of name and value pair of attributes
			 //               mRevId      - Revision ID
			 //
			 //    Outputs:   none
			 //
			 //     Return:   Vector - vector of GET_ItemRevision Smart Pointer objects
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     21 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static vector<GET_ItemRevisionUnqPtr> findByAttributes ( const map<string, string>, const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:  setRevisionID()
			 //
			 //    Purpose:  Sets the Revision id for this ItemRevision
			 //
			 //     Inputs:  sNewId  - Revision ID to be set (string)
			 //
			 //    Outputs:  none
			 //
			 //     Return:  none
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     21 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual void setRevisionId ( const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   revise()
			 //
			 //    Purpose:   Revises item revision
			 //
			 //     Inputs:   sRevID - The new Revision ID to be set for the revise operation
			 //
			 //    Outputs:   none
			 //
			 //     Return:   GET_ItemrevisionUnqPtr - The new Item Revision Smart Pointer Object from the revise operation
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     22 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual GET_ItemRevisionUnqPtr revise ( const string &sRev = "" );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   baseline()
             //
             //    Purpose:   Creates a baseline for this Item Revision
             //
             //     Inputs:   sBaselineRevId - The new Baseline Revision ID to be set. Optional,  if not provided will be auto-generated by the system (string)
             //               sBaselineDesc - The Description to be set for the Baseline Revision (string)
             //               sBaselineTemplateName - The Workflow Template to be used for the Baseline process (string)
             //               sJobName - The Baseline Job Name. If empty string is provided, the code will generate a Job name (string)
             //               sJobDesc - The Baseline Job Description (string)
             //
             //    Outputs:   none
             //
             //     Return:   GET_ItemrevisionUnqPtr - The new Baseline Item Revision Smart Pointer Object from the Baseline operation
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     08 Jul, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            virtual GET_ItemRevisionUnqPtr baseline ( const string, const string, const string, const string, const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getBaseRev ()
			 //
			 //    Purpose:   Method to get the Base rev of given baselined revision
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_ItemRevision Smart Pointer of base rev is returned if instance is baselined rev else, NULLTAG is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     30 Sep, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			GET_ItemRevisionUnqPtr getBaseRev();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance ( tTag )
			 //
			 //    Purpose:   Method to get the instance of this class using tag_t
			 //
			 //     Inputs:   tTag - tag of the object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_ItemRevision Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ItemRevisionUnqPtr getInstance ( const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance ( sUID )
			 //
			 //    Purpose:   Method to get the instance of this class using string UID
			 //
			 //     Inputs:   sUID - UID as string
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_ItemRevision Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ItemRevisionUnqPtr getInstance ( const string );
    };
}

#endif // GET_ITEM_REVISION_HXX
