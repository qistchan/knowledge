
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_COMMON_RuleHandlers.cxx
//
//    Purpose:   Source File defining the Common Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     25 Aug, 2016         Initial creation
//  TCS Development Team     11 Apr, 2017         Removed Handler GET6_validateNamedRefRH and consolidated the same with GET6_validateDocumentsRH
//  TCS Development Team     26 May, 2017         Modified GET6_checkRelatedObjectsRH_impl handler
//  TCS Development Team     29 May, 2017         Added Handler implementation for validating related objects status (GET6_checkItemStatusRH, GET6_checkItemStatusRH_impl)
//  TCS Development Team     29 Jun, 2017         Added Handler implementation for BOM Child line validation (GET6_validateBOMChildTypesRH, GET6_validateBOMChildTypesRH_impl)
//  TechM Development Team   02 Aug, 2017         Modified error messages across this file
//  TCS Development Team     28 May, 2018         Added Handler Registration for Traversing and validating EBOM (GET6_traverseBOMRH_impl)
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_BOMWindow.hxx>
#include <GET_COMMON_RuleHandlers.hxx>
#include <GET_Constants.hxx>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_POM_user.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_GroupMember.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_POM_object.hxx>
#include <GET_POM_group.hxx>
#include <GET_Role.hxx>
#include <GET_Utils.hxx>
#include <GET_EPMTask.hxx>
#include <GET_POM_application_object.hxx>
#include <GET_WorkspaceObject.hxx>
// Teamcenter Includes
#include <tc/emh.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// CPP Includes
#include <map>

using namespace get;

// Private Function Prototypes
void GET6_validateInitiatorRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>&  );
void GET6_validateRelatedObjectsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>&  );
void GET6_checkRelatedObjectsRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_checkItemStatusRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_validateBOMChildTypesRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_traverseBOMRH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
void recurseBOM ( GET_BOMLineShrPtr, vector<GET_ItemRevisionShrPtr>, vector<string>, vector<GET_ItemRevisionShrPtr>&, vector<string>& );
bool GET_ExistsInVector( vector<GET_ItemRevisionShrPtr>, GET_ItemRevisionShrPtr );
void addObjectsToRefFolder ( vector<GET_ItemRevisionShrPtr>, string, string, string, vector<GET_POM_objectShrPtr>& );

