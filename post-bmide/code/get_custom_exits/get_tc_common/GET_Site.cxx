
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Site.cxx
//
//    Purpose:   Class for dealing with site objects
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team     28 Mar, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

#include <tc/tc.h>
#include <sa/sa.h>
#include <base_utils/IFail.hxx>
#include <base_utils/ResultCheck.hxx>

#include <GET_Site.hxx>

const string logger = "get.get_tc_common.GET_Site";

namespace get
{
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
    GET_Site::GET_Site ( const GET_DUMMY enDummy, const tag_t tTag ) : GET_POM_object ( enDummy, tTag )
    {
        char *pcSiteName = NULL;

        int iTempSiteID = 0;

        ResultCheck stat;

        stat = SA_ask_site_info2 ( _tag, &pcSiteName, &iTempSiteID );
        sSiteName = pcSiteName;
        MEM_free ( pcSiteName );
        iSiteID = iTempSiteID;
    }

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
    GET_Site::~GET_Site() {}
    
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
    GET_SiteUnqPtr GET_Site::getInstance ( const tag_t tTag )
	{
		LOG_TRACE ( logger, "START : GET_Site::getInstance(tTag)" );

		if ( ! isDescendant ( tTag, SITE_CLASS ) )
		{
			string sMsg = string ( "The given tag is not an instance of the class " ) + SITE_CLASS;
			THROW ( sMsg );
		}

		LOG_TRACE ( logger, "END : GET_Site::getInstance(tTag)" );

		return make_unique<GET_Site> ( GET_DUMMY::GET_DUMMY_VALUE, tTag );
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
     //     Return:   The GET_Site Smart Pointer Instance of the given tag
	 //
	 //    History:
	 //      Who                    Date                 Description
	 //  TCS Development Team     11 Apr, 2016         Initial creation
	 //
	 ===========================================================================
	 //ENDFUNCDOC   ***/
    GET_SiteUnqPtr GET_Site::getInstance ( const string sUID )
	{
		LOG_TRACE ( logger, "START : GET_Site::getInstance(sUID)\n" );

		tag_t tObjectTag = getTagFromUID ( sUID );
		if ( tObjectTag == NULLTAG )
		{
			THROW ( sUID + " is not a valid Teamcenter UID" );
		}

		LOG_TRACE ( logger, "END : GET_Site::getInstance(sUID)" );

		return getInstance ( tObjectTag );
	}

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
    GET_SiteUnqPtr GET_Site::find ( const string sSiteId )
    {
        GET_SiteUnqPtr sitePtr;

        ResultCheck stat;

        tag_t tSiteTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_Site::find(string)" );

        stat = SA_find_site2 ( sSiteId.c_str(), &tSiteTag );
        if ( tSiteTag != NULLTAG )
        {
            sitePtr = make_unique<GET_Site> ( GET_DUMMY::GET_DUMMY_VALUE, tSiteTag );
        }

        LOG_TRACE ( logger, "END : GET_Site::find(string)" );

        return sitePtr;
    }

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
	GET_SiteUnqPtr GET_Site::find ( const int iSiteId )
	{
	    GET_SiteUnqPtr sitePtr;

		ResultCheck stat;

		tag_t tSiteTag = NULLTAG;

		LOG_TRACE ( logger, "START : GET_Site::find(int)" );

		stat = SA_find_site_by_id ( iSiteId, &tSiteTag );
		if ( tSiteTag != NULLTAG )
        {
            sitePtr = make_unique<GET_Site> ( GET_DUMMY::GET_DUMMY_VALUE, tSiteTag );
        }

		LOG_TRACE ( logger, "END : GET_Site::find(int)" );

		return sitePtr;
	}

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
	string GET_Site::getName() const
	{
		return sSiteName;
	}

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
	int GET_Site::getID() const
	{
		return iSiteID;
	}

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
	int GET_Site::getLocalID()
	{
		int iSiteId = 0;

		ResultCheck stat;
		
		LOG_TRACE ( logger, "START : GET_Site::getLocalID" );

        stat = POM_site_id ( &iSiteId ) ;

        LOG_TRACE ( logger, "END : GET_Site::getLocalID" );
		
		return iSiteId;
	 }
}
