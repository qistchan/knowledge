
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_MFG_RuleHandlers.cxx
//
//    Purpose:   Source File defining the Manufacturing Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     16 Sep, 2016         Initial creation
//  TCS Development Team     27 Jan, 2017         Added GET6_validateNumOfRelationRH rule handler
//  TCS Development Team     27 Jan, 2017         Added GET6_checkIsAssemblyRH rule handler
//  TCS Development Team     28 Mar, 2017         Added GET6_validateFlipToBuyRH rule handler
//  TCS Development Team     19 May, 2017         Added GET6_validateUOMRH rule handler
//  TCS Development Team     26 May, 2017         Added GET6_validateStockMaterialAH rule handler
//  TCS Development Team     27 Jun, 2017         Renamed GET6_validateFlipToBuyRH Rule Handler to GET6_validateFlipToMakeBuyRH
//  TCS Development Team     20 Jul, 2017         Added condition in GET6_validateStockMaterialRH_impl to check if released 
//                                                MFG Attribute form is pushed to Oracle or not. 
//  TCS Development Team     07 Aug, 2017         Added GET6_checkSessionProjectContextRH rule handler
//  TCS Development Team     27 Sep, 2017         Added GET6_checkMCNPropsRH rule handler
//  TCS Development Team     11 Oct, 2017         Added GET6_mcnCtrlAttributesRH rule handler
//  TCS Development Team     25 Oct, 2017         Added GET6_validateMCNEffectivityPropsRH rule handler
//  TCS Development Team     20 Jun, 2018         Added GET6_checkUsersProjectRH rule handler
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_AM_PRIVS.hxx>
#include <GET_BOMLine.hxx>
#include <GET_BOMWindow.hxx>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Participant.hxx>
#include <GET_POM_user.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_GroupMember.hxx>
#include <GET_UserSession.hxx>
#include <GET_Utils.hxx>
#include <GET_TC_Types.hxx>
#include <GET_Constants.hxx>
#include <GET_MFG_RuleHandlers.hxx>
#include <GET_MFG_ActionHandlers.hxx>
#include <GET_CheckMCN_AH_Impl.hxx>

// Teamcenter Includes
#include <tc/emh.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// CPP Includes
#include <map>

using namespace get;

// Private Function Prototypes

static void GET6_validateMfgStatusRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
bool validateMfgStatus ( GET_ItemRevisionShrPtr p_getItemRevShrPtr, const string p_strRelationName, string &solUnReleasedItemIds );
static void GET6_checkIsAssemblyRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_validateNumOfRelationRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_validateFlipToMakeBuyRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_validateUOMRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
vector <string> validateUOM ( vector <string> vIncludeItemRevType, vector<GET_POM_objectShrPtr> vPOMUnqPtr, vector <string> vValidateUOM );
static void GET6_validateStockMaterialRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_checkSessionProjectContextRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_checkMCNPropsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_mcnCtrlAttributesRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_validateMCNEffectivityPropsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_checkUsersProjectRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );

const string logger = "get.handler.GET_MFG_RuleHandler";


