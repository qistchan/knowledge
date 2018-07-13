
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_T4O_Common.cxx
//
//    Purpose:   Header class for dealing with the Common T4O function
//    
//    History:
//      Who                   Date                 Description
//  TCS Development Team      01 Dec, 2016         Initial creation
//  TCS Development Team      03 Nov, 2017         Added Release Status argument to getOperation
//
//   ============================================================================
// ENDFILEDOC   ***/


// GE CPP Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_Errors.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_BOMLine.hxx>
#include <GET_BOMWindow.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_POM_object.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_T4O_Common.hxx>
#include <GET_CheckMCN_AH_Impl.hxx>
#include <GET_CollaborationContext.hxx>

// Teamcenter Includes
#include <fclasses/tc_basic.h>
#include <tc/emh.h>
#include <tc/tc.h>
#include <tc/tc_errors.h>
#include <mld/journal/journal.h>
#include <sa/am.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>
#include <collabctx/collabctx.h>

const string logger = "get_tc_common.GET_T4O_Common";

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getLinkedPPPObjects()
 //
 //    Purpose:   Method to get the linked Process, Product and Department share pointer
 //
 //     Inputs:   Workflow target attachment
 //
 //     Outputs:  Linked Process, Product and Department share pointer and thier boolean value
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      31 Jan, 2017         Initial creation
 //  TCS Development Team      03 Nov, 2017         Added Release Status argument to getOperation and getLinkedDepartmentId function
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
void getLinkedPPPObjects (GET_ItemRevisionShrPtr getTargetShrPtr, bool& isProductLinked, bool& isDeptFound, string& sConsolidatedErrorMessage,
        GET_ItemRevisionShrPtr& linkedProductRevShrPtr, GET_ItemRevisionShrPtr& linkedProcessRevShrPtr, GET_ItemRevisionShrPtr& linkedDepartmentRevShrPtr )
{
    int istatus = ITK_ok;

    vector < GET_ItemRevisionShrPtr > vProcessRevisions;
    vector < GET_ItemRevisionShrPtr > vOperations;

    LOG_TRACE ( logger, "Entering...getLinkedPPPObjects" );

    // Clear the existing error stack
    istatus = EMH_clear_errors();

    // Get the Process Revision vector
    getProcessRevisions ( getTargetShrPtr, vProcessRevisions );
    LOG_TRACE( logger, "Size of vProcessRevisions vector is:" + vProcessRevisions.size() );

    if ( vProcessRevisions.size() == 0 )
    {
        // There is no Product linked to Process
        LOG_TRACE ( logger, "There is no Product linked to Process..." );
        sConsolidatedErrorMessage.append ("There is no Product linked to Process..." );
        sConsolidatedErrorMessage.append ("\n");
    }
    else if ( vProcessRevisions.size() > 1 )
    {
        // More than one Product is linked to Process
        LOG_TRACE ( logger, "Solution folder contains more than one Process which are linked to Product..." );
        sConsolidatedErrorMessage.append ("Solution folder contains more than one Process which are linked to Product..." );
        sConsolidatedErrorMessage.append ("\n");
    }
    else
    {
        string sProdErrMsg          = EMPTY_STRING_VALUE;
        string strOwningProject     = EMPTY_STRING_VALUE;
        string strReleaseStatusName = EMPTY_STRING_VALUE;

        // Construct release status string based on MCN Project
        strOwningProject = getTargetShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
        strReleaseStatusName = string ( REVISION_RULE_PREFIX ) + strOwningProject + string ( WIP_REV_RULE_SUFF );

        // Get the Linked Product and Linked Process Id
        getLinkedProductId ( vProcessRevisions, sProdErrMsg, isProductLinked, linkedProductRevShrPtr, linkedProcessRevShrPtr );

        if ( sProdErrMsg.size() > 0 )
        {
            sConsolidatedErrorMessage.append ( sProdErrMsg );
            sConsolidatedErrorMessage.append ("\n");
        }

        // Get the first level Operation objects
        getOperations ( vProcessRevisions, strReleaseStatusName, vOperations );
        LOG_TRACE ( logger, "Total Operation found is ..." + vOperations.size() );

        if ( vOperations.size() == 0 )
        {
            // There is no Operation under to Process
            LOG_TRACE ( logger, "There is no Operation under Process..." );
            sConsolidatedErrorMessage.append ("There is no Operation under Process..." );
            sConsolidatedErrorMessage.append ("\n");
        }
        else
        {
            // Get the Linked Department
            getLinkedDepartmentId ( vOperations, strReleaseStatusName, isDeptFound, linkedDepartmentRevShrPtr );

            if ( isDeptFound == false )
            {
                // No Department found for any of the Operation
                LOG_TRACE ( logger, "There is no Department found for any of the Operation..." );
                sConsolidatedErrorMessage.append ("There is no Department found for any of the Operation..." );
                sConsolidatedErrorMessage.append ("\n");
            }
        }
    }

    LOG_TRACE ( logger, "Exiting...getLinkedPPPObjects" );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getProcessRevisions()
 //
 //    Purpose:   Method to get the vector of Process Revision from given target
 //
 //     Inputs:   Workflow target item pointer
 //
 //     Outputs:  vector of Process Revision share pointer
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      01 Dec, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern void getProcessRevisions ( GET_ItemRevisionShrPtr getTargetShrPtr, vector<GET_ItemRevisionShrPtr>& vProcessRevisions )
{
    LOG_TRACE ( logger, "Entering...getProcessRevisions" );

    // Get all objects from Solution folder
    vector <GET_POM_objectUnqPtr> vSolutionItemsUnqPtr = getTargetShrPtr->getPropTags( CM_HAS_SLITEMS_PROP );
    LOG_TRACE ( logger, "Size of vSolutionItemsUnqPtr vector is ..." + vSolutionItemsUnqPtr.size() );

    // Loop through each objects in Solution Item folder
    for( size_t inx = 0; inx < vSolutionItemsUnqPtr.size(); inx++ )
    {
        GET_ItemRevisionShrPtr getSolutionRevShrPtr ( move ( GET_ItemRevision::getInstance( vSolutionItemsUnqPtr[inx]->getTag() )));

        // Check the type of solution folder object
        if ( getSolutionRevShrPtr->getType() != PROCESSREV_TYPE )
        {
			continue;
		}

		// Get Product revision which are linked to Process with IMAN_METarget relation
		vector <GET_POM_objectUnqPtr> vProductRevisions = getSolutionRevShrPtr->getPropTags( ME_TARGET );
		LOG_TRACE ( logger, "Size of vProductRevisions vector is ..." + vProductRevisions.size() );

		// Product will always be linked only to top level Process
		// if no Product is linked to Process then it is not a Process
		if( vProductRevisions.size() == 0 )
		{
			continue;
		}
		
		// If Product revision linked with IMAN_METarget relation, then its a Process, store in a vector            
		vProcessRevisions.push_back ( getSolutionRevShrPtr );
		LOG_TRACE ( logger, "Size of vProcessRevisions vector is ..." + vProcessRevisions.size() );
    }

    LOG_TRACE ( logger, "Exiting...getProcessRevisions" );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getOperations()
 //
 //    Purpose:   Method to get the vector of Operations for given Process Revision
 //
 //     Inputs:   Vector of Process Revision share pointer
 //
 //     Outputs:  vector of Operations Revision share pointer
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      01 Dec, 2016         Initial creation
 //  TCS Development Team      03 Nov, 2017         Added Release Status argument
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern void getOperations ( vector<GET_ItemRevisionShrPtr> vProcessRevisions, string strReleaseStatusName, vector <GET_ItemRevisionShrPtr>& vOperations )
{
    LOG_TRACE ( logger, "Entering...getOperations");

    // Loop through all Process Revisions to get all Operations
    for (size_t inx = 0; inx <vProcessRevisions.size(); inx++)
    {
        GET_ItemRevisionShrPtr getProcessRevShrPtr ( move (GET_ItemRevision::getInstance( vProcessRevisions[inx]->getTag() )));

		// Operations will be first level child of Process which is of type GET6ProcessRevision
		GET_BOMWindowUnqPtr bomWindowUnqPtr = GET_BOMWindow::create();

		bomWindowUnqPtr->setRevisionRule ( strReleaseStatusName );

		GET_BOMViewRevisionShrPtr bomViewRevShrPtr;
		GET_BOMLineUnqPtr bomLineUnqPtr = bomWindowUnqPtr->setTopLine ( getProcessRevShrPtr, bomViewRevShrPtr );
		vector<GET_BOMLineUnqPtr> vFirstChildLinesVector = bomLineUnqPtr->getChildren();

		for ( size_t i=0; i<vFirstChildLinesVector.size(); i++ )
		{
			GET_ItemRevisionUnqPtr getChildRevUnqPtr = vFirstChildLinesVector[i]->getItemRevision();
			GET_ItemRevisionShrPtr getChildRevShrPtr( move ( getChildRevUnqPtr ) );

			// Validate the first level object is of type Process Revision
			if ( getChildRevShrPtr->getType() == PROCESSREV_TYPE )
			{
				LOG_TRACE ( logger, "First Level child id is ..." + getChildRevShrPtr->getId() );
				vOperations.push_back ( getChildRevShrPtr );
			}
		}
    }

    LOG_TRACE ( logger, "Exiting...getOperations" );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getLinkedProductId()
 //
 //    Purpose:   Method to get the linked Product and Process Revision share pointer
 //
 //     Inputs:   Vector of Process Revision share pointer
 //
 //     Outputs:  Linked Product Revision share pointer and linkedProcess Revision share pointer
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      01 Dec, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern void getLinkedProductId ( vector<GET_ItemRevisionShrPtr> vProcessRevisions, string& sProdErrMsg, bool& isProductLinked,
    GET_ItemRevisionShrPtr& linkedProductRevShrPtr,	GET_ItemRevisionShrPtr& linkedProcessRevShrPtr )
{
    vector <GET_POM_objectUnqPtr> vProductRevisions;
    string linkedProductId = "";
    string linkedProcessId = "";

    LOG_TRACE ( logger, "Entering...getLinkedProductId");

    // Loop through all Process Revisions to get Linked Product
    for ( size_t inx = 0; inx <vProcessRevisions.size(); inx++ )
    {
        GET_ItemRevisionShrPtr getProcessRevShrPtr( move ( GET_ItemRevision::getInstance( vProcessRevisions[inx]->getTag() )));

        // Get Product revision which are linked to Process with IMAN_METarget relation
        vProductRevisions = getProcessRevShrPtr->getPropTags( ME_TARGET );
        LOG_TRACE ( logger, "Size of vProductRevisions vector is ..." + vProductRevisions.size() );

        // Loop through all Product Revisions to get Linked Product
        for ( size_t jnx = 0; jnx < vProductRevisions.size(); jnx++ )
        {
            GET_ItemRevisionShrPtr getProductRevShrPtr ( move ( GET_ItemRevision::getInstance( vProductRevisions[jnx]->getTag() )));

            string sProdRevType = "";
            sProdRevType = getProductRevShrPtr->getType();
            LOG_TRACE ( logger, "Product Revision Type is..." + sProdRevType);

            // Verify if Linked Product revision is different than one of type Mfg or Mech or Elec or Soft
            if ( ! (sProdRevType == MECHREV_TYPE || sProdRevType == ELECREV_TYPE || sProdRevType == MFGREV_TYPE || sProdRevType == SOFTREV_TYPE) )
            {
                string str = "";
                str.append ("Object [" + getProductRevShrPtr->getId() + "] linked to Process [" + getProcessRevShrPtr->getId() + "] is of other than allowed type");
                LOG_TRACE ( logger, str);
                sProdErrMsg.append ("Object [" + getProductRevShrPtr->getId() + "] linked to Process [" + getProcessRevShrPtr->getId() + "] is of other than allowed type");
                sProdErrMsg.append ("\n");
                continue;
            }

			linkedProductRevShrPtr = getProductRevShrPtr;
			linkedProcessRevShrPtr = getProcessRevShrPtr;

			linkedProductId = getProductRevShrPtr->getId();
			linkedProcessId = getProcessRevShrPtr->getId();

			LOG_TRACE ( logger, "Linked Product Id..." + linkedProductId );
			LOG_TRACE ( logger, "Linked Process Id..." + linkedProcessId );
			
			isProductLinked = true;
			break;
        }
    }

    LOG_TRACE ( logger, "Exiting...getLinkedProductId" );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   getLinkedDepartmentId()
 //
 //    Purpose:   Method to get the linked Department Revision share pointer
 //
 //     Inputs:   Vector of Operation Revision share pointer
 //
 //     Outputs:  Linked Department Revision share pointer
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      01 Dec, 2016         Initial creation
 //  TCS Development Team      03 Nov, 2017         Added Release Status argument
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern void getLinkedDepartmentId ( vector<GET_ItemRevisionShrPtr> vOperations, string strReleaseStatusName, bool& isDeptFound, GET_ItemRevisionShrPtr& linkedDepartmentRevShrPtr )
{
    LOG_TRACE (logger, "Entering...getLinkedDepartmentId");

    // Loop through all Operation Revisions to get Linked Departments
    for (size_t inx = 0; inx<vOperations.size(); inx++ )
    {
        GET_ItemRevisionShrPtr getOperationRevShrPtr ( move ( GET_ItemRevision::getInstance(vOperations[inx]->getTag() )));
        LOG_TRACE ( logger, "Operation id is..." + getOperationRevShrPtr->getId() );

        GET_BOMWindowUnqPtr bomWindowUnqPtr = GET_BOMWindow::create();

        bomWindowUnqPtr->setRevisionRule ( strReleaseStatusName );

        GET_BOMViewRevisionShrPtr bomViewRevShrPtr;
        GET_BOMLineUnqPtr bomLineUnqPtr = bomWindowUnqPtr->setTopLine ( getOperationRevShrPtr, bomViewRevShrPtr );
        vector<GET_BOMLineUnqPtr> vChildLinesVector = bomLineUnqPtr->getChildren();
        LOG_TRACE ( logger, "vChildLinesVector.size() is..." + vChildLinesVector.size());

        // Loop through each children of Operation
        for (size_t jnx = 0; jnx < vChildLinesVector.size(); jnx++ )
        {
            GET_ItemRevisionUnqPtr getChildRevUnqPtr = vChildLinesVector[jnx]->getItemRevision();
            GET_ItemRevisionShrPtr getChildRevShrPtr ( move ( getChildRevUnqPtr ));

            string sChildRevType = "";
            sChildRevType = getChildRevShrPtr->getType();

            LOG_TRACE ( logger, "getChildRevShrPtr Type is..." + sChildRevType );
            LOG_TRACE ( logger, "getChildRevShrPtr Id is..." + getChildRevShrPtr->getId() );

            // Verify if child object revision is other than of Department Revision type
            if ( sChildRevType != DEPARTMENTREV_TYPE)
            {
                continue;
            }

            linkedDepartmentRevShrPtr = getChildRevShrPtr;
            string str = "";
            str.append ("Linked Department [" + getChildRevShrPtr->getId() + "] is copied under Operation [" + vOperations[inx]->getId() + "]");
            LOG_TRACE ( logger, str );

            isDeptFound = true;
            break;
        }
    }

    LOG_TRACE ( logger, "Exiting...getLinkedDepartmentId" );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   createStructureContext()
 //
 //    Purpose:   Method to create the required Structure Context needed for CC obj creation
 //
 //     Inputs:   Component share pointer
 //
 //     Outputs:  Share pointer of created Structure Context
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      01 Dec, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern void createStructureContext ( string revRule, GET_ItemRevisionShrPtr componentShrPtr, string contextType, GET_CollaborationContextShrPtr& structCnxtShrPtr )
{
    ResultCheck stat;

    map<string, GET_BOMViewRevisionShrPtr>::iterator mapBVRIterator;
    vector<GET_WorkspaceObjectShrPtr> vBVRObjects;

    string componentId = componentShrPtr->getId();
    string componentRevId = componentShrPtr->getRevId();

    string structContextName = string(componentId) + "-" + string(componentRevId);
    string structContextDesc = structContextName;
    string structContextType = contextType;

    string configContextName = "CfgCxt_"+ string(componentId)+ "-" + string(componentRevId);
    string configContextDesc = configContextName;
    string configContextType = "";

    LOG_TRACE ( logger, "Entering...createStructureContext" );

    // Get the BOM View Revision
    map<string, GET_BOMViewRevisionShrPtr> mpBVRObjects = GET_ItemRevision::getInstance(componentShrPtr->getTag())->getBVRs();

    for(mapBVRIterator = mpBVRObjects.begin(); mapBVRIterator != mpBVRObjects.end(); mapBVRIterator++)
    {
        GET_WorkspaceObjectShrPtr getWorkspaceBVRShrPtr ( move ( GET_WorkspaceObject::getInstance(mapBVRIterator->second->getTag() )));
        vBVRObjects.push_back ( getWorkspaceBVRShrPtr );
    }
    LOG_TRACE ( logger, "size of bomview is..." + mpBVRObjects.size() );

    GET_RevisionRuleUnqPtr getRevRuleUnqPtr = GET_RevisionRule::find ( revRule );
    GET_RevisionRuleShrPtr getRevRuleShrPtr ( move ( getRevRuleUnqPtr) );

    // Create configuration context
    GET_CollaborationContextUnqPtr configCnxtUnqPtr = GET_CollaborationContext::createConfigContext (configContextType, configContextName, configContextDesc );
    GET_CollaborationContextShrPtr configCnxtShrPtr ( move ( configCnxtUnqPtr ));

    if ( (configCnxtShrPtr != NULLTAG) && (getRevRuleShrPtr != NULLTAG) )
    {
        // Set revision rule for configuration context for the product
        GET_CollaborationContext::setConfigRevRule ( configCnxtShrPtr, getRevRuleShrPtr );
    }

    // Create structure context
    GET_CollaborationContextUnqPtr structCnxtUnqPtr = GET_CollaborationContext::createStructContext ( structContextType, structContextName, structContextDesc );
    GET_CollaborationContextShrPtr structureCnxtShrPtr ( move ( structCnxtUnqPtr ));
    structCnxtShrPtr = structureCnxtShrPtr;

    if ( mpBVRObjects.size() > 0 )
    {
        int subType = COLLABCTX_content_rel_background;
        GET_CollaborationContext::addContextContent ( structCnxtShrPtr, vBVRObjects, subType );
    }

    if ( (configCnxtShrPtr != NULLTAG) && (structCnxtShrPtr != NULLTAG) )
    {
        // Associate the configuration context to the MEProductContext
        GET_CollaborationContext::setConfigContext ( structCnxtShrPtr, configCnxtShrPtr );
    }

    LOG_TRACE ( logger, "Exiting...createStructureContext" );
}

/*STARTFUNCDOC ***
 //
 ===========================================================================
 //   Function:   createCCObject()
 //
 //    Purpose:   Method to create the CC object
 //
 //     Inputs:   Share pointer of Process, Product and Department Contexts
 //
 //     Outputs:  Tag of created CC object
 //
 //     Return:   none
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team      01 Dec, 2016         Initial creation
 //
 ===========================================================================
 //ENDFUNCDOC   ***/
extern GET_CollaborationContextShrPtr createCCObject ( GET_CollaborationContextShrPtr productContextShrPtr, GET_CollaborationContextShrPtr processContextShrPtr,
        GET_CollaborationContextShrPtr departmentContextShrPtr, GET_ItemRevisionShrPtr linkedProcessRevShrPtr )
{
    ResultCheck stat;
    GET_CollaborationContextShrPtr clbCnxtShrPtr1;

    LOG_TRACE ( logger, "Entering...createCCObject" );

    string ccName = "CC_" + string( linkedProcessRevShrPtr->getId() ) + "-" + string( linkedProcessRevShrPtr->getRevId() );
    string ccDesc = ccName;
    string ccType = MECC_TYPE;

    LOG_TRACE ( logger, "CC object name to be created is..." + ccName );

    if ( (productContextShrPtr != NULLTAG) && (processContextShrPtr != NULLTAG) && (departmentContextShrPtr != NULLTAG) )
    {
        // Create a new Collaboration Context object of type MECollaborationContext
        GET_CollaborationContextUnqPtr clbCnxtUnqPtr = GET_CollaborationContext::createCollaborationCntx ( ccType, ccName, ccDesc );
        GET_CollaborationContextShrPtr clbCnxtShrPtr ( move ( clbCnxtUnqPtr ));
        clbCnxtShrPtr1 = clbCnxtShrPtr;

        if ( clbCnxtShrPtr != NULLTAG )
        {
            // Associate the structure context object to the CC object
            GET_CollaborationContext::addStructContent( clbCnxtShrPtr, processContextShrPtr );
            GET_CollaborationContext::addStructContent( clbCnxtShrPtr, productContextShrPtr );
            GET_CollaborationContext::addStructContent( clbCnxtShrPtr, departmentContextShrPtr );
        }
    }

    LOG_TRACE ( logger, "Exiting...createCCObject" );

    return clbCnxtShrPtr1;
}
	
