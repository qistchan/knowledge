
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Utils.hxx
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
#ifndef GET_UTILS_HXX_
#define GET_UTILS_HXX_

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// CPP Includes
#include <string>
#include <map>
#include <vector>

// Function Prototypes
extern DLLEXPORT void GET_strtrim ( string& );
extern DLLEXPORT void GET_toUpper ( string& );
extern DLLEXPORT void GET_toLower ( string& );
extern DLLEXPORT string GET_replaceSubString ( const string, const string, const string );
extern DLLEXPORT bool GET_isUpper ( const string );
extern DLLEXPORT bool GET_isLower ( const string );
extern DLLEXPORT bool GET_isAlpha ( const string );
extern DLLEXPORT bool GET_isNumeric ( const string );
extern DLLEXPORT bool GET_isAlphaNumeric ( const string );
extern DLLEXPORT void GET_splitString ( const string, const string, vector<string>& );
extern DLLEXPORT string GET_intToString ( const long );
extern DLLEXPORT void GET_convertToMap ( const int, const char**, map<string, string>& );

extern DLLEXPORT void GET_vectorToArray ( const vector<string>, char*** );

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_vectorToArray
 //
 //    Purpose:   Function to convert vector<T> to T*
 //               This is a utility function that can take any input type and it
 //               converts any vector of given type to its corresponding array
 //
 //     Inputs:   vInput - The input vector with data belonging to the specified type (T)
 //
 //    Outputs:   ppTOutput - An array of objects belonging to the specified type (T**)
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

template <typename T>
extern DLLEXPORT void GET_vectorToArray ( const vector<T> vInput, T **ppTOutput )
{
    if ( vInput.size() > 0 )
    {
        *ppTOutput = ( T* ) malloc ( sizeof ( T ) * vInput.size() );
        for ( size_t iIndex = 0; iIndex < vInput.size(); iIndex++ )
        {
            ( *ppTOutput ) [iIndex] = vInput[iIndex];
        }
    }
}


/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_arrayToVector
 //
 //    Purpose:   Function to convert T* array into vector
 //               This is a utility function that can take any input type and it
 //               converts any array of given type to its corresponding vector
 //
 //     Inputs:   iArraySize - The size of the input array (int)
 //               pTArray    - The input array of the specified type (T*)
 //
 //    Outputs:   vOutput - The vector containing objects of the specified type (T)
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_arrayToVector ( const int, const char**, vector<string>& );

template <typename T>
extern inline DLLEXPORT void GET_arrayToVector ( const int iArraySize, T *pTArray, vector<T> &vOutput )
{
    for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
    {
        vOutput.push_back ( pTArray[iIndex] );
    }
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_numberToString
 //
 //    Purpose:   Function to convert number into string
 //
 //     Inputs:   TInput - The input number to be converted
 //
 //    Outputs:   sOutput - The resultant string value
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   **/
template <typename T>
extern inline DLLEXPORT void GET_numberToString ( const T TInput, string &sOutput )
{
    char cTemp[33];

    sprintf ( cTemp, "%f", TInput );
    sOutput.assign ( cTemp );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_stringToNumber
 //
 //    Purpose:   Function to convert string into Number
 //
 //     Inputs:   sInput - The input string to be converted
 //
 //    Outputs:   TOutput - The resultant number value
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     07 Apr, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
template <typename T>
extern DLLEXPORT void GET_stringToNumber ( const string sInput, T &TOutput )
{
    istringstream myStream ( sInput );

    myStream >> TOutput;
}

extern DLLEXPORT bool GET_isStringNumeric ( const string );

extern DLLEXPORT void GET_free_array ( const int, void** );
extern DLLEXPORT void GET_free ( void* );

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //    Function:  GET_isInVector
 //
 //    Purpose:   Function to find if the given value exists in given vector
 //
 //    Inputs:    vec - Vector in which value is to be searched
 //               value - Value to be searched
 //
 //    Outputs:   none
 //
 //    Return:    bool - True if value exists, else false
 //
 //    History:
 //    Who                      Date                 Description
 //    TCS Development Team     24 Aug, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
template <typename T>
extern DLLEXPORT const bool GET_isInVector ( vector<T>& vec, const T& value )
{
    bool bIsInVector = false;

    if ( find ( vec.begin(), vec.end(), value ) != vec.end() )
    {
        bIsInVector = true;
    }

    return bIsInVector;
}

#endif // GET_UTILS_HXX_