/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateMfgStatusRH()
//
//    Purpose:   Rule Handler to validate release status of Mfg objects in MCN solution folder.
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     16 Sep, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateMfgStatusRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateMfgStatusRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateMfgStatusRH_impl );
    }
    catch ( const IFail &ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        tDecision = EPM_nogo;
        string sMessage = "GET6_validateMfgStatusRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_validateMfgStatusRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateMfgStatusRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateMfgStatusRH handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   bool
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     16 Sep, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateMfgStatusRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &p_vAttachments, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START : GET6_validateMfgStatusRH_impl" );
    bool unReleasedObjFound = false;

    for (int inx = 0; inx < p_vAttachments[EPM_target_attachment].size(); inx++)
    {
        string solUnReleasedItemIds = "";
        GET_ItemRevisionShrPtr getItemRevShrPtr(move(GET_ItemRevision::getInstance(p_vAttachments[EPM_target_attachment][inx])));
        LOG_TRACE(logger, "getItemRevShrPtr->getType()-->" + getItemRevShrPtr->getType());
        if(getItemRevShrPtr->getType() == GET_MCN_REV_BO)
        {
            unReleasedObjFound = validateMfgStatus(getItemRevShrPtr, CM_HAS_SLITEMS_PROP, solUnReleasedItemIds);
        }

        // if any un-status Mfg/Eng object founds, return error msg
        if ( unReleasedObjFound )
        {
            string sConsolidatedErrorMessage = "MCN solution folder contains unreleased Mfg/Eng objects for :" ;

            // Append the string of un-released Mfg/Eng object to error message
            sConsolidatedErrorMessage.append( solUnReleasedItemIds );

            // Throw the error to the calling method (Where it will be handled)
            THROW ( sConsolidatedErrorMessage );
        }
    }

    LOG_TRACE ( logger, "END : GET6_validateMfgStatusRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   validateMfgStatus()
//
//    Purpose:   Action Handler Implementation to assign the release status to MCN
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     16 Sept, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
bool validateMfgStatus ( GET_ItemRevisionShrPtr p_getItemRevShrPtr, const string p_strRelationName, string &solUnReleasedItemIds )
{
    int istatus = ITK_ok;

    vector<GET_WorkspaceObjectShrPtr> vReleaseStatusObjectsAdded;
    map<string, GET_BOMViewRevisionShrPtr>::iterator mapBVRIterator;

    LOG_TRACE ( logger, "Entering...validateMfgStatus" );

    // Get the all BOP object type revisions from the preference
    vector<string> vBOPObjRevPrefValues;
    getStringPrefValues ( GET6_BOP_OBJECT_REVISION_TYPES, vBOPObjRevPrefValues );

    if ( vBOPObjRevPrefValues.size() == 0 )
    {
        string sMessage = "The Preference " + string ( GET6_BOP_OBJECT_REVISION_TYPES ) + " is not defined or does not have a value";
        THROW ( sMessage );
    }

    vector<GET_POM_objectUnqPtr> vSecondaryItems = p_getItemRevShrPtr->getPropTags(p_strRelationName);
    for ( int inx = 0; inx < vSecondaryItems.size(); inx++ )
    {
        GET_WorkspaceObjectShrPtr getWorkspaceShrPtr(move(GET_WorkspaceObject::getInstance(vSecondaryItems[inx]->getTag())));

        // Check if the solution folder object is other than type of BOP object, if yes than add to vector
        if ( ! ( std::find(vBOPObjRevPrefValues.begin(), vBOPObjRevPrefValues.end(), getWorkspaceShrPtr->getType() ) != vBOPObjRevPrefValues.end() ) )
        {
            // Check if the solution folder object is Eng type, if yes than add to vector
            if ( ! ( getWorkspaceShrPtr->getType().compare ( GET_MFG_REV_BO ) ) )
            {
                vReleaseStatusObjectsAdded.push_back(getWorkspaceShrPtr);

                map<string, GET_BOMViewRevisionShrPtr> mpBVRObjects = GET_ItemRevision::getInstance ( vSecondaryItems[inx]->getTag() )->getBVRs();
                for(mapBVRIterator = mpBVRObjects.begin(); mapBVRIterator != mpBVRObjects.end(); mapBVRIterator++)
                {
                    GET_WorkspaceObjectShrPtr getWorkspaceBVRShrPtr ( move ( GET_WorkspaceObject::getInstance ( mapBVRIterator->second->getTag() ) ) );
                    vReleaseStatusObjectsAdded.push_back ( getWorkspaceBVRShrPtr );
                }
            }
        }
    }

    if ( vReleaseStatusObjectsAdded.size() > 0 )
    {
        vector<string> releaseStatusList;
        string solUnReleasedItemId;

        for ( int inx = 0; inx <vReleaseStatusObjectsAdded.size(); inx++ )
        {
            // Get the release status list of Mfg/Eng objects
            releaseStatusList = vReleaseStatusObjectsAdded[inx]->getReleaseStatusList();

            if ( releaseStatusList.size() == 0 )
            {
                if ( vReleaseStatusObjectsAdded[inx]->getType() != BOMVIEWREVISION )
                {
                    // Construct the string of all un-released Mfg/Eng objects for displaying in error message
                    GET_ItemRevisionUnqPtr solItemRevisionPtr = GET_ItemRevision::getInstance ( vReleaseStatusObjectsAdded[inx]->getTag() );
                    solUnReleasedItemId = solItemRevisionPtr ->getId ();

                    solUnReleasedItemIds.append (solUnReleasedItemId);

                    if ( ( inx+1 ) != vReleaseStatusObjectsAdded.size() )
                    {
                        solUnReleasedItemIds.append (",");
                    }
                }
            }
        }

        // Return true if there are any unreleased Mfg/Eng objs found
        if ( solUnReleasedItemIds.size() > 0 )
        {
            return true;
        }
    }

     LOG_TRACE (logger, "Exiting...validateMfgStatus");

     return false;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateNumOfRelationRH()
//
//    Purpose:   Rule Handler to validate the Preconditions for Preliminary release structure
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     27 Jan, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateNumOfRelationRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateNumOfRelationRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateNumOfRelationRH_impl );
    }
    catch ( ... )
    {
           catchHandlerExceptions ( "GET6_validateNumOfRelationRH" );
           tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateNumOfRelationRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateNumOfRelationRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateNumOfRelationRH_impl handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     30 Jan, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateNumOfRelationRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{

    LOG_TRACE ( logger, "START.... : GET6_validateNumOfRelationRH_impl" );

    int iCount = 0;
    int iItemInSolnItem = 0;

    ResultCheck stat;

    string sMCNID;
    string sItemTypeDispName;

    //Vector to store solution item contents
    vector<GET_POM_objectUnqPtr> vSolutionItems;
    GET_EPMTaskUnqPtr epmTaskUnqPtr;

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( RELATION_TYPE ) == mArgumentsMap.end() ||
             mArgumentsMap[RELATION_TYPE].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE ) + "\" is either empty or has an invalid value";
        THROW ( sMsg );
    }

    if ( mArgumentsMap.find ( VALIDATE_COUNT ) == mArgumentsMap.end() ||
                 mArgumentsMap[VALIDATE_COUNT].empty() )
    {
            string sMsg = "The Workflow handler argument \"" + string ( VALIDATE_COUNT ) + "\" is either empty or has an invalid value";
            THROW ( sMsg );
    }

    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() ||
             mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG ) + "\" is either empty or has an invalid value";
        THROW ( sMsg );
    }

    iCount = stoi ( mArgumentsMap[VALIDATE_COUNT] );

    //Loop to check the size of CMHASSOLUTIONITEMS Relation
    //Throw error if solution items contains more then one Business Object
    //Before adding this rule handler, we are making a use of OOTB EPM-check-related-object handler in workflow
    //to ensure solution items folder always contains GET Mfg Part Revision
    //so we are not checking for Mfg Part Revision type
    // Clear the existing error stack
    stat = EMH_clear_errors();

    for ( int iPrelim=0; iPrelim < mAttachmentsMap[EPM_target_attachment].size(); iPrelim++ )
    {
        GET_ItemRevisionUnqPtr itemRevisionUnqPtr = GET_ItemRevision::getInstance ( mAttachmentsMap[EPM_target_attachment][iPrelim] );
        GET_ItemRevisionShrPtr itemRevShrPtr ( move ( itemRevisionUnqPtr ) );

        LOG_TRACE(logger, "itemRevShrPtr->getType()-->" + itemRevShrPtr->getType());

            if ( itemRevShrPtr->getType() == MCNREVISION_TYPE )
            {
                 vSolutionItems = itemRevShrPtr->getPropTags ( mArgumentsMap[RELATION_TYPE] );

                 sMCNID = itemRevShrPtr->getId();
            }
    }

    for ( int iInx = 0; iInx < vSolutionItems.size(); iInx++ )
    {
        GET_ItemRevisionUnqPtr itemRevisionUnqPtr = GET_ItemRevision::getInstance ( vSolutionItems[iInx]->getTag() );

        if ( itemRevisionUnqPtr->getType().compare ( mArgumentsMap[INCLUDE_TYPE_ARG] ) == 0 )
        {
            sItemTypeDispName = itemRevisionUnqPtr->getPropValueAsString ( OBJECT_TYPE_ATTR );
        }
    }

    epmTaskUnqPtr = GET_EPMTask::getInstance( tTaskTag );
    GET_EPMTaskShrPtr epmTaskShrPtr ( move ( epmTaskUnqPtr ) );

    string workflowName = epmTaskShrPtr->getName();

    //As per requirement if solution Item contains more then one Object, error should be thrown.
    if ( vSolutionItems.size() != iCount )
    {
        THROW ( "Only " + mArgumentsMap[VALIDATE_COUNT] + " " + sItemTypeDispName + " should be present under \"" + sMCNID + "\" for "+workflowName );
    }

    LOG_TRACE ( logger, "Exiting.... : GET6_validateNumOfRelationRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkIsAssemblyRH()
//
//    Purpose:   Rule Handler to validate the Preconditions for Preliminary release structure
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     27 Jan, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_checkIsAssemblyRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_checkIsAssemblyRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_checkIsAssemblyRH_impl );
    }
    catch ( ... )
    {
           catchHandlerExceptions ( "GET6_checkIsAssemblyRH" );
           tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_checkIsAssemblyRH" );

    return tDecision;

}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkIsAssemblyRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_checkIsAssemblyRH_impl handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     30 Jan, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_checkIsAssemblyRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START.... : GET6_checkIsAssemblyRH_impl" );

    string sMCNID;
    ResultCheck stat;
    vector<string> vErrorItemIDs;

    //Vector to store solution item contents
    vector<GET_POM_objectUnqPtr> vSolutionItems;

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( RELATION_TYPE ) == mArgumentsMap.end() ||
             mArgumentsMap[RELATION_TYPE].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE ) + "\" is either empty or has an invalid value";
        THROW ( sMsg );
    }

    stat = EMH_clear_errors();

    //Loop to get the MCN Revision and solution items contents
    for(int iPrelim=0; iPrelim < mAttachmentsMap[EPM_target_attachment].size(); iPrelim++)
    {
        GET_ItemRevisionUnqPtr itemRevisionUnqPtr = GET_ItemRevision::getInstance (mAttachmentsMap[EPM_target_attachment][iPrelim] );
        GET_ItemRevisionShrPtr itemRevShrPtr ( move ( itemRevisionUnqPtr ) );

        LOG_TRACE(logger, "itemRevShrPtr->getType()-->" + itemRevShrPtr->getType());

        if(itemRevShrPtr->getType() == MCNREVISION_TYPE)
        {
             vSolutionItems = itemRevShrPtr->getPropTags(mArgumentsMap[RELATION_TYPE]);
             sMCNID = itemRevShrPtr->getId();
        }

    }

    if(vSolutionItems.size()!=0)
    {
        // Get the MfgPart Revision Object and check if it has assembly
        // For Prelim Release Mfg Part Revision Should have a assembly.
        for(int inx =0;inx<vSolutionItems.size();inx++)
        {
            GET_ItemRevisionUnqPtr mfgPartRevisionUnqPtr = GET_ItemRevision::getInstance ( vSolutionItems[inx]->getTag());
            GET_ItemRevisionShrPtr mfgPartRevShrPtr ( move ( mfgPartRevisionUnqPtr ) );
            vector<GET_POM_objectUnqPtr> childObjectsVector = mfgPartRevShrPtr->getPropTags ( PSCHILDREN_ATTR );
            if ( childObjectsVector.size()==0 )
            {
                vErrorItemIDs.push_back( mfgPartRevShrPtr->getId() );

            }
        }

    }

    if ( vErrorItemIDs.size() > 0 )
    {
        string sConsolidatedErrorMessage = "";

        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorItemIDs.size(); iIndex++ )
        {
            sConsolidatedErrorMessage += vErrorItemIDs[iIndex];
            if ( iIndex < ( vErrorItemIDs.size() - 1 ) )
            {
                sConsolidatedErrorMessage += "\n";
            }
        }

        // Throw the error to the calling method (Where it will be handled)
        THROW ( "Following GET Manufacturing Part Revision present under \""+ sMCNID + "\" must have Assembly/Structure "+sConsolidatedErrorMessage);
    }

    LOG_TRACE ( logger, "Exiting.... : GET6_checkIsAssemblyRH_impl" );

}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateFlipToMakeBuyRH()
//
//    Purpose:   Rule handler to validate Mfg Make Buy value
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      28 Mar, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateFlipToMakeBuyRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateFlipToMakeBuyRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateFlipToMakeBuyRH_impl );
    }
    catch ( const IFail &ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        tDecision = EPM_nogo;
        string sMessage = "GET6_validateFlipToMakeBuyRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_validateFlipToMakeBuyRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateFlipToMakeBuyRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateFlipToMakeBuyRH handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   bool
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      28 Mar, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_validateFlipToMakeBuyRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &p_vAttachments, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START : GET6_validateFlipToMakeBuyRH_impl" );

    GET_CheckMCN_AH_Impl*  GET_CheckMCN_AHObj = new GET_CheckMCN_AH_Impl ( tTaskTag, p_vAttachments, mArgumentsMap );
    GET_CheckMCN_AHObj->validateFlipToMakeBuy ();

    LOG_TRACE ( logger, "END : GET6_validateFlipToMakeBuyRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateUOMRH()
//
//    Purpose:   Rule handler to validate UOM Values
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateUOMRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateUOMRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateUOMRH_impl );
    }
    catch ( const IFail &ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        tDecision = EPM_nogo;
        string sMessage = "GET6_validateUOMRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_validateUOMRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateUOMRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateUOMRH_impl handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     19 May, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateUOMRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    int count=0;

    ResultCheck stat;

    vector <GET_POM_objectUnqPtr> vPOMUnqPtr;
    vector <GET_POM_objectShrPtr> vPomShrPtr;
    vector <string> vIncludeItemRevType;
    vector <string> vValidateUOM;
    vector <string> vErrorMessages;
    vector <tag_t> vTargetAttachments;

    GET_POM_objectUnqPtr pomUnqPtr;

    LOG_TRACE ( logger, "START.... : GET6_validateUOMRH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end () || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        THROW ( string ( "The argument \"" ) + INCLUDE_TYPE_ARG + string ( "\" is not provided or has empty value" ) );
    }

    if ( mArgumentsMap.find ( VALIDATE_UOM ) == mArgumentsMap.end () || mArgumentsMap[VALIDATE_UOM].empty() )
    {
        THROW ( string ( "The argument \"" ) + VALIDATE_UOM + string ( "\" is not provided or has empty value" ) );
    }

    if ( mArgumentsMap.find ( SOURCE_TYPE_ARG ) != mArgumentsMap.end() || mArgumentsMap[RELATION_TYPE_ARG].empty() )
    {
        if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[RELATION_TYPE_ARG].empty() )
        {
            THROW ( string ( "The argument \"" ) + SOURCE_TYPE_ARG + string ( "and") + RELATION_TYPE_ARG + string ( "\" are not mutually exclusive" ) );
        }
    }

    if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) != mArgumentsMap.end() || mArgumentsMap[SOURCE_TYPE_ARG].empty() )
    {
        if ( mArgumentsMap.find ( SOURCE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[SOURCE_TYPE_ARG].empty() )
        {
            THROW ( string ( "The argument \"" ) + SOURCE_TYPE_ARG + string ( "and") + RELATION_TYPE_ARG + string ( "\" are not mutually exclusive" ) );
        }
    }

    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeItemRevType );
    GET_splitString ( mArgumentsMap[VALIDATE_UOM], COMMA_CHARACTER, vValidateUOM );

    stat = EMH_clear_errors();

    vTargetAttachments = mAttachmentsMap[EPM_target_attachment];
    //if Source Type argument is provided get the required data from
    //that argument
    if ( mArgumentsMap.find ( SOURCE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        for ( int iIndex = 0; iIndex < vTargetAttachments.size(); iIndex++ )
        {
            // Check if the target is an SOURCE_TYPE_ARG
            if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iIndex], mArgumentsMap [SOURCE_TYPE_ARG] ) )
            {
                continue;
            }
            pomUnqPtr = GET_POM_object::getInstance ( vTargetAttachments[iIndex] );
            LOG_TRACE(logger, "Type Name is -->" + pomUnqPtr->askTypeName());
            break;
        }

        GET_POM_objectShrPtr pomShrPtr ( move ( pomUnqPtr ) );

        // Get Secondary objects for a given primary type object using relation argument
        vPOMUnqPtr = GET_ImanRelation::listRelatedObjects ( pomShrPtr, mArgumentsMap[RELATION_TYPE_ARG], false );

        for ( int iIndex =0; iIndex < vPOMUnqPtr.size(); iIndex++ )
        {
            GET_POM_objectShrPtr getPOMShrPtr ( move ( vPOMUnqPtr[iIndex] ) );
            vPomShrPtr.push_back ( getPOMShrPtr );
        }

        //GET the in item id's with invalid UOM values
        vErrorMessages = validateUOM ( vIncludeItemRevType, vPomShrPtr, vValidateUOM );
    }
    //If no source argument is provided take data from Targets
    else
    {
        for ( int iIndex = 0; iIndex < vTargetAttachments.size(); iIndex++ )
        {
            // Check if the target is an SOURCE_TYPE_ARG
            if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iIndex], ITEMREVISION_CLASS ) )
            {
                continue;
            }
            pomUnqPtr = GET_POM_object::getInstance ( vTargetAttachments[iIndex] );

            LOG_TRACE(logger, "Type Name is -->" + pomUnqPtr->askTypeName());

            GET_POM_objectShrPtr getPOMShrPtr ( move ( pomUnqPtr ) );
            vPomShrPtr.push_back ( getPOMShrPtr );
        }
        vErrorMessages = validateUOM ( vIncludeItemRevType, vPomShrPtr, vValidateUOM );
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage="";

        if ( ! ( mArgumentsMap[SOURCE_TYPE_ARG].empty() ) )
        {
            sConsolidatedErrorMessage = "\nThe following Items present under "+ mArgumentsMap[SOURCE_TYPE_ARG] +" " + mArgumentsMap[RELATION_TYPE_ARG] +" folder has INVALID UOM value as " + mArgumentsMap[VALIDATE_UOM] +"\n";
        }
        else
        {
            sConsolidatedErrorMessage = "\nThe following Items has INVALID UOM value as " + mArgumentsMap[VALIDATE_UOM] +"\n";
        }

        // Store the errors one by one in the stack
        for ( int iIndex = 0; iIndex < vErrorMessages.size(); iIndex++ )
        {
            sConsolidatedErrorMessage += vErrorMessages[iIndex];
            if ( iIndex < ( vErrorMessages.size() - 1 ) )
            {
                sConsolidatedErrorMessage += "\n";
            }
        }
        // Throw the error to the calling method (Where it will be handled)
        THROW ( sConsolidatedErrorMessage );
    }
    LOG_TRACE ( logger, "Exiting.... : GET6_validateUOMRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   validateUOM()
//
//    Purpose:   To validate UOM value supplied and return the Item ID's
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     20 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
vector<string> validateUOM ( vector<string> vIncludeItemRevType, vector<GET_POM_objectShrPtr> vPOMUnqPtr, vector<string> vValidateUOM )
{
    vector <string> vErrorMessages;

    LOG_TRACE ( logger, "START.... : validateUOM" );

    if ( ( vIncludeItemRevType.size() != 0 ) && ( vPOMUnqPtr.size() != 0 ) && ( vValidateUOM.size() != 0 ) )
    {
        for ( int iIndex = 0; iIndex < vPOMUnqPtr.size(); iIndex++ )
        {
            //Checking if allowed types are present in the relation pseudo folder.
            if ( GET_isInVector ( vIncludeItemRevType, vPOMUnqPtr[iIndex]->askTypeName() ) )
            {
                GET_ItemRevisionUnqPtr getItemRevUnqPtr = GET_ItemRevision::getInstance ( vPOMUnqPtr[iIndex]->getTag() );
                GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( getItemRevUnqPtr ) );

                //Get UOM value from Item.
                string sUOMValue = getItemRevShrPtr->getItem()->getPropValueAsString ( UOM_TAG_PROP );

                //Validate the UOM supplied in the argument
                if ( GET_isInVector ( vValidateUOM, sUOMValue ) )
                {
                    LOG_TRACE ( logger, "sUOMValue --> " + sUOMValue );
                    vErrorMessages.push_back ( getItemRevShrPtr->getId() );
                }
            }
        }
    }

    LOG_TRACE ( logger, "END.... : validateUOM" );

    return vErrorMessages;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateStockMaterialRH()
//
//    Purpose:   Rule handler to validate UOM Values
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      20 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateStockMaterialRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateStockMaterialRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateStockMaterialRH_impl );
    }
    catch ( const IFail &ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        tDecision = EPM_nogo;
        string sMessage = "GET6_validateStockMaterialRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_validateStockMaterialRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateStockMaterialRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateStockMaterialRH handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     21 May, 2017         Initial Creation
//  TCS Development Team     20 Jul, 2017         Added condition to validate if released MFG Attribute form is pushed to Oracle or not. 
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateStockMaterialRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START.... : GET6_validateStockMaterialRH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end () || mArgumentsMap[INCLUDE_TYPE_ARG].empty () )
    {
        THROW ( string ( "The argument \"" ) + INCLUDE_TYPE_ARG + string ( "\" is not provided or has empty value" ) );
    }

    vector<string> vErrorMessages;
    vector<tag_t> vTargetObjects;
    vector <string> vIncludeType;
    vector<GET_POM_objectUnqPtr> vSolnItemStockMatrls;
    GET_ItemUnqPtr mtrlUnqPtr;
    GET_ItemUnqPtr itemUnqPtr;
    string sStockMaterialID ="";
    string sTypeName = "";
    string sMcnOrg = "";

    // Get the Target Objects from the Workflow Target Attachments
    vTargetObjects = mAttachmentsMap[EPM_target_attachment];

    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );
    }

    for ( size_t iIndex = 0; iIndex < vTargetObjects.size(); iIndex++ )
    {
        // Validate if MCN Revision is found in target object
        if ( GET_POM_object::isDescendant (vTargetObjects[iIndex], GET_MCN_REVISION_CLASS ) )
        {
            GET_ItemRevisionUnqPtr getMCNRevUnqPtr = GET_ItemRevision::getInstance ( vTargetObjects[iIndex] );
            GET_ItemRevisionShrPtr getMCNRevShrPtr ( move ( getMCNRevUnqPtr ) );

            LOG_TRACE ( logger, "getMCNRevShrPtr->getType()--> " + getMCNRevShrPtr->getType() );

            if ( getMCNRevShrPtr->getType() == GET_MCN_REV_BO )
            {
                sMcnOrg = getMCNRevShrPtr->getPropertyTag ( OWNING_PROJECT_ATTR )->getPropertyString ( PROJECT_ID_ATTR );
                vSolnItemStockMatrls = getMCNRevShrPtr->getPropTags ( CM_HAS_SOLUTION_ITEMS_PROP );

                GET_ItemRevisionUnqPtr getStckRevUnqPtr = GET_ItemRevision::getInstance ( vSolnItemStockMatrls[0]->getTag() );
                GET_ItemRevisionShrPtr getStckRevShrPtr ( move ( getStckRevUnqPtr ) );

                GET_POM_objectUnqPtr stockSolutionItemUnqPtr = GET_POM_object::getInstance ( ( getStckRevShrPtr->getItem() )->getTag() );
                GET_POM_objectShrPtr stockSolutionItemShrPtr ( move ( stockSolutionItemUnqPtr ) );
                sStockMaterialID = getStckRevShrPtr->getId();

                vector<GET_POM_objectUnqPtr> vPOMUnqPtr = GET_ImanRelation::listRelatedObjects ( stockSolutionItemShrPtr, "GET6HasStockMatl",true );
                if ( vPOMUnqPtr.size() == 0)
                {
                    string sNoMaterialStock = "Stock Material " + sStockMaterialID + " is not attach to Material.";
                    THROW ( sNoMaterialStock );
                }
             }
            break;
        }
    }

    for ( size_t iIndex = 0; iIndex < vTargetObjects.size(); iIndex++ )
    {
        // Check if the target is an ItemRevision or not
        if ( ! GET_POM_object::isDescendant ( vTargetObjects[iIndex], ITEMREVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionUnqPtr itemRevUnqPtr = GET_ItemRevision::getInstance ( vTargetObjects[iIndex] );

        // Get the Object Type
        sTypeName = itemRevUnqPtr->getType();

        // Check if the Target is provided in the To Be Checked List
        if ( ! vIncludeType.empty() && ! GET_isInVector ( vIncludeType, sTypeName ) )
        {
            continue;
        }

        // Get the Item from the Revision
        itemUnqPtr = itemRevUnqPtr->getItem();
        GET_ItemShrPtr itemPtr ( move ( itemUnqPtr ) );

        //GET Mfg attribute form attach to Item with GET Part to Org Relation
        vector<GET_POM_objectUnqPtr> vMFgAttrFormPtr = itemPtr->getPropTags ( GET_PART_ORG_ATTR_BO );
        if ( vMFgAttrFormPtr.size()!= 0)
        {
            for ( size_t iIndex = 0; iIndex < vMFgAttrFormPtr.size(); iIndex++)
            {
                 GET_POM_objectShrPtr pomObjectShrPtr ( move ( vMFgAttrFormPtr[iIndex] ) );

                 GET_WorkspaceObjectUnqPtr getWSOUnqPtr = GET_WorkspaceObject::getInstance ( pomObjectShrPtr->getTag() );
                 GET_WorkspaceObjectShrPtr getWSOShrPtr ( move ( getWSOUnqPtr ) );

                 string sOwningProjectID = getWSOShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );

                 // Check Owning Project of Mfg attribute form
                 if ( sMcnOrg.compare ( sOwningProjectID ) == 0 )
                 {
                     GET_DateUnqPtr itemPublishDateUnqPtr = getWSOShrPtr->getPropDate ( ITEM_PUBLISH_DATE );

                     //Check Release Status and Item Publish Date
                     if ( ( getWSOShrPtr->isReleased() ) && ( ! itemPublishDateUnqPtr->toString().empty() ) )
                     {
                         string sMakeBuy = "";
                         sMakeBuy = getWSOShrPtr->getPropString ( MAKE_BUY_PROP );
                         //Check Make_BUY value and error for Buy or Blank.
                         if ( sMakeBuy.compare ( MFG_MAKEBUY_MAKE_VALUE ) != 0 )
                         {
                             string sErrorMessage = string ( "Manufacturing Make/Buy value of " + string ( itemPtr->getId()) + " is " + sMakeBuy +". It Should be Make :");
                             vErrorMessages.push_back ( sErrorMessage );
                         }
                         else
                         {
                             //Check if already any Stock Material is set.
                             GET_POM_objectUnqPtr vGetStockMaterialObject = getWSOShrPtr->getPropTag ( STOCK_MATERIAL_ATTR );
                             if ( vGetStockMaterialObject== NULL || vGetStockMaterialObject.get() == NULL )
                             {
                                 string sErrorMessage = string ( "Stock Material field for Manufacturing Attribute Form attach to  " + string ( itemPtr->getId() ) + " is Empty :");
                                 vErrorMessages.push_back ( sErrorMessage );
                             }
                         }
                     }
                     else
                     {
                         string sErrorMessage = string ( "Manufacturing Attribute form attached to " + string ( itemPtr->getId()) + " for Org " + sMcnOrg +" should be Released and available in Oracle");
                         vErrorMessages.push_back ( sErrorMessage );
                     }
                 }
            }
        }
        else
        {
            string sErrorMessage = string ( "Make Buy Org Form is missing for Part : " ) + itemPtr->getId() + string ( " for Org " ) + sMcnOrg;
            vErrorMessages.push_back ( sErrorMessage );
        }
        // Get the list of Materials Attached under the given relation
        vector<GET_POM_objectUnqPtr> vMaterialObjects = itemPtr->getPropTags ( MADEFROMMATL );
        if ( vMaterialObjects.size() == 0 )
        {
            string sErrorMessage = string ( "Material is not associated with Part : " ) + itemPtr->getId();
            vErrorMessages.push_back ( sErrorMessage );
            continue;
        }
        //Check if the attached material's has the stock material present in MCN Solution Items Folder
        else
        {

        for ( size_t iIndex = 0; iIndex < vMaterialObjects.size(); iIndex++ )
        {
            mtrlUnqPtr = GET_Item::getInstance ( vMaterialObjects[iIndex]->getTag() );
            GET_ItemShrPtr mtrlShrPtr ( move ( mtrlUnqPtr ) );

            // Get the list of Stock Material Attached under the given relation
            vector<GET_POM_objectUnqPtr> vStockMaterials = mtrlShrPtr->getPropTags ( STOCKMATRL );
            if ( vStockMaterials.size() == 0 )
            {
                string sErrorMessage = string ( "No StockMaterial is not associated with Material  : " ) +  mtrlUnqPtr->getId() + "Attached to Part " +  itemPtr->getId();
                vErrorMessages.push_back ( sErrorMessage );
                continue;
            }
            else
            {
                bool bIsStockMtrlPresent;
                for ( size_t iIndex = 0; iIndex < vStockMaterials.size(); iIndex++ )
                {
                    GET_ItemUnqPtr stockMtrlItemPtr = GET_Item::getInstance ( vStockMaterials[iIndex]->getTag() );
                    bIsStockMtrlPresent =false;
                    if( sStockMaterialID.compare ( stockMtrlItemPtr->getId() ) ==0 )
                    {
                        bIsStockMtrlPresent = true;
                        break;
                    }

                }
                if (bIsStockMtrlPresent==false)
                {
                    string sErrorMessage =  " StockMaterial " + sStockMaterialID +" is not associated with Material  : "  + mtrlShrPtr->getId() + " Attached to Part " +  itemPtr->getId();
                    vErrorMessages.push_back ( sErrorMessage );
                }
            }
        }
      }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "";

        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size(); iIndex++ )
        {
            sConsolidatedErrorMessage += vErrorMessages[iIndex];
            if ( iIndex < ( vErrorMessages.size() - 1 ) )
            {
                sConsolidatedErrorMessage += "\n";
            }
        }

        // Throw the error to the calling method (Where it will be handled)
        THROW ( sConsolidatedErrorMessage );
    }

    LOG_TRACE ( logger, "END : GET6_validateStockMaterialRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkSessionProjectContextRH()
//
//    Purpose:   Rule Handler to check presence of session project
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team           07 Aug, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_checkSessionProjectContextRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_checkSessionProjectContextRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_checkSessionProjectContextRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_checkSessionProjectContextRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_checkSessionProjectContextRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkSessionProjectContextRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_checkSessionProjectContextRH handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team           07 Aug, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_checkSessionProjectContextRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START : GET6_checkSessionProjectContextRH_impl" );

    GET_UserSessionUnqPtr userSessionUnqPtr = GET_UserSession::getCurrentUserSession();
    GET_TC_ProjectShrPtr projTagShrPtr = userSessionUnqPtr->getProject();
    if ( projTagShrPtr == NULL )
    {
        THROW ( "The Project context is blank. Please change the Project context using the User Settings command." );
    }

    LOG_TRACE ( logger, "END : GET6_checkSessionProjectContextRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkMCNPropsRH()
//
//    Purpose:   Rule handler to validate MCN mandatory Properties
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     27 Sep, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_checkMCNPropsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_checkMCNPropsRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_checkMCNPropsRH_impl );
    }
    catch ( const IFail &ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        tDecision = EPM_nogo;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        tDecision = EPM_nogo;
        string sMessage = "GET6_checkMCNPropsRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_checkMCNPropsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkMCNPropsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_checkMCNPropsRH handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     27 Sep, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_checkMCNPropsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    int istatus = 0;

    string sEffDecision       = EMPTY_STRING_VALUE;
    string sAffectBOPDecision = EMPTY_STRING_VALUE;
    string strValidationType  = EMPTY_STRING_VALUE;
    string sConsolidatedErrorMessage = EMPTY_STRING_VALUE;

    LOG_TRACE ( logger, "START : GET6_checkMCNPropsRH_impl method" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( TYPE_ARG ) == mArgumentsMap.end ()|| mArgumentsMap[TYPE_ARG].empty () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( TYPE_ARG )
                + "\"  is missing or is empty";
        THROW( sMsg );
    }
    strValidationType = mArgumentsMap [ TYPE_ARG ];
    LOG_TRACE ( logger, "Argument type : " + strValidationType );

    // Clear the existing error stack
    istatus = EMH_clear_errors();

    // Loop through each target objects
    for ( int iTargetIndex = 0; iTargetIndex < mAttachmentsMap[EPM_target_attachment].size(); iTargetIndex++ )
    {
        // Validate if MCN Revision is found in target object
        if (! GET_POM_object::isDescendant ( mAttachmentsMap[EPM_target_attachment][iTargetIndex], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getMCNRevShrPtr ( move ( GET_ItemRevision::getInstance ( mAttachmentsMap[EPM_target_attachment][iTargetIndex] )));
        LOG_TRACE ( logger, "getMCNRevShrPtr->getType()-->" + getMCNRevShrPtr->getType() );

        // If Workflow argument is for validating if MCN is derived from ECN
        if ( strValidationType.compare ( MCN_DERIVED_DECISION_ARG ) == 0 )
        {
            // Check if MCN has CMImplements value (ECN object)
            vector<GET_POM_objectUnqPtr> vDerivedItemsUnqPtr = getMCNRevShrPtr->getPropTags ( CM_IMPLEMENTS_PROP );

            if ( vDerivedItemsUnqPtr.size() > 0 )
            {
                // Set Error so User can Add MBOM
                string sMessage = "MCN is derived from ECN, please add MBOM/BOP to Solution Folder and complete the task ";
                THROW ( sMessage );
            }
            else
            {
                LOG_TRACE ( logger, "Manual MCN created... skipping Add MBOM task" );
            }
        }
        else if ( strValidationType.compare ( AFFECT_BOP_DECISION_ARG ) == 0 ) // If Workflow argument is for BOP Decision
        {
            sAffectBOPDecision = getMCNRevShrPtr->getPropString ( AFFECT_BOP_DECISION_PROP );

            // Check the Affect BOP decision made on MCN Rev object, if not taken, then throw error to User
            if ( sAffectBOPDecision.empty() )
            {
                string sMessage = "Affect BOP Decision on MCN Revision has not been taken, Please take the Decision and complete the task ";
                THROW ( sMessage );
            }
        }
        else if ( strValidationType.compare ( EFF_DECISION_ARG ) == 0 ) // If Workflow argument is for Effectivity Decision
        {
            sEffDecision = getMCNRevShrPtr->getPropString ( EFF_DECISION_PROP );

            // Check the Effectivity Decision made on MCN Rev object, if not taken, then throw error to User
            if ( sEffDecision.empty() )
            {
                string sMessage = "Effectivity Decision on MCN Revision has not been taken, Please take the Decision and complete the task ";
                THROW ( sMessage );
            }
        }
        else if ( strValidationType.compare ( EFF_DATE_CHECK_ARG ) == 0 ) // If Workflow argument is for Effectivity Date Validation
        {
            bool bMBOMExist = false;
            bool bBOPExist  = false;

            vector<string>  vBOPObjRevPrefValues;
            vector<string>  vMBOMObjRevPrefValues;

            // Get the all BOP object type revisions from the preference
            getStringPrefValues ( GET6_BOP_OBJECT_REVISION_TYPES, vBOPObjRevPrefValues );

            if ( vBOPObjRevPrefValues.size() == 0 )
            {
                string sMessage = "The Preference " + string ( GET6_BOP_OBJECT_REVISION_TYPES ) + " is not defined or does not have a value";
                THROW ( sMessage );
            }

            // Get the all valid MBOM and EBOM object type revisions from the preference
            getStringPrefValues ( CM_VALID_MCN_OBJECTS, vMBOMObjRevPrefValues );

            if ( vMBOMObjRevPrefValues.size() == 0 )
            {
                string sMessage = "The Preference " + string ( CM_VALID_MCN_OBJECTS ) + " is not defined or does not have a value";
                THROW ( sMessage );
            }

            // Get all objects from solution folder of MCN object
            vector<GET_POM_objectUnqPtr> vSolItemsUnqPtr = getMCNRevShrPtr->getPropTags ( CM_HAS_SLITEMS_PROP );

            // Loop through each objects in Solution Item folder
            for ( size_t iSolIndex = 0; iSolIndex < vSolItemsUnqPtr.size(); iSolIndex++ )
            {
                GET_WorkspaceObjectShrPtr getWorkspaceShrPtr ( move ( GET_WorkspaceObject::getInstance ( vSolItemsUnqPtr[iSolIndex]->getTag() ) ) );

                // Check if the Solution object is of type MBOM or EBOM
                if ( ( bMBOMExist == false ) && ( std::find ( vMBOMObjRevPrefValues.begin(), vMBOMObjRevPrefValues.end(),
                        getWorkspaceShrPtr->getType() ) != vMBOMObjRevPrefValues.end() ) )
                {
                    bMBOMExist = true;
                }
                else if ( ( bBOPExist == false ) && ( std::find ( vBOPObjRevPrefValues.begin(), vBOPObjRevPrefValues.end(),
                        getWorkspaceShrPtr->getType() ) != vBOPObjRevPrefValues.end() ) )
                {
                    bBOPExist = true;
                }
            }

            if ( bMBOMExist == true )
            {
                // Check for MBOM Start Effectivity Date
                if ( ( getMCNRevShrPtr->getPropertyDate ( MBOM_EFF_START_DATE_PROP )->toString() ).empty() )
                {
                    sConsolidatedErrorMessage.append ( "\n" );
                    sConsolidatedErrorMessage.append ("MBOM Start Effectivity Date is empty, please provide the value ");
                }
            }
            if ( bBOPExist == true )
            {
                if ( ( getMCNRevShrPtr->getPropertyDate ( BOP_EFF_START_DATE_PROP )->toString() ).empty() )
                {
                    sConsolidatedErrorMessage.append ( "\n" );
                    sConsolidatedErrorMessage.append ("BOP Start Effectivity Date is empty, please provide the value ");
                }
            }

            LOG_TRACE ( logger, "sConsolidatedErrorMessage.size()..." + sConsolidatedErrorMessage.size() );
            if ( sConsolidatedErrorMessage.size() > 0 )
            {
                // Throw the error to the calling method (Where it will be handled)
                THROW ( sConsolidatedErrorMessage );
            }
        }

        // Break the loop as MCN Revision has found
        break;
    }

    LOG_TRACE ( logger, "Exiting.... : GET6_checkMCNPropsRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_mcnCtrlAttributesRH()
//
//    Purpose:   Rule Handler to check MCN Control attributes
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team             11 Oct, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_mcnCtrlAttributesRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_mcnCtrlAttributesRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_mcnCtrlAttributesRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_mcnCtrlAttributesRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_mcnCtrlAttributesRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_mcnCtrlAttributesRH_impl()
//
//    Purpose:   Rule Handler implementation function for MCN Control attributes GET6_mcnCtrlAttributesRH handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team             17 Oct, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_mcnCtrlAttributesRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START.... : GET6_mcnCtrlAttributesRH_impl" );

    vector<tag_t> vTargetObjects;
    vector <string> vErrorMessages;
    vector <string> vTaskName;
    string sTaskResult;
    string sAffectBOPDecision;
    string sEffectivityDecision;
    GET_ItemRevisionUnqPtr getMCNRevUnqPtr;

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( TASK_NAME_ARG ) == mArgumentsMap.end () || mArgumentsMap[TASK_NAME_ARG].empty () )
    {
        THROW ( string ( "The argument \"" ) + TASK_NAME_ARG + string ( "\" is not provided or has empty value" ) );
    }

    // Get the Target Objects from the Workflow Target Attachments
    vTargetObjects = mAttachmentsMap[EPM_target_attachment];

    GET_splitString ( mArgumentsMap[TASK_NAME_ARG], COMMA_CHARACTER, vTaskName );

    GET_EPMTaskUnqPtr getTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );
    GET_EPMTaskShrPtr getTaskShrPtr ( move ( getTaskUnqPtr ) );

    for ( size_t iIndex = 0; iIndex < vTargetObjects.size(); iIndex++ )
    {
        // Validate if MCN Revision is found in target object
        if ( ! GET_POM_object::isDescendant  (vTargetObjects[iIndex], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }
        getMCNRevUnqPtr = GET_ItemRevision::getInstance ( vTargetObjects[iIndex] );
        break;
    }

    GET_ItemRevisionShrPtr getMCNRevShrPtr ( move ( getMCNRevUnqPtr ) );
    sAffectBOPDecision = getMCNRevShrPtr->getPropString ( AFFECT_BOP_DECISION_PROP );
    sEffectivityDecision = getMCNRevShrPtr->getPropString ( EFF_DECISION_PROP );

    vector<GET_EPMTaskUnqPtr> vTasksUnqPtr = getTaskShrPtr->getSubTasks();

    // Loop through each input task names
    for ( int iInx = 0; iInx < vTaskName.size(); iInx++ )
    {
    	for ( int iJnx = 0; iJnx < vTasksUnqPtr.size(); iJnx++ )
    	{
    		if ( vTasksUnqPtr[iJnx]->getPropString ( OBJECT_NAME_ATTR ).compare ( vTaskName[iInx] ) == 0 )
    		{
    			string sTaskResult;

    			vTasksUnqPtr[iJnx]->getDecision ( sTaskResult );

    			if ( sTaskResult.compare ( TASK_UNSET_RESULT ) != 0 )
    			{
                    if ( vTaskName[iInx].compare ( AFFECTS_BOP_TASK ) == 0 )
                    {
                        if ( sAffectBOPDecision.compare ( sTaskResult ) != 0 )
                        {
                            string sErrorMessage ="You are not entitled to modify Affect BOP Decision property";
                            vErrorMessages.push_back ( sErrorMessage );
                        }
                    }
                    if ( vTaskName[iInx].compare ( EFFECTIVITY_DECISION_TASK ) == 0 )
                    {
                        if ( sEffectivityDecision.compare ( sTaskResult ) != 0 )
                        {
                            string sErrorMessage ="You are not entitled to modify Effectivity decision property";
                            vErrorMessages.push_back ( sErrorMessage );
                        }
                    }
    			}
    		}
    	}
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "";
        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size(); iIndex++ )
        {
            sConsolidatedErrorMessage += vErrorMessages[iIndex];
            if ( iIndex < ( vErrorMessages.size() - 1 ) )
            {
                sConsolidatedErrorMessage += "\n";
            }
        }

        // Throw the error to the calling method (Where it will be handled)
        THROW ( sConsolidatedErrorMessage );
    }

    LOG_TRACE ( logger, "END.... : GET6_mcnCtrlAttributesRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateMCNEffectivityPropsRH()
//
//    Purpose:   Rule Handler to check validity of MCN Effectivity dates
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team             25 Oct, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateMCNEffectivityPropsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_mcnCtrlAttributesRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateMCNEffectivityPropsRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_mcnCtrlAttributesRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_mcnCtrlAttributesRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateMCNEffectivityPropsRH_impl()
//
//    Purpose:   Rule Handler implementation function to check for valid MCN Effectivity dates
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team             25 Oct, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateMCNEffectivityPropsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START.... : GET6_validateMCNEffectivityPropsRH_impl" );

    bool bIsMBOMInSolnItem = false;

    vector<tag_t> vTargetObjects;
    vector <string> vErrorMessages;

    GET_ItemRevisionUnqPtr getMCNRevUnqPtr;

    // Get the Target Objects from the Workflow Target Attachments
    vTargetObjects = mAttachmentsMap[EPM_target_attachment];

    for ( size_t iIndex = 0; iIndex < vTargetObjects.size(); iIndex++ )
    {
        // Validate if MCN Revision is found in target object
        if ( ! GET_POM_object::isDescendant ( vTargetObjects[iIndex], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }
        getMCNRevUnqPtr = GET_ItemRevision::getInstance ( vTargetObjects[iIndex] );
        break;
    }

    GET_ItemRevisionShrPtr getMCNRevShrPtr ( move ( getMCNRevUnqPtr ) );

    string sAffectBOPDecision = getMCNRevShrPtr->getPropString ( AFFECT_BOP_DECISION_PROP );

    vector<GET_POM_objectUnqPtr> vSolutionItems = getMCNRevShrPtr->getPropTags ( CM_HAS_SLITEMS_PROP );
    for ( int iInx = 0; iInx < vSolutionItems.size(); iInx++ )
    {
    	if ( ( vSolutionItems[iInx]->askTypeName().compare ( MECHREV_TYPE ) == 0 ) || ( vSolutionItems[iInx]->askTypeName().compare ( MFGREV_TYPE ) == 0 ) )
        {
    		bIsMBOMInSolnItem = true;
    		break;
        }
    }

    //Check Effectivity dates for both MBOM and BOP
    if ( ( bIsMBOMInSolnItem == true ) && ( sAffectBOPDecision.compare ( MCN_LOV_TRUE_VALUE ) == 0 ) )
    {
    	GET_DateUnqPtr MBOMEffStartDateUnqPtr = getMCNRevShrPtr->getPropertyDate ( MBOM_EFF_START_DATE_PROP );
    	GET_DateUnqPtr MBOMEffEndDateUnqPtr   = getMCNRevShrPtr->getPropertyDate ( MBOM_EFF_END_DATE_PROP );
    	GET_DateUnqPtr BOPEffStartDateUnqPtr = getMCNRevShrPtr->getPropertyDate ( BOP_EFF_START_DATE_PROP );
    	GET_DateUnqPtr BOPEffEndDateUnqPtr   = getMCNRevShrPtr->getPropertyDate ( BOP_EFF_END_DATE_PROP );

    	GET_DateShrPtr MBOMEffStartDateShrPtr ( move ( MBOMEffStartDateUnqPtr ) );
    	GET_DateShrPtr BOPEffStartDateShrPtr ( move ( BOPEffStartDateUnqPtr ) );

    	if ( ! MBOMEffEndDateUnqPtr->toString().empty() )
    	{
    	    if ( MBOMEffEndDateUnqPtr->compare ( MBOMEffStartDateShrPtr ) == -1 )
    		{
    			string sErrorMessage = "MBOM Effectivity End date that is entered is less than the MBOM Effectivity Start date";
    			vErrorMessages.push_back ( sErrorMessage );
    		}
    	}

    	if ( ! BOPEffEndDateUnqPtr->toString().empty() )
    	{
    		if ( BOPEffEndDateUnqPtr->compare ( BOPEffStartDateShrPtr ) == -1 )
    		{
    			string sErrorMessage = "BOP Effectivity End date that is entered is less than the BOP Effectivity Start date";
    			vErrorMessages.push_back ( sErrorMessage );
    		}
    	}

    	if ( BOPEffStartDateShrPtr->compare ( MBOMEffStartDateShrPtr ) == -1  )
    	{
			string sErrorMessage = "BOP Effectivity Start date that is entered is less than the MBOM Effectivity Start date";
			vErrorMessages.push_back ( sErrorMessage );
    	}
    }

    //Check Effectivity Dates for MBOM if BOP is false
    if ( ( bIsMBOMInSolnItem == true ) && ( sAffectBOPDecision.compare ( MCN_LOV_FALSE_VALUE ) == 0 ) )
    {
    	GET_DateUnqPtr MBOMEffStartDateUnqPtr = getMCNRevShrPtr->getPropertyDate ( MBOM_EFF_START_DATE_PROP );
    	GET_DateUnqPtr MBOMEffEndDateUnqPtr = getMCNRevShrPtr->getPropertyDate ( MBOM_EFF_END_DATE_PROP );
    	if ( ! MBOMEffEndDateUnqPtr->toString().empty() )
    	{
    		GET_DateShrPtr MBOMEffStartDateShrPtr ( move ( MBOMEffStartDateUnqPtr ) );
            if ( MBOMEffEndDateUnqPtr->compare ( MBOMEffStartDateShrPtr ) == -1 )
    		{
    			string sErrorMessage = "MBOM Effectivity End date that is entered is less than the MBOM Effectivity Start date";
    			vErrorMessages.push_back ( sErrorMessage );
    		}
    	}
    }

    //  //Check Effectivity Dates for BOP Only
    if ( ( bIsMBOMInSolnItem == false ) && ( sAffectBOPDecision.compare ( MCN_LOV_TRUE_VALUE ) == 0 ) )
    {
    	GET_DateUnqPtr BOPEffStartDateUnqPtr = getMCNRevShrPtr->getPropertyDate ( BOP_EFF_START_DATE_PROP );
    	GET_DateUnqPtr BOPEffEndDateUnqPtr   = getMCNRevShrPtr->getPropertyDate ( BOP_EFF_END_DATE_PROP );

    	if ( ! BOPEffEndDateUnqPtr->toString().empty() )
    	{
    		GET_DateShrPtr BOPEffStartDateShrPtr ( move ( BOPEffStartDateUnqPtr ) );
    		if ( BOPEffEndDateUnqPtr->compare ( BOPEffStartDateShrPtr ) == -1 )
    		{
    			string sErrorMessage = "BOP Effectivity End date that is entered is less than the BOP Effectivity Start date";
    			vErrorMessages.push_back ( sErrorMessage );
    		}
    	}
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "";
        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size(); iIndex++ )
        {
            sConsolidatedErrorMessage += vErrorMessages[iIndex];
            if ( iIndex < ( vErrorMessages.size() - 1 ) )
            {
                sConsolidatedErrorMessage += "\n";
            }
        }
        // Throw the error to the calling method (Where it will be handled)
        THROW ( sConsolidatedErrorMessage );
    }

    LOG_TRACE ( logger, "END.... : GET6_validateMCNEffectivityPropsRH_impl" );
}


/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkUsersProjectRH()
//
//    Purpose:   Rule Handler to check user session project
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team             20 June, 2018         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_checkUsersProjectRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_checkUsersProjectRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_checkUsersProjectRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_checkUsersProjectRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_checkUsersProjectRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkUsersProjectRH_impl()
//
//    Purpose:    Rule Handler to check usersession project
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team             20 June, 2018         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_checkUsersProjectRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
	ResultCheck stat;
	vector<string> vErrorMessages;
	vector<string> vSelectedOrgID;
	vector<string> vAssignedProjectIds;
	vector<string> vMCNOrgList;

	vector <GET_TC_ProjectUnqPtr> vAssignedProjectUnqPtr;
	map <string, vector<string>> 	mItemIdsToPropValues;

	LOG_TRACE ( logger, "START.... : GET6_checkUsersProjectRH_impl" );

	// Clear the existing error stack
	stat = EMH_clear_errors();

	// Get the all MCN Org List from the preference
	getStringPrefValues ( MCN_ORG_LIST, vMCNOrgList );

    mItemIdsToPropValues = readMultiOrgList ( tTaskTag, mAttachmentsMap, mArgumentsMap );
    LOG_TRACE ( logger, "mItemIdsToPropValues.size()--> " + mItemIdsToPropValues.size() );

	for ( std::map<string, vector<string>>::iterator itItemIdsToPropValues=mItemIdsToPropValues.begin(); itItemIdsToPropValues!=mItemIdsToPropValues.end(); ++itItemIdsToPropValues )
	{
		string			itemId;
		vector <string> vPropValue;

		itemId 		= itItemIdsToPropValues->first;
		vPropValue 	= itItemIdsToPropValues->second;
		LOG_TRACE ( logger, "ItemId--> " + itemId );

		std::map<string, string>::iterator it;

		for ( size_t iPropValueIndex=0; iPropValueIndex < vPropValue.size(); iPropValueIndex++ )
		{
			LOG_TRACE ( logger, "vPropValue--> " + vPropValue[iPropValueIndex] );
			if ( vPropValue[iPropValueIndex].compare ( CM_LOV_YES_VALUE ) == 0 )
			{
				bool bProjAlreadyExists = GET_isInVector ( vSelectedOrgID, vMCNOrgList[iPropValueIndex] );

				if ( !bProjAlreadyExists )
				{
					vSelectedOrgID.push_back ( vMCNOrgList[iPropValueIndex] );
				}
			}
		}
	}

	LOG_TRACE ( logger, "vSelectedOrgID.size()--> " + vSelectedOrgID.size() );

    //If Affected Org property is not empty then
    //Perform the validations to deriving an MCN
    if ( vSelectedOrgID.size() > 0 )
    {
    	GET_UserSessionUnqPtr userSessionUnqPtr = GET_UserSession::getCurrentUserSession();

    	GET_TC_ProjectShrPtr projTagShrPtr = userSessionUnqPtr->getProject();
    	GET_POM_userShrPtr pomUserShrPtr = userSessionUnqPtr->getUser();

    	 vAssignedProjectUnqPtr = pomUserShrPtr->getAssignedProjects ( true, true );
    	 LOG_TRACE ( logger, "vAssignedProjectUnqPtr.size()--> " + vAssignedProjectUnqPtr.size() );

    	 //Loop to check, if user is member of a project
		 if ( vAssignedProjectUnqPtr.size() == 0 )
		 {
			 THROW ( "User is not a member of any Projects." );
		 }

    	 //Check User session value, if it is not blank then throw a error.
    	 if ( projTagShrPtr != NULL)
    	 {
    		 string sErrorMessage = string ( "Please make your Session Project blank");
    		 vErrorMessages.push_back ( sErrorMessage );
    	 }

    	 //Get project ids
    	 for ( int iIndex = 0; iIndex < vAssignedProjectUnqPtr.size(); iIndex++ )
    	 {
    		 vAssignedProjectIds.push_back ( vAssignedProjectUnqPtr[iIndex]->getProjectId() );
    	 }

    	 //Loop to verify if user belong to an orgs selected to Derive a MCN.
    	 for ( size_t iAffOrgIndex = 0; iAffOrgIndex < vSelectedOrgID.size(); iAffOrgIndex++ )
    	 {
    		bool bProjExists = false;

    		//Check whether User present in the org selected to derive an MCN
			bProjExists = GET_isInVector ( vAssignedProjectIds, vSelectedOrgID[iAffOrgIndex] );
    		if ( bProjExists == false )
    		{
    			 string sErrorMessage = string ( "MCN cannot be derived for :"+ vSelectedOrgID[iAffOrgIndex] +" as user is not a member of " + vSelectedOrgID[iAffOrgIndex]+ " ORG" );
    			 vErrorMessages.push_back ( sErrorMessage );
    		}
    	 }
     }

    // Store the error messages, if any in the Teamcenter Error Stack
	if ( vErrorMessages.size() > 0 )
	{
		string sConsolidatedErrorMessage = "";
		// Store the errors one by one in the stack
		for ( size_t iIndex = 0; iIndex < vErrorMessages.size(); iIndex++ )
		{
			sConsolidatedErrorMessage += vErrorMessages[iIndex];
			if ( iIndex < ( vErrorMessages.size() - 1 ) )
			{
				sConsolidatedErrorMessage += "\n";
			}
		}

		// Throw the error to the calling method (Where it will be handled)
		THROW ( sConsolidatedErrorMessage );
	}
	LOG_TRACE ( logger, "END.... : GET6_checkUsersProjectRH_impl" );
}

