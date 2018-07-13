
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_DispatcherRequest.cxx
//
//    Purpose:   Class for dealing with GET_DispatcherRequest objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Apr, 2016         Initial creation
//  TCS Development Team     22 Sep, 2017         Corrected the spacing errors in createInstance() method
//   ============================================================================
// ENDFILEDOC   ***/
#include <GET_cpp_stl.h>
#include <GET_TC_Logger.hxx>
#include <GET_Exception.hxx>
#include <base_utils/ResultCheck.hxx>
#include <GET_DispatcherRequest.hxx>
#include <GET_Dataset.hxx>
#include <GET_ItemRevision.hxx>
#include <dispatcher/dispatcher_itk.h>

const string logger = "get_tc_common.GET_DispatcherRequest";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_DispatcherRequest
    //
    //    Purpose:   Constructor for the class GET_DispatcherRequest
    //
    //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
    //               tTag    - The Tag of this Teamcenter DispatcherRequest Object
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
    GET_DispatcherRequest::GET_DispatcherRequest ( const GET_DUMMY stDummy, const tag_t tTag ) : GET_POM_application_object ( stDummy, tTag ) {};

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   ~GET_DispatcherRequest
    //
    //    Purpose:   Destructor for the class GET_DispatcherRequest
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
    GET_DispatcherRequest::~GET_DispatcherRequest() {};

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getInstance ( tTag )
    //
    //    Purpose:   Method to get the instance of this class using tag_t
    //
    //     Inputs:   tTag - tag of the object
    //
    //    Outputs:   none
    //
    //     Return:   The GET_DispatcherRequest Smart Pointer object is returned
    //
    //    History:
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DispatcherRequestUnqPtr GET_DispatcherRequest::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_DispatcherRequest::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, DISPATCHERREQUEST_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + DISPATCHERREQUEST_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_DispatcherRequest::getInstance(tTag)" );

        return make_unique<GET_DispatcherRequest> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   createInstance
    //
    //    Purpose:   Method to create the instance of this class using the args
    //
    //     Inputs:   Provider Name, Service Name,  tag of Secondary Objects and tag of Primary objects
    //
    //    Outputs:   none
    //
    //     Return:   The GET_DispatcherRequest Smart Pointer object is returned
    //
    //    History:
    //      Who                    Date                 Description
    //  TCS Development Team     18 May, 2017         Initial creation
    //  TechM Development Team   21 Sep, 2017         Changed the function arguments to pointers
    //  TCS Development Team     22 Sep, 2017         Corrected the spacing errors in this method
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DispatcherRequestUnqPtr GET_DispatcherRequest::createInstance ( const string providerName, const string serviceName, const int priority, const GET_ItemRevisionShrPtr itemRevPtr, const GET_DatasetShrPtr datasetPtr )
    {
        GET_DispatcherRequestUnqPtr dispUnqPtr;

        ResultCheck stat;

        tag_t tDatasetTag = datasetPtr->getTag();
        tag_t tItemRevTag = itemRevPtr->getTag();
        tag_t tRequestTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_DispatcherRequest::createInstance()" );

        stat = DISPATCHER_create_request ( providerName.c_str(), serviceName.c_str(), priority, 0, 0, 0, 1, &tDatasetTag, &tItemRevTag, 0, NULL, NULL, 0, NULL, NULL, &tRequestTag );        
        if ( tRequestTag != NULLTAG )
        {
            dispUnqPtr = make_unique<GET_DispatcherRequest> ( GET_DUMMY::GET_DUMMY_VALUE, tRequestTag );
        }

        LOG_TRACE ( logger, "END : GET_DispatcherRequest::createInstance()" );

        return dispUnqPtr;    
    }
}
