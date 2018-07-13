
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ResourcePool.cxx
//
//    Purpose:   Class for dealing with GET_ResourcePool objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     11 May, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_TC_Logger.hxx>
#include <GET_Exception.hxx>
#include <GET_ResourcePool.hxx>

// Teamcenter Includes
#include <epm/epm.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.ge_tc_common.GET_ResourcePool";

namespace get
{
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
    GET_ResourcePool::GET_ResourcePool ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag )
	{
        logical lAllowSubGroup = FALSE;

        ResultCheck stat;

        tag_t tGroupTag = NULLTAG;
        tag_t tRoleTag = NULLTAG;

        // Get the Group/Role from the Resource Pool
        stat = EPM_ask_resource_pool_group_role ( tTag, &tGroupTag, &tRoleTag, &lAllowSubGroup );
        if ( tGroupTag != NULLTAG )
        {
            groupPtr = make_shared<GET_POM_group> ( GET_DUMMY::GET_DUMMY_VALUE, tGroupTag );
        }
        if ( tRoleTag != NULLTAG )
        {
            rolePtr = make_shared<GET_Role> ( GET_DUMMY::GET_DUMMY_VALUE, tRoleTag );
        }
        bAllowSubGroup = ( lAllowSubGroup == TRUE ? true : false );
	}

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
	 //  TCS Development Team     02 May, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ResourcePool::~GET_ResourcePool(){}

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
    GET_POM_groupShrPtr GET_ResourcePool::getGroup()
    {
        return groupPtr;
    }

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
    GET_RoleShrPtr GET_ResourcePool::getRole()
    {
        return rolePtr;
    }

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
    GET_ResourcePoolUnqPtr GET_ResourcePool::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_ResourcePool::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, RESOURCEPOOL_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + RESOURCEPOOL_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_ResourcePool::getInstance(tTag)\n" );

        return make_unique<GET_ResourcePool> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

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
    GET_ResourcePoolUnqPtr GET_ResourcePool::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_ResourcePool::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_ResourcePool::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }
}
