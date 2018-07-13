/********************************************************************************
 * Copyright     :  General Electric Transportation Systems, Erie
 *
 * Title         :  gets_crypt.h
 *
 * Author        :  Jothiraj P
 *
 * Description   :  This code contains functions declarations for performing
 *                  Base64 decryption of character strings.
 *
 * Requirements  :  Linked to Custom TC utility to decrypt the string
 *
 * History       :
 * ------------------------------------------------------------------------------
 *   Name                Date              Description
 * ------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 ********************************************************************************/


#ifndef GETS_CRYPT_H
#define GETS_CRYPT_H

/**
 * OS Specific Header files
 */
#ifdef UNX
    /* System Includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <string.h>
#elif WIN32
    /* System Includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <io.h>
#elif WIN64
    /* System Includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <io.h>
#endif

/**
 * OS Specific constants
 */
#ifdef UNX
    #ifndef FILE_SEPARATOR
    #define FILE_SEPARATOR   "/"
    #endif

    #ifndef DLLEXPORT
    #define DLLEXPORT
    #endif
#elif WIN32
    #ifndef FILE_SEPARATOR
    #define FILE_SEPARATOR   "\\"
    #endif

    #ifndef DLLEXPORT
    #define DLLEXPORT        __declspec(dllexport)
    #endif
#elif WIN64
    #ifndef FILE_SEPARATOR
    #define FILE_SEPARATOR   "\\"
    #endif

    #ifndef DLLEXPORT
    #define DLLEXPORT        __declspec(dllexport)
    #endif
#endif

/**
 * define constants
 */
#define MAX_TC_PASSWORD_LEN  100
#define MAX_ENCRYPT_PWD_LEN  137

#define GETS_COMMON_DECODE   "GETS_COMMON_DECODE"

/****************************************************************************
 * Function     :  GETS_decode64
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
 * Jothiraj P       03 May 2013       Re-used for GE Trasportation
 *
 ****************************************************************************/
extern DLLEXPORT int GETS_decode64 (const char * in,
                                    unsigned inlen,
                                    char * out,
                                    unsigned * outlen);

/********************************************************************************
 * Function     :  GETS_SYSAPI_check_FileOrDirExists
 *
 * Description  :  Check whether the file or directory exists in the file system
 *
 * Author       :   Jothiraj P
 *
 * Parameters   :  [[in] path - Path of file or directory to check
 *
 * Returns      :  [ 0] - For Success
 *                [!0] - Non-zero for error
 *
 * History      :
 * ------------------------------------------------------------------------------
 *   Name                Date              Description
 * ------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 ********************************************************************************/
extern DLLEXPORT int GETS_SYSAPI_check_FileOrDirExists (const char * path);


/********************************************************************************
 * Function     :  GETS_readPasswordFile
 *
 * Description  :  This function reads the encrypted password from file
 *
 * Author       :   Jothiraj P
 *
 * Parameters   :  [in]  pwf          - Encrypt/Decrypt mode
 *                 [out] pEncryptedPw - Encrypted Pwd File path
 *
 * Returns      :  [ 0] - SUCCESS
 *                 [-1] - FAILURE
 *
 * History      :
 * ------------------------------------------------------------------------------
 *   Name                Date              Description
 * ------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 ********************************************************************************/
extern DLLEXPORT int GETS_readPasswordFile (const char * pwf,
                                            char ** pEncryptedPw);

/*****************************************************************************
 * Function     :  GETS_unEncryptPwd
 *
 * Description  :  Unencrypt the passcode
 *
 * Author       :   Jothiraj P
 *
 * Parameters   :  [in]  userId     - TC User Id
 *                 [out] userPasswd - TC Passcode
 *
 * Returns      :  [ 0] - SUCCESS
 *                 [-1] - FAILURE
 *
 * STDOUT       :  [Encrypted /Decrypted] password (or) ERROR
 *
 * History      :
 * ------------------------------------------------------------------------------
 *   Name                Date              Description
 * ------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 *****************************************************************************/
extern DLLEXPORT int GETS_unEncryptPwd (char * userId, char * userPasswd);

#endif /* GETS_CRYPT_H */
