#ifndef	_GET_OCCI_INCLUDES_H_
#define	_GET_OCCI_INCLUDES_H_

#ifdef WIN32
    #define DLLEXPORT __declspec(dllexport)
    #define DLLIMPORT __declspec(dllimport)
#elif WIN64
    #define DLLEXPORT __declspec(dllexport)
    #define DLLIMPORT __declspec(dllimport)
#else
    #define DLLEXPORT
    #define DLLIMPORT
#endif

// Oracle Includes
#include <occi.h>
#include <occiCommon.h>

#include "GET_OCCI.h"
#include "GET_ResultSet.h"
#include "GET_OCCI_DateTime.h"

#include <assert.h>
#ifndef	ASSERT
#	define	ASSERT	assert
#endif


#endif
