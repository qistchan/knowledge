
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_T4O_Common.hxx
 //
 //    Purpose:   Header class for dealing with the Common T4O function
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      01 Dec, 2016         Initial creation
 //  TCS Development Team      03 Nov, 2017         Added Release Status argument to getOperation and getLinkedDepartmentId function
 //
 //   ============================================================================
 // ENDFILEDOC   ***/

#ifndef GET_T4O_COMMON_HXX
#define GET_T4O_COMMON_HXX

// GE CPP Includes
#include <GET_cpp_stl.h>
#include <GET_POM_object.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_CollaborationContext.hxx>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

using namespace get;

extern void getLinkedPPPObjects ( GET_ItemRevisionShrPtr getTargetShrPtr, bool& isProductLinked, bool& isDeptFound, string& sConsolidatedErrorMessage, GET_ItemRevisionShrPtr& linkedProductRevShrPtr, GET_ItemRevisionShrPtr& linkedProcessRevShrPtr, GET_ItemRevisionShrPtr& linkedDepartmentRevShrPtr );
extern void getProcessRevisions ( GET_ItemRevisionShrPtr getTargetShrPtr, vector<GET_ItemRevisionShrPtr>& vProcessRevisions );
extern void getOperations ( vector<GET_ItemRevisionShrPtr> vProcessRevisions, string strReleaseStatusName, vector<GET_ItemRevisionShrPtr>& vOperations );
extern void getLinkedProductId ( vector<GET_ItemRevisionShrPtr> vProcessRevisions, string& sProdErrMsg, bool& isProductLinked, GET_ItemRevisionShrPtr& linkedProductRevShrPtr, GET_ItemRevisionShrPtr& linkedProcessRevShrPtr );
extern void getLinkedDepartmentId ( vector<GET_ItemRevisionShrPtr> vOperations, string strReleaseStatusName, bool& isDeptFound, GET_ItemRevisionShrPtr& linkedDepartmentRevShrPtr );
extern void createStructureContext ( string revRule, GET_ItemRevisionShrPtr componentShrPtr, string contextType, GET_CollaborationContextShrPtr& structContextTag );
extern GET_CollaborationContextShrPtr createCCObject ( GET_CollaborationContextShrPtr productContextShrPtr, GET_CollaborationContextShrPtr processContextShrPtr, GET_CollaborationContextShrPtr departmentContextShrPtr, GET_ItemRevisionShrPtr linkedProcessRevShrPtr );

#endif // GET_T4O_COMMON_HXX
