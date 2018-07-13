
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Dataset.cxx
//
//    Purpose:   Class for dealing with the Dataset objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016           Initial creation
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
 
// GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Dataset.hxx>
#include <GET_ImanFile.hxx>
#include <GET_ImanTextFile.hxx>
#include <GET_ImanBinaryFile.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Types.hxx>

// TC Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/item.h>
#include <pom/enq/enq.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_Dataset";

namespace get
{
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
    GET_Dataset::GET_Dataset ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag )
    {
        LOG_TRACE ( logger, "GET_Dataset::GET_Dataset" );

        sDatasetName = getPropString ( OBJECT_NAME_ATTR );

        LOG_TRACE ( logger, "GET_Dataset::GET_Dataset" );
    }

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
    GET_Dataset::~GET_Dataset() {}

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
    GET_DatasetUnqPtr GET_Dataset::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_Dataset::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, DATASET_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + DATASET_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_Dataset::getInstance(tTag)" );

        return make_unique<GET_Dataset> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

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
    GET_DatasetUnqPtr GET_Dataset::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_Dataset::getInstance(sUID)\n" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_Dataset::getInstance(sUID)\n" );

        return getInstance ( tObjectTag );
    }

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
    vector<GET_POM_objectUnqPtr> GET_Dataset::getNamedRefs()
    {
        ResultCheck stat;

        vector<GET_POM_objectUnqPtr> vNamedRefs;

        LOG_TRACE ( logger, "START : GET_Dataset::getNamedRefs" );

        vector<GET_POM_objectUnqPtr> namedRefObjs = getPropTags ( REFLIST_ATTR );
        for ( size_t iIndex = 0; iIndex < namedRefObjs.size(); iIndex++ )
        {
            vNamedRefs.push_back ( make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, namedRefObjs[iIndex]->getTag() ) );
        }

        LOG_TRACE ( logger, "END : GET_Dataset::getNamedRefs" );

        return vNamedRefs;
    }

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
    vector<GET_POM_objectUnqPtr> GET_Dataset::getNamedRefs ( const string sRefName )
    {
        char **ppcRefNamesList = NULL;

        int iRefNamesCount = 0;
        int iRefListCount = 0;

        IFail *exception = NULL;

        logical *lIsNull = NULL;
        logical *lIsEmpty = NULL;

        tag_t tRefListAttr = NULLTAG;
        tag_t tRefNamesAttr = NULLTAG;

        tag_t *tRefList = NULL;

        ResultCheck stat;

        vector<GET_POM_objectUnqPtr> vNamedRefPtrs;

        LOG_TRACE ( logger, "START : GET_Dataset::getNamedRefs" );

        try
        {
            stat = POM_attr_id_of_attr ( REFLIST_ATTR, DATASET, &tRefListAttr );
            stat = POM_length_of_attr ( _tag, tRefListAttr, &iRefListCount );
            if ( iRefListCount > 0 )
            {
                stat = POM_ask_attr_tags ( _tag, tRefListAttr, 0, iRefListCount, &tRefList, &lIsNull, &lIsEmpty );
                MEM_free ( lIsNull );
                MEM_free ( lIsEmpty );
            }

            stat = POM_attr_id_of_attr ( REFNAMES_ATTR, DATASET, &tRefNamesAttr );
            stat = POM_length_of_attr ( _tag, tRefNamesAttr, &iRefNamesCount );
            if ( iRefNamesCount > 0 )
            {
                stat = POM_ask_attr_strings ( _tag, tRefNamesAttr, 0, iRefNamesCount, &ppcRefNamesList, &lIsNull, &lIsEmpty );
                MEM_free ( lIsNull );
                MEM_free ( lIsEmpty );
            }

            for ( int iIndex = 0; iIndex < iRefNamesCount; iIndex++ )
            {
                if ( sRefName.compare ( ppcRefNamesList[iIndex] ) != 0 )
                {
                    continue;
                }
                if ( tRefList[iIndex] == NULLTAG )
                {
                    continue;
                }
                vNamedRefPtrs.push_back ( make_unique<GET_POM_object> ( GET_DUMMY::GET_DUMMY_VALUE, tRefList[iIndex] ) );
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        MEM_free ( ppcRefNamesList );
        MEM_free ( tRefList );

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Dataset::getNamedRefs" );

        return vNamedRefPtrs;
    }

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
    GET_DatasetUnqPtr  GET_Dataset::createInstance ( const string sDSTypeName, const string sToolName, const string sDSId, const string sDSRev, const string sDSDescription )
    {
        ResultCheck stat;

        tag_t tDatasetTypeTag = NULLTAG;
        tag_t tToolTag = NULLTAG;
        tag_t tDatasetTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_Dataset::createInstance" );

        stat = AE_find_datasettype2 ( sDSTypeName.c_str(),  &tDatasetTypeTag );
        stat = AE_find_tool2 ( sToolName.c_str(), &tToolTag );
        stat = AE_create_dataset_with_id ( tDatasetTypeTag, sDSId.c_str(), sDSDescription.c_str(), sDSId.c_str(), sDSRev.c_str(), &tDatasetTag );
        stat = AE_set_dataset_tool ( tDatasetTag, tToolTag );
        stat = AOM_save ( tDatasetTag );

        LOG_TRACE ( logger, "END : GET_Dataset::createInstance" );

        return make_unique<GET_Dataset> ( GET_DUMMY::GET_DUMMY_VALUE, tDatasetTag );
    }

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
	void GET_Dataset::addNamedRef ( const GET_ImanFileShrPtr imanFilePtr, const string sRefName, const bool &bIsLockRequired, const bool &bISaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Dataset::addNamedRef" );

        try
        {
            if ( bIsLockRequired )
            {
                refreshObject ( true );
            }
            stat = AE_add_dataset_named_ref2 ( _tag, sRefName.c_str(), AE_ASSOCIATION, imanFilePtr->getTag() );
            if ( bISaveRequired )
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
            refreshObject ( false );
        }

        // Throw the exception caught, if any to the calling method
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Dataset::addNamedRef" );
    }

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
    vector<GET_DatasetUnqPtr> GET_Dataset::find ( const string sDatasetName, const string sDatasetType )
    {
        const char *pcEnqID = "dataset_query";

        IFail *exception = NULL;

        int iRowCount = 0;
        int iColCount = 0;

        ResultCheck stat;

        vector<GET_DatasetUnqPtr> vDataset;

        void ***pppvValues = NULL;

        LOG_TRACE ( logger, "START : GET_Dataset::find" );

        stat = POM_enquiry_create ( pcEnqID );

        try
        {
            const char *pcjoinExp1 = "JOINEXP1";
            const char *pcjoinExp2 = "JOINEXP2";
            const char *pcCombExp = "COMBINED_EXPR1";
            const char *pcSelectAttrList[]  = { PUID_ATTR };

            stat = POM_enquiry_add_select_attrs ( pcEnqID,  DATASET,  1,  pcSelectAttrList );

            stat = POM_enquiry_set_string_expr ( pcEnqID,  pcjoinExp1,  DATASET,  OBJECT_NAME_ATTR,  POM_enquiry_equal, ( char* ) sDatasetName.c_str() );
            stat = POM_enquiry_set_string_expr ( pcEnqID,  pcjoinExp2,  DATASET,  OBJECT_TYPE_ATTR,  POM_enquiry_equal, ( char* ) sDatasetType.c_str() );
            stat = POM_enquiry_set_expr ( pcEnqID, pcCombExp, pcjoinExp1, POM_enquiry_and, pcjoinExp2 );
            stat = POM_enquiry_set_where_expr ( pcEnqID,  pcCombExp );
            stat = POM_enquiry_set_distinct ( pcEnqID, TRUE );
            stat = POM_enquiry_execute ( pcEnqID,  &iRowCount,  &iColCount,  &pppvValues );

            for ( int iIndex = 0; iIndex < iRowCount; iIndex++ )
            {
                tag_t tempTag = * ( tag_t* ) ( pppvValues[iIndex][0] );
                vDataset.push_back ( make_unique<GET_Dataset> ( GET_DUMMY::GET_DUMMY_VALUE, tempTag ) );
            }

            stat =  POM_enquiry_delete ( pcEnqID ) ;
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free_tc_array ( iRowCount, iColCount, ( void*** ) pppvValues );

        // Throw exceptions if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Dataset::find" );

        return vDataset;
    }

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
    void GET_Dataset::removeNamedRef ( const GET_ImanFileShrPtr imanFilePtr, const string sReferenceName, const bool &bIsLockRequired, const bool &bISaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Dataset::removeNamedRef" );

        try
        {
            if ( bIsLockRequired )
            {
                refreshObject ( true );
            }
            stat = AE_remove_dataset_named_ref_by_tag2 ( _tag, sReferenceName.c_str(), imanFilePtr->getTag() );
            if ( bISaveRequired )
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
            refreshObject ( false );
        }

        // Throw exceptions if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Dataset::removeDatasetNamedRef" );
    }

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
    void GET_Dataset::deleteInstance()
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Dataset::deleteInstance" );

        refreshObject ( true );
        stat = AOM_delete( _tag );

        LOG_TRACE ( logger, "END : GET_Dataset::deleteInstance" );
    }

     /*STARTFUNCDOC ***
     //
     //     ===========================================================================
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
    string GET_Dataset::getDatasetTypeName()
    {
        char *pcDatasetTypeName = NULL;

        ResultCheck stat;

        string sDatasetTypeName = "";

        tag_t tdatasetTypeTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_Dataset::getDatasetTypeName" );

        stat = AE_ask_dataset_datasettype ( _tag, &tdatasetTypeTag );
        stat = AE_ask_datasettype_name2 ( tdatasetTypeTag, &pcDatasetTypeName );
        if ( pcDatasetTypeName != NULL )
        {
            sDatasetTypeName = pcDatasetTypeName;
            MEM_free ( pcDatasetTypeName );
        }

        LOG_TRACE ( logger, "END : GET_Dataset::getDatasetTypeName" );

        return sDatasetTypeName;
    }

     /*STARTFUNCDOC ***
     //
     //     ===========================================================================
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
    GET_Dataset::RefType GET_Dataset::getFormat()
    {
        char *pcFormatName = NULL;

        RefType rType;

        ResultCheck stat;

        string sFormatName = "";

        LOG_TRACE ( logger, "START : GET_Dataset::getFormat" );

        stat = AE_ask_dataset_format2 ( _tag, &pcFormatName );

        if ( pcFormatName != NULL )
        {
            sFormatName = pcFormatName;
            MEM_free ( pcFormatName );
        }

        if ( sFormatName.compare ( TEXT_REF ) == 0 )
        {
            rType = TEXT;
        }
        else
        {
            rType = BINARY;
        }

        LOG_TRACE ( logger, "END : GET_Dataset::getFormat" );

        return rType;
    }

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
    void GET_Dataset::importNamedReference ( const string sReferenceName, const string sOsFullPathName, const string sNewFileName, const int iFileTypeFlag,
                                             const bool &bIsLockRequired, const bool &bISaveRequired, const bool &bIsUnlockRequired )
    {
        IFail *exception = NULL;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Dataset::importNamedReference" );

        try
        {
            if ( bIsLockRequired )
            {
                refreshObject ( true );
            }
            stat = AE_import_named_ref ( _tag, sReferenceName.c_str(), sOsFullPathName.c_str(), sNewFileName.c_str(), iFileTypeFlag );
            if ( bISaveRequired )
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
             refreshObject ( false );
        }

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Dataset::importNamedReference" );
    }

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
    void GET_Dataset::exportNamedReference ( const string sReferenceName, const string sOsFullPathName )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Dataset::exportNamedReference" );

        stat = AE_export_named_ref ( _tag, sReferenceName.c_str(), sOsFullPathName.c_str() );

        LOG_TRACE ( logger, "END : GET_Dataset::exportNamedReference" );
    }

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
    void GET_Dataset::removeNamedReferences ( const string sReferenceName, const bool &bIsLockRequired, const bool &bISaveRequired, const bool &bIsUnlockRequired )
    {
        ResultCheck stat;

        IFail *exception = NULL;

        vector<GET_POM_objectUnqPtr> vFilePtrs;

        LOG_TRACE ( logger, "START : GET_Dataset::removeNamedReferences" );

        try
        {
            vFilePtrs = GET_Dataset::getNamedRefs ( sReferenceName );
            if ( vFilePtrs.size() > 0 )
            {
                if ( bIsLockRequired )
                {
                    refreshObject ( true );
                }
                for ( size_t iIndex = 0; iIndex < vFilePtrs.size(); iIndex++ )
                {
                    stat = AE_remove_dataset_named_ref_by_tag ( _tag, sReferenceName.c_str(), vFilePtrs[iIndex]->getTag() );
                }
                if ( bISaveRequired )
                {
                    save();
                }
            }
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        if ( bIsUnlockRequired )
        {
            refreshObject ( false );
        }

        // Throw the exception if any, to the calling function
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Dataset::removeNamedReferences" );
    }
}
