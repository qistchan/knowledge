
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ImanQuery.hxx
//
//    Purpose:   Class for dealing with Teamcenter Queries
//
//    History:
//      Who                           Date                 Description
//  Capgemini Development Team     25 May, 2017         Initial creation
//  TCS Development Team           31 May, 2017         Consolidated Query related constants
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_IMANQUERY_HXX
#define GET_IMANQUERY_HXX

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_application_object.hxx>

// CPP Includes
#include <vector>

// Query Names
#define DISPATCHER_QUERY "GET Dispatcher Requests"
#define ITEM_REVISION_QUERY "Item Revision..."

// Query Criteria Names
#define QUERY_ID_ENTRY "ID"
#define QUERY_REVISION_ENTRY "Revision"
#define QUERY_CREATED_AFTER_ENTRY "Created After"
#define QUERY_TYPE_ENTRY "Type"
#define QUERY_STATUS_ENTRY "Release Status"

namespace get
{
    class DLLEXPORT GET_ImanQuery : public GET_POM_application_object
    {
        private:        
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
             //     Return:   tQueryTag - The tag_t Teamcenter Query instance, NULLTAG if not found
             //
             //    History:
             //      Who                               Date                 Description
             //  Capgemini Development Team     25 May, 2017         Initial creation
             //
             ===========================================================================
             //ENDFUNCDOC   ***/
            static tag_t findQuery ( const string );

        public:        
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
            static vector<GET_POM_objectUnqPtr> executeQuery ( const string, const vector<string>&, const vector<string>& );
    };
}

#endif // GET_IMANQUERY_HXX
