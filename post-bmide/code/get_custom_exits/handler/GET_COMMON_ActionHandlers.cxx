
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_COMMON_ActionHandlers.cxx
//
//    Purpose:   Source File defining the common Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  Kumaresan K             10 May, 2016         Initial creation
//  TCS Development Team    19 Jul, 2016         Added handler implementation for deleting datasets related to Workflow targets
//  TCS Development Team    27 Apr, 2017         Modified the GET6_notifyAH_impl method to make it more generic
//  TCS Development Team    19 May, 2017         Modified the GET6_notifyAH_impl to display email body in tabular format
//                                               and included the provision of reporting in case of review task.
//  TCS Development Team    29 May, 2017         Simplified the call to get the root task from the current task in the GET6_notifyAH_impl handler implementation
//  TCS Development Team    29 May, 2017         Added handler implementation for identifying if Dispatcher Requests are created in the current Workflow (GET6_findDispatcherRequestsAH)
//  TCS Development Team    31 May, 2017         Modified query constants to reflect changes in Query file in the GET6_findDispatcherRequestsAH_impl method
//  Ganesh Ubale            30 Aug, 2017         Modified the GET6_notifyAH_impl method to add AWC link and add attachments to emails 
//  TechM Development Team  18 Sep, 2017         Added handler GET6_createDispatcherRequestsAH implementation to create Dispatcher request for the specified primary, relation and dataset types
//  TCS Development Team    22 Sep, 2017         Corrected the variable name for target attachments map in all the methods
//  TCS Development Team    12 Oct, 2017         Add the function createECNSummaryReport
//  TCS Development Team    19 Dec, 2017         Modified the GET6_notifyAH_impl method to create random directory for disposition files and delete those files at the end
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_BOMWindow.hxx>
#include <GET_COMMON_ActionHandlers.hxx>
#include <GET_Constants.hxx>
#include <GET_Dataset.hxx>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_ImanQuery.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Person.hxx>
#include <GET_POM_group.hxx>
#include <GET_POM_user.hxx>
#include <GET_ReleaseStatus.hxx>
#include <GET_RuntimeBusinessObject.hxx>
#include <GET_Site.hxx>
#include <GET_SMTP_Mail.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Types.hxx>
#include <GET_Utils.hxx>
#include <GET_DispatcherRequest.hxx>
#include <GET_ImanTextFile.hxx>
#include <GET_Preferences.hxx>

// Teamcenter Includes
#include <tc/emh.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// C Includes
#include <time.h>
#include <vector>
#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

using namespace get;

// Private Function Prototypes

void GET6_notifyAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_deleteRelatedDatasetAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_setStatusAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_findDispatcherRequestsAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
void GET6_createDispatcherRequestsAH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
string recurseWfSubTasks( GET_EPMTaskShrPtr taskShrPtr );
void createECNSummaryReport( string htmlPage, GET_ItemRevisionShrPtr ecnRevisionShrPtr );

const string logger = "get.handler.GET_COMMON_ActionHandlers";

