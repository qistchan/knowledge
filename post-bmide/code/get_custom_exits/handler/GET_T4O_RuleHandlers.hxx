
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_T4O_RuleHandlers.hxx
//
//    Purpose:   Header File defining the T4O Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_T4O_RuleHandlers_HXX
#define GET_T4O_RuleHandlers_HXX

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_arguments.h>
#include <base_utils/IFail.hxx>

#ifdef __cplusplus
extern "C"
{
#endif

extern EPM_decision_t GET6_validateT4OTransferRH ( EPM_rule_message_t );

#ifdef __cplusplus
}
#endif

#endif // GET_T4O_RuleHandlers_HXX
