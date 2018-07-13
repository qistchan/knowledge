
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_cpp_stl.h
//
//    Purpose:   Handle the differences between Windows and Unix 
//    STL implementations
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_CPP_STL_H
#define GET_CPP_STL_H


#ifdef _HPUX_SOURCE
    #include <iostream.h>
    #include <fstream.h>
    #include <strstream.h>
    #include <sstream.h>
	#include <string.h>
#else
    #include <iostream>
    #include <fstream>
    //#include <strstream>
    #include <sstream>
	#include <string>
    using namespace std;
#endif




#endif /* GET_CPP_STL_H */
