
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GETPreviewServiceDBOperation.java
//    Purpose:   DB Operation class for custom GET previewservice translator services
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     08 May, 2016         Initial creation
//  TCS Development Team     12 Jul, 2018         Added method setDatasetName() to set the generated dataset name to match the Item/Rev ID
//
//   ============================================================================
 */

//==== Package  ===============================================================
package com.ge.getpreviewservice;

//==== Imports  ===============================================================
import com.ge.GETCommon;
import com.teamcenter.ets.soa.SoaHelper;
import com.teamcenter.ets.translator.ugs.basic.DatabaseOperation;
import com.teamcenter.services.strong.core._2007_01.DataManagement.VecStruct;
import com.teamcenter.services.strong.core._2007_06.DataManagement.ExpandGRMRelationsPref;
import com.teamcenter.services.strong.core._2007_06.DataManagement.ExpandGRMRelationsResponse;
import com.teamcenter.services.strong.core._2007_06.DataManagement.RelationAndTypesFilter2;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.services.strong.workflow.WorkflowService;
import com.teamcenter.services.strong.workflow._2014_06.Workflow.PerformActionInputInfo;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.DispatcherRequest;
import com.teamcenter.soa.client.model.strong.EPMConditionTask;
import com.teamcenter.soa.client.model.strong.EPMTask;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.translationservice.task.TranslationDBMapInfo;
import com.teamcenter.ets.request.TranslationRequest;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * This custom class is a sub class of the base DatabaseOperation class which
 * performs the loading operation related to getting the file lists from the
 * Mapper Objects. The main advantage of this class is derived classes do not
 * have to understand the mapping logic.
 *
 * @author TCS Development Team
 */
public class GETPreviewServiceDBOperation extends DatabaseOperation
{
    /**
     * Custom load method overriding the super class method
     */
    @Override
    protected void load(TranslationDBMapInfo zDbMapInfo, List<String> zFileList) throws Exception 
    {
        m_zTaskLogger.debug("Entering GETPreviewServiceDBOperation.load method ...");

        // Calling the super class load method
        super.load(zDbMapInfo, zFileList);

        // Complete the current WF task and move it ahead
        completeWFConditionTask();

        // Set the Dataset name to match Item ID/Rev ID
        setDatasetName();

        m_zTaskLogger.debug("Exiting GETPreviewServiceDBOperation.load method ...");
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

        m_zTaskLogger.debug("Entering GETPreviewServiceDBOperation.completeWFConditionTask method ...");

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
                    if (TranslationRequest.isInTerminalState(request) || currentState.equalsIgnoreCase(GETCommon.dispatcherNoTransState) ||
                            (noResultFileList != null && noResultFileList.size() > 0))
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
            m_zTaskLogger.error("Error in GETPreviewServiceDBOperation :Exception");
            m_zTaskLogger.error(ex.getMessage());
        }
        m_zTaskLogger.debug("Exiting GETPreviewServiceDBOperation.completeWFConditionTask method ...");
    }

    /**
     * Method to set the Dataset name matching the ItemRevision ID/Rev format
     */
    private void setDatasetName()
    {
        m_zTaskLogger.debug("Entering GETPreviewServiceDBOperation.setDatasetName method ...");

        try
        {
            DataManagementService dmService = DataManagementService.getService(SoaHelper.getSoaConnection());
            RelationAndTypesFilter2 filter = new RelationAndTypesFilter2();
            filter.objectTypeNames = new String[] {GETCommon.pdfDatasetType};
            filter.relationName = GETCommon.imanmanifestationRelType;
            ExpandGRMRelationsPref relationsPref = new ExpandGRMRelationsPref();
            relationsPref.expItemRev = false;
            relationsPref.info = new RelationAndTypesFilter2[] {filter};
            ExpandGRMRelationsResponse response = dmService.expandGRMRelationsForPrimary(new ModelObject[] {secondaryObj}, relationsPref);
            if (response != null)
            {
                if (response.serviceData != null)
                {
                    String errorMessage = GETCommon.getErrorFromServiceData(response.serviceData);
                    if (errorMessage != null)
                    {
                        throw new Exception(errorMessage);
                    }
                }
                if (response.output != null && response.output.length > 0 &&
                    response.output[0].otherSideObjData != null && response.output[0].otherSideObjData.length > 0 &&
                    response.output[0].otherSideObjData[0].otherSideObjects != null && response.output[0].otherSideObjData[0].otherSideObjects.length > 0)
                {
                    m_zTaskLogger.info("Setting the generated dataset name to match the Item ID/Rev ID ...");

                    dmService.getProperties(new ModelObject[] {secondaryObj}, new String[]{GETCommon.itemIDAttr, GETCommon.itemrevisionIDAttr});

                    // Set the Dataset name to Item ID/Rev ID
                    VecStruct propValueStruct = new VecStruct();
                    propValueStruct.stringVec = new String[] {((ItemRevision)secondaryObj).get_item_id() + "/" + ((ItemRevision)secondaryObj).get_item_revision_id()};
                    Map<String, VecStruct> propMap = new HashMap<String, VecStruct>();
                    propMap.put(GETCommon.objectNameAttr, propValueStruct);
                    ServiceData serviceData = dmService.setProperties(response.output[0].otherSideObjData[0].otherSideObjects, propMap);
                    String errorMessage = GETCommon.getErrorFromServiceData(serviceData);
                    if (errorMessage != null)
                    {
                        throw new Exception(errorMessage);
                    }
                }
            }
        }
        catch (Exception ex)
        {
            m_zTaskLogger.error("Error in GETPreviewServiceDBOperation :Exception");
            m_zTaskLogger.error(ex.getMessage());
        }

        m_zTaskLogger.debug("Exiting GETPreviewServiceDBOperation.setDatasetName method ...");
    }
}
