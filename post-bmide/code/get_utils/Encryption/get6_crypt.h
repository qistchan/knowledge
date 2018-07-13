/********************************************************************************
 * Copyright     :  General Electric Transportation Systems, Erie
 *
 * Title         :  gets_crypt.h
 *
 * Description   :  This code contains functions declarations for performing
 *                  Base64 decryption of character strings.
 *
 * ------------------------------------------------------------------------------
 *   Name                       Date              Description
 * ------------------------------------------------------------------------------
 * TCS Development Team         02 Oct 2016          Created
 *
 ********************************************************************************/

#ifndef GETS_CRYPT_H
#define GETS_CRYPT_H

/**
 * OS Specific Header files
 */
#ifdef _UNX
    /* System Includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <string.h>
#elif _WIN32
    /* System Includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <io.h>
#elif _WIN64
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
#ifdef _UNX
    #ifndef FILE_SEPARATOR
    #define FILE_SEPARATOR   "/"
    #endif

    #ifndef DLLEXPORT
    #define DLLEXPORT
    #endif
#elif _WIN32
    #ifndef FILE_SEPARATOR
    #define FILE_SEPARATOR   "\\"
    #endif

    #ifndef DLLEXPORT
    #define DLLEXPORT        __declspec(dllexport)
    #endif
#elif _WIN64
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
/**
 *  define constants
 */
#define  NUM_PARAMETERS       3
#define  PARAM_MODE           1
#define  PARAM_PASSWORD       2

#define SUCCESS               0
#define FAILURE               -1
#define BUFOVER               -2

#define  ENCRYPT_L            "/e"
#define  ENCRYPT_U            "/E"
#define  DECRYPT_L            "/d"
#define  DECRYPT_U            "/D"


#endif /* GETS_CRYPT_H */
