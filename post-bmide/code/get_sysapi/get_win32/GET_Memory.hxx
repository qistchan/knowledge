
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Memory.hxx
//
//    Purpose:   Header File for Smart Pointer Implementation
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     08 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_MEMORY_HXX_
#define GET_MEMORY_HXX_

// CPP Includes
#include <memory>

// GE Includes
#include <GET_cpp_stl.h>

// Function Prototypes
#define MAKE_UNIQUE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4)   \
  template<class T COMMA LIST(_CLASS_TYPE)>  \
  inline unique_ptr<T> make_unique(LIST(_TYPE_REFREF_ARG))  \
  {  \
      return unique_ptr<T>(new T(LIST(_FORWARD_ARG)));  \
  }
_VARIADIC_EXPAND_0X(MAKE_UNIQUE, , , , )
#undef MAKE_UNIQUE

#endif /*GET_MEMORY_HXX_*/
