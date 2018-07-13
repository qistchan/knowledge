
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanFile.hxx
//
//    Purpose:   Header class for dealing with ImanFile objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     9 Mar, 2016           Initial creation
//  TCS Development Team     18 Jul, 2016          Added method to differentiate the file name from the original file name
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_IMANFILE_HXX
#define GET_IMANFILE_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_application_object.hxx>

//CPP Includes
#include <string>
#include <vector>

//Teamcenter Includes
#include <sa/tcfile.h>

// Smart Pointer Definition
namespace get
{
    #define GET_ImanFileUnqPtr unique_ptr<GET_ImanFile>
    #define GET_ImanFileShrPtr shared_ptr<GET_ImanFile>
}

namespace get
{
    class DLLEXPORT GET_ImanFile : public GET_POM_application_object
    {
        private:
            string sFileName;
            string sOriginalFileName;

        public:
            enum GET_ImanFileType
            {
                UNKNOWN = 0,
            	TEXT = SS_TEXT,
            	BINARY = SS_BINARY,
            	TRANSLATE = SS_TRANSLATE
            };

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
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_ImanFile ( const GET_DUMMY, const tag_t );

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
			virtual ~GET_ImanFile();

			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getFileName()
			 //
			 //    Purpose:   Method to get the Iman file Name
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The Iman File name of this File (string)
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     9 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			string getFileName();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getOriginalFileName()
             //
             //    Purpose:   Method to get the original Volume file Name
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Original File name of this File in the Volume (string)
             //
             //    History:
             //      Who                   Date                 Description
             //  TCS Development Team     18 Jul, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            string getOriginalFileName();

            /*STARTFUNCDOC ***
        	 //
        	 ===========================================================================
        	 //   Function:   setOriginalFileName()
        	 //
        	 //    Purpose:   Method to set the Original file Name
        	 //
        	 //     Inputs:   const string value
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

             void setOriginalFileName( const string );
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
			void exportFile ( const string );

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
			virtual void replaceFile ( const string, const bool &bKeepFileName = true );

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
			static GET_ImanFileUnqPtr getInstance ( const tag_t );

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
			static GET_ImanFileUnqPtr getInstance ( const string );
    };
}

#endif // GET_IMANFILE_HXX
