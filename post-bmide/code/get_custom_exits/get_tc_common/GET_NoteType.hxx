
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_NoteType.hxx
//
//    Purpose:   Header class for dealing with NoteType objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     13 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_NOTETYPE_HXX
#define GET_NOTETYPE_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>

//Teamcenter Includes
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_NoteTypeUnqPtr unique_ptr<GET_NoteType>
    #define GET_NoteTypeShrPtr shared_ptr<GET_NoteType>
}

namespace get
{
    class DLLEXPORT GET_NoteType : public GET_POM_object
    {
        private:
            string sNoteName;

        public:
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
            GET_NoteType ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_NoteType();

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getName()
            //
            //   Purpose :   Method to get Note name
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   The note name is returned (string)
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     02 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            string getName() { return sNoteName; };

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
            static GET_NoteTypeUnqPtr getInstance ( const tag_t );

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
            static GET_NoteTypeUnqPtr getInstance ( const string );

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
            static GET_NoteTypeUnqPtr find ( const string );
    };
}

#endif // GET_NOTETYPE_HXX
