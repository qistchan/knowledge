
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_T4O_ActionHandlers.cxx
//
//    Purpose:   Source File defining the T4O Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016         Initial creation
//  TCS Development Team      03 Mar, 2017         Action Handler for T4O transfer decision
//  TCS Development Team      30 Mar, 2017         Fix for T4O Error Log file attachment issue
//  TCS Development Team      20 Jul, 2017         Added -subject workflow argument
//  TCS Development Team      27 Sep, 2017         Restructured GET_T4O_Create_CC_Object_AH_impl function
//  TCS Development Team      13 Oct, 2017         Changes the Revision rule from Released to WIP for CC Obj creation
//  TCS Development Team      28 May, 2018         Updated GET6_notifyT4OAH_impl function to get the responsible party detail
//
//   ============================================================================
// ENDFILEDOC   ***/

// Teamcenter Includes
#include <tc/tc.h>
#include <tc/emh.h>
#include <epm/epm.h>
#include <tc/tc_arguments.h>
#include <base_utils/IFail.hxx>
#include <base_utils/ResultCheck.hxx>

// GET Includes
#include <GET_Errors.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Types.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_CheckMCN_AH_Impl.hxx>
#include <GET_T4O_Common.hxx>
#include <GET_T4O_ActionHandlers.hxx>
#include <GET_Utils.hxx>
#include <GET_POM_object.hxx>
#include <GET_EPMJob.hxx>
#include <GET_Constants.hxx>

// Private Function Prototypes

static void GET_T4O_Create_CC_Object_AH_impl ( const tag_t, map<int, vector<tag_t>>&, map<string, string>& );
static void createCCObjects ( tag_t p_tTaskTag, string sRevRule, GET_ItemRevisionShrPtr linkedProductRevShrPtr,
    GET_ItemRevisionShrPtr linkedProcessRevShrPtr, GET_ItemRevisionShrPtr linkedDepartmentRevShrPtr );
static void GET_T4OTransferDecisionAH_impl ( const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& mArgumentsMap );
static void GET6_notifyT4OAH_impl ( const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& mArgumentsMap );

