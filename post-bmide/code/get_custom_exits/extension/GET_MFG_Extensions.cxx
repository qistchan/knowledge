
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_MFG_Extensions.cxx
 //
 //    Purpose:   Source file for Manufacturing extensions
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     31 May, 2017         Initial creation
 //  TCS Development Team     31 May, 2017         Extension to validate UOM for Stock Material
 //  TCS Development Team     21 Jun, 2017         Extension to check User project is selected during 
 //                                                Save As operation
 //  TCS Development team     02 Aug, 2017         Extension Method added to trigger propagation rules
 //   ============================================================================
 // ENDFILEDOC   ***/

// GET Includes
#include <GET_MFG_Extensions.hxx>
#include <GET_Constants.hxx>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_GroupMember.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_Item.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_POM_application_object.hxx>
#include <GET_POM_group.hxx>
#include <GET_POM_user.hxx>
#include <GET_UserSession.hxx>
#include <GET_Preferences.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>

#include <GET_TC_Project.hxx>

// Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <tc/tc_arguments.h>
#include <ug_va_copy.h>
#include <metaframework/CreateInput.hxx>

#include <vector>

void getUOMValidationMsg ( GET_ItemShrPtr itemShrPtr );
using namespace get;
using namespace Teamcenter; // For accessing Teamcenter C++ Objects

