
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ENG_RuleHandlers.hxx
//
//    Purpose:   Header File defining the Engineering Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     28 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_INTG_RULEHANDLERS_HXX
#define GET_INTG_RULEHANDLERS_HXX

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/tc.h>
#include <tc/tc_arguments.h>

#define ECN_TYPE_PREFIX "ECN"
#define IP_CLASSFICATION "IP"
#define ECCN "ECCN"
#define ATTRIBUTE_VALUE "ATTRIBUTE_VALUE"
#define get6ECCN "get6ECCN"
#define P "P"
#define G "G"
#define H "H"
#define PS "PS"
#define HT "HT"
#define START_WITH_15 "15"
#define START_WITH_17 "17"
#define START_WITH_B  "B"

#define ATTRIBUTETYPE "ATTRIBUTE_TYPE"
#define GET_RINS_CREDENTIALS "GET.INTEGRATION.RIN.CREDENTIALS"
#define GET_CONTROLCARD_INTEGRATION_ON "GET.INTEGRATION.CONTROLCARD.TURNON"

// Function Prototypes

#ifdef __cplusplus
extern "C"
{
#endif

extern EPM_decision_t GET6_validateItemIDInCCRH ( EPM_rule_message_t );

#ifdef __cplusplus
}
#endif

#endif // GET_INTG_RULEHANDLERS_HXX
