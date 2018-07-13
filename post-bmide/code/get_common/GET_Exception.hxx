
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Exception.hxx
//
//    Purpose:   Class for dealing with exception handling
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_EXCEPTION_HXX
#define GET_EXCEPTION_HXX

//STL includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <string>

#define GET_GENERAL_EXCEPTION 95001


/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  Macro to throw an new exception
 //
 //    Purpose:  Macro to throw an new exception, this macro requires a logger to be defined
 //
 //     Inputs:  none
 //
 //    Outputs:  none
 //
 //     Return:  none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
#define THROW( message ) \
{ \
    LOG_WARN (logger, "Throwing GET_Exception"); \
    throw new GET_Exception (__FILE__, __LINE__, message); \
}

// Class definition
class DLLEXPORT GET_Exception {
    public:

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
		 GET_Exception ( const string sFileName, const int iLineNumber, string sMessage );

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
         ~GET_Exception  (void );

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
         void print ( void );

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
        string getErrorMessage ( void );

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
        int getLineNumber();

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
        string getFileName();
    private:
        int lineNumber;
        string errorMessage;
        string fileName;
};

#endif // GET_EXCEPTION_HXX
