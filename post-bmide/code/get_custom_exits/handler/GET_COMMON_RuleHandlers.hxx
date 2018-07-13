
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_COMMON_RuleHandlers.hxx
//
//    Purpose:   Header File defining the Common Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     25 Aug, 2016         Initial creation
//  TCS Development Team     11 Apr, 2017         Removed Handler GET6_validateNamedRefRH and consolidated the same with GET6_validateDocumentsRH
//  TCS Development Team     29 May, 2017         Added Handler Registration for validating related objects status (GET6_checkItemStatusRH)
//  TCS Development Team     29 Jun, 2017         Added Handler Registration for validating related objects status (GET6_validateBOMChildTypesRH)
//  TCS Development Team     28 May, 2018         Added Handler Registration for Traversing and validating EBOM (GET6_traverseBOMRH)
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_COMMON_RULEHANDLERS_HXX
#define GET_COMMON_RULEHANDLERS_HXX

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

extern EPM_decision_t GET6_validateInitiatorRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateRelatedObjectsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_checkRelatedObjectsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_checkItemStatusRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateBOMChildTypesRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_traverseBOMRH ( EPM_rule_message_t );

#ifdef __cplusplus
}
#endif

#endif // GET_ENG_RULEHANDLERS_HXX
