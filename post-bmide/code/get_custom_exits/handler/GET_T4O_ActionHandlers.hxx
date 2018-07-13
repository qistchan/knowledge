
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_T4O_ActionHandlers.hxx
//
//    Purpose:   Header File defining the T4O Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016         Initial creation
//  TCS Development Team      03 Mar, 2017         Action Handler to take decision whether T4O transfer is required
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_T4O_ActionHandlers_HXX
#define GET_T4O_ActionHandlers_HXX

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/tc.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define T4O_TRANSFER_ARG_VALUE          "T4O"
#define ROUTING_ARG_VALUE               "ROUTING"
#define T4X_LOGFILE_DESC                "T4x-LOGFILE"

extern int GET6_T4OCreateCCObjectAH ( EPM_action_message_t p_tMsg );
extern int GET6_T4OTransferDecisionAH( EPM_action_message_t p_tMsg );
extern int GET6_notifyT4OAH( EPM_action_message_t p_tMsg );

#ifdef __cplusplus
}
#endif

#endif // GET_T4O_ActionHandlers_HXX
