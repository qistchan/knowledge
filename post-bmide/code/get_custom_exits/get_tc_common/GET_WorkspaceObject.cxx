
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_WorkspaceObject.cxx
 //
 //    Purpose:   Class for dealing with GET_WorkspaceObject objects
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     25 Mar, 2016         Initial creation
 //  Ganesh Ubale             12 Sep, 2017         Added Method getAWCUrl() to get active workspace link of object
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_POM_user.hxx>
#include <GET_POM_group.hxx>

//TC Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <tccore/tctype.h>
#include <tccore/workspaceobject.h>
#include <tccore/grm.h>
#include <cxpom/cxpom_errors.h>
#include <tccore/item.h>
#include <res/reservation.h>
#include <base_utils/ResultCheck.hxx>

#include <GET_WorkspaceObject.hxx>

const string logger = "get.get_tc_common.GET_WorkspaceObject";

namespace get
{
     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   GET_WorkspaceObject ( const GET_DUMMY, const tag_t )
     //
     //   Purpose :   Constructor for the class GET_WorkspaceObject
     //
     //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
     //               tTag - The Tag of this Teamcenter BOMView Object
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
    GET_WorkspaceObject::GET_WorkspaceObject ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_application_object ( enDummy, tTag )
    {
        LOG_TRACE ( logger, "START : GET_WorkspaceObject::GET_WorkspaceObject" );

        char *pcName = NULL;
        char *pcType = NULL;
        char *pcDesc = NULL;

        ResultCheck stat;

        stat = WSOM_ask_name2 ( tTag, &pcName );
        sName = pcName;
        MEM_free ( pcName );

        stat = WSOM_ask_object_type2 ( tTag, &pcType );
        sType = pcType;
        MEM_free ( pcType );

        stat = WSOM_ask_description2 ( tTag, &pcDesc );
        sDesc = pcDesc;
        MEM_free ( pcDesc );

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::GET_WorkspaceObject" );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   getInstance (tTag)
     //
     //   Purpose :   Method to get the instance of this class using tag_t
     //
     //   Inputs  :   tTag - tag of the object
     //
     //   Outputs :   none
     //
     //   Return  :   The GET_WorkspaceObject Smart Pointer Instance for the given tag
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_WorkspaceObjectUnqPtr GET_WorkspaceObject::getInstance ( const tag_t tTag )
    {
        LOG_TRACE ( logger, "START : GET_WorkspaceObject::getInstance(tTag)" );

        if ( ! isDescendant ( tTag, WORKSPACEOBJECT_CLASS ) )
        {
            string sMsg = string ( "The given tag is not an instance of the class " ) + WORKSPACEOBJECT_CLASS;
            THROW ( sMsg );
        }

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::getInstance(tTag)" );

        return make_unique<GET_WorkspaceObject> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //   Return  :   The GET_WorkspaceObject Smart Pointer Instance for the given UID
     //
     //     History:
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_WorkspaceObjectUnqPtr GET_WorkspaceObject::getInstance ( const string sUID )
    {
        LOG_TRACE ( logger, "START : GET_WorkspaceObject::getInstance(sUID)" );

        tag_t tObjectTag = getTagFromUID ( sUID );
        if ( tObjectTag == NULLTAG )
        {
            THROW ( sUID + " is not a valid Teamcenter UID" );
        }

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::getInstance(sUID)" );

        return getInstance ( tObjectTag );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   ~GET_WorkspaceObject
     //
     //   Purpose :   Virtual Destructor
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //    History:
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_WorkspaceObject::~GET_WorkspaceObject(){}

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   toString()
     //
     //   Purpose :   Method to represent object as string
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The object represented as string is returned(string)
     //
     //   History :
     //      Who                    Date                 Description
     //  TCS Development Team     11 Apr, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_WorkspaceObject::toString (void)
    {
        char *pcObjectID = NULL;

        ResultCheck stat;

        string sString = "";

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::toString" );

        stat = WSOM_ask_object_id_string ( _tag, &pcObjectID );

        if ( pcObjectID != NULL )
        {
        	sString = pcObjectID;
        	MEM_free ( pcObjectID );
        }

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::toString" );

        return sString;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getReleaseStatusCount
    //
    //   Purpose :   Method to get ReleaseStatusCount in the object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   Number of release status applied to object (int)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    int  GET_WorkspaceObject::getReleaseStatusCount()
    {
        int iReleaseStatusCount = 0;

        ResultCheck stat;

        tag_t *tReleaseSatus = NULL;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::getReleaseStatusCount" );

        stat = WSOM_ask_release_status_list ( _tag, &iReleaseStatusCount, &tReleaseSatus );

        MEM_free ( tReleaseSatus );

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::getReleaseStatusCount" );

        return iReleaseStatusCount;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getType()
    //
    //   Purpose :   Method to get the type of the object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   Type of the object (string)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string GET_WorkspaceObject::getType()
    {
        return sType;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getName()
    //
    //   Purpose :   Method to get the Name of the object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   Name of the object (string)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string GET_WorkspaceObject::getName()
    {
        return sName;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   setName()
    //
    //   Purpose :   Method to set object name
    //
    //   Inputs  :   New Name
    //
    //   Outputs :   none
    //
    //   Return  :   None
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     25 Jul, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_WorkspaceObject::setName( const string sNewName )
    {
        LOG_TRACE ( logger, "START : GET_WorkspaceObject::setName" );

        ResultCheck stat = ITK_ok;

        stat = WSOM_set_name2	( _tag, sNewName.c_str()  );
        this->sName = sNewName;

        LOG_TRACE ( logger, "[GET] END : GET_WorkspaceObject::setName" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getDesc()
    //
    //   Purpose :   Method to get the Description of the object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   Description of the object (string)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string GET_WorkspaceObject::getDesc()
    {
        return sDesc;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getAssignedProjects()
    //
    //   Purpose :   Method to get Assigned Projects in the object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   Project object to which the object belongs to (vector<GET_POM_objectUnqPtr>)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_POM_objectUnqPtr> GET_WorkspaceObject::getAssignedProjects()
    {
        vector<GET_POM_objectUnqPtr> vAssignedProjTags;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::getAssignedProjects" );

        vAssignedProjTags = getPropertyTags ( PROJECTLIST_ATTR );

        LOG_TRACE ( logger, "[GET] END : GET_WorkspaceObject::getAssignedProjects" );

        return vAssignedProjTags;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   hasReleaseStatus (const string )
    //
    //   Purpose :   Method to check the given object has the passed release status
    //
    //   Inputs  :   sToBeCheckStatusName - Release status name to check
    //
    //   Outputs :   none
    //
    //   Return  :   true  - If the object has given release status
    //               false - If the object doesn't has any release status or given release status(bool)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_WorkspaceObject::hasReleaseStatus ( const string sToBeCheckStatusName )
    {
        bool bIsAvailable = false;

        ResultCheck stat;

        vector<string> vRelStatusList;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::hasReleaseStatus" );

        vRelStatusList = getReleaseStatusList();
        for ( size_t iIndex = 0; iIndex < vRelStatusList.size(); iIndex++ )
        {
            if ( sToBeCheckStatusName.compare ( vRelStatusList[iIndex] ) == 0 )
            {
                bIsAvailable = true;
                break;
            }
        }

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::hasReleaseStatus" );

        return bIsAvailable;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getReleaseStatusList (const string )
    //
    //   Purpose :   Method to get release status list present in the object
    //
    //   Inputs  :   sToBeCheckStatusName - Release status name to check
    //
    //   Outputs :   none
    //
    //   Return  :   Vector of release status list (vector<string>)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<string> GET_WorkspaceObject::getReleaseStatusList()
    {
        vector<string> vRelStatusList;

        vector<GET_POM_objectUnqPtr> vRelObjectsList;

        // Get release status list
        vRelObjectsList = getPropTags ( RELEASE_STATUS_LIST_ATTR );
        for ( size_t iIndex = 0; iIndex < vRelObjectsList.size(); iIndex++ )
        {
            vRelStatusList.push_back ( vRelObjectsList[iIndex]->getPropertyString ( NAME_ATTR ) );
        }

        return vRelStatusList;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   isReleased()
    //
    //   Purpose :   Method to check the release status of the object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   true  - If the object has release status
    //               false - If the object doesn't has any release status(bool)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_WorkspaceObject::isReleased()
    {
        bool bIsReleased = false;

        ResultCheck stat;

        vector<string> vRelStatusList;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::isReleased" );

        if ( getReleaseStatusList().size() > 0 )
        {
            bIsReleased = true;
        }

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::isReleased" );

        return bIsReleased;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   isWsObject()
    //
    //   Purpose :   Method to check the given object belongs to workspace object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   true  - If the object belongs to workspace object
    //               false - If the object doesn't belongs to workspace object (bool)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_WorkspaceObject::isWsObject ( const GET_POM_objectShrPtr wsoPtr )
    {
        return isDescendant ( wsoPtr->getTag(), WORKSPACEOBJECT_CLASS );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   isCheckedOut()
    //
    //   Purpose :   Method to find object is checked out
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   true  - If the object is checked out
    //               false - If the object is not checked out (bool)
    //
    //   History :
    //      Who                    Date                 Description
    //  TCS Development Team     11 Apr, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_WorkspaceObject::isCheckedOut (void)
    {
        logical verdict = FALSE;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::isCheckedOut" );

        stat = RES_is_checked_out ( _tag, &verdict );

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::isCheckedOut" );

        return ( verdict == TRUE ? true : false );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   checkout()
     //
     //   Purpose :   Method to check out the object
     //
     //   Inputs  :   sReason - The reason for check-out (string)
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     9 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_WorkspaceObject::checkout ( const string sReason )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::checkout" );

        stat = RES_checkout2 ( _tag, sReason.c_str(), NULL, NULL, RES_EXCLUSIVE_RESERVE);

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::checkout" );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   checkin()
     //
     //   Purpose :   Method to check in the object
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   none
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     9 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    void GET_WorkspaceObject::checkin()
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::checkin" );

        stat = RES_checkin ( _tag );

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::checkin" );
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   findWhoCheckedOut()
     //
     //   Purpose :   Method to find who checked out the object.
     //
     //   Inputs  :   none
     //
     //   Outputs :   none
     //
     //   Return  :   The user who checked out this object or null if none
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     9 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    GET_POM_userUnqPtr GET_WorkspaceObject::findWhoCheckedOut()
    {
        GET_POM_userUnqPtr userPtr;

        ResultCheck stat;

        tag_t tUserTag = NULLTAG;
        tag_t tGroupTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::findWhoCheckedOut" );

        stat = RES_who_checked_object_out ( _tag, &tUserTag, &tGroupTag );
        if ( tUserTag != NULLTAG )
        {
            userPtr = make_unique<GET_POM_user> ( GET_DUMMY::GET_DUMMY_VALUE, tUserTag );
        }

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::findWhoCheckedOut" );

        return userPtr;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   cancelCheckOut()
    //
    //   Purpose :   Method to cancel checked out the object.
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     9 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_WorkspaceObject::cancelCheckOut ( const bool &bCopyFlag )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::cancelCheckOut" );

        stat = RES_cancel_checkout ( _tag, ( bCopyFlag ? TRUE : FALSE ) );

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::cancelCheckOut" );

    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   transferCheckout (const GET_POM_userShrPtr, const GET_POM_groupShrPtr )
    //
    //   Purpose :   Method to transfer check out the object.
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     9 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    void GET_WorkspaceObject::transferCheckout ( const GET_POM_userShrPtr userPtr, const GET_POM_groupShrPtr groupPtr )
    {
        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::cancelCheckOut" );

        stat =  RES_transfer_checkout ( _tag, userPtr->getTag(), groupPtr->getTag() );

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::cancelCheckOut" );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getAWCUrl ( )
    //
    //   Purpose :   Method to get active workspace link of object
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   active workspace link url string
    //
    //   History :
    //      Who                   Date                 Description
    //  Ganesh Ubale           12 Sep, 2017         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    string GET_WorkspaceObject::getAWCUrl ( void )
    {
        char *url = NULL;

        ResultCheck stat;

        urlFormat_t urlType=AWC;
    
        string sString = "";

        LOG_TRACE ( logger, "START : GET_WorkspaceObject::getAWCUrl" );
    
		stat =  TC_tag_to_url ( _tag, urlType, &url );
        if ( url != NULL )
        {
            sString = url;
            MEM_free ( url );
        }

        LOG_TRACE ( logger, "END : GET_WorkspaceObject::getAwcUrl" );

        return sString;
    }

}
