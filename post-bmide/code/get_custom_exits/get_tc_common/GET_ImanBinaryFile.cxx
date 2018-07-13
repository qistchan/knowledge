
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanBinaryFile.cxx
//
//    Purpose:    class for dealing with GET_ImanBinaryFile objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     05 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE includes
#include <GET_ImanBinaryFile.hxx>
#include <GET_cpp_stl.h>
#include <GET_TC_Logger.hxx>
#include <GET_Exception.hxx>

//TC Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <sa/tcfile.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get_tc_common.GET_ImanBinaryFile";

namespace get 
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_ImanBinaryFile()
	 //
	 //    Purpose:   Constructor for the class GET_ImanBinaryFile
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag    - The Tag of this Teamcenter ImanFile Object
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     02 May, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanBinaryFile::GET_ImanBinaryFile ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_ImanFile ( enDummy, tTag ) {}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_ImanBinaryFile()
	 //
	 //    Purpose:   Destructor for the class GET_ImanBinaryFile
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     02 May, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanBinaryFile::~GET_ImanBinaryFile() {}

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
	 //     Return:   The GET_ImanBinaryFile Smart Pointer instance of this given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanBinaryFileUnqPtr GET_ImanBinaryFile::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_ImanBinaryFile::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, IMANFILE_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + IMANFILE_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_ImanBinaryFile::getInstance(tTag)" );

		return make_unique<GET_ImanBinaryFile> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //     Return:   The GET_ImanBinaryFile Smart Pointer instance of this given UID
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanBinaryFileUnqPtr GET_ImanBinaryFile::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_ImanFile::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );
		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_ImanFile::getInstance(sUID)\n" );

		return getInstance ( tObjectTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   import()
	 //
	 //    Purpose:   Method to import binary file
	 //
	 //     Inputs:   sOsFileSpec - The OS file name to import (string)
	 //               sFileName   - The new file name to be set (string)
	 //
	 //    Outputs:   none
	 //
	 //     Return:   GET_ImanBinaryFileUnqPtr - Smart Pointer for The GET_ImanBinaryFile object is returned
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     18 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanBinaryFileUnqPtr GET_ImanBinaryFile::import ( const string sOsFileSpec, const string sFileName )
	{
	    GET_ImanBinaryFileUnqPtr binaryFilePtr;

		ResultCheck stat;

		tag_t tImportedFile = NULLTAG;

		IMF_file_t fDesc = NULL;

		LOG_TRACE ( logger, "START : GET_ImanBinaryFile::import" );

		stat = IMF_import_file ( sOsFileSpec.c_str(), sFileName.c_str(), BINARY, &tImportedFile, &fDesc );

		stat = IMF_close_file ( fDesc );
		binaryFilePtr = make_unique<GET_ImanBinaryFile> ( GET_DUMMY::GET_DUMMY_VALUE, tImportedFile );
		binaryFilePtr->save();

		LOG_TRACE ( logger, "END : GET_ImanBinaryFile::import" );

		return binaryFilePtr;
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   createInstance()
	 //
	 //    Purpose:   Method to Create GET_ImanBinaryFile with name passed as Input and writing in the file with input string
	 //
	 //     Inputs:   sFileContent     - Named reference file content(string)
	 //				  sOrginalFileName - Named reference original file name(string)
	 //
	 //    Outputs:   none
	 //
     //     Return:   GET_ImanBinaryFileUnqPtr - Smart Pointer for the GET_ImanBinaryFile object is returned
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanBinaryFileUnqPtr GET_ImanBinaryFile::createInstance ( const string sFileContent, const string sOrginalFileName )
	{
	    GET_ImanBinaryFileUnqPtr binaryFilePtr;

		IMF_file_t tFileDescr = NULL;

		ResultCheck stat;

		tag_t tNamedrefFile = NULLTAG;

		LOG_TRACE ( logger, "START : GET_ImanBinaryFile::createInstance" );

        stat = IMF_create_file ( NULL, BINARY, &tNamedrefFile, &tFileDescr );
        stat = IMF_set_original_file_name2 ( tNamedrefFile, sOrginalFileName.c_str() );
        stat = IMF_close_file ( tFileDescr );
        binaryFilePtr = make_unique<GET_ImanBinaryFile> ( GET_DUMMY::GET_DUMMY_VALUE, tNamedrefFile );
        stat = IMF_open_file ( tFileDescr, SS_APPEND );
        stat = IMF_write_file_line2 ( tFileDescr, sFileContent.c_str() );
        stat = IMF_close_file ( tFileDescr );
        binaryFilePtr->save();

		LOG_TRACE ( logger, "END : GET_ImanBinaryFile::createInstance" );

		return binaryFilePtr;
	}
}
