
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanFile.cxx
//
//    Purpose:   Class for dealing with GET_ImanFile objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     9 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/item.h>
#include <pom/enq/enq.h>
#include <tccore/aom.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

#include <GET_ImanFile.hxx>

const string logger = "get.ge_tc_common.GET_ImanFile";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_ImanFile()
	 //
	 //    Purpose:   Constructor for the class GET_ImanFile
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
	 //  TCS Development Team     18 July, 2016        Modified the constructor code to differentiate between File Name & Original File Name
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ImanFile::GET_ImanFile ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_application_object ( enDummy, tTag )
    {
        char *pcOriginalFileName = NULL;

        ResultCheck stat;

        stat = IMF_ask_original_file_name2 ( tTag, &pcOriginalFileName );
        sOriginalFileName = pcOriginalFileName;
        MEM_free ( pcOriginalFileName );

        sFileName = getPropString ( FILENAME_ATTR );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_ImanFile()
	 //
	 //    Purpose:   Destructor for the class GET_ImanFile
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
    GET_ImanFile::~GET_ImanFile(){}

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
	 //     Return:   GET_ImanFileUnqPtr - Smart Pointer for GET_ImanFile object is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ImanFileUnqPtr GET_ImanFile::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_ImanFile::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, IMANFILE_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + IMANFILE_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_ImanFile::getInstance(tTag)" );

		return make_unique<GET_ImanFile> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
	 //
	 //    Outputs:   none
	 //
	 //     Return:   GET_ImanFileUnqPtr - Smart Pointer for GET_ImanFile object is returned
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ImanFileUnqPtr GET_ImanFile::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_ImanFile::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );
		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_ImanFile::getInstance(sUID)" );

		return getInstance(tObjectTag);
	}

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getFileName()
	 //
	 //    Purpose:   Method to get the Volume file Name
	 //
	 //     Inputs:   none
	 //               
	 //    Outputs:   none
	 //
	 //     Return:   The Volume name of this File (string)
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     9 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    string GET_ImanFile::getFileName()
    {
        return sFileName;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getOriginalFileName()
     //
     //    Purpose:   Method to get the Original file Name
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   The Original name of this File (string)
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     18 July, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_ImanFile::getOriginalFileName()
    {
        return sOriginalFileName;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   setOriginalFileName()
	 //
	 //    Purpose:   Method to set the Original file Name
	 //
	 //    Inputs:   const string value
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The Original name of this File (string)
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     25 July, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
     void GET_ImanFile::setOriginalFileName( const string originalFileName )
     {
    	 ResultCheck stat;

    	 LOG_TRACE ( logger, "START : GET_ImanFile::setOriginalFileName" );

    	 stat = IMF_set_original_file_name2 ( _tag,  originalFileName.c_str() );

    	 LOG_TRACE ( logger, "END : GET_ImanFile::setOriginalFileName" );
     }

	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   exportFile()
	 //
	 //    Purpose:   Method to export Iman file
	 //
	 //     Inputs:   sPathName - Path Name of the iman file to be exported (string)
	 //   
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //    
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     9 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    void GET_ImanFile::exportFile ( const string sPathName )
	{
		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_ImanFile::exportFile" );

        string sPath = sPathName + string( GET_SYSAPI_getFileSeparator() ) + this->getFileName();

		stat = IMF_export_file ( _tag, sPath.c_str() );

        LOG_TRACE ( logger, "END : GET_ImanFile::exportFile" );
	}

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   replaceFile()
	 //
	 //    Purpose:   Method to export Iman file
	 //
	 //     Inputs:   pathName      - Path Name of the iman file to replace
	 //               bKeepFileName - If it is set to true, it sets the original file name of a given TcFile to the original file name of file_tag
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     9 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    void GET_ImanFile::replaceFile ( const string sPathName, const bool &bKeepFileName )
    {
    	ResultCheck stat;

    	LOG_TRACE ( logger, "START : GET_ImanFile::replaceFile");

    	stat = IMF_replace_file ( _tag, sPathName.c_str(), ( bKeepFileName ? TRUE : FALSE ) );

    	LOG_TRACE ( logger, "END : GET_ImanFile::replaceFile");
    }
}
