
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_HandlerImpl.cxx
 //
 //    Purpose:   Source File GE Transportation Workflow Handler Implementation Abstraction
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     28 Apr, 2016         Initial creation
 //  TCS Development Team     06 Jul, 2016         Added Handler Registration for creating Baseline
 //  TCS Development Team     15 Jul, 2016         Added Handler Registration for validating GET Document Revision
 //  TCS Development Team     16 Sep, 2016         Added Handler Registration for assigning generic release status to BOP
 //  TCS Development Team     28 Mar, 2017         Added Handler Registrations for validating and changing Make to Buy value for FlipToBuy workflow
 //  TCS Development Team     11 Apr, 2017         Removed Handler Registration for GET6_validateNamedRefRH
 //  TCS Development Team     12 Apr, 2017         Added Handler Registrations for Email Error Notification for T4O
 //  TCS Development Team     02 May, 2017         Added Handler Registration for AME2.2 changes
 //  TCS Development Team     15 May, 2017         Added Handler Registration for Validating Checkmate results
 //  TCS Development Team     18 May, 2017         Renamed GET-ValidateFlipToBuy Rule Handler
 //  TCS Development Team     18 May, 2017         Added Handler Registration for Traversing and attaching the Mfg Attribute Forms to Target
 //  TCS Development Team     23 May, 2017         Added Handler Registration for creating BOM Index request dataset
 //  TCS Development Team     29 May, 2017         Added Handler Registration for validating related objects status (GET-check-item-status)
 //  TCS Development Team     29 May, 2017         Added Handler Registration for finding dispatcher requests created from the current WF (GET-find-DispatcherRequests)
 //  TCS Development Team     29 May, 2017         Added Handler Registration for checking the release status of related objects (GET-check-item-status)
 //  TCS Development Team     27 Jun, 2017         Renamed GET-ValidateFlipToBuy Rule Handler to GET-ValidateFlipToMakeBuy
 //  TCS Development Team     29 Jun, 2017         Added Handler Registration for BOMLine children validation (GET-validate-BOM-child-types)
 //  TechM Development Team   18 Sep, 2017         Added handler Registration for creating Dispatcher Request (GET6_createDispatcherRequestsAH)
 //  TCS Development Team     27 Sep, 2017         Added Handler Registration to check MCN mandatory properties (GET-check-MCN-Prop)
 //  TCS Development Team     27 Sep, 2017         Removed Handler Registration for GET6-traverseBOM
 //  TCS Development Team     27 Sep, 2017         Added Handler Registration to route MBOM and/BOP based on solution folder contents (GET-route-MBOM-BOP)
 //  TCS Development Team     27 Sep, 2017         Added Handler Registration to reset the Oracle transfer flag of Mfg Attribute Forms (GET-ResetMfgAttrOracleXferPropValue)
 //  TCS Development Team     11 Oct, 2017         Added Handler Registration for MCN control attributes
 //  TCS Development Team     25 Oct, 2017         Added Handler Registration for MCN Effectivity
 //  TCS Development Team     28 May, 2018         Added Rule handler for traversing the EBOM
 //  TCS Development Team     20 Jun, 2018         Added Handler Registration for Multi Org
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

// GET Includes
#include <GET_COMMON_ActionHandlers.hxx>
#include <GET_Constants.hxx>
#include <GET_ENG_ActionHandlers.hxx>
#include <GET_ENG_RuleHandlers.hxx>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_MFG_ActionHandlers.hxx>
#include <GET_MFG_RuleHandlers.hxx>
#include <GET_T4O_RuleHandlers.hxx>
#include <GET_T4O_ActionHandlers.hxx>
#include <GET_INTG_RuleHandlers.hxx>
#include <GET_COMMON_RuleHandlers.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>
#include <GET_Exception.hxx>

// Teamcenter Includes
#include <tc/emh.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// Private Function Prototypes
static void GET_getHandlerArguments ( TC_argument_list_t*, map<string, string>&, bool = true );

