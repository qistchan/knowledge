
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Exception.cxx
//
//    Purpose:   Class for dealing with exception handling
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#include <GET_Exception.hxx>
#include <GET_Utils.hxx>

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_Exception()
 //
 //    Purpose:   Constructor for this class
 //
 //     Inputs:   sFileName - file name
 //               iLineNumber - line number
 //
 //    Outputs:   sMessage - error message
 //
 //     Return:   GET_Exception object
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 GET_Exception::GET_Exception ( const string sFileName, const int iLineNumber, string sMessage )
 {
    fileName     = sFileName;
    lineNumber   = iLineNumber;
    errorMessage = sMessage;
 }

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_Exception()
 //
 //    Purpose:   Destructor for this class
 //
 //     Inputs:   none
 //
 //    Outputs:   none
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
GET_Exception::~GET_Exception() {}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   print()
 //
 //    Purpose:   Method for printing exception
 //
 //     Inputs:   none
 //
 //    Outputs:   none
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
void GET_Exception::print()
{
    string message = "GET Exception : " + errorMessage + " in File : " + fileName + " @ line # : " + GET_intToString(lineNumber) + "\n";
    fprintf(stderr, message.c_str());
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getErrorMessage()
 //
 //    Purpose:   Method for getting error message
 //
 //     Inputs:   none
 //
 //    Outputs:   none
 //
 //     Return:   errorMessage - error message
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
string GET_Exception::getErrorMessage()
{
    return errorMessage;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getLineNumber()
 //
 //    Purpose:   getter for line number
 //
 //     Inputs:   none
 //
 //    Outputs:   none
 //
 //     Return:   lineNumber - line number
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
int  GET_Exception::getLineNumber()
{
    return lineNumber;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getFileName()
 //
 //    Purpose:   Getter for file name
 //
 //     Inputs:   none
 //
 //    Outputs:   none
 //
 //     Return:   string - file name
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
string GET_Exception::getFileName()
{
    return fileName;
}
