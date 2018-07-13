
/* STARTFILEDOC ***
  //   ===========================================================================
  //   Filename:   GET_PSOccurrence.hxx
  //
  //    Purpose:   Class for dealing with GET_PSOccurrence objects
  //
  //    History:
  //      Who                   Date                 Description
  //  TCS Development Team     21 Mar, 2016         Initial creation
  //
  //   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_PSOCCURRENCE_HXX
#define GET_PSOCCURRENCE_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>
#include <GET_POM_object.hxx>

//CPP Includes
#include <string>
#include <vector>
#include <set>

// Smart Pointer Definition
namespace get
{
    #define GET_PSOccurrenceUnqPtr unique_ptr<GET_PSOccurrence>
    #define GET_PSOccurrenceShrPtr shared_ptr<GET_PSOccurrence>
}

namespace get
{
    class GET_BOMViewRevision;
    class DLLEXPORT GET_PSOccurrence : public GET_POM_object
    {
        private:
            set<tag_t> sOccNoteTagList;
            set<string> sOccNoteList;

            unique_ptr<GET_BOMViewRevision> parentBVRPtr;

        public:

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
            GET_PSOccurrence ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_PSOccurrence();

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
            static GET_PSOccurrenceUnqPtr getInstance ( const tag_t );

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
            static GET_PSOccurrenceUnqPtr getInstance ( const string );

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
            GET_WorkspaceObjectUnqPtr getWsObject();

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
            virtual void deleteOccurrence ( const bool &bIsBVRSaveRequired = true );

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
            void deleteNote ( const string, const bool &bIsBVRSaveRequired = true );

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
            virtual bool doesNoteExists ( const string );

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
            virtual set<string> getNotes();

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
            virtual string getNoteText ( const string );

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
            virtual double getQuantity();

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
            virtual string getQuantityStr();

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
            virtual bool isQuantityAR();

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
            virtual void setNoteText ( const string, const string, const bool &bIsBVRSaveRequired = true );

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
            void setQuantity ( const double, const bool &bIsBVRSaveRequired = true );

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
            virtual void setQuantityAR ( const bool &bIsBVRSaveRequired = true );

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
            virtual void clearQuantityAR ( const bool &bIsBVRSaveRequired = true );
   };
}

#endif // GET_PSOCCURRENCE_HXX
