
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Utils.cxx
//
//    Purpose:   Class containing all utility methods
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//  TCS Development Team     18 Jul, 2016         Added methods GET_isUpper & GET_isLower
//  TCS Development Team     07 Oct, 2016         Added methods GET_isAlpha, GET_isNumeric, & GET_isAlphaNumeric
//  TCS Development Team     19 May, 2017         Added method replaceSubString
//
//   ============================================================================
// ENDFILEDOC   ***/

/* GE includes */
#include <GET_Utils.hxx>
#include <GET_sysapi.h>

// C Includes
#include <ctype.h>

// CPP Includes
#include <algorithm>

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_strtrim()
 //
 //    Purpose:   Removes the leading and trailing spaces of the given string
 //
 //     Inputs:   sString - The string to be trimmed
 //
 //    Outputs:   sString-  The resultant trimmed string
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_strtrim ( string &sString )
{
    sString.erase ( 0, sString.find_first_not_of ( " \t" ) );
    sString.erase ( sString.find_last_not_of ( " \t" ) + 1 );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_toUpper()
 //
 //    Purpose:   Function to convert a given string to upper case
 //
 //     Inputs:   sString - The input string to be converted to upper case
 //
 //    Outputs:   sString-  The resultant upper case string
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_toUpper ( string &sString )
{
    transform ( sString.begin(), sString.end(),
                sString.begin(), ( int ( * ) ( int ) ) toupper );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_toLower()
 //
 //    Purpose:   Function to convert a given string to lower case
 //
 //     Inputs:   sString - The input string to be converted to lower case
 //
 //    Outputs:   sString-  The resultant lower case string
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_toLower ( string &sString )
{
    transform ( sString.begin(), sString.end(),
                sString.begin(), ( int ( * ) ( int ) ) tolower );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_replaceSubString()
 //
 //    Purpose:   Function to replace all the given Sub Strings with a new Sub String
 //
 //     Inputs:   sInputString - The input string to be modified
 //               sSubString - The Sub String to be replaced
 //               sReplacement - The replacement string for the identified Sub String
 //
 //    Outputs:   none
 //
 //     Return:   Input string with all Sub String occurrences replaced with the new Sub String
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     19 May, 2017         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT string GET_replaceSubString ( const string sInputString, const string sSubString, const string sReplacement )
{
    bool bIsfound = true;

    string sOutputString = sInputString;

    while ( bIsfound )
    {
        size_t iPosition = sOutputString.find ( sSubString );
        if ( iPosition == string::npos )
        {
            bIsfound = false;
        }
        else
        {
            sOutputString.replace ( iPosition, sSubString.length(), sReplacement );
        }
    }

    return sOutputString;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_isUpper()
 //
 //    Purpose:   Function to check whether a given input string contains only upper case characters
 //
 //     Inputs:   sString - The input string to be checked for upper case characters
 //
 //    Outputs:   none
 //
 //     Return:   A boolean flag indicating whether the given string contains only upper case characters or not (true/false)
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     18 Jul, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT bool GET_isUpper ( const string sString )
{
    return find_if ( sString.begin(), sString.end(), ::islower ) == sString.end();
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_isLower()
 //
 //    Purpose:   Function to check whether a given input string contains only lower case characters
 //
 //     Inputs:   sString - The input string to be checked for lower case characters
 //
 //    Outputs:   none
 //
 //     Return:   A boolean flag indicating whether the given string contains only lower case characters or not (true/false)
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     18 Jul, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT bool GET_isLower ( const string sString )
{
    return find_if ( sString.begin(), sString.end(), ::isupper ) == sString.end();
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_isAlpha()
 //
 //    Purpose:   Function to check whether a given input string contains only alphabetic characters
 //
 //     Inputs:   sString - The input string to be checked for alphabetic characters
 //
 //    Outputs:   none
 //
 //     Return:   A boolean flag indicating whether the given string contains only alphabetic characters or not (true/false)
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Oct, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT bool GET_isAlpha ( const string sString )
{
    bool bIsAlpha = false;

    for ( size_t iIndex = 0; iIndex < sString.length(); iIndex++ )
    {
        bIsAlpha = isalpha ( sString [iIndex] );
        if ( ! bIsAlpha )
        {
            break;
        }
    }

    return bIsAlpha;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_isNumeric()
 //
 //    Purpose:   Function to check whether a given input string contains only numeric characters
 //
 //     Inputs:   sString - The input string to be checked for numeric characters
 //
 //    Outputs:   none
 //
 //     Return:   A boolean flag indicating whether the given string contains only numeric characters or not (true/false)
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Oct, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT bool GET_isNumeric ( const string sString )
{
    bool bIsNumeric = false;

    for ( size_t iIndex = 0; iIndex < sString.length(); iIndex++ )
    {
        bIsNumeric = isdigit ( sString [iIndex] );
        if ( ! bIsNumeric )
        {
            break;
        }
    }

    return bIsNumeric;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_isAlphaNumeric()
 //
 //    Purpose:   Function to check whether a given input string contains only alphanumeric characters
 //
 //     Inputs:   sString - The input string to be checked for alphanumeric characters
 //
 //    Outputs:   none
 //
 //     Return:   A boolean flag indicating whether the given string contains only alphanumeric characters or not (true/false)
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Oct, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT bool GET_isAlphaNumeric ( const string sString )
{
    bool bIsAlphaNumeric = false;

    for ( size_t iIndex = 0; iIndex < sString.length(); iIndex++ )
    {
        bIsAlphaNumeric = isalnum ( sString [iIndex] );
        if ( ! bIsAlphaNumeric )
        {
            break;
        }
    }

    return bIsAlphaNumeric;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_splitString
 //
 //    Purpose:   Splits the string into a string array
 //
 //     Inputs:   sInput - The string that needs to be split
 //               sDelimiter - The delimiter to split the string
 //
 //    Outputs:   vOutput - The vector containing the split strings
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_splitString ( const string sInput, const string sDelimiter, vector<string> &vOutput )
{
    size_t iPos = 0;
    string sTemp = "";
    string sTempInput = sInput;

    while ( true )
    {
        if ( ( iPos = sTempInput.find ( sDelimiter, 0 ) ) != string::npos )
        {
            sTemp = sTempInput.substr ( 0, iPos );
            GET_strtrim ( sTemp );
            vOutput.push_back ( sTemp );
            sTempInput.erase ( 0, ( iPos + 1 ) );
            GET_strtrim ( sTempInput );
        }
        else
        {
            GET_strtrim ( sTempInput );
            if ( ! sTempInput.empty() )
            {
                vOutput.push_back ( sTempInput );
            }
            break;
        }
    }
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_intToString
 //
 //    Purpose:   Converts the given long number to a string.
 //
 //     Inputs:   lNumber - The number that needs to be converted
 //
 //    Outputs:   none
 //
 //     Return:   The number in string format
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT string GET_intToString ( const long lNumber )
{
    char cTemp[20];
    sprintf ( cTemp, "%d", lNumber );
    return string ( cTemp );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_convertToMap
 //
 //    Purpose:   Converts the command line arguments to a more
 //               user friendly key-value map pairs
 //
 //     Inputs:   iArgc - The input number of arguments
 //               ppcArgv - The actual argument array
 //
 //    Outputs:   mArguments - The arguments in a string name-value pair format in a map
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_convertToMap ( const int iArgc, const char **ppcArgv, map<string, string> &mArguments )
{
    string sSingleArg = "";
    int iPos = -1;

    // Skip the initial one as it is the program name
    for ( int iIndex = 1; iIndex < iArgc; iIndex++ )
    {
        sSingleArg.assign ( ppcArgv[iIndex] );
        iPos = ( int ) sSingleArg.find_first_of ( "=" );
        if ( iPos == -1 )
        {
            // Individual arguments with no value
            //pArguments.insert ( pair<string, string> ( sSingleArg, "" ) );
            mArguments [ sSingleArg ] = "";
        }
        else
        {
            mArguments [ sSingleArg.substr ( 0, iPos ) ] = sSingleArg.substr ( iPos + 1, sSingleArg.length() );
        }
    }
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET_vectorToArray
 //
 //    Purpose:  Function to convert vector<string> to char**
 //
 //     Inputs:  vInput - The input vector containing string objects
 //
 //    Outputs:  pppcOutput - The output pointer to char** converted from the vector
 //
 //     Return:  none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_vectorToArray ( const vector<string> vInput, char ***pppcOutput )
{
    if ( vInput.size() > 0 )
    {
        *pppcOutput = ( char ** ) malloc ( sizeof ( char* ) * vInput.size() );
        for ( size_t iIndex = 0; iIndex < vInput.size(); iIndex++ )
        {
            ( *pppcOutput ) [iIndex] = ( char* ) malloc ( sizeof ( char ) * ( vInput[iIndex].size() + 1 ) );
            strcpy ( ( *pppcOutput ) [iIndex], vInput[iIndex].c_str() );
        }
    }
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_arrayToVector
 //
 //    Purpose:   Function to convert char** array into vector
 //
 //     Inputs:   iArraySize - The size of the input array (int)
 //               ppcArray    - The input character array (char **)
 //
 //    Outputs:   vOutput - The vector of strings converted from the input character array
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_arrayToVector ( const int iArraySize, const char **ppcArray, vector<string> &vOutput )
{
    for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
    {
        if ( ppcArray[iIndex] != NULL )
        {
            vOutput.push_back ( ppcArray[iIndex] );
        }
        else
        {
            vOutput.push_back ( "" );
        }
    }
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_isStringNumeric
 //
 //    Purpose:   Function to check if the given string is a number or not
 //
 //     Inputs:   sInput The input string to be checked
 //
 //    Outputs:   none
 //
 //     Return:   boolean indicating whether the given string is a boolean or not
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT bool GET_isStringNumeric ( const string sInput )
{
    bool bIsDigit = true;

    string sTemp = sInput;

    GET_strtrim ( sTemp );

    if ( sTemp.empty() )
    {
        bIsDigit = false;
    }
    else
    {
        for ( string::const_iterator it = sInput.begin(); it != sInput.end(); ++it )
        {
            if ( ! isdigit ( *it ) )
            {
                bIsDigit = false;
                break;
            }
        }
    }

    return bIsDigit;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_free_array
 //
 //    Purpose:   To free memory allocated by malloc() for double pointers.
 //
 //     Inputs:   iArraySize   - size of the array
 //               ppvArray - a double pointer
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
extern DLLEXPORT void GET_free_array ( const int iArraySize, void **ppvArray )
{
    // Free the array members and the top level variable
    if ( ppvArray != NULL && iArraySize >= 1 )
    {
        for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
        {
            if ( ppvArray[iIndex] != NULL )
            {
                free ( ppvArray[iIndex] );
                ppvArray[iIndex] = NULL;
            }
        }

        free ( ppvArray );
        ppvArray = NULL;
    }
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_free
 //
 //    Purpose:   To free memory allocated by malloc() for single pointers.
 //
 //     Inputs:   pvVar - a pointer
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
extern DLLEXPORT void GET_free ( void *pvVar )
{
    // Free the array
    if ( pvVar != NULL )
    {
        free ( pvVar );
        pvVar = NULL;
    }
}
