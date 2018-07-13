
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_errors.h
//
//    Purpose:   Header file for dealing with Teamcenter errors
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     3 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_ERRORS_H
#define GET_ERRORS_H

#include <tc/emh.h>
#include <common/emh_const.h>

//the 900 series error codes are used for exception handling

#define GET_general_exception ( EMH_USER_error_base + 900 )

// Macro to log a EMH_error_store_1 msg
#define LOG_EMH_ERROR_1(severity, iFail, message) \
{ \
    EMH_store_error_s1 ( severity, iFail, message ); \
}

#endif