struct propNameAndValues
{
    string sPropName;
    string sPropValue;
    propNameAndValues ( const string& sPropertyName, const string& sPropertyValue )
    {
        sPropName  = sPropertyName;
        sPropValue = sPropertyValue;
    }
};

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_notifyAH()
//
//    Purpose:   Handler to send email notification based on a property containing valid email address
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    Integer indicating ITK_ok or error codes
//
//     History:
//      Who                   Date                 Description
//  Kumaresan K             13 May, 2016         Initial creation
//  TCS Development Team    27 Apr, 2017         Modified the GET6_notifyAH_impl method to make it more generic
//  TCS Development Team    19 May, 2017         Modified the GET6_notifyAH_impl method to give current task as output instead of root task.
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_notifyAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_notifyAH" );

    try
    {
        GET_processHandler ( tMessage, GET6_notifyAH_impl, false );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_notifyAH" );
    }

    LOG_TRACE ( logger, "END : GET6_notifyAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_notifyAH_impl()
//
//    Purpose:   Implementation business logic for GET6_NotifyAH handler
//
//    Inputs:    None
//
//    Outputs:   tTaskTag - tag value of the root task
//                 mAttachmentsMap - a map containing attachments tag values
//                 mArgumentsMap - a string map containing handler arguments and its values
//
//    Return:    None
//
//     History:
//      Who                   Date                 Description
//  Kumaresan K             13 May, 2016         Initial creation
//  TCS Development Team    09 May, 2017         Cleaned the code for standards
//  TCS Development Team    19 May, 2017         Modified the GET6_notifyAH_impl to display email body in tabular format
//                                               and included the provision of reporting in case of review task.
//  TCS Development Team    29 May, 2017         Simplified the call to get the root task from the current task
//  Ganesh Ubale            30 Aug, 2017         Modified to add AWC link and add attachments to emails
//  TCS Development Team    22 Sep, 2017         Corrected the variable name for target attachments map
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_notifyAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    GET_ItemRevisionUnqPtr targetRevisionUnqPtr;

    int iNoOfColumns = 0;
    int iWaitTime = 2;

    PROP_value_type_t propType;

    string sTime = "";
    string sHTMLTotalPage = "";
    string sHTMLTitle = "";
    string sHTMLAWCLink = "";
    string sHTMLHeader = "";
    string sHTMLBody = "";
    string sHTMLFooter1 = "";
    string sHtmlTimeStamp = "";
    string strSubject ="";
    string sPropValue ="";
    string sSiteName = "";
    string sBomLineQty = "";
    string sBomLineSeqNo = "";
    string sUnqTmpDir = "";

    const string sHTMLStart = "<!DOCTYPE html><head><title></title></head><body bgcolor=\"#FFFFFF\">";
    const string sHTMLEnd = "<br>This is autogenerated Mail. Please do not reply<br><hr></body>\n</html>";
    const string slineAsSeperator = "<hr WIDTH=100% >\n";

    time_t rawtime;

    vector<propNameAndValues> vEmailHeaderProps;
    vector<propNameAndValues> vEmailBodyProps;
    vector<propNameAndValues> vEmailFooter1Props;

    vector<string> vPrefValues;
    vector<string> vEmailPropValues;
    vector<string> vPropNames;
    vector<string> vReleaseStatusList;
    vector<string> vGroupRole;
    vector<string> vDatasetTypes;
    vector<string> vNamedRefTypes;
    vector<string> vTablePropsNames;
    vector<string> vTablePropColumns;
    vector<string> vTableProperties;
    vector<int> vServerPrefValues;

    vector<GET_POM_objectUnqPtr> vTargetAttachmentsUnqPtr;

    LOG_TRACE ( logger, "START : GET6_notifyAH_impl" );

    // Get property name from argument
    if ( mArgumentsMap.find ( TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[TYPE_ARG].empty() )
    {
        THROW ( string ( "The argument \"" ) + TYPE_ARG + string ( "\" is not provided or has empty value" ) );
    }

    // User can mention properties or resource pool or recipient's email id    
    if ( ( mArgumentsMap.find ( EMAIL_PROP_NAME_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap[EMAIL_PROP_NAME_HANDLER_ARG].empty() ) &&
         ( mArgumentsMap.find ( RESOURCE_POOL_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap [RESOURCE_POOL_HANDLER_ARG].empty() ) &&
         ( mArgumentsMap.find ( TO_EMAIL_ID_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap [TO_EMAIL_ID_HANDLER_ARG].empty() ) )
    {
         THROW ( string ( "At least one among these arguments \"" ) + EMAIL_PROP_NAME_HANDLER_ARG + string ( " or " ) + RESOURCE_POOL_HANDLER_ARG + string ( " or " ) + TO_EMAIL_ID_HANDLER_ARG + string ( "\" has to be provided" ) );
    }

    // Subject is mandatory
    if ( mArgumentsMap.find ( SUBJECT_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap[SUBJECT_HANDLER_ARG].empty() )
    {
        THROW ( string ( "The argument \"" ) + SUBJECT_HANDLER_ARG + string ( "\" is not provided or has empty value" ) );
    }

    // EMAIL_TITLE_HANDLER_ARG is mandatory
    if ( mArgumentsMap.find ( EMAIL_TITLE_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap[EMAIL_TITLE_HANDLER_ARG].empty() )
    {
        THROW ( string ( "The argument \"" ) + EMAIL_TITLE_HANDLER_ARG + string ( "\" is not provided or has empty value" ) );
    }

    // EMAIL_BODY_PROPS_HANDLER_ARG is mandatory    
    if ( mArgumentsMap.find ( EMAIL_BODY_PROPS_HANDLER_ARG ) == mArgumentsMap.end() || mArgumentsMap[EMAIL_BODY_PROPS_HANDLER_ARG].empty() )
    {
        THROW ( string ( "The argument \"" ) + EMAIL_BODY_PROPS_HANDLER_ARG + string ( "\" is not provided or has empty value" ) );
    }

    // If EMAIL_BODY_PROPS_HANDLER_ARG value contains bom value then Revision rule arg is mandatory 
    if ( mArgumentsMap[EMAIL_BODY_PROPS_HANDLER_ARG].find ( BODY_BOM_PROP ) != string::npos )
    {
        // If the  email body prop is "bom" then keep this as mandatory
        if ( mArgumentsMap.find ( REVISION_RULE_ARG ) == mArgumentsMap.end() || mArgumentsMap[REVISION_RULE_ARG].empty() )
        {
            THROW ( string ( BODY_BOM_PROP ) + " is passed as an argument value. So the \""  + REVISION_RULE_ARG + string ( "\" argument should be provided" ) );
        }
    }

    // Get dataset type of attachment
    if ( mArgumentsMap.find ( DATASET_TYPE_ARG ) != mArgumentsMap.end() && ! mArgumentsMap[DATASET_TYPE_ARG].empty() )
    {
        //Get named reference type
        if ( mArgumentsMap.find ( REFERENCE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[REFERENCE_TYPE_ARG].empty() )
        {
            THROW ( string ( DATASET_TYPE_ARG ) + " is passed as an argument value. So the \""  + REFERENCE_TYPE_ARG + string ( "\" argument should be provided" ) );
        }
        GET_splitString ( mArgumentsMap[DATASET_TYPE_ARG], COMMA_CHARACTER, vDatasetTypes );
        GET_splitString ( mArgumentsMap[REFERENCE_TYPE_ARG], COMMA_CHARACTER, vNamedRefTypes );
    }

    // Get root task and the attachments
    GET_EPMTaskUnqPtr currentTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );
    GET_EPMTaskUnqPtr rootTaskUnqPtr = currentTaskUnqPtr->getRootTask();
    vTargetAttachmentsUnqPtr = rootTaskUnqPtr->askAttachments ( EPM_target_attachment );
    
    // Get the target Revision Object
    // Note : Only the first found target of the given type will be fetched
    for ( size_t iIndex = 0; iIndex < vTargetAttachmentsUnqPtr.size(); ++iIndex )
    {
        // Comparing the types... if they are not matching, continue
        if ( vTargetAttachmentsUnqPtr[iIndex]->askTypeName().compare ( mArgumentsMap[TYPE_ARG] ) != 0 )
        {
            continue;
        }
        targetRevisionUnqPtr = GET_ItemRevision::getInstance ( vTargetAttachmentsUnqPtr[iIndex]->getTag() );
        break;
    }
    
    // Check the revision tag
    if ( targetRevisionUnqPtr.get() != NULL )
    {
        string sAttachmentFilePath = "";
        string sRelationType = "";
        string fileFormatType = "=B";

        vector<string> vEmailIds;
        vector<string> vEmailPrefNames;
        vector<string> vExportedFilePaths;

        vector<GET_POM_userUnqPtr> vUserUnqPtr;

        ofstream fileAttachmentPtr;

        GET_ItemRevisionShrPtr itemRevShrPtr ( move ( targetRevisionUnqPtr ) );

        // Get the email ids from given Teamcenter property name
        if ( mArgumentsMap.find ( EMAIL_PROP_NAME_HANDLER_ARG ) != mArgumentsMap.end() )
        {
            // Retrieving email ids and sending mail
            propType = itemRevShrPtr->askPropValueType ( mArgumentsMap[EMAIL_PROP_NAME_HANDLER_ARG] );
            if ( propType != PROP_string )
            {
                THROW ( "Invalid Property Type !!! \"" + mArgumentsMap[EMAIL_PROP_NAME_HANDLER_ARG] + "\" is not a string property" );
            }

            if ( itemRevShrPtr->isPropList ( mArgumentsMap[EMAIL_PROP_NAME_HANDLER_ARG] ) )
            {
                   vector<string> vEmailIds = itemRevShrPtr->getPropStrings ( mArgumentsMap[EMAIL_PROP_NAME_HANDLER_ARG] );
                   for ( int iInx = 0; iInx < vEmailIds.size(); iInx++ )
                   {
                       if ( ! vEmailIds[iInx].empty() && vEmailIds[iInx].find ( "@" ) != string::npos && vEmailIds[iInx].find ( ".com" ) != string::npos )
                       {
                           vEmailPropValues.push_back ( vEmailIds[iInx] );
                           LOG_TRACE ( logger, "Sending email to : " + vEmailIds[iInx] );
                       }
                   }
            }
            else
            {
                string sEmailId = itemRevShrPtr->getPropString ( mArgumentsMap[EMAIL_PROP_NAME_HANDLER_ARG] );
                if ( ! sEmailId.empty() && sEmailId.find ( "@" ) != string::npos && sEmailId.find ( ".com" ) != string::npos )
                {
                    vEmailPropValues.push_back ( sEmailId );
                    LOG_TRACE ( logger, "Sending email to : " + sEmailId );
                }
            }
        }

        // Get the email ids of approver role and send email to them
        if ( mArgumentsMap.find ( RESOURCE_POOL_HANDLER_ARG ) != mArgumentsMap.end() )
        {
            GET_splitString ( mArgumentsMap[RESOURCE_POOL_HANDLER_ARG], COLON_SEPERATOR, vGroupRole );
            if ( vGroupRole.size() == 2 )
            {
                vector<GET_GroupMemberUnqPtr> vGrpMembers = GET_GroupMember::find ( vGroupRole[0], vGroupRole[1] );
                for ( int iInx = 0; iInx < vGrpMembers.size(); iInx++ )
                {
                    string sEmailId = vGrpMembers[iInx]->getUser()->getPerson()->getEmailId();
                    if ( ! sEmailId.empty() && sEmailId.find ( "@" ) != string::npos && sEmailId.find ( ".com" ) != string::npos )
                    {
                        vEmailPropValues.push_back ( sEmailId );
                        LOG_TRACE ( logger, "Sending email to : " + sEmailId );
                    }
                }
            }
        }

        // Get the Email ID directly from the handler arguments
        if ( mArgumentsMap.find ( TO_EMAIL_ID_HANDLER_ARG ) != mArgumentsMap.end() )
        {
            GET_splitString ( mArgumentsMap[TO_EMAIL_ID_HANDLER_ARG], COMMA_CHARACTER, vEmailIds );

            for ( int iInx = 0; iInx < vEmailIds.size(); iInx++ )
            {
                vector<string> vEmailIdValues;
                if ( vEmailIds[iInx].compare ( PROCESS_OWNER_ATTR ) == 0 )
                {
                    // Retrieving email ids and sending mail
                    GET_POM_userUnqPtr initiatorUnqPtr = GET_POM_user::getInstance ( ( rootTaskUnqPtr->getPropTag ( OWNING_USER_ATTR ) )->getTag() );
                    vEmailIdValues.push_back ( initiatorUnqPtr->getPerson()->getEmailId() );
                }
                else if ( vEmailIds[iInx].compare ( REVIEWER_ATTR ) == 0 )
                {
                    vUserUnqPtr = currentTaskUnqPtr->askReviewers();
                    for ( int iKnx = 0; iKnx < vUserUnqPtr.size(); iKnx++ )
                    {
                        vEmailIdValues.push_back ( vUserUnqPtr[iKnx]->getPerson()->getEmailId() );
                    }
                }
                else
                {
                    vEmailIdValues.push_back ( vEmailIds[iInx] );
                }

                for ( int iKnx = 0; iKnx < vEmailIdValues.size(); iKnx++ )
                {
                    if ( ! vEmailIdValues[iKnx].empty() && vEmailIdValues[iKnx].find ( "@" ) != string::npos && vEmailIdValues[iKnx].find ( ".com" ) != string::npos )
                    {
                        LOG_TRACE ( logger, "Sending email to : " + vEmailIdValues[iKnx] );
                        vEmailPropValues.push_back ( vEmailIdValues[iKnx] );
                    }
                }
            }
        }

        // Get the Email ID from the preference,  if the argument is supplied
        if ( mArgumentsMap.find ( TO_EMAIL_PREF_HANDLER_ARG ) != mArgumentsMap.end() )
        {
            GET_splitString ( mArgumentsMap[TO_EMAIL_PREF_HANDLER_ARG], COMMA_CHARACTER, vEmailPrefNames );
            for ( int iInx = 0; iInx < vEmailPrefNames.size(); iInx++ )
            {
                vector<string> vEmailPrefValues;

                try
                {
                    getStringPrefValues ( vEmailPrefNames[iInx], vEmailPrefValues );
                }
                catch ( IFail &ex )
                {
                    LOG_ERROR ( logger, "Exception in getting Preference value " + ex.getMessage() );
                }

                for ( int iKnx = 0; iKnx < vEmailPrefValues.size(); iKnx++ )
                {
                    if ( ! vEmailPrefValues[iKnx].empty() && vEmailPrefValues[iKnx].find ( "@" ) != string::npos && vEmailPrefValues[iKnx].find ( ".com" ) != string::npos )
                    {
                        LOG_TRACE ( logger, "Sending email to : " + vEmailPrefValues[iKnx] );
                        vEmailPropValues.push_back ( vEmailPrefValues[iKnx] );
                    }
                }
            }
        }

        //preference to get the wait time to transfer the excel files to tmp location
        getIntPrefValues ( GET_WAITTIME_FOR_FILE_TRANSFER, vServerPrefValues );

        if ( vEmailPropValues.size() > 0 )
        {
            // Get the site id
            int iSiteId = GET_Site::getLocalID();
            if ( iSiteId ) 
            {        
                GET_SiteUnqPtr siteUnqPtr = GET_Site::find ( iSiteId );   
                if ( siteUnqPtr != NULL ) 
                {
                    sSiteName = siteUnqPtr->getName();
                }
            }

            if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) != mArgumentsMap.end() && ! mArgumentsMap[RELATION_TYPE_ARG].empty() )
            {
                sRelationType = mArgumentsMap[RELATION_TYPE_ARG];
            }

            if ( vDatasetTypes.size() > 0 )
            {
                vector<GET_WorkspaceObjectUnqPtr> vWSObjects = GET_ImanRelation::listRelatedWsObjects ( itemRevShrPtr, sRelationType );
                for ( size_t iIndex = 0; iIndex < vWSObjects.size(); iIndex++ )
                {
                    if ( ! GET_isInVector ( vDatasetTypes, vWSObjects[iIndex]->getType() ) )
                    {
                       continue;
                    }
                    // Create folder in Temp directory and delete after the usage
                    sUnqTmpDir = string ( GET_SYSAPI_getTempDir() ) + string ( GET_SYSAPI_getFileSeparator() ) + "GET_NOTIFY_" + GET_intToString ( rand() );
                    if ( GET_SYSAPI_createDirectory ( sUnqTmpDir.c_str(), -1 ) != 0 )
                    {
                        THROW ( "Unable to create a TEMP directory at the path : " + sUnqTmpDir );
                    }

                    GET_DatasetUnqPtr datasetPtr = GET_Dataset::getInstance ( vWSObjects[iIndex]->getTag() );
                    for ( size_t jIndex = 0; jIndex < vNamedRefTypes.size(); jIndex++ )
                    {
                        vector<GET_POM_objectUnqPtr> vNamedRefObjects = datasetPtr->getNamedRefs ( vNamedRefTypes[jIndex] );
                        for ( size_t kIndex = 0; kIndex < vNamedRefObjects.size(); kIndex++ )
                        {
                            string sOriginalFileName = "";
                            string sDSNamedRefFullPath = "";

                            sOriginalFileName = vNamedRefObjects[kIndex]->getPropertyString ( ORIGINALFILENAME_ATTR ); 
                            // Create the full file path for exporting the Dataset Named Referenced file
                            sDSNamedRefFullPath = sUnqTmpDir +  string ( GET_SYSAPI_getFileSeparator() ) + sOriginalFileName;
                            if ( GET_isInVector ( vExportedFilePaths, sDSNamedRefFullPath ) )
                            {
                                size_t sfileExt = sDSNamedRefFullPath.rfind ( DOT_CHARACTER );
                                sDSNamedRefFullPath.insert ( sfileExt, GET_intToString ( rand() ) );
                            }
                            datasetPtr->exportNamedReference ( vNamedRefTypes[jIndex], sDSNamedRefFullPath.c_str() );
                            vExportedFilePaths.push_back ( sDSNamedRefFullPath ); 
                        } 

                        //Check the Preference value
                        // Ashok C - Removing vServerPrefValues[0] != NULL to avoid Linux compilation error
                        //if ( vServerPrefValues.size() > 0 && vServerPrefValues[0] != NULL )
                        if ( vServerPrefValues.size() > 0 )
                        {
                            iWaitTime = vServerPrefValues[0];
                            //Sleep the program for 2 sec for exporting to resolve async issue
                            GET_SYSAPI_sleep( iWaitTime );
                        }
                        else
                        {
                           LOG_DEBUG ( logger, "GET_WAITTIME_FOR_FILE_TRANSFER preference value is not set.Using the default value :"+ iWaitTime );
                           GET_SYSAPI_sleep ( iWaitTime );
                        }
                    }
                }
            }
            if ( vExportedFilePaths.size() > 0 )
            {
                // Create the file name for the mail attachment list file
                sAttachmentFilePath = sUnqTmpDir + string ( GET_SYSAPI_getFileSeparator() ) + "attachment_list_" + GET_intToString ( rand() ) + ".txt";

                // Create the body file
                fileAttachmentPtr.open ( sAttachmentFilePath.c_str() );
                if ( ! fileAttachmentPtr.is_open() )
                {
                      string sMsg = "Unable to create a temporary file with the name " + sAttachmentFilePath + " for creating the Mail Attachment";
                      THROW ( sMsg );
                }
                for ( size_t iIndex = 0; iIndex < vExportedFilePaths.size(); iIndex++ )
                {
                     fileAttachmentPtr << vExportedFilePaths[iIndex].c_str() << fileFormatType.c_str() << endl;
                }
                fileAttachmentPtr.close(); 
            }

            // Get the Subject of the email and append Site id to the email subject
            strSubject = string ( OPEN_SQUARE_CHAR_VALUE ) + sSiteName + string ( CLOSE_SQUARE_CHAR_VALUE ) ;
            strSubject = mArgumentsMap[SUBJECT_HANDLER_ARG] + " " + strSubject;

            // Get the Header properties and push into a vector
            vPropNames.clear();
            GET_splitString ( mArgumentsMap[EMAIL_HEADER_PROPS_HANDLER_ARG], COLON_SEPERATOR, vPropNames );
            for ( int iIndex = 0; iIndex < vPropNames.size(); iIndex++ )
            {    
                string sPropDisplayName = itemRevShrPtr->getPropDisplayName ( vPropNames[iIndex] );
                sPropValue = itemRevShrPtr->getPropValueAsString ( vPropNames[iIndex] );
                vEmailHeaderProps.push_back ( propNameAndValues ( sPropDisplayName, sPropValue ) );
            }

            // Get the Title of the email:converting sEmailTitle to upper case and framing HTML for sEmailTitle section
            transform ( mArgumentsMap[EMAIL_TITLE_HANDLER_ARG].begin(), mArgumentsMap[EMAIL_TITLE_HANDLER_ARG].end(), mArgumentsMap[EMAIL_TITLE_HANDLER_ARG].begin(), ::toupper );
            sHTMLAWCLink = "<td valign=top align=left ><b><font size=+1><a href=" + itemRevShrPtr->getAWCUrl() + ">Active Workspace link to " + itemRevShrPtr->getPropString ( OBJECT_STRING_ATTR ) +
            "</a></font></b></td>"; 
            sHTMLTitle = "<b><font size=+2>" + mArgumentsMap[EMAIL_TITLE_HANDLER_ARG] + "</font></b><br>\n";

            // Framing HTML tags for pushing header properties
            if( mArgumentsMap.find ( EMAIL_HEADER_PROPS_HANDLER_ARG ) != mArgumentsMap.end() )
            {
                sHTMLHeader ="<hr><table BORDER=0 cellpadding=2 cellspacing=0 WIDTH=\"100%\">\n<tr>\n";
                iNoOfColumns = 0;
                for ( vector<propNameAndValues>::iterator it = vEmailHeaderProps.begin(); it != vEmailHeaderProps.end(); ++it )
                {
                    sHTMLHeader = sHTMLHeader + "<td valign=top align=left ><b>" + ( *it ).sPropName + "</b>&nbsp:&nbsp" + ( *it ).sPropValue + "</td>";
                    iNoOfColumns++;
                    if ( iNoOfColumns == 3 )
                    {
                        sHTMLHeader = sHTMLHeader + "</tr>\n<tr>";
                        iNoOfColumns = 0;
                    }
                }
                sHTMLHeader = sHTMLHeader + "</tr>\n<tr>";
                sHTMLHeader = sHTMLHeader +  "</tr>" + "</table>\n";
            }
            // Get the body properties and push into vector
            vPropNames.clear();
            GET_splitString ( mArgumentsMap[EMAIL_BODY_PROPS_HANDLER_ARG], COLON_SEPERATOR, vPropNames );
            for ( int iIndex = 0; iIndex < vPropNames.size(); iIndex++ )
            {
                // If the emailBodyProp doesn't contains BOM as value then this loop will be executed    
                if ( vPropNames[iIndex].compare ( BODY_BOM_PROP ) != 0 )
                {
                    PROP_type_t propTypeObj = itemRevShrPtr->askPropertyType( vPropNames[iIndex] );
                    if( propTypeObj == PROP_table )
                    {
                        vTableProperties.push_back( vPropNames[iIndex] );
                        continue;
                    }
                    string sPropDisplayName = itemRevShrPtr->getPropDisplayName ( vPropNames[iIndex] );
                    string sPropValue = itemRevShrPtr->getPropValueAsString ( vPropNames[iIndex] );
                    vEmailBodyProps.push_back ( propNameAndValues ( sPropDisplayName, sPropValue ) );
                }
                else
                {
                    // Create a BOM Window and set topline and get the children
                    GET_BOMWindowUnqPtr bomWindowUnqPtr = GET_BOMWindow::create();
                    bomWindowUnqPtr->setRevisionRule ( mArgumentsMap[REVISION_RULE_ARG] );
                    GET_BOMViewRevisionShrPtr bomViewRevShrPtr;
        
                    GET_BOMLineUnqPtr BOMLineUnqPtr = bomWindowUnqPtr->setTopLine ( itemRevShrPtr, bomViewRevShrPtr );
                    vector<GET_BOMLineUnqPtr> vFirstChildLinesVector = BOMLineUnqPtr->getChildren();

                    // Framing HTML tags for pushing body properties                
                    sHTMLBody = sHTMLBody + "<li style=\"color:#2035E5\"><b><i><font size=+1>Following Parts in Preliminary Assembly are Released</font></i></b><br/></li>";
                    sHTMLBody = sHTMLBody + "</tr>\n<tr>";
                    sHTMLBody = sHTMLBody  + "<table style=\"width: 60%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 60%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td> Part ID </td> <td> Part Name </td> <td> Quantity </td> <td> FindNumber </td> <td> Release Status </td></tr>";
        
                    // Get the Child Line and its release status
                    for ( size_t iIndex = 0; iIndex < vFirstChildLinesVector.size(); iIndex++ )
                    {
                        GET_ItemRevisionUnqPtr getChildRevUnqPtr = vFirstChildLinesVector[iIndex]->getItemRevision();
                        GET_ItemRevisionShrPtr getChildRevShrPtr ( move ( getChildRevUnqPtr ) ); 
                        GET_WorkspaceObjectShrPtr getWorkspaceShrPtr ( move ( GET_WorkspaceObject::getInstance ( getChildRevShrPtr->getTag() ) ) );

                        // Get the released status    
                        vReleaseStatusList = getWorkspaceShrPtr->getReleaseStatusList();
        
                        // Use the getStringProp
                        sBomLineSeqNo = vFirstChildLinesVector[iIndex]->getStringProperty ( bomAttr_occSeqNo );
                        sBomLineQty = vFirstChildLinesVector[iIndex]->getStringProperty ( bomAttr_occQty );
        
                        // Add find no, quantity and release status of the released bom in the email body 
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + getChildRevShrPtr->getId() + "</b></td>";
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + getChildRevShrPtr->getName() + "</b></td>";
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + sBomLineQty + "</b></td>";
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + sBomLineSeqNo + "</b></td>";

                        if ( ! vReleaseStatusList.empty() )
                        {
                            for ( int iInx = 0; iInx < vReleaseStatusList.size(); iInx++ ) 
                            {
                                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + vReleaseStatusList[iInx]  +"</b></td>";
                            }
                        }
                        sHTMLBody = sHTMLBody + "</tr>\n<tr>";
                    }
                    sHTMLBody = sHTMLBody +  "</table>\n";
                }
            }

            // To print the properties and values in body
            if ( vEmailBodyProps.size() > 0 )
            {
                int columns = 0;
                
                string sHTMLBodyTableHeader = "";
                string sHTMLBodyTableData = "";
                
                vector<string> table;

                sHTMLBody = "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80;\">";
                for ( vector<propNameAndValues>::iterator it = vEmailBodyProps.begin(); it != vEmailBodyProps.end(); ++it )
                {
                    // Framing HTML tags for pushing body properties
                    sHTMLBodyTableHeader = sHTMLBodyTableHeader  + "<th style=\"color: white;\">" + ( *it ).sPropName + "</th>";
                    sHTMLBodyTableData = sHTMLBodyTableData  + "<td><b>" + ( *it ).sPropValue + "</b></td>";
                    columns++;
                    if( columns%8 == 0 )
                    {
                        table.push_back( sHTMLBody + sHTMLBodyTableHeader + "</tr>" + "<tr>" + sHTMLBodyTableData + "</tr>" );
                        sHTMLBodyTableHeader = "";
                        sHTMLBodyTableData = "";
                        sHTMLBody = "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80;\">";
                    }
                }
                if ( table.size() > 0)
                {
                    sHTMLBody = "";
                    for ( int iIndex = 0; iIndex < table.size(); iIndex++ )
                    {
                        sHTMLBody = sHTMLBody + table[iIndex] + "</tbody></table><br/>";
                    }
        
                    if ( columns%8 != 0 )
                    {
                        sHTMLBody = sHTMLBody + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80;\">" + sHTMLBodyTableHeader + "</tr>" + "<tr>" + sHTMLBodyTableData + "</tr>" + "</tbody></table><br/>";
                    }
                    sHTMLBody = sHTMLBody + "<br/><br/>";
                }
                else
                {
                    sHTMLBody = sHTMLBody + sHTMLBodyTableHeader + "</tr>" + "<tr>" + sHTMLBodyTableData + "</tr></tbody></table><br/><br/>";
                }
            }

            if( vTableProperties.size() > 0 )
            {
                vector<string> vTablePropertiesColumns;

                for ( int iIndex = 0; iIndex < vTableProperties.size(); iIndex++ )
                {
                    vTablePropertiesColumns.clear();
                    if ( mArgumentsMap.find ( vTableProperties[iIndex] + ".columns" ) == mArgumentsMap.end() || mArgumentsMap[vTableProperties[iIndex] + ".columns"].empty() )
                    {
                         THROW ( string ( "The argument \"" ) + vTableProperties[iIndex] + ".columns" + string ( "\" is not provided or has empty value" ) );
                    }
                    GET_splitString ( mArgumentsMap[vTableProperties[iIndex] + ".columns"], COLON_SEPERATOR, vTablePropertiesColumns );
                    vector<GET_POM_objectUnqPtr> vPomObjectUnqPtrs = itemRevShrPtr->getPropTags( vTableProperties[iIndex] );
                    if ( vPomObjectUnqPtrs.size() > 0 )
                    {
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + itemRevShrPtr->getPropDisplayName ( vTableProperties[iIndex] ) + "</b></td>";
                        sHTMLBody = sHTMLBody  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\">";

                        //column will be get6PartNo, get6Disposition, get6ChangeDesc
                        for ( int iInx = 0; iInx < vTablePropertiesColumns.size(); iInx++ )
                        {
                            sHTMLBody = sHTMLBody + "<td>" + vPomObjectUnqPtrs[0]->getPropertyDisplayName ( vTablePropertiesColumns[iInx] ) + "</td>";
                        }

                        sHTMLBody = sHTMLBody + "</tr>"; 
                        for ( int iInx = 0; iInx < vPomObjectUnqPtrs.size(); iInx++ )
                        {
                            sHTMLBody = sHTMLBody + "<tr>";
                            for ( int jInx = 0; jInx < vTablePropertiesColumns.size(); jInx++ )
                            {
                                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + vPomObjectUnqPtrs[iInx]->getPropertyString ( vTablePropertiesColumns[jInx] ) + "</b></td>";
                            }
                            sHTMLBody = sHTMLBody + "</tr>";
                        }
                        sHTMLBody = sHTMLBody  + "</tbody></table><br/>";    
                    }
                }
            }
            //To Add Tables for table properties and/or relation properties
            if ( mArgumentsMap.find ( BODY_TABLE_PROPS ) != mArgumentsMap.end() &&  ! mArgumentsMap[BODY_TABLE_PROPS].empty() )
            {
                if( mArgumentsMap.find ( BODY_TABLE_COLUMNS ) == mArgumentsMap.end() || mArgumentsMap[BODY_TABLE_COLUMNS].empty() )
                {
                    THROW ( string ( "The argument \"" ) + BODY_TABLE_COLUMNS + string ( "\" is not provided or has empty value" ) );
                }
                GET_splitString ( mArgumentsMap[BODY_TABLE_PROPS], COLON_SEPERATOR, vTablePropsNames );
                GET_splitString ( mArgumentsMap[BODY_TABLE_COLUMNS], COLON_SEPERATOR, vTablePropColumns );
                for ( int iIndex = 0; iIndex < vTablePropsNames.size(); iIndex++ )
                {
                    vector<GET_POM_objectUnqPtr> vPomObjectUnqPtrs = itemRevShrPtr->getPropTags( vTablePropsNames[iIndex] );
                    if ( vPomObjectUnqPtrs.size() > 0 )
                    {
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + itemRevShrPtr->getPropDisplayName (vTablePropsNames[iIndex] ) + "</b></td>";
                        sHTMLBody = sHTMLBody  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\">";
                        for ( int iInx = 0; iInx < vTablePropColumns.size(); iInx++ )
                        {
                            sHTMLBody = sHTMLBody + "<td>" + vPomObjectUnqPtrs[0]->getPropertyDisplayName ( vTablePropColumns[iInx] ) + "</td>";
                        }
                        sHTMLBody = sHTMLBody + "</tr>";                    
                        for ( int iInx = 0; iInx < vPomObjectUnqPtrs.size(); iInx++ )
                        {
                            sHTMLBody = sHTMLBody + "<tr>";
                            for ( int jInx = 0; jInx < vTablePropColumns.size(); jInx++ )
                            {
                                GET_WorkspaceObjectUnqPtr wsObjectUnqPtr = GET_WorkspaceObject::getInstance ( vPomObjectUnqPtrs[iInx]->getTag() );
                                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + wsObjectUnqPtr->getPropValueAsString ( vTablePropColumns[jInx] ) + "</b></td>";
                            }
                            sHTMLBody = sHTMLBody + "</tr>";
                        }
                        sHTMLBody = sHTMLBody  + "</tbody></table><br/>";
                    }
                }
            }

            // Get the footer1 properties and push into vector
            if ( mArgumentsMap.find ( EMAIL_FOOTER1_PROPS_HANDLER_ARG ) != mArgumentsMap.end() && ! mArgumentsMap[EMAIL_FOOTER1_PROPS_HANDLER_ARG].empty() )
            {
                vPropNames.clear();
                GET_splitString ( mArgumentsMap[EMAIL_FOOTER1_PROPS_HANDLER_ARG], COLON_SEPERATOR, vPropNames );
                for ( int iKnx = 0; ! vPropNames.empty() && iKnx < vPropNames.size(); iKnx++ )
                {
                    string sPropDisplayName1 = itemRevShrPtr->getPropDisplayName ( vPropNames[iKnx] ); 
                    string sPropValue1 = itemRevShrPtr->getPropValueAsString ( vPropNames[iKnx] );
                    vEmailFooter1Props.push_back ( propNameAndValues ( sPropDisplayName1, sPropValue1 ) ); 
                }
        
                // Framing HTML tags for pushing footer1 properties
                if ( ! mArgumentsMap[EMAIL_FOOTER1_TITLE_HANDLER_ARG].empty() )
                {
                    sHTMLFooter1 = "<table BORDER=0 cellpadding=2 cellspacing=2 WIDTH=\"100%\"><tr><td valign=top align=left ><b><font size=+2>" 
                                 + mArgumentsMap[EMAIL_FOOTER1_TITLE_HANDLER_ARG] + "</b></td></tr><tr>";
                    iNoOfColumns = 0;
                    for ( vector<propNameAndValues>::iterator it = vEmailFooter1Props.begin(); it != vEmailFooter1Props.end(); ++it )
                    {
                        sHTMLFooter1 = sHTMLFooter1 + "<td valign=top align=left ><b>" + (*it).sPropName + ":" + "</b></td>";
                        sHTMLFooter1 = sHTMLFooter1 + "<td valign=top> " + (*it).sPropValue + "</td>";
                        iNoOfColumns = iNoOfColumns + 2;
        
                        if ( iNoOfColumns == 6 )
                        {
                            sHTMLFooter1 = sHTMLFooter1 + "</tr>\n<tr>";
                            iNoOfColumns = 0;
                        }
                    }
                    sHTMLFooter1 = sHTMLFooter1 +  "</tr>" + "</table>\n";
                }
            }

            // Getting current time and framing HTML tags to provide time stamp
            time ( &rawtime );
            sTime = string ( ctime ( &rawtime ) );
            sHtmlTimeStamp = "<br>Report Generated at: " + sTime + " Local Time Zone \n";           
        
            // Adding provision for review task, if present.
            if ( currentTaskUnqPtr->getType().compare ( PERFORM_SIGNOFF_TASK_TYPE ) == 0 )
            {
                if ( mArgumentsMap.find ( REPORT_HANDLER_ARG ) != mArgumentsMap.end() )
                {
                    // Structure variable declaration
                    ReviewTaskResults reviewDecisionResults;
        
                    vUserUnqPtr = currentTaskUnqPtr->askReviewers();
                    if ( vUserUnqPtr.size() > 0 )
                    {
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + "Release Level : " + currentTaskUnqPtr->getName() + "</b></td>";
                        sHTMLBody = sHTMLBody  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Reviewer</td><td>Decision</td><td>Decision Date</td><td>Comments</td></tr>";
                        for ( int iInx = 0; iInx < vUserUnqPtr.size(); iInx++ )
                        {
                            GET_POM_userShrPtr UserShrPtr ( move ( vUserUnqPtr[iInx] ) );
        
                            currentTaskUnqPtr->getDecision ( UserShrPtr, reviewDecisionResults );
        
                            if ( ( reviewDecisionResults.sDecision == APPROVED_DECISION_ATTR ) || ( reviewDecisionResults.sDecision == REJECT_DECISION_ATTR ) )
                            {
                                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + UserShrPtr->getName() + " (" + UserShrPtr->getID() + ")" + "</b></td>";    
                                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + reviewDecisionResults.sDecision + "</b></td>";
                                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + reviewDecisionResults.decisionDatePtr->toString() + "</b></td>";
                                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + reviewDecisionResults.sComments + "</b></td></tr>";
                            }
                        }
                        //sHTMLBody = sHTMLBody + "</tr>\n<tr>";
                        sHTMLBody = sHTMLBody  + "</tbody></table><br/>";
                    }
                }
            }

            //Participant Tab
            if ( mArgumentsMap.find ( PARTICIPANTS_ARG ) != mArgumentsMap.end() )
            {   
                map<string, vector<GET_ParticipantShrPtr> > mParticipantsMap = itemRevShrPtr->getAllParticipants();
                if ( mParticipantsMap.size() > 0 )
                {
                    sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + "Participants" + "</b></td>";
                    sHTMLBody = sHTMLBody  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\">";
                    sHTMLBody = sHTMLBody + "<td>" + "Participant" + "</td>";
                    sHTMLBody = sHTMLBody + "<td>" + "User" + "</td>";
                    sHTMLBody = sHTMLBody + "<td>" + "Group" + "</td>";
                    sHTMLBody = sHTMLBody + "<td>" + "Role" + "</td>";
                    sHTMLBody = sHTMLBody + "</tr>";                    
                    for ( std::map<string, vector<GET_ParticipantShrPtr> >::iterator participantMapIterator = mParticipantsMap.begin();\
                    participantMapIterator != mParticipantsMap.end(); ++participantMapIterator )
                    {
                        vector<GET_ParticipantShrPtr> participantsShrPtr = participantMapIterator->second;    
                        for ( int jInx = 0; jInx <participantsShrPtr.size() ; jInx++ )
                        {
                            GET_POM_objectUnqPtr pObjectUnqPtr = participantsShrPtr[jInx]->getAssignee();
                            GET_GroupMemberUnqPtr groupMemberPtr = participantsShrPtr[jInx]->getParticipantGroupMember();
                            if( groupMemberPtr.get() == NULL )
                            {
                                continue;
                            }
                            sHTMLBody = sHTMLBody + "<tr><td valign=top align=left ><b>" + participantsShrPtr[jInx]->askTypeDisplayName() + "</b></td>";
                            sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + groupMemberPtr->getUser()->getName() + " (" + groupMemberPtr->getUser()->getID() + ")" + "</b></td>";
                            sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + groupMemberPtr->getGroup()->getGroupFullName() + "</b></td>";
                            sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + groupMemberPtr->getRole()->getRoleName() + "</b></td></tr>";
                        }
                    }
                    sHTMLBody = sHTMLBody  + "</tbody></table><br/>";
                }
            }

            if ( mArgumentsMap.find ( EMAIL_BODY_WORKFLOW_TAB_ARG ) != mArgumentsMap.end() )
            {
                vector<string> vWfPropNames;
        
                sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + "Review" + "</b></td>";
                sHTMLBody = sHTMLBody  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\">";
                sHTMLBody = sHTMLBody  + "<td>Task</td><td>Reviewer</td><td>Decision</td><td>Decision Date</td><td>Comments</td></tr>";
        
                GET_EPMTaskShrPtr rootTaskShrPtr ( move ( rootTaskUnqPtr ) );
        
                sHTMLBody = sHTMLBody + recurseWfSubTasks ( rootTaskShrPtr );
                sHTMLBody = sHTMLBody  + "</tbody></table><br/>";
            }
        
            sHTMLTotalPage = sHTMLStart + sHTMLTitle + slineAsSeperator + sHTMLAWCLink;
            if ( ! sHTMLHeader.empty() )
            {
                sHTMLTotalPage = sHTMLTotalPage + sHTMLHeader;
            }
            sHTMLTotalPage = sHTMLTotalPage + string ( sHTMLBody );
            if ( ! sHTMLFooter1.empty() )
            {
                sHTMLTotalPage = sHTMLTotalPage + slineAsSeperator + sHTMLFooter1;
            } 
            sHTMLTotalPage = sHTMLTotalPage + slineAsSeperator + sHtmlTimeStamp + sHTMLEnd;

            // Send the Email
            sendMailAsHtml ( vEmailPropValues, strSubject, sHTMLTotalPage, sAttachmentFilePath );

            //Sleep the program for 2 sec 
            // Ashok C - Removing vServerPrefValues[0] != NULL to avoid Linux compilation error
			//if ( vServerPrefValues.size() > 0 && vServerPrefValues[0] != NULL )
			if ( vServerPrefValues.size() > 0 )
            {
                iWaitTime = vServerPrefValues[0];
                GET_SYSAPI_sleep ( iWaitTime );
            }
            else
            {
                LOG_DEBUG ( logger, "GET_WAITTIME_FOR_FILE_TRANSFER preference value is not set.Using the default value :"+ iWaitTime );
                GET_SYSAPI_sleep ( iWaitTime );
            }
           
            // Delete the created temp files
            if ( ! sAttachmentFilePath.empty() )
            {
                GET_SYSAPI_unLink ( ( char * ) sAttachmentFilePath.c_str() );
            }
            for ( size_t iIndex = 0; iIndex < vExportedFilePaths.size(); iIndex++ )
            {
                if ( ! vExportedFilePaths[iIndex].empty() )
                {
                   GET_SYSAPI_unLink ( ( char * ) vExportedFilePaths[iIndex].c_str() );
                }
            }
            // Delete the temp directory if created
            if ( ! sUnqTmpDir.empty() )
            {
                GET_SYSAPI_removeDirectory ( sUnqTmpDir.c_str() );
            }
        }
        if ( mArgumentsMap.find ( SAVE_ECN_REPORT_ARG ) != mArgumentsMap.end() )
        {
            createECNSummaryReport( sHTMLTotalPage, itemRevShrPtr );
        }
    }

    LOG_TRACE ( logger, "END : GET6_notifyAH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//    Function:  createECNSummaryReport()
//
//    Purpose:   Method for creating ECN summary report, which will be attached to ECN Revision as references
//
//    Inputs:    HTML page, ECN Revision shared pointer
//
//    Outputs:   none
//
//    Return:    None
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     12 Oct, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void createECNSummaryReport(string sHTMLTotalPage, GET_ItemRevisionShrPtr ecnRevisionShrPtr)
{
    string dsName = ecnRevisionShrPtr->getItem()->getId()+SUMMARY_REPORT;
    string sOrginalFileName = dsName + "-" + SUMMARY_REPORT;
    sOrginalFileName.append( HTML_FILE_EXT );
    GET_POM_objectShrPtr relDataPtr;

    // Create the html file in Teamcenter
    GET_ImanTextFileUnqPtr iManFileUnqPtr = GET_ImanTextFile::createInstance ( sHTMLTotalPage, sOrginalFileName );

    // Create the dataset
    GET_DatasetUnqPtr dsUnqPtr = GET_Dataset::createInstance ( HTML_DATASET, HTMLEDITOR_TOOL,dsName, ecnRevisionShrPtr->getRevId(), "HTML dataset for ECN Summary Report" );
    GET_ImanFileShrPtr iManFileShrPtr ( move ( iManFileUnqPtr ) );

    // Relate the html dataset to the ECN Revision with EC_reference_item_rel relation
    GET_DatasetShrPtr dataSetShrPtr ( move ( dsUnqPtr ) );
    dataSetShrPtr->addNamedRef ( iManFileShrPtr, HTML_REFNAME );
    GET_ImanRelation::create ( ecnRevisionShrPtr, dataSetShrPtr, CMREFERENCES, relDataPtr );
}
/*STARTFUNCDOC ***
//
===========================================================================
//    Function:  recurseWfSubTasks()
//
//    Purpose:   Method for getting review report of All reviewers who reviewed the workflow targets
//
//    Inputs:    taskShrPtr - Root task share pointer (GET_EPMTaskShrPtr)
//
//    Outputs:   none
//
//    Return:    A string with review reports in HTML table format
//
//     History:
//      Who                   Date                 Description
//  Ganesh Ubale         12 Sep, 2017           Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
string recurseWfSubTasks ( GET_EPMTaskShrPtr taskShrPtr )
{
    string sHTMLBody = "";
    vector<GET_EPMTaskUnqPtr> vSubTaskUnqPtrs = taskShrPtr->getSubTasks();
    for ( int inx = 0; inx < vSubTaskUnqPtrs.size(); inx++ )
    {
        if ( vSubTaskUnqPtrs[inx]->getType().compare ( PERFORM_SIGNOFF_TASK_TYPE ) == 0 )
        {
            // Structure variable declaration
            ReviewTaskResults reviewDecisionResults;
            vector<GET_POM_userUnqPtr> vUserUnqPtr = vSubTaskUnqPtrs[inx]->askReviewers();
            if ( vUserUnqPtr.size() > 0 )
            {
                for ( int iInx = 0; iInx < vUserUnqPtr.size(); iInx++ )
                {
                    GET_POM_userShrPtr UserShrPtr ( move ( vUserUnqPtr[iInx] ) );

                    vSubTaskUnqPtrs[inx]->getDecision ( UserShrPtr, reviewDecisionResults );

                    if ( ( reviewDecisionResults.sDecision == APPROVED_DECISION_ATTR ) || ( reviewDecisionResults.sDecision == REJECT_DECISION_ATTR ) )
                    {
                        sHTMLBody = sHTMLBody + "<tr><td valign=top align=left ><b>" + vSubTaskUnqPtrs[inx]->getName() + "</b></td>";    
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + UserShrPtr->getName() + "(" + UserShrPtr->getID() + ")" + "</b></td>";    
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + reviewDecisionResults.sDecision + "</b></td>";
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + reviewDecisionResults.decisionDatePtr->toString() + "</b></td>";
                        sHTMLBody = sHTMLBody + "<td valign=top align=left ><b>" + reviewDecisionResults.sComments + "</b></td></tr>";
                    }
                }
                //sHTMLBody = sHTMLBody + "</tr>";
            }
        }
        GET_EPMTaskShrPtr taskShrPtr1 ( move ( vSubTaskUnqPtrs[inx] ) );
        sHTMLBody = sHTMLBody + recurseWfSubTasks ( taskShrPtr1 );
    }

    return sHTMLBody;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_deleteRelatedDatasetAH()
//
//    Purpose:   Action handler for deleting a dataset related to the workflow targets
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    A Integer code indicating success - Zero or failure - Non-Zero
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team    19 Jul, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_deleteRelatedDatasetAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_deleteRelatedDatasetAH" );

    try
    {
        GET_processHandler ( tMessage, GET6_deleteRelatedDatasetAH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_deleteRelatedDatasetAH" );
    }

    LOG_TRACE ( logger, "END : GET6_deleteRelatedDatasetAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_deleteRelatedDatasetAH_impl()
//
//    Purpose:   Action Handler implementation function for GET6_deleteRelatedDataset handler
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
//  TCS Development Team     19 Jul, 2016         Initial Creation
//  TCS Development Team     09 May, 2017         Cleaned the code for standards
//  TCS Development Team     22 Sep, 2017         Corrected the variable name for target attachments map
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_deleteRelatedDatasetAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    LOG_TRACE ( logger, "START : GET6_deleteRelatedDatasetAH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[RELATION_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( DATASET_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[DATASET_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( DATASET_TYPE_ARG ) + "\" is either empty or has an invalid value";
        THROW ( sMsg );
    }

    // Get the target Revision Object
    GET_ItemRevisionUnqPtr itemRevisionUnqPtr = GET_ItemRevision::getInstance ( mAttachmentsMap[EPM_target_attachment][0] );
    GET_ItemRevisionShrPtr itemRevPtr ( move ( itemRevisionUnqPtr ) );

    vector<GET_WorkspaceObjectUnqPtr> vRelatedObjs = GET_ImanRelation::listRelatedWsObjects ( itemRevPtr, mArgumentsMap[RELATION_TYPE_ARG], mArgumentsMap[DATASET_TYPE_ARG] );

    for ( size_t iIndex = 0; iIndex < vRelatedObjs.size(); iIndex++ )
    {
        if ( ! GET_POM_object::isDescendant ( vRelatedObjs[iIndex]->getTag(), DATASET_CLASS ) )
        {
            continue;
        }

        vRelatedObjs[iIndex]->deleteFromParent ( itemRevPtr );
    }

    LOG_TRACE ( logger, "END : GET6_deleteRelatedDatasetAH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_setStatusAH()
//
//    Purpose:   Action Handler to assign correct release status to MCN Objects
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_setStatusAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     06 Oct, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_setStatusAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_setStatusAH" );

    try
    {
        GET_processHandler ( tMessage, GET6_setStatusAH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_setStatusAH" );
    }

    LOG_TRACE ( logger, "END : GET6_setStatusAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_setStatusAH_impl()
//
//    Purpose:   Action Handler Implementation to add status
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     06 Oct, 2016         Initial creation
//  TCS Development Team     09 May, 2017         Cleaned the code for standards
//  TCS Development Team     22 Sep, 2017         Corrected the variable name for target attachments map
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_setStatusAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    vector<string> vIncludeType;
    vector<string> vExcludeType;
    vector<tag_t> vTargetAttachments = mAttachmentsMap[EPM_target_attachment];
    vector<GET_WorkspaceObjectShrPtr> vReleaseTargets;

    LOG_TRACE ( logger, "START: GET6_setStatusAH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( STATUS_ARG ) == mArgumentsMap.end() || mArgumentsMap[STATUS_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( STATUS_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) != mArgumentsMap.end() && mArgumentsMap.find ( EXCLUDE_TYPE_ARG ) != mArgumentsMap.end() )
    {
        string sMsg = string ( INCLUDE_TYPE_ARG ) + " and " + string ( EXCLUDE_TYPE_ARG ) + " are mutually exclusive!!!";
        THROW ( sMsg );
    }

    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );
    GET_splitString ( mArgumentsMap[EXCLUDE_TYPE_ARG], COMMA_CHARACTER, vExcludeType );

    for ( int iIndex = 0; iIndex < vTargetAttachments.size(); iIndex++ )
    {
        if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iIndex], WORKSPACEOBJECT_CLASS ) )
        {
            continue;
        }

        GET_WorkspaceObjectShrPtr wsoShrPtr ( move ( GET_WorkspaceObject::getInstance ( vTargetAttachments[iIndex] ) ) );
        string sObjType = wsoShrPtr->getType();

        if ( ( vIncludeType.empty() && vExcludeType.empty() ) ||
             ( ( !vIncludeType.empty() && GET_isInVector ( vIncludeType, sObjType ) ) ||
             ( !vExcludeType.empty() && !GET_isInVector ( vExcludeType, sObjType  ) ) ) )
        {
            LOG_DEBUG ( logger, "Status will be added to " + sObjType );
            vReleaseTargets.push_back ( wsoShrPtr );
        }
    }

    if ( vReleaseTargets.size() > 0 )
    {
        GET_ReleaseStatusUnqPtr relStatusUnqPtr = GET_ReleaseStatus::createStatus ( mArgumentsMap[STATUS_ARG] );
        relStatusUnqPtr->addStatus ( vReleaseTargets, false );
    }

    LOG_TRACE ( logger, "END: GET6_setStatusAH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_findDispatcherRequestsAH()
//
//    Purpose:   Action Handler to find Dispatcher Requests created in the current WF and set the condition task result accordingly
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     29 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_findDispatcherRequestsAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_findDispatcherRequestsAH" );

    try
    {
        GET_processHandler ( tMessage, GET6_findDispatcherRequestsAH_impl, false );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_findDispatcherRequestsAH" );
    }

    LOG_TRACE ( logger, "END : GET6_findDispatcherRequestsAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_findDispatcherRequestsAH_impl()
//
//    Purpose:   Action Handler Implementation to add status
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     29 May, 2017         Initial creation
//  TCS Development Team     31 May, 2017         Modified query constants to reflect changes in Query file
//  TCS Development Team     22 Sep, 2017         Corrected the variable name for target attachments map
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_findDispatcherRequestsAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    bool bResultToSet = false;

    string sItemIDString = "";
    string sRevisionIDString = "";

    vector<string> vIncludeType;

    vector<GET_POM_objectUnqPtr> vTargetAttachmentsUnqPtr;

    LOG_TRACE ( logger, "START: GET6_findDispatcherRequestsAH_impl" );

    // Validate the arguments supplied
    if ( mArgumentsMap.find ( INCLUDE_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[INCLUDE_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( INCLUDE_TYPE_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    GET_splitString ( mArgumentsMap[INCLUDE_TYPE_ARG], COMMA_CHARACTER, vIncludeType );

    // Get root task and attachments
    GET_EPMTaskUnqPtr currentTaskUnqPtr = GET_EPMTask::getInstance ( tTaskTag );
    GET_EPMTaskUnqPtr rootTaskUnqPtr = currentTaskUnqPtr->getRootTask();
    vTargetAttachmentsUnqPtr = rootTaskUnqPtr->askAttachments ( EPM_target_attachment );
    for ( int iIndex = 0; iIndex < vTargetAttachmentsUnqPtr.size(); iIndex++ )
    {
        if ( ! GET_isInVector ( vIncludeType, vTargetAttachmentsUnqPtr[iIndex]->askTypeName() ) )
        {
            continue;
        }
        GET_ItemRevisionUnqPtr itemRevisionPtr = GET_ItemRevision::getInstance ( vTargetAttachmentsUnqPtr[iIndex]->getTag() );
        sItemIDString = sItemIDString + itemRevisionPtr->getId() + SEMICOLON_SEPERATOR;
        sRevisionIDString = sRevisionIDString + itemRevisionPtr->getRevId() + SEMICOLON_SEPERATOR;
    }

    // Execute the query and find out if any Dispatcher Requests were created as part of this WF
    if ( ! sItemIDString.empty() )
    {
        vector<string> vQueryEntries;
        vector<string> vQueryValues;
        vector<GET_POM_objectUnqPtr> vDispRequests;

        // Construct the Query clauses (Entries and Values)
        vQueryEntries.push_back ( QUERY_ID_ENTRY );
        vQueryEntries.push_back ( QUERY_REVISION_ENTRY );
        vQueryEntries.push_back ( QUERY_CREATED_AFTER_ENTRY );
        vQueryValues.push_back ( sItemIDString );
        vQueryValues.push_back ( sRevisionIDString );
        vQueryValues.push_back ( rootTaskUnqPtr->getPropDate ( CREATION_DATE_ATTR )->toString() );

        // Execute the query
        vDispRequests = GET_ImanQuery::executeQuery ( DISPATCHER_QUERY, vQueryEntries, vQueryValues );
        if ( vDispRequests.size() > 0 )
        {
            bResultToSet = true;
        }
    }

    // set the task result
    currentTaskUnqPtr->setTaskResult ( bResultToSet ? TRUE_VALUE : FALSE_VALUE );

    LOG_TRACE ( logger, "END: GET6_findDispatcherRequestsAH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_createDispatcherRequestsAH()
//
//    Purpose:   Action Handler to create Dispatcher Requests for the specified primary object, relation and dataset types
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (EPM_action_message_t)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TechM Development Team   18 Sep, 2017         Initial creation
//  TCS Development Team     22 Sep, 2017         Removed the unnecessary third argument
//
===========================================================================
//ENDFUNCDOC   ***/
extern int GET6_createDispatcherRequestsAH ( EPM_action_message_t tMessage )
{
    int iFail = ITK_ok;

    LOG_TRACE ( logger, "START : GET6_createDispatcherRequestsAH" );

    try
    {
        GET_processHandler ( tMessage, GET6_createDispatcherRequestsAH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_createDispatcherRequestsAH" );
    }

    LOG_TRACE ( logger, "END : GET6_createDispatcherRequestsAH" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_createDispatcherRequestsAH_impl()
//
//    Purpose:   Action Handler Implementation to create dispatcher request
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TechM Development Team   18 Sep, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_createDispatcherRequestsAH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{
    bool bResultToSet = false;

    int iPriority = 1;

    string sRelationType = "";

    vector<string> vDatasetTypes;
    vector<string> vPrimaryTypes;

    vector<tag_t> vTargetAttachments;

    LOG_TRACE ( logger, "START: GET6_createDispatcherRequestsAH_impl" );

     // Validate the Mandatory arguments supplied
    if ( mArgumentsMap.find ( PROVIDER_NAME_ARG ) == mArgumentsMap.end() || mArgumentsMap[PROVIDER_NAME_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( PROVIDER_NAME_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( SERVICE_NAME_ARG ) == mArgumentsMap.end() || mArgumentsMap[SERVICE_NAME_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( SERVICE_NAME_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( mArgumentsMap.find ( DATASET_TYPE_ARG ) == mArgumentsMap.end() || mArgumentsMap[DATASET_TYPE_ARG].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( DATASET_TYPE_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    GET_splitString ( mArgumentsMap[DATASET_TYPE_ARG], COMMA_CHARACTER, vDatasetTypes );

    // Optional Arguments, if supplied
    if ( mArgumentsMap.find ( PRIORITY_ARG ) != mArgumentsMap.end() && ! mArgumentsMap[PRIORITY_ARG].empty() )
    {
        iPriority = stoi ( mArgumentsMap[PRIORITY_ARG], NULL, 0 );
    }
    if ( mArgumentsMap.find ( PRIMARY_TYPE_ARG ) != mArgumentsMap.end() && ! mArgumentsMap[PRIMARY_TYPE_ARG].empty() )
    {
        GET_splitString ( mArgumentsMap[PRIMARY_TYPE_ARG], COMMA_CHARACTER, vPrimaryTypes );
    }
    if ( mArgumentsMap.find ( RELATION_TYPE_ARG ) != mArgumentsMap.end() && ! mArgumentsMap[RELATION_TYPE_ARG].empty() )
    {
        sRelationType = mArgumentsMap[RELATION_TYPE_ARG];
    }

    // Get the target attachments
    vTargetAttachments = mAttachmentsMap[EPM_target_attachment];
    for ( int iIndex = 0; iIndex < vTargetAttachments.size(); iIndex++ )
    {
        // Get the specified primary type objects from the target attachments
        GET_POM_objectUnqPtr pomObjectPtr = GET_POM_object::getInstance ( vTargetAttachments[iIndex] );
        if ( vPrimaryTypes.size() > 0 && ! GET_isInVector ( vPrimaryTypes, pomObjectPtr->askTypeName() ) )
        {
            continue;
        }
        else if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iIndex], ITEMREVISION_CLASS ) )
        {
            continue;
        }
        GET_ItemRevisionUnqPtr itemRevisionPtr = GET_ItemRevision::getInstance ( vTargetAttachments[iIndex] );
        GET_ItemRevisionShrPtr itemRevShrPtr ( move ( itemRevisionPtr ) );
        //Get the secondary objects having specified relation type and dataset type
        vector<GET_WorkspaceObjectUnqPtr> vSecondaryPtr = GET_ImanRelation::listRelatedWsObjects ( itemRevShrPtr, sRelationType );
        for ( int jIndex = 0; jIndex < vSecondaryPtr.size(); jIndex++ )
        {
            if ( ! GET_isInVector ( vDatasetTypes, vSecondaryPtr[jIndex]->getType() ) )
            {
                continue;
            }
            //Create a dispatcher request with the specified arguments
            GET_DatasetShrPtr datasetShrPtr ( move ( GET_Dataset::getInstance ( vSecondaryPtr[jIndex]->getTag() ) ) );
            GET_DispatcherRequestUnqPtr dispRqstPtr =  GET_DispatcherRequest::createInstance ( mArgumentsMap[PROVIDER_NAME_ARG], mArgumentsMap[SERVICE_NAME_ARG], iPriority, itemRevShrPtr, datasetShrPtr );
        }
    }

    LOG_TRACE ( logger, "END: GET6_createDispatcherRequestsAH_impl" );
}
