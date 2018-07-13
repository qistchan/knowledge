
package com.get.ontrack.getrans;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.get.ontrack.common.GETConstants;
import com.get.ontrack.getrans.clientx.GETSession;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.services.strong.core._2007_01.DataManagement.GetItemFromIdPref;
import com.teamcenter.services.strong.core._2007_01.DataManagement.RelationFilter;
import com.teamcenter.services.strong.core._2007_06.DataManagement.RelationAndTypesFilter;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsData2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsPref2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsResponse2;
import com.teamcenter.services.strong.core._2008_06.DataManagement.AttrInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.DatasetFilter;
import com.teamcenter.services.strong.core._2008_06.DataManagement.DatasetInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.DatasetOutput;
import com.teamcenter.services.strong.core._2008_06.DataManagement.DatasetRelationFilter;
import com.teamcenter.services.strong.core._2008_06.DataManagement.GetItemAndRelatedObjectsInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.GetItemAndRelatedObjectsItemOutput;
import com.teamcenter.services.strong.core._2008_06.DataManagement.GetItemAndRelatedObjectsResponse;
import com.teamcenter.services.strong.core._2008_06.DataManagement.ItemInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.NROutput;
import com.teamcenter.services.strong.core._2008_06.DataManagement.RevInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.RevisionOutput;
import com.teamcenter.services.strong.core._2009_10.DataManagement.GetItemFromAttributeInfo;
import com.teamcenter.services.strong.core._2009_10.DataManagement.GetItemFromAttributeResponse;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.Property;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.Dataset;
import com.teamcenter.soa.client.model.strong.ImanFile;
import com.teamcenter.soa.client.model.strong.ImanRelation;
import com.teamcenter.soa.client.model.strong.Item;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.soa.client.model.strong.POM_application_object;

/**
 * Class to perform different operations in the DataManagementService
 *
 *@author TCSL
 */
public class GETDataManagement
{
	private static DataManagementService dmService;
	

	private static final String clientID = "GETTransPLMLite";

	private static GETDataManagement m_instance;
	
	//private static GETSession session;

	/**
	 * Constructor for the class GETDataManagement. This is a private constructor that cannot be called from outside this class
	 * 
	 * @param connection - Connection object for the session
	 */
	private GETDataManagement(Connection connection)
	{
	    dmService = DataManagementService.getService(connection);
	}
	
	/**
	 * Static Singleton method to return the instance of the class GETDataManagement.
     *
     * @param connection - Connection object for the session
     * @return an instance of the class GETDataManagement
	 */
	public static GETDataManagement getDMService(Connection connection)
	{
		if(m_instance == null)
		{
			m_instance = new GETDataManagement(connection);
		}

		return m_instance;
	}

	/**
	 * Method to load objects to memory
	 * 
	 * @param objectUIDS - Array of UIDs of objects to be loaded
	 * @return modelObjects - An array of ModelObject instances from the given input UIDs
	 */
	public ModelObject[] loadObjects(String[] objectUIDS) throws Exception
	{
	    ModelObject[] modelObjects = null;
	    //dmService = DataManagementService.getService(session.getConnection());
		ServiceData serviceData = null;
		serviceData = dmService.loadObjects(objectUIDS);
		String errorMessage = GETCommon.getErrorFromServiceData(serviceData);
		if (errorMessage != null && !errorMessage.isEmpty())
		{
		    throw new Exception(errorMessage);
		}
		if (serviceData.sizeOfPlainObjects() > 0)
		{
		    modelObjects = new ModelObject[serviceData.sizeOfPlainObjects()];
		    for (int index = 0; index < serviceData.sizeOfPlainObjects(); index++)
		    {
		        modelObjects[index] = serviceData.getPlainObject(index);
		    }
		}

		return modelObjects;
	}

