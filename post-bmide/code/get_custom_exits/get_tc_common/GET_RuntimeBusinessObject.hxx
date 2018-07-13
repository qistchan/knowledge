
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_RuntimeBusinessObject.hxx
//
//    Purpose:   Header class for defining the basic behavior of all Teamcenter Runtime Objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     22 Apr, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_RUNTIME_BO_HXX
#define GET_RUNTIME_BO_HXX

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>
#include <fclasses/tc_date.h>

// Smart Pointer Definition
namespace get
{
    #define GET_RuntimeBusinessObjectUnqPtr unique_ptr<GET_RuntimeBusinessObject>
    #define GET_RuntimeBusinessObjectShrPtr shared_ptr<GET_RuntimeBusinessObject>
}

// Class Definition
namespace get
{
    class DLLEXPORT GET_RuntimeBusinessObject
    {
        private:
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
            void init ( const tag_t );

        protected:
            tag_t _tag;
            enum GET_DUMMY { GET_DUMMY_VALUE }; // DUMMY Enum to make sure that only classes within the hierarchy can use constructors

        public:
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
            GET_RuntimeBusinessObject ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_RuntimeBusinessObject();

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
            tag_t getTag() const;

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
            string getStringProperty ( string sAttrName );

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
            vector<string> getStringProperties ( string sAttrName );

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
            static GET_RuntimeBusinessObjectUnqPtr getInstance ( const tag_t );

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
            static GET_RuntimeBusinessObjectUnqPtr getInstance ( const string );
    };
}

#endif // GET_RUNTIME_BO_HXX
