
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_MFG_RuleHandlers.hxx
//
//    Purpose:   Header File defining the Manufacturing Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     16 Sep, 2016         Initial creation
//  TCS Development Team     27 Jun, 2017         Renamed GET-ValidateFlipToBuy Rule Handler to GET-ValidateFlipToMakeBuy
//  TCS Development Team     07 Aug, 2017         Added declaration for GET6_checkSessionProjectContextRH and GET6_checkSessionProjectContextRH_impl
//  TCS Development Team     27 Sep, 2017         Added declaration for GET6_checkMCNPropsRH and GET6_checkMCNPropsRH_impl
//  TCS Development Team     25 Oct, 2017         Added declaration for GET6_validateMCNEffectivityPropsRH
//  TCS Development Team     20 Jun, 2018         Added declaration for GET6_checkUsersProjectRH
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_MFG_RULEHANDLERS_HXX
#define GET_MFG_RULEHANDLERS_HXX

#include <algorithm>

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/tc.h>
#include <tc/tc_arguments.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern EPM_decision_t GET6_validateMfgStatusRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_checkIsAssemblyRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateNumOfRelationRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateFlipToMakeBuyRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateUOMRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateStockMaterialRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_checkSessionProjectContextRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_checkMCNPropsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_mcnCtrlAttributesRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateMCNEffectivityPropsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_checkUsersProjectRH ( EPM_rule_message_t );

#ifdef __cplusplus
}
#endif

#endif // GET_MFG_RULEHANDLERS_HXX
