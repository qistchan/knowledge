
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_T4O_RuleHandlers.cxx
//
//    Purpose:   Source File defining the T4O Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016         Initial creation
//  TCS Development Team      27 Sep, 2017         Updated GET6_validateT4OTransferRH_impl function to add validation for BOP structure
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_T4O_Common.hxx>
#include <GET_T4O_RuleHandlers.hxx>
#include <GET_MFG_RuleHandlers.hxx>
#include <GET_MFG_ActionHandlers.hxx>
#include <GET_POM_object.hxx>

// CPP Includes
#include <map>

using namespace get;

// Private Function Prototypes

static void GET6_validateT4OTransferRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );

const string logger = "get.handler.GET_T4O_RuleHandler";


/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateT4OTransferRH()
//
//    Purpose:   Rule Handler to validate all required attributes/objects for T4O transfer.
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     01 Dec, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateT4OTransferRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateT4OTransferRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateT4OTransferRH_impl );
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
        string sMessage = "GET6_validateT4OTransferRH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_validateT4OTransferRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateT4OTransferRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateT4OTransferRH handler
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
//  TCS Development Team     01 Dec, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_validateT4OTransferRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &p_vAttachments, map<string, string> &mArgumentsMap )
{
    int istatus = ITK_ok;
				
	bool isProductLinked = false;
    bool isDeptFound = false;
    bool bMBOMExist = false;
    bool bBOPExist  = false;
    bool bProdExistInSoFol = false;

    vector<string>  vBOPObjRevPrefValues;
    vector<string>  vMBOMObjRevPrefValues;
	string sConsolidatedErrorMessage = EMPTY_STRING_VALUE;
	
	GET_ItemRevisionShrPtr linkedProductRevShrPtr;
	GET_ItemRevisionShrPtr linkedProcessRevShrPtr;
	GET_ItemRevisionShrPtr linkedDepartmentRevShrPtr;

    LOG_TRACE ( logger, "START : GET6_validateT4OTransferRH_impl" );

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

	// Clear the existing error stack
    istatus = EMH_clear_errors();

    // Loop through each target objects
    for ( int inx = 0; inx < p_vAttachments[EPM_target_attachment].size(); inx++ )
    {
        // Validate if MCN Revision is found in target object
        if (! GET_POM_object::isDescendant ( p_vAttachments[EPM_target_attachment][inx], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getTargetShrPtr ( move ( GET_ItemRevision::getInstance ( p_vAttachments[EPM_target_attachment][inx] ) ) );
        LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getTargetShrPtr->getType() );

        // Call function to validate BOP structure
        getLinkedPPPObjects ( getTargetShrPtr, isProductLinked, isDeptFound, sConsolidatedErrorMessage,
                linkedProductRevShrPtr, linkedProcessRevShrPtr, linkedDepartmentRevShrPtr );

        if ( ! ( isDeptFound && isProductLinked ) )
        {
            // Throw the error to the calling method (Where it will be handled)
            THROW ( sConsolidatedErrorMessage );
        }
        else
        {
            sConsolidatedErrorMessage = EMPTY_STRING_VALUE;

            // To get Owning project of MCN
            string sMCNSelectedOrg = getTargetShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );

            // Validate if Solution Folder contain MBOM object only or BOP only or both
            // Get all objects from Solution folder
            vector <GET_POM_objectUnqPtr> vSolItemsUnqPtr = getTargetShrPtr->getPropTags ( CM_HAS_SLITEMS_PROP );

            // Loop through each objects in Solution Item folder
            for ( size_t iSolIndex = 0; iSolIndex < vSolItemsUnqPtr.size(); iSolIndex++ )
            {
                GET_ItemRevisionShrPtr p_getItemRevShrPtr ( move ( GET_ItemRevision::getInstance ( vSolItemsUnqPtr[iSolIndex]->getTag() ) ) );
                if ( p_getItemRevShrPtr->getId() == linkedProductRevShrPtr->getId() )
                {
                    bProdExistInSoFol = true;
                }

                // Check if the Solution object is of type MBOM or EBOM
                if ( ( bMBOMExist == false ) && ( std::find ( vMBOMObjRevPrefValues.begin(), vMBOMObjRevPrefValues.end(),
                        p_getItemRevShrPtr->getType() ) != vMBOMObjRevPrefValues.end() ) )
                {
                    bMBOMExist = true;
                }
                else if ( ( bBOPExist == false ) && ( std::find ( vBOPObjRevPrefValues.begin(), vBOPObjRevPrefValues.end(),
                        p_getItemRevShrPtr->getType() ) != vBOPObjRevPrefValues.end() ) )
                {
                    bBOPExist = true;
                }
            }

            if ( bMBOMExist == true && bBOPExist == true )
            {
                // MBOM and BOP, both objects exist in Solution Folder
                // Check if linked Prod exist in Solution Folder (is part of same MCN Process)
                if ( bProdExistInSoFol == false )
                {
                    string sErr = "Linked Product (" + linkedProductRevShrPtr->getId() + ") does not exist in Solution Folder...";
                    LOG_TRACE ( logger, sErr );
                    sConsolidatedErrorMessage.append ( sErr );
                    sConsolidatedErrorMessage.append ("\n");
                }
                else
                {
                    LOG_TRACE ( logger, "Linked Product exist in Solution Folder..." );
                }
            }
            else if ( bMBOMExist == false && bBOPExist == true )
            {
                // Only BOP objects exist in Solution Folder
                // Check if linked Prod is Released and already Transferred to Oracle
                vector<string> vReleaseStatusList = linkedProductRevShrPtr->getReleaseStatusList();

                if ( vReleaseStatusList.size() > 0 )
                {
                    // Get the Form which is associated to the Object for corresponding MCN Org
                    GET_FormShrPtr sameOrgFormShrPtr = getSameOrgForm ( linkedProductRevShrPtr, sMCNSelectedOrg );

                    if ( ( sameOrgFormShrPtr != NULL )  &&  ( sameOrgFormShrPtr.get() != NULL ) )
                    {
                        // Get the Item Publish Date
                        GET_DateShrPtr getItemPublishDateShrPtr ( move ( sameOrgFormShrPtr->getPropDate ( ITEM_PUBLISH_DATE_PROP ) ) );

                        if ( getItemPublishDateShrPtr->toString() == "" )
                        {
                            string sErr = "Linked Product (" + linkedProductRevShrPtr->getId() + ") is not transferred to Oracle...";
                            LOG_TRACE ( logger, sErr );
                            sConsolidatedErrorMessage.append ( sErr );
                            sConsolidatedErrorMessage.append ("\n");
                        }
                        else
                        {
                            LOG_TRACE ( logger, "Linked Product is Released and also transferred to Oracle..." );
                        }
                    }
                    else
                    {
                        string sErr = "Mfg Attr Form for Linked Product (" + linkedProductRevShrPtr->getId() + ") is not found...";
                        LOG_TRACE ( logger, sErr );
                        sConsolidatedErrorMessage.append ( sErr );
                        sConsolidatedErrorMessage.append ("\n");
                    }
                }
                else
                {
                    string sErr = "Linked Product (" + linkedProductRevShrPtr->getId() + ") is not Released...";
                    LOG_TRACE ( logger, sErr );
                    sConsolidatedErrorMessage.append ( sErr );
                    sConsolidatedErrorMessage.append ("\n");
                }
            }

            LOG_TRACE ( logger, "sConsolidatedErrorMessage.size() is..." + sConsolidatedErrorMessage.size() );

            if ( sConsolidatedErrorMessage.size() > 0 )
            {
                // Throw the error to the calling method (Where it will be handled)
                THROW ( sConsolidatedErrorMessage );
            }
        }

        // Break the loop as MCN Revision has found
        break;
	}

    LOG_TRACE ( logger, "END : GET6_validateT4OTransferRH_impl" );	
}
