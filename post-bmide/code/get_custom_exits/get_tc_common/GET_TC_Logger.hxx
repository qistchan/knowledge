
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

#ifndef GET_TC_LOGGER_HXX
#define GET_TC_LOGGER_HXX

#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <string>
#include <vector>

#include <mld/logging/Logger.hxx>

namespace get
{
	class DLLEXPORT GET_TC_Logger
	{
		public:
			static GET_TC_Logger* getInstance();
		protected:
			GET_TC_Logger();
		private:
			static GET_TC_Logger* _instance;
	};

	// Macro to log a DEBUG message
	#define LOG_DEBUG(key, message) \
	{ \
		Teamcenter::Logging::Logger *tc_logger = Teamcenter::Logging::Logger::getLogger ( key ); \
        if ( tc_logger->isDebugEnabled() ) \
        { \
            tc_logger->debug ( message ); \
        } \
	}

	// Macro to log a INFO message
	#define LOG_INFO(key, message) \
	{ \
		Teamcenter::Logging::Logger *tc_logger = Teamcenter::Logging::Logger::getLogger ( key ); \
        if ( tc_logger->isInfoEnabled() ) \
        { \
            tc_logger->info ( message ); \
        } \
	}

	// Macro to log a WARN message
	#define LOG_WARN(key, message) \
	{ \
		Teamcenter::Logging::Logger *tc_logger = Teamcenter::Logging::Logger::getLogger ( key ); \
        if ( tc_logger->isWarnEnabled() ) \
        { \
            tc_logger->warn ( message ); \
        } \
	}

	// Macro to log a ERROR message
	#define LOG_ERROR(key, message) \
	{ \
		Teamcenter::Logging::Logger *tc_logger = Teamcenter::Logging::Logger::getLogger ( key ); \
        if ( tc_logger->isErrorEnabled() ) \
        { \
            tc_logger->error ( message ); \
        } \
	}

	// Macro to log a FATAL message
	#define LOG_FATAL(key, message) \
	{ \
		Teamcenter::Logging::Logger *tc_logger = Teamcenter::Logging::Logger::getLogger ( key ); \
        if ( tc_logger->isFatalEnabled() ) \
        { \
            tc_logger->fatal(message); \
        } \
	}

	// Macro to log a Trace message
	#define LOG_TRACE(key, message) \
    { \
		Teamcenter::Logging::Logger *tc_logger = Teamcenter::Logging::Logger::getLogger ( key ); \
		if ( tc_logger->isTraceEnabled() ) \
		{ \
			tc_logger->trace ( message ); \
		} \
    }
}

#endif // GET_TC_LOGGER_HXX
