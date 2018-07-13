
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_MFG_Extensions.hxx
//
//    Purpose:   Header File defining the GE Transportation extension implementation
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     31 May, 2017         Initial creation
//  TCS Development team     31 May, 2017         Extension to validate UOM for Stock Material
//  TCS Development team     21 Jun, 2017         Extension to check if Project is filled
//                                                or not for UserSession.
//  TCS Development team     02 Aug, 2017         Extension Method added to trigger propagation rules
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_MFG_EXTENSIONS_HXX
#define GET_MFG_EXTENSIONS_HXX

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


#ifdef __cplusplus
extern "C"
{
#endif

extern DLLEXPORT int GET6_validateStockMtrlUOMCreate ( METHOD_message_t* msg, va_list args );
extern DLLEXPORT int GET6_validateStockMtrlUOMSave ( METHOD_message_t* msg, va_list args );
extern DLLEXPORT int GET6_checkProjectContext ( METHOD_message_t* msg, va_list args );
extern DLLEXPORT int GET6_bvrPostActionForCreatePost ( METHOD_message_t* msg, va_list args );

#ifdef __cplusplus
}
#endif

#endif // GET_MFG_EXTENSIONS_HXX
