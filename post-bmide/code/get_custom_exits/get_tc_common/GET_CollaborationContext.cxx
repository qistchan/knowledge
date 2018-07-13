
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_CollaborationContext.cxx
//
//    Purpose:   Class to dealing with Teamcenter Collaboration Context objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_sysapi.h>
#include <GET_Utils.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_CollaborationContext.hxx>
#include <GET_Item.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_TC_Attributes.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/item.h>
#include <tccore/tctype.h>
#include <epm/epm_toolkit_tc_utils.h>
#include <ps/ps.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <collabctx/collabctx.h>

const string logger = "get.get_tc_common.GET_CollaborationContext";

namespace get
{    
	/*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_CollaborationContext
	 //
	 //    Purpose:   Constructor for the class GET_CollaborationContext
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag    - The Tag of this Teamcenter Item Revision Object
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
    GET_CollaborationContext::GET_CollaborationContext ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_WorkspaceObject ( enDummy, tTag ) {}

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_CollaborationContext
	 //
	 //    Purpose:   Destructor for the class GET_CollaborationContext
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
    GET_CollaborationContext::~GET_CollaborationContext() {};
	
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
     //     Return:   The GET_CollaborationContext Smart Pointer object is returned
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team       01 Dec, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_CollaborationContextUnqPtr GET_CollaborationContext::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_CollaborationContext::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, COLLABORATIONCONTEXT_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + COLLABORATIONCONTEXT_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_CollaborationContext::getInstance(tTag)" );

        return make_unique<GET_CollaborationContext> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
    }

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
     //     Return:   The GET_CollaborationContext Smart Pointer object is returned
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team       01 Dec, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_CollaborationContextUnqPtr GET_CollaborationContext::getInstance ( const string sUID )
    {
        tag_t tObjectTag = getTagFromUID ( sUID );
        LOG_TRACE ( logger, "START : GET_CollaborationContext::getInstance(sUID)" );

        if ( tObjectTag == NULLTAG )
        {
            THROW(sUID + " is not a valid Teamcenter UID");
        }

        LOG_TRACE ( logger, "END : GET_CollaborationContext::getInstance(sUID)" );

        return getInstance ( tObjectTag );

    }
	
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   createConfigContext ( const string, const string, const string )
    //
    //   Purpose :   Method to create configuration context for given name
    //
    //   Inputs  :   Type name - can be empty - will take default type
    //               Name of the ConfigurationContext
    //               Description of the ConfigurationContext
    //
    //   Outputs :   Unique pointer of ConfigurationContext instance
    //
    //   Return  :   The GET_CollaborationContext Smart Pointer instance of Collaboration Context Object
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team       01 Dec, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_CollaborationContextUnqPtr GET_CollaborationContext::createConfigContext ( const string configContextType,
		const string configContextName, const string configContextDesc )
    {
        ResultCheck stat;
		tag_t configContextTag = NULLTAG;
		GET_CollaborationContextUnqPtr configCnxtUnqPtr;

		LOG_TRACE ( logger, "START: GET_CollaborationContext::createConfigContext" );

		stat = COLLABCTX_create_configuration_context ( configContextType.c_str(), configContextName.c_str(),
			configContextDesc.c_str(), &configContextTag );
		
		// Construct a Smart Pointer for the new Config Context Object
		configCnxtUnqPtr = make_unique<GET_CollaborationContext> ( GET_DUMMY::GET_DUMMY_VALUE, configContextTag );

        LOG_TRACE ( logger, "END : GET_CollaborationContext::createConfigContext" );

        return configCnxtUnqPtr;
    }
	
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setConfigRevRule ( GET_CollaborationContextShrPtr, GET_RevisionRuleShrPtr )
    //
    //   Purpose :   Method to set configuration revision rule
    //
    //   Inputs  :   Share pointer of Config Context & Revision Rule
    //
    //   Outputs :   None
    //
    //   Return  :   None
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team       01 Dec, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_CollaborationContext::setConfigRevRule ( GET_CollaborationContextShrPtr configContextShrPtr, GET_RevisionRuleShrPtr revRuleShrPtr )
    {
        ResultCheck stat;
        LOG_TRACE ( logger, "START: GET_CollaborationContext::setConfigRevRule" );

		stat = COLLABCTX_configuration_set_revisionrule ( configContextShrPtr->getTag(), revRuleShrPtr->getTag() );
		
        LOG_TRACE ( logger, "END : GET_CollaborationContext::setConfigRevRule" );
    }
	
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   createStructContext ( const string, const string, const string )
    //
    //   Purpose :   Method to create Structure Context
    //
    //   Inputs  :   structContextType, structContextName, structContextDesc
    //
    //   Outputs :   None
    //
    //   Return  :   Unique pointer of created Structure context
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team       01 Dec, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_CollaborationContextUnqPtr GET_CollaborationContext::createStructContext ( const string structContextType,
		const string structContextName, const string structContextDesc )
    {
	    ResultCheck stat;
		tag_t structContextTag = NULLTAG;
		GET_CollaborationContextUnqPtr structCnxtUnqPtr;

		LOG_TRACE ( logger, "START: GET_CollaborationContext::createStructContext" );

		stat = COLLABCTX_create_structure_context ( structContextType.c_str(), structContextName.c_str(),
		        structContextDesc.c_str(), &structContextTag );
		
		// Construct a Smart Pointer for the new Structure Context Object
		structCnxtUnqPtr = make_unique<GET_CollaborationContext> ( GET_DUMMY::GET_DUMMY_VALUE, structContextTag );

        LOG_TRACE ( logger, "END : GET_CollaborationContext::createStructContext" );

        return structCnxtUnqPtr;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   addContextContent ( GET_CollaborationContextShrPtr structCnxtShrPtr, vector<GET_WorkspaceObjectShrPtr>, int )
    //
    //   Purpose :   Method to add Context Content
    //
    //   Inputs  :   Share pointer of Struct Context and Component, subType
    //
    //   Outputs :   None
    //
    //   Return  :   None
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team       01 Dec, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
	void GET_CollaborationContext::addContextContent ( GET_CollaborationContextShrPtr structCnxtShrPtr, vector<GET_WorkspaceObjectShrPtr> componentShrPtr, int subType )
    {
	    ResultCheck stat;
	    LOG_TRACE ( logger, "START: GET_CollaborationContext::addContextContent" );

		stat = COLLABCTX_context_add_content ( structCnxtShrPtr->getTag(), componentShrPtr[0]->getTag(), subType );
		
        LOG_TRACE ( logger, "END : GET_CollaborationContext::addContextContent" );
    }
	
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setConfigContext ( tag_t, tag_t )
    //
    //   Purpose :   Method to set configuration context
    //
    //   Inputs  :   Share pointer of Struct Context and Config Context
    //
    //   Outputs :   None
    //
    //   Return  :   None
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team       01 Dec, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
	void GET_CollaborationContext::setConfigContext ( GET_CollaborationContextShrPtr structCnxtShrPtr, GET_CollaborationContextShrPtr configCnxtShrPtr)
    {
	    ResultCheck stat;
	    LOG_TRACE ( logger, "START: GET_CollaborationContext::setConfigContext" );

		stat = COLLABCTX_context_set_config_context ( structCnxtShrPtr->getTag(), configCnxtShrPtr->getTag() );
		
        LOG_TRACE ( logger, "END : GET_CollaborationContext::setConfigContext" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   createCollaborationCntx ( const string, const string, const string )
    //
    //   Purpose :   Method to create CC Object
    //
    //   Inputs  :   ccType, ccName, ccDesc
    //
    //   Outputs :   None
    //
    //   Return  :   Unique pointer of created Collaboration context
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team       01 Dec, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
	GET_CollaborationContextUnqPtr GET_CollaborationContext::createCollaborationCntx ( const string ccType, const string ccName, const string ccDesc )
    {
	    ResultCheck stat;
		tag_t ccObjectTag = NULLTAG;
		GET_CollaborationContextUnqPtr clbCnxtUnqPtr;

		LOG_TRACE ( logger, "START: GET_CollaborationContext::createCollaborationCntx" );

		stat = COLLABCTX_create_ccobject ( ccType.c_str(), ccName.c_str(), ccDesc.c_str(), &ccObjectTag );
		
        // Construct a Smart Pointer for the new Collaboration Context Object
		clbCnxtUnqPtr = make_unique<GET_CollaborationContext> ( GET_DUMMY::GET_DUMMY_VALUE, ccObjectTag );

        LOG_TRACE ( logger, "END : GET_CollaborationContext::createConfigContext" );

        return clbCnxtUnqPtr;
    }
	
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   addStructContent ( GET_CollaborationContextShrPtr, GET_CollaborationContextShrPtr )
    //
    //   Purpose :   Method to add Structure Content
    //
    //   Inputs  :   Share pointer of Collaboration context & Component Context
    //
    //   Outputs :   None
    //
    //   Return  :   None
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team       01 Dec, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
	void GET_CollaborationContext::addStructContent( GET_CollaborationContextShrPtr clbCnxtShrPtr, GET_CollaborationContextShrPtr componentContextShrPtr )
    {
	    ResultCheck stat;
	    LOG_TRACE ( logger, "START: GET_CollaborationContext::addStructContent" );

		stat = COLLABCTX_add_structure_context ( clbCnxtShrPtr->getTag(), componentContextShrPtr->getTag() );
		
        LOG_TRACE ( logger, "END : GET_CollaborationContext::addStructContent" );
    }
	
}