	/**
	 * Method to load the given properties to memory for the given objects
	 * 
	 * @param modelObjects - Array of Model Objects
	 * @param strings - Array of properties to be loaded for the given Model Objects
	 */
	public void getProperties(ModelObject[] modelObjects, String[] strings) throws Exception
	{
		ServiceData serviceData = null;
		serviceData = dmService.getProperties(modelObjects, strings);
		String errorMessage = GETCommon.getErrorFromServiceData(serviceData);
		if (errorMessage != null && !errorMessage.isEmpty())
        {
            throw new Exception(errorMessage);
        }
	}
	
	 /**
     * Method to get the latest created object
     * 
     * @param objects - Array of model objects
     * @return ModelObject - Latest created object among the given objects
     */
    public ModelObject getLatestCreatedObject(ModelObject[] objects) throws Exception
    {
    	getProperties(objects, new String[]{GETConstants.BusinessObjects.Properties.strCreationDate});
        ModelObject latestCreatedObj = objects[0];
        Calendar latestCreationDate = ((POM_application_object)objects[0]).get_creation_date();
        for(ModelObject obj : objects)
        {
            Calendar creationDate = ((POM_application_object)objects[objects.length - 1]).get_creation_date();
            if(creationDate.compareTo(latestCreationDate) > 0)
            {
                latestCreatedObj = obj;
            }
        }

        return latestCreatedObj;
    }
    
//    /**
//     * Method to get latest created Revisions and associated Datasets of the Revision with the given Relation
//     * 
//     * @param itemArr - Array of items whose latest revisions are to be retrieved
//     * @param relnMap - Map of Relation Type Name and Array of Type of Objects
//     * @return - itemLatestRevDatasetMap - Map of Item and Map of Latest Revision and Array of associated Datasets
//     */
//    public Map<ModelObject, Map<ModelObject, Dataset[]>> getLatestCreatedRevs(ModelObject[] itemArr, Map<String, String[]> relnMap)
//    {
//        Map<ModelObject, Map<ModelObject, Dataset[]>> itemLatestRevDatasetMap = null;
//
//        try
//        {
//            /*"item_id", "object_type"*/
//            GetItemFromAttributeInfo[] attrInfo = new GetItemFromAttributeInfo[itemArr.length];
//            GetItemFromIdPref itemFromIdPref = new GetItemFromIdPref();
//            int nRev = 1;
//            RelationFilter[] relnFilter = null;
//            if(relnMap != null && relnMap.size() > 0)
//            {
//                relnFilter = new RelationFilter[relnMap.size()];
//                int relnMapIndex = 0;
//                for(Map.Entry<String, String[]> entry : relnMap.entrySet())
//                {
//                    relnFilter[relnMapIndex] = new RelationFilter();
//                    relnFilter[relnMapIndex].relationTypeName = entry.getKey();
//                    relnFilter[relnMapIndex++].objectTypeNames = entry.getValue();
//                }
//                itemFromIdPref.prefs = relnFilter;
//            }
//
//        //   getProperties(itemArr, new String[]{GETConstants.BusinessObjects.Properties.strItemID});
//           
//           for(int itemIndex = 0; itemIndex < itemArr.length; itemIndex++)
//           {
//        	   Item item = (Item)itemArr[itemIndex]; 
//               attrInfo[itemIndex] = new GetItemFromAttributeInfo();
//               Map<String, String> itemAttrMap = new HashMap<String, String>();
//               itemAttrMap.put(GETConstants.BusinessObjects.Properties.strItemID, (item.get_item_id()));
//               itemAttrMap.put(GETConstants.BusinessObjects.Properties.strObjectType, (item.get_object_type()));
//               attrInfo[itemIndex].revIds = new String[]{""};
//               attrInfo[itemIndex].itemAttributes = itemAttrMap;
//           }
//
//           GetItemFromAttributeResponse attrResponse = dmService.getItemFromAttribute(attrInfo, nRev, itemFromIdPref);
//           GETCommon.getErrorFromServiceData(attrResponse.serviceData);
//           for(int outIndex = 0; outIndex < attrResponse.output.length; outIndex++)
//           {
//               Map<ModelObject, Dataset[]> latestRevDatasetMap = new HashMap<ModelObject, Dataset[]>();
//               for(int revIndex = 0; revIndex < attrResponse.output[outIndex].itemRevOutput.length; revIndex++)
//               {
//                   latestRevDatasetMap.put(attrResponse.output[outIndex].itemRevOutput[revIndex].itemRevision, attrResponse.output[outIndex].itemRevOutput[revIndex].datasets);
//               }
//               if(itemLatestRevDatasetMap == null)
//               {
//                   itemLatestRevDatasetMap = new HashMap<ModelObject, Map<ModelObject, Dataset[]>>();
//               }
//               itemLatestRevDatasetMap.put(attrResponse.output[outIndex].item, latestRevDatasetMap);
//           }
//        }
//        catch (Exception e)
//        {
//            e.printStackTrace();
//        }
//
//        return itemLatestRevDatasetMap;
//    }
    
