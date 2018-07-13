
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_SMTP_Mail.cxx
//
//    Purpose:   Class definition for Teamcenter SMTP Email
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     1 Mar, 2016         Initial creation
//  TCS Development Team     12 Apr, 2017        Added attachment argument 
//  Ganesh Ubale             12 Sep, 2017        Modified to accepts multiple recipients
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_SMTP_Mail.hxx>
#include <GET_Exception.hxx>
#include <GET_Utils.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Preferences.hxx>
//#include <regex.h>
//#include <regex>
const string logger = "get.get_tc_common.GET_smtp_mail";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   sendMail()
    //
    //   Purpose :   Method to send Teamcenter SMTP email
    //
    //   Inputs  :   sToMailID - Recipient of the Email (string)
    //               sSubjectString - The Email Subject (string)
    //               sBodyString   - Message body to be sent in email (string)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     1 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void sendMail ( const string sToMailID, const string sSubjectString, const string sBodyString )
    {

    	LOG_TRACE ( logger, "START : sendMail" );
        GET_Exception *exception = NULL;

        ofstream bodyFile;

        string sMailString = "";
        string sBodyFileString = "";
        string sToFileString = "";

        try
        {
            vector<string> vServerPrefValues;

            // Get the Mail Server Name from the preferences
            getStringPrefValues ( MAIL_SERVER_NAME_PREF, vServerPrefValues );
            if ( vServerPrefValues.size() == 0 )
            {
                string sMessage = "The Preference " + string ( MAIL_SERVER_NAME_PREF ) + " is not defined or does not have a value";
                THROW ( sMessage );
            }

            // Create the file name for the body file
            sBodyFileString = string ( GET_SYSAPI_getTempDir() )
                               + string ( GET_SYSAPI_getFileSeparator() )
                               + "get_mail_body_" + GET_intToString ( rand() ) + ".txt";

            // Create the body file
            bodyFile.open ( sBodyFileString.c_str() );
            if ( !bodyFile.is_open() )
            {
                string sMessage = "Unable to create/open a file with the name " + sBodyFileString + " for creating the Mail Body";
                THROW ( sMessage.c_str() );
            }
            bodyFile<<sBodyString.c_str();
            bodyFile.close();

            // Construct the mail string
            sMailString = "tc_mail_smtp -subject=\"" + sSubjectString + "\" -server="
                    + vServerPrefValues[0] + " -body=" + sBodyFileString;
            sMailString += " -to=" + sToMailID;

            // Send the mail
            if ( system ( sMailString.c_str() ) != ITK_ok )
            {
                string sMessage = "Failed to send Teamcenter e-mail\n\n";
                sMessage += "The Command executed id : " + sMailString + "\n\n";
                THROW ( sMessage );
            }
        }
        catch ( GET_Exception *ex )
        {
            exception = ex;
        }

        // Delete the created temp files
        if ( !sBodyFileString.empty() )
        {
            GET_SYSAPI_unLink ( ( char * ) sBodyFileString.c_str() );
        }

        // throw the exception to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : sendMail" );
    }

   /*STARTFUNCDOC ***
	//
	===========================================================================
	//   Function:   sendMailAsHtml()
	//
	//   Purpose :   Method to send Teamcenter SMTP email as HTML page.
	//
	//   Inputs  :   vToMailIDs - Recipients of the Emails (vector<string>)
	//               sSubjectString - The Email Subject (string)
	//               sBodyString   - Message body to be sent in email (string)
	//               sAttachmentString - A file containing the paths of email file attachments (string). Default value is empty string
    //
	//   Outputs :   none
	//
	//   Return  :   none
	//
	//   History :
	//      Who                   Date                 Description
	//  TCS Development Team     09 June, 2016         Initial creation
	//  Ganesh Ubale             4 Sep, 2017           Modified to accepts multiple recipients
	===========================================================================
	//ENDFUNCDOC   ***/
	extern DLLEXPORT void sendMailAsHtml ( const vector<string> vToMailIDs, const string sSubjectString, const string sBodyString, const string sAttachmentString )
	{
        LOG_TRACE ( logger, "START : sendMailAsHtml" );
		GET_Exception *exception = NULL;

		ofstream bodyFile;
		ofstream emailListFilePtr;

        string sEmailListFilePath = "";
		string sMailString = "";
		string sBodyFileString = "";
		string sToFileString = "";

        try
        {
            vector<string> vServerPrefValues;

            if ( vToMailIDs.size() == 0 )
			{
                string sMessage = "No TO email id specified" ;
			    THROW ( sMessage );
		    }
            
			// Get the Mail Server Name from the preferences
			getStringPrefValues ( MAIL_SERVER_NAME_PREF, vServerPrefValues );
			if ( vServerPrefValues.size() == 0 )
			{
				string sMessage = "The Preference " + string ( MAIL_SERVER_NAME_PREF ) + " is not defined or does not have a value";
				THROW ( sMessage );
			}

			// Create the file name for the body file
			sBodyFileString = string ( GET_SYSAPI_getTempDir() )
							   + string ( GET_SYSAPI_getFileSeparator() )
							   + "get_mail_body_" + GET_intToString ( rand() ) + ".html";

			// Create the body file
			bodyFile.open ( sBodyFileString.c_str() );
			if ( !bodyFile.is_open() )
			{
				string sMessage = "Unable to create/open a file with the name " + sBodyFileString + " for creating the Mail Body";
				THROW ( sMessage.c_str() );
			}
			bodyFile<<sBodyString.c_str();
			bodyFile.close();
	
	        // Construct the mail string
			sMailString = "tc_mail_smtp -subject=\"" + sSubjectString + "\" -server="
					+ vServerPrefValues[0] + " -body=" + sBodyFileString;

            if ( ! sAttachmentString.empty() )
			{
			    sMailString += " -attachments=" + sAttachmentString;
			}

			if( vToMailIDs.size() == 1 )
			{
                sMailString += " -to=" + vToMailIDs[0];
		    }
            else
			{
                // Create the file name for the email list
       	        sEmailListFilePath = string ( GET_SYSAPI_getTempDir() )
       			     		       + string ( GET_SYSAPI_getFileSeparator() )
       						       + "email_list_" + GET_intToString ( rand() ) + ".txt";
       	         
                // Create the body for email list file
       	        emailListFilePtr.open ( sEmailListFilePath.c_str() );
			    if ( ! emailListFilePtr.is_open() )
       	        {
       		        string sMsg = "Unable to create a temporary file with the name " + sEmailListFilePath + " for creating recipients email list";
       		        THROW ( sMsg );
       	        }
			    for ( size_t iIndex = 0; iIndex < vToMailIDs.size(); iIndex++ )
       	        {
			        emailListFilePtr << vToMailIDs[iIndex].c_str() << endl;
       	        }
                emailListFilePtr.close();

			    sMailString += " -to_list_file=" + sEmailListFilePath;
			}

			// Send the mail
			if ( system ( sMailString.c_str() ) != ITK_ok )
			{
				string sMessage = "Failed to send Teamcenter e-mail\n\n";
				sMessage += "The Command executed id : " + sMailString + "\n\n";
				THROW ( sMessage );
			}
		}
		catch ( GET_Exception *ex )
		{
			exception = ex;
		}

		// Delete the created temp files
		if ( ! sBodyFileString.empty() )
		{
			GET_SYSAPI_unLink ( ( char * ) sBodyFileString.c_str() );
		}
        if ( ! sEmailListFilePath.empty() )
   	    {
            GET_SYSAPI_unLink ( ( char * ) sEmailListFilePath.c_str() );
        }

		// throw the exception to the calling method
		if ( exception != NULL )
		{
			throw exception;
		}

		LOG_TRACE ( logger, "END : sendMailAsHtml" );
	}
}
