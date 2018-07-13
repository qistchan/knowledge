
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Form.cxx
//
//    Purpose:   Class for dealing with Form objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     18 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_Form.hxx>
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Utils.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tccore/item.h>
#include <tc/tc_errors.h>
#include <tccore/grm.h>
#include <tccore/aom.h>
#include <form/form.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <tccore/tctype.h>

const string logger = "get.get_tc_common.GET_Form";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_Form ( const GET_DUMMY, const tag_t )
    //
    //   Purpose :   Constructor for the class GET_Form
    //
    //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
    //               tTag    - The Tag of this Teamcenter Form Object
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
    GET_Form::GET_Form ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {};

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_Form()
    //
    //   Purpose :   Destructor for the class GET_Form
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
    GET_Form::~GET_Form() {};

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance(tTag)
    //
    //    Purpose:   Method to Get the GET_Form Smart Pointer instance from the give the tag
    //
    //    Inputs:    tTag - The Teamcenter tag of the Input Form Object (tag_t)
    //
    //    Outputs:   none
    //
    //    Return:    The GET_Form smart pointer for the the given tag
    //
    //     History:
    //      Who                   Date                 Description
    //  TCS Development Team     22 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_FormUnqPtr GET_Form::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_Form::getInstance(tTag)" );

        if(! isDescendant(tTag, FORM_CLASS ))
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + FORM_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_Form::getInstance(tTag)" );

        return make_unique<GET_Form> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance(sUID)
    //
    //    Purpose:   Method to Get the GET_Form Smart Pointer instance from the give the UID
    //
    //    Inputs:    sUID - The Teamcenter UID of the Input Form Object (string)
    //
    //    Outputs:   none
    //
    //    Return:    The GET_Form smart pointer for the the given UID
    //
    //     History:
    //      Who                   Date                 Description
    //  TCS Development Team     22 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_FormUnqPtr GET_Form::getInstance(const string sUID)
    {
        LOG_TRACE ( logger, "START : GET_Form::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_Form::getInstance(sUID)" );

        return getInstance(tObjectTag);;
    }

	 /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getDataFile()
	 //
	 //    Purpose:   Method to Get Data File Object for this Form
	 //
	 //    Inputs:    none
	 //
	 //    Outputs:   none
	 //
	 //    Return:    The GET_POM_object smart pointer for the Data File Object for this form
	 //
	 // 	History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     22 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_POM_objectUnqPtr GET_Form::getDataFile ( void )
     {
        GET_POM_objectUnqPtr dataFilePtr;

         ResultCheck stat;

         logical isNull = false;
         logical isEmpty = false;
         logical isFormLoaded = false;

         tag_t dataFileTag = NULLTAG;
         tag_t dataFileAttr = NULLTAG;
         tag_t tempTag = NULLTAG;

         LOG_TRACE ( logger, "START : GET_Form::getDataFile" );

         dataFilePtr = getPropTag ( DATAFILE_ATTR );

         LOG_TRACE ( logger, "[GET] END : GET_Form::getDataFile \n" );

         return dataFilePtr;
    }

	 /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   setDataFile()
	 //
	 //    Purpose:   Method to set Data File for this Form
	 //
	 //    Inputs:    dataFilePtr - The GET_POM_object Smart Pointer for the Data File Object to be set for this Form
	 //
	 //    Outputs:   none
	 //
	 //    Return:    none
	 //
	 // 	History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     22 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    void GET_Form::setDataFile ( const GET_POM_objectShrPtr dataFilePtr )
    {
        LOG_TRACE ( logger, "START : GET_Form::createDataFile" );

        setProperty ( DATAFILE_ATTR, dataFilePtr );

        LOG_TRACE ( logger, "END : GET_Form::createDataFile" );
    }

	 /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   createForm()
	 //
	 //    Purpose:   Method to create form
	 //
	 //    Inputs:    sFormName - The Form Name (string)
	 //				  sFormDescription - The Description to be set for the Form (string)
	 //				  sFormType	- The Form Type to be created (string)
	 //
	 //    Outputs:   none
	 //
	 //    Return:    The GET_Form Smart Pointer instance for the newly created Form
	 //
	 // 	History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     22 Mar, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_FormUnqPtr GET_Form::createForm ( const string sFormName, const string sFormDescription, const string sFormType)
    {
        GET_FormUnqPtr formPtr;

		ResultCheck stat;

		tag_t tFormTag = NULLTAG;
		tag_t tCreateFormTag = NULLTAG;
		tag_t tFormBOtag =NULLTAG;

		LOG_TRACE ( logger ,"START : GET_Form::Create" );

        stat = TCTYPE_find_type ( sFormType.c_str(), NULL, &tFormTag );
        if ( tFormTag == NULLTAG )
        {
            string sMsg = string ( "Given Type " ) + sFormType + " does not exist";
            THROW ( sMsg );
        }

		stat = TCTYPE_construct_create_input ( tFormTag , &tCreateFormTag );
		stat = AOM_set_value_string ( tCreateFormTag, OBJECT_NAME_ATTR, sFormName.c_str() );
		stat = AOM_set_value_string ( tCreateFormTag, OBJECT_DESC_ATTR, sFormDescription.c_str() );
		stat = TCTYPE_create_object ( tCreateFormTag, &tFormBOtag );

		formPtr = make_unique<GET_Form> ( GET_DUMMY::GET_DUMMY_VALUE, tFormBOtag  );
		formPtr->save();

		LOG_TRACE ( logger ,"End : GET_Form::Create" );

		return formPtr;
    }
}