    /**
     * Method to find Item and get its associated item revisions and associated datasets with specified relations and attributes
     * 
     * @param itemAttrInfoMapList - List of Map of attr name and attr value for finding/retrieving info of item
     * @param revProcessing - String - To get info of specific revision("ids") or no. of revisions("nRevs")
     * @param nRevList - List of integers of no. of most recent revisions to be retrieved for each corresponding item in itemAttrInfoMapList(in case revProcessing is specified as "nRevs" else pass null)
     * @param revIDList - List of revIds which are to be retrieved(1 rev) for each corresponding item in itemAttrInfoMapList(in case revProcessing is specified as "ids" else pass null)
     * @param datasetRelationFilterMapList - List of Map of Relation Type name, array of Dataset Type name that is to be retrieved for each revision corresponding to each item
     * 
     * @return result -  Map of Item, map of item revision, Map of Dataset, Map of relation name, Map of Named Reference, named reference name
     */
    public Map<Item, Map<ItemRevision, Map<Dataset, Map<String, Map<ModelObject, String>>>>> getItemAndRelatedObjects(List<Map<String, String>> itemAttrInfoMapList, String revProcessing, 
            List<Integer> nRevList, List<String> revIDList, List<Map<String, String[]>> datasetRelationFilterMapList)
    {
        Map<Item, Map<ItemRevision, Map<Dataset, Map<String, Map<ModelObject, String>>>>> result = null;
        try
        {
            GetItemAndRelatedObjectsResponse itemAndRelatedObjectsResponse = null;
            GetItemAndRelatedObjectsInfo[] itemAndRelatedObjectsInfoInput = new GetItemAndRelatedObjectsInfo[itemAttrInfoMapList.size()];
            
            int index = 0;
            for(Map<String, String> itemAttrInfoMap : itemAttrInfoMapList)
            {
                itemAndRelatedObjectsInfoInput[index] = new GetItemAndRelatedObjectsInfo();
                
                ItemInfo itemInfo = new ItemInfo();
                AttrInfo[] itemAttrInfoArray = new AttrInfo[itemAttrInfoMap.size()];
                int attrMapIndex = 0;
                for(Map.Entry<String, String> entry : itemAttrInfoMap.entrySet())
                {
                    itemAttrInfoArray[attrMapIndex] = new AttrInfo();
                    itemAttrInfoArray[attrMapIndex].name = entry.getKey();
                    itemAttrInfoArray[attrMapIndex++].value = entry.getValue();
                }
                itemInfo.clientId = clientID;
                itemInfo.useIdFirst = false;
                itemInfo.ids = itemAttrInfoArray;
                
                RevInfo revinfo = new RevInfo();
                revinfo.clientId = clientID;
                if(revProcessing.equals("ids"))
                {
                    revinfo.id = revIDList.get(index);
                    revinfo.useIdFirst = true;
                }
                {
                    revinfo.nRevs = nRevList.get(index);
                    revinfo.useIdFirst = false;
                }
                
                revinfo.processing = revProcessing;
                DatasetInfo dsInfo = new DatasetInfo();
                DatasetFilter dsFilter = new DatasetFilter();
                dsFilter.useNameFirst = false;
                dsFilter.processing = "Min";
                
                Map<String, String[]> datasetRelationFilterMap = datasetRelationFilterMapList.get(index);
                
                //calculate no. of elements
                int dsCount = 0;
                for(Map.Entry<String, String[]> entry : datasetRelationFilterMap.entrySet())
                {
                    dsCount += entry.getValue().length;
                }

                DatasetRelationFilter[] dsRelnFilterArray = new DatasetRelationFilter[dsCount];
                int dsRelnIndex = 0;
                for(Map.Entry<String, String[]> entry : datasetRelationFilterMap.entrySet())
                {
                    for(String dsType : entry.getValue())
                    {
                        dsRelnFilterArray[dsRelnIndex] = new DatasetRelationFilter();
                        dsRelnFilterArray[dsRelnIndex].relationTypeName = entry.getKey();
                        dsRelnFilterArray[dsRelnIndex++].datasetTypeName = dsType;
                    }
                }
                dsFilter.relationFilters = dsRelnFilterArray;
                dsInfo.clientId = clientID;
                dsInfo.filter = dsFilter;
                
                itemAndRelatedObjectsInfoInput[index].clientId = clientID;
                itemAndRelatedObjectsInfoInput[index].datasetInfo = dsInfo;
                itemAndRelatedObjectsInfoInput[index].itemInfo = itemInfo;
                itemAndRelatedObjectsInfoInput[index++].revInfo = revinfo;
            }
    
            itemAndRelatedObjectsResponse = dmService.getItemAndRelatedObjects(itemAndRelatedObjectsInfoInput);
            result = new HashMap<Item, Map<ItemRevision, Map<Dataset, Map<String, Map<ModelObject, String>>>>>();
            
            for(GetItemAndRelatedObjectsItemOutput itemOut :  itemAndRelatedObjectsResponse.output)
            {
                Map<ItemRevision, Map<Dataset, Map<String, Map<ModelObject, String>>>> revisionOutMap = new HashMap<ItemRevision, Map<Dataset, Map<String, Map<ModelObject, String>>>>();
                for(RevisionOutput revOut :  itemOut.itemRevOutput)
                {
                    Map<Dataset, Map<String, Map<ModelObject, String>>> dsOutMap = new HashMap<Dataset, Map<String, Map<ModelObject, String>>>();
                    Map<String, Map<ModelObject, String>> relnOutMap = new HashMap<String, Map<ModelObject, String>>();
                    for(DatasetOutput dsOut :  revOut.datasetOutput)
                    {
                        Map<ModelObject, String> nrOutmap = new HashMap<ModelObject, String>();
                        for(NROutput nrOut : dsOut.namedReferenceOutput)
                        {
                            nrOutmap.put(nrOut.namedReference, nrOut.namedReferenceName);
                        }
                        relnOutMap.put(dsOut.relationTypeName, nrOutmap);
                        dsOutMap.put(dsOut.dataset, relnOutMap);
                    }
                    revisionOutMap.put(revOut.itemRevision, dsOutMap);
                }
                result.put(itemOut.item, revisionOutMap);
            }
        }

        catch(Exception ex)
        {
            ex.printStackTrace();
        }

        return result;
    }
	