const string logger = "get.handler.GET_HandlerImpl";

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET_processHandler
 //
 //    Purpose:  Function for wrapping Teamcenter Workflow handler implementation
 //
 //    Inputs:   msg - The Message input from the handler. It can be either EPM_action_message_t or EPM_rule_message_t
 //              implFnPointer - The Function Pointer for the actual Handler Implementation Function
 //              bGetFromRootTask - A boolean flag to indicate whether to get the targets from the Root Task or the current Task.
 //                                 true - Root Task, false - Current Task. Default value is true
 //              bToTrim - A boolean flag to indicate whether to trim (remove leading & trailing spaces) the argument values
 //                        that are passed from the Workflow handlers.
 //                        true - Trim, false - Do Not Trim. Default is true
 //
 //    Outputs:  none
 //
 //    Return:   An Integer error code. 0 indicates Handler got executed successfully, non-zero indicates Handler execution failed
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

// Template Declaration
template void GET_processHandler ( EPM_rule_message_t msg,\
          void ( *implFnPointer ) ( const tag_t, map<int, vector<tag_t> >&, map <string, string>& ),\
          bool, bool );

template void GET_processHandler ( EPM_action_message_t msg,\
          void ( *implFnPointer ) ( const tag_t, map<int, vector<tag_t> >&, map <string, string>& ),\
          bool, bool );

