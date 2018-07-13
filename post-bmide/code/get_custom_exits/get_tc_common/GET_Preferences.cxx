
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Preferences.cxx
//
//   Purpose :   Source File for dealing with Teamcenter Preferences
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// TC includes
#include <ae/ae.h>
#include <sa/am.h>
#include <epm/cr.h>
#include <tccore/aom.h>
#include <tccore/aom_prop.h>
#include <ae/dataset.h>
#include <sa/sa.h>
#include <sa/group.h>
#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <sa/tcfile.h>
#include <tccore/item.h>
#include <pom/pom/pom.h>
#include <ss/ss_const.h>
#include <tccore/workspaceobject.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// GE includes
#include <GET_TC_Utils.hxx>
#include <GET_Preferences.hxx>
#include <GET_Utils.hxx>
#include <GET_sysapi.h>

const string logger = "get.get_tc_common.GET_Preferences";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getStringPrefValues ( const string, vector<string>&, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get string preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //   Outputs :   Vector of preference values (vector<string>&)
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void getStringPrefValues ( const string sPrefName, vector<string> &vPrefValues, const TC_preference_search_scope_t &scope )
    {
        char **ppcPrefValues = NULL;

        int iPrefCount = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::getStringPrefValues" );

        stat = PREF_ask_char_values_at_location ( sPrefName.c_str(), scope, &iPrefCount, &ppcPrefValues );
        for ( int iIndex = 0; iIndex < iPrefCount; iIndex++ )
        {
            // Store the Pref Value in the Output Vector
            vPrefValues.push_back ( ppcPrefValues[iIndex] );
        }

        // Free the Memory
        MEM_free ( ppcPrefValues );

        LOG_TRACE ( logger, "END : GET_Preferences::getStringPrefValues" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getIntPrefValues ( const string, vector<int>&, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get int preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //
    //   Outputs :   Vector of preference values (vector<int>&)
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void getIntPrefValues ( const string sPrefName, vector<int> &vPrefValues, const TC_preference_search_scope_t &scope )
    {
        int *piPrefValues = NULL;

        int iPrefCount = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::getIntPrefValues" );

        stat = PREF_ask_int_values_at_location ( sPrefName.c_str(), scope, &iPrefCount, &piPrefValues );
        for ( int iIndex = 0; iIndex < iPrefCount; iIndex++ )
        {
            // Store the Pref Value in the Output Vector
            vPrefValues.push_back ( piPrefValues[iIndex] );
        }

        // Free the Memory
        MEM_free ( piPrefValues );

        LOG_TRACE ( logger, "END : GET_Preferences::getIntPrefValues" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getDoublePrefValues ( const string, vector<double>&, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get int preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //
    //   Outputs :   Vector of preference values (vector<double>&)
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void getDoublePrefValues ( const string sPrefName, vector<double> &vPrefValues, const TC_preference_search_scope_t &scope )
    {
        double *pdPrefValues = NULL;

        int iPrefCount = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::getDoublePrefValues" );

        stat = PREF_ask_double_values_at_location ( sPrefName.c_str(), scope, &iPrefCount, &pdPrefValues );
        for ( int iIndex = 0; iIndex < iPrefCount; iIndex++ )
        {
            // Store the Pref Value in the Output Vector
            vPrefValues.push_back ( pdPrefValues[iIndex] );
        }

        // Free the Memory
        MEM_free ( pdPrefValues );

        LOG_TRACE ( logger, "END : GET_Preferences::getDoublePrefValues" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getLogicalPrefValues ( const string, vector<bool>&, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get int preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //
    //   Outputs :   Vector of preference values (vector<bool>&)
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void getLogicalPrefValues ( const string sPrefName, vector<bool> &vPrefValues, const TC_preference_search_scope_t &scope )
    {
        logical *plPrefValues = NULL;

        int iPrefCount = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::getLogicalPrefValues" );

        stat = PREF_ask_logical_values_at_location ( sPrefName.c_str(), scope, &iPrefCount, &plPrefValues );
        for ( int iIndex = 0; iIndex < iPrefCount; iIndex++ )
        {
            // Store the Pref Value in the Output Vector
            vPrefValues.push_back ( plPrefValues[iIndex] == TRUE ? true : false );
        }

        // Free the Memory
        if ( plPrefValues != NULL )
        {
        	MEM_free ( plPrefValues );
        }

        LOG_TRACE ( logger, "END : GET_Preferences::getLogicalPrefValues" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setStringPrefValues ( const string, const vector<string>, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get int preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               vPrefValues - Vector of preference values (const vector<string>)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void setStringPrefValues ( const string sPrefName, const vector<string> vPrefValues, const TC_preference_search_scope_t &scope )
    {
        char **ppcPrefValues = NULL;

        IFail *exception = NULL;

        int iPrefCount = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::setStringPrefValues" );

        try
        {
            // Convert the vector to array
            GET_vectorToArray ( vPrefValues, &ppcPrefValues );
            stat = PREF_set_char_values_at_location ( sPrefName.c_str(), scope, vPrefValues.size(), ppcPrefValues );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free_array ( ( int ) vPrefValues.size(), ( void** ) ppcPrefValues );

        // Throw the exceptions, if any to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Preferences::setStringPrefValues" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setIntPrefValues ( const string, const vector<int>, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get int preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               vPrefValues - Vector of preference values (const vector<int>)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void setIntPrefValues ( const string sPrefName, const vector<int> vPrefValues, const TC_preference_search_scope_t &scope )
    {
        IFail *exception = NULL;

        int iPrefCount = 0;

        int *piPrefValues = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::setIntPrefValues" );

        try
        {
            // Convert the vector to array
            GET_vectorToArray ( vPrefValues, &piPrefValues );
            stat = PREF_set_int_values_at_location ( sPrefName.c_str(), scope, vPrefValues.size(), piPrefValues );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free ( ( void* ) piPrefValues );

        // Throw the exceptions, if any to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Preferences::setIntPrefValues" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setDoublePrefValues ( const string, const vector<double>, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get int preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               vPrefValues - Vector of preference values (const vector<double>)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void setDoublePrefValues ( const string sPrefName, const vector<double> vPrefValues, const TC_preference_search_scope_t &scope )
    {
        IFail *exception = NULL;

        double *pdPrefValues = NULL;

        int iPrefCount = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::setDoublePrefValues" );

        try
        {
            // Convert the vector to array
            GET_vectorToArray ( vPrefValues, &pdPrefValues );
            stat = PREF_set_double_values_at_location ( sPrefName.c_str(), scope, vPrefValues.size(), pdPrefValues );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free ( ( void* ) pdPrefValues );

        // Throw the exceptions, if any to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Preferences::setDoublePrefValues" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setLogicalPrefValues ( const string, const vector<bool>, const TC_preference_search_scope_t& )
    //
    //   Purpose :   Method to get int preference values
    //
    //   Inputs  :   sPrefName   - Preference Name(const string)
    //               vPrefValues - Vector of preference values (const vector<bool>)
    //               scope       - Scope of the preference(const TC_preference_search_scope_t&) *(optional - Site Scope is the default)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     02 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    extern DLLEXPORT void setLogicalPrefValues ( const string sPrefName, const vector<bool> vPrefValues, const TC_preference_search_scope_t &scope )
    {
        IFail *exception = NULL;

        logical *plPrefValues = NULL;

        int iPrefCount = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Preferences::setLogicalPrefValues" );

        try
        {
            // Convert the vector to array
            GET_vectorToArray ( vPrefValues, &plPrefValues );
            stat = PREF_set_logical_values_at_location ( sPrefName.c_str(), scope, vPrefValues.size(), plPrefValues );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free ( ( void* ) plPrefValues );

        // Throw the exceptions, if any to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Preferences::setLogicalPrefValues" );
    }
}
