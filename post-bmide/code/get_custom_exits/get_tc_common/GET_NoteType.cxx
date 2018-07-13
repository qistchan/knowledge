
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_NoteType.cxx
//
//    Purpose:   Class for dealing with NoteType objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     13 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#include <GET_NoteType.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

#include <ps/ps.h>

#include <base_utils/ResultCheck.hxx>

const string logger = "get.get_tc_common.GET_NoteType";

namespace get
{
     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   GET_NoteType (tTag)
     //
     //   Purpose :   Constructor for the class GET_NoteType
     //
     //   Inputs  :   tTag - tag of the object
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     13 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_NoteType::GET_NoteType ( const GET_DUMMY enDummy, const tag_t tTag ): GET_POM_object ( enDummy, tTag )
    {
        LOG_TRACE ( logger, "START : GET_NoteType::GET_NoteType" );

        sNoteName = getPropertyString ( NAME_ATTR );

        LOG_TRACE ( logger, "END : GET_NoteType::GET_NoteType" );
    };

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_NoteType()
    //
    //   Purpose :   Destructor for the class GET_NoteType
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
    GET_NoteType::~GET_NoteType() {};

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance (tTag)
     //
     //   Purpose :   Method to get the instance of this class using tag_t
     //
     //   Inputs  :   tTag - tag of the object
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_NoteType Smart Pointer object is returned
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     13 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_NoteTypeUnqPtr GET_NoteType::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_NoteType::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, NOTE_TYPE_CLASS ) )
        {
            string sMsg = string ("The given tag is not an instance of the class ") + NOTE_TYPE_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_NoteType::getInstance(tTag)" );

        return make_unique<GET_NoteType> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //   Return  :   The GET_NoteType Smart Pointer object is returned
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     13 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_NoteTypeUnqPtr GET_NoteType::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_NoteType::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_NoteType::getInstance(sUID)" );

        return getInstance ( tObjectTag ) ;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:  find()
     //
     //   Purpose :  Method to find a given Note Type using the Note Type Name
     //
     //   Inputs  :  sNoteName - The Note Type Name
     //
     //   Outputs :  none
     //
     //   Return  :  The GET_NoteType Smart Pointer object is returned
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     13 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_NoteTypeUnqPtr GET_NoteType::find ( const string sNoteName )
    {
        GET_NoteTypeUnqPtr noteTypePtr;

        ResultCheck stat;

        tag_t tNoteTypeTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_NoteType::find" );

        stat = PS_find_note_type ( sNoteName.c_str(), &tNoteTypeTag );
        if ( tNoteTypeTag != NULLTAG )
        {
            noteTypePtr = make_unique<GET_NoteType> ( GET_DUMMY::GET_DUMMY_VALUE, tNoteTypeTag );
        }

        LOG_TRACE ( logger, "END : GET_NoteType::find" );

        return noteTypePtr;
    }
}
