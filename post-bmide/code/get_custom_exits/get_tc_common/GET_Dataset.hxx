
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Dataset.hxx
//
//    Purpose:   Header  class for dealing with the Dataset class
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016         Initial creation
//  TCS Development Team     18 Jul, 2016         Modified the method signature for returning GET_ImanFile Objects
//  TCS Development Team     12 Apr, 2017         Added new method exportNamedReference
//  TCS Development Team     17 May, 2017         Modified the getNamedRefs method to retrieve all Reference Types (Form & ImanFile)
//  TCS Development Team     17 May, 2017         Corrected the method name for importNameReference
//  TCS Development Team     17 May, 2017         Modified the getNamedRefs(string) code to return all Named Reference Types for a given reference name
//  TCS Development Team     23 May, 2017         Remove the unnecessary refType argument and added parameters for controlling instance locking/modification in the addNamedRef method
//  TCS Development Team     23 May, 2017         Added parameters for controlling instance locking/modification in the methods removeNamedRef, importNamedReference, removedNamedReferences
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_DATASET_HXX
#define GET_DATASET_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_ImanFile.hxx>
#include <GET_WorkspaceObject.hxx>

//CPP Includes
#include <string>
#include <vector>

//Teamcenter Includes
#include <ae/ae.h>
#include <tccore/aom.h>

// Smart Pointer Definition
namespace get
{
    #define GET_DatasetUnqPtr unique_ptr<GET_Dataset>
    #define GET_DatasetShrPtr shared_ptr<GET_Dataset>
}

namespace get
{
    class DLLEXPORT GET_Dataset : public GET_WorkspaceObject
	{
	    private:
            string sDatasetName;

	    public:
            enum RefType
            {
                TEXT, BINARY, HTML
            };

             /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   GET_Dataset ( const GET_DUMMY, const tag_t )
             //
             //   Purpose :   Constructor for the class GET_Dataset
             //
             //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
             //               tTag    - The Tag of this Teamcenter Dataset Object
             //
             //   Outputs :   none
             //
             //   Return  :   none
             //
             //   History :
             //      Who                    Date                 Description
             //  TCS Development Team     02 May, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_Dataset ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   ~GET_Dataset()
            //
            //   Purpose :   Destructor for the class GET_Dataset
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     02 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            virtual ~GET_Dataset();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getNamedRefs()
            //
            //   Purpose :   Method to get the named references of this instance
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The Vector of GET_DatasetUnqPtr of named references(vector<GET_DatasetUnqPtr>)
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //   TCS Development Team     18 Jul, 2016         Modified the method signature for returning GET_ImanFile Objects
            //   TCS Development Team     17 May, 2017         Modified the getNamedRefs method to retrieve all Reference Types (Form & ImanFile)
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_POM_objectUnqPtr> getNamedRefs();

            /*STARTFUNCDOC ***
            //
            //  ===========================================================================
            //   Function:   getNamedRefs()
            //
            //   Purpose :   Get POM objects that are attached to the Dataset as named references
            //
            //   Inputs  :   sRefName - reference name to get reference
            //
            //   Outputs :   none
            //
            //   Return  :   The vector of POM Objects objects for the input dataset ( vector<GET_POM_objectUnqPtr> )
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     30 Mar, 2016         Initial creation
            //  TCS Development Team     17 May, 2017         Modified the code to return all Named Reference Types for a given reference name
            //
            // ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_POM_objectUnqPtr> getNamedRefs ( const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   createInstance ( const string, const string, const string, const string, const string )
            //
            //   Purpose :   Method to Create GET_Dataset with input type , toolName , dataset ID , dataset rev , dataset description
            //
            //   Inputs  :   sDSTypeName    - Dataset type ( const string )
            //               sToolName      - Dataset Tool Name ( const string )
            //               sDSId          - Dataset ID ( const string )
            //               sDSRev         - Dataset Revision ID ( const string )
            //               sDSDescription - Dataset Description (const string )
            //
            //   Outputs :   none
            //
            //   Return  :   The Dataset Unique pointer of the created object is returned (GET_DatasetUnqPtr)
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_DatasetUnqPtr createInstance ( const string, const string, const string, const string, const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   addNamedRef ( const GET_ImanFileShrPtr, const string )
            //
            //   Purpose :   Method to add input namedref file to dataset with the given refernce name
            //
            //   Inputs  :   imanFilePtr - Iman file object to be added ( const string )
            //               sRefName    - Reference Name ( const string )
            //               bIsLockRequired   - Is Lock Required before adding named reference *(optional, default is true)(const bool&)
            //               bIsSaveRequired   - Is Save Required after adding named reference *(optional, default is true)(const bool&)
            //               bIsUnlockRequired - Is unlock required for adding named reference *(optional, default is true)(const bool&)
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //   TCS Development Team     23 May, 2017         Remove the unnecessary refType argument and added parameters for controlling instance locking/modification
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void addNamedRef ( const GET_ImanFileShrPtr, const string, const bool &bIsLockRequired = true, const bool &bISaveRequired = true, const bool &bIsUnlockRequired = true );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   find ( const string, const string )
            //
            //   Purpose :   Method to find Dataset for the given dataset Name and given dataset type
            //
            //   Inputs  :   sDatasetName - Dataset Name  ( const string )
            //               sDatasetType - Dataset Type ( const string )
            //
            //   Outputs :   none
            //
            //   Return  :   The vector of found Dataset unique smart pointer is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            vector<GET_DatasetUnqPtr> find ( const string, const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   removeNamedRef ( const GET_ImanFileShrPtr, const string )
            //
            //   Purpose :   Method to remove named reference for the given imanfile and reference name
            //
            //   Inputs  :   imanFilePtr    - Iman file object to be removed  ( const string )
            //               sReferenceName - Reference Name ( const string )
            //               bIsLockRequired   - Is Lock Required before adding named reference *(optional, default is true)(const bool&)
            //               bIsSaveRequired   - Is Save Required after adding named reference *(optional, default is true)(const bool&)
            //               bIsUnlockRequired - Is unlock required for adding named reference *(optional, default is true)(const bool&)
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     11 Apr, 2016         Initial creation
            //  TCS Development Team     23 May, 2017         Added parameters for controlling instance locking/modification
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void removeNamedRef ( const GET_ImanFileShrPtr, const string, const bool &bIsLockRequired = true, const bool &bISaveRequired = true, const bool &bIsUnlockRequired = true );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   deleteInstance()
            //
            //   Purpose :   Method to delete Dataset instance from Teamcenter
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            void deleteInstance();

            /*STARTFUNCDOC ***
            //
            //  ===========================================================================
            //   Function:   getDatasetTypeName()
            //
            //   Purpose :   Getter for getting dataset type name
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The Dataset type object is returned (string)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     30 Mar, 2016         Initial creation
            //
            // ===========================================================================
            //ENDFUNCDOC   ***/
            virtual string getDatasetTypeName() ;

