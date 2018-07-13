
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Site.hxx
//
//    Purpose:   Header Class for dealing with Site Objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     28 Mar, 2016           Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_SITE_HXX
#define GET_SITE_HXX

#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>

#include <string>
#include <vector>

// Smart Pointer Definition
namespace get
{
    #define GET_SiteUnqPtr unique_ptr<GET_Site>
    #define GET_SiteShrPtr shared_ptr<GET_Site>
}

namespace get
{
    class DLLEXPORT GET_Site : public GET_POM_object
    {
        private:
            string sSiteName;
            int iSiteID;

        public:

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_Site
			 //
			 //    Purpose:   Constructor for the class GET_Site
			 //
			 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
			 //               tTag    - The Tag of this Teamcenter Site Object
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
            GET_Site ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_Site
			 //
			 //    Purpose:   Destructor for the class GET_Site
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
            virtual ~GET_Site();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   find ( string )
			 //
			 //    Purpose:   Method to find site given the Site ID string
			 //
			 //     Inputs:   siteID - Site to be found ( string )
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_Site Smart Pointer Instance matching the given Site ID
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     28 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_SiteUnqPtr find ( const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   find ( int )
			 //
			 //    Purpose:   Method to find site given the Site ID
			 //
			 //     Inputs:   siteID - Site to be found(int)
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_Site Smart Pointer Instance matching the given Site ID
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     05 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_SiteUnqPtr find ( const int );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getName()
			 //
			 //    Purpose:   Method to get site Name
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The Site Name of this site (string)
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     28 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			string getName() const;

			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getLocalID()
			 //
			 //    Purpose:   Method to get site ID of the local POM installation
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The Site ID of the Local logged in Site (int)
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     28 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			static int getLocalID();

			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getID()
			 //
			 //    Purpose:   Method to get site ID
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   Site ID of this site (int)
			 //
			 //    History:
			 //      Who                   Date                 Description
			 //  TCS Development Team     28 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			int getID() const;

			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance (tTag)
			 //
			 //    Purpose:   Method to get the instance of this class using tag_t
			 //
			 //     Inputs:   tTag - tag of the object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_Site Smart Pointer Instance of the given tag
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			static GET_SiteUnqPtr getInstance ( const tag_t );

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
			 //     Return:   The GET_Site Smart Pointer Instance of the given tag
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			static GET_SiteUnqPtr getInstance ( const string );
    };
}

#endif // GET_SITE_HXX
