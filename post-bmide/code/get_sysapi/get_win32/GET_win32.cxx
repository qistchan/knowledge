#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

/* System Includes */
#include <stdlib.h>
#include <stdio.h>
#include <io.h> /* for _mktemp*/
#include <time.h>
#include <sys/stat.h>
#include <string.h> /* string compare */
#include <winsock2.h>  /* for gethostname() */
#include <winbase.h>  /* for Sleep() */
#include <assert.h>

/* Windows dependent include headers */
#include <msdir.h>
#include <direct.h> /*for change directory*/
#include <stdarg.h>
#include <process.h> /* for getting process id */
#include <windows.h> /* Allocate a new console for internal ufunc progrms */
#include <winsock.h> /* For socket functions */

/* GET Includes */
#include <GET_win32.h>
#include <GET_syspath.h>
#include <GET_sysconst.h>
#include <GET_cpp_stl.h>

//C++ includes
#include <regex>

using namespace std;

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_getDate
 //
 //   Purpose :   Function to return current date as a string in specified format
 //
 //   Inputs  :   dateFormat -  The specified date format
 //
 //   Outputs :   date       -  The current date
 //
 //   Returns :   Current date
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_getDate(const char* dateFormat, char** date)
{
    struct tm* timer;
    time_t ltime;

    (*date) = NULL;

    ltime = time(&ltime);
    timer = localtime(&ltime);
    (*date) = (char*) malloc(sizeof(char) * 128);
    strftime((*date), sizeof(char) * 128, dateFormat, timer);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_makeUniqueName
 //
 //   Purpose :   To create a unique file name
 //
 //   Inputs  :   iPathLength - contains value of SS_MAXPATHLEN defined in
 //               ss_const.h (iMAN header file)
 //
 //   Returns :   A string built from the process id and the user name
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_makeUniqueName(int iPathLength)
{
    char* szUserName = NULL;
    char* pszTempName = NULL;

    szUserName = getenv("USERNAME");

    if (szUserName != NULL)
    {
        char szSeed[BUFSIZ] = "";

        pszTempName = (char*) malloc((iPathLength + 1) * sizeof(char));

        sprintf(szSeed, "%s_XXXXXX", szUserName);
        _mktemp(szSeed);
        strncpy(pszTempName, szSeed, iPathLength);
    }

    return pszTempName;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_deleteFilesInDirectory
 //
 //   Purpose :  Deletes the files in the specified directory
 //
 //   Inputs  :  szDirName - The directory name in which the files to be deleted
 //
 //   Returns :
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_deleteFilesInDirectory(char* szDirName)
{
    int iFail = 0;

    DIR *pDir = NULL;

    struct dirent *psDir = NULL;
    struct _stat sStat;
    char *temp_ptr = NULL;
    char initial_string[256] = "";

    printf("Trying to open %s\n", szDirName);

    // try to open the passed in directory
    pDir = opendir(szDirName);
    if (!pDir)
    {
        perror("Could not open directory");
        iFail = -1;
    }

    // change to it since psDir->d_name doesn't give full path names
    if (_chdir(szDirName))
    {
        perror("Could not go to the directory");
        iFail = -1;
    }
    printf("Changed directory to %s\n", szDirName);

    // walk the tree, determining what you find
    // take special care with the "." and ".." entries
    // if you don't you will delete the WHOLE directory from root!!!
    while ((psDir = readdir(pDir)) != NULL)
    {
        if (strcmp("..", psDir->d_name) && strcmp(".", psDir->d_name))
        {
            // stat the file
            if (_stat(psDir->d_name, &sStat))
            {
                perror("Could not stat");
                iFail = -1;
                break;
            }

            if (S_ISDIR(sStat.st_mode))
            {
                // this is a directory so recurse
                GET_WIN32_deleteFilesInDirectory(psDir->d_name);
            }
            else
            {
                if (S_ISFIFO(sStat.st_mode))
                {
                    // don't mess with pipes
                    printf("cannot remove a PIPE\n");
                }
                else
                {
                    temp_ptr = NULL;
                    temp_ptr = strrchr(psDir->d_name, '.');
                    strcpy(initial_string, "");
                    if (temp_ptr != NULL)
                    {
                        strcpy(initial_string, temp_ptr + 1);
                    }
                    if (!strcmp(initial_string, "lnk"))
                    {
                        printf("Cannot remove a symbolic link \n");
                    }
                    else
                    {
                        // this is file, so remove it
                        printf("removing %s\n", psDir->d_name);
                        if (remove(psDir->d_name))
                        {
                            perror("Could not remove");
                            iFail = -1;
                        }
                    }
                }
            }
        }
    }

    // now close the directory, back up one and try to remove it
    printf("Closing directory %s\n", szDirName);
    closedir(pDir);
    if (_chdir(".."))
    {
        perror("Could not back up one level");
        iFail = -1;
    }

    printf("removing directory %s\n", szDirName);

    if (_rmdir(szDirName))
    {
        perror("Could not remove the directory");
        iFail = -1;
    }

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_createDirectory
 //
 //   Purpose :   To create a directory with given permissions
 //
 //   Inputs  :   szDir    - The name of the directory to be created
 //               iMode    - The permissions for the Directory
 //
 //   Returns :
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_createDirectory(const char* szDir, int iMode)
{
    int iCreateDir = 0;

    _mkdir(szDir);

    /* this is throwing an Insure error about invalid pmode.  Need a fix to secure contents on multi-user
     FN machines where access licenses to data may vary.  Logged problem in SupportCentral 11/12/04 and switched to symbolics
     that duplicate the current state properly, without the error. */
    /*iCreateDir =  _chmod( szDir, iMode );*/
    iCreateDir = _chmod(szDir, _S_IREAD | _S_IWRITE);

    return iCreateDir;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_removeDirectory
 //
 //   Purpose :   To remove the specified directory
 //
 //   Inputs  :   szDir   - The name of the directory to be removed
 //
 //   Returns :   none
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_removeDirectory(const char* szDir)
{
    char szCmd[BUFSIZ] = "";

    sprintf(szCmd, "%s %s 2>nul", REMOVE_DIR, szDir);
    system(szCmd);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_renameDirectory
 //
 //   Purpose :   To rename the specified directory
 //
 //   Inputs  :   szDir      - The name of the directory to be renamed
 //               pszNewName - The new name for the existing directory
 //
 //   Returns :   none
 //  ==============================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_renameDirectory(const char* szDir, const char* pszNewName)
{
    char szCmd[BUFSIZ] = "";

    sprintf(szCmd, "%s %s %s > nul 2>&1 ", MOVE_COMMAND, szDir, pszNewName);
    system(szCmd);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_getProcessId
 //
 //   Purpose :   To get the process ID
 //
 //   Inputs  :   none
 //
 //   Returns :   Process ID
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_getProcessId(void)
{
    return _getpid();
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_unLink
 //
 //   Purpose :   To delete the specified file
 //
 //   Inputs  :   tempFile - The file name to be deleted
 //
 //   Returns :
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_unLink(char* tempFile)
{
    return _unlink(tempFile);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function: GET_WIN32_getLogin
 //
 //   Purpose : To get the users login name
 //
 //   Inputs  : none
 //
 //   Returns : The user login name on this machine
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getLogin(void)
{
    char* szUserName = NULL;
    char* buff = NULL;

    buff = getenv("USERNAME");

    if (buff != NULL)
    {
        szUserName = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(szUserName, buff);
    }

    return szUserName;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function : GET_WIN32_getTempFileName;
 //
 //   Purpose  : To get the temp file name using site code and process id
 //
 //   Inputs   : siteCode    - site code
 //              pid         - process id
 //              isTestImage - test image flag
 //
 //   Returns  : The temporary file name
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getTempFileName(char* siteCode, int pid, int isTestImage)
{
    char* tmpfile = NULL;
    char* szSiteCode = NULL;

    szSiteCode = getenv("SITECODE");

    if (szSiteCode != NULL)
    {
        char buff[BUFSIZ] = "";
        int IS_MILITARY = 0;

        if (!strcmp(szSiteCode, "evml1"))
        {
            IS_MILITARY = 1;
        }

        if (isTestImage)
        {
            sprintf(buff, "%s%s%s%stmp_%d", TRANSFER_OWNER_LOG_DIR_TEST, FILE_SEP_WIN32, siteCode, FILE_SEP_WIN32, pid);
        }
        else
        {
            if (IS_MILITARY)
            {
                sprintf(
                        buff,
                        "%s%s%s%stmp_%d",
                        TRANSFER_OWNER_LOG_DIR_PROD_MILITARY,
                        FILE_SEP_WIN32,
                        siteCode,
                        FILE_SEP_WIN32,
                        pid);
            }
            else
            {
                sprintf(
                        buff,
                        "%s%s%s%stmp_%d",
                        TRANSFER_OWNER_LOG_DIR_PROD,
                        FILE_SEP_WIN32,
                        siteCode,
                        FILE_SEP_WIN32,
                        pid);
            }
        }

        tmpfile = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(tmpfile, buff);
    }

    return tmpfile;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function: GET_WIN32_getTempDir;
 //
 //   Purpose : To get the temporary directory name
 //
 //   Inputs  : none
 //
 //   Returns : The temporary directory name
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getTempDir(void)
{
    return GET_TEMP_DIR;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function: GET_WIN32_getFileSeparator;
 //
 //   Purpose : To get the file separator
 //
 //   Inputs  : none
 //
 //   Returns : The file separator
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getFileSeparator(void)
{
    return FILE_SEP_WIN32;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function: GET_WIN32_getPATHSeparator;
 //
 //   Purpose : To get the PATH separator
 //
 //   Inputs  : none
 //
 //   Returns : The path separator
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getPATHSeparator(void)
{
    return PATH_SEP_WIN32;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_zipDir
 //
 //   Purpose :   To Compress the files
 //
 //   Inputs  :   tmp_loc   - The location of files to be compressed
 //	             tar_ball  - Compressed file Name (ItemID_date_time)
 //
 //   Returns :
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_zipDir(char* tmp_loc, char* tar_ball)
{
    int iFail = 0;

    /* Change the directory to temp file location */
    iFail = _chdir(tmp_loc);

    if (iFail == 0)
    {
        char zip_command[BUFSIZ] = "";

        /* Compress the files */
        sprintf(zip_command, "%s %s.zip *", ZIP_COMMAND, tar_ball);
        iFail = system(zip_command);
    }

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_moveDir
 //
 //   Purpose :  To move the compressed files to the destination directory
 //
 //   Inputs  :  tmp_loc     - The directory in which source zip file presents
 //              tar_ball    - Zip file name(ItemID_date_time)
 //              siteCode    - The destination directory(Named as SITECODE)
 //              isTestImage - Test image flag
 //
 //   Returns :
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_moveDir(char* tmp_loc, char* tar_ball, char* siteCode, int isTestImage)
{
    int iFail = 0;
    char *szSiteCode = NULL;
    int IS_MILITARY = 0;

    szSiteCode = getenv("SITECODE");
    if (szSiteCode != NULL && !strcmp(szSiteCode, "evml1"))
    {
        IS_MILITARY = 1;
    }

    /* Change the directory to temp file location */
    iFail = _chdir(tmp_loc);

    if (iFail == 0)
    {
        char mv_command[BUFSIZ] = "";
        char zipFilePath[BUFSIZ] = "";

        sprintf(zipFilePath, "%s%s%s.zip", tmp_loc, FILE_SEP_WIN32, tar_ball);

        /* Move the zip file to TRANSFER_OWNER_LOG_DIR */
        if (isTestImage)
        {
            sprintf(
                    mv_command,
                    "%s %s \"%s%s%s\"",
                    MOVE_COMMAND,
                    zipFilePath,
                    TRANSFER_OWNER_LOG_DIR_TEST,
                    FILE_SEP_WIN32,
                    siteCode);
        }
        else
        {
            if (IS_MILITARY)
            {
                sprintf(
                        mv_command,
                        "%s %s \"%s%s%s\"",
                        MOVE_COMMAND,
                        zipFilePath,
                        TRANSFER_OWNER_LOG_DIR_PROD_MILITARY,
                        FILE_SEP_WIN32,
                        siteCode);
            }
            else
            {
                sprintf(
                        mv_command,
                        "%s %s \"%s%s%s\"",
                        MOVE_COMMAND,
                        zipFilePath,
                        TRANSFER_OWNER_LOG_DIR_PROD,
                        FILE_SEP_WIN32,
                        siteCode);
            }
        }

        iFail = system(mv_command);
    }

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_createPipe
 //
 //   Purpose :   To create the pipe and execute the command
 //
 //   Inputs  :   szCommand   -  Command to be executed
 //               mode        -  Mode of the command
 //
 //   Returns :
 // =================================================================================
 //ENDFUNCDOC   ***/

extern FILE* GET_WIN32_createPipe(const char* szCommand, const char* mode)
{
    return (FILE*) _popen(szCommand, mode);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_closePipe
 //
 //   Purpose :   To close the stream on associated pipe
 //
 //   Inputs  :   fp - File pointer
 //
 //	 Returns :
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_closePipe(FILE* fp)
{
    return _pclose(fp);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_deleteFiles
 //
 //   Purpose :   To delete the files
 //
 //   Inputs  :   none
 //
 //   Returns :   Delete file command
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_deleteFiles(void)
{
    return FILE_DEL_COMMAND;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_clearScreen
 //
 //    Purpose:  To clear the Screen
 //
 //     Inputs:  none
 //
 //    Returns:  none
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_clearScreen(void)
{
    system("cls");
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_getExportLogDirPath
 //
 //   Purpose :  To get the GET_EXPORT_LOG_DIR path
 //
 //   Inputs  :  isTestImage - Test image flag
 //
 //	 Returns :  The export log directory path
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getExportLogDirPath(int isTestImage)
{
    char* pszExportDir = NULL;
    char buff[BUFSIZ] = "";

    if (isTestImage)
    {
        sprintf(buff, "%s", GET_EXPORT_LOG_DIR_TEST);
    }
    else
    {
        sprintf(buff, "%s", GET_EXPORT_LOG_DIR_PROD);
    }

    pszExportDir = (char*) malloc(strlen(buff) + 1 * sizeof(char));

    strcpy(pszExportDir, buff);

    return pszExportDir;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_getHomeDir;
 //
 //   Purpose :  To get the Home Directory
 //
 //   Inputs  :  none
 //
 //	 Returns :  The HOME directory
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getHomeDir(void)
{
    char* pszHomeDir = NULL;
    char* userProfile = NULL;

    userProfile = getenv("USERPROFILE");

    if (userProfile != NULL)
    {
        pszHomeDir = (char*) malloc(strlen(userProfile) + 1 * sizeof(char));
        strcpy(pszHomeDir, userProfile);
    }

    return pszHomeDir;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_getHostName
 //
 //   Purpose :  Get the name of the current host
 //
 //   Inputs  :  none
 //
 //   Outputs :  szHostName - host name <OF>
 //
 //	 Returns :  success status
 //  ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_getHostName(char** szHostName)
{
    int rc = 0;
    char buff[BUFSIZ];
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 2);

    /* Initialize Windows Sockets API */
    if (WSAStartup(wVersionRequested, &wsaData))
    {
        printf("WSAStartup failed\n");
    }

    /* Get the hostname */
    if (gethostname(buff, BUFSIZ))
    {
        rc = WSAGetLastError();
    }

    /* Terminate Windows Sockets API */
    WSACleanup();

    /* Assign memory, and copy hostname to it */
    if (rc == 0)
    {
        *szHostName = (char*) malloc(sizeof(char) * strlen(buff) + 1);
        if (*szHostName != NULL)
        {
            strcpy(*szHostName, buff);
        }
    }

    return rc;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_getDomainName
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

extern char* GET_WIN32_getDomainName(void)
{
    char* domainName = NULL;
    char* buff = NULL;

    buff = getenv("USERDOMAIN");
    if (buff != NULL)
    {
        domainName = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(domainName, buff);
    }

    return domainName;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_copyFile
 //
 //   Purpose :  To copy the specified file from source to destination
 //
 //   Inputs  :  szFile1 - Source file
 //              szFile2 - Destination file
 //
 //	 Returns :
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_copyFile(char* szFile1, char* szFile2)
{
    int iFail = 0;
    char szCopyFile[256] = "";

    sprintf(szCopyFile, "COPY /Y %s %s", szFile1, szFile2);

    iFail = system(szCopyFile);

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_copyDir
 //
 //   Purpose :  To copy the specified Directory from source to destination
 //
 //   Inputs  :  szDir1 - Source Directory
 //              szDir2 - Destination Directory
 //
 //	 Returns :
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_copyDir(char* szDir1, char* szDir2)
{
    int iFail = 0;
    char szCopyDir[256] = "";

    sprintf(szCopyDir, "cp -R %s %s", szDir1, szDir2);

    /* this only works because/when we are sure there is more than one file being copied */
    /*not working on XP at CIAT, and maybe other places...  sprintf(szCopyDir,"XCOPY /E /Q /Y /I %s %s",szDir1,szDir2);*/
    iFail = system(szCopyDir);

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_changeDirPermission
 //
 //   Purpose :   To change the specified directory permissions
 //
 //   Inputs  :   szDirName  - The Directory name
 //               iMode      - The permissions reqd for directory
 //
 //	 Returns :   none
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_changeDirPermission(char* szDirName, int iMode)
{
    _chmod(szDirName, iMode);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_openFile
 //
 //   Purpose :   Command for open a file
 //
 //   Inputs  :   none
 //
 //	 Returns :   Command for opening of a file
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_openFile(void)
{
    return FILE_OPEN_COMMAND;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_newConsole
 //
 //   Purpose :  To open a new Console window for internal ufunc programs
 //
 //   Inputs  :  none
 //
 //	 Returns :  none
 //   ============================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_newConsole(void)
{
    /* Allocate console window conout$ */
    AllocConsole();

    /* reopen stdout on conout$ for fprintf and printf */
    freopen("conout$", "w", stdout);

    /* Avoid buffer overflows*/
    setvbuf(stdout, NULL, _IONBF, 2);

    printf("This is Windows Printing\n");
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_sleep
 //
 //   Purpose :  Specifies the time, in seconds,for which to suspend execution
 //
 //   Inputs  :  iTime - Specifies the time, in seconds,
 //
 //	 Returns :  none
 //   ============================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_sleep(int iTime)
{
    Sleep(iTime * 1000);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_sleepMilli
 //
 //   Purpose :  Specifies the time, in milliseconds,for which to suspend execution
 //
 //   Inputs  :  iTime - Specifies the time, in milliseconds,
 //
 //  Returns :  none
 //   ============================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_sleepMilli(int iTime)
{
    Sleep(iTime);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_getLoadDefnFilePath
 //
 //   Purpose :  To get the Load definition File Path
 //
 //   Inputs  :  none
 //
 //	 Returns :
 //   ============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getLoadDefnFilePath(void)
{
    return LOAD_DEFN_FILE;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_moveFiles
 //
 //   Purpose :   To Move files from source to destination
 //
 //   Inputs  :   szSrcLoc   - Source file location
 //               szDesLoc   - Destination directory
 //
 //	 Returns :
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_moveFiles(char* szSrcLoc, char* szDesLoc)
{
    int iFail = 0;

    char szMoveFile[BUFSIZ] = "";

    sprintf(szMoveFile, "%s %s %s", MOVE_COMMAND, szSrcLoc, szDesLoc);

    iFail = system(szMoveFile);

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_renameTifFiles
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

extern void GET_WIN32_renameTifFiles(char* szTmpDir, char* szTabNum, char* szItemId)
{
    char szOldTifName[256] = "";
    char szTifName[256] = "";

    int iFail = 0;

    DIR* dirp;
    struct dirent *dp;

    /* now read the TIF file name(s) in the dir and rename them  */
    dirp = opendir(szTmpDir);
    while ((dp = readdir(dirp)) != NULL)
    {
        if (strcmp(&dp->d_name[strlen(dp->d_name) - 4], ".tif") == 0)
        {
            sprintf(szTifName, "%s%s%s%s", szTmpDir, FILE_SEP_WIN32, szTabNum, &dp->d_name[strlen(szItemId)]);
            sprintf(szOldTifName, "%s%s%s", szTmpDir, FILE_SEP_WIN32, dp->d_name);
            printf("Found: %s - renaming to %s\n", dp->d_name, szTifName);

            iFail = rename(szOldTifName, szTifName);
            if (iFail != 0)
            {
                printf("Error renaming TIF file");
                iFail = 1;
                return;
            }
        }
        else
        {
            printf("Skipping: %s\n", dp->d_name);
        }
    }

    (void) closedir(dirp);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_basename
 //
 //   Purpose :
 //
 //
 //   Inputs  :
 //
 //	 Returns :  none
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_basename(const char* path, char** base)
{
    int iFail = 0;
    size_t i = 0;
    char* _path = NULL;
    char* _base = NULL;

    _path = _strdup(path);

    /* Do a reverse search for the delimeter */
    for (i = strlen(_path); i > 0; i--)
    {
        if (_path[i] == '\\')
        {
            _base = &(_path[i + 1]);
            break;
        }
    }

    /* If no delimiter found, return complete string */
    if (_base == NULL)
    {
        _base = &(_path[0]);
    }

    *base = (char*) malloc(sizeof(char) * strlen(_base) + 1);

    strcpy(*base, _base);

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_runBckgrdSysCmd
 //
 //   Purpose :  Run a system command in the background
 //
 //   Inputs  :  command - command to execute in background
 //
 //	 Returns :  success status
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_runBckgrdSysCmd(char* command)
{
    int iFail = 0;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    if (!CreateProcess(NULL, // No module name (use command line)
            command, // Command line
            NULL, // Process handle not inheritable
            NULL, // Thread handle not inheritable
            FALSE, // Set handle inheritance to FALSE
            0, // No creation flags
            NULL, // Use parent's environment block
            NULL, // Use parent's starting directory 
            &si, // Pointer to STARTUPINFO structure
            &pi) // Pointer to PROCESS_INFORMATION structure
    )
    {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        iFail = GetLastError();
        return iFail;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return iFail;
}

/**
 * Function to create socket connection between server and client
 * 
 * @param	Host where LR daemon is running
 * @param 	Port on which LR daemon is registered
 * @param	pointer to Socket File Descriptor
 * 
 * @return status 0 for success and 1 for failure
 */

extern int GET_WIN32_connectServer(const char* szServer, const int iPort, int* iSockFd)
{
    WSADATA wsaData;
    struct hostent *tHe;
    int iTempSockFd = -1;
    struct sockaddr_in servAddr;

    *iSockFd = -1; /* -1 is error */
    int iFail = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iFail != NO_ERROR)
    {
        fprintf(stderr, "WSAStartup failed with error: %d\n", iFail);
        return 1;
    }

    /* Create socket descriptor */
    iTempSockFd = (int)socket(PF_INET, SOCK_STREAM, 0);
    if (iTempSockFd == INVALID_SOCKET)
    {
        fprintf(stderr, "socket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    tHe = gethostbyname(szServer);
    /* Get IP address of host */
    if (tHe == NULL)
    {
        fprintf(stderr, "Error in getting IP address\n");
        WSACleanup();
        return 1;
    }

    servAddr.sin_family = AF_INET; /* host byte order */
    servAddr.sin_port = htons(iPort); /* short, network byte order */
    servAddr.sin_addr = *((struct in_addr *) tHe->h_addr);
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    /* Connect to server */
    int iConnect = connect(iTempSockFd, (struct sockaddr*) &servAddr, sizeof(struct sockaddr));
    if (iConnect == SOCKET_ERROR)
    {
        fprintf(stderr, "connect failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    *iSockFd = iTempSockFd;

    /* Return 0 for success and non-zero is error */
    return 0;
}

/**
 * Function to send request string to server
 * 
 * @param	iSockFd - Socket File Descriptor
 * @param 	szXMLStr -	Request string to Server
 * 
 * @return status 0 for success and 1 for failure
 */

extern int GET_WIN32_sendRequest(const int iSockFd, const char *szBuf)
{
    unsigned int iTotal = 0; /* how many bytes we've sent */
    size_t iBytesLeft = strlen(szBuf); /* how many we have left to send */
    int iCount = 0;

    while (iTotal < strlen(szBuf))
    {
        iCount = send(iSockFd, szBuf + iTotal, (int)iBytesLeft, 0);

        if (iCount == SOCKET_ERROR)
        {
            fprintf(stderr, "send failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        iTotal += iCount;
        iBytesLeft -= iCount;
    }

    return 0;
}

/**
 * Function to receive request string from server
 * 
 * @param	iSocketFd - Socket File Descriptor
 * @param 	iWaitTime  - Time to wait to get response from server
 * @param	iSleepTime - Time in milli seconds to sleep before reading server response
 * 
 * @return status 0 for success and 1 for failure
 */

extern int GET_WIN32_receiveResponse(const int iSockFd, const int iWaitTime, const int iSleepTime, char** szResponse)
{
    int iRetVal = 0;
    int iNumBytes = 0;
    const int iBufSize = 4096;
    fd_set tReadFds;
    struct timeval tTimeVal;
    char szBuf[iBufSize] = "";

    string szTempResponse = "";

    *szResponse = NULL;

    /* Clear the set ahead of time */
    FD_ZERO(&tReadFds);

    /* add our descriptors to the set */
    FD_SET(iSockFd, &tReadFds);

    /* wait until either socket has data ready to be recv()d, or timeout occurs */
    tTimeVal.tv_sec = iWaitTime;
    tTimeVal.tv_usec = 0;
    iRetVal = select(iSockFd + 1, &tReadFds, NULL, NULL, &tTimeVal);
    if (iRetVal == SOCKET_ERROR)
    {
        fprintf(stderr, "select failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else if (iRetVal == 0)
    {
        fprintf(stderr, "socket connection timed out\n");
        WSACleanup();
        return 1;
    }

    Sleep(iSleepTime);

    int totalBytes = 0;

    do
    {
        iNumBytes = recv(iSockFd, szBuf, iBufSize - 1, 0);
        if (iNumBytes > 0)
        {
            szTempResponse += string(szBuf);
            totalBytes += iNumBytes;
        }
        else if (iNumBytes == 0)
        {
            if (totalBytes == 0)
            {
                // failed to receive anything from the socket
                WSACleanup();
                return 1;
            }
        }
        else
        {
            fprintf(stderr, "recv failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
    } while (iNumBytes > 0);

    string strResponse = szTempResponse;

    size_t indx1 = strResponse.find("[");
    size_t indx2 = strResponse.find("]");

    if (indx1 != 0 || indx2 < 2)
    {
        fprintf(stderr, "Invalid string: %s\n", strResponse.c_str());
        return 1;
    }
    else
    {
        int length = atoi((strResponse.substr(indx1 + 1, indx2 - 1)).c_str());

        string szReply = strResponse.substr(indx2 + 1, length);

        *szResponse = (char*) malloc(sizeof(char) * (szReply.length() + 1));
        strcpy(*szResponse, szReply.c_str());
    }

    return 0;
}

/**
 * Function to close connection with server
 * 
 * @param	iSocketFd - Socket File Descriptor
 * 
 * @return status 0 for success and 1 for failure
 */
extern int GET_WIN32_closeConnection(const int iSockFd)
{
    int iFail = closesocket(iSockFd);

    if (iFail == SOCKET_ERROR)
    {
        fprintf(stderr, "close socket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();

    return 0;
}

extern int GET_WIN32_intToString(const long value, char* string)
{
    _ltoa(value, string, 10);

    return 0;
}

extern int GET_WIN32_strcmp(const char* s1, const char* s2, const int flag)
{
    int result = 0;

    if (flag == 0)
    {
        result = strcmp(s1, s2);
    }
    else
    {
        result = _stricmp(s1, s2);
    }

    return result;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_renameFiles
 //
 //   Purpose :  To rename File names using Tabulated number and item id
 //              in the specified directory
 //
 //   Inputs  :  szTmpDir   - The Directory name in which tif files present
 //              szTabNum   - Tabulated shop mod Number
 //              szItemId   - Itemid
 //				 szFileType - Type of file (Ex: tif,pdf,...)
 //	 Returns :  none
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern void GET_WIN32_renameFiles(char* szTmpDir, char* szTabNum, char* szItemId, char *szFileType)
{
    char szOldTifName[256] = "";
    char szTifName[256] = "";

    int iFail = 0;

    DIR* dirp;
    struct dirent *dp;

    /* now read the file name(s) in the dir and rename them  */
    dirp = opendir(szTmpDir);
    while ((dp = readdir(dirp)) != NULL)
    {
        if (strcmp(&dp->d_name[strlen(dp->d_name) - 4], szFileType) == 0)
        {
            sprintf(szTifName, "%s%s%s%s", szTmpDir, FILE_SEP_WIN32, szTabNum, &dp->d_name[strlen(szItemId)]);
            sprintf(szOldTifName, "%s%s%s", szTmpDir, FILE_SEP_WIN32, dp->d_name);
            printf("Found: %s - renaming to %s\n", dp->d_name, szTifName);

            iFail = rename(szOldTifName, szTifName);
            if (iFail != 0)
            {
                printf("Error while renaming file");
                iFail = 1;
                return;
            }
        }
        else
        {
            printf("Skipping: %s\n", dp->d_name);
        }
    }

    (void) closedir(dirp);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function: GET_WIN32_getUserLoginID
 //
 //   Purpose : To get the users Machine login ID
 //
 //   Inputs  : None
 //
 //   Returns : User machine login ID string
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getUserLoginID(void)
{
    char szLoginID[256] = "";
    char *pszUserID = NULL;
    DWORD cchBuff = 256;

    GetUserName(szLoginID, &cchBuff);

    if (strlen(szLoginID) == 0)
    {
        fputs("\nError: User Login ID is  not defined\n", stderr);
        printf("\nError: User Login ID is  not defined\n");
        return NULL;
    }

    pszUserID = (char*) malloc(strlen(szLoginID) + 1 * sizeof(char));
    strcpy(pszUserID, szLoginID);

    return pszUserID;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_getEnvVariableValue
 //
 //   Purpose :  To get the environment variable value from the command prompt
 //
 //   Inputs  :  Environment variable name
 //	 Returns :  Environment variable value
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getEnvVariableValue(char* envName)
{
    int ifail = 0;
    char *envValue = NULL;
    char buff[4096] = "";
    DWORD nSize = 4096;

    ifail = GetEnvironmentVariable(envName, buff, nSize);

    if (ifail > 0)
    {
        envValue = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(envValue, buff);
    }

    return envValue;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_check_FileOrDirExists
 //
 //   Purpose :  To check of the given file or directory exists in the file
 //              system
 //
 //   Inputs  :  path   - The File/Directory path name to check
 //
 //    Returns : 0 - Exists & Non-Zero - Does Not Exist
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_check_FileOrDirExists(const char* path)
{
    return (_access(path, 0));
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_WIN32_changeDirectory
 //
 //   Purpose :  To check the directory location from within the code
 //
 //   Inputs  :  path   - The Absolute Directory path name
 //	 Returns :  (0 - Success & Non-Zero - Failure)
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_changeDirectory(const char *path)
{
    return _chdir(path);
}

/*STARTFUNCDOC ***
 //   ==============================================================================
 //   Function:  GET_WIN32_PrepStringForCmd
 //
 //   Purpose :  To prepare string for windows cmd to avoid conversion due to special
 //				characters in string.
 //   Inputs  :  stringVal   - string
 //	 Returns :  return string
 //              (Conversion not required for windows cmd.)
 //   ==============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_PrepStringForCmd(const char *stringVal)
{
    char *pszValue = (char*) malloc(strlen(stringVal) + 1 * sizeof(char));
    strcpy(pszValue, stringVal);
    return pszValue;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_Scan_FilesInDirectory
 //
 //   Purpose:   To scan a directory and list all the files
 //
 //   Inputs:   dirName    - The name of the directory to be scanned
 //
 //   Returns:  files      - List of files inside the directory
 //              file_count - Total number of files inside dir
 //
 //   Returns :   Current date
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_WIN32_Scan_FilesInDirectory(char* dirName, int MaxFile_Count, char*** files, int* file_count)
{
    int ifile = 0;
    char* pname = NULL;
    WIN32_FIND_DATA info;
    char* dirScan = NULL;
    char** fileList = NULL;
    (*file_count) = 0;
    (*files) = NULL;

    dirScan = (char *) malloc(strlen(dirName) + 4);
    sprintf(dirScan, "%s*.*", dirName);
    HANDLE h = FindFirstFile(dirScan, &info);
    free (dirScan);

    if (h == INVALID_HANDLE_VALUE)
    {
        printf("\n Error in reading directory");
        return -1;
    }
    fileList = (char**) malloc(MaxFile_Count * sizeof(char*));
    do
    {
        if ((info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
            /* skip directories */
            continue;
        }
        pname = (char*) malloc((strlen(info.cFileName) + 1) * sizeof(char));
        strcpy(pname, info.cFileName);
		fileList[ifile] = pname;
        ifile = ifile + 1;
    } while (FindNextFile(h, &info));

    /* Close directory scan */
    FindClose(h);

    (*file_count) = ifile;
    (*files) = fileList;

    return 0;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_getCurrentTimeMilli
 //
 //   Purpose :   To get the current time in milliseconds since Epoch. Replicates
 //               System.currentTimeMillis() from Java.
 //
 //   Inputs  :   None
 //
 //   Returns :   Current time in milliseconds as a string.
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_WIN32_getCurrentTimeMilli(void)
{
    /************************************
     * Define time at Epoch - 1970/1/1
     ************************************/
    static const __int64 msAtEpoch = 116444736000000000;

    /**************************************
     * Define and Initialize variables
     **************************************/
    stringstream timeSS;
    string retTime = "";
    SYSTEMTIME st;
    FILETIME   ft;
    __int64 t;

    /********************************
     * Get the current time in ns
     ********************************/
    GetSystemTime(&st);
    SystemTimeToFileTime(&st,&ft);

    /*************************************************
     * Move to an __int64 which is long enough to hold it
     *************************************************/
    memcpy(&t,&ft,sizeof t);

    /********************************
     * Scale to ms
     ********************************/
    t = (t - msAtEpoch)/10000;

    /********************************
     * Format as a string
     ********************************/
    timeSS << t;
    retTime += timeSS.str();

    /********************************
     * Format as char*
     ********************************/
    char* cstr_char = new char[retTime.length() + 1];
    strcpy(cstr_char, retTime.c_str());


    return cstr_char;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_WIN32_regexMatch
 //
 //   Purpose :   To compare if the value matches regex pattern
 //
 //   Inputs  :   None
 //
 //   Returns :   true/false
 //  ===============================================================================
 //ENDFUNCDOC   ***/
extern bool GET_WIN32_regexMatch( const char* sPattern, const char* sValue )
{
	return regex_match ( sPattern, regex ( sValue ) );
}
