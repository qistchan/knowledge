
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ENG_RuleHandlers.cxx
//
//    Purpose:   Source File defining the Engineering Rule Handler Implementations
//
//    History:
//      Who                         Date                 Description
//  TCS Development Team           28 Apr, 2016         Initial creation
//  TCS Development Team           14 Jul, 2016         Modified the code for changes in attribute types from string to boolean
//  TCS Development Team           15 Jul, 2016         Added the handler implementation for validating GET Document Revision
//  TCS Development Team           21 Jul, 2016         Modified the GET6_validateDocumentsRH_impl method to check only Item Revision instances
//  TCS Development Team           27 Oct, 2016         Added handler implementation for validating Materials associated with a Production Part
//  Capgemini Development Team     07 Feb, 2017         Added handler implementation for validating Group and Properties associated with an ECR for Mining
//  Capgemini Development Team     16 Feb, 2017         Modified the GET6_validateParticipantsRH_impl method to check Explosive Atmosphere Compliance participant
//  TCS Development Team           11 Apr, 2017         Modified GET6_validateDocumentsRH_impl method to validate presence of Named Reference file
//                                                      and rename Dataset and Named Reference file to Item ID
//  TCS Development Team           04 May, 2017         Added code to include piece parts with "Made from Parts" into the Preliminary Assy Process
//  TCS Development Team           12 May, 2017         Removed the unwanted function declaration GET6_validateInitiatorRH_impl from this file
//  TCS Development Team           15 May, 2017         Added Handler method implementation for Validating Checkmate results
//  TCS Development Team           06 Jul, 2017         Corrected the code to fix spacing errors
//  TechM Development Team         02 Aug, 2017         Modified error messages across this file
//  Ganesh Ubale                   08 Aug, 2017         Modified Handler method to include UGPART dataset for Validating Checkmate results
//  TCS Development Team           09 Aug, 2017         Fix the defect in GET6_validateCheckmateResultsRH_impl method to make sure all dataset types are validated
//  TechM Development Team         30 Aug, 2017         Updated GET6_validateParticipantsRH_impl with MFG CutIn participant validation
//  Ganesh Ubale                   01-Nov, 2017          Added Service Approval participant validation
//  TechM Development Team         15 Dec, 2017         Updated GET6_validateMaterialsRH_impl with Made from Part validation
//  TCS Development Team           30 May, 2018         Modified the GET6_validateDocumentsRH_impl method to set the dataset name to item_id/rev_id
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_AM_PRIVS.hxx>
#include <GET_BOMLine.hxx>
#include <GET_BOMWindow.hxx>
#include <GET_ENG_RuleHandlers.hxx>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_Form.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_Item.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Participant.hxx>
#include <GET_POM_user.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_GroupMember.hxx>
#include <GET_Utils.hxx>
#include <GET_Constants.hxx>
#include <GET_EPMTask.hxx>
#include <GET_EPMJob.hxx>

// Teamcenter Includes
#include <tc/emh.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// CPP Includes
#include <map>

using namespace get;

// Private Function Prototypes

static void GET6_validateParticipantsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_validateBaselineRqmtsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_validateDocumentsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static bool GET6_isParticipantFound ( const vector<GET_ParticipantShrPtr>, const string, const string, const bool );
static void GET6_validateMaterialsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_checkGroupObjectPropertyRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_validateCheckmateResultsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
static void GET6_validateWFRetrievalRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );

