
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_COMMON_ActionHandlers.hxx
//
//    Purpose:   Header File defining the common action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  Kumaresan K             10 May, 2016         Initial creation
//  TCS Development Team    19 Jul, 2016         Added action handler for deleting datasets related to Workflow targets
//  TCS Development Team    29 May, 2017         Added handler implementation for identifying if Dispatcher Requests are created in the current Workflow (GET6_findDispatcherRequestsAH)
//  TechM Development Team  18 Sep, 2017         Added handler GET6_createDispatcherRequestsAH implementation to create Dispatcher request for the specified primary, relation and dataset types
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_COMMON_ACTIONHANDLERS_HXX
#define GET_COMMON_ACTIONHANDLERS_HXX

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_EPMTask.hxx>
#include <vector>

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/tc.h>
#include <tc/tc_arguments.h>

// Function Prototypes

#ifdef __cplusplus
extern "C"
{
#endif

#define BODY_BOM_PROP "bom"

extern int GET6_notifyAH ( EPM_action_message_t tMessage );
extern int GET6_deleteRelatedDatasetAH ( EPM_action_message_t tMessage );
extern int GET6_setStatusAH ( EPM_action_message_t tMessage );
extern int GET6_findDispatcherRequestsAH ( EPM_action_message_t tMessage );
extern int GET6_createDispatcherRequestsAH ( EPM_action_message_t tMessage );

#ifdef __cplusplus
}
#endif

#endif // GET_ENG_RULEHANDLERS_HXX
