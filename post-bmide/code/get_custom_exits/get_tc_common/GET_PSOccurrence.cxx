
 /* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_PSOccurrence.cxx
 //
 //    Purpose:   Class for dealing with GET_PSOccurrence objects
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     21 Mar, 2016         Initial creation
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_PSOccurrence.hxx>
#include <GET_NoteType.hxx>
#include <GET_BOMViewRevision.hxx>
#include <GET_Utils.hxx>
#include <GET_TC_Attributes.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <ps/ps.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/item.h>
#include <tccore/aom.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_PSOccurrence";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_PSOccurrence
	 //
	 //    Purpose:   Constructor for the class GET_PSOccurrence
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag - The Tag of this Teamcenter PSOccurrence Object
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
    GET_PSOccurrence::GET_PSOccurrence ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag )
    {
        parentBVRPtr = make_unique<GET_BOMViewRevision> ( GET_DUMMY::GET_DUMMY_VALUE, ( getPropertyTag ( PARENT_BVR_ATTR ) )->getTag() );
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_PSOccurrence
	 //
	 //    Purpose:   Destructor for the class GET_PSOccurrence
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
    GET_PSOccurrence::~GET_PSOccurrence() {};


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
	 //     Return:   The GET_PSOccurrence Smart Pointer Instance for the given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_PSOccurrenceUnqPtr GET_PSOccurrence::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_PSOccurrence::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, PSOCCURRENCE_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + PSOCCURRENCE_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_PSOccurrence::getInstance(tTag)" );

		return make_unique<GET_PSOccurrence> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
	 //    Outputs:   None
	 //
     //     Return:   The GET_PSOccurrence Smart Pointer Instance for the given UID
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_PSOccurrenceUnqPtr GET_PSOccurrence::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_PSOccurrence::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );

		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_PSOccurrence::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getWsObject()
	 //
	 //    Purpose:   Method to get the Child workspace Object
	 //
	 //     Inputs:   none
	 //
	 //    Outputs:   none
	 //
	 //     Return:   The GET_WorkspaceObject Smart Pointer Instance for this Occurrence
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     18 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_WorkspaceObjectUnqPtr GET_PSOccurrence::getWsObject()
    {
        ResultCheck stat;

        tag_t tChildItem = NULLTAG;
        tag_t tChildBv = NULLTAG;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::getWsObject" );

        // Get the Child Item from Occurrence tag
        stat = PS_ask_occurrence_child ( parentBVRPtr->getTag(), _tag, &tChildItem, &tChildBv );

        LOG_TRACE ( logger, "END : GET_PSOccurrence::getWsObject" );

        return make_unique<GET_WorkspaceObject> ( GET_DUMMY::GET_DUMMY_VALUE, tChildItem );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   deleteOccurrence()
     //
     //    Purpose:   Method to delete occurrence
     //
     //     Inputs:   bSave - boolean value to save
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_PSOccurrence::deleteOccurrence ( const bool &bIsBVRSaveRequired )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::deleteOccurrence" );

        stat = PS_delete_occurrence ( parentBVRPtr->getTag(), _tag );
        if ( bIsBVRSaveRequired )
        {
            parentBVRPtr->save();
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::deleteOccurrence" );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   deleteNote()
     //
     //    Purpose:   Method to delete Note
     //
     //     Inputs:   sNote - Note to delete
     //               bIsSaveRequired - boolean flag value to indicate whether save is required (Default is true)
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_PSOccurrence::deleteNote ( const string sNoteName, const bool &bIsBVRSaveRequired )
    {
        GET_NoteTypeUnqPtr noteTypePtr;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::deleteNote" );

        noteTypePtr = GET_NoteType::find ( sNoteName );
        if ( noteTypePtr.get() == NULL )
        {
            THROW ( sNoteName + " is not a valid Teamcenter Note Type" );
        }
        if ( this->doesNoteExists ( sNoteName ) )
        {
            stat = PS_delete_occurrence_note ( parentBVRPtr->getTag(), _tag, noteTypePtr->getTag() );
            if ( bIsBVRSaveRequired )
            {
                parentBVRPtr->save();
            }
        }

        LOG_TRACE ( logger, "START : GET_PSOccurrence::deleteNote" );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   doesNoteExists()
     //
     //    Purpose:   Method to know whether Note exists or not for a given Occurrence
     //
     //     Inputs:   sNoteName - The Note Name to be searched for
     //
     //    Outputs:   none
     //
     //     Return:   boolean - indicating whether the given Note Name exists or not
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    bool GET_PSOccurrence::doesNoteExists ( const string sNoteName )
    {
        bool bVerdict = false;
        set<string> sTempOccNodeList;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::doesNoteExists" );

        sTempOccNodeList = this->getNotes();
        if ( sTempOccNodeList.find ( sNoteName ) != sTempOccNodeList.end() )
        {
            bVerdict = true;
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::doesNoteExists" );

        return bVerdict;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getNotes()
     //
     //    Purpose:   Method to fetch Note Names for the given Occurrence
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   set of string denoting the Occurrence Note Types for the given Occurrence
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    set<string> GET_PSOccurrence::getNotes()
    {
        IFail *exception = NULL;

        int iNotes = 0;

        ResultCheck stat;

        set<string> sOccNoteList;

        tag_t *tNoteTypes = NULL;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::getNotes" );

        try
        {
            stat = PS_list_occurrence_notes ( parentBVRPtr->getTag(), _tag, &iNotes, &tNoteTypes );
            for ( int iIndex = 0; iIndex < iNotes; iIndex++ )
            {
                char *pcNoteName = NULL;

                stat = PS_ask_note_type_name ( tNoteTypes[iIndex], &pcNoteName );

                sOccNoteList.insert ( pcNoteName );

                MEM_free ( pcNoteName );
            }
        }
        catch ( IFail& ex )
        {
            exception = &ex;
        }

        MEM_free ( tNoteTypes );

        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::getNotes" );

        return sOccNoteList;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getNoteText()
     //
     //    Purpose:   To get Note text
     //
     //     Inputs:   sNote - Note name
     //
     //    Outputs:   none
     //
     //     Return:   The Occurrence Note Text as string
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_PSOccurrence::getNoteText ( const string sNoteName )
    {
        char *pcText = NULL;

        GET_NoteTypeUnqPtr noteTypePtr;

        ResultCheck stat;

        string sNoteValue = "";

        LOG_TRACE ( logger, "START : GET_PSOccurrence::getNoteText" );

        noteTypePtr = GET_NoteType::find ( sNoteName );
        if ( noteTypePtr.get() == NULL )
        {
            THROW ( sNoteName + " is not a valid Teamcenter Note Type" );
        }
        if ( this->doesNoteExists ( sNoteName ) )
        {
            stat = PS_ask_occurrence_note_text ( parentBVRPtr->getTag(), _tag, noteTypePtr->getTag(), &pcText );
            sNoteValue = pcText;
            MEM_free ( pcText );
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::getNoteText" );

        return sNoteValue;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getQuantity()
     //
     //    Purpose:   To get quantity
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   double - returns quantity
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    double GET_PSOccurrence::getQuantity()
    {
      double dQtyDouble = 0.0;

      ResultCheck stat;

      LOG_TRACE ( logger,"START : GET_PSOccurrence::getQuantity" );

      stat = PS_ask_occurrence_qty ( parentBVRPtr->getTag(), _tag, &dQtyDouble );

      LOG_TRACE ( logger, "END : GET_PSOccurrence::getQuantity" );

      return dQtyDouble;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getQuantityStr()
     //
     //    Purpose:   To get quantity in string format
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   string - returns quantity
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_PSOccurrence::getQuantityStr()
    {
        double dQtyDouble = 0.0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::getQuantityStr" );

        stat = PS_ask_occurrence_qty ( parentBVRPtr->getTag(), _tag, &dQtyDouble );

        /* Convert the Double to String */
        string sQtyStr = "";
        GET_numberToString ( dQtyDouble, sQtyStr );

        LOG_TRACE ( logger, "END : GET_PSOccurrence::getQuantityStr" );

        return sQtyStr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   isQuantityAR()
     //
     //    Purpose:   To know quantity is required
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   boolean - true or false
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    bool GET_PSOccurrence::isQuantityAR()
    {
        logical lVerdict = FALSE;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::isQuantityAR" );

        stat = PS_ask_occurrence_flag ( parentBVRPtr->getTag(), _tag, PS_qty_as_required, &lVerdict );

        LOG_TRACE ( logger, "END : GET_PSOccurrence::isQuantityAR" );

        return ( lVerdict == FALSE ? false : true );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setNoteText()
     //
     //    Purpose:   To set the Note Text
     //
     //     Inputs:   sNoteName - NoteName that to be set(string)
     //               sNoteValue- Value to be set for Note(string)
     //               bIsBVRSaveRequired - true or false to save the BVR(boolean)
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_PSOccurrence::setNoteText ( const string sNoteName, const string sNoteValue, const bool &bIsBVRSaveRequired )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::setNoteText" );

        if ( ! sNoteValue.empty() )
        {
            GET_NoteTypeUnqPtr noteTypePtr = GET_NoteType::find ( sNoteName );
            if ( noteTypePtr.get() == NULL )
            {
                THROW ( sNoteName + " is not a valid Teamcenter Note Type" );
            }
            stat = PS_set_occurrence_note_text ( parentBVRPtr->getTag(), _tag, noteTypePtr->getTag(), sNoteValue.c_str() );

            if ( bIsBVRSaveRequired )
            {
                parentBVRPtr->save();
            }
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::setNoteText" );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setQuantity()
     //
     //    Purpose:   To set the quantity
     //
     //     Inputs:   dQtyDouble - Quantity to set
     //               bSave      - boolean to save
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_PSOccurrence::setQuantity ( double dQtyDouble, const bool &bIsBVRSaveRequired )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::setNoteText" );

        stat = PS_set_occurrence_qty ( parentBVRPtr->getTag(), _tag, dQtyDouble );

        if ( bIsBVRSaveRequired )
        {
            parentBVRPtr->save();
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::setNoteText" );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   clearQuantityAR()
     //
     //    Purpose:   To clear the quantity as required
     //
     //     Inputs:   bSave - boolean to save
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_PSOccurrence::clearQuantityAR ( const bool &bIsBVRSaveRequired )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::clearQuantityAR" );

        if ( isQuantityAR() )
        {
            stat = PS_clear_occurrence_flag ( parentBVRPtr->getTag(), _tag, PS_qty_as_required );

            if ( bIsBVRSaveRequired )
            {
                parentBVRPtr->save();
            }
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::clearQuantityAR" );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   setQuantityAR
     //
     //    Purpose:   To set the quantity as required
     //
     //     Inputs:   bSave - boolean to save
     //
     //    Outputs:   none
     //
     //     Return:   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     25 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_PSOccurrence::setQuantityAR ( const bool &bIsBVRSaveRequired )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_PSOccurrence::setQuantityAR" );

        stat = PS_set_occurrence_flag ( parentBVRPtr->getTag(), _tag, PS_qty_as_required );

        if ( bIsBVRSaveRequired )
        {
            parentBVRPtr->save();
        }

        LOG_TRACE ( logger, "END : GET_PSOccurrence::setQuantityAR" );
    }
}
