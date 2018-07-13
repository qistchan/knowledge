
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Person.cxx
//
//    Purpose:   Class to dealing with Person objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     24 Mar, 2016         Initial creation
//  TCS Development Team     01 Jun, 2017         Added find method to find existing person
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Person.hxx>

//Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <sa/sa.h>
#include <sa/person.h>

const string logger = "get.get_tc_common.GET_Person";

namespace get
{
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
    GET_Person::GET_Person ( GET_DUMMY enDummy, tag_t tTag ) : GET_POM_application_object ( enDummy, tTag )
    {
        ResultCheck stat;

        char *pcName = NULL;
        char *pcEmail = NULL;

        stat = SA_ask_person_name2 ( tTag, &pcName );
        sName = pcName;
        MEM_free ( pcName );

        stat = SA_ask_person_email_address ( tTag, &pcEmail );
        sEmail = pcEmail;
        MEM_free ( pcEmail );
    }

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
    GET_Person::~GET_Person() {};

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
    GET_PersonUnqPtr GET_Person::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_Person::getInstance(tTag)" );

        if ( ! isDescendant(tTag, PERSON_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + PERSON_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_Person::getInstance(tTag)" );

        return make_unique<GET_Person> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

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
   GET_PersonUnqPtr GET_Person::find ( const string sPersonName )
   {
       GET_PersonUnqPtr personPtr;

       ResultCheck stat;

       tag_t tPersonTag = NULLTAG;

       LOG_TRACE ( logger, "START : GET_Person::find" );

       stat = SA_find_person2 ( sPersonName.c_str(), &tPersonTag );
       if ( tPersonTag != NULLTAG )
       {
           personPtr = make_unique<GET_Person> ( GET_DUMMY::GET_DUMMY_VALUE, tPersonTag );
       }

       LOG_TRACE ( logger, "END : GET_Person::find" );

       return personPtr;
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
    GET_PersonUnqPtr GET_Person::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_Person::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_Person::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }

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
    string GET_Person::getName()
    {
        return sName;
    }

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
    string GET_Person::getEmailId()
    {
        return sEmail;
    }
}
