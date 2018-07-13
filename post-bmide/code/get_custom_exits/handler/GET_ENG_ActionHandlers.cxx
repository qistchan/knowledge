
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ENG_ActionHandlers.cxx
//
//    Purpose:   Source File defining the Engineering Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Jul, 2016         Initial creation
//  TCS Development Team     23 May, 2017         Added handler implementation for creating BOM Index request dataset
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_BOMWindow.hxx>
#include <GET_ENG_ActionHandlers.hxx>
#include <GET_EPMTask.hxx>
#include <GET_Exception.hxx>
#include <GET_Errors.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_TC_Types.hxx>
#include <GET_Constants.hxx>
#include <GET_Utils.hxx>
#include <GET_DispatcherRequest.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_ImanTextFile.hxx>

// Teamcenter Includes
#include <tc/emh.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

using namespace get;

// Private Function Prototypes

void GET6_createBaselineAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_PropagatePORAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_createBOMIndexReqDatasetAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );

const string logger = "get.handler.GET_ENG_ActionHandlers";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_createBaselineAH()
//
//    Purpose:   Handler to create Baseline for the target Revision
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    Integer indicating ITK_ok or error codes
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     06 Jul, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_createBaselineAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_createBaselineAH" );

    try
    {
        GET_processHandler ( tMessage, GET6_createBaselineAH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_createBaselineAH" );
    }

    LOG_TRACE ( logger, "END : GET6_createBaselineAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_createBaselineAH_impl()
//
//    Purpose:   Implementation business logic for GET6_createBaselineAH handler
//
//    Inputs:    none
//
//    Outputs:   tTaskTag - tag value of the root task
//               vAttachments - a vector containing attachments tag values
//               mArgumentsMap - a string map containing handler arguments and its values
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     06 Jul, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_createBaselineAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
    // Boolean to indicate whether the current target is an assembly or not
    bool bIsAssy = false;

    LOG_TRACE ( logger, "START : GET6_createBaselineAH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( BASELINE_PROCESS_TYPE_ARG ) == mArgumentsMap.end() ||
         ( mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( BASELINE_PROCESS_TYPE_VALUE ) != 0 &&
           mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( PRELIMINARY_PROCESS_TYPE_VALUE ) != 0 ) )
    {
        string sMsg = "The Workflow handler argument \"" + string ( BASELINE_PROCESS_TYPE_ARG ) + "\" is either empty or has an invalid value";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( BASELINE_TEMPLATE_ARG ) == mArgumentsMap.end() ||
         mArgumentsMap[BASELINE_TEMPLATE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( BASELINE_TEMPLATE_ARG ) + "\" is either empty or has an invalid value";
        THROW ( sMsg );
    }

    // Get the target Revision Object
    GET_ItemRevisionUnqPtr itemRevisionUnqPtr = GET_ItemRevision::getInstance ( vAttachments[EPM_target_attachment][0] );
    GET_ItemRevisionShrPtr itemRevPtr ( move ( itemRevisionUnqPtr ) );

    // Check if the Target Revision is an assembly or not
    vector<GET_POM_objectUnqPtr> childObjectsVector = itemRevPtr->getPropTags ( PSCHILDREN_ATTR );
    if ( childObjectsVector.size() > 0 )
    {
        bIsAssy = true;
    }

    // Check if the Revision Rule Argument is provided in the Handler
    if ( bIsAssy && mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( BASELINE_PROCESS_TYPE_VALUE ) == 0 &&
         ( mArgumentsMap.find ( REVISION_RULE_ARG ) == mArgumentsMap.end() || mArgumentsMap[REVISION_RULE_ARG].empty() ) )
    {
        string sMsg = "The Workflow handler argument \"" + string ( REVISION_RULE_ARG ) + "\" is not provided or has an empty value";
        THROW ( sMsg );
    }

    // Remove the currently selected ItemRevision from the Target list
    GET_EPMTaskUnqPtr epmTaskPtr = GET_EPMTask::getInstance ( tTaskTag );
    vector<GET_POM_objectShrPtr> vAttachObjects;
    vAttachObjects.push_back ( itemRevPtr );
    epmTaskPtr->removeAttachments ( vAttachObjects );
    LOG_DEBUG ( logger, "Removed base item revision from targets" );

    // Create Baseline/Preliminary Release based on Structure Conditions
    if ( bIsAssy && mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( BASELINE_PROCESS_TYPE_VALUE ) == 0 )
    {
        LOG_DEBUG ( logger, "Baselining assembly" );
        // Create a BOM Window and apply Baseline to the BOM Window
        GET_BOMWindowUnqPtr bomWindowPtr = GET_BOMWindow::create();
        bomWindowPtr->setRevisionRule ( mArgumentsMap[REVISION_RULE_ARG] );
        GET_BOMViewRevisionShrPtr bvrShrPtr;
        GET_BOMLineUnqPtr topBOMLinePtr = bomWindowPtr->setTopLine ( itemRevPtr, bvrShrPtr );
        bomWindowPtr->baseline ( "", BASELINE_PROCESS_TYPE_VALUE, mArgumentsMap[BASELINE_TEMPLATE_ARG], "", "" );
    }
    else
    {
        LOG_DEBUG ( logger, "Baselining pc part" );
        itemRevPtr->baseline ( "", BASELINE_PROCESS_TYPE_VALUE, mArgumentsMap[BASELINE_TEMPLATE_ARG], "", "" );
    }

    LOG_TRACE ( logger, "END : GET6_createBaselineAH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_PropagatePORAH()
//
//    Purpose:   Action Handler to add targets to given targets related project object relation
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_PropagatePORAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     07 Nov, 2016          Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_PropagatePORAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE(logger, "START : GET6_PropagatePORAH");

    try
    {
        GET_processHandler ( tMessage, GET6_PropagatePORAH_impl, false );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_PropagatePORAH" );
    }

    LOG_TRACE ( logger, "END : GET6_PropagatePORAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_PropagatePORAH_impl()
//
//    Purpose:   Action Handler Implementation to add target to given targets related project object relation
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     07 Nov, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_PropagatePORAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
    vector <string> vIncludeType;
    vector <string> vExcludeType;
    vector <string> vRefType;
    vector <string> vRefProp;

    vector <tag_t> vTargetAttachments = vAttachments[EPM_target_attachment];
    vector <tag_t> vRefAttachments = vAttachments[EPM_reference_attachment];

    GET_POM_objectUnqPtr porPtr;
    GET_WorkspaceObjectUnqPtr wsoSourceRefPtr;

    LOG_TRACE( logger, "START: GET6_PropagatePORAH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( REFERENCE_TYPE_ARG ) == mArgumentsMap.end () || mArgumentsMap[REFERENCE_TYPE_ARG].empty () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( REFERENCE_TYPE_ARG ) + "\"  is missing or is empty";
        THROW( sMsg );
    }
    if ( mArgumentsMap.find ( PROPERTY_ARG ) == mArgumentsMap.end () || mArgumentsMap[PROPERTY_ARG].empty () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( PROPERTY_ARG ) + "\"  is missing or is empty";
        THROW( sMsg );
    }
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) != mArgumentsMap.end () && mArgumentsMap.find ( EXCLUDE_TYPE_ARG ) != mArgumentsMap.end () )
    {
        string sMsg = string ( INCLUDE_TYPE_ARG ) + " and " + string ( EXCLUDE_TYPE_ARG ) + " are mutually exclusive!!!";
        THROW( sMsg );
    }
    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );
    GET_splitString ( mArgumentsMap[EXCLUDE_TYPE_ARG], COMMA_CHARACTER, vExcludeType );
    GET_splitString ( mArgumentsMap[REFERENCE_TYPE_ARG], COMMA_CHARACTER, vRefType );
    GET_splitString ( mArgumentsMap[PROPERTY_ARG], COMMA_CHARACTER, vRefProp );

    //Get POR from source type
    for ( int iIndex = 0; iIndex < vRefAttachments.size (); iIndex++ )
    {
        wsoSourceRefPtr = GET_WorkspaceObject::getInstance ( vRefAttachments[iIndex] );
        string sRefObjType = wsoSourceRefPtr->getType();

        if ( !GET_isInVector ( vRefType, sRefObjType ) )
        {
            continue;
        }

        GET_POMReferencersUnqPtr pPomReferences = wsoSourceRefPtr->getPomReferences();
        for ( size_t iRefIndex = 0; iRefIndex < pPomReferences->iNoInstances; ++iRefIndex )
        {
            if ( !GET_POM_object::isDescendant ( pPomReferences->vRefInstances[iRefIndex]->getTag(), PROJECTOBJECTRELATION_TYPE ) )
            {
                continue;
            }
            porPtr = GET_POM_object::getInstance ( pPomReferences->vRefInstances[iRefIndex]->getTag() );
            break;
        }
        break;
    }

    if ( porPtr && porPtr.get() != NULL )
    {
        vector<GET_POM_objectUnqPtr> vPropObjList = porPtr->getPropertyTags ( PROPAGATION_OBJ_LIST_ATTR );
        vector <tag_t> vPropObjTag;
        for ( size_t iVecIndex = 0; iVecIndex < vPropObjList.size(); ++iVecIndex )
        {
            vPropObjTag.push_back ( vPropObjList[iVecIndex]->getTag() );
        }

        vector<GET_POM_objectShrPtr> vObjToBeAdded;
        for ( int iIndex = 0; iIndex < vTargetAttachments.size (); iIndex++ )
        {
            if ( !GET_POM_object::isDescendant ( vTargetAttachments[iIndex], WORKSPACEOBJECT_CLASS ) ||
                    GET_isInVector ( vPropObjTag, vTargetAttachments[iIndex] ) )
            {
                continue;
            }
            GET_WorkspaceObjectUnqPtr wsoPtr = GET_WorkspaceObject::getInstance ( vTargetAttachments[iIndex] );
            string sObjType = wsoPtr->getType();

            if (  ( vIncludeType.empty() && vExcludeType.empty() ) ||
                    ( ( !vIncludeType.empty() && GET_isInVector ( vIncludeType, sObjType ) ) ||
                    ( !vExcludeType.empty() && !GET_isInVector ( vExcludeType, sObjType  ) ) ) )
            {
                GET_POM_objectShrPtr poShrPtr ( move ( GET_POM_object::getInstance ( wsoPtr->getTag() ) ) );
                vObjToBeAdded.push_back ( poShrPtr );
            }
        }
        porPtr->appendProperty ( PROPAGATION_OBJ_LIST_ATTR, vObjToBeAdded );

        for ( size_t iIndex = 0; iIndex < vRefProp.size(); ++iIndex )
        {
            wsoSourceRefPtr->setProp ( vRefProp[iIndex], wsoSourceRefPtr->getPropString ( vRefProp[iIndex] ) );
        }
    }

    LOG_TRACE( logger, "END: GET6_PropagatePORAH_impl" );
}
/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_createBOMIndexReqDatasetAH()
//
//    Purpose:   Action Handler to create the text dataset required for BOM Index request creation
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_BOMIndexTransReqAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     23 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_createBOMIndexReqDatasetAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE(logger, "START : GET6_createBOMIndexReqDatasetAH");

    try
    {
        GET_processHandler ( tMessage, GET6_createBOMIndexReqDatasetAH_impl, false );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_createBOMIndexReqDatasetAH" );
    }

    LOG_TRACE ( logger, "END : GET6_createBOMIndexReqDatasetAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_createBOMIndexReqDatasetAH_impl()
//
//    Purpose:   Action Handler implementation to create the text dataset required for BOM Index request creation
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     23 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_createBOMIndexReqDatasetAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
    GET_EPMTaskUnqPtr currentTaskUnqPtr;
    GET_ItemRevisionUnqPtr targetRevisionUnqPtr;
    GET_RevisionRuleUnqPtr revRulePtr;

    string sSecondaryObjectType = "";
    string sFileContents = "";

    vector<tag_t> vTargetAttachments;

    LOG_TRACE ( logger, "START: GET6_createBOMIndexReqDatasetAH_impl" );

    if ( mArgumentsMap.find ( REVISION_RULE_ARG ) == mArgumentsMap.end () || mArgumentsMap[REVISION_RULE_ARG].empty () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( REVISION_RULE_ARG ) + "\"  is missing or is empty";
        THROW( sMsg );
    }
    revRulePtr = GET_RevisionRule::find ( mArgumentsMap[REVISION_RULE_ARG] ) ;
    if ( revRulePtr.get() == NULL )
    {
        THROW ( "No Revision Rule with the name \"" + mArgumentsMap[REVISION_RULE_ARG] + "\" found in Teamcenter" );
    }

    vTargetAttachments = vAttachments[EPM_target_attachment];
    currentTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );
    for ( size_t iIndex = 0; iIndex < vTargetAttachments.size(); ++iIndex )
    {
        GET_POM_objectUnqPtr pomObjectPtr = GET_POM_object::getInstance ( vTargetAttachments[iIndex] );

        // Proceed only if we get an ECN Revision object
        if ( pomObjectPtr->askTypeName().compare ( ECNREVISION_TYPE ) != 0 )
        {
            continue;
        }
        targetRevisionUnqPtr = GET_ItemRevision::getInstance ( vTargetAttachments[iIndex] );
        break;
    }
    if ( targetRevisionUnqPtr.get() == NULL )
    {
        THROW ( "Engineering Change Notice Revision not found in Target List" );
    }

    GET_ItemRevisionShrPtr ecnRevisionShrPtr ( move ( targetRevisionUnqPtr ) );
    string sOrginalFileName = ecnRevisionShrPtr->getItem()->getId() + DOT_CHARACTER + TEXT_FILE_EXTENSION;

    // Get the solution items of ECN
    vector<GET_POM_objectUnqPtr> vSolutionItems = GET_ImanRelation::listRelatedObjects ( ecnRevisionShrPtr, CM_HAS_SOLUTION_ITEMS_PROP, false );
    for ( size_t iNumSol = 0; iNumSol < vSolutionItems.size(); iNumSol++ )
    {
        //Get the solution item ID
        GET_ItemRevisionUnqPtr solItemRevisionPtr = GET_ItemRevision::getInstance ( vSolutionItems[iNumSol]->getTag() );
        GET_ItemUnqPtr solItemPtr = solItemRevisionPtr->getItem();
        string solItemId = solItemPtr->getId();
        string solItemRevId = solItemRevisionPtr->getRevId();

        // Check if the Target Revision is an assembly or not
        vector<GET_POM_objectUnqPtr> childObjectsVector = solItemRevisionPtr->getPropTags ( PSCHILDREN_ATTR );
        if ( childObjectsVector.size() == 0 )
        {
            continue;
        }

        sFileContents = sFileContents + BOM_INDEX_ITEMID_PREFIX + solItemRevisionPtr->getItem()->getId() + PIPE_SEPERATOR + solItemRevisionPtr->getRevId() + PIPE_SEPERATOR
                     + mArgumentsMap[REVISION_RULE_ARG] + PIPE_SEPERATOR + PIPE_SEPERATOR + PIPE_SEPERATOR + PIPE_SEPERATOR + PIPE_SEPERATOR + VDS_ARGUMENT + PIPE_SEPERATOR + "\n";
    }

    // Create the dataset, attach it to the ECN Revision as well as the WF Targets
    if ( ! sFileContents.empty() )
    {
        GET_POM_objectShrPtr relDataPtr;

        vector<GET_POM_objectShrPtr> vAttachmentsVector;

        // Create the text file in Teamcenter
        GET_ImanTextFileUnqPtr iManFileUnqPtr = GET_ImanTextFile::createInstance ( sFileContents, sOrginalFileName );

        // Create the dataset
        GET_DatasetUnqPtr dsUnqPtr = GET_Dataset::createInstance ( TEXT_DATASET, TEXTEDITOR_TOOL, ecnRevisionShrPtr->getItem()->getId(), ecnRevisionShrPtr->getRevId(), "Text dataset for Automatic BOM Indexing" );

        // Import the created file as a Named Reference to the dataset
        GET_ImanFileShrPtr iManFileShrPtr ( move ( iManFileUnqPtr ) );

        // Relate the text dataset to the ECN Revision with Iman Specification relation
        GET_DatasetShrPtr dataSetShrPtr ( move ( dsUnqPtr ) );
        dataSetShrPtr->addNamedRef ( iManFileShrPtr, TEXT_REFNAME );
        GET_ImanRelation::create ( ecnRevisionShrPtr, dataSetShrPtr, IMAN_SPECIFICATION, relDataPtr );

        // Add the dataset to the WF Target
        vAttachmentsVector.push_back ( dataSetShrPtr );
        currentTaskUnqPtr->addAttachments ( EPM_target_attachment, vAttachmentsVector );
    }

    LOG_TRACE ( logger, "END: GET6_createBOMIndexReqDatasetAH_impl" );
}