const string logger = "get.handler.GET_COMMON_RuleHandler";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateInitiatorRH()
//
//    Purpose:   Rule Handler to validate the initiator of the workflow
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     25 Aug, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateInitiatorRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateInitiatorRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateInitiatorRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateInitiatorRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateInitiatorRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateInitiatorRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateInitiatorRH_impl handler
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
//  TCS Development Team     25 Aug, 2016         Initial Creation
//  TechM Development Team   27 Oct, 2016         Enhanced the functionality to pass Any User, Any Group or Any Role arguments
//  TCS Development Team     01 Nov, 2016         Re-factored the code to comply with standards
===========================================================================
//ENDFUNCDOC   ***/
void GET6_validateInitiatorRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    vector < string > vUser;
    vector < string > vGroup;
    vector < string > vRole;
    vector < string > vIncludeType;
    vector < string > vErrorMessages;

    LOG_TRACE( logger, "START : GET6_validateInitiatorRH_impl" );

    //Message for invalid arguments
    if ( mArgumentsMap.empty() )
    {
        string sErrorMessage = string ( "At least one of the \"" ) + USER_ARG + "\" or \"" + GROUP_ARG + "\" or \"" + ROLE_ARG + "\" argument has to be specified";
        THROW ( sErrorMessage );
    }

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( USER_ARG ) != mArgumentsMap.end() )
    {
       GET_splitString ( mArgumentsMap[USER_ARG], COMMA_CHARACTER, vUser );
    }
    if ( mArgumentsMap.find ( GROUP_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[GROUP_ARG], COMMA_CHARACTER, vGroup );
    }
    if ( mArgumentsMap.find ( ROLE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[ROLE_ARG], COMMA_CHARACTER, vRole );
    }
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );
    }

    //Process Target Attachments in loop
    vector < tag_t > vTargetAttachments = mAttachmentsMap[EPM_target_attachment];

    GET_POM_userUnqPtr loggedInUser = GET_POM_user::getCurrentLoggedInUser();
    GET_GroupMemberUnqPtr loggedInGrpMember = GET_GroupMember::getCurrentGroupMember();
    GET_RoleUnqPtr loggedInRole = GET_Role::getCurrentLoggedInUserRole();

    for ( size_t index = 0; index < vTargetAttachments.size (); ++index )
    {
        GET_WorkspaceObjectUnqPtr wsPtr = GET_WorkspaceObject::getInstance ( vTargetAttachments[index] );
        
        //Check include type argument
        if ( !vIncludeType.empty() && !GET_isInVector ( vIncludeType, wsPtr->getType() ) )
        {
            LOG_DEBUG ( logger, "Skipping object of type : " + wsPtr->getType() + ", as it is not in allowed type" );
            continue;
        }

        //Check User argument
        if ( !vUser.empty() && !( GET_isInVector ( vUser, loggedInUser->getID() ) ||
               ( GET_isInVector ( vUser, string ( OWNING_USER_ARG_VAL ) ) && loggedInUser->getID().compare ( wsPtr->getOwningUser()->getID() ) == 0 ) ) )
        {
            string sErrorMessage = "You are not authorized to initiate workflow on " + wsPtr->getPropString ( OBJECT_STRING_ATTR );
            vErrorMessages.push_back ( sErrorMessage );
            continue;
        }

        //Check Group argument
        if ( !vGroup.empty() && !( GET_isInVector ( vGroup, loggedInGrpMember->getGroup()->getGroupFullName() ) ||
               ( GET_isInVector ( vGroup, string ( OWNING_GROUP_ARG_VAL ) ) &&
               loggedInGrpMember->getGroup()->getGroupFullName().compare ( wsPtr->getOwningGroup()->getGroupFullName() ) == 0 ) ) )
        {
            string sErrorMessage = "You do not belong to authorized group to initiate workflow on " + wsPtr->getPropString ( OBJECT_STRING_ATTR );
            vErrorMessages.push_back ( sErrorMessage );
            continue;
        }

        //Check Role argument
        if ( !vRole.empty() && !GET_isInVector ( vRole, loggedInRole->getRoleName() ) )
        {
            string sErrorMessage = "You do not belong to authorized role to initiate workflow on " + wsPtr->getPropString ( OBJECT_STRING_ATTR );
            vErrorMessages.push_back ( sErrorMessage );
        }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "GET6-Validate-Initiator found the following discrepancies : \n";
        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size (); iIndex++ )
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

    LOG_TRACE( logger, "END : GET6_validateInitiatorRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateRelatedObjectsRH()
//
//    Purpose:   Rule Handler to validate that the object/related object has null value
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     03 Nov, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateRelatedObjectsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateRelatedObjectsRH" );
    try
    {
        GET_processHandler ( tMsg, GET6_validateRelatedObjectsRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET-Validate-Related-Objects" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateRelatedObjectsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateRelatedObjectsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateNullValueRH_impl handler
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
//  TCS Development Team     03 Nov, 2016         Initial Creation
===========================================================================
//ENDFUNCDOC   ***/
void GET6_validateRelatedObjectsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    vector<string> vErrorMessages;
    vector<string> vExcludeType;
    vector<string> vIncludeType;
    vector<string> vPropertyRelation;
    vector<string> vNumAllowedValues;
    vector<string> vErrMsgValues;

    LOG_TRACE( logger, "START : GET6_validateRelatedObjectsRH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( PROPERTY_ARG ) != mArgumentsMap.end() )
    {
       GET_splitString ( mArgumentsMap[PROPERTY_ARG], COMMA_CHARACTER, vPropertyRelation );
    }
    if ( mArgumentsMap.find ( RELATION_ARG ) != mArgumentsMap.end() )
    {
       if ( !vPropertyRelation.empty() )
       {
           string sErrorMessage = string ( PROPERTY_ARG ) + " and " + string ( RELATION_ARG ) + " are mutually exclusive!!!";
           THROW ( sErrorMessage );
       }
       GET_splitString ( mArgumentsMap[RELATION_ARG], COMMA_CHARACTER, vPropertyRelation );
    }
    if ( vPropertyRelation.empty() )
    {
        string sErrorMessage = string ( "One of the " ) + PROPERTY_ARG + " or " + RELATION_ARG + " argument has to be specified";
        THROW ( sErrorMessage );
    }
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );
    }
    if ( mArgumentsMap.find ( EXCLUDE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[EXCLUDE_TYPE_ARG], COMMA_CHARACTER, vExcludeType );
    }
    if ( !vIncludeType.empty() && !vExcludeType.empty() )
    {
        string sMsg = string ( INCLUDE_TYPE_ARG ) + " and " + string ( EXCLUDE_TYPE_ARG ) + " are mutually exclusive!!!";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( NUM_ALLOWED_VAL_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[NUM_ALLOWED_VAL_ARG], COMMA_CHARACTER, vNumAllowedValues );
    }
    if ( mArgumentsMap.find ( ERROR_MSG_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[ERROR_MSG_ARG], COMMA_CHARACTER, vErrMsgValues );
    }

    //Process Target Attachments in loop
    vector < tag_t > vTargetAttachments = mAttachmentsMap[EPM_target_attachment];

    for ( size_t index = 0; index < vTargetAttachments.size (); ++index )
    {
        GET_WorkspaceObjectUnqPtr wsPtr = GET_WorkspaceObject::getInstance ( vTargetAttachments[index] );

        //Check include type argument
        if ( !vIncludeType.empty() && !GET_isInVector ( vIncludeType, wsPtr->getType() ) )
        {
            LOG_DEBUG ( logger, "Skipping object of type : " + wsPtr->getType() + ", as it is not in allowed type" );
            continue;
        }
        if ( !vExcludeType.empty() && GET_isInVector ( vExcludeType, wsPtr->getType() ) )
        {
            LOG_DEBUG ( logger, "Skipping object of type : " + wsPtr->getType() + ", as it is not in allowed type" );
            continue;
        }

        for ( size_t iPropIndex = 0; iPropIndex < vPropertyRelation.size(); ++iPropIndex )
        {
            int iNumAllowedValue = 0;
            string sErrorMessage = "";

            if ( vNumAllowedValues.size() > iPropIndex )
            {
                iNumAllowedValue = stoi ( vNumAllowedValues[iPropIndex] );
            }
            if ( vErrMsgValues.size() > iPropIndex )
            {
                sErrorMessage = vErrMsgValues[iPropIndex];
            }

            if ( mArgumentsMap.find ( PROPERTY_ARG ) != mArgumentsMap.end() )
            {
                int iNumValue = wsPtr->numElements ( vPropertyRelation[iPropIndex] );
                if ( iNumValue > iNumAllowedValue )
                {
                    if ( sErrorMessage.empty() || sErrorMessage.compare("") == 0 )
                    {
                        sErrorMessage = "The property " + vPropertyRelation[iPropIndex] + " of " + wsPtr->getPropString ( OBJECT_STRING_ATTR )
                                    + " has number of values > " + GET_intToString ( iNumAllowedValue );
                    }
                    vErrorMessages.push_back ( sErrorMessage );
                    continue;
                }
            }
            else
            {
                GET_WorkspaceObjectShrPtr wsShrPtr ( move ( wsPtr ) );
                vector<GET_WorkspaceObjectUnqPtr> relatedWsObjects = GET_ImanRelation::listRelatedWsObjects ( wsShrPtr,
                        vPropertyRelation[iPropIndex], "", mArgumentsMap.find ( PRIMARY_ARG ) != mArgumentsMap.end() );
                if ( relatedWsObjects.size() >  iNumAllowedValue )
                {
                    if ( sErrorMessage.empty() || sErrorMessage.compare("") == 0 )
                    {
                        sErrorMessage = wsShrPtr->getPropString ( OBJECT_STRING_ATTR ) + " has more than " + GET_intToString ( iNumAllowedValue ) +
                                " objects associated with the relation " + vPropertyRelation[iPropIndex];
                    }
                    vErrorMessages.push_back ( sErrorMessage );
                    continue;
                }
            }
        }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "GET6_validateRelatedObjectsRH_impl found the following discrepancies : \n";
        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size (); iIndex++ )
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

    LOG_TRACE( logger, "END : GET6_validateRelatedObjectsRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkRelatedObjectsRH()
//
//    Purpose:   Rule handler to check allowed object types in solution item folder
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      02 Mar, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_checkRelatedObjectsRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_checkRelatedObjectsRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_checkRelatedObjectsRH_impl );
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
        string sMessage = "GET6_checkRelatedObjectsRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_checkRelatedObjectsRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkRelatedObjectsRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_checkRelatedObjectsRH handler
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
//  TCS Development Team      02 Mar, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_checkRelatedObjectsRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &p_vAttachments, map<string, string> &mArgumentsMap )
{
    bool bDisallowedObjFound = false;

    string sConsolidatedErrorMessage = "";

    vector<string> vAllowedType;
    vector<string> vDisallowedType;

    LOG_TRACE ( logger, "START : GET6_checkRelatedObjectsRH_impl" );

    // Clear the existing error stack
    EMH_clear_errors();

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[RELATION_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    if ( mArgumentsMap.find ( ALLOWED_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[ALLOWED_TYPE_ARG], COMMA_CHARACTER, vAllowedType );
    }
    if ( mArgumentsMap.find ( DISALLOWED_TYPE_ARG ) != mArgumentsMap.end() )
    {
        GET_splitString ( mArgumentsMap[DISALLOWED_TYPE_ARG], COMMA_CHARACTER, vDisallowedType );
    }
    if ( !vAllowedType.empty() && !vDisallowedType.empty() )
    {
        string sMsg = string ( ALLOWED_TYPE_ARG ) + " and " + string ( DISALLOWED_TYPE_ARG ) + " are mutually exclusive!!!";
        THROW ( sMsg );
    }
    if ( vAllowedType.empty() && vDisallowedType.empty() )
    {
        string sMsg = string ( "One of the " ) + ALLOWED_TYPE_ARG + " or " + DISALLOWED_TYPE_ARG + " arguments has to be specified";
        THROW ( sMsg );
    }

    // Loop through each target objects
    for ( int iTargetIndex = 0; iTargetIndex < p_vAttachments[EPM_target_attachment].size(); iTargetIndex++ )
    {
        string sERRTypes = "";

        GET_WorkspaceObjectUnqPtr getTargetUnqPtr = GET_WorkspaceObject::getInstance ( p_vAttachments[EPM_target_attachment][iTargetIndex] );
        GET_WorkspaceObjectShrPtr getTargetShrPtr ( move ( getTargetUnqPtr ) );
        LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getTargetShrPtr->getType() );

        if ( ( mArgumentsMap[INCLUDE_TYPE_ARG] ).compare ( getTargetShrPtr->getType() ) != 0 )
        {
            continue;
        }

        // Get the Secondary objects for given primary type object
        vector<GET_POM_objectUnqPtr> vSecondaryObjects = GET_ImanRelation::listRelatedObjects ( getTargetShrPtr, mArgumentsMap[RELATION_TYPE_ARG], false );
        LOG_TRACE ( logger, "Size of Secondary Object is ..." + vSecondaryObjects.size() );

        // Loop through each objects in Solution Item folder
        for ( size_t iRelObjIndex = 0; iRelObjIndex < vSecondaryObjects.size(); iRelObjIndex++ )
        {
            string sSecondaryObjectType = vSecondaryObjects[iRelObjIndex]->askTypeName();

            if ( vAllowedType.empty() )
            {
                // Check if the Related object folder contains any disallowed type object
                if ( GET_isInVector ( vDisallowedType, sSecondaryObjectType ) )
                {
                    // If any disallowed object type found, break the loop
                    sERRTypes.append ( sSecondaryObjectType );
                    sERRTypes.append ( ", " );
                }
            }
            else
            {
                // Check if the Related object folder contains any disallowed type object
                if ( ! GET_isInVector ( vAllowedType, sSecondaryObjectType ) )
                {
                    // If any disallowed object type found, break the loop
                    sERRTypes.append ( sSecondaryObjectType );
                    sERRTypes.append ( ", " );
                }
            }
        }
        if ( !sERRTypes.empty() )
        {
            sConsolidatedErrorMessage.append ( "Target Object (" + getTargetShrPtr->getPropString ( OBJECT_STRING_ATTR ) + ") has invalid object of types (" + sERRTypes + ") attached with relation " + mArgumentsMap[RELATION_TYPE_ARG] );
            sConsolidatedErrorMessage.append ( "\n" );
        }
    }

    // If any disallowed object type found, return error msg
    if ( !sConsolidatedErrorMessage.empty() )
    {
        // Throw the error to the calling method (Where it will be handled)
        THROW ( sConsolidatedErrorMessage );
    }

    LOG_TRACE ( logger, "END : GET6_checkRelatedObjectsRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkItemStatusRH()
//
//    Purpose:   Rule handler to check if the related objects (If any) have the required status
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     29 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_checkItemStatusRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_checkItemStatusRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_checkItemStatusRH_impl );
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
        string sMessage = "GET6_checkItemStatusRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_checkItemStatusRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkItemStatusRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_checkItemStatusRH handler
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
//  TCS Development Team     29 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_checkItemStatusRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &p_vAttachments, map<string, string> &mArgumentsMap )
{
    bool bDisallowedObjFound = false;

    string sAllowedStatus = "";
    string sConsolidatedErrorMessage = "";

    vector<string> vErrorMessages;
    vector<string> vIncludedType;

    LOG_TRACE ( logger, "START : GET6_checkItemStatusRH_impl" );

    // Clear the existing error stack
    EMH_clear_errors();

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[RELATION_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    if ( mArgumentsMap.find ( ALLOWED_STATUS_ARG ) == mArgumentsMap.end() || mArgumentsMap[ALLOWED_STATUS_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( ALLOWED_STATUS_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    // Process the include type and allowed status argument values
    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludedType );
    sAllowedStatus = mArgumentsMap[ALLOWED_STATUS_ARG];
    GET_toLower ( sAllowedStatus );

    // Loop through each target objects
    for ( int iTargetIndex = 0; iTargetIndex < p_vAttachments[EPM_target_attachment].size(); iTargetIndex++ )
    {
        GET_WorkspaceObjectUnqPtr getTargetUnqPtr = GET_WorkspaceObject::getInstance ( p_vAttachments[EPM_target_attachment][iTargetIndex] );
        GET_WorkspaceObjectShrPtr getTargetShrPtr ( move ( getTargetUnqPtr ) );

        // Validate the target type
        if ( ! GET_isInVector ( vIncludedType, getTargetShrPtr->getType() ) )
        {
            continue;
        }

        // Get the related objects
        vector<GET_WorkspaceObjectUnqPtr> vRelatedObjects = GET_ImanRelation::listRelatedWsObjects ( getTargetShrPtr, mArgumentsMap[RELATION_TYPE_ARG],
                mArgumentsMap[RELATED_TYPE_ARG], mArgumentsMap.find ( PRIMARY_ARG ) != mArgumentsMap.end() ? true : false );
        for ( size_t iRelObjIndex = 0; iRelObjIndex < vRelatedObjects.size(); iRelObjIndex++ )
        {
            // Validate the status
            if ( sAllowedStatus.compare ( NONE_ARG_VAL ) == 0 || sAllowedStatus.compare ( NULL_ARG_VAL ) == 0 )
            {
                if ( vRelatedObjects[iRelObjIndex]->isReleased() )
                {
                    vErrorMessages.push_back ( vRelatedObjects[iRelObjIndex]->getPropString ( OBJECT_STRING_ATTR ) + " is expected to be in a Working state, but it is already released" );
                }
                continue;
            }
            if ( sAllowedStatus.compare ( ANY_ARG_VAL ) == 0 )
			{
				if ( ! vRelatedObjects[iRelObjIndex]->isReleased() )
				{
					vErrorMessages.push_back ( vRelatedObjects[iRelObjIndex]->getPropString ( OBJECT_STRING_ATTR ) + " is expected to be released status, but it is in a working state" );
				}
				continue;
			}
            if ( ! vRelatedObjects[iRelObjIndex]->hasReleaseStatus ( mArgumentsMap[ALLOWED_STATUS_ARG] ) )
            {
                vErrorMessages.push_back ( vRelatedObjects[iRelObjIndex]->getPropString ( OBJECT_STRING_ATTR ) + " is not released with the status " + mArgumentsMap[ALLOWED_STATUS_ARG] );
            }
        }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "GET6_checkItemStatusRH_impl found the following discrepancies : \n";
        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size (); iIndex++ )
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

    LOG_TRACE ( logger, "END : GET6_checkItemStatusRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateBOMChildTypesRH()
//
//    Purpose:   Rule handler to validate BOM Line children
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     29 Jun, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateBOMChildTypesRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateBOMChildTypesRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateBOMChildTypesRH_impl );
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
        string sMessage = "GET6_validateBOMChildTypesRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_validateBOMChildTypesRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateBOMChildTypesRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateBOMChildTypesRH handler
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
//  TCS Development Team     29 Jun, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_validateBOMChildTypesRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    string sConsolidatedErrorMessage = "";

    vector<string> vAllowedChildTypes;
    vector<string> vIncludeTypes;
    vector<string> vErrorMessages;

    LOG_TRACE ( logger, "START : GET6_validateBOMChildTypesRH_impl" );

    // Clear the existing error stack
    EMH_clear_errors();

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( REVISION_RULE_ARG ) == mArgumentsMap.end() || mArgumentsMap[REVISION_RULE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( REVISION_RULE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( ALLOWED_CHILD_TYPES_ARG ) == mArgumentsMap.end() || mArgumentsMap[ALLOWED_CHILD_TYPES_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( ALLOWED_CHILD_TYPES_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    // Process the include type and allowed status argument values
    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeTypes );
    GET_splitString ( mArgumentsMap[ALLOWED_CHILD_TYPES_ARG], COMMA_CHARACTER, vAllowedChildTypes );

    // Loop through each target objects
    for ( int iTargetIndex = 0; iTargetIndex < mAttachmentsMap[EPM_target_attachment].size(); iTargetIndex++ )
    {
    	// Validate if target is Item Revision
        if ( ! GET_POM_object::isDescendant ( mAttachmentsMap[EPM_target_attachment][iTargetIndex], ITEMREVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionUnqPtr itemRevUnqPtr = GET_ItemRevision::getInstance ( mAttachmentsMap[EPM_target_attachment][iTargetIndex] );
        GET_ItemRevisionShrPtr itemRevShrPtr ( move ( itemRevUnqPtr ) );

        // Validate the target type
        if ( ! GET_isInVector ( vIncludeTypes, itemRevShrPtr->getType() ) )
        {
            continue;
        }

        // Create BOM Window
        GET_BOMWindowUnqPtr bomWindowPtr = GET_BOMWindow::create();
        bomWindowPtr->setRevisionRule ( mArgumentsMap[REVISION_RULE_ARG] );
        GET_BOMViewRevisionShrPtr bvrShrPtr;
        GET_BOMLineUnqPtr topBOMLinePtr = bomWindowPtr->setTopLine ( itemRevShrPtr, bvrShrPtr );

        // Traverse only upto 1 level of structure
        vector<GET_BOMLineUnqPtr> vBOMLineChildren = topBOMLinePtr->getChildren();
        for ( int iInx = 0; iInx < vBOMLineChildren.size(); iInx++ )
        {
            // Validate incorrect child item types in BOM
            if ( ! GET_isInVector ( vAllowedChildTypes, vBOMLineChildren[iInx]->getItemRevision()->getType() ) )
            {
                vErrorMessages.push_back ( vBOMLineChildren[iInx]->getItemRevision()->getPropString ( OBJECT_STRING_ATTR ) );
            }
        }
    }

    // Store the error messages, if any in the Teamcenter Error Stack
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "Below BOM Child lines are not allowed to be part of the BOM, as their types are not valid:\n";
        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size (); iIndex++ )
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

    LOG_TRACE ( logger, "END : GET6_validateBOMChildTypesRH" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_traverseBOMRH()
//
//    Purpose:   Action Handler to traverse the BOM
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team    22 May, 2018         Added action handler for traversing the BOM
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_traverseBOMRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : EPM_rule_message_t" );

    try
    {
        GET_processHandler ( tMsg, GET6_traverseBOMRH_impl );
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
        string sMessage = "EPM_rule_message_t failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : EPM_rule_message_t" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_traverseBOMRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_traverseBOMRH handler
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
//  TCS Development Team     22 May, 2018         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_traverseBOMRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    string sConsolidatedErrorMessage = "";

    vector<string> vErrorMessages;
    vector<string> vAllowedChildTypes;

    vector<GET_ItemRevisionShrPtr> 	vValidSolutionItems;
    vector<GET_ItemRevisionShrPtr>  getItemRevList;
    vector<GET_POM_objectShrPtr>    vPOMObjShrPtr;

    LOG_TRACE ( logger, "START : GET6_traverseBOMRH_impl" );

    // Clear the existing error stack
    EMH_clear_errors();

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[RELATION_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( REVISION_RULE_ARG ) == mArgumentsMap.end() || mArgumentsMap[REVISION_RULE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( REVISION_RULE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( ALLOWED_CHILD_TYPES_ARG ) == mArgumentsMap.end() || mArgumentsMap[ALLOWED_CHILD_TYPES_ARG].empty() )
	{
		string sMsg = "The Workflow handler argument \"" + string ( ALLOWED_CHILD_TYPES_ARG )
				+ "\"  is missing or is empty";
		THROW ( sMsg );
	}

	// Process the allowed status argument values
    GET_splitString ( mArgumentsMap[ALLOWED_CHILD_TYPES_ARG], COMMA_CHARACTER, vAllowedChildTypes );

    // Loop through each target objects
    for ( int iTargetIndex = 0; iTargetIndex < mAttachmentsMap[EPM_target_attachment].size(); iTargetIndex++ )
    {
    	// Validate if target is ECN Revision
        if ( ! GET_POM_object::isDescendant ( mAttachmentsMap[EPM_target_attachment][iTargetIndex], ECNREVISION_TYPE ) )
        {
            continue;
        }

        GET_ItemRevisionUnqPtr ecnRevUnqPtr = GET_ItemRevision::getInstance ( mAttachmentsMap[EPM_target_attachment][iTargetIndex] );
        GET_ItemRevisionShrPtr ecnRevShrPtr ( move ( ecnRevUnqPtr ) );

        vector<GET_POM_objectUnqPtr> vSolutionItems = ecnRevShrPtr->getPropTags ( mArgumentsMap[RELATION_TYPE_ARG] );
        for( size_t iSolIndex = 0; iSolIndex < vSolutionItems.size(); iSolIndex++ )
		{
        	GET_ItemRevisionUnqPtr getItemRevUnqPtr = GET_ItemRevision::getInstance ( vSolutionItems[iSolIndex]->getTag() );
			GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( getItemRevUnqPtr ) );

			// Check the Solution Item object type
			if ( GET_isInVector ( vAllowedChildTypes, getItemRevShrPtr->getType() ) )
			{
			   vValidSolutionItems.push_back ( getItemRevShrPtr );
			}
		}
        LOG_TRACE ( logger, "Count of Valid Target object List from MCN Solution Items => " + vValidSolutionItems.size() );

        // Loop through each Solution Folder object
        for ( size_t iValidSolIndex = 0; iValidSolIndex < vValidSolutionItems.size(); iValidSolIndex++ )
		{
			// Create BOM Window
			GET_BOMWindowUnqPtr bomWindowPtr = GET_BOMWindow::create();
			bomWindowPtr->setRevisionRule ( mArgumentsMap[REVISION_RULE_ARG] );
			GET_BOMViewRevisionShrPtr bvrShrPtr;
			GET_BOMLineUnqPtr topBOMLineUnqPtr = bomWindowPtr->setTopLine ( vValidSolutionItems[iValidSolIndex], bvrShrPtr );
			GET_BOMLineShrPtr topBOMLineShrPtr ( move ( topBOMLineUnqPtr ) );

			// Call recurseBOM method to traverse to its BOMLine components
			recurseBOM ( topBOMLineShrPtr, vValidSolutionItems, vAllowedChildTypes, getItemRevList, vErrorMessages );
		}

		// ECN Revision found in Target, so break the loop
		break;
    }

    // Check the Error msg size
    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "Below BOM Child lines are not allowed to be part of the BOM, as they are not Released:\n";
        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size (); iIndex++ )
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
    else if ( getItemRevList.size() > 0 )
    {
    	// Adding Items to ITEM Folder
		addObjectsToRefFolder ( getItemRevList, FOLDERTYPE, OBJECT_ITEM, "Holds Child Items to be Transfered to Oracle", vPOMObjShrPtr );

		//Adding folders to to EPM Task
		GET_EPMTaskUnqPtr getEPMTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );
		getEPMTaskUnqPtr->addAttachments ( EPM_reference_attachment, vPOMObjShrPtr );

		getItemRevList.clear();
    }

    LOG_TRACE ( logger, "END : GET6_traverseBOMRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   recurseBOM()
//
//    Purpose:   Function to recurse BOM
//
//    Inputs:    BOMLine
//
//    Outputs:   Vector of Item
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     22 May, 2018         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void recurseBOM ( GET_BOMLineShrPtr p_getBOMLineShrPtr, vector<GET_ItemRevisionShrPtr> vValidSolutionItems, vector<string> vAllowedChildTypes, vector<GET_ItemRevisionShrPtr>& vItemRevList, vector<string>& vErrorMessages )
{
    LOG_TRACE(logger, "Entering...recurseBOM");

	GET_ItemRevisionUnqPtr getParentItemRevUnqPtr = p_getBOMLineShrPtr->getItemRevision();

    // Check whether BOMLine is configured or unconfigured
    if ( getParentItemRevUnqPtr == NULL || getParentItemRevUnqPtr.get() == NULL )
    {
        GET_ItemUnqPtr getItemUnqPtr = p_getBOMLineShrPtr->getItem();
        vErrorMessages.push_back ( getParentItemRevUnqPtr->getPropString ( OBJECT_STRING_ATTR ) );
	}
    else
    {
        GET_ItemRevisionShrPtr getParentItemRevShrPtr ( move ( getParentItemRevUnqPtr ) );

        // Check if Item is already processed, if not then only process
        if ( GET_ExistsInVector ( vItemRevList, getParentItemRevShrPtr ) == false )
        {
        	vItemRevList.push_back ( getParentItemRevShrPtr );

        	// Check if Item Revision is Released
			if ( ! getParentItemRevShrPtr->isReleased() )
			{
				// Check if this Non Released Item Revision is already copied to Solution Folder, if not error out
				if ( GET_ExistsInVector ( vValidSolutionItems, getParentItemRevShrPtr ) == false )
				{
					vErrorMessages.push_back ( getParentItemRevShrPtr->getPropString ( OBJECT_STRING_ATTR ) );
				}
			}

			vector<GET_BOMLineUnqPtr> vBOMLineChildren = p_getBOMLineShrPtr->getChildren();

			for ( int inx = 0; inx < vBOMLineChildren.size(); inx++ )
			{
				// Process only for allowed child type
				if ( GET_isInVector ( vAllowedChildTypes, vBOMLineChildren[inx]->getItemRevision()->getType() ) )
				{
					GET_BOMLineShrPtr getBOMLineShrPtr ( move ( vBOMLineChildren[inx] ) );
					recurseBOM ( getBOMLineShrPtr, vValidSolutionItems, vAllowedChildTypes, vItemRevList, vErrorMessages );
				}
			}
        }
    }

    LOG_TRACE(logger, "Exiting...recurseBOM");
}

bool GET_ExistsInVector( vector<GET_ItemRevisionShrPtr> TargetItemRevVector, GET_ItemRevisionShrPtr ItemRevVector )
{
    bool isTrue = false;
    string Itemid = ItemRevVector->getId();

    for( size_t inx=0; inx<TargetItemRevVector.size(); inx++ )
    {
        string targetID =  TargetItemRevVector[inx]->getId();
        if( strcmp( targetID.c_str(), Itemid.c_str() ) == 0 )
        {
            isTrue = true;
            break;
        }
    }
    return isTrue;
}

void addObjectsToRefFolder ( vector<GET_ItemRevisionShrPtr> vObjectRevList, string sObjectType, string sfolderName, string sfolderDecs, vector<GET_POM_objectShrPtr>& vPOMObjShrPtr )
{
	GET_FolderUnqPtr getFolderUnqPtr = GET_Folder::create ( sObjectType, sfolderName, sfolderDecs );

    for( size_t iObjRevIndex = 0; iObjRevIndex < vObjectRevList.size(); iObjRevIndex++ )
    {
        GET_WorkspaceObjectShrPtr getWSObjShrPtr ( move ( GET_WorkspaceObject::getInstance ( vObjectRevList[iObjRevIndex]->getTag() ) ) );
        getFolderUnqPtr->insertInto ( getWSObjShrPtr, iObjRevIndex );
    }

    // convert folder object in proper format to add in EPM Task
    GET_POM_objectShrPtr getPOMITEMFolderObjShrPtr ( move ( GET_POM_object::getInstance ( getFolderUnqPtr->getTag() ) ) );
    vPOMObjShrPtr.push_back ( getPOMITEMFolderObjShrPtr );
}
