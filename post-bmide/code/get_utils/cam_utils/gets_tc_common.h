/********************************************************************************
 * Copyright     :  General Electric Transportation Systems, Erie
 *
 * Title         :  gets_tc_common.h
 *
 * Author        :  Jothiraj P
 *
 * Description   :  This code contains the declaration of TC common functions
 *
 * Requirements  :  Linked to TC code for using the common funtions
 *
 * History       :
 * ------------------------------------------------------------------------------
 *   Name                Date              Description
 * ------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 ********************************************************************************/


#ifndef GETS_TC_COMMON_H
#define GETS_TC_COMMON_H

/** GETS Header Files */
#include <gets_crypt.h>
//#include <gets_tc_macros.h>

/** TC Includes */
#include <tc/tc.h>

/**********************************************************************************
 * Function     :  GETS_HPA_secured_login
 *
 * Description  :  Secured Login for TC using "-u=" (Only TC DBA User "infodba" &
 *                 "imanadmn") & "-g=" values supplied via command line arguments
 *
 * Author       :  Jothiraj P
 *
 * Parameters   :  none
 *
 * Returns      :  [ 0]  - SUCCESS
 *                 [!0]  - FAILURE
 *
 * History      :
 * --------------------------------------------------------------------------------
 *   Name                Date              Description
 * --------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 **********************************************************************************/
//extern DLLEXPORT int GETS_HPA_secured_login ();

/**********************************************************************************
 * Function     :  GETS_manual_login
 *
 * Description  :  Manually logging into TC using "-u=", "-p=" & "-g="[Optional]
 *                 values supplied via command line arguments
 *
 * Author       :  Jothiraj P
 *
 * Parameters   :  none
 *
 * Returns      :  [ 0]  - SUCCESS
 *                 [!0]  - FAILURE
 *
 * History      :
 * --------------------------------------------------------------------------------
 *   Name                Date              Description
 * --------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 **********************************************************************************/
//extern DLLEXPORT int GETS_manual_login ();

/**********************************************************************************
 * Function     :  GETS_info_log
 *
 * Description  :  Logging the message into STDOUT & TC Syslog
 *
 * Author       :  Jothiraj P
 *
 * Parameters   :  none
 *
 * Returns      :  [ 0]  - SUCCESS
 *                 [!0]  - FAILURE
 *
 * History      :
 * --------------------------------------------------------------------------------
 *   Name                Date              Description
 * --------------------------------------------------------------------------------
 * Jothiraj P         03 May 2013          Created
 *
 **********************************************************************************/
//extern DLLEXPORT void GETS_info_log ( const char * message );

#endif /* GETS_TC_COMMON_H */
