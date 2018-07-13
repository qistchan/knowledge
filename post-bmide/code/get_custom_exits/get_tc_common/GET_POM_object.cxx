
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_object.cxx
//
//    Purpose:   Class for dealing with the pom_object class
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016          Initial creation
//  TCS Development Team     03 Mar, 2017          Modified method to make as instance method for returning the type name
//  TCS Development Team     08 May, 2017          Commented the code to save the instance after creation in the createInstance() method
//  TCS Development Team     09 May, 2017          Added a new Parameter (bIsLockRequired) for all the setProperty() methods
//                                                 for controlling instance locking before attempting to set the attribute value
//  TCS Development Team     19 May, 2017          Added method definition getAllInstances for retrieving all instances of a given class
//  TCS Development Team     26 May, 2017          Added method for POM_compare_dates
//  TCS Development Team     27 Jun, 2017          Removed method for POM_compare_dates
//  TCS Development Team     11 Sep, 2017          Added a new method askTypeDisplayName for retrieving the Display name of the object's type
//  Ganesh Ubale             11 Sep  2017          Added method getPropertyDisplayName for retrieving the Display name of the object's properties
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_AM_PRIVS.hxx>
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_POM_object.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <pom/pom/pom.h>
#include <sa/am.h>
#include <tccore/aom.h>
#include <tccore/aom_prop.h>
#include <tccore/tctype.h>
#include <lov/lov.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_POM_object";

