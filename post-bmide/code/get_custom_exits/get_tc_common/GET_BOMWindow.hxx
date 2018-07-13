
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_BOMWindow.hxx
//
//    Purpose:   Header class for dealing with the BOMWindow
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     1 Mar, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_BOM_OBJECT_HXX
#define GET_BOM_OBJECT_HXX

//GE CPP Includes
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
#include <GET_BOMLine.hxx>
#include <GET_RevisionRule.hxx>

// Smart Pointer Definition
namespace get
{
    #define GET_BOMWindowUnqPtr unique_ptr<GET_BOMWindow>
    #define GET_BOMWindowShrPtr shared_ptr<GET_BOMWindow>
}

namespace get
{
    class DLLEXPORT GET_BOMWindow : GET_RuntimeBusinessObject
    {
        private:
            bool isWindowClosed;

        public:

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_BOMWindow()
			 //
			 //    Purpose:   Constructor method for the GET BOM Window Class
			 //
			 //     Inputs:   enDummy - A dummy enum value that is not accessible outside this hierarchy (GET_DUMMY)
			 //               tTag    - Tag of the BOM Window object (tag_t)
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     1 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_BOMWindow ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_BOMWindow()
			 //
			 //    Purpose:   Destructor method for the GET BOM Window Class. Closes
			 //               the underlying BOM Window.
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     1 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual ~GET_BOMWindow ();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   create()
             //
             //    Purpose:   Method to create a new instance of Teamcenter BOM Window
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   A GET_BOMWindow Smart Pointer of the newly created BOM Window Instance
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     1 Mar, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_BOMWindowUnqPtr create();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   setRevisionRule()
             //
             //    Purpose:   Method to set the Revision Rule for this BOM Window
             //
             //     Inputs:   sRevRuleName - The Revision Rule Name to be set
             //
             //    Outputs:   none
             //
             //     Return:   none
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     05 Jul, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            void setRevisionRule ( const string );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   setRevisionRule()
             //
             //    Purpose:   Method to set the Revision Rule for this BOM Window
             //
             //     Inputs:   revRulePtr - The Smart Pointer Representation of the Teamcenter Revision Rule
             //
             //    Outputs:   none
             //
             //     Return:   none
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     05 Jul, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            void setRevisionRule ( const GET_RevisionRuleShrPtr );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   setTopLine()
			 //
			 //    Purpose:   Method to set the Window Top Line in this BOM Window Instance
			 //
			 //     Inputs:   itemRevPtr    - The Smart PointerRepresentation of the ItemRevision
			 //                               instance to be set as the top line
			 //               bomViewRevPtr - The Smart Pointer Representation of the BOMViewRevision
			 //                               (Optional - Can also be a null pointer)
			 //
			 //    Outputs:   none
			 //
			 //     Return:   A GET_BOMLine Smart Pointer representation for the BOM Window Top Line
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     1 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_BOMLineUnqPtr setTopLine ( shared_ptr<GET_ItemRevision>, shared_ptr<GET_BOMViewRevision> );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   baseline()
             //
             //    Purpose:   Method to create baseline for the structure loaded in this BOM Window
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
            GET_ItemRevisionUnqPtr baseline ( const string, const string, const string, const string, const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getTopLine()
			 //
			 //    Purpose:   Method to get the top line of this BOM Window Instance
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   A GET_BOMLine Smart Pointer representation for the BOM Window Top Line
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     1 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_BOMLineUnqPtr getTopLine();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   save()
			 //
			 //    Purpose:   Method to  save the underlying BOM Window Instance
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     1 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            void save();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   close()
			 //
			 //    Purpose:   Method to close the BOM Structure window
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     1 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            void close();
    };
}

#endif // GET_BOM_OBJECT_HXX
