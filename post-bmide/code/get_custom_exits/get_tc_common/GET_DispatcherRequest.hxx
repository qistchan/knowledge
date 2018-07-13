
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_DispatcherRequest.hxx
//
//    Purpose:   Class for dealing with GET_DispatcherRequest objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Apr, 2016         Initial creation
//  TCS Development Team     22 Sep, 2017         Corrected the method signatures to use typedefs for the method createInstance()
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_DISPATCHERREQUEST_HXX
#define GET_DISPATCHERREQUEST_HXX

#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

#include <GET_POM_application_object.hxx>
#include <GET_Dataset.hxx>
#include <GET_ItemRevision.hxx>

// Smart Pointer Definition
namespace get
{
    #define GET_DispatcherRequestUnqPtr unique_ptr<GET_DispatcherRequest>
    #define GET_DispatcherRequestShrPtr shared_ptr<GET_DispatcherRequest>
}

namespace get
{
    class DLLEXPORT GET_DispatcherRequest : public GET_POM_application_object
    {
        public:

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
            GET_DispatcherRequest ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_DispatcherRequest();

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
            static GET_DispatcherRequestUnqPtr getInstance ( const tag_t );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getInstance ( sUID )
             //
             //    Purpose:   Method to get the instance of this class using string UID
             //
             //     Inputs:   sUID - UID as string
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
            static GET_DispatcherRequestUnqPtr getInstance ( const string );

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   createInstance
             //
             //    Purpose:   Method to create the instance of this class 
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
             //  TCS Development Team     22 Sep, 2017         Corrected the method signatures to use typedefs
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static GET_DispatcherRequestUnqPtr createInstance ( const string, const string, const int, const GET_ItemRevisionShrPtr, const GET_DatasetShrPtr );
    };
}

#endif // GET_DISPATCHERREQUEST_HXX
