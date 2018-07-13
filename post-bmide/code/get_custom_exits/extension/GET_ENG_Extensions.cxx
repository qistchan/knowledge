
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_ENG_Extensions.cxx
 //
 //    Purpose:   Source file for Engineering extensions
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     20 May, 2016         Initial creation
 //  TCS Development Team     16 Nov, 2016         Created a Pre-Action Extension method for finalizeCreateInput operation
 //  Capgemini Development Team     23 Jan, 2017         Created a Pre-Condition GET6_validateOverallUOM for IMAN_Save operation
 //  Ganesh Ubale             25 Apr, 2017         Created a Pre-Condition GET6_revisePreCondition for ITEM_copy_rev operation
 //  TechM Development Team   23 June, 2017        Modified GET6_revisePreCondition to ignore baseline revisions
 //  TechM Development Team   30 June, 2017        Modified GET6_revisePreCondition to check the revision id sequence
 //  TCS Development Team     06 July, 2017        Replaced the string literal "." with the constant DOT_CHARACTER in the method GET6_revisePreCondition
 //  TCS Development Team     21 July, 2017        Modified the GET6_generateRevID method to match the change in preference value for ASSIGNED_ITEM_REV_MODIFIABLE
 //  TCS Development Team     01 Sep, 2017         Added property getter method GET6_get6CASDownloderURLGetValue
 //   ============================================================================
 // ENDFILEDOC   ***/

// GET Includes
#include <GET_ENG_Extensions.hxx>
#include <GET_Constants.hxx>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_GroupMember.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_Item.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_POM_application_object.hxx>
#include <GET_POM_group.hxx>
#include <GET_POM_user.hxx>
#include <GET_Preferences.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>

// Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <tc/tc_arguments.h>
#include <ug_va_copy.h>

#include <vector>

// Private Function Prototypes
string generateNextAlpha ( const string );
string getNextRevisionID ( const string );

using namespace get;
using namespace Teamcenter; // For accessing Teamcenter C++ Objects

const string logger = "get.extension.GET_ENG_Extensions";

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  generateNextAlpha
 //
 //    Purpose:  Function to generate the next alphabet in sequence
 //
 //    Inputs:   sAlpha - Input upper case alphabet
 //
 //    Outputs:  none
 //
 //    Return:   The next alphabet
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     30 Sep, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
string generateNextAlpha ( const string sAlpha )
{
    const char *pAlpha = sAlpha.c_str();
    string nextAlpha = "";

    if ( sAlpha[sAlpha.length() - 1] == 'Z' )
    {
        if ( sAlpha.length() > 1 )
        {
            string sTemp = sAlpha.substr ( 0, sAlpha.length() - 1 );
            nextAlpha =  generateNextAlpha ( sTemp ) + "A";
        }
        else
        {
            nextAlpha =  nextAlpha + "AA";
        }
    }
    else
    {
        string sSubTemp = ( sAlpha.substr ( 0, sAlpha.length() - 1 ) );
        string sLastLetter = "";
        sLastLetter = pAlpha[sAlpha.length() -1] + 1;
        string sTemp =  sSubTemp + sLastLetter;
        nextAlpha = nextAlpha + sTemp;
    }

    return nextAlpha;
}

