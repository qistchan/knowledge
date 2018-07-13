
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Folder.hxx
//
//    Purpose:   Header class for dealing with GET_Folder objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_FOLDER_HXX
#define GET_FOLDER_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_FolderUnqPtr unique_ptr<GET_Folder>
    #define GET_FolderShrPtr shared_ptr<GET_Folder>
}

namespace get
{
    class DLLEXPORT GET_Folder : public GET_WorkspaceObject
    {
        public:
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   GET_Folder ( const GET_DUMMY, const tag_t )
            //
            //   Purpose :   Constructor for the class GET_Folder
            //
            //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
            //               tTag    - The Tag of this Teamcenter Folder Object
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
            GET_Folder ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   insertInto ( const GET_WorkspaceObjectShrPtr, const int )
            //
            //   Purpose :   Method to insert object into a folder
            //
            //   Inputs  :   wsoPtr   - Object which needs to be inserted into the folder(GET_WorkspaceObjectShrPtr)
            //               position - Position of the object to be inserted(int)
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
            void insertInto ( const GET_WorkspaceObjectShrPtr, const int );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   remove ( const GET_WorkspaceObjectShrPtr )
            //
            //   Purpose :   Method to remove object from a folder
            //
            //   Inputs  :   wsoPtr   - Object which needs to be removed from the folder(GET_WorkspaceObjectShrPtr)
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
            void remove ( const GET_WorkspaceObjectShrPtr );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   create ( const string, const string,  const string)
            //
            //   Purpose :   Method to create a folderwith the given input
            //
            //   Inputs  :   sObjectType - Type of the oject(string)
            //               sfolderName - Name of the folder(string)
            //               sfolderDecs - Description of the folder(string)
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_Folder smart pointer is returned
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     02 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_FolderUnqPtr create ( const string, const string, const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getInstance (tTag)
            //
            //   Purpose :   Method to get the instance of this class using tag_t
            //
            //   Inputs  :   tTag - tag of the Folder
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_Folder Smart Pointer object is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_FolderUnqPtr getInstance ( const tag_t );

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
            //   Return  :   The GET_Folder Smart Pointer object is returned
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     11 Apr, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_FolderUnqPtr getInstance ( const string );
    };
}

#endif // GET_FOLDER_HXX
