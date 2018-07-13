
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_MFG_ActionHandlers.cxx
//
//    Purpose:   Source File defining the Manufacturing Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     17 May, 2017         Making GET6_AssignReleaseStatusAH_impl function generic
//  TCS Development Team     18 May, 2017         Adding GET6_AttachMfgAttrFormsToTarget action handler
//  TCS Development Team     20 Jul, 2017         Fix for no other validation needed for item having UOM as RF
//  TCS Development Team     08 Aug, 2017         Removed the line which assign owning project to MCN.
//  TCS Development Team     27 Sep, 2017         Restructured the file and code to meet best coding standard
//  TCS Development Team     27 Sep, 2017         Added GET6_routeMBOMBOPAH action handler implementation
//  TCS Development Team     27 Sep, 2017         Added GET6_resetMfgAttrOracleXferPropValueAH action handler implementation
//  TCS Development Team     27 Sep, 2017         Removed GET6_traverseBOMAH handler implementation
//  TCS Development Team     18 Oct, 2017         Added assignEffectivity function
//  TCS Development Team     25 May, 2018         Added code to reset Oracle Xfer Prop as True in case of SM Update
//  TCS Development Team     20 Jun, 2018         Added Handler Registration for Multi Org
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_HandlerImpl.hxx>
#include <GET_MFG_ActionHandlers.hxx>
#include <GET_ReleaseStatus.hxx>
#include <GET_BOMViewRevision.hxx>
#include <GET_CheckMCN_AH_Impl.hxx>
#include <GET_EPMJob.hxx>
#include <GET_Item.hxx>

//Global Variable Declaration
string sMCNSelectedOrg;

using namespace get;

// Private Function Prototypes

static void GET6_CheckMCN_AH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
static void GET_Derive_Change_Object_AH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
int deriveChangeObject ( string, GET_POM_objectShrPtr, vector<string>, map<int, vector<tag_t>>, map<string, string> );
static void GET6_AssignReleaseStatusAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>& );
void addReleaseStatusToObjects (GET_ItemRevisionShrPtr, const string );
void GET6_addObjectsToTargetAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
void GET6_setStructureCodeAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
void checkAdditionalStructureCode ( GET_ItemRevisionShrPtr, GET_FormShrPtr );
bool isFormInTarget ( GET_FormShrPtr );
void GET6_attachedrelatedobjectsAH_impl(const tag_t, map<int, vector<tag_t> >&, map<string, string>&);
static void GET6_AttachMfgAttrFormsToTargetAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>& );
static void GET6_resetMfgAttrOracleXferPropValueAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>& );
static void GET6_UpdateStockMaterialMfgFrmAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
static void GET6_routeMBOMBOPAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
void assignEffectivity ( GET_ReleaseStatusShrPtr, string, string );
static void GET6_populateMultiOrgListAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>& );
static void GET6_readMultiOrgListAH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>& );