            /*STARTFUNCDOC ***
            //     ===========================================================================
            //   Function:   importNamedReference()
            //
            //   Purpose :   Imports the specified file into Teamcenter Engineering,
            //               creating a new ImanFile using the specified file name and
            //               associates that ImanFile object with the specified dataset object.
            //               The reference type is used for the named reference connecting the dataset  to the ImanFile.
            //
            //   Inputs  :   sReferenceName  - Name of the reference used for associating the file and dataset.
            //               sOsFullPathName - Source location in the operating system (including file name).
            //               sNewFileName    - Name of the file to be used as meta data in Teamcenter Engineering.
            //               iFileTypeFlag   - Flag to indicate BINARY or TEXT file type
            //               bIsLockRequired   - Is Lock Required before adding named reference *(optional, default is true)(const bool&)
            //               bIsSaveRequired   - Is Save Required after adding named reference *(optional, default is true)(const bool&)
            //               bIsUnlockRequired - Is unlock required for adding named reference *(optional, default is true)(const bool&)
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History:
            //      Who                   Date                 Description
            //  TCS Development Team     11 Apr, 2016         Initial creation
            //  TCS Development Team     17 May, 2017         Corrected the method name
            //  TCS Development Team     23 May, 2017         Added parameters for controlling instance locking/modification
            //
            // ===========================================================================
            //ENDFUNCDOC   ***/
            virtual void importNamedReference ( const string, const string, const string, const int, const bool &bIsLockRequired = true, const bool &bISaveRequired = true, const bool &bIsUnlockRequired = true );

            /*STARTFUNCDOC ***
            //  ===========================================================================
            //   Function:   exportNamedReference()
            //
            //   Purpose :   Export the Named Ref file into given OS file path for selected Dataset,
            //
            //   Inputs  :   sReferenceName  - Name of the reference used for associating the file and dataset.
            //               sOsFullPathName - Source location in the operating system (including file name).
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History:
            //      Who                   Date                 Description
            //  TCS Development Team      12 Apr, 2017         Initial creation
            //
            // ===========================================================================
            //ENDFUNCDOC   ***/
            virtual void exportNamedReference ( const string, const string );

            /*STARTFUNCDOC ***
            //     ===========================================================================
            //   Function:   removeNamedReferences ( const string )
            //
            //    Purpose:   Method to remove the named Reference from the Dataset
            //
            //    Inputs:    sReferenceName - name of the reference to remove, Defaults to 'Text' ( const string )
            //               bIsLockRequired   - Is Lock Required before adding named reference *(optional, default is true)(const bool&)
            //               bIsSaveRequired   - Is Save Required after adding named reference *(optional, default is true)(const bool&)
            //               bIsUnlockRequired - Is unlock required for adding named reference *(optional, default is true)(const bool&)
            //
            //    Outputs:   none
            //
            //    return:    none
            //
            //     History:
            //      Who                   Date                 Description
            //  TCS Development Team     30 Mar, 2016         Initial creation
            //  TCS Development Team     17 May, 2017         Modified the code to reflect the change in getNamedRefs method
            //  TCS Development Team     23 May, 2017         Added parameters for controlling instance locking/modification
            //
            // ===========================================================================
            //ENDFUNCDOC   ***/
            virtual void removeNamedReferences ( const string, const bool &bIsLockRequired = true, const bool &bISaveRequired = true, const bool &bIsUnlockRequired = true );

            /*STARTFUNCDOC ***
            //
            //  ===========================================================================
            //   Function:   getFormat()
            //
            //   Purpose :   Getter for getting format of the dataset
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   GET Dataset Reference type is returned (RefType)
            //
            //   History :
            //      Who                   Date                 Description
            //  TCS Development Team     30 Mar, 2016         Initial creation
            //
           // ===========================================================================
            //ENDFUNCDOC   ***/
            virtual RefType getFormat();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getInstance (tTag)
            //
            //   Purpose :   Method to get the instance of this class using tag_t
            //
            //   Inputs  :   tTag - tag of the Dataset
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_Dataset Smart Pointer object is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_DatasetUnqPtr getInstance ( const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getInstance (sUID)
            //
            //   Purpose :   Method to get the instance of this class using string UID
            //
            //   Inputs  :   sUID - UID as string
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_Dataset Smart Pointer object is returned
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_DatasetUnqPtr getInstance ( const string );
    };
}

#endif // GET_DATASET_HXX
