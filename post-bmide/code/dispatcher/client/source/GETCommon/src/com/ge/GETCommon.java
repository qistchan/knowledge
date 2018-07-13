
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GETCommon.java
//    Purpose:   Class for common Utility methods required for Dispatcher Client
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     25 May, 2016         Initial creation
//
//   ============================================================================
 */
package com.ge;

import java.util.ArrayList;
import java.util.List;

import com.teamcenter.ets.soa.SoaHelper;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.services.strong.query.SavedQueryService;
import com.teamcenter.services.strong.query._2007_09.SavedQuery.QueryResults;
import com.teamcenter.services.strong.query._2007_09.SavedQuery.SavedQueriesResponse;
import com.teamcenter.services.strong.query._2008_06.SavedQuery.QueryInput;
import com.teamcenter.services.strong.query._2010_04.SavedQuery.FindSavedQueriesCriteriaInput;
import com.teamcenter.services.strong.query._2010_04.SavedQuery.FindSavedQueriesResponse;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.ServiceData;

public class GETCommon
{
    public static final String dispatcherCancelledState= "CANCELLED";
    public static final String dispatcherCompleteState = "COMPLETE";
    public static final String dispatcherDeleteState= "DELETE";
    public static final String dispatcherDuplicateState= "DUPLICATE";
    public static final String dispatcherNoTransState= "NO_TRANS";
    public static final String dispatcherSupersededState= "SUPERSEDED";
    public static final String dispatcherTerminalState= "TERMINAL";

    public static final String dispatcherQueryName = "GET Dispatcher Requests";
    public static final String queryCreatedAfterEntry = "Created After";
    public static final String queryIDEntry = "ID";
    public static final String queryRevisionEntry = "Revision";

    public static final String documentRevisionType = "GET6DocumentRevision";
    public static final String electPartRevisionType = "GET6ElectPartRevision";
    public static final String mechPartRevisionType = "GET6MechPartRevision";
    public static final String specsRevisionType = "GET6SpecsRevision";
    public static final String ugpartDatasetType = "UGPART";
    public static final String msexcelDatasetType = "MSExcel";
    public static final String bctinspectorDatasetType = "GET6BctInspector";
    public static final String pdfDatasetType = "PDF";
    public static final String textDatasetType = "Text";
    public static final String textnamedrefName = "Text";
    public static final String pdfreferenceType = "PDF_Reference";
    public static final String textreferencetype = "Text";
    public static final String imanspecificationRelType = "IMAN_specification";
    public static final String imanmanifestationRelType = "IMAN_manifestation";
    public static final String creationDateAttr = "creation_date";
    public static final String currentStateAttr = "currentState";
    public static final String providerNameAttr = "providerName";
    public static final String rootTargetAttachmentsAttr = "root_target_attachments";
    public static final String rootTaskAttr = "root_task";
    public static final String serviceNameAttr = "serviceName";
    public static final String taskIDAttr = "taskID";
    public static final String primaryObjectsAttr = "primaryObjects";
    public static final String secondaryObjectsAttr = "secondaryObjects";
    public static final String currentNameAttr = "current_name";
    public static final String itemsTagAttr = "items_tag";
    public static final String itemIDAttr = "item_id";
    public static final String itemrevisionIDAttr = "item_revision_id";
    public static final String priobjuidAttr = "priobjuid";
    public static final String secobjuidAttr = "secobjuid";
    public static final String fnd0PartIdentifierAttr = "fnd0PartIdentifier";
    public static final String itemidAttr = "itemid";
    public static final String revisionidAttr = "revisionid";
    public static final String objectNameAttr = "object_name";
    public static final String objectTypeAttr = "object_type";
    public static final String structureRevisionsAttr = "structure_revisions";
    public static final String refListAttr = "ref_list";
    public static final String lastModDateAttr = "last_mod_date";
    public static final String blChildlinesAttr = "bl_child_lines";
    public static final String GETNXToPvDirectServiceName = "nxtopvdirect";
    public static final String GETPreviewServiceServiceName = "getpreviewservice";

    public static final String teamcenterDateFormat = "dd-MMM-yyyy HH:mm";
    public static final String latestworkingRevisionRule = "Latest Working";
    public static final String EPMCompleteAction = "SOA_EPM_complete_action";
    public static final String failureResult = "FAILURE";
    public static final String successResult = "SUCCESS";

    public static final String SEMICOLON = ";";

    /**
     * Returns resultant objects of the query
     * 
     * @param strQueryName - name of the saved query to execute
     * @param strQueryEntrys - Array of query entries
     * @param strQueryValues - Array of values corresponding to query entries
     * @return - array of resultant objects of query
     */
    public static ModelObject[] queryObject(String strQueryName, String[] strQueryEntrys, String[] strQueryValues) throws Exception
    {
        ModelObject[] foundObjs = null;

        SavedQueryService savedQueryService = SavedQueryService.getService(SoaHelper.getSoaConnection());
        FindSavedQueriesCriteriaInput input = new FindSavedQueriesCriteriaInput();
        input.queryNames = new String[]{strQueryName};
        FindSavedQueriesResponse response = savedQueryService.findSavedQueries(new FindSavedQueriesCriteriaInput[]{input});
        if (response.savedQueries == null || response.savedQueries.length == 0)
        {
            System.out.println("No Teamcenter Saved Query found with the given name");
        }

        QueryInput savedQueryInput[] = new QueryInput[1];
        savedQueryInput[0] = new QueryInput();
        savedQueryInput[0].query = response.savedQueries[0];
        savedQueryInput[0].maxNumToReturn = 10000;
        savedQueryInput[0].limitList = new ModelObject[0];
        savedQueryInput[0].entries = strQueryEntrys;
        savedQueryInput[0].values = strQueryValues;
        SavedQueriesResponse savedQueriesResponseObj = savedQueryService.executeSavedQueries(savedQueryInput);
        if (savedQueriesResponseObj.arrayOfResults != null && savedQueriesResponseObj.arrayOfResults.length > 0)
        {
            QueryResults queryResultsObj = savedQueriesResponseObj.arrayOfResults[0];
            DataManagementService dmService = DataManagementService.getService(SoaHelper.getSoaConnection());
            ServiceData serviceData = dmService.loadObjects(queryResultsObj.objectUIDS);
            String errorMessage = getErrorFromServiceData(serviceData);
            if (errorMessage != null)
            {
                throw new Exception(errorMessage);
            }
            if ( serviceData.sizeOfPlainObjects() > 0)
            {
                List<ModelObject> foundObjsList = new ArrayList<ModelObject>();
                for ( int index = 0; index < serviceData.sizeOfPlainObjects(); index++ )
                {
                    foundObjsList.add(serviceData.getPlainObject(index));
                }
                foundObjs = foundObjsList.toArray(new ModelObject[foundObjsList.size()]);
            }
        }

        return foundObjs;
    }

    /**
     * Method to get error message from service data
     *
     * @param serviceData - ServiceData instance of any SOA Response Object 
     * @return errorMessage - A String containing the consolidated error messages from the Service Data or null if there are no errors
     */
    public static String getErrorFromServiceData(ServiceData serviceData)
    {
        String errorMessage = null;
        if (serviceData != null && serviceData.sizeOfPartialErrors() > 0)
        {
            StringBuilder messageBuffer = new StringBuilder();
            for (int index = 0; index < serviceData.sizeOfPartialErrors(); index++)
            {
                for (String message : serviceData.getPartialError(index).getMessages())
                {
                    messageBuffer.append(message).append("\n");
                }
            }
            errorMessage = messageBuffer.toString();
        }

        return errorMessage;
    }
}