const string logger = "get.handler.GET_MFG_ActionHandlers";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_CheckMCNAH()
//
//    Purpose:   Action Handler to validate the MCN
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_CheckMCNAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_CheckMCNAH(EPM_action_message_t p_tMsg) {

    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GET6_CheckMCNAH");

    try {

        GET_processHandler(p_tMsg, GET6_CheckMCN_AH_impl);
    } catch(const IFail &ex) {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    } catch(GET_Exception *ex) {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    } catch(...) {
		istatus = GET_general_exception;
        string sMessage = "GET6_CheckMCNAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_CheckMCNAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_CheckMCN_AH_impl()
//
//    Purpose:   Action Handler Implementation to validate the MCN
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_CheckMCN_AH_impl(const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& p_vArguments) {

    LOG_TRACE(logger, "Entering...GET6_CheckMCN_AH_impl");
    GET_CheckMCN_AH_Impl*  GET_CheckMCN_AHObj = new GET_CheckMCN_AH_Impl(p_tTaskTag, p_vAttachments, p_vArguments);
    GET_CheckMCN_AHObj->validateMCN();
    LOG_TRACE (logger, "Exiting...GET6_CheckMCN_AH_impl");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_addObjectsToTargetAH()
//
//    Purpose:   Method that calls implementation method
//
//    Inputs:    p_tMsg - EPM Action message
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     28 Dec, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_addObjectsToTargetAH ( EPM_action_message_t p_tMsg )
{
    int istatus = ITK_ok;
    
    LOG_TRACE ( logger, "START: GET6_addObjectsToTargetAH method" );

    try
    {
        GET_processHandler( p_tMsg, GET6_addObjectsToTargetAH_impl );//needs to be modified/implemented
    }
    catch ( const IFail &ex )
    {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        istatus = GET_general_exception;
        string sMessage = "GET6_addObjectsToTargetAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }
    
    LOG_TRACE ( logger, "END : GET6_addObjectsToTargetAH method" );
    
    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_addObjectsToTargetAH_impl()
//
//    Purpose:   Action Handler Implementation to get objects from folders and copy to target
//
//    Inputs:    tTaskTag - Tag of EPM Task
//               vAttachments - list of attachments from EPM Task
//               mArgumentsMap - list of handler arguments
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     28 Dec, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_addObjectsToTargetAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
    int istatus = 0;

    string strInputObjType = "";

    LOG_TRACE ( logger, "START : GET6_addObjectsToTargetAH_impl method" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( TYPE_ARG ) == mArgumentsMap.end ()|| mArgumentsMap[TYPE_ARG].empty () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( TYPE_ARG )
                + "\"  is missing or is empty";
        THROW( sMsg );
    }
    strInputObjType = mArgumentsMap [ TYPE_ARG ];
    LOG_TRACE ( logger, "Argument type : " + strInputObjType );

    GET_EPMTaskUnqPtr getEPMTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );
    vector<GET_POM_objectUnqPtr>  vReferenceObjUnqPtr = getEPMTaskUnqPtr->askAttachments ( EPM_reference_attachment );
    LOG_TRACE ( logger, "List of objects attached under References =>" + vReferenceObjUnqPtr.size() );

    for ( size_t iRefObjs=0; iRefObjs < vReferenceObjUnqPtr.size(); iRefObjs++ )
    {
        // Get the list of POM objects from Ref Folder
        if ( vReferenceObjUnqPtr [ iRefObjs ]->getPropertyString ( OBJECT_TYPE_ATTR ).compare ( FOLDERTYPE ) == 0 )
        {
            string foldername = vReferenceObjUnqPtr[ iRefObjs ]->getPropertyString ( OBJECT_NAME_ATTR );
            LOG_TRACE ( logger, "Name of the folder => " + foldername );

            if ( foldername.compare ( strInputObjType ) == 0 )
            {
                vector<GET_POM_objectShrPtr> vFolderObjectShrPtr;
                vector<GET_POM_objectUnqPtr> vFolderContents = vReferenceObjUnqPtr[ iRefObjs ]->getPropertyTags ( CONTENTS );

                for( size_t jnx=0; jnx< vFolderContents.size(); jnx++ )
                {
                    GET_POM_objectShrPtr getPOMShrPtr ( move (  vFolderContents [jnx] ) );

                    vFolderObjectShrPtr.push_back( getPOMShrPtr );
                }

                getEPMTaskUnqPtr->addAttachments ( EPM_target_attachment, vFolderObjectShrPtr );

                // Since input folder type found, break the loop
                break;
            }
        }
    }
    vReferenceObjUnqPtr.clear();

    LOG_TRACE ( logger, "END : GET6_addObjectsToTargetAH_impl method" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_resetMfgAttrOracleXferPropValueAH()
//
//    Purpose:   Action Handler to reset the Oracle transfer flag of Mfg Attribute Forms
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_resetMfgAttrOracleXferPropValueAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      29 Aug, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_resetMfgAttrOracleXferPropValueAH(EPM_action_message_t p_tMsg) {

    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GET6_resetMfgAttrOracleXferPropValueAH");

    try {

        GET_processHandler(p_tMsg, GET6_resetMfgAttrOracleXferPropValueAH_impl);
    } catch(const IFail &ex) {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    } catch(GET_Exception *ex) {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    } catch(...) {
        istatus = GET_general_exception;
        string sMessage = "GET6_resetMfgAttrOracleXferPropValueAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_resetMfgAttrOracleXferPropValueAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_resetMfgAttrOracleXferPropValueAH_impl()
//
//    Purpose:   Action Handler Implementation to Reset Mfg Attribute Forms Modified flag
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      29 Aug, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_resetMfgAttrOracleXferPropValueAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
    LOG_TRACE(logger, "Entering...GET6_resetMfgAttrOracleXferPropValueAH_impl");

    GET_CheckMCN_AH_Impl*  GET_CheckMCN_AHObj = new GET_CheckMCN_AH_Impl ( tTaskTag, vAttachments, mArgumentsMap );
    GET_CheckMCN_AHObj->resetMfgAttrOracleXferPropValue();

    LOG_TRACE (logger, "Exiting...GET6_resetMfgAttrOracleXferPropValueAH_impl");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_AssignReleaseStatusAH()
//
//    Purpose:   Action Handler to assign correct release status to MCN Objects
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_AssignReleaseStatusAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      17 Jun, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_AssignReleaseStatusAH(EPM_action_message_t p_tMsg)
{
    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GET6_AssignReleaseStatusAH");

    try
    {
        GET_processHandler(p_tMsg, GET6_AssignReleaseStatusAH_impl);
    }
    catch(const IFail &ex)
    {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch(GET_Exception *ex)
    {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch(...)
    {
        istatus = GET_general_exception;
        string sMessage = "GET6_AssignReleaseStatusAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_AssignReleaseStatusAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_AssignReleaseStatusAH_impl()
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
//  TCS Development Team      17 Jun, 2016         Initial creation
//  TCS Development Team      17 May, 2017         Making this function generic for Org based status as well as for Default Release status
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_AssignReleaseStatusAH_impl(const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& p_vArguments)
{
    string sEffDecision         = EMPTY_STRING_VALUE;
    string strOwningProject     = EMPTY_STRING_VALUE;
    string strInputObjType      = EMPTY_STRING_VALUE;
    string strReleaseStatusName = EMPTY_STRING_VALUE;

    LOG_TRACE(logger, "Entering...GET6_AssignReleaseStatusAH_impl");

    // Loop through each target objects
    for ( size_t iTargetObj=0; iTargetObj<p_vAttachments[EPM_target_attachment].size(); iTargetObj++ )
    {
        // Validate if MCN Revision is found in target object
        if ( ! GET_POM_object::isDescendant ( p_vAttachments[EPM_target_attachment][iTargetObj], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( GET_ItemRevision::getInstance( p_vAttachments[EPM_target_attachment][iTargetObj] )));
        LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getItemRevShrPtr->getType() );

        sEffDecision = getItemRevShrPtr->getPropString ( EFF_DECISION_PROP );

        // Check the effectivity decision made on MCN Rev object, if Yes then construct Org based release status string
        if ( sEffDecision.compare ( MCN_LOV_TRUE_VALUE ) == 0 )
        {
            strOwningProject = getItemRevShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
            LOG_TRACE(logger, "strOwningProject-->" + strOwningProject);

            strReleaseStatusName = string ( GET6_PREFIX_VALUE ) + strOwningProject + string ( RELEASED_SUFFIX_VALUE );
            LOG_TRACE(logger, "strReleaseStatusName-->" + strReleaseStatusName);
        }
        else if ( p_vArguments.find ( RELEASE_STATUS_LIST_ARG ) != p_vArguments.end() )
        {
            // In case of Prelim workflow we are passing GET6Preliminary release status from handler argument
            strReleaseStatusName = p_vArguments[RELEASE_STATUS_LIST_ARG];
        }
        else
        {
            strReleaseStatusName = GET6_RELEASED_VALUE;
        }

        // Apply the Release status to all objects added in Solution Item Folder
        addReleaseStatusToObjects ( getItemRevShrPtr, strReleaseStatusName );

        // Break the loop as MCN Revision has found
        break;
    }

    LOG_TRACE (logger, "Exiting...GET6_AssignReleaseStatusAH_impl");
}

void addReleaseStatusToObjects ( GET_ItemRevisionShrPtr getItemRevShrPtr, const string strReleaseStatusName )
{
    vector<string>                      vBOPObjRevPrefValues;
    vector<string>                      vMBOMObjRevPrefValues;
    vector<GET_WorkspaceObjectShrPtr>   vMBOMReleaseStatusObjects;
    vector<GET_WorkspaceObjectShrPtr>   vBOPReleaseStatusObjects;

    LOG_TRACE(logger, "Entering...addReleaseStatusToObjects");

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
    vector<GET_POM_objectUnqPtr> vSolItemsUnqPtr = getItemRevShrPtr->getPropTags ( CM_HAS_SLITEMS_PROP );

    // Loop through each objects in Solution Item folder
    for ( size_t iSolIndex = 0; iSolIndex < vSolItemsUnqPtr.size(); iSolIndex++ )
    {
        GET_WorkspaceObjectShrPtr getWorkspaceShrPtr (move ( GET_WorkspaceObject::getInstance ( vSolItemsUnqPtr[iSolIndex]->getTag() ) ) );

        // Check if Release Status workflow argument value is "GET6Released" and
        // Solution folder object is already Released with GET6Released status
        // If yes, then skip this object as there cannot be two GET6Released status on same object
        if ( strReleaseStatusName.compare ( GET6RELEASED ) == 0 )
        {
            if ( getWorkspaceShrPtr->isReleased() && getWorkspaceShrPtr->hasReleaseStatus ( GET6RELEASED ) )
            {
                continue;
            }
        }

        // Check if the Solution object is of type MBOM or EBOM, if yes then add to MBOM vector
        if ( std::find ( vMBOMObjRevPrefValues.begin(), vMBOMObjRevPrefValues.end(), getWorkspaceShrPtr->getType() ) != vMBOMObjRevPrefValues.end() )
        {
            // Add the found object to the vector of objects to be assign given status
            vMBOMReleaseStatusObjects.push_back ( getWorkspaceShrPtr );

            // Get the BVR object
            map<string, GET_BOMViewRevisionShrPtr> mpBVRObjects = GET_ItemRevision::getInstance ( vSolItemsUnqPtr[iSolIndex]->getTag() )->getBVRs();

            map<string, GET_BOMViewRevisionShrPtr>::iterator mapBVRIterator;
            for ( mapBVRIterator = mpBVRObjects.begin(); mapBVRIterator != mpBVRObjects.end(); mapBVRIterator++ )
            {
                GET_WorkspaceObjectShrPtr getWorkspaceBVRShrPtr ( move ( GET_WorkspaceObject::getInstance ( mapBVRIterator->second->getTag() ) ) );
                vMBOMReleaseStatusObjects.push_back ( getWorkspaceBVRShrPtr );
            }
        }
        // Check if the Solution object is of type BOP, if yes then add to BOP vector
        if ( std::find ( vBOPObjRevPrefValues.begin(), vBOPObjRevPrefValues.end(), getWorkspaceShrPtr->getType() ) != vBOPObjRevPrefValues.end() )
        {
            // Add the found object to the vector of objects to be assign given status
            vBOPReleaseStatusObjects.push_back ( getWorkspaceShrPtr );

            // Get the BVR object
            map<string, GET_BOMViewRevisionShrPtr> mpBVRObjects = GET_ItemRevision::getInstance ( vSolItemsUnqPtr[iSolIndex]->getTag() )->getBVRs();

            map<string, GET_BOMViewRevisionShrPtr>::iterator mapBVRIterator;
            for ( mapBVRIterator = mpBVRObjects.begin(); mapBVRIterator != mpBVRObjects.end(); mapBVRIterator++ )
            {
                GET_WorkspaceObjectShrPtr getWorkspaceBVRShrPtr ( move ( GET_WorkspaceObject::getInstance ( mapBVRIterator->second->getTag() ) ) );
                vBOPReleaseStatusObjects.push_back ( getWorkspaceBVRShrPtr );
            }
        }
    }

    // Add Release status to MBOM objects found
    if ( vMBOMReleaseStatusObjects.size() > 0 )
    {
        string sMBOMEffStartDate = getItemRevShrPtr->getPropertyDate ( MBOM_EFF_START_DATE_PROP )->toString();
        string sMBOMEffEndDate   = getItemRevShrPtr->getPropertyDate ( MBOM_EFF_END_DATE_PROP )->toString();

        // Create the status for given status name
        GET_ReleaseStatusUnqPtr getMBOMReleaseStatusUnqPtr = GET_ReleaseStatus::createStatus ( strReleaseStatusName );
        GET_ReleaseStatusShrPtr getMBOMReleaseStatusShrPtr( move ( getMBOMReleaseStatusUnqPtr ) );
        // Apply Release status to MBOM objects
        getMBOMReleaseStatusShrPtr->addStatus ( vMBOMReleaseStatusObjects, false );

        //Assigneffectivity on project based status.
        if ( strReleaseStatusName.compare ( GET6RELEASED ) != 0 )
        {
        	assignEffectivity ( getMBOMReleaseStatusShrPtr, sMBOMEffStartDate, sMBOMEffEndDate );
        }
    }

    // Add Release status to BOP objects found
    if ( vBOPReleaseStatusObjects.size() > 0 )
    {
        string sBOPEffStartDate  = getItemRevShrPtr->getPropertyDate ( BOP_EFF_START_DATE_PROP )->toString();
        string sBOPEffEndDate    = getItemRevShrPtr->getPropertyDate ( BOP_EFF_END_DATE_PROP )->toString();

        // Create the status for given status name
        GET_ReleaseStatusUnqPtr getBOPReleaseStatusUnqPtr = GET_ReleaseStatus::createStatus ( strReleaseStatusName );
        GET_ReleaseStatusShrPtr getBOPReleaseStatusShrPtr( move ( getBOPReleaseStatusUnqPtr ) );
        // Apply Release status to BOP objects
        getBOPReleaseStatusShrPtr->addStatus ( vBOPReleaseStatusObjects, false );

        //Assigneffectivity on project based status.
        if ( strReleaseStatusName.compare ( GET6RELEASED ) != 0 )
        {
        	assignEffectivity ( getBOPReleaseStatusShrPtr, sBOPEffStartDate, sBOPEffEndDate );
        }

    }

    LOG_TRACE (logger, "Exiting...addReleaseStatusToObjects");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   assignEffectivity()
//
//    Purpose:   To assign effectivity to BOP and MBOM
//
//    Inputs:    GET_ReleaseStatusShrPtr, string, string
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     18 Oct, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void assignEffectivity ( GET_ReleaseStatusShrPtr releaseStatusShrPtr, string sEffStartDate, string sEffEndDate )
{
	string sRangeDate = "";
	logical lAns = 0;

	if ( releaseStatusShrPtr->getTag() != NULLTAG )
	{
		if ( sEffEndDate.empty() )
		{
			sRangeDate = sEffStartDate + " to UP";
		}
		else
		{
			sRangeDate = sEffStartDate + " to " + sEffEndDate;
		}

		string sClassName = releaseStatusShrPtr->getClassName();
		lAns = releaseStatusShrPtr->isLoaded();

		if ( lAns == 1 )
		{
			GET_POM_objectUnqPtr pomObjUnqPtr = releaseStatusShrPtr->setEffectivity ( sRangeDate );
		}
	}
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GETDeriveChangeObjectAH()
//
//    Purpose:   Action Handler to Derive Change Objects
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GETDerviceChangeObjectAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GETDeriveChangeObjectAH(EPM_action_message_t p_tMsg) {

    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GETDerviceChangeObjectAH");

    try {

        GET_processHandler(p_tMsg, GET_Derive_Change_Object_AH_impl);
    } catch(const IFail &ex) {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    } catch(GET_Exception *ex) {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    } catch(...) {
		istatus = GET_general_exception;
        string sMessage = "GETAssignReleaseStatusAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GETDeriveChangeObjectAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET_Derive_Change_Object_AH_impl()
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
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     20 Jun, 2018         Updated for Multi Org 
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET_Derive_Change_Object_AH_impl ( const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& p_vArguments )
{
	int istatus = ITK_ok;

	string strNamingPattern = EMPTY_STRING_VALUE;
	vector<string> vMCNOrgID;
	vector<string> vItemID;

	GET_POM_objectShrPtr getProjectObjShrPtr;

	LOG_TRACE(logger, "Entering...GET_Derive_Change_Object_AH_impl");

	try
	{
		GET_ItemRevisionUnqPtr targetRevisionUnqPtr;
		if ( ( p_vArguments.find ( SOURCE_HANDLER_ARG ) == p_vArguments.end()) || ( p_vArguments[SOURCE_HANDLER_ARG].empty() ) )
		{
			THROW ( "Missing Argument --> " + string ( SOURCE_HANDLER_ARG ) );
		}
		else if ( ( p_vArguments.find ( TARGET_HANDLER_ARG ) == p_vArguments.end() ) || ( p_vArguments[TARGET_HANDLER_ARG].empty() ) )
		{
			THROW ( "Missing Argument --> " + string ( TARGET_HANDLER_ARG ) );
		}

		if ( p_vArguments[TARGET_HANDLER_ARG] == GET_MCN_BO )
		{
			getStringPrefValues ( CM_MCN_ORG_PROJ_PREF, vMCNOrgID, TC_preference_site );

			for ( int inx = 0; inx < vMCNOrgID.size(); inx++ )
			{
				GET_TC_ProjectUnqPtr projUnqPtr = GET_TC_Project::find ( vMCNOrgID[inx] );

				GET_POM_objectShrPtr getProjectObjShrPtr ( move ( GET_POM_object::getInstance ( projUnqPtr->getTag() ) ) );

				strNamingPattern = string ( NAMING_PATTERN_PREFIX ) + vMCNOrgID[inx] + string ( NAMING_PATTERN_SUFFIX );

				istatus = deriveChangeObject ( strNamingPattern, getProjectObjShrPtr, vItemID, p_vAttachments, p_vArguments );
			}
		}
		else
		{
			istatus = deriveChangeObject ( strNamingPattern, getProjectObjShrPtr, vItemID, p_vAttachments, p_vArguments );
		}
	}
	catch ( const IFail &ex )
	{
		istatus = ex.ifail();
		LOG_ERROR ( logger, ex.getMessage() );
		EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
	}
	catch ( GET_Exception *ex )
	{
		istatus = GET_general_exception;
		LOG_ERROR ( logger, ex->getErrorMessage() );
		EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
		delete ex;
	}
	catch ( ... )
	{
		istatus = GET_general_exception;
		string sMessage = "GET_Derive_Change_Object_AH_impl failed due to an unexpected error. Please Contact your system administrator";
		LOG_ERROR ( logger, sMessage );
		EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
	}

	LOG_TRACE(logger, "Exiting...GET_Derive_Change_Object_AH_impl");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   deriveChangeObject()
//
//    Purpose:   Action Handler Implementation to deriveChangeObject
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     20 Jun, 2018         Updated for Multi Org 
//
===========================================================================
//ENDFUNCDOC   ***/
int deriveChangeObject ( string p_pszNamingPattern, GET_POM_objectShrPtr p_getProjectPtr, vector<string> vItemID, map<int, vector<tag_t>> p_vAttachments, map<string, string> p_vArguments )
{
	int iFail = ITK_ok;
	string sItemID = EMPTY_STRING_VALUE;
	string strDerivePref = EMPTY_STRING_VALUE;
	vector<string> vPropagateProperties;

	GET_POM_objectShrPtr getUserDataPtr;

	for ( int inx = 0; inx < p_vAttachments[EPM_target_attachment].size(); inx++ )
	{
		// Validate if ECN Revision is found in target object
		if ( ! GET_POM_object::isDescendant ( p_vAttachments[EPM_target_attachment][inx], ECNREVISION_TYPE ) )
		{
			continue;
		}
		GET_ItemRevisionShrPtr getSourceItemRevShrPtr ( move ( GET_ItemRevision::getInstance ( p_vAttachments[EPM_target_attachment][inx] ) ) );

		if ( getSourceItemRevShrPtr->getType() == string ( p_vArguments[SOURCE_HANDLER_ARG] + string ( REVISION_KEYWORD_VALUE ) ) )
		{
			sItemID = GET_Item::getNRPatternNextValue ( p_vArguments[TARGET_HANDLER_ARG].c_str(), ITEM_ID_ATTR, NULLTAG, EMPTY_STRING_VALUE, EMPTY_STRING_VALUE, EMPTY_STRING_VALUE, NULLTAG, EMPTY_STRING_VALUE, EMPTY_STRING_VALUE, p_pszNamingPattern );

			if ( ! sItemID.empty() )
			{
				GET_ItemShrPtr getTargetObjectShrPtr ( move ( GET_Item::create ( p_vArguments[TARGET_HANDLER_ARG], string ( sItemID ), getSourceItemRevShrPtr->getName(), INTIAL_REV_ID_VALUE, getSourceItemRevShrPtr->getDesc() ) ) );

				if ( getTargetObjectShrPtr.get() )
				{
					GET_ItemRevisionShrPtr getTargetObjectRevisionShr ( move ( getTargetObjectShrPtr->getLatestRevision() ) );

				    strDerivePref = string ( CM_DERIVE_CHANGE_PREF ) + p_vArguments[SOURCE_HANDLER_ARG] + string ( CM_DERIVE_CHANGE_SUFF );

					getStringPrefValues ( strDerivePref, vPropagateProperties, TC_preference_site );

					for ( int jnx = 0; jnx < vPropagateProperties.size(); jnx++ )
					{
						PROP_type_t propTypeObj = getTargetObjectRevisionShr->askPropertyType ( vPropagateProperties[jnx] );

						switch ( propTypeObj )
						{
							case PROP_attribute:
							{
								PROP_value_type_e propValueTypeObj = getSourceItemRevShrPtr->askPropValueType ( vPropagateProperties[jnx] );

								switch ( propValueTypeObj )
								{
									case PROP_int:
									{
										getTargetObjectRevisionShr->setProp ( vPropagateProperties[jnx], getSourceItemRevShrPtr->getPropInteger ( vPropagateProperties[jnx] ) );
										break;
									}
									case PROP_string:
									{
										getTargetObjectRevisionShr->setProp ( vPropagateProperties[jnx], getSourceItemRevShrPtr->getPropString ( vPropagateProperties[jnx] ) );
										break;
									}
									default:
									{
										THROW ( "Unknown Property Type Found, Please update Implementation Method --> " + vPropagateProperties[jnx] );
										break;
									}
								}
								break;
							}
							case PROP_relation:
							{
								vector<GET_POM_objectUnqPtr> vPomObjectUnqPtr = getSourceItemRevShrPtr->getPropTags ( vPropagateProperties[jnx] );

								GET_POM_objectShrPtr getMCNPOMShrPtr ( move ( GET_POM_object::getInstance ( getTargetObjectRevisionShr->getTag() ) ) );

								for ( int knx = 0; knx < vPomObjectUnqPtr.size(); knx++ )
								{
									if ( ( vPomObjectUnqPtr[knx]->askTypeName().compare ( ELECREV_TYPE ) != 0 ) && ( vPomObjectUnqPtr[knx]->askTypeName().compare ( MECHREV_TYPE ) != 0 ) )
									{
										GET_POM_objectShrPtr getPomObjectShrPtr ( move ( vPomObjectUnqPtr[knx] ) );
										GET_ImanRelation::create ( getMCNPOMShrPtr, getPomObjectShrPtr, CMREFERENCES, getUserDataPtr );
									}
									else
									{
										// Copy only the selected Items to respective MCN's Solution Folder
										if ( vPropagateProperties[jnx].compare ( CM_HAS_SOLUTION_ITEMS_PROP ) == 0 )
										{
											GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( GET_ItemRevision::getInstance ( vPomObjectUnqPtr[knx]->getTag() ) ) );

											string sItemID = getItemRevShrPtr->getItem()->getId();

											if ( std::find ( vItemID.begin(), vItemID.end(), sItemID ) != vItemID.end() )
											{
												GET_POM_objectShrPtr getPomObjectShrPtr ( move ( vPomObjectUnqPtr[knx] ) );
												GET_ImanRelation::create ( getMCNPOMShrPtr, getPomObjectShrPtr, vPropagateProperties[jnx], getUserDataPtr );
											}
										}
									}
								}
								break;
							}
							default:
							{
								THROW ( "Unknown Property Type Found, Please update Implementation Method --> " + vPropagateProperties[jnx] );
								break;
							}
						}
					}

					GET_POM_objectShrPtr getSourcePomObjShr ( move ( GET_POM_object::getInstance ( getSourceItemRevShrPtr->getTag() ) ) );
					GET_POM_objectShrPtr getTargetPomObjShrPtr ( move ( GET_POM_object::getInstance ( getTargetObjectRevisionShr->getTag() ) ) );

					GET_TC_ProjectUnqPtr tcProjUnqPtr = GET_TC_Project::getInstance ( p_getProjectPtr->getTag() );

					vector<GET_TC_ProjectShrPtr> vProjShrPtrs;
					vector<GET_WorkspaceObjectShrPtr> vMCNShrPtrs;

					GET_WorkspaceObjectUnqPtr mcnUnqPtr = GET_WorkspaceObject::getInstance ( getTargetObjectRevisionShr->getItem()->getTag() );
					GET_WorkspaceObjectShrPtr mcnShrPtr ( move ( mcnUnqPtr ) );
					vMCNShrPtrs.push_back( mcnShrPtr );

					GET_TC_ProjectShrPtr tcProjShrPtr ( move ( tcProjUnqPtr ) );

					//Setting owning project
					mcnShrPtr->setProp ( "owning_project", p_getProjectPtr );

					vProjShrPtrs.push_back ( tcProjShrPtr );

					//Assign project and project ids
					GET_TC_Project::assignProjectToItem ( vProjShrPtrs, vMCNShrPtrs );

					//Creation relation between ECN Rev and MCN Rev
					GET_ImanRelation::create ( getTargetPomObjShrPtr, getSourcePomObjShr, CM_IMPLEMENTS_PROP, getUserDataPtr );

					//Initiate MCN Workflow.
					if ( p_getProjectPtr.get() )
					{
						vector<GET_POM_objectShrPtr> vTargetObjShrPtr;
						vTargetObjShrPtr.push_back ( getTargetObjectRevisionShr );
						GET_EPMJobUnqPtr epmJobUnqPtr = GET_EPMJob::createEPMProcess ( GET_MCN_PROCESS_WF, getTargetObjectRevisionShr->getPropString( OBJECT_STRING_ATTR ), getTargetObjectRevisionShr->getDesc().c_str(), vTargetObjShrPtr, EPM_target_attachment );
					}
				}
			}
			break;
		}
	}
	return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_setStructureCodeAH()
//
//    Purpose:   Method that calls implementation method
//
//    Inputs:    p_tMsg - EPM Action message
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     27 Apr, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_setStructureCodeAH ( EPM_action_message_t p_tMsg )
{
    int istatus = ITK_ok;

    LOG_TRACE ( logger, "START: GET6_setStructureCodeAH method" );

    try
    {
        GET_processHandler( p_tMsg, GET6_setStructureCodeAH_impl );
    }
    catch ( const IFail &ex )
    {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch ( GET_Exception *ex )
    {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch ( ... )
    {
        istatus = GET_general_exception;
        string sMessage = "GET6_setStructureCodeAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET6_setStructureCodeAH method" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_setStructureCodeAH_impl()
//
//    Purpose:   Action Handler Implementation to set structure code on GET6MfgAttrForm based on certain conditions
//
//    Inputs:    tTaskTag - Tag of EPM Task
//				 vAttachments - list of attachments from EPM Task
//				 mArgumentsMap - list of handler arguments
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     27 Mar, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_setStructureCodeAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
    int iStatus = 0;
    string sMCNID = "";
    vector<tag_t>vProcessedItems;

    LOG_TRACE ( logger, "START : GET6_setStructureCodeAH_impl method" );

    vector<string> vValidMCNObjects;
    vector<GET_ItemRevisionShrPtr> vTargetItemRevs;

    getStringPrefValues ( CM_VALID_MCN_OBJECTS, vValidMCNObjects );

    for ( int iInx = 0; iInx < vAttachments [ EPM_target_attachment ].size(); iInx++ )
    {
        // Validate if item Revision is found in target object
        if ( ! GET_POM_object::isDescendant ( vAttachments[EPM_target_attachment][iInx], ITEMREVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionUnqPtr getItemRevUnqPtr = GET_ItemRevision::getInstance ( vAttachments [ EPM_target_attachment ] [ iInx ] );

        LOG_TRACE ( logger, "getItemRevUnqPtr->getType()--> " + getItemRevUnqPtr->getType() );

        if ( getItemRevUnqPtr->getType() ==  GET_MCN_REVISION_CLASS )
        {
            // To get Owning project of MCN
            sMCNSelectedOrg = getItemRevUnqPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );

            LOG_TRACE ( logger, "sMCNSelectedOrg--> " + sMCNSelectedOrg );

            sMCNID = getItemRevUnqPtr->getItem()->getId();

            LOG_TRACE ( logger, "sMCNID--> " + sMCNID );
        }

        // To get only Engineering revision or Electrical revision or Manufacturing part revision object
        if ( getItemRevUnqPtr->getType().compare ( MECHREV_TYPE ) == 0 || getItemRevUnqPtr->getType().compare ( ELECREV_TYPE ) == 0 || getItemRevUnqPtr->getType().compare ( MFGREV_TYPE ) == 0)
        {
            GET_ItemRevisionShrPtr getSolnItemRevShrPtr ( move ( getItemRevUnqPtr ) );
            vTargetItemRevs.push_back ( getSolnItemRevShrPtr );
        }
    }

    if ( vTargetItemRevs.size() > 0 )
    {
        for ( int iInx = 0; iInx < vTargetItemRevs.size(); iInx++ )
        {
            string sUOMValue = EMPTY_STRING_VALUE;

            sUOMValue = vTargetItemRevs[iInx]->getItem()->getPropValueAsString ( UOM_TAG_PROP );

            if ( sUOMValue.compare ( UOM_RF_VALUE ) != 0 )
            {
                if ( GET_isInVector ( vValidMCNObjects, vTargetItemRevs[iInx]->getType() ) )
                {
                    GET_FormShrPtr sameOrgFormShrPtr;

                    LOG_TRACE ( logger, "p_getBOMLineShrPtr-->" + vTargetItemRevs[iInx]->getId() );
                    LOG_TRACE ( logger, "p_getBOMLineShrPtr Revision ID-->" + vTargetItemRevs[iInx]->getRevId() );

                    sameOrgFormShrPtr = getSameOrgForm ( vTargetItemRevs[iInx], sMCNSelectedOrg );

                    if ( ( ! sameOrgFormShrPtr->isReleased() ) || ( ( sameOrgFormShrPtr->isReleased() ) && ( isFormInTarget ( sameOrgFormShrPtr ) ) ) )
                    {
                        // To fetch Make / Buy value of the Item.
                        string sMakeBuy = sameOrgFormShrPtr->getPropValueAsString ( MAKE_BUY_PROP );
                        LOG_TRACE ( logger, "sMakeBuy--> " + sMakeBuy );

                        if ( sMakeBuy.compare ( BUY_VALUE ) == 0 )
                        {
                            sameOrgFormShrPtr->setProp ( STRUCTURE_CODE_PROP, 5, true, true );
                        }
                        else if ( sMakeBuy.compare ( MAKE_VALUE ) == 0 )
                        {
                            bool bIsItemHasAssy = false;

                            // Check if the Target Revision is an assembly or not
                            vector<GET_POM_objectUnqPtr> childObjectsVector = vTargetItemRevs[iInx]->getPropTags ( PSCHILDREN_ATTR );
                            if ( childObjectsVector.size() > 0 )
                            {
                                sameOrgFormShrPtr->setProp ( STRUCTURE_CODE_PROP, 6, true, true );
                                bIsItemHasAssy = true;
                            }
                            if ( ( ( ( vTargetItemRevs[iInx]->getType() ).compare ( MECHREV_TYPE ) == 0 ) || ( ( vTargetItemRevs[iInx]->getType() ).compare ( ELECREV_TYPE ) == 0 ) ) && ( bIsItemHasAssy == false ) )
                            {
                                //To check for additional Structure Code possibilities if item rev is of type GET6MechPartRevision and it doesn't have a BVR.
                                checkAdditionalStructureCode( vTargetItemRevs[iInx], sameOrgFormShrPtr );
                            }
                        }
                    }
                }
            }
        }
    }

    LOG_TRACE ( logger, "END : GET6_setStructureCodeAH_impl method" );
}

void checkAdditionalStructureCode( GET_ItemRevisionShrPtr getParentItemRevShrPtr, GET_FormShrPtr sameOrgFormShrPtr )
{
    bool bValidCondition = false;

    vector<GET_POM_objectUnqPtr> vMadeFromPartItemUnqPtr = getParentItemRevShrPtr->getItem()->getPropTags ( MADE_FROM_PART_PROP );

    LOG_TRACE ( logger, "vMadeFromPartItemUnqPtr.size() --> " + vMadeFromPartItemUnqPtr.size() );

    if( vMadeFromPartItemUnqPtr.size() > 0 )
    {
        sameOrgFormShrPtr->setProp ( STRUCTURE_CODE_PROP, 8, true, true );
        bValidCondition = true;
    }

    if ( !bValidCondition )
    {
        vector<GET_POM_objectUnqPtr> vGetMaterialObject = getParentItemRevShrPtr->getItem()->getPropTags ( MADE_FROM_MATL_PROP );

        LOG_TRACE ( logger, "vGetMaterialObject.size() --> " + vGetMaterialObject.size() );

        if ( vGetMaterialObject.size() > 0 )
        {
            vector<GET_POM_objectUnqPtr> vGetStockMaterialObject = sameOrgFormShrPtr->getPropTags ( STOCK_MATERIAL_PROP );

            if( vGetStockMaterialObject.size() > 0 )
            {
                sameOrgFormShrPtr->setProp ( STRUCTURE_CODE_PROP, 7, true, true );
            }
        }
    }

    LOG_TRACE ( logger, "Exiting setEngStructureCode..." );
}

bool isFormInTarget ( GET_FormShrPtr sameOrgFormShrPtr )
{
    bool isInTarget = false;

    vector<GET_POM_objectUnqPtr> vFormProcessStageListUnqPtr = sameOrgFormShrPtr->getPropTags ( PROCESS_STAGE_LIST_ATTR );

    if ( vFormProcessStageListUnqPtr.size() != 0 )
    {
        isInTarget = true;
    }

   return isInTarget;
}

//To retrieve the form which has the same org as Manufacturing or Engineering Item
GET_FormShrPtr getSameOrgForm( GET_ItemRevisionShrPtr getParentItemRevShrPtr, string sMCNSelectedOrg )
{
    vector<GET_POM_objectUnqPtr> vPOMSecondaryOrgForms;

    GET_FormShrPtr sameOrgFormShrPtr;

    LOG_TRACE ( logger, "Entering getSameOrgForm..." );

    vPOMSecondaryOrgForms = getParentItemRevShrPtr->getItem()->getPropTags ( GET_PART_ORG_ATTR_BO );

    for(int iInx = 0; iInx < vPOMSecondaryOrgForms.size(); iInx++)
	{
        GET_POM_objectShrPtr getPOMObjectShrPtr ( move ( vPOMSecondaryOrgForms[iInx] ) );

        GET_FormUnqPtr getFormUnqPtr = GET_Form::getInstance ( getPOMObjectShrPtr->getTag() );
        GET_FormShrPtr getFormShrPtr ( move ( getFormUnqPtr ) );

        string sOwningProjectID = getFormShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
        
        LOG_TRACE ( logger, "sOwningProjectID --> " + sOwningProjectID );

        if( sMCNSelectedOrg.compare ( sOwningProjectID ) == 0 )
		{
            sameOrgFormShrPtr = getFormShrPtr;
            break;
        }
	}

	LOG_TRACE ( logger, "Exiting getSameOrgForm..." );

	return 	sameOrgFormShrPtr;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_attachedrelatedobjectsAH()
//
//    Purpose:   Action Handler to add that object to target or reference.
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     02 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_attachedrelatedobjectsAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE(logger, "START : GET6_attachedrelatedobjectsAH");

    try
    {
        GET_processHandler( tMessage, GET6_attachedrelatedobjectsAH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_attachedrelatedobjectsAH" );
    }

    LOG_TRACE ( logger, "END : GET6_attachedrelatedobjectsAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_attachedrelatedobjectsAH()
//
//    Purpose:   Action Handler implementation function for GET6_attachedrelatedobjectsAH_impl handler
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
//  TCS Development Team     02 May, 2017         Initial creation
===========================================================================
//ENDFUNCDOC   ***/
void GET6_attachedrelatedobjectsAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{

	LOG_TRACE ( logger, " Start: GET6_attachedrelatedobjectsAH_impl: " );

// Get handler arguments
	if ( mArgumentsMap.find ( SOURCE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[SOURCE_TYPE_ARG].empty() )
	{
		THROW ( string ( "The argument \"" ) + SOURCE_TYPE_ARG + string ( "\" is not provided or has empty value" ) );
	}
	if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[RELATION_TYPE_ARG].empty() )
	{
		THROW ( string ( "The argument \"" ) + RELATION_TYPE_ARG + string ( "\" is not provided or has empty value" ) );
	}
	if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
	{
		THROW ( string ( "The argument \"" ) + INCLUDE_TYPE_ARG + string ( "\" is not provided or has empty value" ) );
	}
	if ( mArgumentsMap.find ( PRIMARY_ARG ) == mArgumentsMap.end() || mArgumentsMap[PRIMARY_ARG].empty() )
	{
		THROW ( string ( "The argument \"" ) + PRIMARY_ARG + string ( "\" is not provided or has empty value. If Yes then Primary and No means Secondary" ) );
	}
	if ( mArgumentsMap.find ( ATTACHMENT_TYPE ) == mArgumentsMap.end() || mArgumentsMap[ATTACHMENT_TYPE].empty() )
	{
		THROW ( string ( "The argument \"" ) + ATTACHMENT_TYPE + string ( "\" is not provided or has empty value" ) );
	}

	vector <tag_t> vTargetAttachments;
	GET_POM_objectUnqPtr itemUnqPtr;
	vector<GET_POM_objectUnqPtr> pomUnqPtr;
	vector<GET_POM_objectShrPtr> vPomObjShrPtr;

	vTargetAttachments = vAttachments[EPM_target_attachment];
	GET_EPMTaskUnqPtr epmTaskPtr = GET_EPMTask::getInstance( tTaskTag );

	for ( size_t index = 0; index < vTargetAttachments.size(); ++index )
	{
		  // Check if the target is an Item or not
		if ( ! GET_POM_object::isDescendant ( vTargetAttachments[index], mArgumentsMap [SOURCE_TYPE_ARG] ) )
		{
			continue;
		}

		itemUnqPtr = GET_POM_object::getInstance ( vTargetAttachments[index] );
		LOG_TRACE(logger, "Type Name is -->" + itemUnqPtr->askTypeName());
		break;
	}

	GET_POM_objectShrPtr itemShrPtr ( move ( itemUnqPtr ) );

	// EPM-check-related object need to configured before using this handler to make
	// sure Primary or secondary object is link with the specified relation.
	// Get primary/secondary objects based on Primary_arg value and relation.
	LOG_TRACE ( logger, "mArgumentsMap[PRIMARY_ARG -->" + mArgumentsMap[PRIMARY_ARG] );
	if ( mArgumentsMap[PRIMARY_ARG].compare( PRIMARY_ARG_YES ) == 0 )
	{
		pomUnqPtr = GET_ImanRelation::listRelatedObjects ( itemShrPtr, mArgumentsMap[RELATION_TYPE_ARG],true );
	}
	else if ( mArgumentsMap[PRIMARY_ARG].compare( PRIMARY_ARG_NO ) == 0 )
	{
		pomUnqPtr = GET_ImanRelation::listRelatedObjects ( itemShrPtr, mArgumentsMap[RELATION_TYPE_ARG],false );
	}

	LOG_TRACE ( logger, "pomUnqPtr size  -->" + pomUnqPtr.size() );

	if ( pomUnqPtr.size()>0 )
	{
		for ( size_t iIndex = 0; iIndex < pomUnqPtr.size(); iIndex++ )
		 {
			GET_POM_objectShrPtr pomObjSharedPtr ( move ( pomUnqPtr[iIndex] ) );
			vPomObjShrPtr.push_back( pomObjSharedPtr );
		 }
		// Add the object to reference folder in workflow
		if ( mArgumentsMap[ATTACHMENT_TYPE].compare( REFERENCE_ATTACHMENT ) == 0 )
		{
			epmTaskPtr->addAttachments ( EPM_reference_attachment, vPomObjShrPtr );
		}
		// Add the object to target folder in workflow
		else if ( mArgumentsMap[ATTACHMENT_TYPE].compare( TARGET_ATTACHMENT )== 0 )
		{
			epmTaskPtr->addAttachments ( EPM_target_attachment, vPomObjShrPtr );
		}
	}
	LOG_TRACE ( logger, " End: GET6_attachedrelatedobjectsAH_impl: " );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_AttachMfgAttrFormsToTargetAH()
//
//    Purpose:   Action Handler to Release the Mfg Attribute Forms
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_AttachMfgAttrFormsToTargetAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_AttachMfgAttrFormsToTargetAH(EPM_action_message_t p_tMsg) {

    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GET6_AttachMfgAttrFormsToTargetAH");

    try {

        GET_processHandler(p_tMsg, GET6_AttachMfgAttrFormsToTargetAH_impl);
    } catch(const IFail &ex) {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    } catch(GET_Exception *ex) {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    } catch(...) {
        istatus = GET_general_exception;
        string sMessage = "GET6_AttachMfgAttrFormsToTargetAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_AttachMfgAttrFormsToTargetAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_AttachMfgAttrFormsToTargetAH_impl()
//
//    Purpose:   Action Handler Implementation to attaching Mfg Attribute Forms to target
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_AttachMfgAttrFormsToTargetAH_impl(const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& p_vArguments)
{
    LOG_TRACE(logger, "Entering...GET6_AttachMfgAttrFormsToTargetAH_impl");

    GET_CheckMCN_AH_Impl*  GET_CheckMCN_AHObj = new GET_CheckMCN_AH_Impl ( p_tTaskTag, p_vAttachments, p_vArguments );
    GET_CheckMCN_AHObj->attachMfgAttrFormsToTarget();

    LOG_TRACE (logger, "Exiting...GET6_AttachMfgAttrFormsToTargetAH_impl");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_UpdateStockMaterialMfgFrmAH()
//
//    Purpose:   Action Handler to add that object to target or reference.
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     02 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_UpdateStockMaterialMfgFrmAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE(logger, "START : GET6_UpdateStockMaterialMfgFrmAH");

    try
    {
        GET_processHandler( tMessage, GET6_UpdateStockMaterialMfgFrmAH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_UpdateStockMaterialMfgFrmAH" );
    }

    LOG_TRACE ( logger, "END : GET6_UpdateStockMaterialMfgFrmAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_UpdateStockMaterialMfgFrmAH_impl()
//
//    Purpose:   Action Handler implementation function for GET6_attachedrelatedobjectsAH_impl handler
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
//  TCS Development Team     02 May, 2017         Initial creation
//  TCS Development Team     25 May, 2018         Added code to reset Oracle Xfer Prop as True
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_UpdateStockMaterialMfgFrmAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
	vector <tag_t> vTargetAttachments;
	GET_POM_objectUnqPtr itemUnqPtr;
	vector<GET_FormShrPtr> vPomObjShrPtr;
	GET_ItemRevisionUnqPtr stockSolutionItemRevUnqPtr;
	vector<GET_POM_objectUnqPtr> vSolutionItems;

	string sMcnOrg ="";

	LOG_TRACE ( logger, " Start: GET6_UpdateStockMaterialMfgFrmAH_impl: " );

	for ( size_t iIndex = 0; iIndex <  vAttachments[EPM_target_attachment].size(); ++iIndex )
	{
		// Check if the target is an MCNRevision or not
		if ( GET_POM_object::isDescendant ( vAttachments[EPM_target_attachment][iIndex], GET_MCN_REVISION_CLASS ) )
		{
			 GET_ItemRevisionUnqPtr mcnItemRevUnqPtr = GET_ItemRevision::getInstance ( vAttachments[EPM_target_attachment][iIndex] );
			 GET_ItemRevisionShrPtr mcnItemRevShrPtr ( move ( mcnItemRevUnqPtr ) );
			 vSolutionItems = mcnItemRevShrPtr->getPropTags ( CM_HAS_SOLUTION_ITEMS_PROP );
	    }
		else if ( GET_POM_object::isDescendant ( vAttachments[EPM_target_attachment][iIndex], FORM_CLASS ) )
	    {
			GET_FormUnqPtr formUnqPtr = GET_Form::getInstance ( vAttachments[EPM_target_attachment][iIndex] );
			GET_FormShrPtr formSharedPtr ( move (formUnqPtr) );
			vPomObjShrPtr.push_back( formSharedPtr );
		}
	}

	GET_ItemRevisionShrPtr stockSolutionItemRevShrPtr ( move ( GET_ItemRevision::getInstance ( vSolutionItems[0]->getTag() ) ) );

	GET_POM_objectUnqPtr stockSolutionItemUnqPtr = GET_POM_object::getInstance ( ( stockSolutionItemRevShrPtr->getItem() )->getTag() );

	GET_POM_objectShrPtr stockSolutionItemShrPtr ( move ( stockSolutionItemUnqPtr ) );

	for ( int iInx = 0; iInx < vPomObjShrPtr.size(); iInx++ )
	{
		vPomObjShrPtr[iInx]->setProp ( "get6StockMaterial", stockSolutionItemShrPtr, true, true);
		vPomObjShrPtr[iInx]->setProp ( MFG_ATTR_FORM_ORACLE_XFER_ATTR, MFG_ATTR_FORM_ORACLE_XFER_VALUE, true, true);
	}

	LOG_TRACE ( logger, " END: GET6_UpdateStockMaterialMfgFrmAH_impl: " );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_routeMBOMBOPAH()
//
//    Purpose:   Action Handler to Route MBOM or BOP path based on SOlution folder contents
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_routeMBOMBOPAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      15 Sep, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_routeMBOMBOPAH(EPM_action_message_t p_tMsg) {

    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GET6_routeMBOMBOPAH");

    try
    {
        GET_processHandler(p_tMsg, GET6_routeMBOMBOPAH_impl, false);
    }
    catch(const IFail &ex)
    {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch(GET_Exception *ex)
    {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch(...)
    {
        istatus = GET_general_exception;
        string sMessage = "GET6_routeMBOMBOPAH_impl failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_routeMBOMBOPAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_routeMBOMBOPAH_impl()
//
//    Purpose:   Action Handler Implementation to Route MBOM or BOP path based on SOlution folder contents
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      15 Sep, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_routeMBOMBOPAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
    bool bMBOMExist = false;
    bool bBOPExist  = false;

    vector<string>  vBOPObjRevPrefValues;
    vector<string>  vMBOMObjRevPrefValues;
    string sAffectBOPDecision = MCN_LOV_TRUE_VALUE;

    LOG_TRACE(logger, "Entering...GET6_routeMBOMBOPAH_impl");

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

    GET_EPMTaskUnqPtr currentTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );
    GET_EPMTaskUnqPtr rootTaskUnqPtr = currentTaskUnqPtr->getRootTask();

    vector<GET_POM_objectUnqPtr> vTargetAttachmentsUnqPtr = rootTaskUnqPtr->askAttachments ( EPM_target_attachment );

    // Loop through each target objects
    for ( int iTargetIndex = 0; iTargetIndex < vTargetAttachmentsUnqPtr.size(); iTargetIndex++ )
    {
        // Validate if MCN Revision is found in target object
        if (! GET_POM_object::isDescendant ( vTargetAttachmentsUnqPtr[iTargetIndex]->getTag(), GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getMCNRevShrPtr ( move ( GET_ItemRevision::getInstance ( vTargetAttachmentsUnqPtr[iTargetIndex]->getTag() ) ) );
        LOG_TRACE ( logger, "getMCNRevShrPtr->getType()-->" + getMCNRevShrPtr->getType() );

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

        if ( bMBOMExist == true && bBOPExist == true )
        {
            // Update Affect BOP Decision property as true, coz BOP obj also found along with MBOM obj in Solution folder
            getMCNRevShrPtr->setProp ( AFFECT_BOP_DECISION_PROP, sAffectBOPDecision );
            currentTaskUnqPtr->setTaskResult ( MBOM_DECISION_ROUTE );
        }
        else
        {
            if ( bBOPExist == true )
            {
                // Update Affect BOP Decision property as true, coz BOP obj found in Solution folder
                getMCNRevShrPtr->setProp ( AFFECT_BOP_DECISION_PROP, sAffectBOPDecision );
                currentTaskUnqPtr->setTaskResult ( BOP_ONLY_DECISION_ROUTE );
            }
            else
            {
                currentTaskUnqPtr->setTaskResult ( MBOM_DECISION_ROUTE );
            }
        }

        // Break the loop as MCN Revision has found
        break;
    }

    LOG_TRACE (logger, "Exiting...GET6_routeMBOMBOPAH_impl");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_populateMultiOrgListAH()
//
//    Purpose:   Action Handler to populate Multi Org list during ECN process
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_populateMultiOrgListAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      20 Jun, 2018         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_populateMultiOrgListAH(EPM_action_message_t p_tMsg)
{
    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GET6_populateMultiOrgListAH");

    try
    {
        GET_processHandler(p_tMsg, GET6_populateMultiOrgListAH_impl);
    }
    catch(const IFail &ex)
    {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch(GET_Exception *ex)
    {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch(...)
    {
        istatus = GET_general_exception;
        string sMessage = "GET6_populateMultiOrgListAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_populateMultiOrgListAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_populateMultiOrgListAH_impl()
//
//    Purpose:   Action Handler Implementation to populate Multi Org list during ECN process
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      20 Jun, 2018         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_populateMultiOrgListAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& p_vArguments )
{
    int iStatus = 0;
    int iTableRows = 0;
	tag_t *tTableRows = NULL;

	vector<tag_t> 		vTargetAttachments;

    string sTargetID 	= EMPTY_STRING_VALUE;
    string sFileContent = EMPTY_STRING_VALUE;
    vector <string> vMCNOrgList;

    GET_ItemRevisionUnqPtr          getItemRevUnqPtr;
    GET_ItemRevisionUnqPtr 			targetRevisionUnqPtr;
    vector<GET_POM_objectUnqPtr>    vSolItemsUnqPtr;
    vector<GET_ItemRevisionShrPtr> 	vValidSolItemsShrPtr;

    LOG_TRACE ( logger, "Entering...GET6_populateMultiOrgListAH_impl" );

	vTargetAttachments = p_vAttachments[EPM_target_attachment];
	for ( size_t iIndex = 0; iIndex < vTargetAttachments.size(); ++iIndex )
	{
		GET_POM_objectUnqPtr getPOMObjectPtr = GET_POM_object::getInstance ( vTargetAttachments[iIndex] );

		// check for ECN revision type
		if ( getPOMObjectPtr->askTypeName().compare ( ECNREVISION_TYPE ) == 0 )
		{
			targetRevisionUnqPtr = GET_ItemRevision::getInstance ( vTargetAttachments[iIndex] );
			break;
		}
	}
	if ( targetRevisionUnqPtr.get() == NULL )
	{
		THROW ( "Engineering Change Notice Revision not found in Target List" );
	}

	GET_ItemRevisionShrPtr ecnRevisionShrPtr ( move ( targetRevisionUnqPtr ) );

    // Get the all MCN Org List from the preference
    getStringPrefValues ( MCN_ORG_LIST, vMCNOrgList );

    if ( vMCNOrgList.size() == 0 )
    {
        string sMessage = "The Preference " + string ( MCN_ORG_LIST ) + " is not defined or does not have a value";
        THROW ( sMessage );
    }

	// Get all objects from solution folder of MCN object
	vSolItemsUnqPtr = ecnRevisionShrPtr->getPropTags ( CM_HAS_SLITEMS_PROP );

	// Loop through each objects in Solution Item folder
	for ( size_t iSolIndex = 0; iSolIndex < vSolItemsUnqPtr.size(); iSolIndex++ )
	{
		GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( GET_ItemRevision::getInstance ( vSolItemsUnqPtr[iSolIndex]->getTag() ) ) );

		// To get only Engineering revision or Electrical revision or Manufacturing part revision object
		if ( getItemRevShrPtr->getType().compare ( MECHREV_TYPE ) == 0 || getItemRevShrPtr->getType().compare ( ELECREV_TYPE ) == 0 )
		{
			vValidSolItemsShrPtr.push_back ( getItemRevShrPtr );
		}
	}

	// Lock the ECN Revision for further modification
	ecnRevisionShrPtr->lock();
	vector<GET_POM_objectUnqPtr> vPOMObjUnqPtr = ecnRevisionShrPtr->appendTableRow ( ECN_ITEM_ORG_LIST, vValidSolItemsShrPtr.size() );
	LOG_TRACE ( logger, "Table Row size--> " + vPOMObjUnqPtr.size() );

	// Loop through each objects in Solution Item folder
	for ( size_t iValidSolIndex = 0; iValidSolIndex < vValidSolItemsShrPtr.size(); iValidSolIndex++ )
	{
		vector <string> vOrgID;

		LOG_TRACE ( logger, "Setting Item Id--> " + vValidSolItemsShrPtr[iValidSolIndex]->getItem()->getId() );

		// Add Item Id to Form
		GET_POM_objectShrPtr getTableRowShrPtr ( move ( vPOMObjUnqPtr[iValidSolIndex] ) );
		getTableRowShrPtr->lockInstanceForModification();
		getTableRowShrPtr->setProperty ( ENGG_ITEM_ID, vValidSolItemsShrPtr[iValidSolIndex]->getItem()->getId(), false, false, false );

		vector<GET_POM_objectUnqPtr> vPOMSecondaryOrgForms = vValidSolItemsShrPtr[iValidSolIndex]->getItem()->getPropTags ( GET_PART_ORG_ATTR_BO );

		// Loop through each Org form to get the Org ID
		for ( size_t iOrgFormIndex = 0; iOrgFormIndex < vPOMSecondaryOrgForms.size(); iOrgFormIndex++ )
		{
			GET_POM_objectShrPtr getPOMObjectShrPtr ( move ( vPOMSecondaryOrgForms[iOrgFormIndex] ) );
			GET_FormUnqPtr getOrgFormUnqPtr = GET_Form::getInstance ( getPOMObjectShrPtr->getTag() );
			GET_FormShrPtr getOrgFormShrPtr ( move ( getOrgFormUnqPtr ) );

			string sOrgID = getOrgFormShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
			vOrgID.push_back ( sOrgID );
		}

		vector<string> vOrgValue;
		for ( size_t iOrgIdIndex = 0; iOrgIdIndex < vMCNOrgList.size(); iOrgIdIndex++ )
		{
			if ( std::find ( vOrgID.begin(), vOrgID.end(), vMCNOrgList[iOrgIdIndex] ) != vOrgID.end() )
			{
				vOrgValue.push_back ( CM_LOV_YES_VALUE );
			}
			else
			{
				vOrgValue.push_back ( CM_LOV_NO_VALUE );
			}
		}

		for ( size_t iPropValueIndex = 0; iPropValueIndex < vMCNOrgList.size(); iPropValueIndex++ )
		{
			string sOrgPropName = GET6_ATTR_PREFIX + vMCNOrgList[iPropValueIndex];
			LOG_TRACE ( logger, "sOrgPropName--> " + vOrgValue[iPropValueIndex] );

			getTableRowShrPtr->setProperty ( sOrgPropName, vOrgValue[iPropValueIndex], false, false, false );
		}

		 getTableRowShrPtr->saveInstance();
		 getTableRowShrPtr->loadInstance();
		 getTableRowShrPtr->refresh( POM_no_lock );
	}

	// Save and Unlock the ECN revision
	ecnRevisionShrPtr->save();
	ecnRevisionShrPtr->unlock();
	ecnRevisionShrPtr->refreshObject();

    LOG_TRACE (logger, "Exiting...GET6_populateMultiOrgListAH_impl");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_readMultiOrgListAH()
//
//    Purpose:   Action Handler to populate Multi Org list during ECN process
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_readMultiOrgListAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      20 Jun, 2018         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_readMultiOrgListAH(EPM_action_message_t p_tMsg)
{
    int istatus = ITK_ok;

    LOG_TRACE(logger, "Entering...GET6_readMultiOrgListAH");

    try
    {

        GET_processHandler(p_tMsg, GET6_readMultiOrgListAH_impl);
    }
    catch(const IFail &ex)
    {
        istatus = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, ex.ifail(), ex.getMessage().c_str() );
    }
    catch(GET_Exception *ex)
    {
        istatus = GET_general_exception;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, ex->getErrorMessage().c_str() );
        delete ex;
    }
    catch(...)
    {
        istatus = GET_general_exception;
        string sMessage = "GET6_readMultiOrgListAH failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_readMultiOrgListAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_readMultiOrgListAH_impl()
//
//    Purpose:   Action Handler Implementation to populate Multi Org list during ECN process
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      20 Jun, 2018         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET6_readMultiOrgListAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& p_vArguments )
{
    int iStatus = 0;

    string strNamingPattern = EMPTY_STRING_VALUE;
    vector <string> vFileContents;
    vector <string> vMCNOrgList;
    vector <string> vItemID;

    map <string, vector<string>> 	mItemIdsToPropValues;
    map <string, vector<string>>	mOrgToItemIds;

    LOG_TRACE (logger, "Entering...GET6_readMultiOrgListAH_impl");

	if ( ( p_vArguments.find ( SOURCE_HANDLER_ARG ) == p_vArguments.end() ) || ( p_vArguments[SOURCE_HANDLER_ARG].empty() ) )
	{
		THROW ( "Missing Argument --> " + string ( SOURCE_HANDLER_ARG ) );
	}
	else if ( ( p_vArguments.find ( TARGET_HANDLER_ARG ) == p_vArguments.end() ) || ( p_vArguments[TARGET_HANDLER_ARG].empty() ) )
	{
		THROW ( "Missing Argument --> " + string ( TARGET_HANDLER_ARG ) );
	}

	if ( p_vArguments[TARGET_HANDLER_ARG] != GET_MCN_BO )
	{
		THROW ( "Workflow is not for MCN derivation..." );
	}

    // Get the all MCN Org List from the preference
	getStringPrefValues ( MCN_ORG_LIST, vMCNOrgList );

	if ( vMCNOrgList.size() == 0 )
	{
		string sMessage = "The Preference " + string ( MCN_ORG_LIST ) + " is not defined or does not have a value";
		THROW ( sMessage );
	}

	for ( size_t iMCNOrgIndex = 0; iMCNOrgIndex < vMCNOrgList.size(); iMCNOrgIndex++ )
	{
		mOrgToItemIds.insert ( std::pair<string, vector<string>> ( vMCNOrgList[iMCNOrgIndex], vItemID ) );
	}

	// Read Multi Org form content
	mItemIdsToPropValues = readMultiOrgList ( tTaskTag, p_vAttachments, p_vArguments );
	LOG_TRACE ( logger, "mItemIdsToPropValues.size()--> " + mItemIdsToPropValues.size() );

	for ( std::map<string, vector<string>>::iterator itItemIdsToPropValues=mItemIdsToPropValues.begin(); itItemIdsToPropValues!=mItemIdsToPropValues.end(); ++itItemIdsToPropValues )
	{
		string			itemId;
		vector <string> vPropValue;

		itemId 		= itItemIdsToPropValues->first;
		vPropValue 	= itItemIdsToPropValues->second;

		std::map<string, vector<string>>::iterator it;

		for ( size_t iPropValueIndex=0; iPropValueIndex < vPropValue.size(); iPropValueIndex++ )
		{
			LOG_TRACE ( logger, "vPropValue--> " + vPropValue[iPropValueIndex] );
			if ( vPropValue[iPropValueIndex].compare ( CM_LOV_YES_VALUE ) == 0 )
			{
				LOG_TRACE ( logger, "vMCNOrgList--> " + vMCNOrgList[iPropValueIndex] );
				it = mOrgToItemIds.find ( vMCNOrgList[iPropValueIndex] );
				if ( it != mOrgToItemIds.end() )
				{
					LOG_TRACE ( logger, "Inserting itemId--> " + itemId );
					it->second.push_back ( itemId );
				}
			}
		}
	}

	LOG_TRACE ( logger, "mOrgToItemIds.size()--> " + mOrgToItemIds.size() );
	for ( std::map<string, vector<string>>::iterator it=mOrgToItemIds.begin(); it!=mOrgToItemIds.end(); ++it )
	{
		string sOrgName = EMPTY_STRING_VALUE;
		string sItemIds = EMPTY_STRING_VALUE;
		vector<string> vItemID;

		sOrgName = it->first;
		vItemID = it->second;
		LOG_TRACE ( logger, "sOrgName--> " + sOrgName );

		if ( vItemID.size() == 0 )
		{
			continue;
		}

		GET_TC_ProjectUnqPtr projUnqPtr = GET_TC_Project::find ( sOrgName );

		GET_POM_objectShrPtr getProjectObjShrPtr ( move ( GET_POM_object::getInstance ( projUnqPtr->getTag() ) ) );

		strNamingPattern = string ( NAMING_PATTERN_PREFIX ) + sOrgName + string ( NAMING_PATTERN_SUFFIX );

		iStatus = deriveChangeObject ( strNamingPattern.c_str(), getProjectObjShrPtr, vItemID, p_vAttachments, p_vArguments );
	}

    LOG_TRACE (logger, "Exiting...GET6_readMultiOrgListAH_impl");
}

map <string, vector<string>> readMultiOrgList ( const tag_t tTaskTag, map<int, vector<tag_t> > &vAttachments, map<string, string> &mArgumentsMap )
{
	vector<tag_t> vTargetAttachments;

	vector<string> vFileContents;
    vector <string> vMCNOrgList;

    map <string, vector<string>>	mItemIdsToPropValues;

	GET_ItemRevisionUnqPtr targetRevisionUnqPtr;
	vector<GET_POM_objectUnqPtr> vNamedRefs;

	LOG_TRACE ( logger, "START: readMultiOrgList" );

    // Get the all MCN Org List from the preference
	getStringPrefValues ( MCN_ORG_LIST, vMCNOrgList );

	vTargetAttachments = vAttachments[EPM_target_attachment];
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

	// Read Table Property
	vector<GET_POM_objectUnqPtr> vTablePropValues = ecnRevisionShrPtr->getPropTableRows ( ECN_ITEM_ORG_LIST );
	LOG_TRACE ( logger, "vTablePropValues.size()--> " + vTablePropValues.size() );

	for (size_t iTabRowIndex =0 ; iTabRowIndex <vTablePropValues.size(); iTabRowIndex++ )
	{
		string itemId = "";
		vector <string> vPropValue;

		itemId = vTablePropValues[ iTabRowIndex ]->getPropertyString ( ENGG_ITEM_ID );
		LOG_TRACE ( logger, "ItemId--> " + itemId );

		for ( size_t iPropValueIndex = 0; iPropValueIndex < vMCNOrgList.size(); iPropValueIndex++ )
		{
			string sOrgPropName = GET6_ATTR_PREFIX + vMCNOrgList[iPropValueIndex];
			string sPropValue = vTablePropValues[ iTabRowIndex ]->getPropertyString ( sOrgPropName );
			vPropValue.push_back ( sPropValue );

			LOG_TRACE ( logger, "sOrgPropName--> " + sOrgPropName );
			LOG_TRACE ( logger, "sPropValue--> " + sPropValue );
		}

		// Insert to Map
		mItemIdsToPropValues.insert ( std::pair<string, vector<string>> ( itemId, vPropValue ) );
	}

	LOG_TRACE ( logger, "END: readMultiOrgList" );

	return mItemIdsToPropValues;
}
