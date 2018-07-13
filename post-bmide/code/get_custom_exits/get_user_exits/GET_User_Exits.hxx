
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_User_Exits.hxx
//
//   Purpose:   Header File defining the GE Transportation User Exits Implementation
//
//   History:
//   Who                      Date                 Description
//   TCS Development Team     17 Nov, 2016         Initial creation
//   TCS Development Team     01 Sep, 2017         Added User Exit implementation method for USER_gs_shell_init_module
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_USET_EXITS_HXX
#define GET_USET_EXITS_HXX

#include <GET_sysapi.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern DLLEXPORT int libGET6_custom_exits_register_callbacks();
extern DLLEXPORT int GET_gsShellInitModule ( int *decision, va_list args );

#ifdef __cplusplus
}
#endif

#endif // GET_USET_EXITS_HXX
