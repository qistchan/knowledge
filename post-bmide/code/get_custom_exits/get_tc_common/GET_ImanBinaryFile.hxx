
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanBinaryFile.hxx
//
//    Purpose:   Header class for dealing withGET_ImanBinaryFile objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     05 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_IMANBINARYFILE_HXX
#define GET_IMANBINARYFILE_HXX


//GE includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_ImanFile.hxx>

//Cpp Includes
#include <string>

// Smart Pointer Definition
namespace get
{
    #define GET_ImanBinaryFileUnqPtr unique_ptr<GET_ImanBinaryFile>
    #define GET_ImanBinaryFileShrPtr shared_ptr<GET_ImanBinaryFile>
}

namespace get 
{
    class DLLEXPORT GET_ImanBinaryFile : public GET_ImanFile
	{
    	public:

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
            GET_ImanBinaryFile ( const GET_DUMMY, const tag_t );

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
			virtual ~GET_ImanBinaryFile();

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
			static GET_ImanBinaryFileUnqPtr import ( const string, const string );

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
			static GET_ImanBinaryFileUnqPtr createInstance ( const string, const string );

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
			static GET_ImanBinaryFileUnqPtr getInstance ( const tag_t );

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
			static GET_ImanBinaryFileUnqPtr getInstance ( const string );
	};
}

#endif //GET_IMANBINARYFILE_HXX
