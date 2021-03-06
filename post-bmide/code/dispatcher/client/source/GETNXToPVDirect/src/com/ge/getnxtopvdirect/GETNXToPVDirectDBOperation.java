
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GETNXToPVDirectDBOperation.java
//    Purpose:   DB Operation class for custom GET nxtopvdirect translator services
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     08 May, 2016         Initial creation
//
//   ============================================================================
 */

//==== Package  ===============================================================
package com.ge.getnxtopvdirect;

//==== Imports  ===============================================================
import com.ge.GETCommon;
import com.teamcenter.ets.soa.SoaHelper;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.services.strong.workflow.WorkflowService;
import com.teamcenter.services.strong.workflow._2014_06.Workflow.PerformActionInputInfo;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.DispatcherRequest;
import com.teamcenter.soa.client.model.strong.EPMConditionTask;
import com.teamcenter.soa.client.model.strong.EPMTask;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.ets.load.DatabaseOperation;
import com.teamcenter.ets.request.TranslationRequest;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

/**
 * @author TCS
 *
 * This custom class is a sub class of the base DatabaseOperation class which
 * performs the loading operation related to getting the file lists from the
 * Mapper Objects. The main advantage of this class is derived classes do not
 * have to understand the mapping logic.
 */
public class GETNXToPVDirectDBOperation extends DatabaseOperation
{
    /**
     * Custom load method overriding the super class method
     */
    @Override
    public void load() throws Exception 
    {
        m_zTaskLogger.debug("Entering GETNXToPVDirectDBOperation.load method ...");

        // Complete the current WF task and move it ahead
        completeWFConditionTask();

        m_zTaskLogger.debug("Exiting GETNXToPVDirectDBOperation.load method ...");
    }

