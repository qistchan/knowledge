/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_application_object.cxx
//
//    Purpose:   Class for dealing with GET_POM_application_object objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     31 Mar, 2016         Initial creation
//  TCS Development Team     21 Jul, 2016         Added deleteFromParent function implementation
//  TechM Development Team   20 May, 2017         Added deleteObject function
//  TCS Development Team     26 May, 2017         Modified getPropTag function
//  TCS Development Team     20 Sep, 2017         Added method for lock and unlock 
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_Utils.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_POM_application_object.hxx>
#include <GET_POM_user.hxx>
#include <GET_Site.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_TC_Attributes.hxx>

//Teamncenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <sa/am.h>
#include <tc/tc_errors.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_POM_application_object";

namespace get
{
    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   GET_POM_application_object
     //
     //    Purpose:   Constructor for the class GET_POM_application_object
     //
     //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
     //               tTag - The Tag of this Teamcenter Application Object
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_POM_application_object::GET_POM_application_object ( GET_DUMMY enDummy, tag_t tTag ) : GET_POM_object ( enDummy, tTag ) {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_POM_application_object
	 //
	 //    Purpose:   Destructor for the class GET_POM_application_object
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_POM_application_object::~GET_POM_application_object() {};

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getInstance (tTag)
	 //
	 //    Purpose:   Method to get the instance of this class using tag_t
	 //
	 //     Inputs:   tTag - tag of the object
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_POM_application_object Smart Pointer Instance for the given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_POM_application_objectUnqPtr GET_POM_application_object::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_POM_application_object::getInstance(tTag)\n" );

		if ( ! isDescendant ( tTag, POM_APPLICATION_OBJECT_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + POM_APPLICATION_OBJECT_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_POM_application_object::getInstance(tTag)\n" );

		return make_unique<GET_POM_application_object> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getInstance (sUID)
	 //
	 //    Purpose:   Method to get the instance of this class using string UID
	 //
	 //     Inputs:   sUID - UID as string
	 //
	 //    Outputs:   none
	 //
     //     Return:   The GET_POM_application_object Smart Pointer Instance for the given UID
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_POM_application_objectUnqPtr GET_POM_application_object::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_POM_application_object::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );

		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_POM_application_object::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   refreshObject
    //
    //   Purpose :   Method to refresh the object
    //
    //   Inputs  :   bIsLockRequired - A boolean indicating whether a lock is required *(optional, default is false)(const bool&)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::refreshObject ( const bool &bIsLockRequired )
    {
        LOG_TRACE ( logger, "START : GET_POM_application_object::refreshObject" );

        ResultCheck stat =  AOM_refresh ( _tag, ( bIsLockRequired ? TRUE : FALSE ) );

        LOG_TRACE ( logger, "END : GET_POM_application_object::refreshObject" );
    }

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   save()
	 //
	 //    Purpose:   Method to save the instance
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     31 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	void GET_POM_application_object::save()
	{
		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_application_object::save" );

		stat = AOM_save_with_extensions ( _tag );

		LOG_TRACE ( logger, "END : GET_POM_application_object::save - END" );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   lock()
	 //
	 //    Purpose:   Method to lock the instance
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     20 Junr, 2018         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	void GET_POM_application_object::lock()
	{
		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_application_object::lock" );

		stat = AOM_lock ( _tag );

		LOG_TRACE ( logger, "END : GET_POM_application_object::lock - END" );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   unlock()
	 //
	 //    Purpose:   Method to unlock the instance
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     20 Junr, 2018         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	void GET_POM_application_object::unlock()
	{
		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_application_object::unlock" );

		stat = AOM_unlock ( _tag );

		LOG_TRACE ( logger, "END : GET_POM_application_object::unlock - END" );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   setOwner
	 //
	 //    Purpose:   Method to set the owner
	 //
	 //     Inputs:   userPtr  - Smart Pointer for GET_POM_user object.
	 //               groupPtr - Smart Pointer for GET_POM_group object.
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     31 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	void GET_POM_application_object::setOwner ( const GET_POM_userShrPtr userPtr, GET_POM_groupShrPtr groupPtr, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
	{
	    IFail *exception = NULL;

		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_application_object::setOwner" );

		try
		{
            // Load the Object for Modification
            refreshObject ( true );

            // Set the Owner
		    stat = AOM_set_ownership ( _tag, userPtr->getTag(), groupPtr->getTag() );

		    // Save the Object, if required
		    if ( bIsSaveRequired )
		    {
		        save();
		    }
		}
		catch ( IFail &ex )
        {
            exception = &ex;
        }

		// Unlock the Object, if required
        if ( bIsUnlockRequired )
        {
            refreshObject();
        }

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

		LOG_TRACE ( logger, "END : GET_POM_application_object::setOwner" );
	}

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   deleteObject()
    //
    //   Purpose :   Method to delete this object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TehM Development Team     20 May, 2017        Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::deleteObject()
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::deleteObject" );

        stat = AOM_delete ( _tag );

        LOG_TRACE ( logger, "END : GET_POM_application_object::deleteObject" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   deleteFromParent ( const GET_POM_application_objectShrPtr parentShrPtr )
    //
    //   Purpose :   Method to remove relation between this object from given parent
    //
    //   Inputs  :   parentShrPtr - GET_POM_application_object smart pointer instance of the parent (GET_POM_application_objectShrPtr)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     21 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::deleteFromParent ( const GET_POM_application_objectShrPtr parentShrPtr )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::deleteFromParent" );

        stat = AOM_delete_from_parent ( _tag, parentShrPtr->getTag() );

        LOG_TRACE ( logger, "END : GET_POM_application_object::deleteFromParent" );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setPropValueAsString()
     //
     //    Purpose:   sets display value of the property
     //
     //     Inputs:   sPropName - Name of the property(string)
     //               sValue    - Value to set(string)
     //               bIsSaveRequired   - Is Save Required after setting Property *(optional, default is true)(const bool&)
     //               bIsUnlockRequired - Is unlock required for setting Property *(optional, default is true)(const bool&)
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     05 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_POM_application_object::setPropValueAsString ( const string sPropName, const string sPropValue, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "GET_POM_application_object::setPropValueAsString" );

        try
        {
            // Load the Object for Modification
            refreshObject ( true );

            // Set the Property Value
            stat = AOM_UIF_set_value ( _tag, sPropName.c_str(), sPropValue.c_str() );

            // Save the Object, if required
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Unlock the Object, if required
        if ( bIsUnlockRequired )
        {
            refreshObject();
        }

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_POM_application_objoect::setPropValueAsString" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setProp ( const string, const string, const bool&, const bool& )
    //
    //   Purpose :   Method to set value to a string Property for this object
    //
    //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
    //               sPropValue        - Property Value to be set (const string)
    //               bIsSaveRequired   - Is Save Required after setting Property *(optional, default is true)(const bool&)
    //               bIsUnlockRequired - Is unlock required for setting Property *(optional, default is true)(const bool&)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::setProp ( const string sPropName, const string sPropValue, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(string)" );

        try
        {
            // Load the Object for Modification
            refreshObject ( true );

            // Set the Property Value
            stat = AOM_set_value_string ( _tag, sPropName.c_str(), sPropValue.c_str() );

            // Set the Property Value
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Unlock the Object, if required
        if ( bIsUnlockRequired )
        {
            refreshObject();
        }

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(string)" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setProp ( const string, const vector<string>, const bool&, const bool& )
    //
    //   Purpose :   Method to set value to an array of string property for this object
    //
    //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
    //               vPropValues       - Vector of Property Values to be set (const vector<string>)
    //               bIsSaveRequired   - Is save Required after setting Property *(optional, default is true)(const bool&)
    //               bIsUnlockRequired - Is unlock required for setting Property *(optional, default is true)(const bool&)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::setProp ( const string sPropName, const vector<string> vPropValues, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
        char **ppcPropValues = NULL;

        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(strings)" );

        try
        {
            int iPropCount = vPropValues.size();

            GET_vectorToArray ( vPropValues, &ppcPropValues );

            // Load the Object for Modification
            refreshObject ( true );

            // Set the Property Value
            stat = AOM_set_value_strings ( _tag, sPropName.c_str(), iPropCount, ppcPropValues );

            // Save the Object, if required
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail &ex )
        {
           exception = &ex;
        }

        // Unlock the Object, if required
        if ( bIsUnlockRequired )
        {
            refreshObject();
        }

        // Free the Memory
        GET_free_array ( ( int ) vPropValues.size(), ( void** ) ppcPropValues );

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(strings)" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setProp ( const string, const int, const bool&, const bool& )
    //
    //   Purpose :   Method to set value to a int property for this object
    //
    //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
    //               iPropValue        - Property Value to be set (const int)
    //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
    //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::setProp ( const string sPropName, const int iPropValue, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(int)" );

        try
        {
            // Load the Object for Modification
            refreshObject ( true );

            // Set the Property Value
            stat = AOM_set_value_int ( _tag, sPropName.c_str(), iPropValue );

            // Save the Object, if required
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail &ex )
        {
             exception = &ex;
        }

        // Unlock the Object, if required
        if ( bIsUnlockRequired )
        {
             refreshObject();
        }

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
             throw exception;
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(int)" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setProp ( const string, const vetor<int>, const bool&, const bool& )
    //
    //   Purpose :   Method to set value to an array of int property for this object
    //
    //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
    //               vPropValues       - Vector of Property Values to be set (const vector<int>)
    //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
    //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::setProp ( const string sPropName, const vector<int> vPropValues, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        int *piPropValues = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(ints)" );

        try
        {
            int iPropCount = vPropValues.size();

            GET_vectorToArray ( vPropValues, &piPropValues );

            // Load the Object for Modification
            refreshObject ( true );

            // Set the Property Value
            stat = AOM_set_value_ints ( _tag, sPropName.c_str(), iPropCount, piPropValues );

            // Save the Object, if required
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Unlock the Object, if required
        if ( bIsUnlockRequired )
        {
            refreshObject();
        }

        // Free the Memory
        GET_free ( ( void* ) piPropValues );

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(ints)" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setProp ( const string, const double, const bool&, const bool& )
    //
    //   Purpose :   Method to set value to a double property for this object
    //
    //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
    //               dPropValue        - Property Value to be set (const double)
    //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
    //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::setProp ( const string sPropName, const double dPropValue, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(double)" );

        try
        {
            // Load the Object for Modification
            refreshObject ( true );

             // Set the Property Value
             stat = AOM_set_value_double ( _tag, sPropName.c_str(), dPropValue );

            // Save the Object, if required
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        if ( bIsUnlockRequired )
        {
            refreshObject();
        }

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(double)" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setProp ( const string, const vector<double>, const bool&, const bool& )
    //
    //   Purpose :   Method to set value to an array of double property for this object
    //
    //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
    //               vPropValues       - Vector of Property Values to be set (const vector<double>)
    //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
    //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     11 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_POM_application_object::setProp ( const string sPropName, const vector<double> vPropValues, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        double *pdPropValues = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(doubles)" );

        try
        {
            int iPropCount = vPropValues.size();

            GET_vectorToArray ( vPropValues, &pdPropValues );

            // Load the Object for Modification
            refreshObject ( true );

            // Set the Property Value
            stat = AOM_set_value_doubles ( _tag, sPropName.c_str(), iPropCount, pdPropValues );

            // Save the Object, if required
            if ( bIsSaveRequired )
            {
                save();
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Unlock the Object, if required
        if ( bIsUnlockRequired )
        {
            refreshObject();
        }

        // Free the Memory
        GET_free ( ( void* ) pdPropValues );

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(doubles)" );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setProp ( const string, const bool, const bool&, const bool& )
     //
     //   Purpose :   Method to set value to a logical property for this object
     //
     //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
     //               bPropValue        - Property Value to be set (const bool)
     //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
     //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //   TCS Development Team     11 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     void GET_POM_application_object::setProp ( const string sPropName, const bool bPropValue, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
     {
         IFail *exception = NULL;

         ResultCheck stat;

         LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(boolean)" );

         try
         {
             // Load the Object for Modification
             refreshObject ( true );

             // Set the Property Value
             stat = AOM_set_value_logical ( _tag, sPropName.c_str(), ( bPropValue == false ? FALSE : TRUE ) );

             // Save the Object, if required
             if ( bIsSaveRequired )
             {
                 save();
             }
          }
          catch ( IFail &ex )
          {
             exception = &ex;
          }

          // Unlock the Object, if required
          if ( bIsUnlockRequired )
          {
              refreshObject();
          }

          // Throw the exception if any, to the calling function
         if ( exception != NULL )
         {
             throw exception;
         }

         LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(boolean)" );
     }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setProp ( const string, const vector<bool>, const bool&, const bool& )
     //
     //   Purpose :   Method to set value to an array of logical property for this object
     //
     //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
     //               vPropValues       - Vector of Property Values to be set (const vector<bool>)
     //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
     //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //   TCS Development Team     11 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     void GET_POM_application_object::setProp ( const string sPropName, const vector<bool> vPropValues, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
     {
         IFail *exception = NULL;

         logical *plPropValues = NULL;

         ResultCheck stat;

         LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(booleans)" );

         try
         {
             int iPropCount = vPropValues.size();

             GET_vectorToArray ( vPropValues, &plPropValues );

             // Load the Object for Modification
             refreshObject ( true );

             // Set the Property Value
             stat = AOM_set_value_logicals ( _tag, sPropName.c_str(), iPropCount, plPropValues );

             // Save the Object, if required
             if ( bIsSaveRequired )
             {
                 save();
             }
         }
         catch ( IFail &ex )
         {
             exception = &ex;
         }

         // Unlock the Object, if required
         if ( bIsUnlockRequired )
         {
             refreshObject();
         }

         // Free the Memory
         GET_free ( ( void* ) plPropValues );

         // Throw the exception if any, to the calling function
         if ( exception != NULL )
         {
             throw exception;
         }

         LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(booleans)" );
     }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setProp ( const string, const GET_DateShrPtr, const bool&, const bool& )
     //
     //   Purpose :   Method to set value to a date property for this object
     //
     //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
     //               datePtrPropValue  - Property Value to be set (const GET_DateShrPtr)
     //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
     //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //   TCS Development Team     11 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     void GET_POM_application_object::setProp ( const string sPropName, const GET_DateShrPtr datePtrPropValue, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
     {
         IFail *exception = NULL;

         ResultCheck stat;

         LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(date)" );

         try
         {
             // Load the Object for Modification
             refreshObject ( true );

             // Set the Property Value
             stat = AOM_set_value_date ( _tag, sPropName.c_str(), datePtrPropValue->getDate() );

             // Save the Object, if required
             if ( bIsSaveRequired )
             {
                 save();
             }
          }
          catch ( IFail &ex )
          {
              exception = &ex;
          }

          // Unlock the Object, if required
          if ( bIsUnlockRequired )
          {
              refreshObject();
          }

          // Throw the exception if any, to the calling function
         if ( exception != NULL )
         {
             throw exception;
         }

         LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(date)" );
     }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setProp ( const string, const vector<GET_DateShrPtr>, const bool&, const bool& )
     //
     //   Purpose :   Method to set value to an array of logical property for this object
     //
     //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
     //               datePtrPropValues - Vector of Property Values to be set (const vector<GET_DateShrPtr>)
     //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
     //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //   TCS Development Team     11 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     void GET_POM_application_object::setProp ( const string sPropName, const vector<GET_DateShrPtr> vPropValues, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
     {
         IFail *exception = NULL;

         date_t *pdtPropValues = NULL;

         ResultCheck stat;

         LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(dates)" );

         try
         {
             int iPropCount = vPropValues.size();

             GET_vectorToArray ( vPropValues, &pdtPropValues );

             // Load the Object for Modification
             refreshObject ( true );

             // Set the Property Value
             stat = AOM_set_value_dates ( _tag, sPropName.c_str(), iPropCount, pdtPropValues );
             if ( bIsSaveRequired )
             {
                 save();
             }
          }
          catch ( IFail &ex )
          {
              exception = &ex;
          }

          // Unlock the Object, if required
          if ( bIsUnlockRequired )
          {
              refreshObject();
          }

         // Free the Memory
         GET_free ( ( void* ) pdtPropValues );

         // Throw the exception if any, to the calling function
         if ( exception != NULL )
         {
             throw exception;
         }

         LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(dates)" );
     }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setProp ( const string, const GET_POM_objectShrPtr, const bool&, const bool& )
     //
     //   Purpose :   Method to set value to a tag property for this object
     //
     //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
     //               ptrPropValue      - Property Value to be set (const GET_POM_objectShrPtr)
     //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
     //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //   TCS Development Team     11 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     void GET_POM_application_object::setProp ( const string sPropName, const GET_POM_objectShrPtr ptrPropValue, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
     {
         IFail *exception = NULL;

         ResultCheck stat;

         LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(tag)" );

         try
         {
             // Load the Object for Modification
             refreshObject ( true );

             // Set the Property Value
             stat = AOM_set_value_tag ( _tag, sPropName.c_str(), ptrPropValue->getTag() );

             // Save the Object, if required
             if ( bIsSaveRequired )
             {
                 save();
             }
         }
         catch ( IFail &ex )
         {
             exception = &ex;
         }

         // Unlock the Object, if required
         if ( bIsUnlockRequired )
         {
             refreshObject();
         }

         // Throw the exception if any, to the calling function
         if ( exception != NULL )
         {
             throw exception;
         }

         LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(tag)" );
     }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setProp ( const string, const vector<GET_POM_objectShrPtr>, const bool&, const bool& )
     //
     //   Purpose :   Method to set value to an array of tag property for this object
     //
     //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
     //               vPropValues       - Vector of Property Values to be set (const vector<GET_POM_objectShrPtr>)
     //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
     //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //   TCS Development Team     11 May, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
     void GET_POM_application_object::setProp ( const string sPropName, const vector<GET_POM_objectShrPtr> vPropValues, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
    {
         IFail *exception = NULL;

         ResultCheck stat;

         tag_t *ptPropValues = NULL;

         LOG_TRACE ( logger, "START : GET_POM_application_object::setProp(tags)" );

         try
         {
             int iPropCount = vPropValues.size();

             GET_vectorToArray ( vPropValues, &ptPropValues );

             // Load the Object for Modification
             refreshObject ( true );

             // Set the Property Value
             stat = AOM_set_value_tags ( _tag, sPropName.c_str(), iPropCount, ptPropValues );

             // Save the Object, if required
             if ( bIsSaveRequired )
             {
                 save();
             }
         }
         catch ( IFail &ex )
         {
             exception = &ex;
         }

         // Unlock the Object, if required
         if ( bIsUnlockRequired )
         {
             refreshObject();
         }

         // Free the Memory
         GET_free ( ( void* ) ptPropValues );

         // Throw the exception if any, to the calling function
         if ( exception != NULL )
         {
             throw exception;
         }

         LOG_TRACE ( logger, "END : GET_POM_application_object::setProp(tags)" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getOwningGroup ()
    //
    //    Purpose:   Method to get the owning group
    //
    //     Inputs:   none
    //
    //    Outputs:   none
    //
    //     Return:   none
    //
    //    History:
    //      Who                    Date                 Description
    //  TCS Development Team     31 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_POM_groupUnqPtr GET_POM_application_object::getOwningGroup()
    {
        ResultCheck stat;

        tag_t tGroupTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getOwningGroup" );

        stat = AOM_ask_group ( _tag, &tGroupTag );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getOwningGroup" );

        return make_unique<GET_POM_group> ( GET_DUMMY::GET_DUMMY_VALUE, tGroupTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getOwningUser ()
    //
    //    Purpose:   Method to get the owning user
    //
    //     Inputs:   none
    //
    //    Outputs:   none
    //
    //     Return:   GET_POM_userUnqPtr - Returns Smart Pointer for GET_POM_user.
    //
    //    History:
    //      Who                    Date                 Description
    //  TCS Development Team     31 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_POM_userUnqPtr GET_POM_application_object::getOwningUser()
    {
        ResultCheck stat;

        tag_t tOwnerTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getOwningUser" );

        stat = AOM_ask_owner ( _tag, &tOwnerTag );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getOwningUser" );

        return make_unique<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tOwnerTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getLastModifyingUser()
    //
    //    Purpose:   Method to get last modified user
    //
    //     Inputs:   none
    //
    //    Outputs:   none
    //
    //     Return:   GET_POM_userUnqPtr - Returns Smart Pointer for GET_POM_user.
    //
    //    History:
    //      Who                    Date                 Description
    //  TCS Development Team     31 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_POM_userUnqPtr GET_POM_application_object::getLastModifyingUser()
    {
        ResultCheck stat;

        tag_t tLastModifierTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getLastModifyingUser" );

        stat = AOM_ask_last_modifier ( _tag, &tLastModifierTag );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getLastModifyingUser" );

        return make_unique<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tLastModifierTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getOwningSiteName()
    //
    //    Purpose:   Method to get the owning site name.
    //
    //     Inputs:    none
    //
    //    Outputs:   none
    //
    //     Return:    string - Returns name of the owning site name
    //
    //    History:
    //      Who                    Date                 Description
    //  TCS Development Team     05 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string  GET_POM_application_object::getOwningSiteName()
    {
        GET_SiteUnqPtr sitePtr;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getOwningSiteName" );

        string sOwningSiteName = getPropString ( OWNING_SITE_ATTR );
        if ( sOwningSiteName.empty() )
        {
            int siteID = GET_Site::getLocalID();
            sitePtr = GET_Site::find ( siteID );
        }
        else
        {
            sitePtr = GET_Site::find ( sOwningSiteName );
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::getOwningSiteName" );

        return sitePtr->getName();
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getPropDisplayName()
     //
     //    Purpose:   Find display name of the property
     //
     //     Inputs:   sPropName - property name
     //
     //    Outputs:   none
     //
     //     Return:   string - Returns display name of the property
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     05 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_POM_application_object::getPropDisplayName ( const string sPropName ) const
    {
        char *pcDispName = NULL;

        ResultCheck stat;

        string sDispName = "";

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropDisplayName" );

        stat = AOM_UIF_ask_name ( _tag, sPropName.c_str(), &pcDispName );

        if ( pcDispName != NULL )
        {
        	sDispName = pcDispName;
        	MEM_free ( pcDispName );
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropDisplayName" );

        return sDispName;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getPropValueAsString()
     //
     //    Purpose:   Find display value of the property
     //
     //     Inputs:   sPropName - property name
     //
     //    Outputs:   none
     //
     //     Return:   string - Returns display value of the property
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     05 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_POM_application_object::getPropValueAsString ( const string sPropName ) const
    {
        char *pcDispVal = NULL;

        ResultCheck stat;

        string sDispVal = "";

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropValueAsString" );

        stat = AOM_UIF_ask_value ( _tag, sPropName.c_str(), &pcDispVal );
        if ( pcDispVal != NULL )
        {
        	sDispVal = pcDispVal;
        	MEM_free ( pcDispVal );
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropValueAsString" );

        return sDispVal;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropString ( const string )
    //
    //   Purpose :   Method to get string property value of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The string value for the given property of an object is returned(string)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string GET_POM_application_object::getPropString ( const string sPropName )
    {
        char *pcPropValue = NULL;

        string sPropValue = "";

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropString" );

        stat = AOM_ask_value_string ( _tag, sPropName.c_str(), &pcPropValue );

        if ( pcPropValue != NULL )
        {
        	sPropValue = pcPropValue;
        	MEM_free ( pcPropValue );
        }

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropString" );

        return sPropValue;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropStrings ( const string )
    //
    //   Purpose :   Method to get vector of string property values of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The vector of string values for given property of an object is returned (vector<string>)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<string> GET_POM_application_object::getPropStrings ( const string sPropName )
    {
        char **ppcPropValues = NULL;

        int iPropLength = 0;

        ResultCheck stat;

        vector<string> vPropValues;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropStrings" );

        stat = AOM_ask_value_strings ( _tag, sPropName.c_str(), &iPropLength, &ppcPropValues );

        GET_arrayToVector ( iPropLength, ( const char** ) ppcPropValues, vPropValues );

        // Free the Memory
        GET_free_tc_array ( iPropLength, ( void** ) ppcPropValues );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropStrings" );

        return vPropValues;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropInteger ( const string )
    //
    //   Purpose :   Method to get integer property value of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The int value for given property of an object is returned (int)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    int GET_POM_application_object::getPropInteger ( const string sPropName )
    {
        int iPropValue = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropInteger" );

        stat = AOM_ask_value_int ( _tag, sPropName.c_str(), &iPropValue );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropInteger" );

        return iPropValue;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropIntegers ( const string )
    //
    //   Purpose :   Method to get vector of integer property values of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The vector of integer values for given property of an object is returned (vector<int>)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<int> GET_POM_application_object::getPropIntegers ( const string sPropName )
    {
        int iPropLength = 0;

        int *piPropValues = NULL;

        ResultCheck stat;

        vector<int> vPropValues;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropIntegers" );

        stat = AOM_ask_value_ints ( _tag, sPropName.c_str(), &iPropLength, &piPropValues );

        GET_arrayToVector ( iPropLength, piPropValues, vPropValues );

        // Free the Memory
        GET_free_tc_array ( iPropLength, ( void** ) piPropValues );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropIntegers" );

        return vPropValues;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropDouble ( const string )
    //
    //   Purpose :   Method to get double property value of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The double value for given property of an object is returned (double)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    double GET_POM_application_object::getPropDouble ( const string sPropName )
    {
        double dPropValue = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropDouble" );

        stat = AOM_ask_value_double ( _tag, sPropName.c_str(), &dPropValue );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropDouble" );

        return dPropValue;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropDoubles ( const string )
    //
    //   Purpose :   Method to get vector of double property values of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The vector of double values for given property of an object is returned (vector<double>)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<double> GET_POM_application_object::getPropDoubles ( const string sPropName )
    {
        double *pdPropValues = NULL;

        int iPropLength = 0;

        ResultCheck stat;

        vector<double> vPropValues;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropDouble" );

        stat = AOM_ask_value_doubles ( _tag, sPropName.c_str(), &iPropLength, &pdPropValues );

        GET_arrayToVector ( iPropLength, pdPropValues, vPropValues );

        MEM_free( pdPropValues );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropDouble" );

        return vPropValues;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropLogical ( const string )
    //
    //   Purpose :   Method to get logical property value of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The bool value for given property of an object is returned (bool)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_POM_application_object::getPropLogical( const string sPropName )
    {
        logical lPropValue = FALSE;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropLogical" );

        stat = AOM_ask_value_logical (  _tag, sPropName.c_str(), &lPropValue );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropLogical" );

        return ( lPropValue == FALSE ? false: true );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropLogicals ( const string )
    //
    //   Purpose :   Method to get vector of logical property values of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The vector of  bool values for given property of an object is returned (bool)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<bool> GET_POM_application_object::getPropLogicals ( const string sPropName )
    {
        logical *plPropValues = NULL;

        int iPropLength = 0;

        ResultCheck stat;

        vector<bool> vPropValues;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropLogicals" );

        stat = AOM_ask_value_logicals ( _tag, sPropName.c_str(), &iPropLength, &plPropValues );

        GET_arrayToVector ( iPropLength, plPropValues, vPropValues );

        MEM_free( plPropValues );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropLogicals" );

        return vPropValues;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropDate ( const string )
    //
    //   Purpose :   Method to get date property value of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The Date object for given property of an object is returned (GET_DateUnqPtr)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DateUnqPtr GET_POM_application_object::getPropDate ( const string sPropName )
    {
        date_t dtPropValue = NULLDATE;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropLogical" );

        stat = AOM_ask_value_date ( _tag, sPropName.c_str(), &dtPropValue );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropLogical" );

        return GET_Date::getInstance ( dtPropValue );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropDates ( const string )
    //
    //   Purpose :   Method to get vector of date property values of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The vector of Date smart pointer for given property of an object is returned (vector<GET_DateUnqPtr>)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_DateUnqPtr> GET_POM_application_object::getPropDates ( const string sPropName )
    {
        date_t *pdtPropValues = NULL;

        int iPropLength = 0;

        ResultCheck stat;

        vector<GET_DateUnqPtr> vPropValues;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropLogicals" );

        stat = AOM_ask_value_dates ( _tag, sPropName.c_str(), &iPropLength, &pdtPropValues );

        GET_arrayToVector ( iPropLength, pdtPropValues, vPropValues );

        MEM_free ( pdtPropValues );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropLogicals" );

        return vPropValues;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropTag ( const string )
    //
    //   Purpose :   Method to get property tag of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The GET_POM_object smart pointer for given property is returned (GET_POM_objectUnqPtr)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_POM_objectUnqPtr GET_POM_application_object::getPropTag ( const string sPropName )
    {
    	GET_POM_objectUnqPtr pomObjectPtr;

        ResultCheck stat;

        tag_t tPropValue = NULLTAG;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropTag" );

        stat = AOM_ask_value_tag ( _tag, sPropName.c_str(), &tPropValue );

        if ( tPropValue != NULLTAG )
         {
             pomObjectPtr = make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tPropValue );
         }

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropTag" );

        return pomObjectPtr;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getPropTags ( const string )
    //
    //   Purpose :   Method to vector of get property tags of an object for the given property name
    //
    //   Inputs  :   sPropName - Property Name of the object (string)
    //
    //   Outputs :   none
    //
    //   Return  :   The vector of GET_POM_object smart pointer for given property is returned (vector<GET_POM_objectUnqPtr>)
    //
    //   History :
    //      Who                    Date                 Description
    //   TCS Development Team     2 May, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_POM_objectUnqPtr> GET_POM_application_object::getPropTags ( const string sPropName )
    {
        int iPropLength = 0;

        ResultCheck stat;

        tag_t *ptPropValues = NULL;

        vector<GET_POM_objectUnqPtr> vPropValues;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropTags" );

        stat = AOM_ask_value_tags ( _tag, sPropName.c_str(), &iPropLength, &ptPropValues );

        GET_arrayToVector ( iPropLength, ptPropValues, vPropValues );
        MEM_free ( ptPropValues );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropTags" );

        return vPropValues;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getPropTableRows ( const string sPropName )
     //
     //   Purpose :   Method to get the Table Property row objects
     //
     //   Inputs  :   sPropName - Table Property Name of the object (string)
     //
     //   Outputs :   none
     //
     //   Return  :   The vector of GET_POM_object smart pointer corresponding to the rows of the Table property is returned (vector<GET_POM_application_objectUnqPtr>)
     //
     //   History :
     //      Who                    Date                 Description
     //   TCS Development Team     8 Sep, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    vector<GET_POM_objectUnqPtr> GET_POM_application_object::getPropTableRows ( const string sPropName )
    {
        int iPropLength = 0;

        ResultCheck stat;

        tag_t *ptTablePropValues = NULL;

        vector<GET_POM_objectUnqPtr> vTablePropValues;

        LOG_TRACE ( logger, "START : GET_POM_application_object::getPropTableRows" );

        stat = AOM_ask_table_rows ( _tag, sPropName.c_str(), &iPropLength, &ptTablePropValues );
        GET_arrayToVector ( iPropLength, ptTablePropValues, vTablePropValues );
        MEM_free ( ptTablePropValues );

        LOG_TRACE ( logger, "END : GET_POM_application_object::getPropTableRows" );

        return vTablePropValues;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   appendTableRow()
     //
     //    Purpose:   To append the table row
     //
	 //     Inputs:   sTableRowPropName - Table property name
	 // 			  int - number to row to append
     //
     //    Outputs:   Table Row Business Object appended
     //
     //     Return:   vector<GET_POM_objectUnqPtr> - Returns the table rows appended.
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     20 June, 2018         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    vector<GET_POM_objectUnqPtr> GET_POM_application_object::appendTableRow ( const string sTableRowPropName, int iNoRows )
    {
    	IFail *exception = NULL;

    	int iTableRows = 0;

    	ResultCheck stat;

    	tag_t *tTableRows = NULL;

    	vector<GET_POM_objectUnqPtr> vTableRows;

    	LOG_TRACE ( logger, "START : GET_POM_object::appendTableRow" );

    	stat = AOM_append_table_rows ( _tag, sTableRowPropName.c_str(), iNoRows, &iTableRows, &tTableRows );

    	for ( int iRowIndex = 0; iRowIndex <= iTableRows; iRowIndex++ )
		{
			if ( tTableRows[iRowIndex]  != NULLTAG )
			{
				vTableRows.push_back ( make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tTableRows[iRowIndex] ) );
			}
		}

		MEM_free( tTableRows );

    	LOG_TRACE ( logger, "END : GET_POM_object::appendTableRow" );

    	return vTableRows;
    }

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   isPropModifiable()
	 //
	 //    Purpose:   sPropName - Name of the property(string)
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   boolean - Returns boolean value whether property is modifiable or not
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	bool GET_POM_application_object::isPropModifiable ( const string sPropName ) const
	{
		logical lModflag = FALSE;

		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_application_object::isModifiable" );

		stat = AOM_is_modifiable ( _tag, sPropName.c_str(), &lModflag );

		LOG_TRACE ( logger, "END : GET_POM_application_object::isModifiable" );

		return ( lModflag == TRUE ? true : false );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   askPropertyType()
	 //
	 //    Purpose:   Find the property type
	 //
	 //     Inputs:   sPropName - Name of the property(string)
	 //
	 //    Outputs:   none
	 //
	 //     Return:    PROP_type_t - Returns property type
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	PROP_type_t GET_POM_application_object::askPropertyType ( const string sPropName ) const
	{
		char *pcPropType = NULL;

		PROP_type_t pType;

		ResultCheck stat;

		LOG_TRACE( logger, "START : GET_POM_application_object::askPropertyType" );

		stat = AOM_ask_property_type ( _tag, sPropName.c_str(), &pType, &pcPropType );
		MEM_free ( pcPropType );

		LOG_TRACE ( logger, "END : GET_POM_application_object::askPropertyType" );

		return pType;
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   askPropValueType()
	 //
	 //    Purpose:   Find value type of the property
	 //
	 //    Inputs:    sPropName - Name of the property
	 //
	 //    Outputs:   none
	 //
	 //    Return:   PROP_value_type_t - returns property value type
	 //
	 // 	History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	PROP_value_type_t GET_POM_application_object::askPropValueType ( const string sPropName ) const
	{
		char *pcValType = NULL;

		PROP_value_type_t vType;

		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_application_object::askValueType" );

		stat = AOM_ask_value_type ( _tag, sPropName.c_str(), &vType, &pcValType );
		MEM_free ( pcValType );

		LOG_TRACE ( logger, "END : GET_POM_application_object::askValueType" );

		return vType;
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   isPropList()
	 //
	 //    Purpose:   sPropName - Name of the property(string)
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   boolean - Returns boolean value whether property is list or not
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	bool GET_POM_application_object::isPropList ( const string sPropName ) const
	{
		int iArrayFlag = 0;

		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_POM_application_object::isPropList" );

		stat = AOM_ask_max_num_elements  ( _tag, sPropName.c_str(), &iArrayFlag );

		LOG_TRACE ( logger, "END : GET_POM_application_object::isPropList" );

		return ( iArrayFlag == -1 ? true : false );
	}

	/*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   isNull()
    //
    //    Purpose:   Method to get the Property Value Type
    //
    //     Inputs:   sPropName - Name of the property whose value is to be checked
    //
    //    Outputs:   none
    //
    //     Return:   Returns true/false
    //
    //    History:
    //      Who                   Date                 Description
    //  TCS Development Team     03 Nov, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_POM_application_object::isNull ( const string sPropName, bool bCheckZeroLength ) const
    {
        logical isNullEmpty;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::isNullEmpty" );

        stat = AOM_is_null_empty ( _tag, sPropName.c_str(), ( bCheckZeroLength ? TRUE : FALSE ), &isNullEmpty );

        LOG_TRACE ( logger, "END : GET_POM_application_object::isNullEmpty" );

        return ( isNullEmpty ? true : false );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   numElements()
    //
    //    Purpose:   Method to get the number of elements
    //
    //     Inputs:   sPropName - Name of the property for which number of elements are to be returned
    //
    //    Outputs:   none
    //
    //     Return:   Returns true/false
    //
    //    History:
    //      Who                   Date                 Description
    //  TCS Development Team     15 Nov, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    int GET_POM_application_object::numElements ( const string sPropName ) const
    {
        int numElements = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_POM_application_object::numElements" );

        stat = AOM_ask_num_elements ( _tag, sPropName.c_str(), &numElements );

        LOG_TRACE ( logger, "END : GET_POM_application_object::numElements" );

        return numElements;
    }
}