const string logger = "get.handler.GET_ENG_RuleHandler";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateParticipantsRH()
//
//    Purpose:   Rule Handler to validate the Participants added to the ECR object during the review process.
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateParticipantsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateParticipantsRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateParticipantsRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateParticipantsRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateParticipantsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateBaselineRqmtsRH()
//
//    Purpose:   Rule Handler to validate the Preconditions for Baselining a Part/Assembly
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateBaselineRqmtsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateBaselineRqmtsRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateBaselineRqmtsRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateBaselineRqmtsRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateBaselineRqmtsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateDocumentsRH()
//
//    Purpose:   Rule Handler to validate the Preconditions for GET Document Revision
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     15 Jul, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateDocumentsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateDocumentsRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateDocumentsRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateDocumentsRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateDocumentsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_isParticipantFound()
//
//    Purpose:   Method to find whether a given Participants List contains a Participant matching the given group/role or within the hierarchy
//
//    Inputs:    vParticipantsVector - A vector containing GET_Participant Smart Pointer Objects (vector<GET_ParticipantShrPtr>
//               sGroupName - The Group Name to me matched in the Participants List (string)
//               sRoleName - The Role Name to me matched in the Participants List (string)
//               bGroupHierarchy - Boolean flag to indicate whether to match the Teamcenter Organization hierarchy or not (bool)
//
//    Outputs:   A boolean flag indicating whether the given group/role exists in the input Participants List
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     10 Apr, 2016         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static bool GET6_isParticipantFound ( const vector<GET_ParticipantShrPtr> vParticipantsVector, const string sGroupName, const string sRoleName, const bool bGroupHierarchy )
{
    bool bFound = false;

    LOG_TRACE ( logger, "START : GET6_isParticipantFound" );

    for ( size_t iIndex = 0; iIndex < vParticipantsVector.size(); iIndex++ )
    {
        bool bIsRoleMatching = true;

        string sParticipantGroupName = "";
        string sParticipantRoleName = "";

        GET_GroupMemberUnqPtr groupMemberPtr = vParticipantsVector[iIndex]->getParticipantGroupMember();
        if ( groupMemberPtr.get() == NULL )
        {
            continue;
        }

        sParticipantGroupName = groupMemberPtr->getGroup()->getGroupFullName();
        sParticipantRoleName = groupMemberPtr->getRole()->getRoleName();

        if ( ! sRoleName.empty() && sRoleName.compare ( sParticipantRoleName ) != 0 )
        {
            bIsRoleMatching = false;
        }

        if ( bIsRoleMatching )
        {
            if ( bGroupHierarchy && sParticipantGroupName.find ( sGroupName ) != string::npos )
            {
                bFound = true;
            }
            else if ( sParticipantGroupName.compare ( sGroupName ) == 0 )
            {
                bFound = true;
            }
        }

        // Break the loop if the desired result is achieved
        if ( bFound )
        {
            break;
        }
    }

    LOG_TRACE ( logger, "END : GET6_isParticipantFound" );

    return bFound;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateMaterialsRH()
//
//    Purpose:   Rule Handler to validate the GET Materials associated with Production Parts
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     15 Jul, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateMaterialsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateMaterialsRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateMaterialsRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateMaterialsRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateMaterialsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateBaselineRqmtsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateBaselineRqmts handler
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
//  TCS Development Team     14 Jul, 2016         Initial Creation
//  TCS Development Team     04 May, 2017         Added code to include piece parts with "Made from Parts" into the Preliminary Assy Process
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateBaselineRqmtsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    // Boolean to indicate whether the current target is an assembly or not
    bool bIsAssy = false;

    // String to identify the Process Type - Baseline or Preliminary Release
    string sProcessType = "";

    LOG_TRACE ( logger, "START : GET6_validateBaselineRqmtsRH_impl" );

    // Validate the Workflow Targets and make sure that only 1 target is present
    if ( mAttachmentsMap[EPM_target_attachment].size() != 1 )
    {
        THROW ( "Only one Part can be selected as a Target for this Workflow Process" );
    }

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( BASELINE_PROCESS_TYPE_ARG ) == mArgumentsMap.end() ||
         ( mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( BASELINE_PROCESS_TYPE_VALUE ) != 0 &&
           mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( PRELIMINARY_PROCESS_TYPE_VALUE ) != 0 ) )
    {
        string sMsg = "The Workflow handler argument \"" + string ( BASELINE_PROCESS_TYPE_ARG ) + "\" is either empty or has an invalid value";
        THROW ( sMsg );
    }

    // Get the Part Revision Object
    GET_ItemRevisionUnqPtr itemRevisionUnqPtr = GET_ItemRevision::getInstance ( mAttachmentsMap[EPM_target_attachment][0] );
    GET_ItemRevisionShrPtr itemRevPtr ( move ( itemRevisionUnqPtr ) );

    // Check if the Target Revision is an assembly or not
    vector<GET_POM_objectUnqPtr> childObjectsVector = itemRevPtr->getPropTags ( PSCHILDREN_ATTR );
    if ( childObjectsVector.size() > 0 )
    {
        bIsAssy = true;
    }

    // Preliminary Release process should not be initiated on a Piece Part without a valid "Made From Part"
    if ( ! bIsAssy && mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( PRELIMINARY_PROCESS_TYPE_VALUE ) == 0 )
    {
        bool bIsValidPiecePart = false;

        vector<GET_POM_objectUnqPtr> vMadeFromPartsVector = itemRevPtr->getItem()->getPropTags ( MADE_FROM_PART_PROP );
        if ( vMadeFromPartsVector.size() > 0 )
        {
            GET_ItemUnqPtr madeFromPartItemPtr;

            vector<GET_ItemRevisionUnqPtr> vRevisions;

            // Get all the revisions and if there is even one released revision, its considered valid
            madeFromPartItemPtr = GET_Item::getInstance ( vMadeFromPartsVector[0]->getTag() );
            vRevisions = madeFromPartItemPtr->getRevisions();
            for ( size_t iIndex = 0; iIndex < vRevisions.size(); iIndex++ )
            {
                bIsValidPiecePart = vRevisions[iIndex]->hasReleaseStatus ( GET6RELEASED );
                if ( bIsValidPiecePart )
                {
                    break;
                }
            }
        }
        if ( ! bIsValidPiecePart )
        {
            string sMadeFromPartAttrName = itemRevPtr->getItem()->getPropDisplayName ( MADE_FROM_PART_PROP );
            THROW ( string ( "Preliminary Release Process can only be initiated on an Assembly or on a Piece Part with a valid Part attached with the relation \"" )
                    + sMadeFromPartAttrName + "\"" );
        }
    }

    // In Case of an Assembly, the Revision Rule Argument should also be provided
    if ( bIsAssy )
    {
        bool bFoundReleasedCompForPrelRelease = false;

        if ( mArgumentsMap.find ( REVISION_RULE_ARG ) == mArgumentsMap.end() || mArgumentsMap[REVISION_RULE_ARG].empty() )
        {
            string sMsg = "The Workflow handler argument \"" + string ( REVISION_RULE_ARG ) + "\" is not provided or has an empty value";
            THROW ( sMsg );
        }

        // Create a BOM Window and traverse the children of the target component
        GET_BOMWindowUnqPtr bomWindowPtr = GET_BOMWindow::create();
        bomWindowPtr->setRevisionRule ( mArgumentsMap[REVISION_RULE_ARG] );
        GET_BOMViewRevisionShrPtr bvrShrPtr;
        GET_BOMLineUnqPtr topBOMLinePtr = bomWindowPtr->setTopLine ( itemRevPtr, bvrShrPtr );

        // Traverse the assembly and in case of Baselining an assembly top level, make sure
        // that all its Sub-assemblies are also either baselined or released. It should not contain any working sub-assemblies.
        // In case of Preliminary Release of an assembly, it should contain at the least on released children
        vector<GET_BOMLineUnqPtr> vChildLinesVector = topBOMLinePtr->getChildren();
        for ( size_t iIndex = 0; iIndex < vChildLinesVector.size(); iIndex++ )
        {
            GET_ItemRevisionUnqPtr childRevisionPtr = vChildLinesVector[iIndex]->getItemRevision();
            if ( mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( BASELINE_PROCESS_TYPE_VALUE ) == 0 )
            {
                if ( ! childRevisionPtr->isReleased() && vChildLinesVector[iIndex]->getChildren().size() > 0 )
                {
                    string sMsg = "One of the Sub Assembly \"" + childRevisionPtr->getPropString ( OBJECT_STRING_ATTR )
                                + "\" is still in a Working state. Please baseline it first";
                    THROW ( sMsg );
                }
            }
            else
            {
                if ( childRevisionPtr->hasReleaseStatus ( GET6RELEASED ) )
                {
                    bFoundReleasedCompForPrelRelease = true;
                    break;
                }
            }
        }
        if ( mArgumentsMap[BASELINE_PROCESS_TYPE_ARG].compare ( PRELIMINARY_PROCESS_TYPE_VALUE ) == 0 &&
             ! bFoundReleasedCompForPrelRelease )
        {
            THROW ( "No Released children found under the Target Assembly. Preliminary Release requires at least one released children" );
        }
    }

    LOG_TRACE ( logger, "END : GET6_validateBaselineRqmtsRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateDocumentsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateDocuments handler
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
//  TCS Development Team     15 Jul, 2016         Initial Creation
//  TCS Development Team     21 Jul, 2016         Added checks to make sure that only Item Revisions are checked
//  TCS Development Team     11 Apr, 2017         Modified GET6_validateDocumentsRH_impl method to validate presence of Named Reference file  
//                                                and rename Dataset and Named Reference file to Item ID
//  TCS Development Team     30 May, 2018         Modified the code to set the dataset name to item_id/rev_id
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateDocumentsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    // Vector to store all the errors
    vector<string> vErrorMessages;

    vector<string>vAllowedItemRevType;

    // Vector to store the Target Document Revisions
    vector<tag_t> vTargetDocumentRevisions;

    LOG_TRACE ( logger, "START : GET6_validateDocumentsRH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[ RELATION_TYPE_ARG ].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vAllowedItemRevType );

    // Get the Target Document Revisions from the Workflow Target Attachments
    vTargetDocumentRevisions = mAttachmentsMap[EPM_target_attachment];

    // Loop through the Target list and find out if any Document Revision's Dataset Named Reference name does not match with its Item ID
    for ( size_t iIndex = 0; iIndex < vTargetDocumentRevisions.size(); iIndex++ )
    {
        // Check if the target is an ItemRevision or not
        if ( ! GET_POM_object::isDescendant ( vTargetDocumentRevisions[iIndex], ITEMREVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionUnqPtr docRevUnqPtr = GET_ItemRevision::getInstance ( vTargetDocumentRevisions[iIndex] );
        GET_ItemRevisionShrPtr docRevPtr ( move ( docRevUnqPtr ) );

        //Checking for GET Document or Purchase Spec Item Revision types
        if ( ! GET_isInVector ( vAllowedItemRevType, docRevPtr->getType() ) )
        {
            continue;
        }

        // Get the list of Documents Attached under the given relation
        vector<GET_WorkspaceObjectUnqPtr> relatedWsObjects = GET_ImanRelation::listRelatedWsObjects ( docRevPtr, mArgumentsMap[RELATION_TYPE_ARG],
                                                                                                      mArgumentsMap[DATASET_TYPE_ARG] );
        if ( relatedWsObjects.size() == 0 )
        {
            continue;
        }
        // Loop through the secondary Objects and check the Dataset Name & the Named References
        for ( size_t iLoopIndex = 0; iLoopIndex < relatedWsObjects.size(); iLoopIndex++ )
        {
            bool bIsFileFound = false;

            if ( ! GET_POM_object::isDescendant ( relatedWsObjects[iLoopIndex]->getTag(), DATASET_CLASS ) )
            {
                continue;
            }

            //To check if Named Reference of dataset is empty
            vector<GET_POM_objectUnqPtr> namedRefObjs = relatedWsObjects[iLoopIndex]->getPropTags ( REFLIST_ATTR );
            for ( size_t iInnerIndex = 0; iInnerIndex < namedRefObjs.size(); iInnerIndex++ )
            {
                if ( ! GET_POM_object::isDescendant ( namedRefObjs[iInnerIndex]->getTag(), IMANFILE_CLASS ) )
                {
                    continue;
                }

                bIsFileFound = true;

                string sOriginalFileName = namedRefObjs[iInnerIndex]->getPropertyString ( ORIGINALFILENAME_ATTR );
                string sNewName = sOriginalFileName;
                string sExtension = "";
                size_t iPos = sNewName.find_last_of ( "." );
                if ( iPos != string::npos )
                {
                    sExtension = sNewName.substr( iPos + 1 );
                    sNewName.erase ( iPos );
                }
                GET_toUpper ( sNewName );

                // Validate if the File Name Attributes contain only lower case letters and
                if ( sNewName.compare ( docRevPtr->getId() ) != 0 || !GET_isLower ( sOriginalFileName ) )
                {
                    GET_ImanFileUnqPtr imfUnqPtr = GET_ImanFile::getInstance ( namedRefObjs[iInnerIndex]->getTag() );
                    sNewName = docRevPtr->getId() + "." + sExtension;
                    GET_toLower ( sNewName );
                    imfUnqPtr->setProp ( ORIGINALFILENAME_ATTR, sNewName );
                }
            }

            if ( ! bIsFileFound )
            {
                vErrorMessages.push_back ( relatedWsObjects[iLoopIndex]->getName() );
                continue;
            }

            //To Change Datasets Name to Item ID
            string sDatasetName = relatedWsObjects[iLoopIndex]->getPropertyString ( OBJECT_NAME_ATTR );
            string sDocItemRevId = docRevPtr->getId() + "/" + docRevPtr->getRevId();

            if ( sDatasetName.compare ( sDocItemRevId ) != 0 )
            {
                GET_toUpper ( sDocItemRevId );
                GET_DatasetUnqPtr datasetUnqPtr = GET_Dataset::getInstance ( relatedWsObjects[iLoopIndex]->getTag() ); 
                datasetUnqPtr->setProp ( OBJECT_NAME_ATTR, sDocItemRevId );
            }
        }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "\nThe following Datasets do not have named reference/file attached\n";
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

    LOG_TRACE ( logger, "END : GET6_validateDocumentsRH_impl" );
}

/*===========================================================================
//   Function:   GET6_validateParticipantsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateParticipants handler
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
//      Who                        Date                 Description
//  TCS Development Team          11 Feb, 2016         Initial creation
//  TCS Development Team          14 Jul, 2016         Modified the code for changes in attribute types from string to boolean
//  TechM Development Team        03 Oct, 2016         Modified the code for changes as per new ORG
//  Capgemini Development Team    16 Feb, 2017         Modified the GET6_validateParticipantsRH_impl method to check Explosive Atmosphere Compliance participant
//  TechM Development Team        26 Apr, 2017         Removed Program Manager, Product Manager participants, and added CCB Coordinator participant validation for ECR
//  TCS Development Team          06 Jul, 2017         Corrected the code to fix spacing errors
//  TechM Development Team        30-Aug-2017          Added MFG CutIn participant validation
//  Ganesh Ubale                  01-Nov-2017          Added Service Approval participant validation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_validateParticipantsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    GET_ItemRevisionUnqPtr ecRevisionPtr;

    // Map to store the Participants defined in the ECR Revision
    map<string, vector<GET_ParticipantShrPtr> > mParticipantsMap;

    string sOwningGroupName;
    string sTypeName;

    // Vector to store the Required Participant Names
    vector<string> vParticipantNames;
    // Vector to store all the errors
    vector<string> vErrorMessages;
    
    LOG_TRACE ( logger, "START : GET6_validateParticipantsRH_impl" );

    vector <tag_t> vTargetAttachments = mAttachmentsMap[EPM_target_attachment];

    for ( size_t iTargetAttachemtIndex = 0; iTargetAttachemtIndex < vTargetAttachments.size(); ++iTargetAttachemtIndex )
    {
        if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iTargetAttachemtIndex], CHANGEREVISION_CLASS ) )
        {
            continue;
        }
        ecRevisionPtr = GET_ItemRevision::getInstance ( vTargetAttachments[iTargetAttachemtIndex] );
        break;
    }
    if ( ! ecRevisionPtr || ecRevisionPtr.get() == NULL )
    {
        LOG_DEBUG ( logger, "Either a ECR or ECN should be present in Target List" );
        THROW ( "Change Item Revision not found in Target List" );
    }

    // Get the Object Type
    sTypeName = ecRevisionPtr->getType();

    // Get the Assigned Participants for this ECR Revision
    mParticipantsMap = ecRevisionPtr->getAllParticipants();

    // Get the Owning Group Name
    sOwningGroupName = ecRevisionPtr->getOwningGroup()->getGroupFullName();

    // Depending on the attribute values, check if all the required participants are assigned
    if ( sTypeName.compare ( ECRREVISION_TYPE ) == 0 )
    {
        // Variable for Participants
        vector<GET_ParticipantShrPtr> vComplianceParticipants;
        vector<GET_ParticipantShrPtr> vPrincipalEngrParticipants;
        vector<GET_ParticipantShrPtr> vSubGrpMgrParticipants;
        vector<GET_ParticipantShrPtr> vWorkAssignCoParticipants;
        vector<GET_ParticipantShrPtr> vCCBCoParticipants;

        // Get the Individual Participants List
        if ( sTypeName.compare ( ECRREVISION_TYPE ) == 0 && mParticipantsMap.find ( GET6COMPLIANCE_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vComplianceParticipants = mParticipantsMap[GET6COMPLIANCE_PARTICIPANT];
        }
        if ( sTypeName.compare ( ECRREVISION_TYPE ) == 0 && mParticipantsMap.find ( GET6PRINCIPALENGR_PARTICIPANT ) != mParticipantsMap.end() )
        {
               vPrincipalEngrParticipants = mParticipantsMap[GET6PRINCIPALENGR_PARTICIPANT];
        }
        if ( ecRevisionPtr->getPropLogical ( CCC_ATTR ) )
        {
            // Get the CCC_ATTR Display Name
            string sCCCAttrDisplayName = ecRevisionPtr->getPropDisplayName ( CCC_ATTR );

            if ( ! GET6_isParticipantFound ( vPrincipalEngrParticipants, sOwningGroupName, PRINCIPALENGINEER_ROLE, false ) &&
                ! GET6_isParticipantFound ( vPrincipalEngrParticipants, PRINCIPALENGINEERING_GROUP_FULL_NAME, ENGINEERINGMANAGER_ROLE, false ) )
            {
                string sErrorMessage = "\"" + sCCCAttrDisplayName + "\" is set to \"TRUE\". But a valid \""
                                    + string ( PRINCIPALENGINEER_ROLE ) + "\" Participant is not added for review";
                vErrorMessages.push_back ( sErrorMessage );
            }
            if ( ! GET6_isParticipantFound ( vComplianceParticipants, COMPLIANCE_GROUP_FULL_NAME, SAFETYCOMPLIANCE_ROLE, false ) )
            {
                string sErrorMessage = "\"" + sCCCAttrDisplayName + "\" is set to \"TRUE\". But a valid \""
                                    + string ( SAFETYCOMPLIANCE_ROLE ) + "\" Participant is not added for review";
                vErrorMessages.push_back ( sErrorMessage );
            }
        }
        if ( ecRevisionPtr->getPropString ( EXP_CONTROL_ATTR ).compare ( ECCN_LR ) == 0 ||
             ecRevisionPtr->getPropString ( ECCN_SOURCE_ATTR ).compare ( ECCNSRC_ECTAGGER ) == 0 )
        {
            // Get the EXP_CONTROL_ATTR, ECCN_SOURCE_ATTR Display Name
            string sExpCtrlAttrDisplayName = ecRevisionPtr->getPropDisplayName ( EXP_CONTROL_ATTR );
            string sECCNSrcAttrDisplayName = ecRevisionPtr->getPropDisplayName ( ECCN_SOURCE_ATTR );

            if ( ! GET6_isParticipantFound ( vComplianceParticipants, COMPLIANCE_GROUP_FULL_NAME, EXPORTCOMPLIANCE_ROLE, false ) )
            {
                string sErrorMessage = "\"" + sExpCtrlAttrDisplayName + "\"/\"" + sECCNSrcAttrDisplayName
                                     + "\" is set to \"" + string ( ECCN_LR ) + "\"/\"" + string ( ECCNSRC_ECTAGGER )
                                     + "\". But a valid \"" + string ( EXPORTCOMPLIANCE_ROLE ) + "\" Participant is not added for review";
                vErrorMessages.push_back ( sErrorMessage );
            }
        }
        if ( ecRevisionPtr->getPropLogical ( ECC_ATTR ) )
        {
            // Get the ECC_ATTR Display Name
            string sECCAttrDisplayName = ecRevisionPtr->getPropDisplayName ( ECC_ATTR );

            if ( ! GET6_isParticipantFound ( vComplianceParticipants, COMPLIANCE_GROUP_FULL_NAME, EMISSIONSCONTROLCOMPLIANCE_ROLE, false ) )
            {
                string sErrorMessage = "\"" + sECCAttrDisplayName + "\" is set to \"TRUE\". But a valid \""
                                     + string ( EMISSIONSCONTROLCOMPLIANCE_ROLE ) + "\" Participant is not added for review";
                vErrorMessages.push_back ( sErrorMessage );
            }
        }
        if ( ecRevisionPtr->getPropLogical ( HOMOLOGATION_ATTR ) )
        {
            // Get the HOMOLOGATION_ATTR Display Name
            string sHomologationAttrDisplayName = ecRevisionPtr->getPropDisplayName ( HOMOLOGATION_ATTR );

            if ( ! GET6_isParticipantFound ( vComplianceParticipants, COMPLIANCE_GROUP_FULL_NAME, HOMOLOGATION_ROLE, false ) )
            {
                string sErrorMessage = "\"" + sHomologationAttrDisplayName + "\" is set to \"TRUE\". But a valid \""
                                     + string ( HOMOLOGATION_ROLE ) + "\" Participant is not added for review";
                vErrorMessages.push_back ( sErrorMessage );
            }
        }
        if ( ecRevisionPtr->getPropLogical ( CRITICAL_PART_ATTR ) )
        {
            // Get the CRITICAL_PART_ATTR Display Name
            string sCriticalPartAttrDisplayName = ecRevisionPtr->getPropDisplayName ( CRITICAL_PART_ATTR );

            if ( ! GET6_isParticipantFound ( vComplianceParticipants, COMPLIANCE_GROUP_FULL_NAME, CRITICALPART_ROLE, false ) )
            {
                string sErrorMessage = "\"" + sCriticalPartAttrDisplayName + "\" is set to \"TRUE\". But a valid \""
                                     + string ( CRITICALPART_ROLE ) + "\" Participant is not added for review";
                vErrorMessages.push_back ( sErrorMessage );
            }
        }
        
        // Check if Explosive Atmosphere attribute is set to True
        if ( ecRevisionPtr->getPropLogical ( EXPLOSIVE_ATMOSPHERE_ATTR ) )
        {
            // Get the EXPLOSIVE_ATMOSPHERE_ATTR Display Name
            string sExplosiveAtmAttrDisplayName = ecRevisionPtr->getPropDisplayName ( EXPLOSIVE_ATMOSPHERE_ATTR );
            
            if ( ! GET6_isParticipantFound ( vComplianceParticipants, COMPLIANCE_GROUP_FULL_NAME, EXPLOSIVEATMOSPHERE_ROLE, false ) )
            {
                string sErrorMessage = "\"" + sExplosiveAtmAttrDisplayName + "\" is set to \"TRUE\". But a valid \""
                                 + string ( EXPLOSIVEATMOSPHERE_ROLE ) + "\" Participant is not added for review";
                vErrorMessages.push_back ( sErrorMessage );
            }
        }

        // Check if a valid Work Assignment Coordinator is added as a Participant
        if ( mParticipantsMap.find ( GET6WORKASSIGNCO_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vWorkAssignCoParticipants = mParticipantsMap[GET6WORKASSIGNCO_PARTICIPANT];
        }
        if ( ! GET6_isParticipantFound ( vWorkAssignCoParticipants, sOwningGroupName, DESIGNCOORDINATOR_ROLE, false ) )
        {
            string sErrorMessage = string ( "A valid \"" ) + string ( DESIGNCOORDINATOR_ROLE ) + "\" Participant is not added for review";
            vErrorMessages.push_back ( sErrorMessage );
        }
        // Check if a valid CCB Coordinator is added as a Participant
        if ( mParticipantsMap.find ( GET6CCBCO_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vCCBCoParticipants = mParticipantsMap[GET6CCBCO_PARTICIPANT];
        }
        if ( vCCBCoParticipants.size() == 0 )
        {
            string sErrorMessage = string ( "A valid CCB Coordinator is not added for review" );
            vErrorMessages.push_back ( sErrorMessage );
        }
        // Engineering Sub Group Manager's approval is required only if the ECN is created by an Engineer. For ECR its mandatory
        if ( mParticipantsMap.find ( GET6SUBGROUPMGR_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vSubGrpMgrParticipants = mParticipantsMap[GET6SUBGROUPMGR_PARTICIPANT];
        }
        // Check if a valid Engineering Sub Group Manager is added as a Participant
        if ( ! GET6_isParticipantFound ( vSubGrpMgrParticipants, sOwningGroupName, ENGINEERINGMANAGER_ROLE, false ) )
        {
            string sErrorMessage = string ( "A valid \"" ) + string ( ENGINEERINGMANAGER_ROLE )
                                 + "\" Participant belonging to \"" + sOwningGroupName + "\" is not added for review";
            vErrorMessages.push_back ( sErrorMessage );
        }
        // if the number of Engineering Sub Group Reviewers are greater than 2, then any person belonging to Systems Integration Group must be added as a participant
        if ( sTypeName.compare ( ECRREVISION_TYPE ) == 0 && vSubGrpMgrParticipants.size() >= 2 )
        {
            vector<GET_ParticipantShrPtr> vSystemsEngrParticipants;
            if ( mParticipantsMap.find ( GET6SYSTEMSENGR_PARTICIPANT ) != mParticipantsMap.end() )
            {
                vSystemsEngrParticipants = mParticipantsMap[GET6SYSTEMSENGR_PARTICIPANT];
            }
            if ( ! GET6_isParticipantFound ( vSystemsEngrParticipants, TRANSPORTATIONSYSTEMS_GROUP_FULL_NAME, ENGINEERINGMANAGER_ROLE, false ) &&
                 ! GET6_isParticipantFound ( vSystemsEngrParticipants, TRANSPORTATIONSYSTEMS_GROUP_FULL_NAME, ENGINEER_ROLE, false ) )
            {
                string sErrorMessage = string ( "This ECR affects more than 2 sub systems. But a valid \"" ) + ENGINEERINGMANAGER_ROLE + string ( "\" or an \"" )
                                     + ENGINEER_ROLE + string ( "\" Participant belonging to \"" ) + TRANSPORTATIONSYSTEMS_GROUP_FULL_NAME
                                     + string ( "\" or its sub groups is not added for review" );
                vErrorMessages.push_back ( sErrorMessage );
            }
        }
        /**
         * Viswanathan - 14-JUL-2016 - This attribute has been removed from the data model.
         * Commenting the below checks
         */
        //if ( ecRevisionPtr->getPropString ( STDPROD_ATTR ).compare ( CM_LOV_YES_VALUE ) == 0 )
        //{
            // Add the code when the requirements are clear
        //}
    }

    // ECR/ECN Type Specific Checks
    if ( sTypeName.compare ( ECNREVISION_TYPE ) == 0 )
    {
        vector<GET_ParticipantShrPtr> vEngineerParticipants;
        vector<GET_ParticipantShrPtr> vGlobalPrdcibilityParticipants;
        vector<GET_ParticipantShrPtr> vMfgCutInParticipants;
		vector<GET_ParticipantShrPtr> vServiceParticipants;

        if ( mParticipantsMap.find ( GET6ENGRAPPROVAL_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vEngineerParticipants = mParticipantsMap[GET6ENGRAPPROVAL_PARTICIPANT];
        }
        // Check if a valid Global Producibility user is added as a Participant
        if ( mParticipantsMap.find ( GET6PRODUCIBILITY_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vGlobalPrdcibilityParticipants = mParticipantsMap[GET6PRODUCIBILITY_PARTICIPANT];
        }
        if ( ! GET6_isParticipantFound ( vGlobalPrdcibilityParticipants, GLOBALPRODUCIBILITY_GROUP_FULL_NAME, MFGENGINEER_ROLE, false ) )
        {
            string sErrorMessage = string ( "A valid \"" ) + string ( MFGENGINEER_ROLE )
                    + "\" Participant belonging to \"" + string ( GLOBALPRODUCIBILITY_GROUP_FULL_NAME ) + "\" is not added for review";
            vErrorMessages.push_back ( sErrorMessage );
        }
        if ( mParticipantsMap.find ( GET6MFGCUTIN_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vMfgCutInParticipants = mParticipantsMap[GET6MFGCUTIN_PARTICIPANT];
        }
        if ( ecRevisionPtr->getPropLogical ( MOD_DESIGN_CUTIN_ATTR ) )
        {
            // Get the MOD_DESIGN_CUTIN_ATTR Display Name
            string sModDesignCutInAttrDisplayName = ecRevisionPtr->getPropDisplayName ( MOD_DESIGN_CUTIN_ATTR );
            if ( ! GET6_isParticipantFound ( vMfgCutInParticipants, OPERATIONS_GROUP_FULL_NAME, MFG_CHANGE_CONTROL_ROLE, false ) )
            {
            string sErrorMessage = "\"" + sModDesignCutInAttrDisplayName + "\" is set to \"TRUE\". But a valid \"" + string ( MFG_CHANGE_CONTROL_ROLE )
                    + "\" Participant belonging to \"" + string ( OPERATIONS_GROUP_FULL_NAME ) + "\" is not added for review";
            vErrorMessages.push_back ( sErrorMessage );
            }
        }
		if ( mParticipantsMap.find ( GET6SERVICE_PARTICIPANT ) != mParticipantsMap.end() )
        {
            vServiceParticipants = mParticipantsMap[GET6SERVICE_PARTICIPANT];
        }
        if ( ecRevisionPtr->getPropLogical ( SERVICE_IMPACT_ATTR ) )
        {
            // Get the SERVICE_IMPACT_ATTR Display Name
            string sServiceImpactAttrDisplayName = ecRevisionPtr->getPropDisplayName ( SERVICE_IMPACT_ATTR );
            if ( ! GET6_isParticipantFound ( vServiceParticipants, SERVICE_GROUP_FULL_NAME, SERVICE_ROLE, false ) )
            {
            string sErrorMessage = "\"" + sServiceImpactAttrDisplayName + "\" is set to \"TRUE\". But a valid \"" + string ( SERVICE_ROLE )
                    + "\" Participant belonging to \"" + string ( SERVICE_GROUP_FULL_NAME ) + "\" is not added for review";
            vErrorMessages.push_back ( sErrorMessage );
            }
        }
        // Get the Requestor User Name
        vector<GET_ParticipantShrPtr> vRequestorParticipants = mParticipantsMap[REQUESTOR_PARTICIPANT];
        string sEngineeringUserName = vRequestorParticipants[0]->getParticipantGroupMember()->getUser()->getName();
        // Check if a valid Engineer is added as a Participant
        if ( ! GET6_isParticipantFound ( vEngineerParticipants, sOwningGroupName, ENGINEER_ROLE, false ) )
        {
            string sErrorMessage = string ( "A valid \"" ) + string ( ENGINEER_ROLE )
                                 + "\" Participant belonging to \"" + sOwningGroupName + "\" is not added for review";
            vErrorMessages.push_back ( sErrorMessage );
        }
        // Check if the current user has added himself as an Engineer Participant
        for ( size_t iIndex = 0; iIndex < vEngineerParticipants.size(); iIndex++ )
        {
            if ( vEngineerParticipants[iIndex]->getParticipantGroupMember()->getUser()->getName().compare ( sEngineeringUserName ) == 0 )
            {
                string sErrorMessage = string ( "The Process Owner cannot add himself as an approver for the Participant \"" ) + GET6ENGRAPPROVAL_PARTICIPANT + "\"";
                vErrorMessages.push_back ( sErrorMessage );
                break;
            }
        }
    }

    //added code to verify read privilege on data for participants
    vector<GET_WorkspaceObjectShrPtr> vTargetShrPtr;
    for ( size_t index = 0; index < vTargetAttachments.size(); ++index )
    {
        vTargetShrPtr.push_back ( GET_WorkspaceObjectShrPtr ( move ( GET_WorkspaceObject::getInstance ( vTargetAttachments[index] ) ) ) );
    }
    for ( std::map<string, vector<GET_ParticipantShrPtr> >::iterator participantMapIterator = mParticipantsMap.begin();\
    participantMapIterator != mParticipantsMap.end(); ++participantMapIterator )
    {
        vector<GET_ParticipantShrPtr> vParticipants = participantMapIterator->second;
        for ( size_t vectorIndex = 0; vectorIndex < vParticipants.size(); ++vectorIndex )
        {
            GET_POM_objectUnqPtr assigneeUnqPtr = vParticipants[vectorIndex]->getPropertyTag ( PARTICIPANT_ASSIGNEE_ATTR );
            GET_GroupMemberUnqPtr groupMemberUnqPtr = GET_GroupMember::getInstance ( assigneeUnqPtr->getTag() );
            GET_POM_userShrPtr participantUserShrPtr = groupMemberUnqPtr->getUser();

            for ( size_t index = 0; index < vTargetShrPtr.size(); index++ )
            {
                if ( !vTargetShrPtr[index]->checkUserPrivilege ( participantUserShrPtr, AM_PRIV_READ ) )
                {
                     string sErrorMessage = string ( "The participant " ) + string ( participantMapIterator->first )
                                          + string ( " does not have read access to the object " )
                                          + string ( vTargetShrPtr[index]->getPropString ( OBJECT_STRING_ATTR ) );
                     vErrorMessages.push_back ( sErrorMessage );
                }
            }
        }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "\n";

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

    LOG_TRACE ( logger, "END : GET6_validateParticipantsRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateMaterialsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateMaterials handler
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
//  TCS Development Team     27 Oct, 2016         Initial Creation
//  TechM Development Team   15 Dec, 2017         Updated GET6_validateMaterialsRH_impl with Made from Part validation
//  TechM Development Team   02 Mar, 2018         Updated Error Message text and removed the check if the revision of Made from Part is released
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateMaterialsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    vector<string> vErrorMessages;
    vector<tag_t> vTargetObjects;
    vector <string> vIncludeType;

    LOG_TRACE ( logger, "START : GET6_validateMaterialsRH_impl" );

    // Get the Target Objects from the Workflow Target Attachments
    vTargetObjects = mAttachmentsMap[EPM_target_attachment];

    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );
    }

    for ( size_t iIndex = 0; iIndex < vTargetObjects.size(); iIndex++ )
    {
        // Variable declaration
        bool bIsReleased = false;
        string sTypeName = "";

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

        // Check if the given Part is a leaf part or not
        vector<GET_POM_objectUnqPtr> vChildren = itemRevUnqPtr->getPropTags ( PSCHILDREN_ATTR );
        if ( vChildren.size() > 0 )
        {
            continue;
        }

        // Check if the Make/Buy value is Make
        if ( itemRevUnqPtr->getPropString ( ENG_MAKEBUY ).compare ( ENG_MAKEBUY_MAKE_VALUE ) != 0 )
        {
            continue;
        }

        // Get the Item from the Revision
        GET_ItemUnqPtr itemUnqPtr = itemRevUnqPtr->getItem();
        GET_ItemShrPtr itemPtr ( move ( itemUnqPtr ) );

        // Get the list of Materials Attached under the given relation
        vector<GET_WorkspaceObjectUnqPtr> relatedWsObjects = GET_ImanRelation::listRelatedWsObjects ( itemPtr, MADEFROMMATL );

        // Get the list of Parts Attached under the Made from part relation
        vector<GET_WorkspaceObjectUnqPtr> relatedParts = GET_ImanRelation::listRelatedWsObjects ( itemPtr, MADEFROMPART );
        if ( relatedWsObjects.size() == 0 && relatedParts.size() == 0)
        {
            string sErrorMessage = string ( "A Make Part : ") + string ( itemPtr->getPropString ( OBJECT_STRING_ATTR ) ) + string ( ", is required to have an associated Made from Material or Made From Part with it" ) ;
            vErrorMessages.push_back ( sErrorMessage );
            continue;
        }

        // Invalid Data condition check
        if ( relatedWsObjects.size() != 0 && relatedParts.size() != 0)
        {
            string sErrorMessage = string ( "A Make Part : ") + string ( itemPtr->getPropString ( OBJECT_STRING_ATTR ) ) + string (", cannot be associated with both a Material and a Made From Part" );
            vErrorMessages.push_back ( sErrorMessage );
            continue;
        }
        //Check if the attached material's latest revision is released
        if ( relatedWsObjects.size() != 0 )
        {
            GET_ItemUnqPtr mtrlUnqPtr = GET_Item::getInstance ( relatedWsObjects[0]->getTag() );
            GET_ItemRevisionUnqPtr mtrlRevision = mtrlUnqPtr->getLatestRevision();

            bIsReleased = mtrlRevision->hasReleaseStatus ( APPROVED );
            if ( !bIsReleased )
            {
                string sErrorMessage = string ( "The latest revision of the Material associated to the item : " ) + string ( itemPtr->getPropString ( OBJECT_STRING_ATTR ) )
                                              + string ( ", does not have a valid release status" );
                vErrorMessages.push_back ( sErrorMessage );
                continue;
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

    LOG_TRACE ( logger, "END : GET6_validateMaterialsRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkGroupObjectPropertyRH()
//
//    Purpose:   Rule Handler to validate the Group and Properties to the ECR object during the review process.
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                           Date                 Description
//  Capgemini Development Team     07 Feb, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_checkGroupObjectPropertyRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_checkGroupObjectPropertyRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_checkGroupObjectPropertyRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_checkGroupObjectPropertyRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_checkGroupObjectPropertyRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkGroupObjectPropertyRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_checkGroupObjectPropertyRH handler
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
//  Capgemini Development Team     07 Feb, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_checkGroupObjectPropertyRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    vector<string> vErrorMessages;
    vector<tag_t> vTargetObjects;
    vector <string> vIncludeType;
    vector <string> vIncludeGroups;
    vector <string> vExcludeGroups;
    vector <string> vIncludeProps;

    LOG_TRACE ( logger, "START : GET6_checkGroupObjectPropertyRH_impl" );

    // Get the Target Objects from the Workflow Target Attachments
    vTargetObjects = mAttachmentsMap[EPM_target_attachment];
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );
    }

    if ( mArgumentsMap.find ( PROPERTY_ARG ) == mArgumentsMap.end() || mArgumentsMap[PROPERTY_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( PROPERTY_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    GET_splitString ( mArgumentsMap[GROUP_ARG], COMMA_CHARACTER, vIncludeGroups );
    GET_splitString ( mArgumentsMap[EXCLUDE_GROUP_ARG], COMMA_CHARACTER, vExcludeGroups );
    GET_splitString ( mArgumentsMap[PROPERTY_ARG], COMMA_CHARACTER, vIncludeProps );
    
    for ( size_t iIndex = 0; iIndex < vTargetObjects.size(); iIndex++ )
    {
        // Variable to store the Type Name
        string sTypeName = "";
        // Variable to store the Group Name
        string sGroupName = "";
         
        // Check if the target is an ItemRevision or not
        if ( ! GET_POM_object::isDescendant ( vTargetObjects[iIndex], WORKSPACEOBJECT_CLASS ) )
        {
            continue;
        }
        
        GET_WorkspaceObjectUnqPtr wsoUnqPtr = GET_WorkspaceObject::getInstance ( vTargetObjects[iIndex] );
        
        // Get the Object Type
        sTypeName = wsoUnqPtr->getType();

        // Check if the Target is provided in the To Be Checked List
        if ( ! vIncludeType.empty() && ! GET_isInVector ( vIncludeType, sTypeName ) )
        {
            continue;
        }   

        // Get the Group Name
        sGroupName = wsoUnqPtr->getOwningGroup()->getGroupFullName();

        // Check if the Target is provided in the To Be Checked List
        if ( ( ! vIncludeGroups.empty() && ! GET_isInVector ( vIncludeGroups, sGroupName ) ) || ( ! vExcludeGroups.empty() && GET_isInVector ( vExcludeGroups, sGroupName ) ) )
        {
            continue;
        }

        for ( size_t iIndx = 0; iIndx < vIncludeProps.size(); ++iIndx )
        {
            if ( ( wsoUnqPtr->getPropValueAsString ( vIncludeProps [iIndx] ) ).empty() )
            {
                string sPropDisplayname = wsoUnqPtr->getPropDisplayName ( vIncludeProps [iIndx] );
                string sErrorMessage = string ("The task attachment object ") + string (wsoUnqPtr->getPropString ( OBJECT_STRING_ATTR ) ) + string (" contains empty value for the property: " ) + sPropDisplayname;
                vErrorMessages.push_back ( sErrorMessage );
                continue;
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

    LOG_TRACE ( logger, "END : GET6_checkGroupObjectPropertyRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateCheckmateResultsRH()
//
//    Purpose:   Rule Handler to validate NX Checkmate result for a Part
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                           Date                 Description
//  TCS Development Team           15 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateCheckmateResultsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateCheckmateResultsRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateCheckmateResultsRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateCheckmateResultsRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateCheckmateResultsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateCheckmateResultsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateCheckmateResultsRH handler
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
//  TCS Development Team           15 May, 2017         Initial Creation
//  TCS Development Team           09 Aug, 2017         Fix the defect in this method method to make sure all dataset types are validated
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateCheckmateResultsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    GET_ItemRevisionUnqPtr ecnRevisionPtr;

    vector<string> vErrorMessages;
    vector<tag_t> vTargetObjects;
    vector <string> vIncludeTypes;
    vector <string> vDatasetTypes;

    LOG_TRACE ( logger, "START : GET6_validateCheckmateResultsRH_impl" );

    // Get the Target Objects from the Workflow Target Attachments
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( DATASET_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[DATASET_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( DATASET_TYPE_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeTypes );
    GET_splitString ( mArgumentsMap[DATASET_TYPE_ARG], COMMA_CHARACTER, vDatasetTypes );

    // Process the target objects list and get the required Engineering Change Notice Object
    vTargetObjects = mAttachmentsMap[EPM_target_attachment];
    for ( size_t iIndex = 0; iIndex < vTargetObjects.size(); iIndex++ )
    {
        GET_POM_objectUnqPtr pomObjectPtr;

        // Variable to store the Type Name
        string sTypeName = "";

        // Check if the target is one of the required types
        pomObjectPtr = GET_POM_object::getInstance ( vTargetObjects[iIndex] );
        sTypeName = pomObjectPtr->askTypeName();
        if ( sTypeName.compare ( ECNREVISION_TYPE ) != 0 )
        {
            continue;
        }
        ecnRevisionPtr = GET_ItemRevision::getInstance ( vTargetObjects[iIndex] );
        break;
    }
    if ( ! ecnRevisionPtr || ecnRevisionPtr.get() == NULL )
    {
        THROW ( "Engineering Change Notice Revision not found in Target List" );
    }
    // If Checkmate bypass is enabled, then a valid reason shall be mentioned
    if ( ecnRevisionPtr->getPropLogical ( BYPASS_CHECKMATE ) )
    {
        string sBypassCommentsAttrValue = ecnRevisionPtr->getPropString ( BYPASS_COMMENTS );
        string sBypassReasonAttrValue = ecnRevisionPtr->getPropString ( BYPASS_REASON );
        GET_strtrim ( sBypassCommentsAttrValue );
        GET_strtrim ( sBypassReasonAttrValue );
        if ( sBypassCommentsAttrValue.empty() || sBypassReasonAttrValue.empty() )
        {
            string sBypassCommentsAttrName = ecnRevisionPtr->getPropDisplayName ( BYPASS_COMMENTS );
            string sBypassReasonAttrName = ecnRevisionPtr->getPropDisplayName ( BYPASS_REASON );
            THROW ( "NX Checkmate check is bypassed. Hence attributes \"" + sBypassCommentsAttrName + "\" and \"" +
                    sBypassReasonAttrName + "\" cannot have empty values" );
        }
    }
    else
    {
        // Get the Solution Item Revisions and check if they have passed checkmate or not
        vector<GET_POM_objectUnqPtr> vSolutionItems = ecnRevisionPtr->getPropTags ( CM_HAS_SOLUTION_ITEMS_PROP );
        for ( size_t iIndex = 0; iIndex < vSolutionItems.size(); iIndex++ )
        {
            bool bIsCheckmatePassed = false;

            vector<GET_WorkspaceObjectUnqPtr> vWSObjects;

            // Check if the Solution Item belong to the required type
            if ( ! GET_isInVector ( vIncludeTypes, vSolutionItems[iIndex]->askTypeName() ) )
            {
                continue;
            }

            // Get the Specification datasets and validate the NX Checkmate conditions
            GET_ItemRevisionShrPtr itemRevPtr ( move ( GET_ItemRevision::getInstance ( vSolutionItems[iIndex]->getTag() ) ) );
            vWSObjects = GET_ImanRelation::listRelatedWsObjects ( itemRevPtr, IMAN_SPECIFICATION );
            for ( size_t iIndex = 0; iIndex < vWSObjects.size(); iIndex++ )
            {
                if ( ! GET_isInVector ( vDatasetTypes, vWSObjects[iIndex]->getType() ) )
                {
                    continue;
                }

                // Initializing this value to false
                bIsCheckmatePassed = false;

                GET_DatasetUnqPtr datasetPtr = GET_Dataset::getInstance ( vWSObjects[iIndex]->getTag() );
                vector<GET_POM_objectUnqPtr> vNamedRefs = datasetPtr->getNamedRefs ( UGPART_ATTRIBUTES_REFNAME );
                if ( vNamedRefs.size() > 0 )
                {
                    vector<string> vTitles;
                    vector<string> vValues;

                    GET_FormUnqPtr formPtr = GET_Form::getInstance ( vNamedRefs[0]->getTag() );
                    vTitles = formPtr->getPropStrings ( TITLES_ATTR );
                    vValues = formPtr->getPropStrings ( VALUES_ATTR );
                    if ( vTitles.size() == vValues.size() )
                    {
                        for ( size_t iInx = 0; iInx < vTitles.size(); iInx++ )
                        {
                            if ( vTitles[iInx].compare ( GETR_CHECKMATE_STATUS ) != 0 )
                            {
                                continue;
                            }
                            if ( vValues[iInx].compare ( TRUE_VALUE ) == 0 )
                            {
                                bIsCheckmatePassed = true;
                            }
                        }
                    }
                }

                // If the Checkmate conditions are not satisfied, break this loop
                if ( ! bIsCheckmatePassed )
                {
                    break;
                }
            }

            // Verify if checkmate flag is set
            if ( ! bIsCheckmatePassed )
            {
                vErrorMessages.push_back ( itemRevPtr->getPropString ( OBJECT_STRING_ATTR ) );
            }
        }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "The Following Solution Items have some datasets that has failed the NX Checkmate check\n";

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

    LOG_TRACE ( logger, "END : GET6_validateCheckmateResultsRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateWFRetrievalRH()
//
//    Purpose:   Rule Handler to validate Change workflow deletion and retrieval
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                           Date                 Description
//  TechM Development Team           20 May, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateWFRetrievalRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateWFRetrievalRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateWFRetrievalRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateWFRetrievalRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateWFRetrievalRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateWFRetrievalRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateWFRetrievalRH handler
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
//  TechM Development Team           20 May, 2017         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateWFRetrievalRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    GET_ItemRevisionUnqPtr ecRevisionPtr;

    vector<tag_t> vTargetAttachments = mAttachmentsMap[EPM_target_attachment];

    LOG_TRACE ( logger, "START : GET6_validateWFRetrievalRH_impl" );

    for ( size_t iTargetAttachemtIndex = 0; iTargetAttachemtIndex < vTargetAttachments.size(); ++iTargetAttachemtIndex )
    {
        if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iTargetAttachemtIndex], CHANGEREVISION_CLASS ) )
        {
            continue;
        }
        ecRevisionPtr = GET_ItemRevision::getInstance ( vTargetAttachments[iTargetAttachemtIndex] );
        break;
    }
    if ( ecRevisionPtr.get() == NULL )
    {
        LOG_DEBUG ( logger, "Either a ECR or ECN should be present in target items" );
        THROW ( "Change Item Revision not found in target items" );
    }

    //Get root task pointer
    GET_EPMTaskUnqPtr currentTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );

    //Get task owner
    GET_POM_userUnqPtr currentTaskOwnerPtr = currentTaskUnqPtr->getOwningUser();
    vector<GET_POM_objectUnqPtr> vAllWorflowsPtr = ecRevisionPtr->getPropTags ( All_WORKFLOWS );
     for ( size_t iIndx = 0; iIndx < vAllWorflowsPtr.size(); ++iIndx )
    {
        // Get workflow pointer
        GET_EPMTaskUnqPtr epmUnqPtr = GET_EPMTask::getInstance ( vAllWorflowsPtr[iIndx]->getTag() );
        if ( ( currentTaskUnqPtr->getUID().compare( epmUnqPtr->getUID() ) != 0 ) && ( epmUnqPtr->getPropValueAsString ( REAL_STATE ).compare ( REAL_STATE_STARTED ) == 0 ) )
        {
            if ( epmUnqPtr->getOwningUser()->getID().compare ( currentTaskOwnerPtr->getID() ) == 0 )
            {
                GET_EPMJobUnqPtr epmJobUnqPtr = epmUnqPtr->askEPMJob();
                epmJobUnqPtr->deleteObject();
            }
            else
            {
                LOG_DEBUG ( logger, "Only the Workflow initiator can delete the job and retrieve the Change" );
                THROW ( "Only the Workflow initiator can delete the job and retrieve the Change" );
            }
        }
    }

    LOG_TRACE ( logger, "END : GET6_validateWFRetrievalRH_impl" );
}
