
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_TC_Logger.cxx
//
//    Purpose:   Class for Teamcenter Logging
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     13 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifdef GE_ENABLE_LOG4CXX // Use compiler directive to activate log4cxx

#include <GET_TC_Logger.hxx>

namespace get
{
	// Initialize instance as null
	GET_TC_Logger *Logger::_instance = 0;

	/**
	 * Protected constructor
	 */
	GET_TC_Logger::GET_TC_Logger()
	{
	}

	/**
	 * Public method for geting a pointer to the instance
	 */
	GET_TC_Logger* GET_TC_Logger::getInstance()
	{
		if ( _instance == 0 )
		{
			_instance = new Logger();
		}
		return _instance;
	}
}

#endif
