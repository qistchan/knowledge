
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_RevisionRule.hxx
//
//    Purpose:   Header class for dealing with Teamcenter Revision Rule objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     05 Jul, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_REVISIONRULE_HXX
#define GET_REVISIONRULE_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_RevisionRuleUnqPtr unique_ptr<GET_RevisionRule>
    #define GET_RevisionRuleShrPtr shared_ptr<GET_RevisionRule>
}

namespace get
{
    class DLLEXPORT GET_RevisionRule : public GET_WorkspaceObject
    {
        public:
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
            //  TCS Development Team     05 Jul, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            GET_RevisionRule ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   find ( const string )
            //
            //   Purpose :   Method to find a Teamcenter Revision Rule matching the given name
            //
            //   Inputs  :   The Revision Rule Name to be found (string)
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_RevisionRule Smart Pointer instance of the Revision Rule Object
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     05 Jul, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_RevisionRuleUnqPtr find ( const string );

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
            //   TCS Development Team     05 Jul, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_RevisionRuleUnqPtr getInstance ( const tag_t );

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
            //   TCS Development Team     05 Jul, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_RevisionRuleUnqPtr getInstance ( const string );
    };
}

#endif // GET_REVISIONRULE_HXX
