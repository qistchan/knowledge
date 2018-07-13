
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Participant.cxx
//
//    Purpose:   Class for dealing with GET_Participant objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     06 Apr, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#include <time.h>

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Participant.hxx>
#include <GET_TC_Attributes.hxx>

//Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tccore/item.h>
#include <tc/tc.h>
#include <tccore/tctype.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_tc_common.GET_Participant";

namespace get
{
    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   GET_Participant
	 //
	 //    Purpose:   Constructor for the class GET_Participant
	 //
	 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
	 //               tTag    - The Tag of this Teamcenter Participant Object
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
    GET_Participant::GET_Participant ( const GET_DUMMY enDummy, const tag_t tTag) : GET_POM_object ( enDummy, tTag ) {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   ~GET_Participant
	 //
	 //    Purpose:   Destructor for the class GET_Participant
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
    GET_Participant::~GET_Participant() {};

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   getInstance (tTag)
	 //
	 //    Purpose:   Method to get the instance of this class using tag_t
	 //
	 //     Inputs:    tTag - tag of the object
	 //
	 //    Outputs:   none
	 //
	 //     Return:    The GET_Participant -Smart Pointer Instance for the given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ParticipantUnqPtr GET_Participant::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_Participant::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, PARTICIPANT_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + PARTICIPANT_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_Participant::getInstance(tTag)" );

		return make_unique<GET_Participant> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //     Return:   The GET_Participant -Smart Pointer Instance for the given UID
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_ParticipantUnqPtr GET_Participant::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_Participant::getInstance(sUID)" );

		tag_t tObjectTag = getTagFromUID ( sUID );

		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_Participant::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getParticipantType()
     //
     //    Purpose:   Method to get the Participant Type for this Participant
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   The Participant Type for this Participant (string)
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     06 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_Participant::getParticipantType()
    {
        char *pcParticipantName = NULL;

        ResultCheck stat;

        string sParticipantName = "";

        tag_t tParticipantTypeTag = NULLTAG;

        // Get the Participant Type
        stat = TCTYPE_ask_object_type ( _tag, &tParticipantTypeTag );
        stat = TCTYPE_ask_name2 ( tParticipantTypeTag, &pcParticipantName );

        if ( pcParticipantName != NULL )
        {
        	sParticipantName = pcParticipantName;
        	MEM_free ( pcParticipantName );
        }

        return sParticipantName;
    }

    /*STARTFUNCDOC ***
   	 //
   	 ===========================================================================
   	 //   Function:   getAssignee()
   	 //
   	 //    Purpose:   Method to get assignee for Participant
   	 //
   	 //     Inputs:   none
   	 //
   	 //    Outputs:   none
   	 //
   	 //     Return:   GET_POM_objectUnqPtr - Smart Pointer for GET_GroupMember object
   	 //
   	 //    History:
   	 //      Who                   Date                 Description
   	 //  TCS Development Team     06 Apr, 2016         Initial creation
   	 //
   	 ===========================================================================
   	 //ENDFUNCDOC   ***/
    GET_POM_objectUnqPtr GET_Participant::getAssignee()
    {
        GET_POM_objectUnqPtr pomObjectPtr;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Participant::getAssignee" );

        pomObjectPtr = getPropertyTag ( ASSIGNEE_ATTR );

    	LOG_TRACE ( logger, "END : GET_Participant::getAssignee" );

        return pomObjectPtr;
    }

    /*STARTFUNCDOC ***
	 //
	 ===========================================================================
	 //   Function:   setAssignee()
	 //
	 //    Purpose:   Method to set assignee for Participant
	 //
	 //     Inputs:   pomObjectPtr - Smart Pointer for GET_POM_object. This can be either a GroupMember object or a ResourcePool object
	 //
	 //    Outputs:   none
	 //
	 //     Return:   none
	 //
	 //    History:
	 //      Who                   Date                 Description
	 //  TCS Development Team     06 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
	void GET_Participant::setAssignee ( const GET_POM_objectShrPtr pomObjectPtr )
	{
	    IFail *exception = NULL;

		ResultCheck stat;

		LOG_TRACE ( logger, "START : GET_Participant::setAssignee" );

		try
		{
		    lockInstanceForModification();
		    setProperty ( ASSIGNEE_ATTR, pomObjectPtr );
		}
		catch ( IFail &ex )
		{
		    exception = &ex;
		}

		// Throw the exception, if any to the calling function
		if ( exception != NULL )
		{
		    throw exception;
		}

		LOG_TRACE ( logger, "END : GET_Participant::setAssignee" );
	}

	/*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getParticipantGroupMember()
     //
     //    Purpose:   Method to get the GroupMember of the assigned participant (can be null)
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   GET_GroupMemberUnqPtr - Smart Pointer for GET_GroupMember object
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     06 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_GroupMemberUnqPtr GET_Participant::getParticipantGroupMember()
    {
        GET_POM_objectUnqPtr pomObjectPtr;

        GET_GroupMemberUnqPtr groupMemberPtr;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Participant::getParticipantGroupMember" );

        pomObjectPtr = getAssignee();
        if ( pomObjectPtr->getClassName().compare ( GROUPMEMBER_CLASS ) == 0 )
        {
            groupMemberPtr = make_unique<GET_GroupMember> ( GET_DUMMY::GET_DUMMY_VALUE, pomObjectPtr->getTag() );
        }

        LOG_TRACE ( logger, "END : GET_Participant::getParticipantGroupMember" );

        return groupMemberPtr;
    }

    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getParticipantResorcePool()
     //
     //    Purpose:   Method to get the ResourcePool of the assigned participant (can be null)
     //
     //     Inputs:   none
     //
     //    Outputs:   none
     //
     //     Return:   GET_ResourcePoolUnqPtr - Smart Pointer for GET_ResourcePool object
     //
     //    History:
     //      Who                   Date                 Description
     //  TCS Development Team     06 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_ResourcePoolUnqPtr GET_Participant::getParticipantResorcePool()
    {
        GET_POM_objectUnqPtr pomObjectPtr;

        GET_ResourcePoolUnqPtr resourcePoolPtr;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Participant::getParticipantResorcePool" );

        pomObjectPtr = getAssignee();
        if ( pomObjectPtr->getClassName().compare ( RESOURCEPOOL_CLASS ) == 0 )
        {
            resourcePoolPtr = make_unique<GET_ResourcePool> ( GET_DUMMY::GET_DUMMY_VALUE, pomObjectPtr->getTag() );
        }

        LOG_TRACE ( logger, "END : GET_Participant::getParticipantResorcePool" );

        return resourcePoolPtr;
    }
}
