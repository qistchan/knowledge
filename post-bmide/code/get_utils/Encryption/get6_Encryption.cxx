/********************************************************************************
 * Copyright     :  General Electric Transportation Systems, Erie
 *
 * Title         :  gets_encryption.cxx
 *
 * Author        :  TCS Development Team
 * Description   :  1. This program reads a single parameter and
 *                     encrypts it using Base64 encryption
 *                  2. This program reads a file path and decrpt the
 *                     word from the file using Base64 decryption
 *
 * Requirements  :  Depend on "GET_sysapi.cxx" & "gets_crypt.h" file
 *                  for Decrypting funtions
 *
 * History       :
 * ------------------------------------------------------------------------------
 *   Name                Date              Description
 * ------------------------------------------------------------------------------
 * TCS Team         01 Oct 2016         Created
 *
 ********************************************************************************/


/**
 *  C Header Files
 */
#include <stdio.h>
#include <string.h>

/**
 *  GETS Header Files
 */
#include "get6_crypt.h"

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

/**
 * Global Variables
 */
static char basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????";

/*****************************************************************************
 * Function     :  GETS_encode64
 *
 * Author       :  Kevin Fait
 *
 * Description  :  This function will encrypt a character string using
 *                 Base64 encryption algorithm
 *
 * Parameters   :  [in]  _in    - Character string to be encrypted
 *                 [in]  inlen  - Length of the input character string
 *                 [out] _out   - The encrypted result of the string
 *                 [in]  outmax - The maximum length of the encrypted result
 *                 [out] outlen - The length of the encrypted result
 *
 * Returns      :  [ 0] - SUCCESS
 *                 [-2] - On Buffer Overflow
 *
 * History     :
 * --------------------------------------------------------------------------
 *   Name                Date              Description
 * --------------------------------------------------------------------------
 * Kevin Fait				27 Mar 2002       Designed
 * TCS Development Team     02 Oct 2016       Re-used for GE Trasportation
 *
 *****************************************************************************/
int GET6_encode64(const char *_inStr, unsigned inStrLen, char *_outStr, unsigned outMax, unsigned *outLen)
{
    const unsigned char * inStr = (const unsigned char *) _inStr;
    unsigned char * outStr = (unsigned char *) _outStr;
    unsigned char oVal;
    char * cOutStr;
    unsigned oLen;

    oLen = (inStrLen + 2) / 3 * 4;

    if (outLen) *outLen = oLen;

    if (outMax < oLen) return BUFOVER;

    cOutStr = (char *) outStr;

    while (inStrLen >= 3)
    {
        /* user provided max buffer size; make sure we don't go over it */
        *outStr++ = basis_64[inStr[0] >> 2];
        *outStr++ = basis_64[((inStr[0] << 4) & 0x30) | (inStr[1] >> 4)];
        *outStr++ = basis_64[((inStr[1] << 2) & 0x3c) | (inStr[2] >> 6)];
        *outStr++ = basis_64[inStr[2] & 0x3f];
        inStr += 3;
        inStrLen -= 3;
    }

    if (inStrLen > 0)
    {
        /* user provided max buffer size; make sure we don't go over it */
        *outStr++ = basis_64[inStr[0] >> 2];
        oVal = (inStr[0] << 4) & 0x30;

        if (inStrLen > 1) oVal |= inStr[1] >> 4;

        *outStr++ = basis_64[oVal];
        *outStr++ = (inStrLen < 2) ? '=' : basis_64[(inStr[1] << 2) & 0x3c];
        *outStr++ = '=';
    }

    if (oLen < outMax) *outStr = '\0';

    return SUCCESS;
}

/*****************************************************************************
 * Function     :  main
 *
 * Description  :  This program will read in a single string and encrypt it
 *                 for use in the Company Attribute Active Response module
 *
 * Parameters   :  [in] argc - Encrypt/Decrypt mode
 *              :  [in] argv - Character string to be Encrypted/File path which
 *                             contains the Encrypted word to Decrypt
 *
 * Returns      :  [ 0] - SUCCESS
 *                 [-1] - FAILURE
 *
 * STDOUT       :  [Encrypted /Decrypted] password (or) ERROR
 *
 *****************************************************************************/
int main(int argc, char *argv[])
{

    /* Declare variables */
    int iReturnVal             = SUCCESS;
    int iFuncCode              = 0;

    unsigned nPasswordLen      = 0;
    unsigned nEncryptedPwLen   = 0;
  
    char szPassword      [MAX_TC_PASSWORD_LEN + 1];
    char szEncryptedPw   [MAX_ENCRYPT_PWD_LEN + 1];
   
    /* Initialize variables */
    (void) memset (szPassword,      '\0', MAX_TC_PASSWORD_LEN + 1);
    (void) memset (szEncryptedPw,   '\0', MAX_ENCRYPT_PWD_LEN + 1);
  
    /* Check the number of arguments passed */
    if (argc != NUM_PARAMETERS)
    {
        iReturnVal = FAILURE;
    }

    /* Encrypt the password */
    if (iReturnVal == SUCCESS)
    {
        if (strcmp(argv[PARAM_MODE], ENCRYPT_L) == 0 ||
            strcmp(argv[PARAM_MODE], ENCRYPT_U) == 0)
        {
            /* Get the the password and string length */
            if (strlen (argv[PARAM_PASSWORD]) <= MAX_TC_PASSWORD_LEN)
            {
                /* Get the the password and string length */
                (void) strncpy (szPassword,
                                argv[PARAM_PASSWORD],
                                MAX_TC_PASSWORD_LEN);

                nPasswordLen = strlen (szPassword);

                iFuncCode = GET6_encode64 (szPassword,
                                           nPasswordLen,
                                           szEncryptedPw,
                                           MAX_ENCRYPT_PWD_LEN,
                                           &nEncryptedPwLen);

                if (iFuncCode != 0)
                {
                    iReturnVal = FAILURE;
                }
                else
                {
                    /* Display the encrypted Pwd */
                    (void) printf ("%s\n", szEncryptedPw);
                }
            }
            else
            {
                iReturnVal = FAILURE;
            }
        }
    }

    /* Display the error message */
    if (iReturnVal == FAILURE)
    {
        (void) printf ("ERROR");
    }

    /****************************************
     * return result
     ****************************************/
    return (iReturnVal);

}