    /**
     * Retrieves secondary objects of given type with given relation for the given primary objects
     * 
     * @param primaryObjs
     * @param relnMap - Map of relation name and array of type of objects
     * @return Map of Primary model object and map of relation and secondary model object
     */
	public Map<ModelObject, Map<ImanRelation, ModelObject>> getSecObjects(ModelObject[] primaryObjs, Map<String , String[] > relnMap, boolean returnRelations, boolean expandRev)
    {
		Map<ModelObject, Map<ImanRelation, ModelObject>> grmSecRelMap = null;
    	try 
    	{
	    	ExpandGRMRelationsPref2 prefInput = new ExpandGRMRelationsPref2();
	    	prefInput.expItemRev = expandRev;
	    	prefInput.returnRelations = returnRelations;
	    	RelationAndTypesFilter[] relnAndTypeFilter = new RelationAndTypesFilter[relnMap.size()];
	    	int index = 0;

	    	for (Map.Entry<String, String[]> entry : relnMap.entrySet())
	    	{
	    		relnAndTypeFilter[index] = new RelationAndTypesFilter();
		    	relnAndTypeFilter[index].otherSideObjectTypes = entry.getValue();
		    	relnAndTypeFilter[index].relationTypeName = entry.getKey();
		    	index++;
	    	}

	    	prefInput.info = relnAndTypeFilter;
	    	ExpandGRMRelationsResponse2 grmResponseOut = dmService.expandGRMRelationsForPrimary(primaryObjs, prefInput);

			if(grmResponseOut.output.length > 0)
			{
				grmSecRelMap = new HashMap<ModelObject, Map<ImanRelation, ModelObject>>();
			}
			
			for(int outIndex = 0; outIndex < grmResponseOut.output.length; outIndex++)
			{
			    Map<ImanRelation, ModelObject> relnObjMap = null;
				ModelObject inputObject = grmResponseOut.output[outIndex].inputObject;
				ExpandGRMRelationsData2[] relDataOut = grmResponseOut.output[outIndex].relationshipData;
				for(int relDataIndex = 0; relDataIndex < relDataOut.length; relDataIndex++)
				{
					for(int dataIndex = 0; dataIndex < relDataOut[relDataIndex].relationshipObjects.length; dataIndex++)
					{
					    if(relnObjMap == null)
					    {
					        relnObjMap = new HashMap<ImanRelation, ModelObject>();
					    }
						relnObjMap.put(relDataOut[relDataIndex].relationshipObjects[dataIndex].relation, relDataOut[relDataIndex].relationshipObjects[dataIndex].otherSideObject);
					}
				}
				if(relnObjMap != null)
				{
				    grmSecRelMap.put(inputObject, relnObjMap);
				}
			}
    	}
    	catch (Exception e) 
    	{
			e.printStackTrace();
		}

    	return grmSecRelMap;
    }

