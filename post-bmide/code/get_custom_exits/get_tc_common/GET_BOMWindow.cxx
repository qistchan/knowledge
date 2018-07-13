/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_BOMWindow.cxx
//
//    Purpose:   class for dealing with the GET_BOMWindow class
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     1 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE CPP Includes
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <mld/journal/journal.h>
#include <sa/am.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// GE Teamcenter Includes
#include <GET_BOMWindow.hxx>
#include <GET_BOMViewRevision.hxx>

const string logger = "get.ge_tc_common.GET_BOMWindow";

namespace get
{
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
    GET_BOMWindow::GET_BOMWindow ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_RuntimeBusinessObject ( enDummy, tTag )
    {
        LOG_TRACE ( logger, "START : GET_BOMWindow::GET_BOMWindow" );

        isWindowClosed = false;

        LOG_TRACE ( logger, "END : GET_BOMWindow::GET_BOMWindow" );
    }

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
    GET_BOMWindow::~GET_BOMWindow()
    {
        LOG_TRACE ( logger, "START : GET_BOMWindow::~GET_BOMWindow" );

        close();

        LOG_TRACE ( logger, "END : GET_BOMWindow::~GET_BOMWindow" );
    }

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
    GET_BOMWindowUnqPtr GET_BOMWindow::create()
    {
        ResultCheck stat;

        tag_t tBomWindow = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMWindow::create" );

        stat = BOM_create_window ( &tBomWindow );

        LOG_TRACE ( logger, "END : GET_BOMWindow::create" );

        return make_unique<GET_BOMWindow> ( GET_DUMMY::GET_DUMMY_VALUE, tBomWindow );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setRevisionRule()
     //
     //    Purpose:   Method to set the Revision Rule for this BOM Window
     //
     //     Inputs:   sRevRuleName - The Revision Rule Name to be set (string)
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
    void GET_BOMWindow::setRevisionRule ( const string sRevRuleName )
    {
        GET_RevisionRuleUnqPtr revRuleUnqPtr;
        GET_RevisionRuleShrPtr revRuleShrPtr;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_BOMWindow::setRevisionRule(string)" );

        // Validate the Revision Rule
        revRuleUnqPtr = GET_RevisionRule::find ( sRevRuleName );
        if ( revRuleUnqPtr.get() == NULL )
        {
            THROW ( "\"" + sRevRuleName + "\" is not a valid Teamcenter Revision Rule" );
        }

        // Set the Revision Rule to the current BOM Window Instance
        revRuleShrPtr = move ( revRuleUnqPtr );
        setRevisionRule ( revRuleShrPtr );

        LOG_TRACE ( logger, "END : GET_BOMWindow::setRevisionRule(string)" );
    }

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
    void GET_BOMWindow::setRevisionRule ( const GET_RevisionRuleShrPtr revRulePtr )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_BOMWindow::setRevisionRule(GET_RevisionRuleShrPtr)" );

        stat = BOM_set_window_config_rule ( _tag, revRulePtr->getTag() );

        LOG_TRACE ( logger, "END : GET_BOMWindow::setRevisionRule(GET_RevisionRuleShrPtr)" );
    }

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
    GET_BOMLineUnqPtr GET_BOMWindow::setTopLine ( GET_ItemRevisionShrPtr itemRevPtr, GET_BOMViewRevisionShrPtr bomViewRevPtr )
    {
        ResultCheck stat;

        tag_t tTopLine = NULLTAG;
        tag_t tBVR = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMWindow::setTopLine" );

        if ( bomViewRevPtr.get() != NULL )
        {
            tBVR = bomViewRevPtr->getTag();
        }
        stat = BOM_set_window_top_line ( this->getTag(), NULLTAG, itemRevPtr->getTag(), tBVR, &tTopLine );

        LOG_TRACE ( logger, "END : GET_BOMWindow::setTopLine" );

        return make_unique<GET_BOMLine> ( GET_DUMMY::GET_DUMMY_VALUE, tTopLine );
    }

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
    GET_ItemRevisionUnqPtr GET_BOMWindow::baseline ( const string sBaselineRevId, const string sBaselineDesc, const string sBaselineTemplateName,
                                                     const string sJobName, const string sJobDesc )
    {
        GET_BOMLineUnqPtr topBOMLinePtr;

        GET_ItemRevisionUnqPtr itemRevPtr;
        GET_ItemRevisionUnqPtr topLineRevPtr;

        ResultCheck stat;

        string sJobTempName = sJobName;

        tag_t tBaselineRev = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMWindow::baseline" );

        // Get the top BOM Line of the current BOM Window Instance
        topBOMLinePtr = getTopLine();
        if ( topBOMLinePtr.get() == NULL )
        {
            THROW ( "No BOM Structure is loaded in this BOM Window" );
        }
        topLineRevPtr = topBOMLinePtr->getItemRevision();

        // Construct the Job Name if its empty
        if ( sJobTempName.empty() )
        {
            sJobTempName = "Baseline_" + topLineRevPtr->getId() + "_" + topLineRevPtr->getRevId() + "." + sBaselineRevId;
        }

        // Create the Baseline revision for the current Item Revision instance
        stat = BOM_create_baseline ( _tag, sBaselineRevId.c_str(), sBaselineDesc.c_str(), sBaselineTemplateName.c_str(), sJobTempName.c_str(), sJobDesc.c_str(), &tBaselineRev );

        // Construct a Smart Pointer for the new Baseline Item Revision
        itemRevPtr = GET_ItemRevision::getInstance ( tBaselineRev );

        LOG_TRACE ( logger, "END : GET_BOMWindow::baseline" );

        return itemRevPtr;
    }

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
    GET_BOMLineUnqPtr GET_BOMWindow::getTopLine()
    {
        ResultCheck stat;

        tag_t tTopLine = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMWindow::getTopLine" );

        stat = BOM_ask_window_top_line ( this->getTag(), &tTopLine );

        LOG_TRACE ( logger, "END : GET_BOMWindow::getTopLine" );

        return make_unique<GET_BOMLine> ( GET_DUMMY::GET_DUMMY_VALUE, tTopLine );
    }

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
    void GET_BOMWindow::save()
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_BOMWindow::save" );

        stat = BOM_save_window ( this->getTag() );

        LOG_TRACE ( logger, "END : GET_BOMWindow::save" );
    }

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
    void GET_BOMWindow::close()
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_BOMWindow::close" );

        if ( ! isWindowClosed )
        {
            stat = BOM_close_window ( this->getTag() );
            isWindowClosed = true;
        }

        LOG_TRACE ( logger, "END : GET_BOMWindow::close" );
    }
}
