
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanTextFile.cxx
//
//    Purpose:    class for dealing with GET_ImanTextFile objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     05 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE includes
#include <GET_ImanTextFile.hxx>
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Utils.hxx>

#include <string>

#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <sa/tcfile.h>
#include <ss/ss_errors.h>

const string logger = "get.get_tc_common.GET_ImanTextFile";

namespace get 
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_ImanTextFile()
	 //
	 //    Purpose:   Constructor for the class GET_ImanTextFile
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
	GET_ImanTextFile::GET_ImanTextFile ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_ImanFile ( enDummy, tTag ) {};

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_ImanTextFile()
	 //
	 //    Purpose:   Destructor for the class GET_ImanTextFile
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
	GET_ImanTextFile::~GET_ImanTextFile() {}

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
	 //     Return:   The GET_ImanTextFile Smart Pointer instance of the given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanTextFileUnqPtr GET_ImanTextFile::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_ImanTextFile::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, IMANFILE_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + IMANFILE_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_ImanTextFile::getInstance(tTag)" );

		return make_unique<GET_ImanTextFile> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //     Return:   The GET_ImanTextFile Smart Pointer instance of the given UID
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanTextFileUnqPtr GET_ImanTextFile::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_ImanTextFile::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );
		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_ImanTextFile::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   import()
	 //
	 //    Purpose:   method to import text file
	 //
	 //     Inputs:   sOsFileSpec - OS file name to import
	 //               sFileName   - new file name
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_ImanTextFile Smart Pointer instance of the newly imported File
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanTextFileUnqPtr GET_ImanTextFile::import ( const string sOsFileSpec, const string sFileName )
	{
		GET_ImanTextFileUnqPtr textFilePtr;

		ResultCheck stat;

		tag_t tImportedFile = NULLTAG;

		IMF_file_t fDesc = NULL;

		LOG_TRACE ( logger, "START : GET_ImanTextFile::import");

		stat = IMF_import_file ( sOsFileSpec.c_str(), sFileName.c_str(), TEXT, &tImportedFile, &fDesc );

		stat = IMF_close_file ( fDesc );
		textFilePtr = make_unique<GET_ImanTextFile> ( GET_DUMMY::GET_DUMMY_VALUE, tImportedFile );
		textFilePtr->save();

		LOG_TRACE ( logger, "END : GET_ImanTextFile::import");

		return textFilePtr;
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   readText()
	 //
	 //    Purpose:   method to read text from this text file
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The text content of this File is returned (string)
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	string GET_ImanTextFile::readText() const
	{
		char *pcBuffer = NULL;

		IMF_file_t fileDescriptor;

		ResultCheck stat;

		string sContent = "";

		LOG_TRACE ( logger, "START : GET_ImanTextFile::readText" );

        stat = IMF_ask_file_descriptor ( _tag, &fileDescriptor );

        stat = IMF_open_file ( fileDescriptor , SS_RDONLY );

        while ( IMF_read_file_line2 ( fileDescriptor, &pcBuffer ) == SS_EOF )
        {
            sContent = sContent + string ( pcBuffer );
            MEM_free ( pcBuffer );
        }

        stat = IMF_close_file ( fileDescriptor );

        LOG_TRACE ( logger, "END : GET_ImanTextFile::readText" );

		return sContent;
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   createInstance()
	 //
	 //    Purpose:   Method to Create GET_ImanTextFile with name passed as Input and writing in the file with input string
	 //
	 //     Inputs:   sFileContent     - named reference file content(string)
	 //				  orginalFileName  - named reference original file name(string)
	 //
	 //    Outputs:   none
	 //
     //     Return:   The GET_ImanTextFile Smart Pointer instance of the newly created File
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     05 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	GET_ImanTextFileUnqPtr GET_ImanTextFile::createInstance ( const string sFileContent , const string sOrginalFileName )
	{
	    GET_ImanTextFileUnqPtr textFilePtr;

		IMF_file_t tFileDescr = NULL;

		ResultCheck stat;

		tag_t tNamedrefFile = NULLTAG;

		LOG_TRACE ( logger, "START : GET_ImanTextFile::createInstance" );

        stat = IMF_create_file ( NULL, TEXT, &tNamedrefFile, &tFileDescr );
        stat = IMF_set_original_file_name2 ( tNamedrefFile, sOrginalFileName.c_str() );
        stat = IMF_close_file ( tFileDescr );
        textFilePtr = make_unique<GET_ImanTextFile> ( GET_DUMMY::GET_DUMMY_VALUE, tNamedrefFile );
        stat = IMF_open_file ( tFileDescr, SS_APPEND );
        stat = IMF_write_file_line2 ( tFileDescr, sFileContent.c_str() );
        stat = IMF_close_file ( tFileDescr );
        textFilePtr->save();

		LOG_TRACE ( logger, "END : GET_ImanTextFile::createInstance" );

		return textFilePtr;
	}
}
