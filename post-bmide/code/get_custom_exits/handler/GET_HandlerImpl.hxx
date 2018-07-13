
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_HandlerImpl.hxx
//
//    Purpose:   Header File defining the GE Transportation Workflow Handler Implementation Abstraction
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     28 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_HANDLERIMPL_HXX
#define GET_HANDLERIMPL_HXX

// GET Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// Teamcenter Includes
#include <epm/epm.h>
#include <tc/tc.h>
#include <tc/tc_arguments.h>
#include <tccore/tctype.h>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

// Function Prototypes

template <typename T>
extern DLLEXPORT void GET_processHandler ( T msg, void ( *implFnPointer ) ( const tag_t, map<int, vector<tag_t> >&, map <string, string>& ), bool = true, bool = true );

#ifdef __cplusplus
extern "C"
{
#endif

extern DLLEXPORT int GET6_registerHandlers();
extern DLLEXPORT void catchHandlerExceptions ( string );

#ifdef __cplusplus
}
#endif

#endif // GET_HANDLERIMPL_HXX
