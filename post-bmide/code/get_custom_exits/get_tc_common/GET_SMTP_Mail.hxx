
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_smtp_mail.hxx
//
//    Purpose:   Header file for class definition for Teamcenter SMTP mail
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     1 Mar, 2016           Initial creation
//  TCS Development Team     12 Apr, 2017          Added attachment argument 
//  Ganesh Ubale             12 Sep, 2017          Modified sendMailAsHtml to accepts multiple recipients
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_SMTP_MAIL_HXX
#define GET_SMTP_MAIL_HXX

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_TC_Attributes.hxx>
#include <vector>

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
    extern DLLEXPORT void sendMail ( const string, const string, const string );

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
    extern DLLEXPORT void sendMailAsHtml ( const vector<string>, const string, const string, const string = "" );
}

#endif // GET_SMTP_MAIL_HXX