const string logger = "get.handler.GET_T4O_ActionHandlers";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_T4OCreateCCObjectAH()
//
//    Purpose:   Action Handler for Creating CC Object for BOP transfer
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_T4OCreateCCObjectAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016          Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_T4OCreateCCObjectAH(EPM_action_message_t p_tMsg)
{
    int istatus = ITK_ok;

	LOG_TRACE ( logger, "Entering...GET6_T4OCreateCCObjectAH");

    try
    {
        GET_processHandler ( p_tMsg, GET_T4O_Create_CC_Object_AH_impl );
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
        string sMessage = "GET6_T4OCreateCCObject failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

    LOG_TRACE ( logger, "Exiting...GET6_T4OCreateCCObjectAH" );

    return istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET_T4O_Create_CC_Object_AH_impl()
//
//    Purpose:   Action Handler Implementation for CC object creation
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016          Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET_T4O_Create_CC_Object_AH_impl ( const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& mArgumentsMap )
{
	int istatus = ITK_ok;
    bool isProductLinked = false;
    bool isDeptFound = false;
    string sConsolidatedErrorMessage = EMPTY_STRING_VALUE;
    string strOwningProject = EMPTY_STRING_VALUE;
    string strReleaseStatusName = EMPTY_STRING_VALUE;
	
	GET_ItemRevisionShrPtr linkedProductRevShrPtr;
	GET_ItemRevisionShrPtr linkedProcessRevShrPtr;
	GET_ItemRevisionShrPtr linkedDepartmentRevShrPtr;
	
	// Clear the existing error stack
	istatus = EMH_clear_errors();
	
	LOG_TRACE ( logger, "Entering...GET_T4O_Create_CC_Object_AH_impl" );

    // Loop through each target objects
    for ( int inx = 0; inx < p_vAttachments[EPM_target_attachment].size(); inx++ )
    {
        // Validate if MCN Revision is found in target object
        if (! GET_POM_object::isDescendant ( p_vAttachments[EPM_target_attachment][inx], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getTargetShrPtr( move ( GET_ItemRevision::getInstance ( p_vAttachments[EPM_target_attachment][inx] ) ) );
        LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getTargetShrPtr->getType() );

        getLinkedPPPObjects ( getTargetShrPtr, isProductLinked, isDeptFound, sConsolidatedErrorMessage,
                linkedProductRevShrPtr, linkedProcessRevShrPtr, linkedDepartmentRevShrPtr );

        LOG_TRACE ( logger, "sConsolidatedErrorMessage.size() is..." + sConsolidatedErrorMessage.size() );

        if ( ! ( isDeptFound && isProductLinked ) )
        {
            // Throw the error to the calling method (Where it will be handled)
            throw ( sConsolidatedErrorMessage );
        }
        else if ( ( linkedProductRevShrPtr->getTag() != NULLTAG ) && ( linkedProcessRevShrPtr->getTag() != NULLTAG ) &&
                ( linkedDepartmentRevShrPtr->getTag() != NULLTAG ) )
        {
            LOG_TRACE ( logger, "All data are good... Now creating CC object..." );

            // Construct release status string based on MCN Project
            strOwningProject = getTargetShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
            strReleaseStatusName = string ( REVISION_RULE_PREFIX ) + strOwningProject + string ( WIP_REV_RULE_SUFF );
            LOG_TRACE ( logger, "strReleaseStatusName-->" + strReleaseStatusName );

            // Create CC object
            createCCObjects ( p_tTaskTag, strReleaseStatusName, linkedProductRevShrPtr, linkedProcessRevShrPtr, linkedDepartmentRevShrPtr );
        }

        // Break the loop as MCN Revision has found
        break;
    }

    LOG_TRACE ( logger, "Exiting...GET_T4O_Create_CC_Object_AH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   createCCObjects()
//
//    Purpose:   Private function for CC object creation
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      1 Dec, 2016          Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void createCCObjects ( tag_t p_tTaskTag, string sRevRule, GET_ItemRevisionShrPtr linkedProductRevShrPtr,
	GET_ItemRevisionShrPtr linkedProcessRevShrPtr, GET_ItemRevisionShrPtr linkedDepartmentRevShrPtr )
{
	int istatus = ITK_ok;

	GET_CollaborationContextShrPtr productContextShrPtr;
	GET_CollaborationContextShrPtr processContextShrPtr;
	GET_CollaborationContextShrPtr departmentContextShrPtr;
	GET_CollaborationContextShrPtr clbCnxtShrPtr;
	
	LOG_TRACE ( logger, "Entering...createCCObjects" );

	LOG_TRACE ( logger, "Linked Product is ..." + linkedProductRevShrPtr->getId() );
	LOG_TRACE ( logger, "Linked Process is ..." + linkedProcessRevShrPtr->getId() );
	LOG_TRACE ( logger, "Linked Department is ..." + linkedDepartmentRevShrPtr->getId() );
	
	// Create config context for Product
	createStructureContext ( sRevRule, linkedProductRevShrPtr, MEPRODUCTCONTEXT_TYPE, productContextShrPtr );
	
	// Create config context for Process
	createStructureContext ( sRevRule, linkedProcessRevShrPtr, MEPROCESSCONTEXT_TYPE, processContextShrPtr );
	
	// Create config context for Department
	createStructureContext ( sRevRule, linkedDepartmentRevShrPtr, MEPLANTCONTEXT_TYPE, departmentContextShrPtr );
	
	clbCnxtShrPtr = createCCObject ( productContextShrPtr, processContextShrPtr, departmentContextShrPtr, linkedProcessRevShrPtr );

	// convert folder object in proper format to add in EPM Task
	GET_POM_objectShrPtr getPOMClbCnxtShrPtr ( move ( GET_POM_object::getInstance ( clbCnxtShrPtr->getTag() ) ) );

	vector<GET_POM_objectShrPtr> vClbCnxtShrPtr;
	vClbCnxtShrPtr.push_back (getPOMClbCnxtShrPtr);

	GET_EPMTaskUnqPtr getEPMTaskUnqPtr = GET_EPMTask::getInstance( p_tTaskTag );
	getEPMTaskUnqPtr->addAttachments ( EPM_target_attachment, vClbCnxtShrPtr );

	LOG_TRACE ( logger, "Status of EPM_add_attachments is ..." + istatus );
	LOG_TRACE ( logger, "Exiting...createCCObjects" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_T4OTransferDecisionAH()
//
//    Purpose:   Action Handler Implementation for taking decision whether T4O transfer is required
//
//    Inputs:    tMessage
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      03 Mar, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_T4OTransferDecisionAH(EPM_action_message_t p_tMsg)
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_T4OTransferDecisionAH" );

    try
    {
        GET_processHandler ( p_tMsg, GET_T4OTransferDecisionAH_impl, false );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_T4OTransferDecisionAH" );
    }

    LOG_TRACE ( logger, "END : GET6_T4OTransferDecisionAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET_T4OTransferDecisionAH_impl()
//
//    Purpose:   Action Handler Implementation for taking decision whether T4O transfer is required
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      03 Mar, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void GET_T4OTransferDecisionAH_impl ( const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& mArgumentsMap )
{
    int istatus = ITK_ok;

    vector<string> vT4OTransferDecisionValue;

    LOG_TRACE ( logger, "Entering...GET_T4OTransferDecisionAH_impl" );

    // Clear the existing error stack
    istatus = EMH_clear_errors();

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( TYPE_ARG ) == mArgumentsMap.end () || mArgumentsMap[TYPE_ARG].empty () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    //get the handler arguments from map into string
    string argType = mArgumentsMap[TYPE_ARG];
    LOG_TRACE ( logger, "Argument type : " + argType );

    GET_EPMTaskUnqPtr getTaskUnqPtr ( move ( GET_EPMTask::getInstance ( p_tTaskTag ) ) );

    // Check if current Condition task for taking T4O Transfer decision
    if ( argType.compare( T4O_TRANSFER_ARG_VALUE ) == 0 )
    {
        // Validate the arguments supplied
        if ( mArgumentsMap.find ( PREF_ARG ) == mArgumentsMap.end () || mArgumentsMap[PREF_ARG].empty () )
        {
            string sMsg = "The Workflow handler argument \"" + string ( PREF_ARG )
                    + "\"  is missing or is empty";
            THROW ( sMsg );
        }
        //get the handler arguments from map into string
        string sPrefName = mArgumentsMap[PREF_ARG];
        LOG_TRACE ( logger, "Preference name : " + sPrefName );

        getStringPrefValues ( sPrefName, vT4OTransferDecisionValue, TC_preference_site );

        if ( vT4OTransferDecisionValue.empty() )
        {
            getTaskUnqPtr->setTaskResult ( CM_LOV_NO_VALUE );
        }
        else
        {
            GET_toUpper( vT4OTransferDecisionValue[0] );
            if ( vT4OTransferDecisionValue[0].compare ( YES_VALUE ) == 0 )
            {
                getTaskUnqPtr->setTaskResult ( CM_LOV_YES_VALUE );
            }
            else
            {
                getTaskUnqPtr->setTaskResult ( CM_LOV_NO_VALUE );
            }
        }
    }
    else if ( argType.compare ( ROUTING_ARG_VALUE ) == 0 )
    {
        bool isProductLinked  = false;
        vector<GET_ItemRevisionShrPtr> vProcessRevisions;
        vector<GET_ItemRevisionShrPtr> vBOMProcessRevisions;
        vector<GET_ItemRevisionShrPtr> vBOMProductRevisions;

        // Loop through each target objects
        for ( size_t iTargetObj=0; iTargetObj<p_vAttachments[EPM_target_attachment].size(); iTargetObj++ )
        {
            // Validate if MCN Revision is found in target object
            if (! GET_POM_object::isDescendant ( p_vAttachments[EPM_target_attachment][iTargetObj], GET_MCN_REVISION_CLASS ) )
            {
                continue;
            }

            GET_ItemRevisionShrPtr getTargetShrPtr ( move ( GET_ItemRevision::getInstance( p_vAttachments[EPM_target_attachment][iTargetObj] )));
            LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getTargetShrPtr->getType() );

            // Validate if Solution item folder has Process revision
            getProcessRevisions ( getTargetShrPtr, vProcessRevisions );
            LOG_TRACE ( logger, "Size of vProcessRevisions vector is:" + vProcessRevisions.size() );

            if ( vProcessRevisions.size() > 0 )
            {
                isProductLinked = true;
                break;
            }
        }

        if ( isProductLinked )
        {
            getTaskUnqPtr->setTaskResult ( CM_LOV_YES_VALUE );
        }
        else
        {
            getTaskUnqPtr->setTaskResult ( CM_LOV_NO_VALUE );
        }
    }
    else
    {
        bool isContentFound = false;

        GET_EPMTaskUnqPtr getEPMTaskUnqPtr = GET_EPMTask::getInstance ( p_tTaskTag );
        vector<GET_POM_objectUnqPtr> vReferenceObjsUnqPtr = getEPMTaskUnqPtr->askAttachments ( EPM_reference_attachment );

        for ( size_t iRefObj=0; iRefObj<vReferenceObjsUnqPtr.size(); iRefObj++ )
        {
           // Validate the reference folder has Folder object
           if ( vReferenceObjsUnqPtr [ iRefObj ]->getPropertyString( OBJECT_TYPE_ATTR ).compare ( FOLDERTYPE ) != 0 )
           {
               continue;
           }
           string foldername = vReferenceObjsUnqPtr[ iRefObj ]->getPropertyString( OBJECT_NAME_ATTR );

           vector<GET_POM_objectUnqPtr> vFolderContents = vReferenceObjsUnqPtr[ iRefObj ]->getPropertyTags( CONTENTS );

           if ( (foldername.compare ( argType ) == 0) && (vFolderContents.size() > 0) )
           {
               isContentFound = true;
               break;
           }
        }

        // If reference folder found with provided argument folder name and folder has content, set the condition task as YES
        if ( isContentFound )
        {
            getTaskUnqPtr->setTaskResult ( CM_LOV_YES_VALUE );
        }
        else
        {
            getTaskUnqPtr->setTaskResult ( CM_LOV_NO_VALUE );
        }
    }

    LOG_TRACE (logger, "Exiting...GET_T4OTransferDecisionAH_impl");
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_notifyT4OAH()
//
//    Purpose:   Action Handler Implementation for sending email with attachment
//
//    Inputs:    tMessage
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      12 Apr, 2017         Initial creation
//  TCS Development Team      28 May, 2018         Updated to get the current task tag
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_notifyT4OAH(EPM_action_message_t p_tMsg)
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_notifyT4OAH" );

    try
    {
        GET_processHandler ( p_tMsg, GET6_notifyT4OAH_impl, false );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_notifyT4OAH" );
    }

    LOG_TRACE ( logger, "END : GET6_notifyT4OAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_notifyT4OAH_impl()
//
//    Purpose:   Action Handler Implementation for sending email with attachment
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      12 Apr, 2017         Initial creation
//  TCS Development Team      20 Jul, 2017         Added -subject workflow argument
//  TCS Development Team      28 May, 2018         Updated GET6_notifyT4OAH_impl function to get the responsible party detail
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_notifyT4OAH_impl ( const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& mArgumentsMap )
{
    bool logFileFound = false;

    int istatus = ITK_ok;
	int iLocalSiteId = 0;
	
    ofstream fileAttachmentPtr;

    string strSubject = "";
    string strContent = "";
    string sAttachmentFilePath= "";
    string sDSNamedRefFullPath = "";
    string fileFormatType = "=T";
	string sSiteName = "";
    string sEmailId = "";
    string sRecipientID = "";

	vector<string> vEmailIDs;

    LOG_TRACE ( logger, "Entering...GET6_notifyT4OAH_impl" );

	// User can mention properties or resource pool or recipient's email id
	if ( ( mArgumentsMap.find ( RESOURCE_POOL_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap [RESOURCE_POOL_HANDLER_ARG].empty() ) &&
		 ( mArgumentsMap.find ( RESPONSIBLE_PARTY_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap [RESPONSIBLE_PARTY_HANDLER_ARG].empty() ) )
	{
		 THROW ( RESOURCE_POOL_HANDLER_ARG + string ( " or " ) + RESPONSIBLE_PARTY_HANDLER_ARG + string ( "\" has to be provided" ) );
	}

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( TYPE_ARG ) == mArgumentsMap.end () || mArgumentsMap[TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    //get the handler arguments from map into string
    string t4oTransferType = mArgumentsMap[TYPE_ARG];
    LOG_TRACE ( logger, "Argument type : " + t4oTransferType );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end () || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG )
                + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( SUBJECT_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap[SUBJECT_HANDLER_ARG].empty() )
    {
        THROW ( string ( "The argument \"" ) + SUBJECT_HANDLER_ARG + string ( "\" is not provided or has empty value" ) );
    }

    //get the handler arguments from map into string
    strSubject = mArgumentsMap[SUBJECT_HANDLER_ARG];

	GET_EPMTaskUnqPtr currentTaskUnqPtr = GET_EPMTask::getInstance( p_tTaskTag );
	GET_EPMTaskUnqPtr rootTaskUnqPtr = currentTaskUnqPtr->getRootTask();

    if ( mArgumentsMap.find ( RESOURCE_POOL_HANDLER_ARG ) != mArgumentsMap.end() )
	{
		sRecipientID = mArgumentsMap[RESOURCE_POOL_HANDLER_ARG];

		// Split the input recipient argument into Group and role filed
		vector<string> vGroupRole;
		GET_splitString ( sRecipientID, COLON_CHAR_VALUE, vGroupRole );

		if ( vGroupRole.size() != 2 )
		{
			string sMsg = "The Workflow handler argument \"" + string ( RESOURCE_POOL_HANDLER_ARG )
						   + "\"  is not in required format, Format must be Group:Role ";
			THROW ( sMsg );
		}

		LOG_TRACE(logger, "vGroupRole[0]-->" + vGroupRole[0]);
		LOG_TRACE(logger, "vGroupRole[1]-->" + vGroupRole[1]);

		vector<GET_GroupMemberUnqPtr> vGroupMemberUnqPtr = GET_GroupMember::find( vGroupRole[0], vGroupRole[1] );

		// Loop through each group member and send email
		for(int inx = 0; inx < vGroupMemberUnqPtr.size(); inx++)
		{
			GET_POM_userShrPtr pUser = vGroupMemberUnqPtr[inx]->getUser();
			GET_PersonUnqPtr person = pUser->getPerson();
			sEmailId = person->getEmailId();
			if ( ! sEmailId.empty() && sEmailId.find ( "@" ) != string::npos && sEmailId.find ( ".com" ) != string::npos )
			{
				vEmailIDs.push_back ( sEmailId );
			}
		}
	}

	if ( mArgumentsMap.find ( RESPONSIBLE_PARTY_HANDLER_ARG ) != mArgumentsMap.end() )
	{
		GET_POM_userUnqPtr getUserUnqPtr = currentTaskUnqPtr->askEPMResponsibleParty();
	    GET_POM_userShrPtr pUser ( move ( getUserUnqPtr ) );
	    GET_PersonUnqPtr person = pUser->getPerson();

	    sEmailId = person->getEmailId();
		if ( ! sEmailId.empty() && sEmailId.find ( "@" ) != string::npos && sEmailId.find ( ".com" ) != string::npos )
		{
			vEmailIDs.push_back ( sEmailId );
		}
	}

	vector<GET_POM_objectUnqPtr> vTargetAttachmentsUnqPtr = rootTaskUnqPtr->askAttachments ( EPM_target_attachment );
	
    // Loop through each target objects
    for ( size_t iTargetObj=0; iTargetObj<vTargetAttachmentsUnqPtr.size(); iTargetObj++ )
    {
		// Validate if target is Item Revision
        if ( ! GET_POM_object::isDescendant ( vTargetAttachmentsUnqPtr[iTargetObj]->getTag(), ITEMREVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionUnqPtr getTargetUnqPtr = GET_ItemRevision::getInstance( vTargetAttachmentsUnqPtr[iTargetObj]->getTag() );
        if ( getTargetUnqPtr->askTypeName().compare ( mArgumentsMap[INCLUDE_TYPE_ARG] ) != 0 )
        {
            continue;
        }

        // Get the Change Item id
        string sChangeItemId = getTargetUnqPtr->getItem()->getId();

		// Get the local Site Id
		iLocalSiteId = GET_Site::getLocalID();
		if( iLocalSiteId )
		{
			GET_SiteUnqPtr siteUnqPtr = GET_Site::find ( iLocalSiteId );
			if( siteUnqPtr != NULL )
			{
				sSiteName = siteUnqPtr->getName();
			}
		}
		sSiteName = string ( OPEN_SQUARE_CHAR_VALUE ) + sSiteName + string ( CLOSE_SQUARE_CHAR_VALUE );
		
        strSubject.append (" T4O ");
        strSubject.append ( t4oTransferType );
        strSubject.append ( " Transfer failed:" );
        strSubject.append ( sChangeItemId );
		strSubject.append (" ");
		strSubject.append ( sSiteName );		

        strContent = "<html><h3 style=\"color: #2e6c80;\">Dear User,</h3>";
        strContent = strContent  + "<p style=\"color:#2035E5\"><strong style=\"color: #2e6c80;\"> " + sChangeItemId + "</strong> has been sent back for the corrections</p><ul>";
        strContent = strContent  + "<p style=\"color:#2035E5\"> " + " Please check the attached logfile in the mail for more detail </p><ul>";
        strContent =  strContent  + "</ul><br/><p style=\"color:#2035E5\">Please correct the error and complete the Error Task <br/><h3 style=\"color: #2e6c80;\">Thanks.</h3></p></html>";
        LOG_TRACE(logger, "strContent-->" + strContent);

        vector<GET_POM_objectUnqPtr> vReferenceObjsUnqPtr = rootTaskUnqPtr->askAttachments( EPM_reference_attachment );

        // Loop through each Workflow Reference object
        for ( size_t iRefObj=0; iRefObj<vReferenceObjsUnqPtr.size(); iRefObj++ )
        {
            // Process only if Text type Dataset is found in Workflow Reference object list
            if ( vReferenceObjsUnqPtr [ iRefObj ]->getPropertyString( OBJECT_TYPE_ATTR ).compare ( TEXT_DATASET ) != 0 )
            {
                continue;
            }

            // Validate if the Workflow Reference object contains the T4O Log file
            string refObjDesc = vReferenceObjsUnqPtr[ iRefObj ]->getPropertyString( OBJECT_DESC_ATTR );
            LOG_TRACE ( logger, "Text Dataset Object Desc is ..." + refObjDesc );
            size_t found = refObjDesc.find ( T4X_LOGFILE_DESC );
            if ( found == string::npos )
            {
                LOG_TRACE ( logger, "T4O Log file not found in Workflow Reference ..." );
                continue;
            }

            logFileFound = true;

            // Truncate the extra character from Text Dataset object name
            string refObjName = vReferenceObjsUnqPtr[ iRefObj ]->getPropertyString( OBJECT_NAME_ATTR );
            refObjName = strtok ( (char *)refObjName.c_str(), "/" );
            LOG_TRACE ( logger, "Text Dataset Object Name is ..." + refObjName );

            // Create the full file path for exporting the Dataset Named Referenced file
            sDSNamedRefFullPath = string ( GET_SYSAPI_getTempDir() )
                                      + string ( GET_SYSAPI_getFileSeparator() )
                                      + refObjName + ".log";

            GET_DatasetUnqPtr getDatasetUnqPtr = GET_Dataset::getInstance(vReferenceObjsUnqPtr[ iRefObj ]->getTag());
            getDatasetUnqPtr->exportNamedReference ( TEXT_REFNAME, sDSNamedRefFullPath.c_str() );

            // Create the file name for the mail attachment file
            sAttachmentFilePath = string ( GET_SYSAPI_getTempDir() )
                                      + string ( GET_SYSAPI_getFileSeparator() )
                                      + "attachment_list_" + GET_intToString ( rand() ) + ".txt";

            // Create the body file
            fileAttachmentPtr.open ( sAttachmentFilePath.c_str() );
            if ( ! fileAttachmentPtr.is_open() )
            {
                string sMsg = "Unable to create/open a file with the name " + sAttachmentFilePath + " for creating the Mail Attachment file";
                THROW ( sMsg );
            }

            fileAttachmentPtr << sDSNamedRefFullPath.c_str();
            fileAttachmentPtr << fileFormatType.c_str();
            fileAttachmentPtr.close();

            if ( logFileFound )
                break;
        }

        if ( ! logFileFound )
        {
            string sMsg = "T4O Log file Not Found in Workflow Reference object list ";
            THROW ( sMsg );
        }

        // Send error log file as email attachement
        if ( vEmailIDs.size() > 0 )
        {
            sendMailAsHtml ( vEmailIDs, strSubject, strContent, sAttachmentFilePath );
        }

        // Delete the created temp files
        if ( !sAttachmentFilePath.empty() )
        {
            GET_SYSAPI_unLink ( ( char * ) sAttachmentFilePath.c_str() );
        }

        if ( !sDSNamedRefFullPath.empty() )
        {
            GET_SYSAPI_unLink ( ( char * ) sDSNamedRefFullPath.c_str() );
        }
    }

    LOG_TRACE (logger, "Exiting...GET6_notifyT4OAH_impl");
}
