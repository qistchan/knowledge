
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ENG_RuleHandlers.hxx
//
//    Purpose:   Header File defining the Engineering Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     28 Apr, 2016         Initial creation
//  TCS Development Team     15 Jul, 2016         Added Rule Handler for validating GET Document Revision
//  TCS Development Team     27 Oct, 2016         Added Rule Handler for validating GET Material Objects attached to Production Parts
//  Capgemini Development Team  07 Feb, 2017      Added Rule Handler for validating Group and Properties associated with an ECR for Mining
    TCS Development Team     15 May, 2017         Added Handler method declarations for Validating Checkmate results
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_ENG_RULEHANDLERS_HXX
#define GET_ENG_RULEHANDLERS_HXX

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

extern EPM_decision_t GET6_validateParticipantsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateBaselineRqmtsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateDocumentsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateMaterialsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_checkGroupObjectPropertyRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateCheckmateResultsRH ( EPM_rule_message_t );
extern EPM_decision_t GET6_validateWFRetrievalRH ( EPM_rule_message_t );
#ifdef __cplusplus
}
#endif

#endif // GET_ENG_RULEHANDLERS_HXX