template<typename T>
void GET_processHandler ( T msg,
                         void ( *implFnPointer ) ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& ),
                         bool bGetFromRootTask, bool bToTrim )
{
    int iCount = 0;

    map< string, string> mArgumentsMap;
    map<int, vector<tag_t> > mAttachmentVecMap;

    ResultCheck stat;

    tag_t tTaskTag = msg.task;

    vector<int> vAttachmentTypesVec;

    LOG_TRACE ( logger, "START : GET_processHandler" );

    // Loop through the argument list and get the name value pairs
    GET_getHandlerArguments ( msg.arguments, mArgumentsMap, bToTrim );

    // Get root task and target attachments from it
    if ( bGetFromRootTask )
    {
        stat = EPM_ask_root_task ( msg.task, &tTaskTag );
    }

    vAttachmentTypesVec.push_back ( EPM_target_attachment );
    vAttachmentTypesVec.push_back ( EPM_reference_attachment );

    for ( size_t iIndex = 0; iIndex < vAttachmentTypesVec.size(); iIndex++ )
    {
        tag_t *ptAttachmentTags = NULL;

        stat = EPM_ask_attachments ( tTaskTag, vAttachmentTypesVec[iIndex], &iCount, &ptAttachmentTags );
        if ( iCount > 0 )
        {
            vector<tag_t> vAttachmentsVec;

            // Convert target attachments array to vector
            GET_arrayToVector ( iCount, ptAttachmentTags, vAttachmentsVec );
            MEM_free ( ptAttachmentTags );

            // Store the vector into a Map
            mAttachmentVecMap[vAttachmentTypesVec[iIndex]] = vAttachmentsVec;
        }
    }

    // Call the implementation function
    implFnPointer ( tTaskTag, mAttachmentVecMap, mArgumentsMap );

    LOG_TRACE ( logger, "END : GET_processHandler" );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET6_registerHandlers
 //
 //    Purpose:  Extension Method for registering Teamcenter Workflow Handlers
 //
 //    Inputs:   msg - The Message input from the handler
 //              vaArgs - The Variable Argument List input for this Extension Method
 //
 //    Outputs:  none
 //
 //    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     05 May, 2016         Initial creation
 //  TCS Development Team     06 Jul, 2016         Added Handler Registration for creating Baseline
 //  TCS Development Team     15 Jul, 2016         Added Handler Registration for validating GET Document Revision
 //  TCS Development Team     06 Jan, 2017         Added Handler Registrations for BOM Traversal - T4O Publish
 //  TCS Development Team     11 Apr, 2017         Removed Handler Registration for GET6_validateNamedRefRH
 //  TCS Development Team     12 Apr, 2017         Added Handler Registrations for Email Error Notification for T4O
 //  TCS Development Team     28 Mar, 2017         Added Handler Registrations for validating and changing Make to Buy value for FlipToBuy workflow
 //  TCS Development Team     15 May, 2017         Added Handler Registration for Validating Checkmate results
 //  TCS Development Team     18 May, 2017         Renamed GET-ValidateFlipToBuy Rule Handler
 //  TCS Development Team     18 May, 2017         Added Handler Registration for Traversing and attaching the Mfg Attribute Forms to Target
 //  TechM Development Team   20 May, 2017         Added Handler Registrations for deleting active workflow
 //  TCS Development Team     29 May, 2017         Added Handler Registration for validating related objects status (GET-check-item-status)
 //  TCS Development Team     29 May, 2017         Added Handler Registration for finding dispatcher requests created from the current WF (GET-find-DispatcherRequests)
 //  TCS Development Team     29 May, 2017         Added Handler Registration for checking the release status of related objects (GET-check-item-status)
 //  TCS Development Team     27 Jun, 2017         Renamed GET-ValidateFlipToBuy Rule Handler to GET-ValidateFlipToMakeBuy
 //  TCS Development Team     29 Jun, 2017         Added Handler Registration for BOMLine children validation (GET-validate-BOM-child-types)
 //  TCS Development Team     07 Aug, 2017         Added Handler Registration to check presence of project for a session (GET6-check-session-project-context)
 //  TechM Development Team   18 Sep, 2017         Added handler Registration for creating Dispatcher Request (GET6_createDispatcherRequestsAH)
 //  TCS Development Team     27 Sep, 2017         Added Handler Registration to check MCN mandatory properties (GET-check-MCN-Prop)
 //  TCS Development Team     27 Sep, 2017         Removed Handler Registration for GET6-traverseBOM
 //  TCS Development Team     27 Sep, 2017         Added Handler Registration to route MBOM and/BOP based on solution folder contents (GET-route-MBOM-BOP)
 //  TCS Development Team     27 Sep, 2017         Added Handler Registration to reset the modified flag of Mfg Attribute Forms (GET-ResetMfgAttrOracleXferPropValue)
 //  TCS Development Team     28 May, 2018         Added action handler for traversing the EBOM (GET6-traverseBOM)
 //  TCS Development Team     20 Jun, 2018         Added Handler Registration for Multi Org
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_registerHandlers()
{
    int iFail = ITK_ok;

    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET6_registerHandlers" );

    try
    {
         // Register rule handlers
        stat = EPM_register_rule_handler ( "GET6_validateParticipants", "Custom rule handler to validate ECR Workflow Participants", GET6_validateParticipantsRH );
        stat = EPM_register_rule_handler ( "GET6_validateBaselineRqmts", "Custom rule handler to validate Baseline conditions", GET6_validateBaselineRqmtsRH );
        stat = EPM_register_rule_handler ( "GET6_validateDocuments", "Custom rule handler to validate GET Document Revision", GET6_validateDocumentsRH );
        stat = EPM_register_rule_handler ( "GET6_validateItemIDInCC", "Custom rule handler to validate Solution item attributes in DCP", GET6_validateItemIDInCCRH );
        stat = EPM_register_rule_handler ( "GET6-Validate-Initiator", "Rule handler to validate owning user and owning group of target objects", GET6_validateInitiatorRH );
        stat = EPM_register_rule_handler ( "GET6-Validate-MfgStatus", "Rule handler to validate status of Mfg objects", GET6_validateMfgStatusRH );
        stat = EPM_register_rule_handler ( "GET-Validate-Material-MadeFromPart", "Rule handler to validate that a Material or a Made From Part is attached to a make piece part", GET6_validateMaterialsRH );
        stat = EPM_register_rule_handler ( "GET-Validate-related-Objects", "Rule handler to validate that the object or related object has null value", GET6_validateRelatedObjectsRH );
        stat = EPM_register_rule_handler ( "GET6-Validate-T4OTransfer", "Rule handler to validate the attributes required for T4O transfer", GET6_validateT4OTransferRH );
        stat = EPM_register_rule_handler ( "GET-Validate-NumberOf-Relation", "Custom rule handler to validate number of item revision related", GET6_validateNumOfRelationRH );
        stat = EPM_register_rule_handler ( "GET-Check-Is-Assembly", "Custom rule handler to validate number of item revision related", GET6_checkIsAssemblyRH );
        stat = EPM_register_rule_handler ( "GET-check-Group-Properties", "Rule handler to check Group name and Properties for associated ECR/ECN", GET6_checkGroupObjectPropertyRH );
        stat = EPM_register_rule_handler ( "GET-Check-Related-Objects", "Rule handler to check related objects", GET6_checkRelatedObjectsRH );
        stat = EPM_register_rule_handler ( "GET-ValidateFlipToMakeBuy", "Rule handler to validate Make Buy value of target object for Org specific to MCN", GET6_validateFlipToMakeBuyRH );
        stat = EPM_register_rule_handler ( "GET-Validate-Checkmate-Results", "Rule handler to validate NX Checkmate results for a Part", GET6_validateCheckmateResultsRH );
        stat = EPM_register_rule_handler ( "GET-Validate-WF-Retrieval", "Rule handler to check the privileges to delete the active workflow", GET6_validateWFRetrievalRH );
        stat = EPM_register_rule_handler ( "GET-Validate-UOM", "Rule handler to validate UOM of a Part", GET6_validateUOMRH );
        stat = EPM_register_rule_handler ( "GET-Validate-StockMaterial", "Rule handler to validate Stock material on Engg Items", GET6_validateStockMaterialRH );
        stat = EPM_register_rule_handler ( "GET-check-item-status", "Rule handler to check the release status of related objects", GET6_checkItemStatusRH );
        stat = EPM_register_rule_handler ( "GET-validate-BOM-child-types", "Rule handler to validate BOMLine children", GET6_validateBOMChildTypesRH );
        stat = EPM_register_rule_handler ( "GET6-check-session-project-context", "Rule handler to check session project", GET6_checkSessionProjectContextRH );
        stat = EPM_register_rule_handler ( "GET-check-MCN-Prop", "Rule handler to validate the MCN mandatory properties", GET6_checkMCNPropsRH );
        stat = EPM_register_rule_handler ( "GET-MCN-Ctrl-Attributes", "Rule handler to validate MCN Control Attributes", GET6_mcnCtrlAttributesRH );
        stat = EPM_register_rule_handler ( "GET-Validate-Effectivity-Props", "Rule handler to validate MCN Control Attributes", GET6_validateMCNEffectivityPropsRH );
        stat = EPM_register_rule_handler ( "GET-traverseBOM", "Rule handler to traverse the BOM", GET6_traverseBOMRH );
        stat = EPM_register_rule_handler ( "GET-check-users-project", "Rule handler to validate user session project", GET6_checkUsersProjectRH );
        
        // Register action handlers
        stat = EPM_register_action_handler ( "GET6_notify", "Custom rule handler to send email notification based on email address", GET6_notifyAH );
        stat = EPM_register_action_handler ( "GET6_notifyT4O", "Custom rule handler to send email notification with Attachment", GET6_notifyT4OAH );
        stat = EPM_register_action_handler ( "GET-Check-MCN", "Custom Action handler to check for Items in MCN", GET6_CheckMCNAH );
        stat = EPM_register_action_handler ( "GET-Assign-Release-Status", "Custom Action handler to assigning correct release status in MCN", GET6_AssignReleaseStatusAH );
        stat = EPM_register_action_handler ( "GET-Derive-Change-Object", "Custom Action handler to derive the change objects", GETDeriveChangeObjectAH );
        stat = EPM_register_action_handler ( "GET6_createBaseline", "Custom Action handler to create Baseline/Preliminary Release Revisions", GET6_createBaselineAH );
        stat = EPM_register_action_handler ( "GET6_deleteRelatedDataset", "Custom Action handler to delete a given type of dataset with specified relation", GET6_deleteRelatedDatasetAH );
        stat = EPM_register_action_handler ( "GET6-Set-Status", "Custom Action handler to create or remove release status", GET6_setStatusAH );
        stat = EPM_register_action_handler ( "GET-Propagate", "Custom Action handler to attach target objects to propagation list", GET6_PropagatePORAH );
        stat = EPM_register_action_handler ( "GET6-T4O-Create-CCObject", "Custom Action handler for creating CC object", GET6_T4OCreateCCObjectAH );
        stat = EPM_register_action_handler ( "GET6-addObjectsToTarget", "Custom Action handler to copy items and BOM to target from reference folder", GET6_addObjectsToTargetAH );
        stat = EPM_register_action_handler ( "GET6-T4O-Transfer-Decision", "Custom Action handler to take decision whether T4O transfer is required", GET6_T4OTransferDecisionAH );
        stat = EPM_register_action_handler ( "GET6-setStructureCode", "Custom Action handler to set structure code on Manufacturing and Engineering items", GET6_setStructureCodeAH );
        stat = EPM_register_action_handler ( "GET-attach-related-objects", "Custom Action handler to attach Primary or Secondary objects", GET6_attachedrelatedobjectsAH );
        stat = EPM_register_action_handler ( "GET-AttachMfgAttrFormsToTarget", "Custom Action handler to traverse and attach the Mfg Attribute Forms to Target", GET6_AttachMfgAttrFormsToTargetAH );
        stat = EPM_register_action_handler ( "GET-create-BOMIndexReq-Dataset", "Custom Action handler to create BOM request file for Indexing", GET6_createBOMIndexReqDatasetAH );
        stat = EPM_register_action_handler ( "GET-Update-StockMaterial", "Custom Action handler to traverse and attach the Mfg Attribute Forms to Target", GET6_UpdateStockMaterialMfgFrmAH );
        stat = EPM_register_action_handler ( "GET-find-DispatcherRequests", "Custom Action handler to find dispatcher requests created from the current WF", GET6_findDispatcherRequestsAH );
        stat = EPM_register_action_handler ( "GET-createDispatcherRequests", "Custom Action handler to  create dispatcher requests from the current WF", GET6_createDispatcherRequestsAH );
        stat = EPM_register_action_handler ( "GET-route-MBOM-BOP", "Custom Action handler to route MBOM and/BOP based on solution folder contents", GET6_routeMBOMBOPAH );
        stat = EPM_register_action_handler ( "GET-resetMfgAttrOracleXferPropValue", "Custom Action handler to reset the Oracle transfer flag of Mfg Attribute Forms", GET6_resetMfgAttrOracleXferPropValueAH );
        stat = EPM_register_action_handler ( "GET-populateMultiOrgList", "Custom Action handler to populate Multi Org list during ECN process", GET6_populateMultiOrgListAH );
        stat = EPM_register_action_handler ( "GET-readMultiOrgList", "Custom Action handler to populate Multi Org List during ECN process", GET6_readMultiOrgListAH );
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_registerHandlers function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_registerHandlers" );

    return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET_getHandlerArguments
 //
 //    Purpose:  Function for retrieving the Teamcenter Workflow Handler Arguments
 //
 //    Inputs:   arguments - The Teamcenter Workflow Argument Structure
 //              bToTrim - A boolean flag to indicate whether to trim (remove leading & trailing spaces) the argument values
 //                        that are passed from the Workflow handlers.
 //                        true - Trim, false - Do Not Trim. Default is true
 //
 //    Outputs:  A Map storing the Teamcenter Workflow Arguments as string Name-Value Pairs
 //
 //    Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
static void GET_getHandlerArguments ( TC_argument_list_t *arguments, map<string, string> &mArgumentsMap, bool bTrimString )
{
    int iArgCount = 0;

    ResultCheck stat;

    iArgCount = TC_number_of_arguments ( arguments );

    LOG_TRACE ( logger, "START : GET_getHandlerArguments" );

    // Get the  arguments from the handler message
    for ( int iIndex = 0; iIndex < iArgCount; iIndex++ )
    {
        char *pcArgName = NULL;
        char *pcArgValue = NULL;

        string sArgName = "";
        string sArgValue = "";

        stat = ITK_ask_argument_named_value ( ( const char* ) TC_next_argument ( arguments ), &pcArgName, &pcArgValue );
        if ( pcArgName != NULL )
        {
            sArgName.assign ( pcArgName );
            MEM_free ( pcArgName );
            if ( bTrimString )
            {
                GET_strtrim ( sArgName );
            }
        }
        if ( pcArgValue != NULL )
        {
            sArgValue.assign ( pcArgValue );
            MEM_free ( pcArgValue );
            if ( bTrimString )
            {
                GET_strtrim ( sArgValue );
            }
        }

        if ( sArgName.empty () )
        {
            continue;
        }

        mArgumentsMap[sArgName] = sArgValue;
    }

    LOG_TRACE ( logger, "END : GET_getHandlerArguments" );
}

extern DLLEXPORT void catchHandlerExceptions( string sErrMsg )
{
    try
    {
        throw;
    }
    catch ( const IFail &ex )
    {
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        string sMessage =  sErrMsg + " failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }
}
