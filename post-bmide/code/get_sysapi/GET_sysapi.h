/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_sysapi.h
//
//    Purpose:   Library of platform independent calls header
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_SYSAPI_H
#define GET_SYSAPI_H

#include <GET_cpp_stl.h>

#ifdef UNX
    #include <get_unx/GET_syscmd.h>
    #include <get_unx/GET_unx.h>
    #include <get_unx/GET_sysconst.h>
    #include <get_unx/GET_syspath.h>
    #include <get_unx/GET_Memory.hxx>
#elif linux
    #include <get_unx/GET_syscmd.h>
    #include <get_unx/GET_unx.h>
    #include <get_unx/GET_sysconst.h>
    #include <get_unx/GET_syspath.h>
    #include <get_unx/GET_Memory.hxx>
#elif __linux__
    #include <get_unx/GET_syscmd.h>
    #include <get_unx/GET_unx.h>
    #include <get_unx/GET_sysconst.h>
    #include <get_unx/GET_syspath.h>
    #include <get_unx/GET_Memory.hxx>
#elif WIN32
    #include <get_win32/GET_syscmd.h>
    #include <get_win32/GET_win32.h>
    #include <get_win32/GET_sysconst.h>
    #include <get_win32/GET_syspath.h>
    #include <get_win32/GET_Memory.hxx>
#elif WIN64
    #include <get_win32/GET_syscmd.h>
    #include <get_win32/GET_win32.h>
    #include <get_win32/GET_sysconst.h>
    #include <get_win32/GET_syspath.h>
    #include <get_win32/GET_Memory.hxx>
#elif WINNT
    #include <get_win32/GET_syscmd.h>
    #include <get_win32/GET_win32.h>
    #include <get_win32/GET_sysconst.h>
    #include <get_win32/GET_syspath.h>
    #include <get_win32/GET_Memory.hxx>
#endif


/* Need to export dll symbols on WIN32 */

#ifdef WIN32
    #define DLLEXPORT __declspec(dllexport)
#elif WIN64
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT
#endif


//#define SUCCESS    0
#define FAILURE    -1

#define CHAR64(c)  (((c) < 0 || (c) > 127) ? -1 : index_64[(c)])

static char index_64[128] = {
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
};

#define MAX_ENCRYPT_PWD_LEN  137


/* Function Prototypes */

extern DLLEXPORT void  GET_SYSAPI_getDate (
    const char* dateFormat,   /* <I> */
    char** date               /* <O> */
);

extern DLLEXPORT char* GET_SYSAPI_makeUniqueName (
    int                       /* <I> */
);

extern DLLEXPORT int   GET_SYSAPI_deleteFilesInDirectory (
    char* szDirName           /* <I> */
);

extern DLLEXPORT int   GET_SYSAPI_createDirectory (
    const char* szDir,        /* <I> */
    int iMode                  /* <I> */
);

extern DLLEXPORT void  GET_SYSAPI_removeDirectory (
    const char* szDir         /* <I> */
);

extern DLLEXPORT void  GET_SYSAPI_renameDirectory (
    const char* szDir,        /* <I> */
    const char* pszNewName    /* <I> */
);

extern DLLEXPORT int   GET_SYSAPI_getProcessId( void );

extern DLLEXPORT int   GET_SYSAPI_unLink(
    char* tempFile            /* <I> */
);

extern DLLEXPORT char* GET_SYSAPI_getLogin( void );

extern DLLEXPORT char* GET_SYSAPI_getTempFileName(
    char* siteCode,             /* <I> */
    int   pid,                  /* <I> */
    int   isTestImage           /* <I> */
);

extern DLLEXPORT char* GET_SYSAPI_getTempDir( void );

extern DLLEXPORT char* GET_SYSAPI_getFileSeparator( void );

extern DLLEXPORT char* GET_SYSAPI_getPATHSeparator( void );

extern DLLEXPORT int   GET_SYSAPI_zipDir(
    char* tmp_loc,            /* <I> */
    char* tar_ball            /* <I> */
);

extern DLLEXPORT int   GET_SYSAPI_moveDir(
    char* tmp_loc,            /* <I> */
    char* tar_ball,           /* <I> */
    char* siteCode,           /* <I> */
    int   isTestImage         /* <I> */
);

extern DLLEXPORT FILE* GET_SYSAPI_createPipe(
   const char* szCommand,    /* <I> */
   const char* mode          /* <I> */
);

extern DLLEXPORT int GET_SYSAPI_closePipe(
   FILE* fp                  /* <I> */
);