const string logger = "get.extension.GET_MFG_Extensions";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  getUOMValidationMsg
//
//    Purpose:  Extension Method added on Post Action of Stock Mtrl Item Create and Pre-Condition on IMAN_SAVE
//
//    Inputs:   msg - The Message input from the handler
//              vaArgs - The Variable Argument List input for this Extension Method
//
//    Outputs:  none
//
//    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
//
//    History:
//      Who                           Date                 Description
//  TCS Development team          31 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void getUOMValidationMsg ( GET_ItemShrPtr itemShrPtr )
{
	string sErrorMessage;
	vector <string> vPrefValues;
	vector <string> vUOMValues;

	LOG_TRACE ( logger, "START : getUOMValidationMsg" );

	//Get the invalid list of UOM from preference.
	getStringPrefValues ( GET_STOCKMTRL_INVALID_UOM_VALUES, vPrefValues );
	if ( ! vPrefValues.empty() )
	{
		GET_splitString ( vPrefValues[0], ",", vUOMValues );
	}
	else
	{
		string sError = string ( GET_STOCKMTRL_INVALID_UOM_VALUES ) + string ( " preference is empty, Please contact system administrator" );
		THROW ( sError );
	}
	vPrefValues.clear ();

	// Retreive the attribute values
	string sUOMValue = itemShrPtr->getPropValueAsString ( UOM_ATTR );

	// Check for invalid uom values for Stock Material.
	if ( GET_isInVector ( vUOMValues, sUOMValue ) )
	{
		sErrorMessage = string ("UOM " + sUOMValue +" is Invalid for Stock Material Item. Please select the correct value.");
		THROW ( sErrorMessage );
	}

	LOG_TRACE ( logger, "END : getUOMValidationMsg" );

}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET6_validateStockMtrlUOMCreate
//
//    Purpose:  Extension Method added on Post Action of Stock Mtrl Item Create and Pre-Condition on IMAN_SAVE
//
//    Inputs:   msg - The Message input from the handler
//              vaArgs - The Variable Argument List input for this Extension Method
//
//    Outputs:  none
//
//    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
//
//    History:
//      Who                           Date                 Description
//  TCS Development team          31 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_validateStockMtrlUOMCreate ( METHOD_message_t* msg, va_list args )
{
	char* pcItemID = NULL;
	char* pcItemName = NULL;
	char* pcTypeName = NULL;
	char* pcRevID = NULL;

	int iFail = ITK_ok;

	tag_t* tNewitem = NULL;
	tag_t* tNewrev = NULL;
	tag_t tItemtag = NULLTAG;
	tag_t tRevtag = NULLTAG;

	//Get the parameters from the ITEM_create_msg
	va_list largs;
	va_copy(largs, args);
	pcItemID = va_arg( largs, char *);
	pcItemName = va_arg(largs, char *);
	pcTypeName = va_arg(largs, char *);
	pcRevID = va_arg(largs, char *);
	tNewitem = va_arg(largs, tag_t *);
	tNewrev = va_arg(largs, tag_t *);
	tItemtag = *tNewitem;
	tRevtag = *tNewrev;
	va_end(largs);

	LOG_TRACE ( logger, "START : GET6_validateStockMtrlUOMCreate" );

	try
	{
		// Get the Item pointer form the tObject.
		GET_ItemUnqPtr itemUnqPtr = GET_Item::getInstance ( tItemtag );
		GET_ItemShrPtr itemShrPtr ( move ( itemUnqPtr ) );

		//Calling method to validation Stock Material UOM
		getUOMValidationMsg ( itemShrPtr );
	}
	catch ( const IFail &ex )
	{
		iFail = ex.ifail();
		LOG_ERROR ( logger, ex.getMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
	}
	catch ( GET_Exception *ex )
	{
		iFail = GET_general_exception;
		LOG_ERROR ( logger, ex->getErrorMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
		delete ex;
	}
	catch ( ... )
	{
		iFail = GET_general_exception;
		string sErrorMessage = "An unexpected error occurred in the GET6_validateOverallUOM function. Please contact your System Administrator";
		LOG_ERROR ( logger, sErrorMessage );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
	}
	LOG_TRACE ( logger, "END : GET6_validateStockMtrlUOMCreate" );

	return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET6_validateStockMtrlUOMSave
//
//    Purpose:  Extension Method added on Pre-Condition IMAN_SAVE
//
//    Inputs:   msg - The Message input from the handler
//              vaArgs - The Variable Argument List input for this Extension Method
//
//    Outputs:  none
//
//    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
//
//    History:
//      Who                           Date                 Description
//  TCS Development team          31 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_validateStockMtrlUOMSave ( METHOD_message_t* msg, va_list args )
{
	int iFail = ITK_ok;

	//Get the parameters from the IMAN_SAVE
	tag_t tItemTag  = va_arg (args, tag_t);

	LOG_TRACE ( logger, "START : GET6_validateStockMtrlUOMSave" );

	try
	{
		// Get the Item pointer form the tObject.
		GET_ItemUnqPtr itemUnqPtr = GET_Item::getInstance ( tItemTag );
		GET_ItemShrPtr itemShrPtr ( move ( itemUnqPtr ) );

		//Calling method to validation Stock Material UOM
		getUOMValidationMsg ( itemShrPtr );
    }
	catch ( const IFail &ex )
	{
		iFail = ex.ifail();
		LOG_ERROR ( logger, ex.getMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
	}
	catch ( GET_Exception *ex )
	{
		iFail = GET_general_exception;
		LOG_ERROR ( logger, ex->getErrorMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
		delete ex;
	}
	catch ( ... )
	{
		iFail = GET_general_exception;
		string sErrorMessage = "An unexpected error occurred in the GET6_validateOverallUOM function. Please contact your System Administrator";
		LOG_ERROR ( logger, sErrorMessage );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
	}
	LOG_TRACE ( logger, "END : GET6_validateStockMtrlUOMSave" );

	return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET6_checkProjectContext
//
//    Purpose:  Extension Method added on Pre-Condition ITEM_Create_Rev
//
//    Inputs:   msg - The Message input from the handler
//              vaArgs - The Variable Argument List input for this Extension Method
//
//    Outputs:  none
//
//    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
//
//    History:
//      Who                           Date                 Description
//  TCS Development team          21 June, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_checkProjectContext ( METHOD_message_t* msg, va_list args )
{
	int iFail = ITK_ok;

	char  *new_item_id  = va_arg (args, char*);         /* args  */
    char  *new_rev_id  = va_arg (args, char*);          /* args  */
    char  *new_name  = va_arg (args, char*);            /* args  */
    char  *new_description  = va_arg (args, char*);     /* args  */

    tag_t old_item  = va_arg (args, tag_t);             /* args  */
    tag_t old_rev  = va_arg (args, tag_t);              /* args  */
    tag_t *new_item  = va_arg (args, tag_t*);           /* args  */
    tag_t *new_rev  = va_arg (args, tag_t*);            /* args  */
    tag_t item_master_form  = va_arg (args, tag_t);     /* args  */
    tag_t item_rev_master_form  = va_arg (args, tag_t); /* args  */

	LOG_TRACE ( logger, "START : GET6_checkProjectContext" );

	try
	{
		GET_UserSessionUnqPtr userSessionUnqPtr = GET_UserSession::getCurrentUserSession();
		GET_TC_ProjectShrPtr projTagShrPtr = userSessionUnqPtr->getProject();

		if ( projTagShrPtr == NULL )
		{
			THROW ( "The Project context is blank. Please change the Project context using the User Settings command." );
		}
    }
	catch ( const IFail &ex )
	{
		iFail = ex.ifail();
		LOG_ERROR ( logger, ex.getMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
	}
	catch ( GET_Exception *ex )
	{
		iFail = GET_general_exception;
		LOG_ERROR ( logger, ex->getErrorMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
		delete ex;
	}
	catch ( ... )
	{
		iFail = GET_general_exception;
		string sErrorMessage = "An unexpected error occurred in the GET6_checkProjectContext function. Please contact your System Administrator";
		LOG_ERROR ( logger, sErrorMessage );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
	}
	LOG_TRACE ( logger, "END : GET6_checkProjectContext" );

	return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:  GET6_bvrPostActionForCreatePost
//
//    Purpose:  Extension Method added on Post-Action CreatePost of BVR
//
//    Inputs:   msg - The Message input from the handler
//              vaArgs - The Variable Argument List input for this Extension Method
//
//    Outputs:  none
//
//    Return:   An Integer error code. 0 indicates no-error, non-zero indicates Some Teamcenter Errors
//
//    History:
//      Who                           Date                 Description
//  TCS Development team          02 Aug, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern DLLEXPORT int GET6_bvrPostActionForCreatePost ( METHOD_message_t* msg, va_list args )
{
	int iFail = ITK_ok;

	va_list largs;
    va_copy ( largs, args );
    Teamcenter::CreateInput *creInput = va_arg ( largs, Teamcenter::CreateInput* );
    va_end ( largs );

    vector<string> vPrefValues;

	LOG_TRACE ( logger, "START : GET6_bvrPostActionForCreatePost" );

	try
	{
	    getStringPrefValues ( GET_PROJECT_PROPAGATION_INCLUSION_LIST, vPrefValues );
		if ( vPrefValues.empty() )
		{
		    string sError = string ( GET_PROJECT_PROPAGATION_INCLUSION_LIST ) + string ( " preference is empty, Please contact system administrator" );
			THROW ( sError );
		}

		GET_BOMViewRevisionUnqPtr bvrUnqPtr = GET_BOMViewRevision::getInstance ( msg->object_tag );
		GET_ItemUnqPtr itemUnqPtr = bvrUnqPtr->getBomView()->getItem();

		if ( GET_isInVector ( vPrefValues, itemUnqPtr->getType() ) )
		{
		    string sDescription = itemUnqPtr->getPropString ( OBJECT_DESC_ATTR );

		    itemUnqPtr->checkout ( EMPTY_CHARACTER );

		    itemUnqPtr->setProp ( OBJECT_DESC_ATTR, sDescription, false, false );

		    bvrUnqPtr->save();

		    itemUnqPtr->checkin();
        }
	}
	catch ( const IFail &ex )
	{
		iFail = ex.ifail();
		LOG_ERROR ( logger, ex.getMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex.getMessage().c_str() );
	}
	catch ( GET_Exception *ex )
	{
		iFail = GET_general_exception;
		LOG_ERROR ( logger, ex->getErrorMessage() );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, ex->getErrorMessage().c_str() );
		delete ex;
	}
	catch ( ... )
	{
		iFail = GET_general_exception;
		string sErrorMessage = "An unexpected error occurred in the GET6_bvrPostActionForCreatePost function. Please contact your System Administrator";
		LOG_ERROR ( logger, sErrorMessage );
		LOG_EMH_ERROR_1 ( EMH_severity_user_error, iFail, sErrorMessage.c_str() );
	}

	LOG_TRACE ( logger, "END : GET6_bvrPostActionForCreatePost" );

	return iFail;
}
