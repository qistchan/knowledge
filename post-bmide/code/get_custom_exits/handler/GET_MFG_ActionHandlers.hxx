
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_MFG_ActionHandlers.hxx
//
//    Purpose:   Header File defining the Manufacturing Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     17 May, 2017         Making GET6_AssignReleaseStatusAH_impl function generic
//  TCS Development Team     18 May, 2017         Adding GET6_AttachMfgAttrFormsToTargetAH action handler
//  TCS Development Team     27 Sep, 2017         Added declaration for GET6_routeMBOMBOPAH and GET6_routeMBOMBOPAH_impl
//  TCS Development Team     27 Sep, 2017         Added declaration for GET6_resetMfgAttrOracleXferPropValueAH
//  TCS Development Team     27 Sep, 2017         Removed GET6_traverseBOMAH handler
//  TCS Development Team     20 Jun, 2018         Added Handler Registration for Multi Org
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_MFG_ACTIONHANDLERS_HXX
#define GET_MFG_ACTIONHANDLERS_HXX

// GET Includes
#include <GET_CheckMCN_AH_Impl.hxx>

// Teamcenter Includes
#include <base_utils/IFail.hxx>
#include <base_utils/ResultCheck.hxx>
#include <algorithm>

#define MFG_OBJECT "MBOM"
#define BOP_OBJECT "BOP"
#define UOM_TAG_PROP "uom_tag"
#define UOM_RF_VALUE "RF"
#define ORG_STATUS "OrgBased"
#define MBOM_DECISION_ROUTE "MBOM"
#define BOP_ONLY_DECISION_ROUTE "BOP only"
#define FLIP_TO_MAKE_DECISION_ROUTE "FlipToMake"

GET_FormShrPtr getSameOrgForm ( GET_ItemRevisionShrPtr, string );
map <string, vector<string>> readMultiOrgList ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap );

#ifdef __cplusplus
extern "C"
{
#endif

extern int GET6_CheckMCNAH(EPM_action_message_t);
extern int GETDeriveChangeObjectAH(EPM_action_message_t);
extern int GET6_AssignReleaseStatusAH(EPM_action_message_t);
extern int GET6_addObjectsToTargetAH(EPM_action_message_t);
extern int GET6_setStructureCodeAH(EPM_action_message_t);
extern int GET6_attachedrelatedobjectsAH ( EPM_action_message_t tMessage );
extern int GET6_AttachMfgAttrFormsToTargetAH(EPM_action_message_t);
extern int GET6_resetMfgAttrOracleXferPropValueAH(EPM_action_message_t);
extern int GET6_UpdateStockMaterialMfgFrmAH ( EPM_action_message_t );
extern int GET6_routeMBOMBOPAH ( EPM_action_message_t );
extern int GET6_populateMultiOrgListAH ( EPM_action_message_t );
extern int GET6_readMultiOrgListAH ( EPM_action_message_t );

#ifdef __cplusplus
}
#endif

#endif // GET_MFG_ACTIONHANDLERS_HXX
