
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanTextFile.hxx
//
//    Purpose:    Header class for dealing with GET_ImanTextFile objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     05 Apr, 2016         Initial creation
//  TCS Development Team     23 May, 2017         Corrected the method type (static) of createInstance method
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_IMANTEXTFILE_HXX
#define GET_IMANTEXTFILE_HXX

//GE includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_ImanFile.hxx>

#include <string>
#include <vector>

// Smart Pointer Definition
namespace get
{
    #define GET_ImanTextFileUnqPtr unique_ptr<GET_ImanTextFile>
    #define GET_ImanTextFileShrPtr shared_ptr<GET_ImanTextFile>
}

namespace get
{
	class DLLEXPORT GET_ImanTextFile : public GET_ImanFile
	{
		public:

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
	        GET_ImanTextFile ( const GET_DUMMY, const tag_t );

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
			virtual ~GET_ImanTextFile();

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
			static GET_ImanTextFileUnqPtr import ( const string sOsFileSpec, const string sFileName );

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
			string readText() const;

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
			 //  TCS Development Team     23 May, 2017         Corrected the method type (static)
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			static GET_ImanTextFileUnqPtr createInstance ( const string sFileContent, const string sOrginalFileName );

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
			static GET_ImanTextFileUnqPtr getInstance ( const tag_t );

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
			static GET_ImanTextFileUnqPtr getInstance ( const string );
	};
}

#endif // GET_IMANTEXTFILE_HXX
