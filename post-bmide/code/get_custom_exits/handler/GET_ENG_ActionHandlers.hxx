
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ENG_ActionHandlers.hxx
//
//    Purpose:   Header File defining the Engineering Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Jul, 2016         Initial creation
//  TCS Development Team     23 May, 2017         Added handler declaration for creating BOM Index request dataset
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_ENG_ACTIONHANDLERS_HXX
#define GET_ENG_ACTIONHANDLERS_HXX

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/tc.h>
#include <tc/tc_arguments.h>

// Function Prototypes

#ifdef __cplusplus
extern "C"
{
#endif

extern int GET6_createBaselineAH ( EPM_action_message_t );
extern int GET6_PropagatePORAH ( EPM_action_message_t tMessage );
extern int GET6_createBOMIndexReqDatasetAH ( EPM_action_message_t tMessage );

#ifdef __cplusplus
}
#endif

// File Specific Constants declaration
#define BOM_INDEX_ITEMID_PREFIX "item_id="
#define VDS_ARGUMENT "VDS"

#endif // GET_ENG_ACTIONHANDLERS_HXX
