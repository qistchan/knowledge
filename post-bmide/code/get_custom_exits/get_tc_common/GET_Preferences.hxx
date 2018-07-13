
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Preferences.hxx
//
//   Purpose :   Header File for dealing with Teamcenter Preferences
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_PREFERENCES_HXX
#define GET_PREFERENCES_HXX

// TC Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <tccore/item.h>
#include <tc/iman_preferences.h>

// GE includes
#include <GET_sysapi.h>

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
    extern DLLEXPORT void getStringPrefValues ( const string, vector<string>&, const TC_preference_search_scope_t &scope = TC_preference_site );

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
    extern DLLEXPORT void getIntPrefValues ( const string, vector<int>&, const TC_preference_search_scope_t &scope = TC_preference_site );

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
    extern DLLEXPORT void getDoublePrefValues ( const string, vector<double>&, const TC_preference_search_scope_t &scope = TC_preference_site );

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
    extern DLLEXPORT void getLogicalPrefValues ( const string, vector<bool>&, const TC_preference_search_scope_t &scope = TC_preference_site );

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
    extern DLLEXPORT void setStringPrefValues ( const string, const vector<string>, const TC_preference_search_scope_t &scope = TC_preference_site );

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
    extern DLLEXPORT void setIntPrefValues ( const string, const vector<int>, const TC_preference_search_scope_t &scope = TC_preference_site );

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
    extern DLLEXPORT void setDoublePrefValues ( const string, const vector<double>, const TC_preference_search_scope_t &scope = TC_preference_site );

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
    extern DLLEXPORT void setLogicalPrefValues ( const string, const vector<bool>, const TC_preference_search_scope_t &scope = TC_preference_site );
}

#endif // GET_PREFERENCES_HXX
