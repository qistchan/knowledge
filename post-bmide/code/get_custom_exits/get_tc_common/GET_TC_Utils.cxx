
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_TC_Utils.cxx
//
//    Purpose:   Source File for common Teamcenter Utility Methods
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     09 Mar, 2016         Initial creation
//  TCS Development Team     19 May, 2017         Added Teamcenter login method for command line utilities
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_TC_Utils.hxx>

// Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

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
extern DLLEXPORT void GET_arrayToVector ( const int iArraySize, const logical *plArray, vector<bool> &vOutput )
{
    for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
    {
        vOutput.push_back ( plArray[iIndex] == FALSE ? false : true );
    }
}

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
extern DLLEXPORT void GET_arrayToVector ( const int iArraySize, const tag_t *ptArray, vector<GET_POM_objectUnqPtr> &vOutput )
{
    for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
    {
        vOutput.push_back ( GET_POM_object::getInstance ( ptArray[iIndex] ) );
    }
}

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
extern DLLEXPORT void GET_arrayToVector ( const int iArraySize, const tag_t *ptArray, vector<GET_POM_application_objectUnqPtr> &vOutput )
{
   for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
   {
       vOutput.push_back ( GET_POM_application_object::getInstance ( ptArray[iIndex] ) );
   }
}

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
extern DLLEXPORT void GET_arrayToVector ( const int iArraySize, const date_t *pdtArray, vector<GET_DateUnqPtr> &vOutput )
{
    for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
    {
        vOutput.push_back ( GET_Date::getInstance ( pdtArray[iIndex] ) );
    }
}

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
extern DLLEXPORT void GET_vectorToArray ( const vector<bool> vInput, logical **pplOutput )
{
    if ( vInput.size() > 0 )
    {
        *pplOutput = ( logical* ) malloc ( sizeof ( logical ) * vInput.size() );
        for ( unsigned int iIndex = 0; iIndex < vInput.size(); iIndex++ )
        {
            ( *pplOutput ) [iIndex] = ( vInput[iIndex] == true ? TRUE : FALSE );
        }
    }
}

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
extern DLLEXPORT void GET_vectorToArray ( const vector<GET_POM_objectShrPtr> vInput, tag_t **pptOutput )
{
    if ( vInput.size() > 0 )
    {
        *pptOutput = ( tag_t* ) malloc ( sizeof ( tag_t ) * vInput.size() );
        for ( unsigned int iIndex = 0; iIndex < vInput.size(); iIndex++ )
        {
            ( *pptOutput ) [iIndex] = vInput[iIndex]->getTag();
        }
    }
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:  GET_vectorToArray
 //
 //   Purpose :  Function to convert a vector of GET_POM_application_objectShrPtr objects into an array of tag_t objects
 //
 //   Inputs  :  vInput - The input vector containing the GET_POM_object Shared Pointer objects
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
extern DLLEXPORT void GET_vectorToArray ( const vector<GET_POM_application_objectShrPtr> vInput, tag_t **pptOutput )
{
    if ( vInput.size() > 0 )
    {
        *pptOutput = ( tag_t* ) malloc ( sizeof ( tag_t ) * vInput.size() );
        for ( unsigned int iIndex = 0; iIndex < vInput.size(); iIndex++ )
        {
            ( *pptOutput ) [iIndex] = vInput[iIndex]->getTag();
        }
    }
}


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
extern DLLEXPORT void GET_vectorToArray ( const vector<GET_DateShrPtr> vInput, date_t **ppdtOutput )
{
    if ( vInput.size() > 0 )
    {
        *ppdtOutput = ( date_t* ) malloc ( sizeof ( date_t ) * vInput.size() );
        for ( unsigned int iIndex = 0; iIndex < vInput.size(); iIndex++ )
        {
            ( *ppdtOutput ) [iIndex] = vInput[iIndex]->getDate();
        }
    }
}

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
extern DLLEXPORT void GET_free_tc_array ( const int iArraySize, void **ppvArray )
{
    // Free the array members and the top level variable
    if ( ppvArray != NULL && iArraySize >= 1 )
    {
        for ( int iIndex = 0; iIndex < iArraySize; iIndex++ )
        {
            if ( ppvArray[iIndex] != NULL )
            {
                MEM_free ( ppvArray[iIndex] );
                ppvArray[iIndex] = NULL;
            }
        }

        MEM_free ( ppvArray );
        ppvArray = NULL;
    }
}

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
extern DLLEXPORT void GET_free_tc_array ( const int iRowCount, const int iColcount, void ***pppvArray )
{
    for ( int iRowIndex = 0; iRowIndex < iRowCount; iRowIndex++ )
    {
        // Free the Memory occupied by the columns
        for ( int iColIndex = 0; iColIndex < iColcount; iColIndex++ )
        {
            if ( pppvArray[iRowIndex][iColIndex] != NULL )
            {
                MEM_free ( pppvArray[iRowIndex][iColIndex] );
                pppvArray[iRowIndex][iColIndex] = NULL;
            }
        }

        // Free the Memory occupied by the rows
        if ( pppvArray[iRowIndex] != NULL )
        {
            MEM_free ( pppvArray[iRowIndex] );
            pppvArray[iRowIndex] = NULL;
        }
    }

    // Free the Memory occupied by the object
    if ( pppvArray != NULL )
    {
        MEM_free ( pppvArray );
        pppvArray = NULL;
    }
}

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
extern DLLEXPORT void loginToTC ( string sUserId, string sPassword, string sGroup )
{
    ResultCheck stat;

    /* Initialize text services. */
    stat = ITK_initialize_text_services ( 0 );
    /* Set Journalling. */
    stat = ITK_set_journalling( 1 );

    /* Login to TC. */
    if ( ! sUserId.empty() )
    {
        if ( sPassword.empty() )
        {
            /*
            * This occurs if the user hasn't specified -p= option in the
            * command line. So use user Id as the password
            */
            sPassword = sUserId;
        }
        stat = ITK_init_module ( sUserId.c_str(), sPassword.c_str(), sGroup.c_str() );
    }
    else
    {
        // If user data is not supplied, use auto login
        stat = ITK_auto_login();
    }
}
