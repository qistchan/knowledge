
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:    GET_BOMView.hxx
//
//    Purpose:   Class for dealing with  GET_BOMView objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     18 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/
#ifndef GET_BOMVIEW_HXX
#define GET_BOMVIEW_HXX

#include <GET_WorkspaceObject.hxx>

// Smart Pointer Definition
namespace get
{
    #define GET_BOMViewUnqPtr unique_ptr<GET_BOMView>
    #define GET_BOMViewShrPtr shared_ptr<GET_BOMView>
}

namespace get
{
    class GET_Item;
    class DLLEXPORT GET_BOMView: public GET_WorkspaceObject
    {
		public:

    	    /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_BOMView
			 //
			 //    Purpose:   Constructor for the class GET_BOMView
			 //
			 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
			 //               tTag - The Tag of this Teamcenter BOMView Object
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
    	    GET_BOMView ( const GET_DUMMY, const tag_t );

    	    /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_BOMView
			 //
			 //    Purpose:   Destructor for the class GET_BOMView
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
			virtual ~GET_BOMView();

			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getItem()
			 //
			 //    Purpose:   Method to get item from bomview
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   GET_ItemUnqPtr- Smart Pointer for GET_Item object
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     24 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			unique_ptr<GET_Item> getItem();

			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   createBomView()
			 //
			 //    Purpose:   Method to create bomview
			 //
			 //     Inputs:   itemPtr     - The Parent GET_Item Smart Pointer for this BOM View
			 //               sViewType   - ViewType of string to be provided
			 //               sViewname   - view name
			 //               sViewdesc   - view description
			 //               bCreateBvrs - true or false to create bomview revisions
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The newly created GET_BOMView Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     28 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			static GET_BOMViewUnqPtr createBOMView ( shared_ptr<GET_Item>, const string, const string &sViewname = "", const string &sViewdesc = "", const bool &bCreateBvrs = false, const bool &bPrecise = false );

			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getViewType()
			 //
			 //    Purpose:   Method to get view type
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   string- View Type as string
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     24 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			virtual string getViewType();

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
			 //     Return:   GET_BOMViewUnqPtr - Smart Pointer for GET_BOMView instance is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			static GET_BOMViewUnqPtr getInstance ( const tag_t );

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
			 //     Return:    GET_BOMViewUnqPtr - GSmart Pointer for GET_BOMView instance is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			static GET_BOMViewUnqPtr getInstance ( const string );
    };
}

#endif //GET_BOMVIEW_HXX
