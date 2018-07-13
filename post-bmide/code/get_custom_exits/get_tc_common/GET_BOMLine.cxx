
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_BOMLine.cxx
//
//    Purpose:   Class for dealing with the BOMLine
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016         Initial creation
//  TCS Development Team     14 Mar, 2017         Added getItem() method
//
//   ============================================================================
// ENDFILEDOC   ***/


// GE CPP Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

// CPP Includes
#include <vector>

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
#include <GET_BOMLine.hxx>

const string logger = "get_tc_common.GET_BOMLine";

namespace get
{
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
    GET_BOMLine::GET_BOMLine ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_RuntimeBusinessObject ( enDummy, tTag ) {}

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
    GET_BOMLine::~GET_BOMLine()
    {
    }

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
    vector<GET_BOMLineUnqPtr > GET_BOMLine::getChildren()
    {
        int iChildCount = 0;

        ResultCheck stat;

        tag_t *ptChildLines = NULL;

        vector<GET_BOMLineUnqPtr > vBomLineChildren;

        LOG_TRACE ( logger, "START : GET_BOMLine::getChildren()" );

        stat = BOM_line_ask_child_lines ( _tag, &iChildCount, &ptChildLines );
        for ( int iChildIdx = 0; iChildIdx < iChildCount; iChildIdx++ )
        {
            vBomLineChildren.push_back ( make_unique<GET_BOMLine> ( GET_DUMMY::GET_DUMMY_VALUE, ptChildLines[iChildIdx] ) );
        }
        MEM_free ( ptChildLines );

        LOG_TRACE ( logger, "END : GET_BOMLine::getChildren()" );

        return vBomLineChildren;
    }

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
    GET_ItemUnqPtr GET_BOMLine::getItem()
    {
        GET_ItemUnqPtr itemUnqPtr;

        ResultCheck stat;

        tag_t tItem = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMLine::getItem()" );

        stat = AOM_ask_value_tag ( _tag, bomAttr_lineItemTag, &tItem );
        if ( tItem != NULLTAG )
        {
            itemUnqPtr = GET_Item::getInstance ( tItem );
        }

        LOG_TRACE ( logger, "END : GET_BOMLine::getItem()" );

        return itemUnqPtr;
    }

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
    GET_ItemRevisionUnqPtr GET_BOMLine::getItemRevision()
    {
        GET_ItemRevisionUnqPtr itemRevUnqPtr;

        ResultCheck stat;

        tag_t tItemRev = NULLTAG;

        LOG_TRACE ( logger, "START : GET_BOMLine::getItemRevision()" );

        stat = AOM_ask_value_tag ( _tag, bomAttr_lineItemRevTag, &tItemRev );
        if ( tItemRev != NULLTAG )
        {
            itemRevUnqPtr = GET_ItemRevision::getInstance ( tItemRev );
        }

        LOG_TRACE ( logger, "END : GET_BOMLine::getItemRevision()" );

        return itemRevUnqPtr;
    }

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
     //     Return:   GET_BOMLineUnqPtr - Smart Pointer for GET_BOMView instance is returned
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_BOMLineUnqPtr GET_BOMLine::getInstance ( const tag_t tTag )
    {
        return make_unique<GET_BOMLine> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }
}
