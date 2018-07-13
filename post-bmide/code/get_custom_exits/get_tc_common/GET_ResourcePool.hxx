
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ResourcePool.hxx
//
//    Purpose:   Header class for dealing with GET_ResourcePool objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 May, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_RESOURCEPOOL_HXX
#define GET_RESOURCEPOOL_HXX

#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

#include <GET_POM_object.hxx>
#include <GET_POM_group.hxx>
#include <GET_Role.hxx>

// Smart Pointer Definition
namespace get
{
    #define GET_ResourcePoolUnqPtr unique_ptr<GET_ResourcePool>
    #define GET_ResourcePoolShrPtr shared_ptr<GET_ResourcePool>
}

namespace get
{
    class DLLEXPORT GET_ResourcePool : public GET_POM_object
    {
        private:

            bool bAllowSubGroup; // Variable to denote whether this Resource Pool allows Sub Groups

            GET_POM_groupShrPtr groupPtr; // Handle for the Group object of this Resource Pool
            GET_RoleShrPtr rolePtr; // Handle for the Role object of this Resource Pool

        public:

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_ResourcePool
			 //
			 //    Purpose:   Constructor for the class GET_ResourcePool
			 //
			 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
			 //               tTag - The Tag of this Teamcenter ResourcePool Object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 May, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_ResourcePool ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_ResourcePool
			 //
			 //    Purpose:   Destructor for the class GET_ResourcePool
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 May, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual ~GET_ResourcePool();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getGroup()
             //
             //    Purpose:   Method to get the Group associated with this ResourcePool
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Smart Pointer instance of the GET_POM_group associated with this ResourcePool
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 May, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            virtual GET_POM_groupShrPtr getGroup();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getRole()
             //
             //    Purpose:   Method to get the Role associated with this ResourcePool
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Smart Pointer instance of the GET_Role associated with this ResourcePool
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 May, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            virtual GET_RoleShrPtr getRole();

            /*STARTFUNCDOC ***
             //
             ===========================================================================
             //   Function:   getRole()
             //
             //    Purpose:   Method to get the Role associated with this ResourcePool
             //
             //     Inputs:   none
             //
             //    Outputs:   none
             //
             //     Return:   The Smart Pointer instance of the GET_Role associated with this ResourcePool
             //
             //    History:
             //      Who                    Date                 Description
             //  TCS Development Team     11 May, 2016         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            virtual bool isSubGroupAllowed() { return bAllowSubGroup; }

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   getInstance (tTag)
            //
            //   Purpose :   Method to get the instance of this class using tag_t
            //
            //   Inputs  :   tTag - tag of the Resource Pool
            //
            //   Outputs :   none
            //
            //   Return  :   The GET_ResourcePool Smart Pointer object is returned
            //
            //   History :
            //      Who                    Date                 Description
            //   TCS Development Team     12 Jul, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_ResourcePoolUnqPtr getInstance ( const tag_t );

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
            //   Return  :   The GET_ResourcePool Smart Pointer object is returned
            //
            //   History:
            //      Who                    Date                 Description
            //   TCS Development Team     12 Jul, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_ResourcePoolUnqPtr getInstance ( const string );
    };
}

#endif // GET_RESOURCEPOOL_HXX
