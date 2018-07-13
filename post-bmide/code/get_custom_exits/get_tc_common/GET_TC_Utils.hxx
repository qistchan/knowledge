
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_TC_Utils.hxx
//
//    Purpose:   Header file for defining commonly used Teamcenter Utility Functions
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     01 Mar, 2016         Initial creation
//  TCS Development Team     19 May, 2017         Added Teamcenter login method for command line utilities
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_TC_UTILS_HXX_
#define GET_TC_UTILS_HXX_

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>
#include <GET_POM_application_object.hxx>
#include <GET_Date.hxx>

// CPP Includes
#include <string>
#include <map>
#include <vector>

// Teamcenter Includes
#include <tc/tc.h>

using namespace get;

// Prototypes for functions dealing with Teamcenter Object Arrays

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_arrayToVector
//
//   Purpose :  Function to convert an array of logical objects into a vector of bool objects
//
//   Inputs  :  iArraySize - The size of the input array (int)
//              plArray - The input logical array to be converted
//
//   Outputs :  A vector of bool objects converted from the input logical array
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_arrayToVector ( const int, const logical*, vector<bool>& );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_arrayToVector
//
//   Purpose :  Function to convert an array of tag_t objects into a vector of GET_POM_objectUnqPtr objects
//
//   Inputs  :  iArraySize - The size of the input array (int)
//              ptArray - The input tag_t array to be converted
//
//   Outputs :  A vector of GET_POM_object Unique Pointer objects (GET_POM_objectUnqPtr) converted from the input tag_t array
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_arrayToVector ( const int, const tag_t*, vector<GET_POM_objectUnqPtr>& );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_arrayToVector
//
//   Purpose :  Function to convert an array of tag_t objects into a vector of GET_POM_application_objectUnqPtr objects
//
//   Inputs  :  iArraySize - The size of the input array (int)
//              ptArray - The input tag_t array to be converted
//
//   Outputs :  A vector of GET_POM_application_object Unique Pointer objects (GET_POM_application_objectUnqPtr) converted from the input tag_t array
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_arrayToVector ( const int, const tag_t*, vector<GET_POM_application_objectUnqPtr>& );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_arrayToVector
//
//   Purpose :  Function to convert an array of date_t objects into a vector of GET_DateUnqPtr objects
//
//   Inputs  :  iArraySize - The size of the input array (int)
//              pdtArray - The input date_t array to be converted
//
//   Outputs :  A vector of GET_Date Unique Pointer objects (GET_DateUnqPtr) converted from the input tag_t array
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_arrayToVector ( const int, const date_t*, vector<GET_DateUnqPtr>& );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_vectorToArray
//
//   Purpose :  Function to convert a vector of bool objects into an array of logical objects
//
//   Inputs  :  vInput - The input vector containing the bool objects
//
//   Outputs :  An array of logical objects converted from the input bool vector
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_vectorToArray ( const vector<bool>, logical** );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_vectorToArray
//
//   Purpose :  Function to convert a vector of GET_POM_objectShrPtr objects into an array of tag_t objects
//
//   Inputs  :  vInput - The input vector containing the GET_POM_object Shared Pointer objects
//
//   Outputs :  An array of tag_t objects converted from the input GET_POM_objectShrPtr vector
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_vectorToArray ( const vector<GET_POM_objectShrPtr>, tag_t** );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_vectorToArray
//
//   Purpose :  Function to convert a vector of GET_POM_application_objectShrPtr objects into an array of tag_t objects
//
//   Inputs  :  vInput - The input vector containing the GET_POM_application_objectShrPtr Shared Pointer objects
//
//   Outputs :  An array of tag_t objects converted from the input GET_POM_application_objectShrPtr vector
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_vectorToArray ( const vector<GET_POM_application_objectShrPtr>, tag_t** );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_vectorToArray
//
//   Purpose :  Function to convert a vector of GET_DateUnqPtr objects into an array of date_t objects
//
//   Inputs  :  vInput - The input vector containing the GET_Date Unique Pointer objects
//
//   Outputs :  An array of date_t objects converted from the input GET_DateUnqPtr vector
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_vectorToArray ( const vector<GET_DateShrPtr>, date_t** );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET_free_tc_array
//
//   Purpose :   To free memory allocated by MEM_alloc() for double pointers.
//
//   Inputs  :   iArraySize - The Size of the array to be freed (int)
//               ppvArray - The input double pointer to be freed (void**)
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_free_tc_array ( const int, void** );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET_free_tc_array
//
//   Purpose :  To free memory allocated by MEM_alloc() for triple pointers.
//
//   Inputs  :  iRowCount - The Row Count of the array to be freed (int)
//              iColCount - The Column Count of the array to be freed (int)
//              ppvArray - The input double pointer to be freed (void***)
//
//   Outputs :  none
//
//   Return  :  none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     07 Apr, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void GET_free_tc_array ( const int, const int, void*** );

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   loginToTC
//
//   Purpose :   Method for Teamcenter login
//
//   Inputs  :   sUserId - The string Teamcenter User ID. If empty, auto login will be attempted
//               sPassword - The string Teamcenter password for the User
//               sGroup - The string Teamcenter group for login
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT void loginToTC ( string sUserId, string sPassword, string sGroup );

#endif // GET_TC_UTILS_HXX_
