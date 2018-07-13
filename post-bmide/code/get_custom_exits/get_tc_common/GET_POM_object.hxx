
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_POM_object.hxx
//
//    Purpose:   Header class for dealing with the pom_object class
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016          Initial creation
//  TCS Development Team     03 Mar, 2017          Modified method to make as instance method for returning the type name
//  TCS Development Team     09 May, 2017          Added a new Parameter (bIsLockRequired) for all the setProperty() methods
//                                                 for controlling instance locking before attempting to set the attribute value
//  TCS Development Team     19 May, 2017          Added method declaration getAllInstances for retrieving all instances of a given class
//  TCS Development Team     26 May, 2017          Added method for POM_compare_dates
//  TCS Development Team     27 Jun, 2017          Removed method for POM_compare_dates
//  TCS Development Team     11 Sep, 2017          Added a new method askTypeDisplayName for retrieving the Display name of the object's type
//  Ganesh Ubale             09 Sep, 2017          Added Method getPropertyDisplayName
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_POM_OBJECT_HXX
#define GET_POM_OBJECT_HXX

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_Date.hxx>
#include <GET_TC_Classes.hxx>
#include <GET_TC_Attributes.hxx>

// CPP Includes
#include <string>
#include <vector>
#include <map>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <fclasses/tc_date.h>

// Smart Pointer Definition
namespace get
{
    #define GET_POM_objectUnqPtr unique_ptr<GET_POM_object>
    #define GET_POM_objectShrPtr shared_ptr<GET_POM_object>
    #define GET_POMReferencersUnqPtr unique_ptr<GET_POM_object::GET_POMReferencers>
    #define GET_POMReferencersShrPtr shared_ptr<GET_POM_object::GET_POMReferencers>
}

namespace get
{
    class DLLEXPORT GET_POM_object
    {
        private:
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
            void init ( const tag_t tTag );

        protected:
            bool bIsLocked;
            tag_t _tag;
            enum GET_DUMMY { GET_DUMMY_VALUE }; // DUMMY Enum to make sure that only classes within the hierarchy can use constructors

        public:

            /*STARTSTRUCTDOC ***
            //
            ===========================================================================
            //   Function:   GET_POMReferencers ()
            //
            //   Purpose :   Structure for pom referencers
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     9 Nov, 2016         Initial creation
            //
            ===========================================================================
            //ENDSTRUCTDOC   ***/
            struct GET_POMReferencers
            {
                int iNoInstances;
                int iNoClasses;
                int iClassLevels;
                int iClassWhereFound;

                vector <GET_POM_objectUnqPtr> vRefInstances;
                vector <GET_POM_objectUnqPtr> vRefClasses;
                vector <int> vInstanceLevels;
                vector <int> vInstanceWhereFound;
            };

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
            GET_POM_object ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_POM_object();

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
            tag_t getTag() const;

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
            string getClassName() const;

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
            virtual bool isLoaded();

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
            virtual void loadInstance();

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
            virtual void unloadInstance();

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
            virtual void lockInstanceForModification();

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
            virtual void saveInstance ( const bool &bIsUnloadRequired = true );

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
            virtual void deleteInstance();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   checkUserPrivilege()
            //
            //   Purpose :   Method to Check the AM privilege of object (READ, WRITE, DELETE, CHANGE, PROMOTE, DEMOTE,
            //               COPY, IMPORT, EXPORT, TRANSFER_IN and TRANSFER_OUT)
            //
            //   Inputs  :  userObj - User whose privilege is to be checked
             *              sPrivilegeName - specific privilege to be checked
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
            bool checkUserPrivilege ( GET_POM_objectShrPtr userObj, const string sPrivilegeName );

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
            void setProperty ( const string, const string, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const vector<string>, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const int, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true ) ;

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
            void setProperty ( const string, const vector<int>, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const double, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const vector<double>, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const bool, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const vector<bool>, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const GET_DateShrPtr, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const vector<GET_DateShrPtr>, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const GET_POM_objectShrPtr, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void setProperty ( const string, const vector<GET_POM_objectShrPtr>, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            void appendProperty ( const string, const vector<GET_POM_objectShrPtr>, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true  );

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
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void setPropertyToNull ( const string, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

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
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 May, 2016         Initial creation
            //   TCS Development Team     09 May, 2017         Added a new Parameter (bIsLockRequired) for controlling instance locking before attempting to set the attribute value
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void setPropertyToNulls ( const string, const bool &bIsLockRequired = true, const bool &bIsSaveRequired = true, const bool &bIsUnlockRequired = true );

            // Method to get property value

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
            string getPropertyString ( const string );

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
            int getPropertyInteger ( const string );

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
            double getPropertyDouble ( const string );

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
            bool getPropertyLogical ( const string );

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
            GET_DateUnqPtr getPropertyDate ( const string );

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
            GET_POM_objectUnqPtr getPropertyTag ( const string );

            // Method to get list of property values

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
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<string> getPropertyStrings ( const string );

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
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<double> getPropertyDoubles ( const string );

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
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<int> getPropertyIntegers ( const string );

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
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<bool> getPropertyLogicals ( const string );

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
            vector<GET_POM_objectUnqPtr> getPropertyTags ( const string );

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
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_DateUnqPtr> getPropertyDates ( const string );

            // Static method prototypes
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
            static bool isDescendant ( const tag_t, const string );

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
            static bool checkPrivilege ( const tag_t tTag, const string sPrivilegeName );

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
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_POM_objectUnqPtr createInstance ( const string );

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
            static GET_POM_objectUnqPtr getInstance ( const tag_t );

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
            static GET_POM_objectUnqPtr getInstance ( const string );

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
            static tag_t getTagFromUID ( const string );

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
            string getUID ( );

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
            GET_POMReferencersUnqPtr getPomReferences ( int = 1, int = POM_in_ds_and_db );

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
            void refresh ( int iLockType );

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
            ===========================================================================
            //ENDFUNCDOC   ***/
            string askTypeName();

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
            string askTypeDisplayName();

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
            static string askTypeName ( const tag_t );

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
            static vector<GET_POM_objectUnqPtr> getAllInstances ( const string, const bool &bIncludeSubClasses = false );
			
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
			string getPropertyDisplayName ( const string );
    };
}

#endif // GET_POM_OBJECT_HXX
