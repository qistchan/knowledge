
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_RuntimeBusinessObject.cxx
//
//    Purpose:   Header class for defining the basic behavior of all Teamcenter Runtime Objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     22 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_RuntimeBusinessObject.hxx>
#include <GET_POM_object.hxx>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tccore/aom_prop.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_RuntimeBusinessObject";

namespace get
{
    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   GET_RuntimeBusinessObject (GET_DUMMY, tTag)
     //
     //   Purpose :   Constructor for the class GET_RuntimeBusinessObject
     //
     //   Inputs  :   enDummy - A dummy enum value (GET_DUMMY)
     //               tTag - The tag of a Runtime Business Object (tag_t)
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
    GET_RuntimeBusinessObject::GET_RuntimeBusinessObject ( const GET_DUMMY enDummy, const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_RuntimeBusinessObject::GET_RuntimeBusinessObject(GET_DUMMY, tag_t)" );
        init ( tTag );
        LOG_TRACE ( logger, "END : GET_RuntimeBusinessObject::GET_RuntimeBusinessObject(GET_DUMMY, tag_t)" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_RuntimeBusinessObject()
    //
    //   Purpose :   Destructor for the class GET_RuntimeBusinessObject
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
    GET_RuntimeBusinessObject::~GET_RuntimeBusinessObject() {};

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance (tTag)
     //
     //   Purpose :   Method to get the instance of this type using tag_t
     //
     //   Inputs  :   tTag - tag of the object
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_RuntimeBusinessObject Smart Pointer Instance for the given tag
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_RuntimeBusinessObjectUnqPtr GET_RuntimeBusinessObject::getInstance ( const tag_t tTag )
    {
        return make_unique<GET_RuntimeBusinessObject> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance (sUID)
     //
     //   Purpose :   Method to get the instance of this type using string UID
     //
     //   Inputs  :   sUID - UID as string
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_RuntimeBusinessObject Smart Pointer Instance for the given UID
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_RuntimeBusinessObjectUnqPtr GET_RuntimeBusinessObject::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_RuntimeBusinessObject::getInstance(sUID)" );

        tag_t tObjectTag = GET_POM_object::getTagFromUID ( sUID );

        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_RuntimeBusinessObject::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:  init (tTag)
     //
     //   Purpose :  Method to initialize the instance
     //
     //   Inputs  :  enDummy - A dummy enum value (GET_DUMMY)
     //              tTag - The tag of a Runtime Business Object (tag_t)
     //
     //   Outputs :  none
     //
     //   Return  :  none
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     13 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_RuntimeBusinessObject::init ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_RuntimeBusinessObject::init" );

        _tag = tTag;

        // Implement
        LOG_TRACE ( logger, "END : GET_RuntimeBusinessObject::init" );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getStringProperty()
     //
     //   Purpose :   Method to get a string Property value from the underlying BOMLine
     //
     //   Inputs  :   sAttrName - The input Property Name whose value is required (string)
     //
     //   Outputs :   none
     //
     //   Return  :   The Value for the given property (String)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     11 Feb, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_RuntimeBusinessObject::getStringProperty ( string sAttrName )
    {
        char *pcAttrValue = NULL;

        ResultCheck stat;

        string sAttrvalue = "";

        LOG_TRACE ( logger, "START : GET_RuntimeBusinessObject::getStringProperty()" );

        stat = AOM_ask_value_string ( _tag, sAttrName.c_str(), &pcAttrValue );
        if ( pcAttrValue != NULL )
        {
            sAttrvalue = pcAttrValue;
            MEM_free ( pcAttrValue );
            pcAttrValue = NULL;
        }

        LOG_TRACE ( logger, "END : GET_RuntimeBusinessObject::getStringProperty()" );

        return sAttrvalue;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getStringProperties()
     //
     //   Purpose :   Method to get a string Properties value from the underlying BOMLine
     //
     //   Inputs  :   sAttrName - The input Property Name whose value is required (string)
     //
     //   Outputs :   none
     //
     //   Return  :   The Values for the given property (vector<string>)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     11 Feb, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    vector<string> GET_RuntimeBusinessObject::getStringProperties ( string sAttrName )
    {
        char **ppcAttrValue = NULL;

        int iCount = 0;

        ResultCheck stat;

        vector<string> vAttrValues;

        LOG_TRACE ( logger, "START : GET_RuntimeBusinessObject::getStringProperty()" );

        stat = AOM_ask_value_strings ( _tag, sAttrName.c_str(), &iCount, &ppcAttrValue );
        if ( ppcAttrValue != NULL && iCount > 0 )
        {
            for ( int iIndex = 0; iIndex < iCount; iIndex++ )
            {
                if ( ppcAttrValue[iIndex] != NULL )
                {
                    vAttrValues.push_back ( ppcAttrValue[iIndex] );
                    MEM_free ( ppcAttrValue[iIndex] );
                }
            }
            MEM_free ( ppcAttrValue );
        }

        LOG_TRACE ( logger, "END : GET_RuntimeBusinessObject::getStringProperty()" );

        return vAttrValues;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getTag
     //
     //   Purpose :   Method to get underlying Teamcenter tag for this instance
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The underlying Teamcenter tag for this current instance (tag_t)
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     11 Feb, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    tag_t GET_RuntimeBusinessObject::getTag() const
    {
        return _tag;
    }
}
