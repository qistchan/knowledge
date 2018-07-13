/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Folder.cxx
//
//    Purpose:   Class to dealing with folder objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_Folder.hxx>
#include <GET_TC_Logger.hxx>

//TC Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <tc/folder.h>
#include <tccore/aom.h>
#include <tccore/tctype.h>

const string logger = "get.get_tc_common.GET_Folder";

namespace get
{
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
    GET_Folder::GET_Folder ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {}

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
    void GET_Folder::insertInto ( const GET_WorkspaceObjectShrPtr wsoPtr, const int position )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Folder::insertInto" );

        stat = FL_insert ( _tag, wsoPtr->getTag(), position );
        save();

        LOG_TRACE ( logger, "END : GET_Folder::insert" );
    }

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
    void GET_Folder::remove ( const GET_WorkspaceObjectShrPtr wsoPtr )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Folder::remove" );

        stat = FL_remove ( _tag, wsoPtr->getTag() );
        save();

        LOG_TRACE ( logger, "END : GET_Folder::remove" );
    }

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
    GET_FolderUnqPtr GET_Folder::create ( const string sObjectType, const string sfolderName, const string sfolderDecs )
    {
        GET_FolderUnqPtr folderPtr;

        ResultCheck stat;

        tag_t tfolderTag = NULLTAG;
        tag_t tfolderInputTag = NULLTAG;
        tag_t tFolderBOtag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_Folder::create" );

        stat = TCTYPE_find_type ( sObjectType.c_str(), NULL, &tfolderTag );
        if ( tfolderTag == NULLTAG )
        {
            string sMsg = string ( "Given Type " ) + sObjectType + " does not exist";
            THROW ( sMsg );
        }
        stat = TCTYPE_construct_create_input ( tfolderTag, &tfolderInputTag );
        stat = AOM_set_value_string ( tfolderInputTag, OBJECT_NAME_ATTR, sfolderName.c_str() );
        stat = AOM_set_value_string ( tfolderInputTag, OBJECT_DESC_ATTR, sfolderDecs.c_str() );
        stat = TCTYPE_create_object ( tfolderInputTag, &tFolderBOtag );

        folderPtr = make_unique<GET_Folder> ( GET_DUMMY::GET_DUMMY_VALUE, tFolderBOtag ) ;
        folderPtr->save();

        LOG_TRACE ( logger, "END : GET_Folder::create" );

        return folderPtr;
    }

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
    GET_FolderUnqPtr GET_Folder::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_Folder::getInstance(tTag)\n" );

        if ( ! isDescendant ( tTag, FOLDER_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + FOLDER_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_Folder::getInstance(tTag)\n" );

        return make_unique<GET_Folder> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
    //   Return  :   The GET_Folder Smart Pointer object is returned
    //
    //   History:
    //      Who                    Date                 Description
    //   TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_FolderUnqPtr GET_Folder::getInstance(const string sUID)
    {
        LOG_TRACE ( logger, "START : GET_Folder::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_Folder::getInstance(sUID)\n" );

        return getInstance ( tObjectTag );
    }
}
