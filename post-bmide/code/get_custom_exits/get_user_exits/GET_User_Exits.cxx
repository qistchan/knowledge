
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_User_Exits.cxx
//
//   Purpose:   Source File defining the GE Transportation User Exits Implementation
//
//   History:
//   Who                      Date                 Description
//   TCS Development Team     17 Nov, 2016         Initial creation
//   TCS Development Team     01 Sep, 2017         Added User Exit implementation for USER_gs_shell_init_module and registered getter method for the Runtime Property on ECN Revision
//
//   ============================================================================
// ENDFILEDOC   ***/

#include <GET_User_Exits.hxx>
#include <GET_Constants.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_ENG_Extensions.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Types.hxx>

#include <user_exits/user_exits.h>
#include <tc/tc_arguments.h>
#include <tccore/method.h>
#include <ug_va_copy.h>
#include <tccore/custom.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

static void GET_registerMethods();

const string logger = "get.get_user_exits";

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   libGET6_custom_exits_register_callbacks()
 //
 //   Purpose :   Custom Entry Point for this DLL
 //
 //   Inputs  :   none
 //
 //   Outputs :   none
 //
 //   Return  :   ITK_ok(Success)/error code (Failure)
 //
 //   History :
 //      Who                    Date                 Description
 //  TCS Development Team     01 Sep, 2017         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern DLLEXPORT int libGET6_custom_exits_register_callbacks()
{
	int iFail = ITK_ok;

	LOG_TRACE ( logger, "START : libGET6_custom_exits_register_callbacks" );

    iFail = CUSTOM_register_exit ( "libGET6_custom_exits", "USER_gs_shell_init_module", ( CUSTOM_EXIT_ftn_t ) GET_gsShellInitModule );	iFail = CUSTOM_register_exit ( "libGET6_custom_exits", "USER_new_revision_id", ( CUSTOM_EXIT_ftn_t ) GET6_generateRevID );

	LOG_TRACE ( logger, "END : libGET6_custom_exits_register_callbacks" );

	return iFail;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   G4O4_gsShellInitModule ( int *decision, va_list args )
 //
 //   Purpose :   User exit method for registering custom methods
 //
 //   Inputs  :   decision - The integer customization decision value
 //               args - The va_list structure containing the arguments
 //
 //   Outputs :   none
 //
 //   Return  :   ITK_ok (All the times)
 //
 //   History :
 //      Who                    Date                 Description
 //  TCS Development Team     01 Sep, 2017         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern int GET_gsShellInitModule ( int *decision, va_list args )
{
    LOG_TRACE ( logger, "START : GET_User_Exits::GET_gsShellInitModule" );

    *decision  = ALL_CUSTOMIZATIONS;

    // Register the custom handlers
    GET_registerMethods();

    LOG_TRACE ( logger, "END : GET_User_Exits::GET_gsShellInitModule" );

    return ITK_ok;
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   GET_registerMethods()
 //
 //   Purpose :   Function for registering custom methods
 //
 //   Inputs  :   none
 //
 //   Outputs :   none
 //
 //   Return  :   none
 //
 //   History :
 //      Who                    Date                 Description
 //  TCS Development Team     01 Sep, 2017         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
static void GET_registerMethods()
{
    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_User_Exits::GET_registerMethods" );

    try
    {
        METHOD_id_t  method;

        stat = METHOD__register_prop_operationFn ( ECNREVISION_TYPE, CAS_DOWNLOADER_URL_ATTR,
                                                   PROP_ask_value_string_msg, &GET6_get6CASDownloderURLGetValue, 0, &method );
    }
    catch ( IFail &ex )
    {
        string sErrorMessage = "Error occurred in GET_User_Exits::GET_registerMethods() method - " + ex.getMessage();
        LOG_ERROR ( logger, sErrorMessage );
        //LOG_EMH_ERROR_1 ( EMH_severity_user_error, ex.ifail(), sErrorMessage.c_str() );
    }

    LOG_TRACE ( logger, "END : GET_User_Exits::GET_registerMethods" ); 
}
