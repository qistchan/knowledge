
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Person.hxx
//
//    Purpose:   Header class for dealing with GET_Person objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016         Initial creation
//  TCS Development Team     01 Jun, 2017         Added find method to find existing person
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_PERSON_HXX
#define GET_PERSON_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_application_object.hxx>

//Teamcenter Includes
#include <sa/groupmember.h>
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_PersonUnqPtr unique_ptr<GET_Person>
    #define GET_PersonShrPtr shared_ptr<GET_Person>
}

namespace get
{
    class DLLEXPORT GET_Person : public GET_POM_application_object
    {
        private:
            string sName;
            string sEmail;

        public:

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   GET_Person
             //
             //    Purpose:   Construcfor for the class GET_Person
             //
             //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
             //     Inputs:   tTag - The Tag of the Teamcenter Person Object
             //
             //    Outputs:   none
             //
             //     Return:   none
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            GET_Person ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   ~GET_Person
             //
             //    Purpose:   Destructor for the class GET_Person
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
            virtual ~GET_Person();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getName()
             //
             //    Purpose:   Method to get the name of this Teamcenter Person
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Name of this Person (string)
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            string getName();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getEmailId()
             //
             //    Purpose:   Method to get the EMail ID of this Teamcenter Person
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The EMail-ID of this Person (string)
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            string getEmailId();

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
             //     Return:   The GET_Person Smart Pointer Instance for the given tag
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_PersonUnqPtr getInstance ( const tag_t );

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
             //     Return:   The GET_Person Smart Pointer Instance for the given UID
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 Apr, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_PersonUnqPtr getInstance ( const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   find()
            //
            //    Purpose:   Method to find Teamcenter Person with the given name
            //
            //     Inputs:   none
            //
            //    Outputs:   none
            //
            //     Return:   The GET_Person Smart Pointer Instance of the found Teamcenter Person
            //
            //    History:
            //      Who                   Date                 Description
            //  TCS Development Team     01 Jun, 2017       Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_PersonUnqPtr find ( const string sPersonName );
    };
}

#endif // GET_PERSON_HXX
