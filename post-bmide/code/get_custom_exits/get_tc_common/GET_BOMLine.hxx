
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_BOMLine.hxx
 //
 //    Purpose:   Header class for dealing with the BOMLine
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     1 Mar, 2016           Initial creation
 //  TCS Development Team     14 Mar, 2017          Added getItem() method
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

#ifndef GET_BOM_LINE_HXX
#define GET_BOM_LINE_HXX

// GE CPP Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// CPP Includes
#include <string>
#include <vector>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <bom/bom.h>
#include <tc/tc.h>

// GE Teamcenter Includes
#include <GET_RuntimeBusinessObject.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Item.hxx>

// Smart Pointer Definition
namespace get
{
    #define GET_BOMLineUnqPtr unique_ptr<GET_BOMLine>
    #define GET_BOMLineShrPtr shared_ptr<GET_BOMLine>
}

namespace get
{
    class DLLEXPORT GET_BOMLine : public GET_RuntimeBusinessObject
    {
        public:

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   GET_BOMLine()
             //
             //    Purpose:   Constructor method for the GET BOM Line class. Creates the
             //               BOM Line Instance with the given BOMLine tag
             //
             //     Inputs:   enDummy - A dummy enum value that is not accessible outside this hierarchy (GET_DUMMY)
             //               tTag    - Tag of the BOMLine to create the Instance
             //
             //    Outputs:   none
             //
             //     Return:   none
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     11 Feb, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_BOMLine ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   ~GET_BOMLine()
             //
             //    Purpose:   Destructor for the class GET_BOMLine
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
            virtual ~GET_BOMLine ();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getChildren()
             //
             //    Purpose:   Method to get children of the BOM Line
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   A vector containing the GET_BOMLine Smart Pointer instances of
             //               the Child Lines
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     11 Feb, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            vector<GET_BOMLineUnqPtr> getChildren();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getItem()
             //
             //    Purpose:   Method to get the Item instance from the underlying BOMLine instance
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Smart Pointer representation for the Item instance
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team      14 Mar, 2017         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_ItemUnqPtr getItem();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getItemRevision()
             //
             //    Purpose:   Method to get the ItemRevision instance from the underlying BOMLine instance
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Smart Pointer representation for the ItemRevision instance
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     11 Feb, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_ItemRevisionUnqPtr getItemRevision();

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
             //     Return:   The GET_BOMLine Smart Pointer object is returned
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_BOMLineUnqPtr getInstance ( const tag_t ); 
    };
}

#endif // GET_BOM_LINE_HXX
