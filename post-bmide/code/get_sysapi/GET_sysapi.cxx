/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_sysapi.cxx
//
//    Purpose:  Library of platform independent calls.This is a library of platform independent calls.  Do not use any platform
// 				dependent calls in any other library, instead use the functions defined here.
//  			Additionally do not use any API specific calls in this library, it should be
//				plain C++.
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 Feb, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#include <GET_sysapi.h>

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getDate()
 //
 //    Purpose:   External accessor method to get date as a string in the specified format.
 //
 //    Inputs:     format - the specified date format(char *)
 //
 //    Outputs:    none
 //
 //    return:    date - the current date (Must be freed by caller)(char *)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT void GET_SYSAPI_getDate (const char* format,
                                           char** date)
{
    #ifdef UNX
        GET_UNX_getDate (format, date);
    #elif linux
        GET_UNX_getDate (format, date);
    #elif WIN32
        GET_WIN32_getDate (format, date);
    #elif WIN64
        GET_WIN32_getDate (format, date);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_makeUniqueName()
 //
 //    Purpose:   External accessor method to create a unique file name
 //
 //    Inputs:     pathLength - contains value of SS_MAXPATHLEN defined in
 //               ss_const.h (iMAN header file)(int)
 //
 //    Outputs:    none
 //
 //    return:    fileName - Unique Name of the file(char *) 
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT char* GET_SYSAPI_makeUniqueName (int pathLength)
{
    char* fileName = NULL;

    #ifdef UNX
        fileName = GET_UNX_makeUniqueName (pathLength);
    #elif linux
        fileName = GET_UNX_makeUniqueName (pathLength);
    #elif WIN32
        fileName = GET_WIN32_makeUniqueName (pathLength);
    #elif WIN64
        fileName = GET_WIN32_makeUniqueName (pathLength);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return fileName;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_deleteFilesInDirectory()
 //
 //    Purpose:   External accessor method to delete the files from a specified directory
 //
 //    Inputs:     dirName - directory name to be deleted(char*)
 //
 //    Outputs:    none
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 
extern DLLEXPORT int GET_SYSAPI_deleteFilesInDirectory (char* dirName)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_deleteFilesInDirectory (dirName);
    #elif linux
        ifail = GET_UNX_deleteFilesInDirectory (dirName);
    #elif WIN32
        ifail = GET_WIN32_deleteFilesInDirectory (dirName);
    #elif WIN64
        ifail = GET_WIN32_deleteFilesInDirectory (dirName);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_createDirectory()
 //
 //    Purpose:   External accessor method to create a directory with given permissions
 //
 //    Inputs:    dirName - name of the directory to be created(char*)
 //				  mode    - permissions for the directory(int)
 //
 //    Outputs:   none
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET_SYSAPI_createDirectory (const char* dirName,
                                                  int mode)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_createDirectory (dirName, mode);
    #elif linux
        ifail = GET_UNX_createDirectory (dirName, mode);
    #elif WIN32
        ifail = GET_WIN32_createDirectory (dirName, mode);
    #elif WIN64
        ifail = GET_WIN32_createDirectory (dirName, mode);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_removeDirectory()
 //
 //    Purpose:   External accessor method to remove the specified directory
 //
 //    Inputs:     dirName - name of the directory to be removed(char*)
 //
 //    return:     none
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_SYSAPI_removeDirectory (const char* dirName)
{
    #ifdef UNX
        GET_UNX_removeDirectory (dirName);
    #elif linux
        GET_UNX_removeDirectory (dirName);
    #elif WIN32
        GET_WIN32_removeDirectory (dirName);
    #elif WIN64
        GET_WIN32_removeDirectory (dirName);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_renameDirectory()
 //
 //    Purpose:   External accessor method to rename the specified directory
 //
 //    Inputs:    dirName - name of the directory to be renamed(char*)
 //               newName - new name for the directory(char*)
 //
 //    return:    none
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_SYSAPI_renameDirectory (const char* dirName,
                                                   const char* newName)
{
    #ifdef UNX
        GET_UNX_renameDirectory (dirName, newName);
    #elif linux
        GET_UNX_renameDirectory (dirName, newName);
    #elif WIN32
        GET_WIN32_renameDirectory (dirName, newName);    
    #elif WIN64
        GET_WIN32_renameDirectory (dirName, newName);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getProcessId()
 //
 //    Purpose:   External accessor method to Get the process ID
 //
 //    Inputs:    none
 //
 //    return:    Process ID(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_getProcessId (void)
{
    int pid = 0;

    #ifdef UNX
        pid = GET_UNX_getProcessId();
    #elif linux
        pid = GET_UNX_getProcessId();
    #elif WIN32
        pid = GET_WIN32_getProcessId();
    #elif WIN64
        pid = GET_WIN32_getProcessId();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return pid;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_unLink()
 //
 //    Purpose:   External accessor method to delete a file
 //
 //    Inputs:    filename -  name of file to be deleted(char*)
 //
 //    Outputs:   none
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_unLink (char* filename)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_unLink (filename);
    #elif linux
        ifail = GET_UNX_unLink (filename);
    #elif WIN32
        ifail = GET_WIN32_unLink (filename);
    #elif WIN64
        ifail = GET_WIN32_unLink (filename);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_unLink()
 //
 //    Purpose:   External accessor method to get the user's login name on this machine
 //
 //    Inputs:    none
 //
 //    Outputs:   none
 //
 //    return:    login - user's login name (Must be freed by caller)(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_getLogin (void)
{
    char* login = NULL;

    #ifdef UNX
        login = GET_UNX_getLogin();
    #elif linux
        login = GET_UNX_getLogin();
    #elif WIN32
        login = GET_WIN32_getLogin();
    #elif WIN64
        login = GET_WIN32_getLogin();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return login;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getTempFileName()
 //
 //    Purpose:   External accessor method to generate a temporary file name using site code and process ID
 //
 //    Inputs:     siteCode    - site code ID(char*),
 //				  pid         - process ID(int),
 //               isTestImage - test image flag(int)
 //
 //    return:    tmpFile(char)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT char* GET_SYSAPI_getTempFileName (char* siteCode,
                                                    int pid,
                                                    int isTestImage)
{
    char* tmpFile = NULL;

    printf ("###################################################\n");
    printf ("# GET_SYSAPI_getTempFileName has been deprecated #\n");
    printf ("###################################################\n");

    #ifdef UNX
        tmpFile = GET_UNX_getTempFileName(siteCode, pid, isTestImage);
    #elif linux
        tmpFile = GET_UNX_getTempFileName(siteCode, pid, isTestImage);
    #elif WIN32
        tmpFile = GET_WIN32_getTempFileName(siteCode, pid, isTestImage);
    #elif WIN64
        tmpFile = GET_WIN32_getTempFileName(siteCode, pid, isTestImage);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return tmpFile;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getTempDir()
 //
 //    Purpose:   External accessor method to get name of the temporary directory
 //
 //    Inputs:     
 //
 //    return:    tmpDir - temporary directory name(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_getTempDir (void)
{
    char* tmpDir = NULL;

    #ifdef UNX
        tmpDir = GET_UNX_getTempDir();
    #elif linux
        tmpDir = GET_UNX_getTempDir();
    #elif WIN32
        tmpDir = GET_WIN32_getTempDir();
    #elif WIN64
        tmpDir = GET_WIN32_getTempDir();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return tmpDir;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getFileSeparator()
 //
 //    Purpose:   External accessor method to get the file separator for this platform
 //
 //    Inputs:    none
 //
 //    return:    file separator(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_getFileSeparator (void)
{
    char* fileSep = NULL;
    #ifdef UNX
        fileSep = GET_UNX_getFileSeparator();
    #elif linux
        fileSep = GET_UNX_getFileSeparator();
    #elif WIN32
        fileSep = GET_WIN32_getFileSeparator();
    #elif WIN64
        fileSep = GET_WIN32_getFileSeparator();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return fileSep;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getPATHSeparator()
 //
 //    Purpose:   External accessor method to get the PATH separator for this platform
 //
 //    Inputs:    none
 //
 //    return:    path separator(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_getPATHSeparator (void)
{
    char* pathSep = NULL;
    #ifdef UNX
        pathSep = GET_UNX_getPATHSeparator();
    #elif linux
        pathSep = GET_UNX_getPATHSeparator();
    #elif WIN32
        pathSep = GET_WIN32_getPATHSeparator();
    #elif WIN64
        pathSep = GET_WIN32_getPATHSeparator();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return pathSep;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_zipDir()
 //
 //    Purpose:   External accessor method to compress files into a ZIP archive
 //
 //    Inputs:     tmpLoc  - location of files to be compressed(char*),
 //               tarBall - compressed archive file name(char*)
 //
 //    return:    ifail- 0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET_SYSAPI_zipDir (char* tmpLoc,
                                         char* tarBall)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_zipDir (tmpLoc, tarBall);
    #elif linux
        ifail = GET_UNX_zipDir (tmpLoc, tarBall);
    #elif WIN32
        ifail = GET_WIN32_zipDir (tmpLoc, tarBall);
    #elif WIN64
        ifail = GET_WIN32_zipDir (tmpLoc, tarBall);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_moveDir()
 //
 //    Purpose:   External accessor method to move compressed files to a destination directory
 //
 //    Inputs:     tmpLoc 	  - absolute directory name containing source zip file(char*),
 //				  tarBall  	  - name of zip file, excluding extension(char*)
 //				  siteCode    - destination directory(char*), 
 //				  isTestImage - test image flag, 0 for production, 1 for test(int)
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET_SYSAPI_moveDir (char* tmpLoc,
                                          char* tarBall,
                                          char* siteCode,
                                          int isTestImage)
{
    int ifail = 0;

    printf ("###########################################\n");
    printf ("# GET_SYSAPI_moveDir has been deprecated #\n");
    printf ("###########################################\n");

    #ifdef UNX
        ifail = GET_UNX_moveDir (tmpLoc, tarBall, siteCode, isTestImage);
    #elif linux
        ifail = GET_UNX_moveDir (tmpLoc, tarBall, siteCode, isTestImage);
    #elif WIN32
        ifail = GET_WIN32_moveDir (tmpLoc, tarBall, siteCode, isTestImage);
    #elif WIN64
        ifail = GET_WIN32_moveDir (tmpLoc, tarBall, siteCode, isTestImage);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_createPipe()
 //
 //    Purpose:   External accessor method to move create a pipe and execute a command
 //
 //    Inputs:     cmd  - command to be executed(char*),
 //               mode - mode of the command(char*)
 //
 //
 //    return:    pointer to pipe(FILE*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT FILE* GET_SYSAPI_createPipe (const char* cmd,
                                               const char* mode)
{
	FILE* fp = NULL;
	
    #ifdef UNX
        fp = GET_UNX_createPipe (cmd, mode);
    #elif linux
        fp = GET_UNX_createPipe (cmd, mode);
    #elif WIN32
        fp = GET_WIN32_createPipe (cmd, mode);
    #elif WIN64
        fp = GET_WIN32_createPipe (cmd, mode);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
    
    return fp;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_closePipe()
 //
 //    Purpose:   External accessor method to move create a pipe and execute a command
 //
 //    Inputs:     fp - pointer to pipe(FILE*)
 //
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_closePipe (FILE* fp)
{
	int ifail = 0;
	
    #ifdef UNX
        ifail = GET_UNX_closePipe (fp);
    #elif linux
        ifail = GET_UNX_closePipe (fp);
    #elif WIN32
        ifail = GET_WIN32_closePipe (fp);
    #elif WIN64
        ifail = GET_WIN32_closePipe (fp);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
    
    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_deleteFiles()
 //
 //    Purpose:   External accessor method to delete files
 //
 //    Inputs:     
 //
 //
 //    return:   delFiles - delete file command(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_deleteFiles (void)
{
    char* delFiles = NULL;
    
    printf ("###############################################\n");
	printf ("# GET_SYSAPI_deleteFiles has been deprecated #\n");
	printf ("###############################################\n");

    #ifdef UNX
        delFiles = GET_UNX_deleteFiles();
    #elif linux
        delFiles = GET_UNX_deleteFiles();
    #elif WIN32
        delFiles = GET_WIN32_deleteFiles();
    #elif WIN64
        delFiles = GET_WIN32_deleteFiles();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return delFiles;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_clearScreen()
 //
 //    Purpose:   External accessor method to clear the screen
 //
 //    Inputs:    none
 //
 //
 //    return:    none
 //    
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_SYSAPI_clearScreen (void)
{
	printf ("###############################################\n");
	printf ("# GET_SYSAPI_clearScreen has been deprecated #\n");
	printf ("###############################################\n");
	
    #ifdef UNX
       GET_UNX_clearScreen();
    #elif linux
       GET_UNX_clearScreen();
    #elif WIN32
       GET_WIN32_clearScreen();
    #elif WIN64
       GET_WIN32_clearScreen();
    #else
       fprintf (stderr, "Platform not supported\n");
    #endif
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getExportLogDirPath()
 //
 //    Purpose:   External accessor method to get the export log directory path
 //
 //    Inputs:    isTestImage - test image flag(int)
 //
 //
 //    return:    expPath     - export log directory path (Must be freed by caller)(char)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_getExportLogDirPath (int isTestImage)
{
    char* expPath = NULL;

    #ifdef UNX
        expPath = GET_UNX_getExportLogDirPath (isTestImage);
    #elif linux
        expPath = GET_UNX_getExportLogDirPath (isTestImage);
    #elif WIN32
        expPath = GET_WIN32_getExportLogDirPath (isTestImage);
    #elif WIN64
        expPath = GET_WIN32_getExportLogDirPath (isTestImage);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return expPath;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getHomeDir()
 //
 //    Purpose:   External accessor method to get the user's HOME directory
 //
 //    Inputs:    none 
 //
 //
 //    return:   homeDir - user's HOME directory (Must be freed by caller)(char)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT char* GET_SYSAPI_getHomeDir (void)
{
    char* homeDir = NULL;

    #ifdef UNX
        homeDir = GET_UNX_getHomeDir();
    #elif linux
        homeDir = GET_UNX_getHomeDir();
    #elif WIN32
        homeDir = GET_WIN32_getHomeDir();
    #elif WIN64
        homeDir = GET_WIN32_getHomeDir();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return homeDir;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getHostName()
 //
 //    Purpose:   External accessor method to get the name of the current host
 //
 //    Inputs:    hostName -  host name (Must be freed by caller)(char*)
 //
 //
 //    return:    ifail - 0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET_SYSAPI_getHostName (char** hostName)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_getHostName (hostName);
    #elif linux
        ifail = GET_UNX_getHostName (hostName);
    #elif WIN32
        ifail = GET_WIN32_getHostName (hostName);
    #elif WIN64
        ifail = GET_WIN32_getHostName (hostName);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getDomainName()
 //
 //    Purpose:   External accessor method to get the domain name of the current user
 //
 //    Inputs:    none 
 //
 //
 //    return:    domainName - domain name (Must be freed by caller)(char)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT char* GET_SYSAPI_getDomainName (void)
{
    char *domainName = NULL;

    #ifdef UNX
        domainName = GET_UNX_getDomainName();
    #elif linux
        domainName = GET_UNX_getDomainName();
    #elif WIN32
        domainName = GET_WIN32_getDomainName();
    #elif WIN64
        domainName = GET_WIN32_getDomainName();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return domainName;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_copyFile()
 //
 //    Purpose:   External accessor method to Copy the specified file from source to destination
 //
 //    Inputs:    sourceFile - source file(char*), 
 //               destFile   - destination file(char*)
 //
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_copyFile (char* sourceFile,
                                           char* destFile)
{
    int ifail = 0;

    #ifdef UNX
        ifail  = GET_UNX_copyFile (sourceFile, destFile);
    #elif linux
        ifail  = GET_UNX_copyFile (sourceFile, destFile);
    #elif WIN32
        ifail  = GET_WIN32_copyFile (sourceFile, destFile);
    #elif WIN64
        ifail  = GET_WIN32_copyFile (sourceFile, destFile);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_copyDir()
 //
 //    Purpose:   External accessor method to Copy the specified directory from source to destination
 //
 //    Inputs:    sourceDir - source directory(char*), 
 //               destDir   - destination directory(char*)
 //
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_copyDir (char* sourceDir,
                                          char* destDir)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_copyDir (sourceDir, destDir);
    #elif linux
        ifail = GET_UNX_copyDir (sourceDir, destDir);
    #elif WIN32
        ifail = GET_WIN32_copyDir (sourceDir, destDir);
    #elif WIN64
        ifail = GET_WIN32_copyDir (sourceDir, destDir);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_changeDirPermission()
 //
 //    Purpose:   External accessor method to Change permissions on a directory
 //
 //    Inputs:     dir  - name of directory(char*), 
 //				  mode - permissions for directory(int)
 //
 //
 //    return:    none
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT void GET_SYSAPI_changeDirPermission (char* dir,
                                                       int mode)
{
    #ifdef UNX
       GET_UNX_changeDirPermission (dir, mode);
    #elif linux
       GET_UNX_changeDirPermission (dir, mode);
    #elif WIN32
       GET_WIN32_changeDirPermission (dir, mode);
    #elif WIN64
       GET_WIN32_changeDirPermission (dir, mode);
    #else
       fprintf (stderr, "Platform not supported\n");
    #endif
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_openFile()
 //
 //    Purpose:   External accessor method to open a file
 //
 //    Inputs:    none 
 //
 //
 //    return:    cmd - command for opening of a file(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_openFile (void)
{
	char* cmd = NULL;
	
    #ifdef UNX
        cmd = GET_UNX_openFile();
    #elif linux
        cmd = GET_UNX_openFile();
    #elif WIN32
        cmd = GET_WIN32_openFile();
    #elif WIN64
        cmd = GET_WIN32_openFile();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
    
    return cmd;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_newConsole()
 //
 //    Purpose:   External accessor method to Open a new console window for internal ufunc programs
 //
 //    Inputs:    none 
 //
 //
 //    return:    none
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT void GET_SYSAPI_newConsole (void)
{
    #ifdef UNX
        GET_UNX_newConsole();
    #elif linux
        GET_UNX_newConsole();
    #elif WIN32
        GET_WIN32_newConsole();
    #elif WIN64
        GET_WIN32_newConsole();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_sleep()
 //
 //    Purpose:   External accessor method to Suspend execution for a specified amount of time
 //
 //    Inputs:     t - time to sleep, in seconds(int)
 //
 //
 //    return:    none
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT void GET_SYSAPI_sleep (int t)
{
    #ifdef UNX
        GET_UNX_sleep (t);
    #elif linux
        GET_UNX_sleep (t);
    #elif WIN32
        GET_WIN32_sleep (t);
    #elif WIN64
        GET_WIN32_sleep (t);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_sleepMilli()
 //
 //    Purpose:   External accessor method to t time to sleep, in milliseconds(int)
 //
 //    Inputs:    none 
 //
 //
 //    return:    none
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT void GET_SYSAPI_sleepMilli (int t)
{
    #ifdef UNX
        GET_UNX_sleepMilli (t);
    #elif linux
        GET_UNX_sleepMilli (t);
    #elif WIN32
        GET_WIN32_sleepMilli (t);
    #elif WIN64
        GET_WIN32_sleepMilli (t);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
}
 
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_moveFiles()
 //
 //    Purpose:   External accessor method to move files from source to destination
 //
 //    Inputs:    srcLoc - source file location(char*),
 //				  desLoc - destination directory(char*)
 //
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET_SYSAPI_moveFiles (char* srcLoc,
                                            char* desLoc)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_moveFiles (srcLoc, desLoc);
    #elif linux
        ifail = GET_UNX_moveFiles (srcLoc, desLoc);
    #elif WIN32
        ifail = GET_WIN32_moveFiles (srcLoc, desLoc);
    #elif WIN64
        ifail = GET_WIN32_moveFiles (srcLoc, desLoc);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_renameTifFiles()
 //
 //    Purpose:   External accessor method to Rename the TIF File names using Tabulated number and item ID in the specified directory
 //
 //    Inputs:    tmpDir - directory containing TIF files(char*)
 //               tabNum - tabulated shop mod number(char*),
 //               itemID - item ID itemID(char*)
 //
 //
 //    return:    
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT void GET_SYSAPI_renameTifFiles (char* tmpDir,
                                                  char* tabNum,
                                                  char* itemID)
{
    #ifdef UNX
        GET_UNX_renameTifFiles (tmpDir, tabNum, itemID);
    #elif linux
        GET_UNX_renameTifFiles (tmpDir, tabNum, itemID);
    #elif WIN32
        GET_WIN32_renameTifFiles (tmpDir, tabNum, itemID);
    #elif WIN64
        GET_WIN32_renameTifFiles (tmpDir, tabNum, itemID);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_basename()
 //
 //    Purpose:   External accessor method to Extract basename of file from fully qualified path
 //
 //    Inputs:    path - full path(char*)
 //              
 //   
 //    Outputs:   base - basename portion (Must be freed by caller)(char*)
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_basename (const char* path,
                                           char** base)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_basename (path, base);
    #elif linux
        ifail = GET_UNX_basename (path, base);
    #elif WIN32
        ifail = GET_WIN32_basename (path, base);
    #elif WIN64
        ifail = GET_WIN32_basename (path, base);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_runBackgroundSystemCommand()
 //
 //    Purpose:   External accessor method to Run a system command in background
 //
 //    Inputs:     cmd - command to run(char*)
 //   
 //    Outputs:    none
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_runBackgroundSystemCommand (char* cmd)
{
    int ifail = 0;
    
    #ifdef UNX
        ifail = GET_UNX_runBckgrdSysCmd (cmd);
    #elif linux
        ifail = GET_UNX_runBckgrdSysCmd (cmd);
    #elif WIN32
        ifail = GET_WIN32_runBckgrdSysCmd (cmd);
    #elif WIN64
        ifail = GET_WIN32_runBckgrdSysCmd (cmd);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_connectServer()
 //
 //    Purpose:   External accessor method to Function to create socket connection between server and client
 //
 //    Inputs:    host - hostname of server listening for connection(char*),
 //               port - port on which server listening for connection(int)
 //               
 //   
 //    Outputs:   fd   - file descriptor for socket connection(int)
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET_SYSAPI_connectServer (const char* host,
                                                const int port,
                                                int* fd)
{
    int ifail = 0;
    
    #ifdef UNX
        ifail = GET_UNX_connectServer (host, port, fd);
    #elif linux
        ifail = GET_UNX_connectServer (host, port, fd);
    #elif WIN32
        ifail = GET_WIN32_connectServer (host, port, fd);
    #elif WIN64
        ifail = GET_WIN32_connectServer (host, port, fd);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
    
	return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_sendRequest()
 //
 //    Purpose:   External accessor method to Function to send requset string to server
 //
 //    Inputs:     fd  - socket File Descriptor(char*),
 //               req - request string to Servern(char *)
 //               
 //   
 //    Outputs:    none
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_sendRequest (const int fd,
                                              const char* req)
{
    int ifail = 0;
    
    #ifdef UNX
        ifail = GET_UNX_sendRequest (fd, req);
    #elif linux
        ifail = GET_UNX_sendRequest (fd, req);
    #elif WIN32
        ifail = GET_WIN32_sendRequest (fd, req);
    #elif WIN64
        ifail = GET_WIN32_sendRequest (fd, req);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

	return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_receiveResponse()
 //
 //    Purpose:   External accessor method to receive request string from server
 //
 //    Inputs:     fd        - socket file descriptor(int),
 //               waitTime  - sleepTime sleep time between buffered reads(int)
 //               sleepTime - sleep time between buffered reads(int),
 //   
 //    Outputs:    resp - response string (Must be freed by caller)(char*)
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_receiveResponse (const int fd,
                                                  const int waitTime,
                                                  const int sleepTime,
                                                  char** resp)
{
	int ifail = 0;
	
    #ifdef UNX
        ifail = GET_UNX_receiveResponse (fd, waitTime, sleepTime, resp);
    #elif linux
        ifail = GET_UNX_receiveResponse (fd, waitTime, sleepTime, resp);
    #elif WIN32
        ifail = GET_WIN32_receiveResponse (fd, waitTime, sleepTime, resp);
    #elif WIN64
        ifail = GET_WIN32_receiveResponse (fd, waitTime, sleepTime, resp);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

	return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_closeConnection()
 //
 //    Purpose:   External accessor method to close connection with server
 //
 //    Inputs:     fd - socket file descriptor(int)
 //               
 //   
 //    Outputs:    none
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_closeConnection (const int fd)
{
    int ifail = 0;
    
    #ifdef UNX
        ifail = GET_UNX_closeConnection (fd);
    #elif linux
        ifail = GET_UNX_closeConnection (fd);
    #elif WIN32
        ifail = GET_WIN32_closeConnection (fd);
    #elif WIN64
        ifail = GET_WIN32_closeConnection (fd);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

	return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_intToString()
 //
 //    Purpose:   External accessor method to Convert integer to string
 //
 //    Inputs:      value  - number to be coverted to string(long)
 //               
 //   
 //    Outputs:     string - representation of number(char)
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_intToString (const long value,
                                              char* string)
{
    int ifail = 0;
    
    #ifdef UNX
        ifail = GET_UNX_intToString (value, string);
    #elif linux
        ifail = GET_UNX_intToString (value, string);
    #elif WIN32
        ifail = GET_WIN32_intToString (value, string);
    #elif WIN64
        ifail = GET_WIN32_intToString (value, string);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_renameFiles()
 //
 //    Purpose:   External accessor method to Rename any file name using tabulated number and item id in the specified directory
 //
 //    Inputs:    tmpDir   - directory name in which given type files present(char*),
 //				  tabNum   - tabulated shop mod number(char*)
 //               itemID   - Item ID(int),
 //				  fileType - type of file(char*)
 //   
 //    Outputs:   none 
 //
 //    return:    none
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT void GET_SYSAPI_renameFiles (char* tmpDir,
                                               char* tabNum,
                                               char* itemID,
                                               char* fileType)
{
    #ifdef UNX
        GET_UNX_renameFiles (tmpDir, tabNum, itemID, fileType);
    #elif linux
        GET_UNX_renameFiles (tmpDir, tabNum, itemID, fileType);
    #elif WIN32
        GET_WIN32_renameFiles (tmpDir, tabNum, itemID, fileType);
    #elif WIN64
        GET_WIN32_renameFiles (tmpDir, tabNum, itemID, fileType);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getUserLoginID()
 //
 //    Purpose:   External accessor method to Get the login ID of the user
 //
 //    Inputs:    value - number to be coverted to string(long)
 //               
 //   
 //    Outputs:   none  
 //
 //    return:    login - login ID of the user (Must be freed by caller)(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT char* GET_SYSAPI_getUserLoginID (void)
{
    char* login = NULL;

    #ifdef UNX
        login = GET_UNX_getUserLoginID();
    #elif linux
        login = GET_UNX_getUserLoginID();
    #elif WIN32
        login = GET_WIN32_getUserLoginID();
    #elif WIN64
        login = GET_WIN32_getUserLoginID();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return login;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getEnvVariableValue()
 //
 //    Purpose:   External accessor method to get the environment variable value from the command prompt
 //
 //    Inputs:    env - environment variable name(char*)
 //               
 //   
 //    Outputs:   none 
 //
 //    return:    val - value of environment variable(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_getEnvVariableValue (char* env)
{
    char* val = NULL;

    #ifdef UNX
        val = GET_UNX_getEnvVariableValue (env);
    #elif linux
        val = GET_UNX_getEnvVariableValue (env);
    #elif WIN32
        val = GET_WIN32_getEnvVariableValue (env);  
    #elif WIN64
        val = GET_WIN32_getEnvVariableValue (env);  
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return val;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_check_FileOrDirExists()
 //
 //    Purpose:   External accessor method to Check whether the file or directory exists in the file system
 //
 //    Inputs:     path - path of file or directory to check(char*)
 //               
 //   
 //    Outputs:    none 
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int GET_SYSAPI_check_FileOrDirExists (const char* path)
{
	int ifail = EXIT_FAILURE;
	
	#ifdef UNX
        ifail = GET_UNX_check_FileOrDirExists (path);
    #elif linux
        ifail = GET_UNX_check_FileOrDirExists (path);
    #elif WIN32
        ifail = GET_WIN32_check_FileOrDirExists (path);
    #elif WIN64
        ifail = GET_WIN32_check_FileOrDirExists (path);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
    
    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_changeDirectory()
 //
 //    Purpose:   External accessor method to Check the directory location from within the code
 //
 //    Inputs:    path - absolute directory path name(char*)
 //               
 //   
 //    Outputs:    none 
 //
 //    return:    0 for success, non-zero for error(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_changeDirectory (const char* path)
{
	int ifail = EXIT_FAILURE;
	
    #ifdef UNX
        ifail = GET_UNX_changeDirectory (path);
    #elif linux
        ifail = GET_UNX_changeDirectory (path);
    #elif WIN32
        ifail = GET_WIN32_changeDirectory (path);
    #elif WIN64
        ifail = GET_WIN32_changeDirectory (path);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif
    
    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_PrepStringForCmd()
 //
 //    Purpose:   External accessor method to windows/unix to overcome special characters in string.
 //
 //    Inputs:    stringVal - string Value(char*)
 //               
 //   
 //    Outputs:    none 
 //
 //    return:    0 - Success & Non-Zero - error, return string (Must be freed by caller)(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT char* GET_SYSAPI_PrepStringForCmd (const char* stringVal)
{

    #ifdef UNX
        return GET_UNX_PrepStringForCmd (stringVal);
    #elif linux
        return GET_UNX_PrepStringForCmd (stringVal);
    #elif WIN32
        return GET_WIN32_PrepStringForCmd (stringVal);
    #elif WIN64
        return GET_WIN32_PrepStringForCmd (stringVal);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return NULL;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_Scan_FilesInDirectory()
 //
 //    Purpose:   External accessor method to Scan a specified directory and returns all files
 //
 //    Inputs:   dirName       -  directory name(char*),
 //              MaxFile_Count -  maximum file count(int)
 //               
 //   
 //    Outputs:   files      - list of files (Must be freed by caller)(char*)
 //               file_count - number of files(int)
 //
 //    return:    list of all the files inside directory file count(int)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/

extern DLLEXPORT int GET_SYSAPI_Scan_FilesInDirectory (char* dirName, int MaxFile_Count, char*** files, int* file_count)
{
    int ifail = 0;

    #ifdef UNX
        ifail = GET_UNX_Scan_FilesInDirectory (dirName, MaxFile_Count, files, file_count);
    #elif linux
        ifail = GET_UNX_Scan_FilesInDirectory (dirName, MaxFile_Count, files, file_count);
    #elif WIN32
        ifail = GET_WIN32_Scan_FilesInDirectory (dirName, MaxFile_Count,files, file_count);
    #elif WIN64
        ifail = GET_WIN32_Scan_FilesInDirectory (dirName, MaxFile_Count,files, file_count);
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return ifail;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_SYSAPI_getCurrentTimeMilli()
 //
 //    Purpose:   External accessor method to get the current time in milliseconds since Epoch
 //
 //    Inputs:    none
 //               
 //   
 //    Outputs:   none
 //
 //    return:    Current time in milliseconds as a string(char*)
 //    
 // 	History:
 //      Who                   Date                 Description
 //  TCS Development Team     11 Feb, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT char* GET_SYSAPI_getCurrentTimeMilli (void)
{
    char *currentTimeMilli = NULL;

    #ifdef UNX
        currentTimeMilli = GET_UNX_getCurrentTimeMilli();
    #elif linux
        currentTimeMilli = GET_UNX_getCurrentTimeMilli();
    #elif WIN32
        currentTimeMilli = GET_WIN32_getCurrentTimeMilli();
    #elif WIN64
        currentTimeMilli = GET_WIN32_getCurrentTimeMilli();
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return currentTimeMilli;
}

extern DLLEXPORT bool GET_SYSAPI_regexMatch ( const char* sPattern, const char* sValue )
{
	bool bMatches = false;
    #ifdef UNX
	    bMatches = GET_UNX_regexMatch( sPattern, sValue );
    #elif linux
	    bMatches = GET_UNX_regexMatch( sPattern, sValue );
    #elif WIN32
	    bMatches = GET_WIN32_regexMatch( sPattern, sValue );
    #elif WIN64
	    bMatches = GET_WIN32_regexMatch( sPattern, sValue );
    #else
        fprintf (stderr, "Platform not supported\n");
    #endif

    return bMatches;
}



/****************************************************************************
 * Function     :  GET_SYSAPI_decode64
 *
 * Author       :  Kevin Fait
 *
 * Description  :  This function will decrypt a character string using
 *                 Base64 encryption algorithm.
 *
 * Parameters   :  [in]  in     - Character string to be decrypted.
 *                 [in]  inlen  - Length of the input character string.
 *                 [out] out    - The decrypted result of the string.
 *                 [out] outlen - The length of the decrypted result.
 *
 * Returns      :  [ 0] - SUCCESS
 *                 [-1] - FAILURE
 *
 * History     :
 * --------------------------------------------------------------------------
 *   Name                Date              Description
 * --------------------------------------------------------------------------
 * Kevin Fait       27 Mar 2002       Designed
 * TCS Team       20 Sept 2016       Re-used for GE Trasportation
 *
 ****************************************************************************/
extern DLLEXPORT int GET_SYSAPI_decode64(const char * inStr, unsigned inStrLen, char * outStr, unsigned * outStrLen)
{
    unsigned usLen = 0;
	unsigned usLup = 0;
	int iReturn = 0;
    int iCnt1 = 0;
	int iCnt2 = 0;
	int iCnt3 = 0;
	int iCnt4 = 0;

    if (inStr[0] == '+' && inStr[1] == ' ') inStr += 2;

    if (*inStr == '\0') return FAILURE;

    for (usLup = 0; usLup < inStrLen / 4; usLup++)
    {
        iCnt1 = inStr[0];
        if (CHAR64(iCnt1) == -1)
            return FAILURE;
        iCnt2 = inStr[1];
        if (CHAR64(iCnt2) == -1)
            return FAILURE;
        iCnt3 = inStr[2];
        if (iCnt3 != '=' && CHAR64(iCnt3) == -1)
            return FAILURE;
        iCnt4 = inStr[3];
        if (iCnt4 != '=' && CHAR64(iCnt4) == -1)
            return FAILURE;
        inStr += 4;
        *outStr++ = (CHAR64(iCnt1) << 2) | (CHAR64(iCnt2) >> 4);
        ++usLen;
        if (iCnt3 != '=')
        {
            *outStr++ = ((CHAR64(iCnt2) << 4) & 0xf0) | (CHAR64(iCnt3) >> 2);
            ++usLen;
            if (iCnt4 != '=')
            {
                *outStr++ = ((CHAR64(iCnt3) << 6) & 0xc0) | CHAR64(iCnt4);
                ++usLen;
            }
        }
    }

    *outStr = 0;
    *outStrLen = usLen;

    return iReturn;
}