/*STARTFUNCDOC ***
//
===========================================================================
//    Function:  GET6_revisePreCondition
//
//    Purpose:  Pre Condition method for ITEM_create_rev, ITEM_copy_rev operation registered on GET6MechPartRevision, GET6ElectPartRevision, GET6DocumentRevision, 
//              GET6SpecsRevision, GET6DrawingRevision, GET6MaterialRevision Item Revision types. 
//              Checks if the selected revision is the latest revision for the given Item or not and displays an error message to the user.
//              Checks if the user entered revision id is valid or in sequence
//
//    Inputs:   msg - The Message input from the handler
//              vaArgs - The Variable Argument List input for this Extension Method
//
//    Outputs:  none
//
//    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
//
//    History:
//      Who                    Date                 Description
//   Ganesh Ubale             25 Apr, 2017         Initial creation
//   TechM Development Team   23 June, 2017        Modified this method to ignore baseline revisions
//   TechM Development Team   30 June, 2017        Modified this method to check the revision id sequence
//   TCS Development Team     06 July, 2017        Replaced the string literal "." with the constant DOT_CHARACTER
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_revisePreCondition ( METHOD_message_t* msg, va_list args )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_revisePreCondition" );

    try
    {
        string sNewRevId = "";
        string sLatestRevId = "";

        tag_t tObject = va_arg ( args, tag_t );
        const char *pcNewRevId = va_arg ( args, char* );
        sNewRevId = pcNewRevId;

        if ( GET_POM_object::isDescendant ( tObject, ITEMREVISION_CLASS ) )
        {
            GET_ItemRevisionUnqPtr sourceRevisionPtr;
            GET_ItemRevisionUnqPtr latestRevisionPtr;
            GET_ItemRevisionUnqPtr itemRevBaseUnqPtr;

            sourceRevisionPtr = GET_ItemRevision::getInstance ( tObject );
            latestRevisionPtr = sourceRevisionPtr->getItem()->getLatestRevision();
            itemRevBaseUnqPtr = latestRevisionPtr->getBaseRev();

            //revise latest revision check, (if the latest revision is baseline revision)
            if ( itemRevBaseUnqPtr.get() != NULL && itemRevBaseUnqPtr->getTag() != NULLTAG )
            {
                sLatestRevId = itemRevBaseUnqPtr->getRevId();
            }
            else
            {
                sLatestRevId = latestRevisionPtr->getRevId();
            }
            //revise latest revision check
            if ( sLatestRevId.compare ( sourceRevisionPtr->getRevId() ) != 0 )
            {
                THROW ( REVISE_LATEST_ERR_MSG );
            }
            //Check revision id sequence - string length of new revision cannot be less than current revision
            //Check revision id sequence - new revision should be greater than current revision
            if ( sNewRevId.length() < sLatestRevId.length() || ( sNewRevId.length() == sLatestRevId.length() && sNewRevId.compare ( sLatestRevId ) < 0 ) )
            {
                THROW ( NEXT_REVID_VALIDATION_ERR_MSG );
            }
        }
        //Execute this code for both ITEM_create_rev and ITEM_copy_rev operation
        //check the user entered rev id doesn't contain invalid characters (.)
        if ( sNewRevId.find ( DOT_CHARACTER ) != string::npos )
        {
            THROW ( REVID_VALIDATION_ERR_MSG );
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_revisePreCondition function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_revisePreCondition" );

    return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET6_setECNID
 //
 //    Purpose:  Extension Method for generating ECN item IDs while deriving from ECR.
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
 //  TCS Development Team     24 May, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_setECNID ( METHOD_message_t* msg, va_list args )
{
    bool bIsExecuteable = false;

    int iFail = ITK_ok;
    int iLastECNCounter = 0;

    GET_ItemRevisionUnqPtr pECNRevisionPtr;
    GET_ItemUnqPtr pECNPtr;
    GET_ItemRevisionUnqPtr pECRRevisionPtr;
    GET_ItemUnqPtr pECRPtr;

    string sNewGenItemID = "";
    string sNewItemId = "";

    vector<int> vECNCounters;
    vector < string > vOutput;
    vector < string > vPrefValues;
    vector < GET_WorkspaceObjectUnqPtr> vRelatedEcns;
    vector < GET_WorkspaceObjectUnqPtr> vRelatedItemMaster;
    vector < GET_WorkspaceObjectUnqPtr> vRelatedItemRevMaster;

    tag_t tPrimary_object = va_arg ( args, tag_t );
    tag_t tSecondary_object = va_arg ( args, tag_t );
    tag_t tRelation_type = va_arg ( args, tag_t );
    tag_t tUser_data = va_arg ( args, tag_t );
    tag_t *tNew_relation = va_arg ( args, tag_t* );

    LOG_TRACE( logger, "START : GET6_setECNID" );

    try
    {
        try
        {
            getStringPrefValues ( CM_GENERATE_ECNID_PREF, vPrefValues );
        }
        catch ( IFail &ex )
        {
            LOG_ERROR ( logger, "Exception in getting Preference value " + ex.getMessage() );
        }

        if ( !vPrefValues.empty () )
        {
            vOutput.clear ();
            const string sPrefValue = vPrefValues[0];

            GET_splitString ( sPrefValue, COLON_SEPERATOR, vOutput );

            if ( !vOutput.empty () && vOutput.size () == 2 )
            {
                if ( vOutput[0].compare ( ECRREVISION_TYPE ) == 0 || vOutput[1].compare ( ECNREVISION_TYPE ) == 0 )
                {
                    if ( GET_POM_object::isDescendant ( tPrimary_object, ECNREVISION_TYPE ) &&
                            GET_POM_object::isDescendant ( tSecondary_object, ECRREVISION_TYPE ) )
                    {
                        bIsExecuteable = true;
                    }
                }
            }
        }
        else
        {
            LOG_DEBUG( logger, "No values found in preference" );
        }

        if ( bIsExecuteable )
        {
            pECNRevisionPtr = GET_ItemRevision::getInstance ( tPrimary_object );

            pECNPtr = pECNRevisionPtr->getItem ();

            string isNewECN = pECNPtr->getPropValueAsString ( IS_NEW_ECN_ATTR );
            if ( isNewECN.compare ( FALSE_DISPLAY ) == 0 )
            {
                LOG_DEBUG( logger, "ECN is already derived from an ECR" );
                LOG_TRACE( logger, "END : GET6_setECNID" );

                return iFail;
            }

            pECRRevisionPtr = GET_ItemRevision::getInstance ( tSecondary_object );

            pECRPtr = pECRRevisionPtr->getItem ();

            const string sItemIdEcr = pECRPtr->getId ();

            vOutput.clear ();

            GET_splitString ( sItemIdEcr, HYPHEN_SEPERATOR, vOutput );

            if ( !vOutput.empty () && vOutput.size () > 1 )
            {
                sNewItemId = string ( ECN_TYPE_PREFIX ) + string ( HYPHEN_SEPERATOR ) + vOutput[1];
            }

            GET_ItemRevisionShrPtr ecrRevisionShrPtr ( move ( pECRRevisionPtr ) );

            vRelatedEcns = GET_ImanRelation::listRelatedWsObjects ( ecrRevisionShrPtr, CMIMPLEMENTS, ECNREVISION_TYPE, true );

            for ( int k = 0; !vRelatedEcns.empty () && k < vRelatedEcns.size (); k++ )
            {
                vOutput.clear();
                GET_ItemRevisionUnqPtr itemRevObjPtr = GET_ItemRevision::getInstance ( vRelatedEcns[k]->getTag() );
                string sTempItemId = itemRevObjPtr->getId();
                GET_splitString ( sTempItemId, HYPHEN_SEPERATOR, vOutput );

                if ( !vOutput.empty () && vOutput.size () > 2 )
                {
                    string sECNCounter = vOutput[2];
                    int iECNCounter = std::stoi ( sECNCounter );
                    vECNCounters.push_back ( iECNCounter );
                }
            }

            if ( !vECNCounters.empty () )
            {
                sort ( vECNCounters.begin (), vECNCounters.end () );
                iLastECNCounter = vECNCounters[vECNCounters.size () - 1];
            }

            while ( true )
            {
                iLastECNCounter++;
                stringstream sTempStream;
                sTempStream << iLastECNCounter;
                string sTempIntString = sTempStream.str ();
                if ( iLastECNCounter < 10 )
                {
                    sTempIntString = string ( ZERO_CHARACTER ) + sTempIntString;
                }

                sNewGenItemID = sNewItemId + string ( HYPHEN_SEPERATOR ) + sTempIntString;

                GET_ItemUnqPtr pItemExists = GET_Item::find ( sNewGenItemID );
                if ( pItemExists == NULL )
                {
                    break;
                }
            }

            const string sPropValue = sNewGenItemID;

            // setting new item ID to ECN
            pECNPtr->setProp ( ITEM_ID_ATTR, sPropValue );
            pECNPtr->setProp ( IS_NEW_ECN_ATTR, false );

            //Now change the Item Master and Item Revision Master Form Names.
            GET_ItemShrPtr ecnShrPtr ( move ( pECNPtr ) );
            GET_ItemRevisionShrPtr ecnRevShrPtr ( move ( GET_ItemRevision::getInstance (tPrimary_object) ) );

            vRelatedItemMaster = GET_ImanRelation::listRelatedWsObjects ( ecnShrPtr, IMANMASTERFORM, ECNMASTERFORM, false );
            vRelatedItemRevMaster = GET_ImanRelation::listRelatedWsObjects ( ecnRevShrPtr, IMANMASTERFORM, ECNMASTERREVISIONFORM, false );

            if ( !vRelatedItemMaster.empty () )
            {
                vRelatedItemMaster[0]->setProp ( OBJECT_NAME_ATTR, sPropValue );
            }

            if ( !vRelatedItemRevMaster.empty () )
            {
                const string sNewPropVal = sPropValue + string ( BACKSLASH_SEPERATOR ) + ecnRevShrPtr->getRevId ();
                vRelatedItemRevMaster[0]->setProp ( OBJECT_NAME_ATTR, sNewPropVal );
            }
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage () );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage ().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_setECNID function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_setECNID" );

    return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET6_propagatePropsECRToECN
 //
 //    Purpose:  Extension Method for propagating properties from ECR to ECN when ECN derived from ECR.
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
 //  TCS Development Team     26 May, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_propagatePropsECRToECN ( METHOD_message_t* msg, va_list args )
{
    bool bIsExecuteable = false;

    int iFail = ITK_ok;

    GET_ItemRevisionUnqPtr pECNRevisionPtr;
    GET_ItemUnqPtr pECNPtr;
    GET_ItemRevisionUnqPtr pECRRevisionPtr;
    GET_ItemUnqPtr pECRPtr;

    tag_t tPrimary_object = va_arg ( args, tag_t );
    tag_t tSecondary_object = va_arg ( args, tag_t );

    vector < string > vOutput;
    vector < string > vPrefValues;

    LOG_TRACE ( logger, "START : GET6_propagatePropsECRToECN" );

    try
    {
        try
        {
            getStringPrefValues ( CM_ECRTOECN_PROPOGATE_PROP_PREF, vPrefValues );
        }
        catch ( const IFail &ex )
        {
            return iFail;
        }

        if ( !vPrefValues.empty () )
        {
            if ( GET_POM_object::isDescendant ( tPrimary_object,
            ECNREVISION_TYPE ) && GET_POM_object::isDescendant ( tSecondary_object,
            ECRREVISION_TYPE ) )
            {
                bIsExecuteable = true;
            }
        }

        if ( bIsExecuteable )
        {
            pECNRevisionPtr = GET_ItemRevision::getInstance ( tPrimary_object );

            pECRRevisionPtr = GET_ItemRevision::getInstance ( tSecondary_object );

            //get secondary objects of ECN and make sure this is the first one

            //split prefValues based on delimiter "|"
            for ( int i = 0; !vPrefValues.empty () && i < vPrefValues.size (); i++ )
            {
                vOutput.clear ();
                GET_splitString ( vPrefValues[i], "|", vOutput );

                if ( !vPrefValues.empty () && vOutput.size () == 2 )
                {
                    PROP_value_type_t ecrPropValueType = pECRRevisionPtr->askPropValueType ( vOutput[0] );
                    PROP_value_type_t ecnPropValueType = pECNRevisionPtr->askPropValueType ( vOutput[1] );

                    if ( ecrPropValueType == ecnPropValueType && pECNRevisionPtr->isPropModifiable ( vOutput[1] ) )
                    {
                        switch (ecrPropValueType)
                        {
                        case PROP_string:

                            if ( pECRRevisionPtr->isPropList ( vOutput[0] ) )
                            {
                                pECNRevisionPtr->setProp ( vOutput[1], pECRRevisionPtr->getPropStrings ( vOutput[0] ) );
                            }
                            else
                            {
                                pECNRevisionPtr->setProp ( vOutput[1], pECRRevisionPtr->getPropString ( vOutput[0] ) );
                            }
                            break;

                        case PROP_int:

                            if ( pECRRevisionPtr->isPropList ( vOutput[0] ) )
                            {
                                pECNRevisionPtr->setProp ( vOutput[1], pECRRevisionPtr->getPropIntegers ( vOutput[0] ) );

                            }
                            else
                            {
                                pECNRevisionPtr->setProp ( vOutput[1], pECRRevisionPtr->getPropInteger ( vOutput[0] ) );
                            }
                            break;

                        case PROP_logical:

                            if ( pECRRevisionPtr->isPropList ( vOutput[0] ) )
                            {
                                pECNRevisionPtr->setProp ( vOutput[1], pECRRevisionPtr->getPropLogicals ( vOutput[0] ) );
                            }
                            else
                            {
                                pECNRevisionPtr->setProp ( vOutput[1], pECRRevisionPtr->getPropLogical ( vOutput[0] ) );
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage () );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage ().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_propagatePropsECRToECN function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_propagatePropsECRToECN" );

    return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET6_generateRevID
 //
 //   Purpose :   To generate next available rev id
 //
 //   Inputs  :   msg (Type - METHOD_message_t*), args (Type - va_list)
 //
 //   Outputs :   none
 //
 //   Return  :   int - ITK return code 0 - Success, Non-Zero - Failure
 //
 //   History :
 //      Who                   Date                 Description
 //  TCS Development Team     30 Sep, 2016         Initial creation
 //  TCS Development Team     21 July, 2017        Modified the code to match the change in preference value for ASSIGNED_ITEM_REV_MODIFIABLE
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_generateRevID ( int *decision, va_list args )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_generateRevId" );

    try
    {
        string sObjType = "";

        vector < string > vPrefValues;
        vector < string > vSkipRevId;
        vector < string > vItemTypes;
        vector < string > vNonModItemTypes;

        va_list largs;

        va_copy ( largs, args );
        tag_t tItemTag = va_arg ( largs, tag_t );
        tag_t tItemType = va_arg ( largs, tag_t );
        logical *mod = va_arg ( largs, logical * );
        char **id = va_arg ( largs, char ** );

        *decision = ALL_CUSTOMIZATIONS;
        *mod = TRUE;

        getStringPrefValues ( GET_ENG_GENERATE_REV_ID_ITEM_TYPES, vPrefValues );
        if ( ! vPrefValues.empty() )
        {
            GET_splitString ( vPrefValues[0], ",", vItemTypes );
        }
        if ( vItemTypes.size() == 0 )
        {
            string sError = string ( GET_ENG_GENERATE_REV_ID_ITEM_TYPES ) + string ( " preference is not set or has empty values, Please contact system administrator" );
            THROW ( sError );
        }

        vPrefValues.clear();
        getStringPrefValues ( GET_ASSIGNED_REV_NON_MODIFIABLE_TYPES, vPrefValues );
        if ( ! vPrefValues.empty() )
        {
            GET_splitString ( vPrefValues[0], ",", vNonModItemTypes );
        }
        if ( vNonModItemTypes.size() == 0 )
        {
            string sError = string ( GET_ASSIGNED_REV_NON_MODIFIABLE_TYPES ) + string ( " preference is not set or has empty values, Please contact system administrator" );
            THROW ( sError );
        }

        sObjType = GET_POM_object::askTypeName ( tItemType );

        //Check if the rev id field should be made editable
        if ( GET_isInVector ( vNonModItemTypes, sObjType ) )
        {
            LOG_DEBUG( logger, "Assigned rev modifiable is set as false for object type " + sObjType );
            *mod = FALSE;
        }
        //Skip the customization for unwanted types
        if ( ! GET_isInVector ( vItemTypes, sObjType ) )
        {
            *decision = NO_CUSTOMIZATION;
        }
        //check if the rev id has to be pre-populated
        else
        {
            string sNewRevId = "";

            if ( tItemTag == NULLTAG ) //Set first revision id as 0
            {
                sNewRevId = string ( ZERO_CHARACTER );
            }
            else
            {
                GET_ItemUnqPtr itemUnqPtr = GET_Item::getInstance ( tItemTag );
                sNewRevId = getNextRevisionID ( itemUnqPtr->getId() );
            }

            *id = (char *) MEM_alloc ( sizeof(char) * ( sNewRevId.length () + 1 ) );
            tc_strcpy ( *id, sNewRevId.c_str() );
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage () );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage ().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_generateEngRevId function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_generateRevId" );

    return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  getNextRevisionID
 //
 //    Purpose:  Function to generate the next Item Revision ID in sequence
 //
 //    Inputs:   sItemId - The Item ID of the Item
 //
 //    Outputs:  none
 //
 //    Return:   The next Item Revision ID in sequence
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     16 Nov, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
string getNextRevisionID ( const string sItemId )
{
    string sNewRevId = "";

    GET_ItemUnqPtr itemUnqPtr = GET_Item::find ( sItemId );
    if ( itemUnqPtr == NULL || itemUnqPtr.get() == NULL )
    {
        // Set first revision id as 0
        sNewRevId = string ( ZERO_CHARACTER );
    }
    else
    {
        bool bGenerate = true;

        string sCurrentRevId = "";

        vector < string > vPrefValues;
        vector < string > vSkipRevId;

        GET_ItemRevisionUnqPtr itemRevUnqPtr = itemUnqPtr->getLatestRevision();

        getStringPrefValues ( GET_ENG_DISALLOWED_REV_IDS, vPrefValues );
        if ( !vPrefValues.empty () )
        {
            GET_splitString ( vPrefValues[0], ",", vSkipRevId );
        }
        else
        {
            string sError = string ( GET_ENG_DISALLOWED_REV_IDS ) + string ( " preference is not set, Please contact system administrator" );
            THROW ( sError );
        }

        // Check if it is a baselined rev and get the base rev
        GET_ItemRevisionUnqPtr itemBaseUnqPtr = itemRevUnqPtr->getBaseRev ();
        if ( itemBaseUnqPtr.get () != NULL && itemBaseUnqPtr->getTag () != NULLTAG )
        {
            LOG_DEBUG( logger, "The revision is baselined one, getting the base rev" );
            sCurrentRevId = itemBaseUnqPtr->getRevId ();
        }
        else
        {
            sCurrentRevId = itemRevUnqPtr->getRevId ();
        }

        sNewRevId = sCurrentRevId;
        // If rev id is not an alphabet, which is expected here, set it as A
        if ( ! GET_isAlpha ( sNewRevId ) )
        {
            LOG_DEBUG ( logger, "The revision id is not alphabetic, changing it to alpha" );
            sNewRevId = "A";
            bGenerate = false;
        }
        GET_toUpper ( sNewRevId ); // Make sure the Id is upper case
        do
        {
            if ( bGenerate )
            {
                sNewRevId = generateNextAlpha ( sNewRevId );
            }
            GET_ItemRevisionUnqPtr existingRevPtr = itemUnqPtr->findRevision ( sNewRevId );
            if ( existingRevPtr.get () != NULL && existingRevPtr->getTag () != NULLTAG )
            {
                bGenerate = true;
                continue;
            }
            bGenerate = false;

            for ( size_t iIndex = 0; iIndex < vSkipRevId.size (); iIndex++ )
            {
                // Start : Manipulating value to skip redundant looping
                size_t iSkipPosn = sNewRevId.find_first_of ( vSkipRevId [iIndex] );
                if ( iSkipPosn != string::npos )
                {
                    size_t iLength = sNewRevId.length ();
                    sNewRevId = sNewRevId.substr ( 0, iSkipPosn + 1 );
                    for ( size_t iSkipIndex = iSkipPosn; iSkipIndex < iLength - 1; iSkipIndex++)
                    {
                        sNewRevId = sNewRevId + "Z";
                    }
                    bGenerate = true;
                    break;
                }
                // End : Manipulating value to skip redundant looping
            }
        }
        while ( bGenerate );
    }

    return sNewRevId;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET6_verifyIPClassificationAccess
 //
 //    Purpose:  Extension Method for verifying whether the current user has access to modify the IP Classification property or not
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
 //  TCS Development Team     29 Nov, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_verifyIPClassificationAccess ( METHOD_message_t* msg, va_list args )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_verifyIPClassificationAccess" );

    try
    {
        // Get the Object from the Message
        GET_POM_application_objectUnqPtr applicationObject = GET_POM_application_object::getInstance ( msg->object_tag );

        va_list largs;
        va_copy ( largs, args );

        tag_t tPropTag = va_arg ( largs, tag_t );
        char *value = va_arg ( largs, char * );

        string sCurrentIPValue = applicationObject->getPropString ( IP_CLASSIFICATION_ATTR );

        //Validate only if the value if different
        if ( sCurrentIPValue.compare ( value ) != 0 )
        {
            // Get the current session group member
            GET_GroupMemberUnqPtr currentGroupMember = GET_GroupMember::getCurrentGroupMember();

            // Check if the current user is the owning user
            if ( currentGroupMember->getUser()->getName().compare ( applicationObject->getOwningUser()->getName() ) != 0 )
            {
                // Check if the current session group is dba or not
                if ( currentGroupMember->getGroup()->getGroupFullName().compare ( DBA_GROUP ) != 0 )
                {
                    string sErrorMessage = "Only the Owning User or a System Administrator can modify the \"" + applicationObject->getPropDisplayName ( IP_CLASSIFICATION_ATTR ) + "\" attribute";
                    THROW ( sErrorMessage );
                }
            }
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_verifyIPClassificationAccess function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_verifyIPClassificationAccess" );

    return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET6_validateOverallUOM
 //
 //    Purpose:  Extension Method used as Pre-Condition to make Overall UOM mandatory if either Overall Width or Overall Height or Overall Length is filled 
 //
 //    Inputs:   msg - The Message input from the handler
 //              vaArgs - The Variable Argument List input for this Extension Method
 //
 //    Outputs:  none
 //
 //    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
 //
 //    History:
 //      Who                           Date                 Description
 //  Capgemini Development Team     23 Jan, 2017         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_validateOverallUOM(METHOD_message_t* msg, va_list args)
{

    int iFail = ITK_ok;
    
    tag_t tObject = va_arg (args, tag_t);
    LOG_TRACE ( logger, "START : GET6_validateOverallUOM" );
    
    try
    {
        // Get the Item Revision pointer
        GET_ItemRevisionUnqPtr pRevisionPtr = GET_ItemRevision::getInstance ( tObject );
        
        // Retreive the attribute values
        string sOverallLength = pRevisionPtr->getPropValueAsString ( OVERALL_LENGTH_ATTR );
        string sOverallWidth = pRevisionPtr->getPropValueAsString ( OVERALL_WIDTH_ATTR);
        string sOverallHeight = pRevisionPtr->getPropValueAsString ( OVERALL_HEIGHT_ATTR);
        string sOverallUom = pRevisionPtr->getPropValueAsString ( OVERALL_UOM_ATTR);
        string sOverallUOMDisplayName = pRevisionPtr->getPropDisplayName(OVERALL_UOM_ATTR);
        string sOverallLengthDisplayName = pRevisionPtr->getPropDisplayName(OVERALL_LENGTH_ATTR);
        string sOverallWidthDisplayName = pRevisionPtr->getPropDisplayName(OVERALL_WIDTH_ATTR);
        string sOverallHeightDisplayName = pRevisionPtr->getPropDisplayName(OVERALL_HEIGHT_ATTR);

        // Check if any of the Overall Length/Width/Height is populated or Overall UOM is null
        if(( !sOverallLength.empty() || !sOverallWidth.empty() || !sOverallHeight.empty() ) && sOverallUom.empty() )
        {
            iFail = GET_general_exception;
            string sErrorMessage = string ("Please populate ") + sOverallUOMDisplayName;
            LOG_ERROR( logger, sErrorMessage );
            LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
        }
        //Limit the Overall length/width/height to 4 decimal places
        if((sOverallLength.find(".")!=string::npos) && (sOverallLength.substr(sOverallLength.find(".")+1)).length()> MAX_DECIMAL_LIMIT)
        {
            iFail = GET_general_exception;
            string sErrorMessage = string ("Maximum allowed decimal limit for ") + sOverallLengthDisplayName + string (" is ") + GET_intToString(MAX_DECIMAL_LIMIT);
            LOG_ERROR( logger, sErrorMessage );
            LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
        }
        if((sOverallWidth.find(".")!=string::npos) && (sOverallWidth.substr(sOverallWidth.find(".")+1)).length()> MAX_DECIMAL_LIMIT)
        {
            iFail = GET_general_exception;
            string sErrorMessage = string ("Maximum allowed decimal limit for ") + sOverallWidthDisplayName + string (" is ") + GET_intToString(MAX_DECIMAL_LIMIT);
            LOG_ERROR( logger, sErrorMessage );
            LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
        }
        if((sOverallHeight.find(".")!=string::npos) && (sOverallHeight.substr(sOverallHeight.find(".")+1)).length()> MAX_DECIMAL_LIMIT)
        {
            iFail = GET_general_exception;
            string sErrorMessage = string ("Maximum allowed decimal limit for ") + sOverallHeightDisplayName + string (" is ") + GET_intToString(MAX_DECIMAL_LIMIT);
            LOG_ERROR( logger, sErrorMessage );
            LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_validateOverallUOM function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }
    
    LOG_TRACE ( logger, "END : GET6_validateOverallUOM" );
    
    return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET6_get6CASDownloderURLGetValue
 //
 //    Purpose:  Getter Method for retrieving the Property value for get6RuntimeProp property
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
 //  TCS Development Team     01 Sep, 2017         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_get6CASDownloderURLGetValue ( METHOD_message_t* msg, va_list args )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_get6CASDownloderURLGetValue" );

    try
    {
        vector < string > vPrefValues;

        va_list largs;
        va_copy ( largs, args );

        va_arg ( largs, tag_t );
        char** value = va_arg ( largs, char** );
        logical* is_null = va_arg ( largs, logical* );
        logical* is_empty = va_arg ( largs, logical* );
        va_end ( largs );

        *value = 0;
        *is_null = FALSE;
        *is_empty = FALSE;

        getStringPrefValues ( GET_CAS_DATA_DOWNLOADER_URL, vPrefValues );
        if ( ! vPrefValues.empty() )
        {
            *value = MEM_string_copy ( ( char* ) vPrefValues[0].c_str() );
        }
        else
        {
            *value = MEM_string_copy ( "GET_CAS_DATA_DOWNLOADER_URL preference is not set or has empty values, Please contact system administrator " );
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        iFail = GET_general_exception;
        string sErrorMessage = "An unexpected error occurred in the GET6_get6CASDownloderURLGetValue function. Please contact your System Administrator";
        LOG_ERROR ( logger, sErrorMessage );
        LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_get6CASDownloderURLGetValue" );

    return iFail;
}
