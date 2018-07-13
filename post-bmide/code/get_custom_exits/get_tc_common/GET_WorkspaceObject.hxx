
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_WorkspaceObject.hxx
//
//    Purpose:   Header class for dealing with the GET_WorkspaceObject
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team    12 Apr, 2016           Initial creation
//  Ganesh Ubale            12 Sep, 2017           Added Method getAWCUrl() to get active workspace link of object
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_WORKSPACEOBJECT_HXX
#define GET_WORKSPACEOBJECT_HXX

//GE  Incudes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>

//CPP Includes
#include <string>
#include <vector>

#include <GET_POM_application_object.hxx>

// Teamcenter Includes
#include <tccore/aom_prop.h>
#include <tccore/project.h>
#include <tccore/releasestatus.h>


// Smart Pointer Definition
namespace get
{
    #define GET_WorkspaceObjectUnqPtr unique_ptr<GET_WorkspaceObject>
    #define GET_WorkspaceObjectShrPtr shared_ptr<GET_WorkspaceObject>
}

namespace get
{
    class GET_POM_user;
    class GET_POM_group;
    class DLLEXPORT GET_WorkspaceObject : public GET_POM_application_object
    {
        private:
            string sName;
            string sType;
            string sDesc;

        public:
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
            GET_WorkspaceObject ( const GET_DUMMY, const tag_t );

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
            virtual ~GET_WorkspaceObject();

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
            string toString ( void );

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
            int getReleaseStatusCount();

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
            vector<GET_POM_objectUnqPtr> getAssignedProjects();

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
            bool hasReleaseStatus ( const string );

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
            vector<string> getReleaseStatusList();

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
            bool isReleased();

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
            static bool isWsObject ( const GET_POM_objectShrPtr );

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
            bool isCheckedOut ( void );

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
            void checkout ( const string );

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
            void checkin();

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
            unique_ptr<GET_POM_user> findWhoCheckedOut();

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
            void cancelCheckOut ( const bool &bCopyFlag = true );

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
            void transferCheckout ( const shared_ptr<GET_POM_user> userPtr, const shared_ptr<GET_POM_group> groupPtr );

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
            string getName();

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
            void setName( const string );

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
            string getDesc();

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
            string getType();

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
            static GET_WorkspaceObjectUnqPtr getInstance ( const tag_t );

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
            static GET_WorkspaceObjectUnqPtr getInstance ( const string );

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
            //  Ganesh Ubale           30 Aug, 2017         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            string getAWCUrl ( void );
    };
}

#endif // GET_WORKSPACEOBJECT_HXX