	/**
	 * Returns list of named reference imanfiles of the given dataset
	 * 
	 * @param dataset
	 * @return List of imanfiles
	 */
	public List<ImanFile> getDSNamedRefs(Dataset dataset)
	{
		List<ImanFile> imfList = null;
		try
		{
			getProperties(new ModelObject[]{dataset}, new String[]{GETConstants.BusinessObjects.Properties.strRefListName});
			ModelObject[] refList = dataset.get_ref_list();
			if((refList != null)  && (refList.length > 0)) 
			{
				if(imfList == null)
				{
					imfList = new ArrayList<ImanFile>();
				}

				for(int inx = 0; inx < refList.length; inx++) 
				{
					if(refList[inx] != null) 
					{
						ImanFile imfObj;
						imfObj = (ImanFile)refList[inx];
						if(imfObj != null) 
						{
							imfList.add(imfObj);
						}
					}
				}
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}
		return imfList;
	}

	/**
	 * Function to return value(array/single) of given property
	 * 
	 * @param mo - ModelObject
	 * @param attr - Attribute name
	 * @param propsLoaded - Boolean specifying whether attr is loaded
	 * @return List of String - Property value(s)
	 * @throws Exception 
	 */
    public List<String> getPropertryValues(ModelObject mo, String attr, boolean propsLoaded) throws Exception
    {
        List<String> result = null;
      //  dmService = DataManagementService.getService(session.getConnection());
        try
        {
//            if(!propsLoaded)
//            {
//               // getProperties(new ModelObject[]{mo}, new String[]{attr});
//            	dmService.getProperties(new ModelObject[]{mo}, new String[]{attr});
//               // dmService.getProperties(modelObjects, strings);
//            }

            Property prop = mo.getPropertyObject(attr);
            if(prop.getPropertyDescription().isArray())
            {
                result = mo.getPropertyDisplayableValues(attr);
            }
            else
            {
                String propValue = mo.getPropertyDisplayableValue(attr);
                result = new ArrayList<String>();
                result.add(propValue);
            }
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
            throw ex;
        }

        return result;
    } 
}