using namespace get;

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET_POM_object ()
//
//   Purpose :   Constructor Method for GET_POM_Object
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
GET_POM_object::GET_POM_object ( const GET_DUMMY enDummy, const tag_t tTag )
{
    LOG_TRACE ( logger, "START : GET_POM_object::GET_POM_object(tag_t)" );

    init ( tTag );

    LOG_TRACE ( logger, "END : GET_POM_object::GET_POM_object(tag_t)" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getTagFromUID ( const string )
//
//   Purpose :   Method to convert UID to tag
//
//   Inputs  :   sUID - Persistent unique identifier of the object for which tag need to created(string)
//
//   Outputs :   none
//
//   Return  :   Created object tag is returned (tag_t)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
tag_t GET_POM_object::getTagFromUID ( const string sUID )
{
    ResultCheck stat;

    tag_t tObjectTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::getTagFromUID()" );

    stat = POM_string_to_tag ( sUID.c_str(), &tObjectTag );

    LOG_TRACE ( logger, "END : GET_POM_object::getTagFromUID()" );

    return tObjectTag;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getUID ( const string )
//
//   Purpose :   Method to convert UID to tag
//
//   Inputs  :   None
//
//   Outputs :   none
//
//   Return  :   uid (string)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     8 Nov, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
string GET_POM_object::getUID ( )
{
    ResultCheck stat;

    char *sUid = NULL;

    string sObjUid;

    LOG_TRACE ( logger, "START : GET_POM_object::getUID()" );

    stat = POM_tag_to_uid ( _tag, &sUid );
    sObjUid = sUid;
    MEM_free ( sUid );

    LOG_TRACE ( logger, "END : GET_POM_object::getUID()" );

    return sObjUid;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   createInstance ( const string )
//
//   Purpose :   Method to create class instance for the given class Name
//
//   Inputs  :   sClassName - Class Name of the object (string)
//
//   Outputs :   none
//
//   Return  :   Created POM object is returned (GET_POM_objectUnqPtr)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//   TCS Development Team     8 May, 2017         Commented the code to save the instance after creation
//
===========================================================================
//ENDFUNCDOC   ***/
GET_POM_objectUnqPtr GET_POM_object::createInstance ( const string sClassName )
{
    GET_POM_objectUnqPtr newObjectPtr;

    ResultCheck stat;

    tag_t tClassID = NULLTAG;
    tag_t tInstanceTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::createInstance" );

    stat = POM_class_id_of_class ( sClassName.c_str(), &tClassID );
    if ( tClassID == NULLTAG )
    {
        THROW ( sClassName + " is not a valid Teamcenter Class" );
    }
    stat = POM_create_instance ( tClassID, &tInstanceTag );
    newObjectPtr = make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tInstanceTag );
    //newObjectPtr->saveInstance();

    LOG_TRACE ( logger, "END : GET_POM_object::createInstance" );

    return newObjectPtr;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getInstance ( const tag_t )
//
//   Purpose :   Method to get the instance of this class using tag_t
//
//   Inputs  :   tTag - tag of the POM_object(tag_t)
//
//   Outputs :   none
//
//   Return  :   The GET_POM_object Smart Pointer object is returned(GET_POM_objectUnqPtr)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
GET_POM_objectUnqPtr GET_POM_object::getInstance ( const tag_t tTag )
{
    LOG_TRACE ( logger, "START : GET_POM_object::getInstance(tTag)" );

    if ( ! isDescendant ( tTag, POM_OBJECT_CLASS ) )
    {
        string sMsg = string ( "The given tag is not an instance of the class " ) + POM_OBJECT_CLASS;
        THROW ( sMsg );
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getInstance(tTag)" );

    return make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getInstance ( const string )
//
//   Purpose :   Method to get the instance of this class using string UID
//
//   Inputs  :   sUID - UID as string(string)
//
//   Outputs :   none
//
//   Return  :   The GET_POM_object Smart Pointer object is returned(GET_POM_objectUnqPtr)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
GET_POM_objectUnqPtr GET_POM_object::getInstance ( const string sUID )
{
    LOG_TRACE ( logger, "START : GET_POM_object::getInstance(sUID)" );

    tag_t tObjectTag = getTagFromUID ( sUID );

    if ( tObjectTag == NULLTAG )
    {
        THROW ( sUID + " is not a valid Teamcenter UID" );
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getInstance(sUID)" );

    return getInstance ( tObjectTag );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET_POM_object()
//
//   Purpose :   Destructor for the class
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
GET_POM_object::~GET_POM_object()
{
    // Make every possible attempt to unlock the object in-case if its left locked
    if ( bIsLocked )
    {
        // Do not throw any exceptions here. Handle it within this function itself
        try
        {
            loadInstance();
            bIsLocked = false;
        }
        catch ( const IFail &ex )
        {
            cout<<endl<<ex.getMessage().c_str()<<endl;
        }
    }
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   init ( const tag_t )
//
//   Purpose :   Instance Initialization method for the class
//
//   Inputs  :   tTag - Tag of the instance(tag_t)
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::init ( const tag_t tTag )
{
    LOG_TRACE ( logger, "START : GET_POM_object::init" );

    _tag = tTag;
    bIsLocked = false;

    // Ensure instance is loaded
    if ( ! isLoaded() )
    {
        loadInstance();
    }

    LOG_TRACE ( logger, "END : GET_POM_object::init" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getTag()
//
//   Purpose :   Getter Method for tag
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   tTag - Tag of the instance(tag_t)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
tag_t GET_POM_object::getTag() const
{
    return _tag;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getClassName()
//
//   Purpose :   Method to get the class name of this instance
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   Class name of the instance is returned(string)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
string GET_POM_object::getClassName() const
{
    char *pcClassName = NULL;

    ResultCheck stat;

    string sClassName = "";

    tag_t tClassID = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::getClassName" );

    stat = POM_class_of_instance ( _tag, &tClassID );
    stat = POM_name_of_class ( tClassID, &pcClassName );

    if ( pcClassName != NULL )
    {
        sClassName = pcClassName;
        MEM_free ( pcClassName );
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getClassName" );

    return sClassName;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   isLoaded()
//
//   Purpose :   Method to identify whether instance is loaded
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   True/false is returned if instance is loaded(bool)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
bool GET_POM_object::isLoaded()
{
    logical lIsLoaded = false;

    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::isLoaded" );

    stat = POM_is_loaded ( _tag, &lIsLoaded );

    LOG_TRACE ( logger, "END : GET_POM_object::isLoaded" );

    return ( lIsLoaded == TRUE ? true : false );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   loadInstance()
//
//   Purpose :   Method to load instance
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::loadInstance()
{
    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::loadInstance" );

    stat = POM_load_instances ( 1, &_tag, NULLTAG, POM_no_lock );
    bIsLocked = false;

    LOG_TRACE ( logger, "END : GET_POM_object::loadInstance" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   unloadInstance()
//
//   Purpose :   Method to unload instance
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::unloadInstance()
{
    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::unloadInstance" );

    stat = POM_unload_instances ( 1, &_tag );

    LOG_TRACE ( logger, "END : GET_POM_object::unloadInstance" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   lockInstanceForModification()
//
//   Purpose :   Method to lock instance for any modification on the object
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::lockInstanceForModification()
{
    LOG_TRACE ( logger, "START : GET_POM_object::lockInstanceForModification" );

    if ( ! bIsLocked )
    {
        ResultCheck stat;

        stat = POM_refresh_instances ( 1, &_tag, NULLTAG, POM_modify_lock );
        bIsLocked = true;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::lockInstanceForModification" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   refresh ()
//
//   Purpose :   Method to lock instance for any modification on the object
//
//   Inputs  :   Lock Type (int) -  (POM_no_lock/POM_read_lock/POM_modify_lock)
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     8 Nov, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::refresh ( int iLockType )
{
    LOG_TRACE ( logger, "START : GET_POM_object::refresh" );

    ResultCheck stat;

    stat = POM_refresh_instances ( 1, &_tag, NULLTAG, iLockType );
    if ( iLockType == POM_modify_lock )
    {
        bIsLocked = true;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::refresh" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   saveInstance()
//
//   Purpose :   Method to save instance after any modification happened
//
//   Inputs  :   bIsUnloadRequired - Flag to indicate if unload instance is required post save *(optional, default is true)(const bool&)
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::saveInstance ( const bool &bIsUnloadRequired )
{
    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::saveInstance" );

    stat = POM_save_instances ( 1, &_tag, ( bIsUnloadRequired == true ? TRUE : FALSE ) );

    LOG_TRACE ( logger, "END : GET_POM_object::saveInstance" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   deleteInstance()
//
//   Purpose :   Method to delete instance from Teamcenter
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::deleteInstance()
{
    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::deleteInstance" );

    stat = POM_delete_instances ( 1, &_tag );

    LOG_TRACE ( logger, "END : GET_POM_object::deleteInstance" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   checkUserPrivilege()
//
//   Purpose :   Method to Check the AM privilege of object (READ, WRITE, DELETE, CHANGE, PROMOTE, DEMOTE,
//               COPY, IMPORT, EXPORT, TRANSFER_IN and TRANSFER_OUT)
//
//   Inputs  :  userObj - User whose privilege is to be checked
//              sPrivilegeName - specific privilege to be checked
//
//   Outputs :   none
//
//   Return  :   verdict (true/false) access for the given object present
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     10 Aug, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
bool GET_POM_object::checkUserPrivilege ( GET_POM_objectShrPtr userObj, const string sPrivilegeName )
{
    logical lVerdict = FALSE;

    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::checkUserPrivilege" );

    stat = AM_check_users_privilege ( userObj->getTag(), _tag, sPrivilegeName.c_str(), &lVerdict );

    LOG_TRACE ( logger, "END : GET_POM_object::checkUserPrivilege" );

    return ( lVerdict == FALSE ? false : true );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   isDescendant ( const tag_t, const string )
//
//   Purpose :   Method to find if one class is anywhere in the class structure below another class
//
//   Inputs  :   tTag            - Tag of the object
//               sSuperClassName - Class Name of the object
//
//   Outputs :   none
//
//   Return  :   verdict (true/false) access for the given object present
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
bool GET_POM_object::isDescendant ( const tag_t tTag, const string sSuperClassName )
{
    logical lVerdict = FALSE;

    ResultCheck stat;

    tag_t tSuperClassId = NULLTAG;
    tag_t tThisClassId = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::isDescendant" );


    stat = POM_class_id_of_class ( sSuperClassName.c_str(), &tSuperClassId );
    if ( tSuperClassId == NULLTAG )
    {
        THROW ( sSuperClassName + " is not a valid Teamcenter class" );
    }
    stat = POM_class_of_instance ( tTag, &tThisClassId );
    stat = POM_is_descendant ( tSuperClassId, tThisClassId, &lVerdict );

    LOG_TRACE ( logger, "END : GET_POM_object::isDescendant" );

    return ( lVerdict == FALSE ? false : true );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   checkPrivilege()
//
//   Purpose :   Method to Check the AM privilege of object (READ, WRITE, DELETE, CHANGE, PROMOTE, DEMOTE,
//               COPY, IMPORT, EXPORT, TRANSFER_IN and TRANSFER_OUT)
//
//   Inputs  :   tTag - Tag of object
//               sPrivilegeName - specific privilege
//
//   Outputs :   none
//
//   Return  :   verdict (true/false) access for the given object present
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     2 May, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
bool GET_POM_object::checkPrivilege ( const tag_t tTag, const string sPrivilegeName )
{
    logical lVerdict = FALSE;

    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::checkPrivilege" );

    stat = AM_check_privilege ( tTag, sPrivilegeName.c_str(), &lVerdict );

    LOG_TRACE ( logger, "END : GET_POM_object::checkPrivilege" );

    return ( lVerdict == FALSE ? false : true );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   setProperty ( const string, const string, const bool&, const bool& )
//
//   Purpose :   Method to set value to a string Property for this object
//
//   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
//               sPropValue        - Property Value to be set (const string)
//               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
//   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_POM_object::setProperty ( const string sPropName, const string sPropValue, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
{
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(string)" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }

    try
    {
        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the Property Value
        stat = POM_set_attr_string ( 1, &_tag, tAttrTag, sPropValue.c_str() );

        // Save the Instance, if required
        if ( bIsSaveRequired )
        {
             saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(string)" );
}

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const vector<string>, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to an array of string property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               vPropValues       - Vector of Property Values to be set (const vector<string>)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const vector<string> vPropValues, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
     char **ppcPropValues = NULL;

     IFail *exception = NULL;

     ResultCheck stat;

     tag_t tAttrTag = NULLTAG;

     LOG_TRACE ( logger, "START : GET_POM_object::setProperty(strings)" );

     try
     {
         int iPropCount = vPropValues.size();

         stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
         if ( tAttrTag == NULLTAG )
         {
             THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
         }

         GET_vectorToArray ( vPropValues, &ppcPropValues );

         // Lock the Instance, if not already done
         if ( bIsLockRequired )
         {
             lockInstanceForModification();
         }

         // Set the Property Value
         stat = POM_set_attr_strings ( 1, &_tag, tAttrTag, 0, iPropCount, ppcPropValues );

         // Save the Instance, if required
         if ( bIsSaveRequired )
         {
             saveInstance();
         }
     }
     catch ( IFail &ex )
     {
         exception = &ex;
     }

     // Free the Memory
     GET_free_array ( ( int ) vPropValues.size(), ( void** ) ppcPropValues );

     // Unlock the Instance, if required
     if ( bIsUnlockRequired )
     {
         loadInstance();
     }

     // Throw the exception if any, to the calling function
     if ( exception != NULL )
     {
         throw exception;
     }

     LOG_TRACE ( logger, "END : GET_POM_object::setProperty(strings)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const int, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to a int property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               iPropValue        - Property Value to be set (const int)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const int iPropValue, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
     IFail *exception = NULL;

     ResultCheck stat;

     tag_t tAttrTag = NULLTAG;

     LOG_TRACE ( logger, "START : GET_POM_object::setProperty(int)" );

     stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
     if ( tAttrTag == NULLTAG )
     {
         THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
     }

     try
     {
         // Lock the Instance, if not already done
         if ( bIsLockRequired )
         {
             lockInstanceForModification();
         }

         // Set the Property Value
         stat = POM_set_attr_int ( 1, &_tag, tAttrTag, iPropValue );

         // Save the Instance, if required
         if ( bIsSaveRequired )
         {
             saveInstance();
         }
     }
     catch ( IFail &ex )
     {
         exception = &ex;
     }

     // Unlock the Instance, if required
     if ( bIsUnlockRequired )
     {
         loadInstance();
     }

     // Throw the exception if any, to the calling function
     if ( exception != NULL )
     {
         throw exception;
     }

     LOG_TRACE ( logger, "END : GET_POM_object::setProperty(int)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const vetor<int>, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to an array of int property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               vPropValues       - Vector of Property Values to be set (const vector<int>)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const vector<int> vPropValues, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
     IFail *exception = NULL;

     int *piPropValues = NULL;

     ResultCheck stat;

     tag_t tAttrTag = NULLTAG;

     LOG_TRACE ( logger, "START : GET_POM_object::setProperty(ints)" );

     try
     {
         int iPropCount = vPropValues.size();

         stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
         if ( tAttrTag == NULLTAG )
         {
             THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
         }

         GET_vectorToArray ( vPropValues, &piPropValues );

         // Lock the Instance, if not already done
         if ( bIsLockRequired )
         {
             lockInstanceForModification();
         }

         // Set the Property Value
         stat = POM_set_attr_ints ( 1, &_tag, tAttrTag, 0, iPropCount, piPropValues );

         // Save the Instance, if required
         if ( bIsSaveRequired )
         {
             saveInstance();
         }
     }
     catch ( IFail &ex )
     {
         exception = &ex;
     }

     // Free the Memory
     GET_free ( ( void* ) piPropValues );

     // Unlock the Instance, if required
     if ( bIsUnlockRequired )
     {
         loadInstance();
     }

     // Throw the exception if any, to the calling function
     if ( exception != NULL )
     {
         throw exception;
     }

     LOG_TRACE ( logger, "END : GET_POM_object::setProperty(ints)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const double, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to a double property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               dPropValue        - Property Value to be set (const double)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const double dPropValue, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(double)" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }
    try
    {
        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the Property Value
        stat = POM_set_attr_double ( 1, &_tag, tAttrTag, dPropValue );

         // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(double)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const vector<double>, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to an array of double property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               vPropValues       - Vector of Property Values to be set (const vector<double>)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const vector<double> vPropValues, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    double *pdPropValues = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(doubles)" );

    try
    {
        int iPropCount = vPropValues.size();

        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }

        GET_vectorToArray ( vPropValues, &pdPropValues );

         // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

         // Set the Property Value
        stat = POM_set_attr_doubles ( 1, &_tag, tAttrTag, 0, iPropCount, pdPropValues );

        // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Free the Memory
    GET_free ( ( void* ) pdPropValues );

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(doubles)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const bool, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to a logical property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               bPropValue        - Property Value to be set (const bool)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const bool bPropValue, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(boolean)" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }

    try
    {
        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the Property Value
        stat = POM_set_attr_logical ( 1, &_tag, tAttrTag, ( bPropValue == false ? FALSE : TRUE ) );

        // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(boolean)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const vector<bool>, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to an array of logical property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               vPropValues       - Vector of Property Values to be set (const vector<bool>)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const vector<bool> vPropValues, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    logical *plPropValues = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(booleans)" );

    try
    {
        int iPropCount = vPropValues.size();

        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }

        GET_vectorToArray ( vPropValues, &plPropValues );

         // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

         // Set the Property Value
        stat = POM_set_attr_logicals ( 1, &_tag, tAttrTag, 0, iPropCount, plPropValues );

         // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Free the Memory
    GET_free ( ( void* ) plPropValues );

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(booleans)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const GET_DateShrPtr, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to a date property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               datePtrPropValue  - Property Value to be set (const GET_DateShrPtr)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const GET_DateShrPtr datePtrPropValue, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(boolean)" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }

    try
    {
        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the Property Value
        stat = POM_set_attr_date ( 1, &_tag, tAttrTag, datePtrPropValue->getDate() );

         // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(boolean)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const vector<GET_DateShrPtr>, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to an array of logical property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               datePtrPropValues - Vector of Property Values to be set (const vector<GET_DateShrPtr>)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const vector<GET_DateShrPtr> vPropValues, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    date_t *pdtPropValues = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(dates)" );

    try
    {
        int iPropCount = vPropValues.size();

        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }

        GET_vectorToArray ( vPropValues, &pdtPropValues );

         // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

         // Set the Property Value
        stat = POM_set_attr_dates ( 1, &_tag, tAttrTag, 0, iPropCount, pdtPropValues );

         // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

     // Free the Memory
    GET_free ( ( void* ) pdtPropValues );

     // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

     // Throw the exception if any, to the calling function
     if ( exception != NULL )
     {
         throw exception;
     }

     LOG_TRACE ( logger, "END : GET_POM_object::setProperty(dates)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const GET_POM_objectShrPtr, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to a tag property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               ptrPropValue      - Property Value to be set (const GET_POM_objectShrPtr)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const GET_POM_objectShrPtr ptrPropValue, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(tag)" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }

    try
    {
        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the Property Value
        stat = POM_set_attr_tag ( 1, &_tag, tAttrTag, ptrPropValue->getTag() );

        // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(tag)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setProperty ( const string, const vector<GET_POM_objectShrPtr>, const bool&, const bool& )
 //
 //   Purpose :   Method to set value to an array of tag property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
 //               vPropValues       - Vector of Property Values to be set (const vector<GET_POM_objectShrPtr>)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setProperty ( const string sPropName, const vector<GET_POM_objectShrPtr> vPropValues, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    tag_t *ptPropValues = NULL;

    LOG_TRACE ( logger, "START : GET_POM_object::setProperty(tags)" );

    try
    {
        int iPropCount = vPropValues.size();

        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }

        GET_vectorToArray ( vPropValues, &ptPropValues );

        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the Property Value
        stat = POM_set_attr_tags ( 1, &_tag, tAttrTag, 0, iPropCount, ptPropValues );

        // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Free the Memory
    GET_free ( ( void* ) ptPropValues );

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::setProperty(tags)" );
 }

 /*STARTFUNCDOC ***
  //
  ===========================================================================
  //   Function:   appendProperty ( const string, const vector<GET_POM_objectShrPtr>, const bool&, const bool& )
  //
  //   Purpose :   Method to append value to an array of tag property for this object
  //
  //   Inputs  :   sPropName         - Property Name for which the value needs to be set (const string)
  //               vPropValues       - Vector of Property Values to be set (const vector<GET_POM_objectShrPtr>)
  //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
  //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
  //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
  //
  //   Outputs :   none
  //
  //   Return  :   none
  //
  //   History :
  //      Who                    Date                 Description
  //   TCS Development Team     07 Nov, 2016         Initial creation
  //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
  //
  ===========================================================================
  //ENDFUNCDOC   ***/
 void GET_POM_object::appendProperty ( const string sPropName, const vector<GET_POM_objectShrPtr> vPropValues, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    tag_t *ptPropValues = NULL;

    LOG_TRACE ( logger, "START : GET_POM_object::appendProperty(tags)" );

    try
    {
       int iPropCount = vPropValues.size();

       stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
       if ( tAttrTag == NULLTAG )
       {
           THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
       }

       GET_vectorToArray ( vPropValues, &ptPropValues );

       // Lock the Instance, if not already done
       if ( bIsLockRequired )
       {
           lockInstanceForModification();
       }

       stat = POM_append_attr_tags ( 1, &_tag, tAttrTag, iPropCount, ptPropValues );

       // Save the Instance, if required
       if ( bIsSaveRequired )
       {
           saveInstance();
       }
    }
    catch ( IFail &ex )
    {
       exception = &ex;
    }

    // Free the Memory
    GET_free ( ( void* ) ptPropValues );

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
       loadInstance();
    }

   // Throw the exception if any, to the calling function
   if ( exception != NULL )
   {
       throw exception;
   }

   LOG_TRACE ( logger, "END : GET_POM_object::appendProperty(tags)" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setPropertyToNull ( const string, const bool&, const bool& )
 //
 //   Purpose :   Method to set NULL value to a property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the NULL value needs to be set (const string)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
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
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setPropertyToNull ( const string sPropName, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setPropertyToNull" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }

    try
    {
        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the NULL Value
        stat = POM_set_attr_null ( 1, &_tag, tAttrTag );

        // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "START : GET_POM_object::setPropertyToNull" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   setPropertyToNulls ( const string, const bool&, const bool& )
 //
 //   Purpose :   Method to set NULL value to an array property for this object
 //
 //   Inputs  :   sPropName         - Property Name for which the NULL values needs to be set (const string)
 //               bIsLockRequired   - Is Lock Required before setting Property *(optional, default is true)(const bool&)
 //               bIsSaveRequired   - Save Required after setting Property *(optional, default is true)(const bool&)
 //               bIsUnlockRequired - Unlock required for setting Property *(optional, default is true)(const bool&)
 //
 //   Outputs :   none
 //
 //   Return  :   none
 //   History :
 //      Who                    Date                 Description
 //   TCS Development Team     11 May, 2016         Initial creation
 //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 void GET_POM_object::setPropertyToNulls ( const string sPropName, const bool &bIsLockRequired, const bool &bIsSaveRequired, const bool &bIsUnlockRequired )
 {
    IFail *exception = NULL;

    int iAttrLength = 0;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::setPropertyToNulls" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }

    try
    {
        stat = POM_length_of_attr ( _tag, tAttrTag, &iAttrLength );

        // Lock the Instance, if not already done
        if ( bIsLockRequired )
        {
            lockInstanceForModification();
        }

        // Set the NULL Value
        stat = POM_set_attr_nulls ( 1, &_tag, tAttrTag, 0, iAttrLength );

        // Save the Instance, if required
        if ( bIsSaveRequired )
        {
            saveInstance();
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Unlock the Instance, if required
    if ( bIsUnlockRequired )
    {
        loadInstance();
    }

    // Throw the exception if any, to the calling function
    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "START : GET_POM_object::setPropertyToNulls" );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyString ( const string )
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
 string GET_POM_object::getPropertyString ( const string sPropName )
 {
    char *pcPropValue = NULL;

    logical lIsNull = FALSE;
    logical lIsEmpty = FALSE;

    string sPropValue = "";

    tag_t tAttrTag = NULLTAG;

    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyString" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }
    stat = POM_ask_attr_string ( _tag, tAttrTag, &pcPropValue, &lIsNull, &lIsEmpty );
    if ( lIsNull == FALSE )
    {
        sPropValue = pcPropValue;
        MEM_free ( pcPropValue );
    }
    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyString" );

    return sPropValue;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyStrings ( const string )
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
 //   TCS Development Team     19 Dec, 2017        Added NULL Check for lIsNull parameter 
 ===========================================================================================
 //ENDFUNCDOC   ***/
 vector<string> GET_POM_object::getPropertyStrings ( const string sPropName )
 {
    char **ppcPropValues = NULL;

    IFail *exception = NULL;

    int iPropLength = 0;

    logical *lIsNull = NULL;
    logical *lIsEmpty = NULL;

    tag_t tAttrTag = NULLTAG;

    ResultCheck stat;

    vector<string> vPropValues;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyStrings" );

    try
    {
        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }
        stat = POM_length_of_attr ( _tag, tAttrTag, &iPropLength );
        stat = POM_ask_attr_strings ( _tag, tAttrTag, 0, iPropLength, &ppcPropValues, &lIsNull, &lIsEmpty );

        if ( lIsNull == FALSE )
        { 
           GET_arrayToVector ( iPropLength, ( const char** ) ppcPropValues, vPropValues );
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Free the Memory
    GET_free_tc_array ( iPropLength, ( void** ) ppcPropValues );

    MEM_free ( lIsNull );
    MEM_free ( lIsEmpty );

    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyStrings" );

    return vPropValues;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyInteger ( const string )
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
 int GET_POM_object::getPropertyInteger ( const string sPropName )
 {
    int iPropValue = 0;

    logical lIsNull = FALSE;
    logical lIsEmpty = FALSE;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyInteger" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }
    stat = POM_ask_attr_int ( _tag, tAttrTag, &iPropValue, &lIsNull, &lIsEmpty );

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyInteger" );

    return iPropValue;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyIntegers ( const string )
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
 //   TCS Development Team     19 Dec, 2017         Added NULL Check for lIsNull parameter 
 ===========================================================================================
 //ENDFUNCDOC   ***/
 vector<int> GET_POM_object::getPropertyIntegers ( const string sPropName )
 {
    IFail *exception = NULL;

    int iPropLength = 0;

    int *piPropValues = NULL;

    logical *lIsNull = NULL;
    logical *lIsEmpty = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    vector<int> vPropValues;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyIntegers" );

    try
    {
        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }
        stat = POM_length_of_attr( _tag, tAttrTag, &iPropLength );
        stat = POM_ask_attr_ints ( _tag, tAttrTag, 0, iPropLength, &piPropValues, &lIsNull, &lIsEmpty );
    
        if ( lIsNull == FALSE )
        { 
            GET_arrayToVector ( iPropLength, piPropValues, vPropValues );
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    //Free Memory
    GET_free_tc_array ( iPropLength, ( void** ) piPropValues );

    MEM_free( lIsNull );
    MEM_free( lIsEmpty );

    if ( exception != NULL )
    {
         throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyIntegers" );

    return vPropValues;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyDouble ( const string )
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
 double GET_POM_object::getPropertyDouble ( const string sPropName )
 {
    double dPropValue = 0;

    logical lIsNull = FALSE;
    logical lIsEmpty = FALSE;

    tag_t tAttrTag = NULLTAG;

    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyDouble" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }
    stat = POM_ask_attr_double ( _tag, tAttrTag, &dPropValue, &lIsNull, &lIsEmpty );

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyDouble" );

    return dPropValue;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyDoubles ( const string )
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
 //   TCS Development Team    19 Dec, 2017         Added NULL Check for lIsNull parameter 
 ===========================================================================================
 //ENDFUNCDOC   ***/
 vector<double> GET_POM_object::getPropertyDoubles ( const string sPropName )
 {
    double *pdPropValues = NULL;

    IFail *exception = NULL;

    int iPropLength = 0;

    logical *lIsNull = NULL;
    logical *lIsEmpty = NULL;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    vector<double> vPropValues;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyDouble" );

    try
    {
        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }
        stat = POM_length_of_attr ( _tag, tAttrTag, &iPropLength );
        stat = POM_ask_attr_doubles ( _tag, tAttrTag, 0, iPropLength, &pdPropValues, &lIsNull, &lIsEmpty );

        if ( lIsNull == FALSE )
        { 
            GET_arrayToVector ( iPropLength, pdPropValues, vPropValues );
        }
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    MEM_free( pdPropValues );
    MEM_free( lIsNull );
    MEM_free( lIsEmpty );

    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyDouble" );

    return vPropValues;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyLogical ( const string )
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
 bool GET_POM_object::getPropertyLogical ( const string sPropName )
 {
    logical lPropValue = FALSE;
    logical lIsNull = FALSE;
    logical lIsEmpty = FALSE;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyLogical" );

    stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
    if ( tAttrTag == NULLTAG )
    {
        THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
    }
    stat = POM_ask_attr_logical (  _tag, tAttrTag, &lPropValue, &lIsNull, &lIsEmpty );

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyLogical" );

    return ( lPropValue == FALSE ? false: true );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyLogicals ( const string )
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
 //   TCS Development Team    19 Dec, 2017         Added NULL Check for lIsNull parameter 
 ========================================================================================
 //ENDFUNCDOC   ***/
 vector<bool> GET_POM_object::getPropertyLogicals ( const string sPropName )
 {
    IFail *exception = NULL;

    logical *plPropValues = NULL;
    logical *lIsNull = NULL;
    logical *lIsEmpty = NULL;

    int iPropLength = 0;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    vector<bool> vPropValues;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyLogicals" );

    try
    {
        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
            THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }
        stat = POM_length_of_attr ( _tag, tAttrTag, &iPropLength );
        stat = POM_ask_attr_logicals ( _tag, tAttrTag, 0, iPropLength, &plPropValues, &lIsNull, &lIsEmpty );

        if ( lIsNull == FALSE )
        { 
            GET_arrayToVector ( iPropLength, plPropValues, vPropValues );
        } 
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    MEM_free( plPropValues );
    MEM_free( lIsNull );
    MEM_free( lIsEmpty );

    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyLogicals" );

    return vPropValues;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyDate ( const string )
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
 GET_DateUnqPtr GET_POM_object::getPropertyDate ( const string sPropName )
 {
     date_t dtPropValue = NULLDATE;

     logical lIsNull = FALSE;
     logical lIsEmpty = FALSE;

     ResultCheck stat;

     tag_t tAttrTag = NULLTAG;

     LOG_TRACE ( logger, "START : GET_POM_object::getPropertyLogical" );

     stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
     if ( tAttrTag == NULLTAG )
     {
         THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
     }
     stat = POM_ask_attr_date ( _tag, tAttrTag, &dtPropValue, &lIsNull, &lIsEmpty );

     LOG_TRACE ( logger, "END : GET_POM_object::getPropertyLogical" );

     return GET_Date::getInstance ( dtPropValue );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyDates ( const string )
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
 //   TCS Development Team    19 Dec, 2017         Added NULL Check for lIsNull parameter 
 ========================================================================================
 //ENDFUNCDOC   ***/
 vector<GET_DateUnqPtr> GET_POM_object::getPropertyDates ( const string sPropName )
 {
    date_t *pdtPropValues = NULL;

    IFail *exception = NULL;

    logical *lIsNull = FALSE;
    logical *lIsEmpty = FALSE;

    int iPropLength = 0;

    ResultCheck stat;

    tag_t tAttrTag = NULLTAG;

    vector<GET_DateUnqPtr> vPropValues;

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyLogicals" );

    try
    {
        stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
        if ( tAttrTag == NULLTAG )
        {
           THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
        }
        stat = POM_length_of_attr ( _tag, tAttrTag, &iPropLength );
        stat = POM_ask_attr_dates ( _tag, tAttrTag, 0, iPropLength, &pdtPropValues, &lIsNull, &lIsEmpty );

        if ( lIsNull == FALSE )
        { 
           GET_arrayToVector ( iPropLength, pdtPropValues, vPropValues );
        }
    }
    catch ( IFail &ex )
    {
       exception = &ex;
    }

    MEM_free ( pdtPropValues );
    MEM_free ( lIsNull );
    MEM_free ( lIsEmpty );

    if ( exception != NULL )
    {
       throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyLogicals" );

    return vPropValues;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyTag ( const string )
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
 GET_POM_objectUnqPtr GET_POM_object::getPropertyTag ( const string sPropName )
 {
     logical lIsNull = FALSE;
     logical lIsEmpty = FALSE;

     ResultCheck stat;

     tag_t tPropValue = NULLTAG;
     tag_t tAttrTag = NULLTAG;

     LOG_TRACE ( logger, "START : GET_POM_object::getPropertyTag" );

     stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
     if ( tAttrTag == NULLTAG )
     {
         THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
     }
     stat = POM_ask_attr_tag ( _tag, tAttrTag, &tPropValue, &lIsNull, &lIsEmpty );

     LOG_TRACE ( logger, "END : GET_POM_object::getPropertyTag" );

     return make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tPropValue );
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyTags ( const string )
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
 vector<GET_POM_objectUnqPtr> GET_POM_object::getPropertyTags ( const string sPropName )
 {
     IFail *exception = NULL;

     int iPropLength = 0;

     logical *lIsNull = NULL;
     logical *lIsEmpty = NULL;

     ResultCheck stat;

     tag_t tAttrTag = NULLTAG;

     tag_t *ptPropValues = NULL;

     vector<GET_POM_objectUnqPtr> vPropValues;

     LOG_TRACE ( logger, "START : GET_POM_object::getPropertyTags" );

     try
     {
         stat = POM_attr_id_of_attr ( sPropName.c_str(), getClassName().c_str(), &tAttrTag );
         if ( tAttrTag == NULLTAG )
         {
             THROW ( sPropName + " is not a valid Teamcenter property for this Object" );
         }
         stat = POM_length_of_attr ( _tag, tAttrTag, &iPropLength );
         stat = POM_ask_attr_tags ( _tag, tAttrTag, 0, iPropLength, &ptPropValues, &lIsNull, &lIsEmpty );

         GET_arrayToVector ( iPropLength, ptPropValues, vPropValues );
     }
     catch ( IFail &ex )
     {
         exception = &ex;
     }

     MEM_free ( ptPropValues );
     MEM_free ( lIsNull );
     MEM_free ( lIsEmpty );

     if ( exception != NULL )
     {
         throw exception;
     }

     LOG_TRACE ( logger, "END : GET_POM_object::getPropertyTags" );

     return vPropValues;
 }

 /*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   askTypeName()
 //
 //   Purpose :   Method to get type name
 //
 //   Inputs  :   none
 //
 //   Outputs :   none
 //
 //   Return  :   String Type name of current object
 //
 //   History :
 //      Who                    Date                 Description
 //   TCS Development Team      03 Mar, 2017         Modified method to make as instance method for returning the type name
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
 string GET_POM_object::askTypeName()
 {
     char *pTypeName = NULL;

     ResultCheck stat;

     string sTypeName = "";

     tag_t tTypeTag = NULLTAG;

     LOG_TRACE ( logger, "START : GET_POM_object::askTypeName()" );

     stat = TCTYPE_ask_object_type ( _tag, &tTypeTag  );
     stat = TCTYPE_ask_name2 ( tTypeTag, &pTypeName );
     if ( pTypeName != NULL )
     {
         sTypeName = pTypeName;
         MEM_free ( pTypeName );
     }

     LOG_TRACE ( logger, "END : GET_POM_object::askTypeName()" );

     return sTypeName;
 }

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   askTypeDisplayName()
//
//   Purpose :   Method to get the display name of the type of this Object
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   String Display name of the type of current object
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team      11 Sep, 2017         Initial Creation
===========================================================================
//ENDFUNCDOC   ***/
 string GET_POM_object::askTypeDisplayName()
 {
     char *pTypeDisplayName = NULL;

     ResultCheck stat;

     string sTypeDisplayName = "";

     tag_t tTypeTag = NULLTAG;

     LOG_TRACE ( logger, "START : GET_POM_object::askTypeDisplayName()" );

     stat = TCTYPE_ask_object_type ( _tag, &tTypeTag  );
     stat = TCTYPE_ask_display_name ( tTypeTag, &pTypeDisplayName );
     if ( pTypeDisplayName != NULL )
     {
         sTypeDisplayName = pTypeDisplayName;
         MEM_free ( pTypeDisplayName );
     }

     LOG_TRACE ( logger, "END : GET_POM_object::askTypeDisplayName()" );

     return sTypeDisplayName;
 }
 
/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   askTypeName ( const tag_t )
//
//   Purpose :   Method to get type name
//
//   Inputs  :   tType - Tag of type
//
//   Outputs :   none
//
//   Return  :   Type name
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     30 Sep, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
string GET_POM_object::askTypeName ( const tag_t tType )
{
    char *pTypeName = NULL;
    ResultCheck stat;
    string sTypeName = "";

    LOG_TRACE ( logger, "START : GET_POM_object::askTypeName()" );

    stat = TCTYPE_ask_name2 ( tType, &pTypeName );
    if ( pTypeName != NULL )
    {
        sTypeName = pTypeName;
        MEM_free ( pTypeName );
    }

    LOG_TRACE ( logger, "END : GET_POM_object::askTypeName()" );

    return sTypeName;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getAllInstances ( const string )
//
//   Purpose :   Method to get all the instances of the given class
//
//   Inputs  :   sClassName - String name of the class
//               bIncludeSubClasses - Flag to indicate if instances of sub-classes are also required *(optional, default is false)(const bool&)
//
//   Outputs :   none
//
//   Return  :   vector of GET_POM_object smart pointer instances (GET_POM_objectUnqPtr)
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
vector<GET_POM_objectUnqPtr> GET_POM_object::getAllInstances ( const string sClassName, const bool &bIncludeSubClasses )
{
    IFail *exception = NULL;

    int iCount = 0;

    ResultCheck stat;

    tag_t tClassId = NULLTAG;

    tag_t *ptInstanceTags = NULL;

    vector<GET_POM_objectUnqPtr> vInstances;

    LOG_TRACE ( logger, "START : GET_POM_object::getAllInstances()" );

    try
    {
        // Get the Teamcenter class ID
        stat = POM_class_id_of_class ( sClassName.c_str(), &tClassId );
        if ( tClassId == NULLTAG )
        {
            THROW ( sClassName + " is not a valid Teamcenter class" );
        }

        // Get all the Instances of the given class
        stat = POM_instances_of_class ( tClassId, bIncludeSubClasses ? TRUE : FALSE, &iCount, &ptInstanceTags );
        GET_arrayToVector ( iCount, ptInstanceTags, vInstances );
    }
    catch ( IFail &ex )
    {
        exception = &ex;
    }

    // Free the memory
    MEM_free ( ptInstanceTags );

    if ( exception != NULL )
    {
        throw exception;
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getAllInstances()" );

    return vInstances;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   getPomReferecers
//
//   Purpose :   Method to convert UID to tag
//
//   Inputs  :   iNoLevels (int) - Number of levels (default 1)
//               iWhereToSearch (int) (default POM_in_ds_and_db)
//
//   Outputs :   none
//
//   Return  :   Struct pomReferencers ptr
//
//   History :
//      Who                    Date                 Description
//   TCS Development Team     9 Nov, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
GET_POMReferencersUnqPtr GET_POM_object::getPomReferences ( int iNoLevels, int iWhereToSearch )
{
    int iNoInstances = 0;
    int *piInstanceLevels = NULL;
    int *piInstanceWhereFound = NULL;
    int iNoClasses = 0;
    int *piClassLevels = NULL;
    int *piClassWhereFound = NULL;

    tag_t *ptRefInstances = NULL;
    tag_t *ptRefClasses = NULL;

    GET_POMReferencersUnqPtr pomRefsPtr = make_unique<GET_POMReferencers>();

    ResultCheck stat;

    LOG_TRACE ( logger, "START : GET_POM_object::getPomReferences()" );

    stat = POM_referencers_of_instance ( _tag, iNoLevels, iWhereToSearch, &iNoInstances,
            &ptRefInstances, &piInstanceLevels, &piInstanceWhereFound, &iNoClasses, &ptRefClasses,
            &piClassLevels, &piClassWhereFound );

    pomRefsPtr->iNoInstances = iNoInstances;
    pomRefsPtr->iNoClasses = iNoClasses;

    for ( int iIndex = 0; iIndex < iNoInstances; iIndex++ )
    {
        if ( !checkPrivilege ( ptRefInstances[iIndex], AM_PRIV_READ ) )
        {
            continue;
        }
        pomRefsPtr->vRefInstances.push_back ( GET_POM_object::getInstance ( ptRefInstances[iIndex] ) );
        pomRefsPtr->vInstanceLevels.push_back ( ptRefInstances[iIndex] );
        pomRefsPtr->vInstanceWhereFound.push_back ( piInstanceWhereFound[iIndex] );
    }

    for ( int iIndex = 0; iIndex < iNoClasses; iIndex++ )
    {
        pomRefsPtr->vRefClasses.push_back ( GET_POM_object::getInstance ( ptRefClasses[iIndex] ) );
    }

    if ( iNoInstances > 0 )
    {
        MEM_free ( ptRefInstances );
        MEM_free ( piInstanceLevels );
        MEM_free ( piInstanceWhereFound );
        MEM_free ( piClassLevels );
        MEM_free ( piClassWhereFound );
    }
    if ( ptRefClasses != NULL )
    {
        MEM_free ( ptRefClasses );
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getPomReferences()" );

    return pomRefsPtr;
}
/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getPropertyDisplayName()
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
 //  Ganesh Ubale          09 Sep, 2017         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
string GET_POM_object::getPropertyDisplayName ( const string sPropName )
{
    char *pcDispName = NULL;

    ResultCheck stat;

    string sDispName = "";

    LOG_TRACE ( logger, "START : GET_POM_object::getPropertyDisplayName" );

    stat = AOM_UIF_ask_name ( _tag, sPropName.c_str(), &pcDispName );
    if ( pcDispName != NULL )
    {
        sDispName = pcDispName;
        MEM_free ( pcDispName );
    }

    LOG_TRACE ( logger, "END : GET_POM_object::getPropertyDisplayName" );

    return sDispName;
}
