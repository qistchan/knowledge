
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_application_object.hxx
//
//    Purpose:   Class for dealing with GET_POM_application_object objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     31 Mar, 2016         Initial creation
//  TCS Development Team     21 Jul, 2016         Added deleteFromParent function
//  TechM Development Team   20 May, 2017         Added deleteObject function
//  TCS Development Team     08 Sep, 2017         Added method getPropTableRows to retrieve Table Property values
//  TCS Development Team     20 Sep, 2017         Added method for lock and unlock 
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_POM_APPLICATION_OBJECT_HXX
#define GET_POM_APPLICATION_OBJECT_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_group.hxx>
#include <GET_POM_object.hxx>

//CPP Includes
#include <string>
#include <vector>

//Teamcenter Includes
#include <tccore/aom.h>
#include <tccore/aom_prop.h>

// Smart Pointer Definition
namespace get
{
    #define GET_POM_application_objectUnqPtr unique_ptr<GET_POM_application_object>
    #define GET_POM_application_objectShrPtr shared_ptr<GET_POM_application_object>
}

namespace get
{
    class GET_POM_user;
    class DLLEXPORT GET_POM_application_object : public GET_POM_object
    {
        public:

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
            GET_POM_application_object ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_POM_application_object();

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
            void refreshObject ( const bool &bIsLockRequired = false );

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
            virtual void save();

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
			 //  TCS Development Team     20 Jun, 2018         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual void lock();

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
			 //  TCS Development Team     20 Jun, 2018         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual void unlock();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   setOwner
            //
            //    Purpose:   Method to set the owner
            //
            //     Inputs:   userPtr  - Smart Pointer for GET_POM_user object
            //               groupPtr - Smart Pointer for GET_POM_group object
            //               bIsSaveRequired   - Is Save Required after setting Property *(optional, default is true)(const bool&)
            //               bIsUnlockRequired - Is unlock required for setting Property *(optional, default is true)(const bool&)
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
            void setOwner ( const shared_ptr<GET_POM_user>, const shared_ptr<GET_POM_group>, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void deleteObject();

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
            void deleteFromParent ( const GET_POM_application_objectShrPtr parentShrPtr );

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
            virtual void setPropValueAsString ( const string, const string, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const string, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const vector<string>, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const int, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true ) ;

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
            void setProp ( const string, const vector<int>, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const double, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const vector<double>, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const bool, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const vector<bool>, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const GET_DateShrPtr, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const vector<GET_DateShrPtr>, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const GET_POM_objectShrPtr, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProp ( const string, const vector<GET_POM_objectShrPtr>, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            virtual unique_ptr<GET_POM_group> getOwningGroup();

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
            virtual unique_ptr<GET_POM_user> getOwningUser();

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
            virtual unique_ptr<GET_POM_user> getLastModifyingUser();

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
            virtual string getOwningSiteName();

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
            virtual string getPropDisplayName ( const string ) const;

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
            virtual string getPropValueAsString ( const string ) const;

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
            string getPropString ( const string );

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
            vector<string> getPropStrings ( const string );

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
            int getPropInteger ( const string );

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
            vector<int> getPropIntegers ( const string );

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
            double getPropDouble ( const string );

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
            vector<double> getPropDoubles ( const string );

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
            bool getPropLogical ( const string );

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
            vector<bool> getPropLogicals ( const string );

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
            GET_DateUnqPtr getPropDate ( const string );

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
            vector<GET_DateUnqPtr> getPropDates ( const string );

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
            GET_POM_objectUnqPtr getPropTag ( const string );

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
            //   Return  :   The vector of GET_POM_object smart pointer for given property is returned (vector<GET_POM_application_objectUnqPtr>)
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     2 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_POM_objectUnqPtr> getPropTags ( const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getPropTableRows ( const string )
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
            vector<GET_POM_objectUnqPtr> getPropTableRows ( const string );

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
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     20 June, 2018         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			vector<GET_POM_objectUnqPtr> appendTableRow ( const string, int );


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
            virtual bool isPropModifiable ( const string ) const;

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
            virtual bool isPropList ( const string ) const;

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   askPropertyType()
            //
            //    Purpose:   Method to get the Property Type
            //
            //     Inputs:   sPropName - Name of the property whose type is required (string)
            //
            //    Outputs:   none
            //
            //     Return:   Returns property type (PROP_type_t)
            //
            //    History:
            //      Who                   Date                 Description
            //  TCS Development Team     05 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            PROP_type_t askPropertyType ( const string ) const;

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   askPropValueType()
            //
            //    Purpose:   Method to get the Property Value Type
            //
            //     Inputs:   sPropName - Name of the property whose value type is required (string)
            //
            //    Outputs:   none
            //
            //     Return:   Returns property type (PROP_type_t)
            //
            //    History:
            //      Who                   Date                 Description
            //  TCS Development Team     05 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            PROP_value_type_t askPropValueType ( const string ) const;

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   isNull()
            //
            //    Purpose:   Method to get the Property Value Type
            //
            //     Inputs:   sPropName - Name of the property whose value is to be checked
            //               bCheckZeroLength - Check if string length is zero or no
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
            bool isNull ( const string, bool = true ) const;

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
            int numElements ( const string ) const;

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
            static GET_POM_application_objectUnqPtr getInstance ( const tag_t );

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
            static GET_POM_application_objectUnqPtr getInstance ( const string );
    };
}

#endif // GET_POM_APPLICATION_OBJECT_HXX
