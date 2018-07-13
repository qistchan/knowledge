/* System Includes */
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/param.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pwd.h> 

/* GET Includes */
#include <GET_unx.h>
#include <GET_syspath.h>
#include <GET_sysconst.h>

//C++ includes
#include <string>
#include <GET_cpp_stl.h>

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

extern void GET_UNX_getDate(const char* dateFormat, char** date)
{
    struct timeval tp;
    struct tm* timer;

    (*date) = NULL;

    gettimeofday(&tp, 0);

    timer = localtime(&(tp.tv_sec));
    (*date) = (char*) malloc(sizeof(char) * 128);
    strftime((*date), sizeof(char) * 128, dateFormat, timer);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_UNX_makeUniqueName
 //
 //    Purpose:   To  a unique file name
 //
 //     Inputs:   iPathLength - contains value of SS_MAXPATHLEN defined in
 //               ss_const.h (iMAN header file)
 //
 //    Returns:   A string built from the process id and the user name
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_makeUniqueName(int iPathLength)
{
    char szSeed[BUFSIZ] = "";
    char* pszTempName = NULL;
    char* id = NULL;

    pszTempName = (char*) malloc((iPathLength + 1) * sizeof(char));
    if ((id = getlogin()) != NULL)
    {
        sprintf(szSeed, "%s_XXXXXX", getlogin());
    }
    else
    {
        sprintf(szSeed, "user_XXXXXX");
    }

    mktemp(szSeed);
    strncpy(pszTempName, szSeed, iPathLength);

    return pszTempName;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //    Function:  GET_UNX_deleteFilesInDirectory
 //
 //    Purpose:  Deletes the files in the specified directory
 //
 //    Inputs:  szDirName - The directory name in which the files to be deleted
 //
 //    Returns:
 //   ==============================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_deleteFilesInDirectory(char* szDirName)
{
    int iFail = 0;

    DIR *pDir = NULL;

    struct dirent *psDir = NULL;
    struct stat sStat;

    printf("Trying to open %s\n", szDirName);

    // try to open the passed in directory
    pDir = opendir(szDirName);
    if (!pDir)
    {
        perror("Could not open directory");
        iFail = -1;
    }

    // change to it since psDir->d_name doesn't give full path names
    if (chdir(szDirName))
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
            if (lstat(psDir->d_name, &sStat))
            {
                perror("Could not stat");
                iFail = -1;
                break;
            }

            if (S_ISLNK(sStat.st_mode))
            {
                // don't follow links
                printf("cannot remove a symbolic link\n");
            }
            else
            {
                if (S_ISDIR(sStat.st_mode))
                {
                    // this is a directory so recurse
                    GET_UNX_deleteFilesInDirectory(psDir->d_name);
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

    // Now close the directory, back up one and try to remove it
    printf("Closing directory %s\n", szDirName);
    closedir(pDir);
    if (chdir(".."))
    {
        perror("Could not back up one level");
        iFail = -1;
    }

    printf("changed directory to %s\n", getenv("PWD"));
    printf("removing directory %s\n", szDirName);

    if (rmdir(szDirName))
    {
        perror("Could not remove the directory");
        iFail = -1;
    }

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //    Function:   GET_UNX_createDirectory
 //
 //    Purpose:   To create a directory with given permissions
 //
 //    Inputs:   szDir    - The name of the directory to be created
 //              iMode    - The permissions for the Directory
 //
 //    Returns:
 //   ========================================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_createDirectory(const char* szDir, int iMode)
{
    int iCreateDir = 0;

    char szCmd[BUFSIZ] = "";

    if (iMode == -1) //-m gives error if Windows NFS is mounted on unix file system. Avoid -m option if -1 is passed
    {
        sprintf(szCmd, "mkdir %s", szDir);
    }
    else
    {
        sprintf(szCmd, "mkdir -m %d %s", iMode, szDir);
    }

    iCreateDir = system(szCmd);

    return iCreateDir;
}

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

extern void GET_UNX_removeDirectory(const char* szDir)
{
    char szCmd[BUFSIZ] = "";

    sprintf(szCmd, " %s %s > /dev/null 2>&1", REMOVE_DIR, szDir);
    system(szCmd);
}

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

extern void GET_UNX_renameDirectory(const char* szDir, const char* pszNewName)
{
    char szCmd[BUFSIZ] = "";

    sprintf(szCmd, "%s %s %s > /dev/null 2>&1 ", MOVE_COMMAND, szDir, pszNewName);
    system(szCmd);
}

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

extern int GET_UNX_getProcessId(void)
{
    return getpid();
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_UNX_unLink
 //
 //    Purpose:   To delete the specified file
 //
 //     Inputs:   tempFile - The name of the file to be deleted
 //
 //    Returns:
 // ================================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_unLink(char* tempFile)
{
    return unlink(tempFile);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_getLogin
 //
 //   Purpose :  To get the users login name
 //
 //   Inputs  :  none
 //
 //   Returns :  the user login on this machine
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_getLogin(void)
{
    char *szUserName = NULL;
    char* buff = NULL;

    buff = getenv("LOGNAME");

    if (buff != NULL)
    {
        szUserName = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(szUserName, buff);
    }

    return szUserName;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_getTempFileName;
 //
 //   Purpose :  To get the temporary file name using site code and process id
 //
 //   Inputs  :  pid         - Process id
 //              siteCode    - Site code
 //              isTestImage - Test image flag
 //
 //   Returns :  The temporary file name
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_getTempFileName(char* siteCode, int pid, int isTestImage)
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
            sprintf(buff, "%s%s%s%stmp_%d", TRANSFER_OWNER_LOG_DIR_TEST, FILE_SEP_UNX, siteCode, FILE_SEP_UNX, pid);
        }
        else
        {
            if (IS_MILITARY)
            {
                sprintf(
                        buff,
                        "%s%s%s%stmp_%d",
                        TRANSFER_OWNER_LOG_DIR_PROD_MILITARY,
                        FILE_SEP_UNX,
                        siteCode,
                        FILE_SEP_UNX,
                        pid);
            }
            else
            {
                sprintf(buff, "%s%s%s%stmp_%d", TRANSFER_OWNER_LOG_DIR_PROD, FILE_SEP_UNX, siteCode, FILE_SEP_UNX, pid);
            }
        }

        tmpfile = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(tmpfile, buff);
    }

    return tmpfile;
}

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

extern char* GET_UNX_getFileSeparator(void)
{
    static char* fileSep = NULL;

    if (fileSep == NULL)
    {
        fileSep = strdup(FILE_SEP_UNX);
    }

    return fileSep;
}

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

extern char* GET_UNX_getPATHSeparator(void)
{
    static char* pathSep = NULL;

    if (pathSep == NULL)
    {
        pathSep = strdup(PATH_SEP_UNX);
    }

    return pathSep;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_getTempDir;
 //
 //   Purpose :  To get the temporary directory name
 //
 //   Inputs  :  none
 //
 //   Returns :  The temporary directory name
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_getTempDir(void)
{
    static char* tempDir = NULL;

    if (tempDir == NULL)
    {
        tempDir = strdup(GET_TEMP_DIR);
    }

    return tempDir;
}

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

extern int GET_UNX_zipDir(char* tmp_loc, char* tar_ball)
{
    char tar_command[BUFSIZ] = "";
    int iFail = 0;

    /* Now tar directory tmp_loc and compress tar file */
    sprintf(tar_command, "cd %s; %s %s.zip *;", tmp_loc, ZIP_COMMAND, tar_ball);
    iFail = system(tar_command);

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_moveDir
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

extern int GET_UNX_moveDir(char* tmp_loc, char* tar_ball, char* siteCode, int isTestImage)
{
    char mv_command[BUFSIZ] = "";
    int iFail = 0;

    char *szSiteCode = NULL;
    int IS_MILITARY = 0;

    szSiteCode = getenv("SITECODE");

    if (szSiteCode != NULL && !strcmp(szSiteCode, "evml1"))
    {
        IS_MILITARY = 1;
    }
    if (isTestImage)
    {
        sprintf(
                mv_command,
                "cd %s; %s %s.tar.Z \"%s%s%s\"",
                tmp_loc,
                MOVE_COMMAND,
                tar_ball,
                TRANSFER_OWNER_LOG_DIR_TEST,
                FILE_SEP_UNX,
                siteCode);
    }
    else
    {
        if (IS_MILITARY)
        {
            sprintf(
                    mv_command,
                    "cd %s; %s %s.tar.Z \"%s%s%s\"",
                    tmp_loc,
                    MOVE_COMMAND,
                    tar_ball,
                    TRANSFER_OWNER_LOG_DIR_PROD_MILITARY,
                    FILE_SEP_UNX,
                    siteCode);
        }
        else
        {
            sprintf(
                    mv_command,
                    "cd %s; %s %s.tar.Z \"%s%s%s\"",
                    tmp_loc,
                    MOVE_COMMAND,
                    tar_ball,
                    TRANSFER_OWNER_LOG_DIR_PROD,
                    FILE_SEP_UNX,
                    siteCode);
        }
    }

    iFail = system(mv_command);

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_UNX_createPipe
 //
 //    Purpose:   To create the pipe and execute the command
 //
 //     Inputs:   szCommand   -  Command to be executed
 //               mode        -  Mode of the command
 //
 //    Returns:
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern FILE* GET_UNX_createPipe(const char* szCommand, const char* mode)
{
    return (FILE*) popen(szCommand, "r");
}

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

extern int GET_UNX_closePipe(FILE* fp)
{
    return pclose(fp);
}

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

extern char* GET_UNX_deleteFiles(void)
{
    static char* delCmd = NULL;

    if (delCmd == NULL);
    {
        delCmd = strdup(FILE_DEL_COMMAND);
    }

    return delCmd;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_clearScreen
 //
 //    Purpose:  To clear the Screen
 //
 //     Inputs:  none
 //
 //    Returns:  none
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern void GET_UNX_clearScreen(void)
{
    system("clear");
}

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

extern char* GET_UNX_getExportLogDirPath(int isTestImage)
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
 //   Function:  GET_UNX_getHomeDir;
 //
 //   Purpose :  To get the Home Directory
 //
 //   Inputs  :  none
 //
 //	 Returns :  The user HOME directory
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_getHomeDir(void)
{
    char* pszHomeDir = NULL;
    char buff[BUFSIZ] = "";

    strcpy(buff, getenv("HOME"));

    if (buff != NULL)
    {
        pszHomeDir = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(pszHomeDir, buff);
    }

    return pszHomeDir;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_getHostName
 //
 //   Purpose :  Get the name of the current host
 //
 //   Inputs  :  none
 //
 //   Outputs :  szHostName - host name <OF>
 //
 //	 Returns :  success status
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_getHostName(char** szHostName)
{
    int rc = 0;
    char buff[MAXHOSTNAMELEN];

    rc = gethostname(buff, MAXHOSTNAMELEN);

    if (rc == 0)
    {
        (*szHostName) = (char*) malloc(sizeof(char) * strlen(buff) + 1);
        if (*szHostName != NULL)
        {
            strcpy(*szHostName, buff);
        }
    }

    return rc;
}

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
extern char* GET_UNX_getDomainName(void)
{
    char* domainName = NULL;
    FILE* fp = NULL;

    if ((fp = popen("domainname", "r")) != NULL)
    {
        char buff[BUFSIZ];

        if (fgets(buff, BUFSIZ, fp) != NULL)
        {
            domainName = (char*) malloc(sizeof(char) * strlen(buff));
            strncpy(domainName, buff, strlen(buff) - 1);
        }
        pclose(fp);
    }

    return domainName;
}

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

extern int GET_UNX_copyFile(char* szFile1, char* szFile2)
{
    int iFail = 0;
    char szCopyFile[256] = "";

    sprintf(szCopyFile, "cp -f %s %s", szFile1, szFile2);

    iFail = system(szCopyFile);

    return iFail;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_copyDir
 //
 //   Purpose :  To copy the specified Directory from source to destination
 //
 //   Inputs  :  szDir1 - Source Directory
 //              szDir2 - Destination Directory
 //	 Returns :
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_copyDir(char* szDir1, char* szDir2)
{
    int iFail = 0;
    char szCopyDir[256] = "";

    sprintf(szCopyDir, "cp -R %s %s", szDir1, szDir2);

    iFail = system(szCopyDir);

    return iFail;
}

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

extern void GET_UNX_changeDirPermission(char* szDirName, int iMode)
{
    char pszChangeDirPermissions[512] = "";

    sprintf(pszChangeDirPermissions, "chmod -R %d %s", iMode, szDirName);

    system(pszChangeDirPermissions);

    return;
}

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

extern char* GET_UNX_openFile(void)
{
    static char* openCmd = NULL;

    if (openCmd == NULL)
    {
        openCmd = strdup(FILE_OPEN_COMMAND);
    }

    return openCmd;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_UNX_newConsole
 //
 //   Inputs  :   none
 //
 //	 Returns :   none
 //   ============================================================================
 //ENDFUNCDOC   ***/

extern void GET_UNX_newConsole(void)
{
    return;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_sleep
 //
 //   Purpose :  Specifies the time, in seconds,for which to suspend execution
 //
 //   Inputs  :  iTime - Specifies the time, in seconds,
 //
 //	 Returns :  none
 //   ============================================================================
 //ENDFUNCDOC   ***/

extern void GET_UNX_sleep(int iTime)
{
    sleep(iTime);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_sleepMilli
 //
 //   Purpose :  Specifies the time, in milliseconds,for which to suspend execution
 //
 //   Inputs  :  iTime - Specifies the time, in milliseconds,
 //
 //  Returns :  none
 //   ============================================================================
 //ENDFUNCDOC   ***/

extern void GET_UNX_sleepMilli(int iTime)
{
    usleep(iTime * 1000);
}

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

extern char* GET_UNX_getLoadDefnFilePath(void)
{
    static char* loadDefn = NULL;

    if (loadDefn == NULL)
    {
        loadDefn = strdup(LOAD_DEFN_FILE);
    }

    return loadDefn;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:   GET_UNX_moveFiles
 //
 //   Purpose :   To Move files from source to destination
 //
 //   Inputs  :   szSrcLoc   - Source file location
 //               szDesLoc   - Destination file location
 //
 //	 Returns :
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_moveFiles(char* szSrcLoc, char* szDesLoc)
{
    int iFail = 0;

    char szMoveFile[BUFSIZ] = "";

    sprintf(szMoveFile, "%s %s %s", MOVE_COMMAND, szSrcLoc, szDesLoc);

    iFail = system(szMoveFile);

    return iFail;
}

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

extern void GET_UNX_renameTifFiles(char* szTmpDir, char* szTabNum, char* szItemId)
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
            sprintf(szTifName, "%s%s%s%s", szTmpDir, FILE_SEP_UNX, szTabNum, &dp->d_name[strlen(szItemId)]);
            sprintf(szOldTifName, "%s%s%s", szTmpDir, FILE_SEP_UNX, dp->d_name);

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
 //   Function:  GET_UNX_basename
 //
 //   Purpose :
 //
 //   Inputs  :
 //
 //	 Returns :  none
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_basename(const char* path, char** base)
{
    int iFail = 0;
    char* buff = NULL;
    int buffLen = 0;

    buff = basename((char*) path);
    buffLen = strlen(buff) + 1;
    *base = (char*) malloc(sizeof(char) * buffLen);

    strncpy(*base, buff, buffLen);

    return iFail;
}

/*STARTFUNCDOC ***
 //   =================================================================================
 //   Function:  GET_UNX_runBckgrdSysCmd
 //
 //   Purpose :  To execute the command line process in Backgorund
 //
 //   Inputs  :  const char* (Command to be exectued)
 //
 //	 Returns :  none
 //  ===================================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_runBckgrdSysCmd(const char* command)
{
    int iFail = 0;
    int mallocLength = 0;
    int stringLength = 0;
    char* bckgrdCommand = NULL;

    mallocLength = strlen(command) + strlen(" &") + 1;
    bckgrdCommand = (char*) malloc(mallocLength * sizeof(char));

    strcpy(bckgrdCommand, command);
    strcat(bckgrdCommand, " &");

    stringLength = strlen(bckgrdCommand);
    if (stringLength > mallocLength)
    {
        fprintf(stderr, "*** ERROR: String length is more than allocated \n");
        iFail = -1;
    }

    //Triggering the System call in Unix to execute in background mode
    if (iFail == 0)
    {

        iFail = system(bckgrdCommand);
        if (iFail != 0)
        {
            printf("*** ERROR: Executing the command on Unix box in background mode : Error Code: %d\n", iFail);
            fprintf(stderr, "*** ERROR: Executing the command on Unix box in background mode : Error Code: %d\n", iFail);
            iFail = -1;
        }
    }

    //Clean up
    free(bckgrdCommand);
    bckgrdCommand = NULL;

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

extern int GET_UNX_connectServer(const char* szServer, const int iPort, int* iSockFd)
{
    struct hostent *tHe = NULL;
    int iTempSockFd = -1;
    bool bConnectFlag = true;
    struct sockaddr_in servAddr;

    *iSockFd = -1; /* -1 is error */

    /* Create socket descriptor */
    if (bConnectFlag == true)
    {
        if ((iTempSockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        {
            perror("Socket Error");
            bConnectFlag = false;
        }
        else
        {
            tHe = gethostbyname(szServer);
            /* Get IP address of host */
            if (tHe == NULL)
            {
                printf("Error in getting IP address\n");
                bConnectFlag = false;
            }
        }

    }
    if (bConnectFlag == true)
    {
        servAddr.sin_family = AF_INET; /* host byte order */
        servAddr.sin_port = htons(iPort); /* short, network byte order */
        servAddr.sin_addr = *((struct in_addr *) tHe->h_addr);
        memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

        /* Connect to server */
        if (connect(iTempSockFd, (struct sockaddr *) &servAddr, sizeof(struct sockaddr)) == -1)
        {
            perror("connect");
            bConnectFlag = false;
        }
    }

    *iSockFd = iTempSockFd;

    /* Return 0 for success and 1 for failure */
    return (bConnectFlag) ? 0 : 1;
}

/**
 * Function to send request string to server
 * 
 * @param	iSocketFd - Socket File Descriptor
 * @param 	szXMLStr -	Request string to Server
 * 
 * @return status 0 for success and 1 for failure
 */

extern int GET_UNX_sendRequest(const int iSockFd, const char *szBuf)
{
    int iTotal = 0; /* how many bytes we've sent */
    int iBytesLeft = strlen(szBuf); /* how many we have left to send */
    int iCount = 0;

    int bSendResult = false;

    while (iTotal < strlen(szBuf))
    {
        iCount = send(iSockFd, szBuf + iTotal, iBytesLeft, 0);
        if (iCount == -1)
        {
            break;
        }
        iTotal += iCount;
        iBytesLeft -= iCount;
    }
    if (iCount != -1)
    {
        bSendResult = true;
    }

    /* Return 0 for success and 1 for failure */
    return (bSendResult) ? 0 : 1;
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

extern int GET_UNX_receiveResponse(const int iSockFd, const int iWaitTime, const int iSleepTime, char** szResponse)
{
    int iRetVal = 0;
    fd_set tReadFds;
    struct timeval tTimeVal;
    bool bReceiveFlag = true;
    char* szTempResponse = NULL;

    *szResponse = NULL;

    /* clear the set ahead of time */
    FD_ZERO(&tReadFds);

    /* add our descriptors to the set */
    FD_SET(iSockFd, &tReadFds);

    /* wait until either socket has data ready to be recv()d, or timeout occurs */
    tTimeVal.tv_sec = iWaitTime;
    tTimeVal.tv_usec = 0;
    iRetVal = select(iSockFd + 1, &tReadFds, NULL, NULL, &tTimeVal);
    if (iRetVal == -1)
    {
        // error occurred in select()
        perror("select");
        bReceiveFlag = false;
    }
    else if (iRetVal == 0)
    {
        printf("Timeout occurred!\n");
        bReceiveFlag = false;
    }
    else
    {
        //Sleep (for unix is in seconds)
        sleep(iSleepTime / 1000);

        /* descriptor has  data */
        do
        {
            int iNumBytes = 0;
            int iBufSize = 500;
            char szBuf[500];

            if ((iNumBytes = recv(iSockFd, szBuf, iBufSize - 1, 0)) == -1)
            {
                perror("recv");
                bReceiveFlag = false;
                break;
            }
            else
            {
                char* szTempStr = NULL;

                if (iNumBytes == 0)
                {
                    // All the data has been read
                    break;
                }

                if (szTempResponse == NULL || strlen(szTempResponse) == 0)
                {
                    szTempResponse = (char *) malloc((iNumBytes + 1) * sizeof(char));
                    sprintf(szTempResponse, "");
                }
                else
                {
                    szTempResponse = (char *) realloc(szTempResponse, (iNumBytes + strlen(szTempResponse) + 1)
                            * sizeof(char));
                }

                szTempStr = (char *) malloc((iNumBytes + 1) * sizeof(char));
                strncpy(szTempStr, szBuf, iNumBytes);
                szTempStr[iNumBytes] = '\0';
                sprintf(szTempResponse, "%s%s", szTempResponse, szTempStr);
                free(szTempStr);

                // Checking for Success of String Copy
                if (szTempResponse == NULL || strlen(szTempResponse) == 0)
                {
                    fputs("\nError: String copy failed \n", stderr);
                    printf("\nError: String copy failed \n");
                    bReceiveFlag = false;
                    szTempResponse = NULL;
                }
                strcpy(szBuf, "");
            }
        } while (true);
    }

    if (bReceiveFlag != false)
    {
        string strResponse = string(szTempResponse);

        int indx1 = strResponse.find("[");
        int indx2 = strResponse.find("]");

        if (indx1 != 0 || indx2 < 2)
        {
            printf("Invalid string\n");
            bReceiveFlag = false;
        }
        else
        {
            int length = atoi((strResponse.substr(indx1 + 1, indx2 - 1)).c_str());

            string szReply = strResponse.substr(indx2 + 1, length);

            *szResponse = (char *) malloc(sizeof(char) * (szReply.length() + 1));
            strcpy(*szResponse, szReply.c_str());
        }
    }

    /* Return 0 for success and 1 for failure */
    return (bReceiveFlag) ? 0 : 1;
}

/**
 * Function to close connection with server
 * 
 * @param	iSocketFd - Socket File Descriptor
 * 
 * @return status 0 for success and 1 for failure
 */

extern int GET_UNX_closeConnection(const int iSockFd)
{
    int iFail = false;

    if (close(iSockFd) == -1)
    {
        perror("Closing Server Connection");
    }
    else
    {
        iFail = true;
    }

    /* Return 0 for success and 1 for failure */
    return (iFail) ? 0 : 1;
}

extern int GET_UNX_intToString(const long value, char* string)
{
    int ifail = 0;

    ifail = sprintf(string, "%d", value);

    return ifail;
}

extern int GET_UNX_strcmp(const char* s1, const char* s2, const int flag)
{
    int result = 0;

    if (flag == 0)
    {
        result = strcmp(s1, s2);
    }
    else
    {
        result = strcasecmp(s1, s2);
    }

    return result;
}
/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_renameFiles
 //
 //   Purpose :  To rename the File names using Tabulated number and item id
 //              in the specified directory
 //
 //   Inputs  :  szTmpDir   - The Directory name in which tif files present
 //              szTabNum   - Tabulated shop mod Number
 //              szItemId   - Itemid
 //				szFileType - Type of file (Ex: tif,pdf,...)
 //	 Returns :  none
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern void GET_UNX_renameFiles(char* szTmpDir, char* szTabNum, char* szItemId, char* szFileType)
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
            sprintf(szTifName, "%s%s%s%s", szTmpDir, FILE_SEP_UNX, szTabNum, &dp->d_name[strlen(szItemId)]);
            sprintf(szOldTifName, "%s%s%s", szTmpDir, FILE_SEP_UNX, dp->d_name);

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
 //   Function:  GET_UNX_getUserLoginID
 //
 //   Purpose :  To get the users Machine login ID
 //
 //   Inputs  :  none
 //
 //   Returns :  User machine login ID string
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_getUserLoginID(void)
{
    struct passwd *passwd;
    char *pszUserID = NULL;
    char buff[256] = "";

    passwd = getpwuid(getuid());
    strcpy(buff, passwd->pw_name);

    if (strlen(buff) == 0)
    {
        fputs("\nError: User Login ID is  not defined\n", stderr);
        printf("\nError: User Login ID is  not defined\n");

        return NULL;
    }

    pszUserID = (char*) malloc(strlen(buff) + 1 * sizeof(char));
    strcpy(pszUserID, buff);

    return pszUserID;
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_getEnvVariableValue
 //
 //   Purpose :  To get the environment variable value from the command prompt
 //
 //   Inputs  :  Environment variable name
 //
 //   Returns :  Environment variable value
 //  ===============================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_getEnvVariableValue(char* envName)
{
    char* envValue = NULL;
    char* buff = NULL;

    buff = getenv(envName);

    if (buff != NULL)
    {
        envValue = (char*) malloc(strlen(buff) + 1 * sizeof(char));
        strcpy(envValue, buff);
    }

    return envValue;
}

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
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_check_FileOrDirExists(const char* path)
{
    struct stat st;

    return (stat(path, &st));
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_changeDirectory
 //
 //   Purpose :  To check the directory location from within the code
 //
 //   Inputs  :  path   - The Absolute Directory path name
 //	 Returns :  (0 - Success & Non-Zero - Failure)
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_changeDirectory(const char *path)
{
    return (chdir(path));
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //   Function:  GET_UNX_PrepStringForCmd
 //
 //   Purpose :  To prepare string for unix shell to avoid conversion due to special
 //				characters in string.
 //   Inputs  :  stringVal   - string
 //	 Returns :  return string with single quote
 //              (Unix shell treat string with single quote literally.)
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern char* GET_UNX_PrepStringForCmd(const char* stringVal)
{
    char *pszValue = (char*) malloc(strlen(stringVal) + 3 * sizeof(char));
    sprintf(pszValue, "'%s'", stringVal);

    return (pszValue);
}

/*STARTFUNCDOC ***
 //   ===========================================================================
 //    Function:   GET_UNX_Scan_FilesInDirectory
 //
 //    Purpose:   To scan a directory and list all the files
 //
 //    Inputs:   dirName    - The name of the directory to be scanned
 //
 //    Returns:  files      - List of files inside the directory
 //              file_count - Total number of files inside dir
 //   ===========================================================================
 //ENDFUNCDOC   ***/

extern int GET_UNX_Scan_FilesInDirectory(char* dirName, int MaxFile_Count, char*** files, int* file_count)
{
    int iFail = 0;
    int count = 0;
    char* pname = NULL;
    char** fileList = NULL;
    DIR *dp;
    struct dirent *ep;
    (*file_count) = 0;
    (*files) = NULL;

    dp = opendir(dirName);

    if (!dp)
    {
        perror("Could not open directory");
        return -1;
    }
    fileList = (char**) malloc(MaxFile_Count * sizeof(char*));
    while ((ep = readdir(dp)) != NULL)
    {
        pname = (char*) malloc((strlen(ep->d_name) + 1) * sizeof(char));
        strcpy(pname, ep->d_name);
        fileList[count] = pname;
        count = count + 1;
    }

    (void) closedir(dp);

    (*file_count) = count;
    (*files) = fileList;

    return iFail;
}

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

extern char* GET_UNX_getCurrentTimeMilli(void){
    /**************************************
     * Define and Initialize variables
     **************************************/
    stringstream timeSS;
    string retTime = "";
    long onek = (long) 1000;
    timeval currentTime;

    /**************************************
     * Get current time
     **************************************/
    gettimeofday(&currentTime, NULL);

    /**********************************************************
     * Take the microseconds off and convert to milliseconds
     **********************************************************/
    long microsAsMillis = (currentTime.tv_usec / onek);

    /**********************************************************
     * Add the converted microseconds to the end of seconds
     * to get total milliseconds
     **********************************************************/
    if ( microsAsMillis >= 100 )
    {
        timeSS << currentTime.tv_sec << microsAsMillis;
    }
    else if ( microsAsMillis >= 10 )
    {
        timeSS << currentTime.tv_sec << "0" << microsAsMillis;
    }
    else
    {
        timeSS << currentTime.tv_sec << "00" << microsAsMillis;
    }

    /**********************************************************
     * Add the stringstream to the string
     **********************************************************/
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
 //   Function:   GET_UNX_regexMatch
 //
 //   Purpose :   To compare if the value matches regex pattern
 //
 //   Inputs  :   None
 //
 //   Returns :   true/false
 //  ===============================================================================
 //ENDFUNCDOC   ***/
extern bool GET_UNX_regexMatch( const char* sPattern, const char* sValue )
{
	bool bMatches = false;;
	int status;
	regex_t regexObj;

	regmatch_t regMatch[2];

	status = regcomp(&regexObj, sPattern, 0);
	regexec ( &regexObj, sValue, 0, regMatch, 0 ) == 0 ? bMatches = true : false;

	regfree( &regexObj );
	return bMatches;
}