    /**
     * Method to process dispatcher requests and complete the current Workflow condition task
     *
     * @throws Exception
     */
    private void completeWFConditionTask() throws Exception
    {
    	boolean isSuccessPath = true;
        boolean completeWFTask = false;

        int nCompletedRequests = 0;
        int nTotalRequests = 0;

        List<ModelObject> propertyList = new ArrayList<ModelObject>();

        StringBuilder itemIDBuilder = new StringBuilder();
        StringBuilder revIDBuilder = new StringBuilder();

        EPMConditionTask conditionTask = null;

        m_zTaskLogger.debug("Entering GETNXToPVDirectDBOperation.completeWFConditionTask method ...");

        try
        {
	        DataManagementService dmService = DataManagementService.getService(SoaHelper.getSoaConnection());
	        ItemRevision sourceRevision = (ItemRevision) secondaryObj;
	        ModelObject[] tasks = sourceRevision.get_process_stage_list();
	        if (tasks != null & tasks.length > 0)
	        {
	        	dmService.getProperties(tasks, new String[]{GETCommon.rootTargetAttachmentsAttr, GETCommon.creationDateAttr, GETCommon.rootTaskAttr});

	            for (ModelObject taskObject : tasks)
	            {
	                if (!(taskObject instanceof EPMConditionTask))
	                {
	                	continue;
	                }
	                completeWFTask = true;
	                m_zTaskLogger.info("Got the EPM Condition Task Instance");

	                conditionTask = (EPMConditionTask) taskObject;
	                ModelObject[] targetAttachments = conditionTask.get_root_target_attachments();
	                if (targetAttachments != null && targetAttachments.length > 0)
	                {
	                	List<ItemRevision> itemRevisionList = new ArrayList<ItemRevision>();

	                	for (ModelObject targetAttachment : targetAttachments)
	                    {
	                        if (targetAttachment.equals(secondaryObj))
	                        {
	                            continue;
	                        }
	                        if (!(targetAttachment instanceof ItemRevision))
	                        {
	                            continue;
	                        }

	                        itemRevisionList.add((ItemRevision)targetAttachment);
	                    }
	                	if (itemRevisionList.size() > 0)
	                	{
	                		dmService.getProperties(itemRevisionList.toArray(new ModelObject[itemRevisionList.size()]), new String[]{GETCommon.itemIDAttr, GETCommon.itemrevisionIDAttr, GETCommon.objectTypeAttr});
		                	for (ItemRevision targetRevision : itemRevisionList)
		                	{
		                        if (!targetRevision.get_object_type().equals(GETCommon.mechPartRevisionType) &&
		                            !targetRevision.get_object_type().equals(GETCommon.electPartRevisionType) &&
		                            !targetRevision.get_object_type().equals(GETCommon.documentRevisionType) &&
		                            !targetRevision.get_object_type().equals(GETCommon.specsRevisionType))
		                        {
		                            continue;
		                        }

		                        m_zTaskLogger.info("The Secondary Object Type is : " + targetRevision.get_object_type());
		                        itemIDBuilder.append(targetRevision.get_item_id()).append(GETCommon.SEMICOLON);
		                        revIDBuilder.append(targetRevision.get_item_revision_id()).append(GETCommon.SEMICOLON);
		                	}
	                	}
	                }
	                break;
	            }
	        }
	
	        if (completeWFTask)
	        {
	            String itemIDString = itemIDBuilder.toString();
	            if (!itemIDString.isEmpty())
	            {
	                String revIDString = revIDBuilder.toString();
	                Calendar creationDate = ((EPMTask)conditionTask.get_root_task()).get_creation_date();
	                SimpleDateFormat dateFormat = new SimpleDateFormat(GETCommon.teamcenterDateFormat);
	                String creationDateString = dateFormat.format(creationDate.getTime());
	
	                ModelObject[] dispRequestsList = GETCommon.queryObject(GETCommon.dispatcherQueryName,
	                        new String[]{GETCommon.queryIDEntry, GETCommon.queryRevisionEntry, GETCommon.queryCreatedAfterEntry},
	                        new String[]{itemIDString, revIDString, creationDateString});
	                if (dispRequestsList != null && dispRequestsList.length > 0)
	                {
	                    for (ModelObject mo : dispRequestsList)
	                    {
	                        propertyList.add(mo);   
	                    }
	                }
	                propertyList.add(request);
	                dmService.getProperties(propertyList.toArray(new ModelObject[propertyList.size()]), new String[]{GETCommon.currentStateAttr, GETCommon.taskIDAttr, GETCommon.providerNameAttr, GETCommon.serviceNameAttr});
	
	                if (dispRequestsList != null && dispRequestsList.length > 0)
	                {
	                    m_zTaskLogger.info("The number of dispatcher requests found from the search is : " + dispRequestsList.length);

	                    nTotalRequests = dispRequestsList.length;
	                    for (ModelObject dispRequest : dispRequestsList)
	                    {
	                        String currentState = ((DispatcherRequest)dispRequest).get_currentState();
	                        if (currentState.equalsIgnoreCase(GETCommon.dispatcherCompleteState) ||
	                            currentState.equalsIgnoreCase(GETCommon.dispatcherDuplicateState) ||
	                            currentState.equalsIgnoreCase(GETCommon.dispatcherDeleteState) ||
	                            currentState.equalsIgnoreCase(GETCommon.dispatcherCancelledState) ||
	                            currentState.equalsIgnoreCase(GETCommon.dispatcherSupersededState) ||
	                            currentState.equalsIgnoreCase(GETCommon.dispatcherNoTransState) ||
	                            currentState.equalsIgnoreCase(GETCommon.dispatcherTerminalState))
	                        {
	                            nCompletedRequests++;
	                        }

	                        // To check if dispatcher request is Terminal.
	                        if (TranslationRequest.isInTerminalState(dispRequest) || currentState.equalsIgnoreCase(GETCommon.dispatcherNoTransState))
	                        {
	                            isSuccessPath = false;
	                        }
	                    }
	                }
	            }
	            else
	            {
	                m_zTaskLogger.info("No other WF Targets found");
	            }

	            if (propertyList.size() == 0)
	            {
	                dmService.getProperties(propertyList.toArray(new ModelObject[]{request}), new String[]{GETCommon.currentStateAttr, GETCommon.taskIDAttr, GETCommon.providerNameAttr, GETCommon.serviceNameAttr});
	            }

	            if (nCompletedRequests == nTotalRequests)
	            {
	                m_zTaskLogger.info("Reached the final Dispatcher Request");

	                String currentState = ((DispatcherRequest)request).get_currentState();
	                if (TranslationRequest.isInTerminalState(request) || currentState.equalsIgnoreCase(GETCommon.dispatcherNoTransState))
	                {
	                    isSuccessPath = false;
	                }

	                String result = isSuccessPath ? GETCommon.successResult : GETCommon.failureResult;
	                m_zTaskLogger.info("The result to be set is : " + result);

	                // Complete the current task of the workflow
	                WorkflowService workflowService = WorkflowService.getService(SoaHelper.getSoaConnection());
	                PerformActionInputInfo inputInfo = new PerformActionInputInfo();
	                inputInfo.action = GETCommon.EPMCompleteAction;
	                inputInfo.actionableObject = conditionTask;
	                inputInfo.clientId = ((DispatcherRequest)request).get_taskID();
	                inputInfo.supportingValue = result;
	                ServiceData serviceData = workflowService.performAction3(new PerformActionInputInfo[]{inputInfo});
	                String errorMessage = GETCommon.getErrorFromServiceData(serviceData);
	                if (errorMessage != null)
	                {
	                    throw new Exception(errorMessage);
	                }
	                m_zTaskLogger.info("Completed the condition task and moved it to the next level");
	            }
	        }
    	}
        catch (Exception ex)
        {
            m_zTaskLogger.error("Error in GETNXToPVDirectDBOperation :Exception");
            m_zTaskLogger.error(ex.getMessage());
        }

        m_zTaskLogger.debug("Exiting GETNXToPVDirectDBOperation.completeWFConditionTask method ...");
    }

    /**
     * Custom query method overriding the super class method
     */
    @Override
    public void query() throws Exception
    {
        m_zTaskLogger.debug("Entering GETNXToPVDirectDBOperation.query method ...");

        this.primaryObj = null;
        this.secondaryObj = null;

        ModelObject[] primObjects = ((DispatcherRequest)request).get_primaryObjects();
        if (primObjects != null && primObjects.length > 0)
        {
            this.primaryObj = primObjects[0];
        }
        ModelObject[] secObjects = ((DispatcherRequest)request).get_secondaryObjects();
        if (secObjects != null && secObjects.length > 0)
        {
            this.secondaryObj = secObjects[0];
        }

        if (this.primaryObj == null)
        {
            throw new Exception("Primary Object is not set.");
        }
        if (this.secondaryObj == null)
        {
            throw new Exception("Secondary Object is not set.");
        }

        m_zTaskLogger.debug("Exiting GETNXToPVDirectDBOperation.query method ...");
    }
}
