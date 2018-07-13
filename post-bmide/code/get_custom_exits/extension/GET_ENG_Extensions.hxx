
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ENG_Extensions.hxx
//
//    Purpose:   Header File defining the GE Transportation extension implementation
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     28 Apr, 2016         Initial creation
//  TCS Development Team     16 Nov, 2016         Created a Pre-Action Extension method for finalizeCreateInput operation
//  Ganesh Ubale             25 Apr, 2017         Created a Pre-Condition Extension method GET6_revisePreCondition for ITEM_copy_rev operation
//  TechM Development Team   30 June, 2017        Modified GET6_revisePreCondition to check the revision id sequence
//  TCS Development Team     01 Sep, 2017         Added property getter method GET6_get6CASDownloderURLGetValue
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_ENG_EXTENSIONS_HXX
#define GET_ENG_EXTENSIONS_HXX

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_Utils.hxx>

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/tc.h>
#include <tccore/custom.h>
#include <tccore/tctype.h>
#include <string>
#include <algorithm>

#define ECN_TYPE_PREFIX "ECN"
#define REVISE_LATEST_ERR_MSG "Only the latest Item Revision can be selected for the revise operation"
#define NEXT_REVID_VALIDATION_ERR_MSG "New Revision Id should always be greater than previous Revision Id"
#define REVID_VALIDATION_ERR_MSG  "Given Revision Id is invalid"

#ifdef __cplusplus
extern "C"
{
#endif

extern DLLEXPORT int GET6_setECNID ( METHOD_message_t*, va_list );
extern DLLEXPORT int GET6_propagatePropsECRToECN ( METHOD_message_t*, va_list );
extern DLLEXPORT int GET6_generateRevID ( int*, va_list );
extern DLLEXPORT int GET6_verifyIPClassificationAccess ( METHOD_message_t*, va_list );
extern DLLEXPORT int GET6_validateOverallUOM ( METHOD_message_t* msg, va_list args );
extern DLLEXPORT int GET6_revisePreCondition ( METHOD_message_t* msg, va_list args );
extern DLLEXPORT int GET6_get6CASDownloderURLGetValue ( METHOD_message_t*  msg, va_list  args );

#ifdef __cplusplus
}
#endif

#endif // GET_ENG_EXTENSIONS_HXX