extern DLLEXPORT char* GET_SYSAPI_deleteFiles( void );

extern DLLEXPORT void GET_SYSAPI_clearScreen( void );

extern DLLEXPORT char* GET_SYSAPI_getExportLogDirPath(
    int isTestImage             /* <I> */
);

extern DLLEXPORT char* GET_SYSAPI_getHomeDir( void );

extern DLLEXPORT int GET_SYSAPI_getHostName (
    char** szHostName   /* <OF> */
);

extern DLLEXPORT char* GET_SYSAPI_getDomainName(void);

extern DLLEXPORT int GET_SYSAPI_copyFile(
    char* szFile1,           /* <I> */
    char* szFile2            /* <I> */
);

extern DLLEXPORT int GET_SYSAPI_copyDir(
    char* szDir1,           /* <I> */
    char* szDir2            /* <I> */
);

extern DLLEXPORT void GET_SYSAPI_changeDirPermission(
    char* szDirName,        /* <I> */
    int iMode               /* <I> */
);

extern DLLEXPORT char* GET_SYSAPI_openFile(void);

extern DLLEXPORT void GET_SYSAPI_newConsole(void);

extern DLLEXPORT void GET_SYSAPI_sleep(
    int iTime               /* <I> */
);

extern DLLEXPORT void GET_SYSAPI_sleepMilli(
    int iTime               /* <I> */
);


extern DLLEXPORT int GET_SYSAPI_moveFiles(
    char* szSrcLoc,        /* <I> */
    char* szDesLoc         /* <I> */
);

extern DLLEXPORT void GET_SYSAPI_renameTifFiles(
	char* szTmpDir,        /* <I> */
	char* szTabNum,        /* <I> */
	char* szItemId         /* <I> */
);

extern DLLEXPORT void GET_SYSAPI_renameFiles(
	char* szTmpDir,        /* <I> */
	char* szTabNum,        /* <I> */
	char* szItemId,         /* <I> */
	char* szFileType	   /* <I> */
);

extern DLLEXPORT int GET_SYSAPI_runBackgroundSystemCommand(
    char* command         /* <I> */
);

extern DLLEXPORT int GET_SYSAPI_basename(
    const char* path,        /* <I> */
    char**      base         /* <OF> */
);

extern DLLEXPORT int GET_SYSAPI_connectServer  (
    const char* szServer, /* <I> */
    const int iPort,     /*  <I> */
    int* iSocketFd  /* <O> */
);

extern DLLEXPORT int GET_SYSAPI_sendRequest (
    const int iSockFd , /* <I> */
    const char *szBuf  /* <I> */
);

extern DLLEXPORT int GET_SYSAPI_receiveResponse (
    const int iSockFd, /* <I> */
    const int iWaitTime, /* <I> */
    const int iSleepTime, /* <I> */
    char** szResponse /* <O> */
);

extern DLLEXPORT int GET_SYSAPI_closeConnection (
    const int iSockFd /* <I> */
);

extern DLLEXPORT int GET_SYSAPI_intToString (
    const long value,
    char* string
);

extern DLLEXPORT char* GET_SYSAPI_getUserLoginID ( void );

extern DLLEXPORT char* GET_SYSAPI_getEnvVariableValue (
    char* szEnvVarName
);

extern DLLEXPORT int GET_SYSAPI_check_FileOrDirExists (
    const char *path
);

extern DLLEXPORT int GET_SYSAPI_changeDirectory (
    const char *path
);

extern DLLEXPORT char* GET_SYSAPI_PrepStringForCmd (
    const char* stringVal
);

extern DLLEXPORT int  GET_SYSAPI_Scan_FilesInDirectory (
    char* dirName,            /* <I> */
    int MaxFile_Count,        /* <I> */
    char*** files,              /* <O> */
    int* file_count           /* <O> */
);

extern DLLEXPORT int  GET_SYSAPI_Scan_FilesInDirectory (
    char* dirName,            /* <I> */
    int MaxFile_Count,        /* <I> */
    char*** files,              /* <O> */
    int* file_count           /* <O> */
);

extern DLLEXPORT char* GET_SYSAPI_getCurrentTimeMilli ( void );

extern DLLEXPORT bool GET_SYSAPI_regexMatch ( const char* sPattern, const char* sValue );

extern DLLEXPORT int GET_SYSAPI_decode64 (const char * inStr,
                                    unsigned inStrLen,
                                    char * outStr,
                                    unsigned * outStrLen);

#endif /* GET_SYSAPI_H */
