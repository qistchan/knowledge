
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_RevisionRule.cxx
//
//    Purpose:   Class to dealing with Teamcenter Revision Rule objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     05 Jul, 2016         Initial creation
//  TCS Development Team     09 May, 2017         Removed an unwanted logger statement from the find() method
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_RevisionRule.hxx>
#include <GET_TC_Logger.hxx>

//TC Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <cfm/cfm.h>
#include <tccore/aom.h>
#include <tccore/tctype.h>

const string logger = "get.get_tc_common.GET_RevisionRule";

namespace get
{
     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   GET_RevisionRule ( const GET_DUMMY, const tag_t )
     //
     //   Purpose :   Constructor for the class GET_RevisionRule
     //
     //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
     //               tTag    - The Tag of this Teamcenter Folder Object
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
    GET_RevisionRule::GET_RevisionRule ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {}

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   find()
     //
     //    Purpose:   Find Revision Rule by its name
     //
     //     Inputs:   sRevRuleName - The Revision Rule Name to be found (string)
     //
     //    Outputs:   none
     //
     //     Return:   The GET_RevisionRule Smart Pointer object is returned
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     18 Mar, 2016         Initial creation
     //  TCS Development Team     09 May, 2017         Removed an unwanted logger statement
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_RevisionRuleUnqPtr GET_RevisionRule::find ( const string sRevRuleName )
    {
        GET_RevisionRuleUnqPtr revRulePtr;

        ResultCheck stat;

        tag_t tRevRuleTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_RevisionRule::find" );

        stat = CFM_find ( sRevRuleName.c_str(), &tRevRuleTag );
        if ( tRevRuleTag != NULLTAG )
        {
            revRulePtr = make_unique<GET_RevisionRule> ( GET_DUMMY::GET_DUMMY_VALUE, tRevRuleTag );
        }
        else
        {
            LOG_TRACE ( logger, "Revision Rule not found" );
        }

        LOG_TRACE ( logger, "END : GET_RevisionRule::find" );

        return revRulePtr;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance (tTag)
    //
    //   Purpose :   Method to get the instance of this class using tag_t
    //
    //   Inputs  :   tTag - tag of the Folder
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_RevisionRule Smart Pointer object is returned
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_RevisionRuleUnqPtr GET_RevisionRule::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_RevisionRule::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, REVISIONRULE_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + REVISIONRULE_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_RevisionRule::getInstance(tTag)" );

        return make_unique<GET_RevisionRule> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
    //   Return  :   The GET_RevisionRule Smart Pointer object is returned
    //
    //   History:
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_RevisionRuleUnqPtr GET_RevisionRule::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_RevisionRule::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_RevisionRule::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }
}
