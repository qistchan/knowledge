
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Item.hxx
//
//    Purpose:   Header class for dealing with item objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     9 Mar, 2016           Initial creation
//  TCS Development Team     9 May, 2018         Added getLatestReleasedRevision
//  TCS Development Team    20 Jun, 2018         Added method to get naming pattern
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_ITEM_HXX
#define GET_ITEM_HXX

//CPP Includes
#include <string>
#include <vector>

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_BOMView.hxx>

//Teamcenter includes
#include <property/nr.h>

// Smart Pointer Definition
namespace get
{
    #define GET_ItemUnqPtr unique_ptr<GET_Item>
    #define GET_ItemShrPtr shared_ptr<GET_Item>
}

namespace get
{
    class DLLEXPORT GET_Item : public GET_WorkspaceObject
    {
        private:
            string sItemID;

        public:
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   GET_Item ( const GET_DUMMY, const tag_t )
            //
            //   Purpose :   Constructor for the class GET_Item
            //
            //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
            //               tTag    - The Tag of this Teamcenter Item Object
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
            GET_Item ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   ~GET_Item()
            //
            //   Purpose :   Destructor for the class GET_Item
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
            virtual ~GET_Item();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getInstance ( tTag )
             //
             //   Purpose :   Method to get the instance of this class using tag_t
             //
             //   Inputs  :   tTag - tag of the object
             //
             //   Outputs :   none
             //
             //   Return  :   The GET_Item Smart Pointer object is returned
             //
             //   History :
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_ItemUnqPtr getInstance ( const tag_t );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getInstance ( sUID )
             //
             //    Purpose:   Method to get the instance of this class using string UID
             //
             //    Inputs:    sUID - UID as string
             //
             //    Outputs:   None
             //
             //    Return:    The GET_Item Smart Pointer object is returned
             //
             //     History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_ItemUnqPtr getInstance ( const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getRevisions()
            //
            //   Purpose :   Method to get all revisions for this item
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   Vector of ItemRevisions associated with item (vector<GET_ItemRevisionUnqPtr>)
            //
            //   History :
            //    Who                   Date                 Description
            //    TCS Dev Team          9 Mar, 2016          Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_ItemRevisionUnqPtr> getRevisions() const;

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   find()
            //
            //   Purpose :   Method to find an item which matches the given item id
            //
            //   Inputs  :   sItemID - Item ID to find (string)
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_Item Smart Pointer Object matching the given Item ID
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     9 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_ItemUnqPtr find ( const string sItemID );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getId()
            //
            //   Purpose :   Method to get an itemID
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The Item id of this Item(string)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     23 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            string getId();

             /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   findRevision()
             //
             //   Purpose :   Method to find item revision within this item
             //
             //   Inputs  :   sRevID - Revision ID to be found within this Item (string)
             //
             //   Outputs :   none
             //
             //   Return  :   The Item Revision Smart Pointer Object for the given revision id
             //
             //   History :
             //      Who                   Date                 Description
             //  TCS Development Team     23 Mar, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_ItemRevisionUnqPtr findRevision ( const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   findRevisions()
            //
            //   Purpose :   Method to find item revisions matching the given revision id within this item
            //
            //   Inputs  :   sRevID - Revision ID to be matched within this Item (string)
            //
            //   Outputs :   none
            //
            //   Return  :   The Item Revision Smart Pointer instances for the matching Revision ids(vector<GET_ItemRevisonUnqPtr>)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     9 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_ItemRevisionUnqPtr> findRevisions ( const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getLatestRevision()
            //
            //   Purpose :   Method to get Latest Revision
            //
            //   Inputs  :   none
            //
            //   Outputs :   revTag - Revision tag found for the item (tag_t)
            //
            //   Return  :   The GET_Item smart pointer is returned
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     9 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            GET_ItemRevisionUnqPtr getLatestRevision() const;

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getLatestReleasedRevision()
            //
            //   Purpose :   Method to get Latest Released Revision
            //
            //   Inputs  :   none
            //
            //   Outputs :   revTag - Revision tag found for the item (tag_t)
            //
            //   Return  :   The GET_ItemRevision smart pointer is returned
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     9 May, 2018         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            GET_ItemRevisionUnqPtr getLatestReleasedRevision() const;

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:  getBomViews()
            //
            //   Purpose :  Method to get bomviews attached to this Item
            //
            //   Inputs  :  none
            //
            //   Outputs :  none
            //
            //   Return  :  map with View Name and GET_BOMView Smart Pointer Objects (map<string, GET_BomBViewUnqPtr)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     28 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            map<string, GET_BOMViewShrPtr> getBomViews();

             /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getBomView()
             //
             //   Purpose :   Method to get a given bom view from this Item
             //
             //   Inputs  :   sViewType - The View Type of the BOM View to be retrieved
             //
             //   Outputs :   none
             //
             //   Return  :   The GET_BOMView Smart Pointer object is returned
             //
             //   History :
             //      Who                   Date                 Description
             //  TCS Development Team     28 Mar, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_BOMViewUnqPtr getBomView ( const string );

            /*STARTFUNCDOC ***
		    //
		    ===========================================================================
		    //   Function:   getNRPatternNextValue()
		    //
		    //   Purpose :   Method to get naming pattern
		    //
		    //   Inputs  :   sViewType - The View Type of the BOM View to be retrieved
		    //
		    //   Outputs :   none
		    //
		    //   Return  :   The GET_BOMView Smart Pointer object is returned
		    //
		    //   History :
		    //      Who                   Date                 Description
		    //  TCS Development Team     20 Jun, 2018         Initial creation
		    //
		    ===========================================================================
		    //ENDFUNCDOC   ***/
            static string getNRPatternNextValue ( const string, const string, tag_t, const string, const string, const string, tag_t, const string, const string, const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   create()
            //
            //   Purpose :   Method to create Item
            //
            //   Inputs  :   sItemType        - Item type for which item to be created(const string)
            //               sItemID          - Item ID(const string)
            //               sItemName        - Name of the item(const string)
            //               sRevID           - Revision ID of the item(const string)
            //               sItemDescription - Description of the item(const string)
            //
            //   Outputs :   none
            //
            //   Return  :   GET_Item - Item instance created (GET_Item*)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     14 Mar, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_ItemUnqPtr create ( const string, const string , const string, const string, const string );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getNewRevId()
             //
             //   Purpose :   Method to generate new revision id for the given item of given type
             //
             //   Inputs  :   tItemTag - The View Type of the BOM View to be retrieved
             //               tItemType - Tag of item type
             //
             //   Outputs :   none
             //
             //   Return  :   string - new revision id
             //
             //   History :
             //      Who                   Date                 Description
             //  TCS Development Team     03 Oct, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static string getNewRevId ( const tag_t tItemTag, const tag_t tItemType );
    };
}

#endif // GET_ITEM_HXX
