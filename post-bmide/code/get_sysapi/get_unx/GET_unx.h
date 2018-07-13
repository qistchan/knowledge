
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_unx.h
//
//    Purpose:   Function Prototypes that perform platform specific calls in Unix
//       Lang:   C
//
//    
// ENDFILEDOC   ***/

#ifndef GET_UNX_H
#define GET_UNX_H

#include <string>
#ifdef __cplusplus
extern "C" {
#endif

/* Unix dependant include headers */
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>


/* Function Prototypes */

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_getDate
//
//    Purpose:   Function to return current date as a string in specified format
//
//     Inputs:   dateFormat -  The specified date format
//
//     Output:   date       -  The current date
//
//    Returns:   Current date
//   ===========================================================================
//ENDFUNCDOC   ***/

extern void   GET_UNX_getDate (
    const char* dateFormat,       /* <I>  */
    char** date                   /* <OF> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_makeUniqueName
//
//    Purpose:   To create a unique file name
//
//     Inputs:   iPathLength - contains value of SS_MAXPATHLEN defined in
//               ss_const.h (iMAN header file)
//
//    Returns:   A string built from the process id and the user name
//  ===============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_makeUniqueName(
    int                           /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_deleteFilesInDirectory
//
//    Purpose:  deletes the files in the specified directory
//
//     Inputs:  *szDirName - The directory name in which the files to be deleted
//
//    Returns:
//   ==============================================================================
//ENDFUNCDOC   ***/

extern int   GET_UNX_deleteFilesInDirectory(
    char* szDirName               /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_createDirectory
//
//    Purpose:   To create a directory with given permissions
//
//     Inputs:   szDir    - The name of the directory to be created
//               iMode    - The permissions for the Directory
//
//    Returns:
//   ===========================================================================
//ENDFUNCDOC   ***/

extern int   GET_UNX_createDirectory(
    const char* szDir,             /* <I>  */
    int iMode                      /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_removeDirectory
//
//    Purpose:   To remove the specified directory
//
//     Inputs:   szDir   - The name of the directory to be removed
//
//    Returns:   none
//  ===============================================================================
//ENDFUNCDOC   ***/

extern void  GET_UNX_removeDirectory (
    const char* szDir             /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_renameDirectory
//
//    Purpose:   To rename the specified directory
//
//     Inputs:   szDir      - The name of the directory to be renamed
//               pszNewName - The new name for the existing directory
//
//    Returns:   none
//  ===============================================================================
//ENDFUNCDOC   ***/

extern void  GET_UNX_renameDirectory (
    const char* szDir,            /* <I>  */
    const char* pszNewName        /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_getProcessId
//
//    Purpose:   To return the process ID
//
//     Inputs:   none
//
//    Returns:   Process ID
//  ===============================================================================
//ENDFUNCDOC   ***/

extern int   GET_UNX_getProcessId ( void );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_unLink
//
//    Purpose:   To delete the specified file
//
//     Inputs:   tempFile - The file name to be deleted
//
//    Returns:
// ================================================================================
//ENDFUNCDOC   ***/

extern int   GET_UNX_unLink (
    char* tempFile                /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getLogin
//
//   Purpose :  To get the users login name
//
//   Inputs  :  none
//
//   Returns :  The user login name on this machine
//  ===============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getLogin (void);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getTempFileName;
//
//   Purpose :  To get the temporary file name using site code and process id
//
//   Inputs  :  siteCode    - Sitecode
//              pid         - process id
//              isTestImage - Test image flag
//
//   Returns :  The temporary file name
//  ===============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getTempFileName(
	char* siteCode,                 /* <I>  */
    int   pid,                      /* <I>  */
    int   isTestImage               /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getFileSeparator;
//
//   Purpose :  To get the file separator
//
//   Inputs  :  none
//
//   Returns :  The file separator
//   ===========================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getFileSeparator ( void );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getPATHSeparator;
//
//   Purpose :  To get the PATH separator
//
//   Inputs  :  none
//
//   Returns :  The PATH separator
//   ===========================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getPATHSeparator ( void );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getTempDir
//
//   Purpose :  To get the temporary directory name
//
//   Inputs  :  none
//
//   Returns :  the temporary directory name
//  ===============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getTempDir( void );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_zipDir
//
//   Purpose :   To Compress the files
//
//   Inputs  :   tmp_loc   - The location of files to be compressed
//	             tar_ball  - Compressed file Name (ItemID_date_time)
//
//    Returns:
//  ===============================================================================
//ENDFUNCDOC   ***/

extern int   GET_UNX_zipDir(
    char* tmp_loc,                /* <I>  */
    char* tar_ball                /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_moveDir
//
//   Purpose :  To move the compressed files to the destination directory
//
//   Inputs  :  tmp_loc     - The directory in which source zip file presents
//              tar_ball    - Zip file name(ItemID_date_time)
//              siteCode    - The destination directory(Named as SITECODE)
//              isTestImage - Test image flag
//
//    Returns:
//  ===============================================================================
//ENDFUNCDOC   ***/

extern int   GET_UNX_moveDir(
    char* tmp_loc,                /* <I>  */
    char* tar_ball,               /* <I>  */
    char* siteCode,               /* <I>  */
    int   isTestImage             /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_createPipe
//
//    Purpose:   To create the pipe and execute the command
//
//     Inputs:   *szCommand   -  Command to be executed
//               *mode        -  Mode of the command
//
//    Returns:
//  ===============================================================================
//ENDFUNCDOC   ***/

extern FILE* GET_UNX_createPipe(
    const char* szCommand,        /* <I>  */
    const char* mode              /* <I>  */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_closePipe
//
//   Purpose :   To close the stream on associated pipe
//
//   Inputs  :   fp - File pointer
//
//	 Returns :
//   ===========================================================================
//ENDFUNCDOC   ***/

extern int GET_UNX_closePipe(
    FILE* fp                     /* <I> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_deleteFiles
//
//    Purpose:  To delete the files
//
//     Inputs:  none
//
//    Returns:  Delete file command
//  ===============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_deleteFiles( void );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_clearScreen
//
//    Purpose:  To clear the Screen
//
//     Inputs:  none
//
//    Returns:
//  ===============================================================================
//ENDFUNCDOC   ***/

extern void GET_UNX_clearScreen( void );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getExportLogDirPath
//
//   Purpose :  To get the GET_EXPORT_LOG_DIR path
//
//   Inputs  :  isTestImage - Test image flag
//
//	 Returns :  The export log directory path
//   ===========================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getExportLogDirPath (
    int isTestImage                 /* <I> */
);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getHomeDir;
//
//   Purpose :  To get the Home Directory
//
//   Inputs  :  none
//
//	 Returns :  The  HOME directory
//   ===========================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getHomeDir( void );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getHostName
//
//   Purpose :  Get the name of the current host
//
//   Inputs  :  none
//
//   Outputs :  szHostName - host name
//
//	 Returns :  success status
//   ===========================================================================
//ENDFUNCDOC   ***/

extern int GET_UNX_getHostName (
    char** szHostName /* <OF> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getDomainName
//
//   Purpose :  Get the domain of the current user
//
//   Inputs  :  none
//
//   Outputs :  none
//
//   Returns :  domain name
//   ===========================================================================
//ENDFUNCDOC   ***/
extern char* GET_UNX_getDomainName(void);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_copyFile
//
//   Purpose :  To copy the specified file from source to destination
//
//   Inputs  :  szFile1 - source file
//              szFile2 - Destination file
//
//	 Returns :
//   ===========================================================================
//ENDFUNCDOC   ***/

extern int GET_UNX_copyFile(
    char* szFile1,                /* <I> */
    char* szFile2                 /* <I> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_copyDir
//
//   Purpose :  To copy the specified Directory from source to destination
//
//   Inputs  :  szDir1 - Source Directory
//              szDir2 - Destination Directory
//
//	 Returns :
//   ===========================================================================
//ENDFUNCDOC   ***/

extern int GET_UNX_copyDir(
    char* szDir1,                /* <I> */
    char* szDir2                 /* <I> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_changeDirPermission
//
//   Purpose :   To change the specified directory permissions
//
//   Inputs  :   szDirName  - The Directory name
//               iMode      - The permissions reqd for directory
//
//	 Returns :   none
//   ===========================================================================
//ENDFUNCDOC   ***/

extern void GET_UNX_changeDirPermission(
    char* szDirName,            /* <I> */
    int iMode                   /* <I> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_openFile
//
//   Purpose :   Command for open a file
//
//   Inputs  :   none
//
//	 Returns :   Command for opening of a file
//   ===========================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_openFile(void);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_newConsole
//
//   Inputs  :   none
//
//	 Returns :   none
//   ============================================================================
//ENDFUNCDOC   ***/

extern void GET_UNX_newConsole(void);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_sleep
//
//   Purpose :  Specifies the time, in seconds,for which to suspend execution
//
//   Inputs  :  iTime - Specifies the time, in seconds,
//
//	 Returns:   none
//   ============================================================================
//ENDFUNCDOC   ***/

extern void GET_UNX_sleep(
    int iTime                   /* <I> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_sleepMilli
//
//   Purpose :  Specifies the time, in milliseconds,for which to suspend execution
//
//   Inputs  :  iTime - Specifies the time, in milliseconds,
//
//   Returns:   none
//   ============================================================================
//ENDFUNCDOC   ***/

extern void GET_UNX_sleepMilli(
    int iTime                   /* <I> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_getLoadDefnFilePath
//
//   Purpose :   To get the Load definition File Path
//
//   Inputs  :   None
//
//	 Returns :
//   ============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getLoadDefnFilePath(void);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:   GET_UNX_moveFiles
//
//   Purpose :   To Move files from source to destination
//
//   Inputs  :   szSrcLoc   - Source file location
//               szDesLoc   - Destination Directory
//
//	 Returns :
//   ===========================================================================
//ENDFUNCDOC   ***/

extern int GET_UNX_moveFiles(
    char* szSrcLoc,          /* <I> */
    char* szDesLoc           /* <I> */
    );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_renameTifFiles
//
//   Purpose :  To rename the TIF File names using Tabulated number and item id
//              in the specified directory
//
//   Inputs  :  szTmpDir   - The Directory name in which tif files present
//              szTabNum   - Tabulated shop mod Number
//              szItemId   - Itemid
//
//	 Returns :  none
//   ===========================================================================
//ENDFUNCDOC   ***/

extern void GET_UNX_renameTifFiles(
    char* szTmpDir,          /* <I> */
    char* szTabNum,          /* <I> */
    char* szItemId           /* <I> */
    );
    /*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_renameFiles
//
//   Purpose :  To rename File names using Tabulated number and item id
//              in the specified directory
//
//   Inputs  :  szTmpDir   - The Directory name in which tif files present
//              szTabNum   - Tabulated shop mod Number
//              szItemId   - Itemid
//				szFileType - Type of file (Ex: tif,pdf,...)
//	 Returns :  none
//   ===========================================================================
//ENDFUNCDOC   ***/
extern void GET_UNX_renameFiles(
	char* szTmpDir,            /* <I> */
	char* szTabNum,            /* <I> */
	char* szItemId,            /* <I> */
	char* szFileType           /* <I> */
	);
/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_basename
//
//   Purpose :
//
//   Inputs  :
//
//	 Returns :  none
//   ===========================================================================
//ENDFUNCDOC   ***/

extern int GET_UNX_basename (
    const char* pathname,          /* <I> */
    char**      basename           /* <OF> */
    );

/*STARTFUNCDOC ***
//   =================================================================================
//   Function:  GET_UNX_runBckgrdSysCmd
//
//   Purpose :  To execute the command line process in Backgorund
//
//   Inputs  :  ocnst char* (Command to be exectued)
//
//	 Returns :  none
//   History :
//    Description                           | Who           |     Date
//  ========================================|===============|==========================
//                                              Jothiraj P      08-Jun-2012
//  ===================================================================================
//ENDFUNCDOC   ***/
extern int GET_UNX_runBckgrdSysCmd (
    const char* command          /* <I> */
    );

/**
 * Function to create socket connection between server and client
 *
 * @param	Host where LR daemon is running
 * @param 	Port on which LR daemon is registered
 * @param	pointer to Socket File Descriptor
 *
 * @return status 0 for success and 1 for failure
 */
extern int  GET_UNX_connectServer  (
		const char* szServer, /* <I> */
		const int iPort,     /*  <I> */
		int* iSockFd  /* <O> */
		);

/**
 * Function to send request string to server
 *
 * @param	iSocketFd - Socket File Descriptor
 * @param 	szXMLStr -	Request string to Server
 *
 * @return status 0 for success and 1 for failure
 */
extern int GET_UNX_sendRequest (
			const int iSockFd , /* <I> */
			const char *szBuf  /* <I> */
			);

/**
 * Function to receive request string from server
 *
 * @param	iSocketFd - Socket File Descriptor
 * @param 	iWaitTime  - Time to wait to get response from server
 * @param	iSleepTime - Time in milli seconds to sleep before reading server response
 *
 * @return status 0 for success and 1 for failure
 */
extern int GET_UNX_receiveResponse (
			const int iSockFd, /* <I> */
			const int iWaitTime, /* <I> */
			const int iSleepTime, /* <I> */
			char** szResponse /* <O> */
			);


/**
 * Function to close connection with server
 *
 * @param	iSocketFd - Socket File Descriptor
 *
 * @return status 0 for success and 1 for failure
 */
extern int GET_UNX_closeConnection (
				const int iSockFd /* <I> */
				);

/**
 * Unix wrapper for ltoa, as _ltoa is not
 * currently available for HP-UX
 *
 * @param value number to be coverted to string
 * @param string string representation of number
 * @return status 0 for success, non-zero for failure
 */
extern int GET_UNX_intToString (
                const long value,
                char* string
);

/**
 * Compare strings
 *
 * @param s1 first string to compare
 * @param s2 second string to compare
 * @param flag 0 = case sensitive, 1 = ignore case
 * @return result of comparison
 */
extern int GET_UNX_strcmp (
                const char* s1,
                const char* s2,
                const int flag
);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getUserLoginID
//
//   Purpose :  To get the users Machine login ID
//
//   Inputs  :  none
//
//   Returns :  User machine login ID string
//  ===============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getUserLoginID (void);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_getEnvVariableValue
//
//   Purpose : To get the environment variable value from the command prompt
//
//   Inputs  : Environment variable name
//
//   Returns :  Environment variable value
//  ===============================================================================
//ENDFUNCDOC   ***/

extern char* GET_UNX_getEnvVariableValue (char* szEnvVarName);

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_check_FileOrDirExists
//
//   Purpose :  To check of the given file or directory exists in the file
//              system
//
//   Inputs  :  path   - The File/Directory path name to check
//
//    Returns : 0 - Exists & Non-Zero - Does Not Exist
//   History :
//    Description                   | Who           |     Date
//  ================================|===============|===========================
//    Genesis                       | Viswanathan R | Tue Aug 25 2009
//   ===========================================================================
//ENDFUNCDOC   ***/
extern int GET_UNX_check_FileOrDirExists ( const char* path );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_changeDirectory
//
//   Purpose :  To check the directory location from within the code
//
//   Inputs  :  path   - The Absolute Directory path name
//	 Returns :  (0 - Success & Non-Zero - Failure)
//   History :
//    Description                   | Who           |     Date
//  ================================|===============|===========================
//    Genesis                       | Viswanathan R | Tue Sep 01 2009
//   ===========================================================================
//ENDFUNCDOC   ***/
extern int GET_UNX_changeDirectory ( const char *path );

/*STARTFUNCDOC ***
//   =============================================================================
//   Function:  GET_UNX_PrepStringForCmd
//
//   Purpose :  To prepare string for unix shell to avoid conversion due to special
//				characters in string.
//   Inputs  :  stringVal   - string
//	 Returns :  return string with single quote
//              (Unix shell treat string with single quote literally.)
//   History :
//    Description                   | Who          			 |     Date
//  ================================|========================|====================
//    Genesis                       |sridharan Chinnaswamy   | Thu Mar 17 2011
//   =============================================================================
//ENDFUNCDOC   ***/
extern char* GET_UNX_PrepStringForCmd ( const char* stringVal );

/*STARTFUNCDOC ***
//   ===========================================================================
//   Function:  GET_UNX_Scan_FilesInDirectory
//
//    Purpose:  To scan a directory and list all the files
//
//     Inputs:  dirName    - The name of the directory to be scanned
//              MaxFile_Count - Max number of files in directory
//
//    Returns:  files      - List of files inside the directory
//   ==============================================================================
//ENDFUNCDOC   ***/

extern int   GET_UNX_Scan_FilesInDirectory(
    char* dirName,              /* <I>  */
    int MaxFile_Count,          /* <I> */
    char*** files,               /* <O>  */
    int* file_count             /* <O>  */
);

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_UNX_getCurrentTimeMilli
 //
 //   Purpose :   To get the current time in milliseconds since Epoch. Replicates
 //               System.currentTimeMillis() from Java.
 //
 //   Inputs  :   None
 //
 //   Returns :   Current time in milliseconds as a string.
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_getCurrentTimeMilli(void);

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_UNX_regexMatch
 //
 //   Purpose :   To compare if the value matches regex pattern
 //
 //   Inputs  :   None
 //
 //   Returns :   true/false
 //  ===============================================================================
 //ENDFUNCDOC   ***/
extern bool GET_UNX_regexMatch( const char* sPattern, const char* sValue );

#ifdef __cplusplus
}
#endif

#endif /* GET_UNX_H To Move files from source to destination*/
