
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanQuery.hxx
//
//    Purpose:   Class for dealing with Teamcenter Queries
//
//    History:
//      Who                           Date                 Description
//  Capgemini Development Team     25 May, 2017         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

//GE Includes
#include <GET_ImanQuery.hxx>
#include <GET_Exception.hxx>
#include <GET_Utils.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Item.hxx>
#include <GET_TC_Utils.hxx>

//Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <qry/qry.h>

const string logger = "get.get_tc_common.GET_ImanQuery";

namespace get
{
    /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:   findQuery()
     //
     //    Purpose:   Find Query Tag
     //
     //     Inputs:   sQueryName - Teamcenter Query Name to search for
     //
     //     Outputs:  none
     //
     //     Return:   tQueryTag - The tag_t Teamcenter Query instance, Exception if not found
     //
     //    History:
     //      Who                               Date                 Description
     //  Capgemini Development Team     25 May, 2017         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    tag_t GET_ImanQuery::findQuery ( const string sQueryName )
    {
        ResultCheck stat;

        tag_t tQueryTag = NULLTAG;

        LOG_TRACE ( logger, "START : GET_ImanQuery::findQuery" );

        stat = QRY_find2 ( sQueryName.c_str(), &tQueryTag );
        if ( tQueryTag == NULLTAG )
        {
            THROW ( "Query with the name " + sQueryName + " not found in Teamcenter" );
        }

        LOG_TRACE ( logger,"END : GET_ImanQuery::findQuery" );
        
        return tQueryTag;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   executeQuery()
    //
    //    Purpose:   Executes given Teamcenter Query with the specified input criteria and returns the results
    //
    //     Inputs:   sQueryName - Name of the Teamcenter Query to execute
    //               vEntries - Vector<string> containing entries for the Query
    //               vValues - Vector<string> containing user values for the Query
    //
    //    Outputs:   none
    //
    //     Return:   vector of GET_POM_object smart pointer instances from the Query results
    //
    //    History:
    //      Who                               Date                 Description
    //  Capgemini Development Team          25 May, 2017         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    vector<GET_POM_objectUnqPtr> GET_ImanQuery::executeQuery ( const string sQueryName, const vector<string> &vEntries, const vector<string> &vValues )
    {
        char **ppcEntries = NULL;
        char **ppcValues = NULL;

        IFail *exception = NULL;

        int iCount = 0;

        ResultCheck stat;

        tag_t tQueryTag = NULLTAG;

        tag_t *tQueryResults = NULL;

        vector<GET_POM_objectUnqPtr> vQueryResults;

        LOG_TRACE ( logger, "START : GET_ImanQuery::executeQuery()" );

        try
        {
            if ( vEntries.size() != vValues.size() )
            {
                THROW ( "The input arrays are not matching in size" );
            }
            tQueryTag = findQuery ( sQueryName );

            GET_vectorToArray ( vEntries, &ppcEntries );
            GET_vectorToArray ( vValues, &ppcValues );
            stat = QRY_execute ( tQueryTag, vEntries.size(), ppcEntries, ppcValues, &iCount, &tQueryResults );
            GET_arrayToVector ( iCount, tQueryResults, vQueryResults );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }

        // Free the Memory
        GET_free_array ( ( int ) vEntries.size(), ( void** ) ppcEntries );
        GET_free_array ( ( int ) vValues.size(), ( void** ) ppcValues );
        MEM_free ( tQueryResults );

        // Throw the exception back to the calling program if any
        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_ImanQuery::executeQuery()" );

        return vQueryResults;
    }
}
