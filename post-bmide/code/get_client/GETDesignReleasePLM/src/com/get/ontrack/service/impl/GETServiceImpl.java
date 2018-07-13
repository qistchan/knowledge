package com.get.ontrack.service.impl;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.Vector;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;

import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.get.ontrack.common.GETDesignReleaseConstants;
import com.get.ontrack.common.ExportToExcel;
import com.get.ontrack.common.GETDesignReleaseCommonOperations;
import com.get.ontrack.common.PLMConstants;
import com.get.ontrack.dao.GETDao;
import com.get.ontrack.model.DesignRelease;
import com.get.ontrack.model.EdotLinkedData;
import com.get.ontrack.model.GETUser;
import com.get.ontrack.model.LinkECRData;
import com.get.ontrack.model.TaskData;
import com.get.ontrack.service.GETService;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.Item;

/**
 * This class is used to call the methods of GETDao
 * @author 455613
 */
@Service
public class GETServiceImpl implements GETService {

	
	private Map<String, GETDao> daoMap;
	private GETDesignReleaseCommonOperations commonOp = new GETDesignReleaseCommonOperations();
	private List<DesignRelease> designRelList = new ArrayList<DesignRelease>();
	private boolean isEdotImplemented = false;
	List<Object> getProjList = null;
	private GETDao getDaoMap(String sessionId){
		GETDao dao = null;
		try {
			if(daoMap == null){
				daoMap = new HashMap<String, GETDao>();
			}
			if(daoMap.containsKey(sessionId)){
				dao = daoMap.get(sessionId);
			}else{
				dao = new GETDao();
				daoMap.put(sessionId, dao);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return dao;
	}

	/**
	 * This method authenticate's User
	 * and initialize session
	 * @return 
	 */
	public  List<Object> login(GETUser getUser, String serverURL) throws Exception {
		GETDao dao = getDaoMap(getUser.getSessionId());
		try {
			getProjList = new ArrayList<Object>();
			dao.setHost(serverURL);
			dao.login(getUser.getUserID(), getUser.getUserPassword(), getUser);
			List<String> getProjects = dao.listGetProjects(PLMConstants.getProject, new String[]{GETDesignReleaseConstants.Properties.itemId}, "*");
			getProjList.add(getProjects);
		} catch (Exception e) {
			throw new Exception(e.getMessage());
		}
		return getProjList;
	}
	
	
	public  List<Object> ssoLogin(String serverURL,GETUser getUser, String ssoAppId, String ssoURL) throws Exception {
		GETDao dao = getDaoMap(getUser.getSessionId());
		try {
			getProjList = new ArrayList<Object>();
			dao.setHost(serverURL);
			dao.ssoLogin( getUser,ssoAppId,ssoURL);
			
			List<String> getProjects = dao.listGetProjects(PLMConstants.getProject, new String[]{GETDesignReleaseConstants.Properties.itemId}, "*");
			getProjList.add(getProjects);
		} catch (Exception e) {
			throw new Exception(e.getMessage());
		}
		return getProjList;
	}
	
	/****************************************************************************
	 * Description: 
	 * @param appUserID
	 * @param ssoSessionKey
	 * @return
	 ****************************************************************************/
	@Override
	public List<Object> ssoLoginWithSessionKey(String serverURL,String appUserID, String ssoSessionKey, GETUser getUser, String ssoAppId, String ssoURL)  throws Exception {
		// TODO Auto-generated method stub
		GETDao dao = getDaoMap(getUser.getSessionId());
		try {
			getProjList = new ArrayList<Object>();
			dao.setHost(serverURL);
			dao.ssoLogin( getUser,ssoAppId,ssoURL);
			List<String> getProjects = dao.listGetProjects(PLMConstants.getProject, new String[]{GETDesignReleaseConstants.Properties.itemId}, "*");
			getProjList.add(getProjects);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			throw new Exception(e.getMessage());
		}
		return getProjList;
	}
	
	
	public List<Object> getGETProject(GETUser getUser) throws Exception {
		return getProjList;
	}
	
		
	/**
	 * This method gets projects list
	 */
	public List<String> getProjects(String sessionId) throws Exception{
		GETDao dao = getDaoMap(sessionId);
		List<String> getProjects = dao.listGetProjects(PLMConstants.getProject, new String[]{GETDesignReleaseConstants.Properties.itemId}, "*");
		return getProjects;
	}
	
	/**
	 * This method gets projects data
	 */
	public Map<String,List<String>> getProjectData(String sessionId,String projectId) throws Exception{
		GETDao dao = getDaoMap(sessionId);
		Map<String, List<String>> projectDataMap = null;
		try {
//			ModelObject mo = dao.itemToModelObjects(projectId);
			Item projectItem = dao.getItem(projectId, GETDesignReleaseConstants.BuinessObjects.GETProject);
			projectDataMap = dao.getProjectProperties(projectItem);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return projectDataMap;
	}
	
	/**
	 * This method gets project associated design items
	 */
	@SuppressWarnings("deprecation")
	public List<DesignRelease> getAssociatedDesignItems(String sessionId,String projectId,List<String> p1DateList, GETUser getuser) throws Exception{
		GETDao dao = getDaoMap(sessionId);
		SimpleDateFormat dateFormatter = new SimpleDateFormat("dd-MMM-yyyy");
		List<DesignRelease> designReleaseList = null;
		
		try {
//			ModelObject mo = dao.itemToModelObjects(projectId);
			designReleaseList = new ArrayList<>();
//			Map<ModelObject, Map<String, List<String>>> projectsDR= dao.getDesignReleaseData(projectId, mo, getuser);
			Map<ModelObject, Map<String, List<String>>> projectsDR= dao.getDesignReleaseData(projectId, getuser);
			if(!CollectionUtils.isEmpty(p1DateList)){
				String piDateValue= p1DateList.get(0);
				if ( piDateValue != null && piDateValue.length() > 0 ){
					Date p1Date = dateFormatter.parse(piDateValue);
					for(Map.Entry<ModelObject,Map<String,List<String>>> entry : projectsDR.entrySet()){
						designReleaseList.add(generateDesignReleaseObj( entry.getValue(), projectId, p1Date));
					}
					if(designReleaseList != null  && designReleaseList.size() > 0)
					{
						designRelList = designReleaseList;
						
						// getEdotData();
					}
			
				}
			}

		} catch (Exception e) {
			// TODO Auto-generated catch block
		//	throw e;
			e.printStackTrace();
		}
		//Collections.sort(designReleaseList);
		return designReleaseList;
	}
	
	public List<LinkECRData> getEdotData(String sessionId) throws Exception //may need session id here
	{
		
		List<LinkECRData> dataList = new ArrayList<LinkECRData>();
		LinkECRData linkECRData=new LinkECRData(); 
		GETDao dao = getDaoMap(sessionId);
		for (int inx = 0; inx < designRelList.size(); inx++) {
			DesignRelease edotRowData = (DesignRelease) designRelList.get(inx);
			//strStatus = edotRowData.getStatus();
			System.out.println("edotRowData.getDesignReleaseId()-->"+edotRowData.getDesignReleaseId());
			if((edotRowData.getStatus().contains("ECR")) && (!dao.getLinkedECRToEdot(edotRowData.getDesignReleaseId())))
			{
				linkECRData = new LinkECRData();
				linkECRData.setBomLineItemId(edotRowData.getBomLineItemId());
				linkECRData.setDescription(edotRowData.getDescription());
				linkECRData.setDesignReleaseId(edotRowData.getDesignReleaseId());
				dataList.add(linkECRData);
			}
		}
		
		return dataList;
	}
	
	public List<EdotLinkedData> getLinkedECNAndTD(String strEdot) throws Exception
	{
		EdotLinkedData linkEdotData;
		List<EdotLinkedData> dataList = new ArrayList<EdotLinkedData>();
		for (int inx = 0; inx < designRelList.size(); inx++) {
			DesignRelease edotRowData = (DesignRelease) designRelList.get(inx);
			if(edotRowData.getDesignReleaseId().equals(strEdot))
			{
				linkEdotData = new EdotLinkedData();
				if(((edotRowData.getDesignECN() != null) && (!edotRowData.getDesignECN().equals(""))) || (((edotRowData.getTechnicalData() != null) && (!edotRowData.getTechnicalData().equals("")))))
				{
					linkEdotData.setEdotId(strEdot);
					linkEdotData.setEcnId(edotRowData.getDesignECN());
					linkEdotData.setTechData(edotRowData.getTechnicalData());
					dataList.add(linkEdotData);
					
				}
			}
		}
		return dataList;
	}
	
	/**
	 * This method gets Template Scopes map
	 */
	public Map<String,List<TaskData>> getTemplateScope(String sessionId,String template,String scope) throws Exception{ 
		GETDao dao = getDaoMap(sessionId);
		Map<String,File> vfiles = dao.getImanFile(PLMConstants.item, PLMConstants.designReleaseTemplate);
		Vector<File> vfiles1 = new Vector<File>();
		String templateScope = template + "-"+scope;
		if(!CollectionUtils.isEmpty(vfiles)){
			for (Map.Entry<String,File> entry : vfiles.entrySet()) {
				String key = entry.getKey();
				String fileName = key.substring(0, key.indexOf("."));
		        if(fileName.equalsIgnoreCase(templateScope)){
		        	vfiles1.add(entry.getValue());
		        }
		    }
		}
		
		TaskData tdata = new TaskData();
		Map<String,List<TaskData>> map = new TreeMap<String,List<TaskData>>();
		if(null != vfiles1){
			try {
					File fXmlFile = new File(vfiles1.elementAt(0).getPath());
					DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
					DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
					Document doc = dBuilder.parse(fXmlFile);
					doc.getDocumentElement().normalize();
					NodeList nList = doc.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.taskData);
					for (int temp = 0; temp < nList.getLength(); temp++) {
						Node nNode = nList.item(temp);
						if (nNode.getNodeType() == Node.ELEMENT_NODE) {
							Element eElement = (Element) nNode;
							tdata = new TaskData();
							tdata.setActivityId(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.activityId).item(0).getTextContent());
							tdata.setDescription(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.description).item(0).getTextContent());
							tdata.setDesignComponentNo(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.designComponentNo).item(0).getTextContent());
							tdata.setEngrComponentNo(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.engrComponentNo).item(0).getTextContent());
							
							tdata.setEngrOrgProject(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.engrComponentNo).item(0).getTextContent());
							tdata.setDesignOrgProject(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.designComponentNo).item(0).getTextContent());
							
							tdata.setBackOff(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.backOff).item(0).getTextContent());
							tdata.setEngrDuration(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.engrDuration).item(0).getTextContent());
							tdata.setDesignDuration(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.designDuration).item(0).getTextContent());
							String root = tdata.getActivityId().substring(0, 2);
							if(temp == 0){
								List<TaskData> tList = new ArrayList<>();
								tList.add(tdata);
								map.put(root,tList);
							}else{
								if(map.containsKey(root)){
									List<TaskData> tList = map.get(root);
									tList.add(tdata);
									map.put(root,tList);
								}else{
									List<TaskData> tList = new ArrayList<>();
									tList.add(tdata);
									map.put(root,tList);
								}
							}
							
						}
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		
		return map;
	}
	
	/**
	 * This method gets Template Scopes files
	 */
	public Map<String,Map<String,List<TaskData>>> getTemplateScopeFiles(String sessionId,String template,String scope) throws Exception{ 
		GETDao dao = getDaoMap(sessionId);
		Map<String,File> vfiles = dao.getImanFile(PLMConstants.item, PLMConstants.designReleaseTemplate);
		Map<String,Map<String,List<TaskData>>> templateScopeFiles = new TreeMap<String,Map<String,List<TaskData>>>();
		if(!CollectionUtils.isEmpty(vfiles)){
			for (Map.Entry<String,File> entry : vfiles.entrySet()) {
				String key = entry.getKey();
				String fileName = key.substring(0, key.indexOf("."));
				TaskData tdata = new TaskData();
				Map<String,List<TaskData>> map = new TreeMap<String,List<TaskData>>();
				if(null != entry.getValue()){
					try {
							File fXmlFile = new File(entry.getValue().getPath());
							DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
							DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
							Document doc = dBuilder.parse(fXmlFile);
							doc.getDocumentElement().normalize();
							NodeList nList = doc.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.taskData);
							for (int temp = 0; temp < nList.getLength(); temp++) {
								Node nNode = nList.item(temp);
								if (nNode.getNodeType() == Node.ELEMENT_NODE) {
									Element eElement = (Element) nNode;
									tdata = new TaskData();
									tdata.setActivityId(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.activityId).item(0).getTextContent());
									tdata.setDescription(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.description).item(0).getTextContent());
									tdata.setDesignComponentNo(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.designComponentNo).item(0).getTextContent());
									tdata.setEngrComponentNo(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.engrComponentNo).item(0).getTextContent());
									
									tdata.setEngrOrgProject(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.engrComponentNo).item(0).getTextContent());
									tdata.setDesignOrgProject(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.designComponentNo).item(0).getTextContent());
									
									tdata.setBackOff(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.backOff).item(0).getTextContent());
									tdata.setEngrDuration(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.engrDuration).item(0).getTextContent());
									tdata.setDesignDuration(eElement.getElementsByTagName(GETDesignReleaseConstants.TemplateScope.designDuration).item(0).getTextContent());
									String root = tdata.getActivityId().substring(0, 2);
									if(temp == 0){
										List<TaskData> tList = new ArrayList<>();
										tList.add(tdata);
										map.put(root,tList);
									}else{
										if(map.containsKey(root)){
											List<TaskData> tList = map.get(root);
											tList.add(tdata);
											map.put(root,tList);
										}else{
											List<TaskData> tList = new ArrayList<>();
											tList.add(tdata);
											map.put(root,tList);
										}
									}
								}
							}
						} catch (Exception e) {
							e.printStackTrace();
							throw e;
						}
					templateScopeFiles.put(fileName, map);
				}
			}
		}
		return templateScopeFiles;
	}
	
	/*
	 * Function to save the Design releases and attach to Project
	 * @see com.get.ontrack.service.GETService#saveDesignRelease(java.lang.String, java.util.List, java.lang.String)
	 */
	public String saveDesignRelease(String projectId,List<DesignRelease> designReleaseList, String sessionId)throws Exception{
		GETDao dao = getDaoMap(sessionId);
		String response = "";
		try{
			String relation = GETDesignReleaseConstants.Relation.desgnReleasePlanRelation;
			ModelObject mo = dao.itemToModelObjects(projectId);
			List<String> designRelationList = new ArrayList<String>();
			Map<String,List<String>> projectProperties = dao.getProjectProperties(mo);
			boolean releasePlainCreated = false;
			if(!CollectionUtils.isEmpty(projectProperties)){
				for (Map.Entry<String,List<String>> entry : projectProperties.entrySet()) {
					String key = entry.getKey();
					List<String> value = entry.getValue();
					if(GETDesignReleaseConstants.Relation.desgnReleasePlanRelation.equalsIgnoreCase(key)){
						if(CollectionUtils.isEmpty(value)){
							ModelObject moPlan = dao.createDesignReleasePlanItem( projectId, "Design Release Schedule" );
							List<ModelObject> moPlainList = new ArrayList<ModelObject>();
							moPlainList.add(moPlan);
							response = dao.attachDesignReleaseToProject(mo, moPlainList, relation);
							releasePlainCreated = true;
							List<ModelObject> getDesignReleases = dao.createDesignReleaseItems(designReleaseList);
							response = dao.attachDesignReleaseToProject(moPlan, getDesignReleases,  GETDesignReleaseConstants.Relation.desgnReleaseRelation);
						}else{
							designRelationList = value;
						}
					}
			    }
			}
			relation = GETDesignReleaseConstants.Relation.desgnReleaseRelation;
			if(!releasePlainCreated){
				String[] relationList = designRelationList.get(0).split("-");
				ModelObject moOfRelation = dao.itemToModelObjects(relationList[0]);
				List<ModelObject> getDesignReleases = dao.createDesignReleaseItems(designReleaseList);
				response = dao.attachDesignReleaseToProject(moOfRelation, getDesignReleases, relation);
			}
		}catch(Exception e){
			throw e;
		}
		
		if(PLMConstants.success.equalsIgnoreCase(response)){
			return PLMConstants.designAttachSuccess;
		}else{
			return response;
		}
		
	}
	
	/*
	 * to generate design release object from teamcenter's data
	 */
	public DesignRelease generateDesignReleaseObj(Map<String,List<String>> projectdata, String projectId, Date p1Date) throws ParseException{
		DesignRelease designRelease = new DesignRelease();
		designRelease.setProjectId(projectId);
		designRelease.setdP1date(p1Date);
		SimpleDateFormat dateFormatter = new SimpleDateFormat("dd-MMM-yyyy");
		SimpleDateFormat dateFormatter1 = new SimpleDateFormat("MM/dd/yyyy");
		try {
			for(Map.Entry<String,List<String>> project: projectdata.entrySet()){
				String key = project.getKey();
				List<String> valueList = project.getValue();
				String value = "";
				if(!CollectionUtils.isEmpty(valueList)){
					value = valueList.get(0);
				}
				if(GETDesignReleaseConstants.Properties.ActivityId.equalsIgnoreCase(key)){
					designRelease.setBomLineItemId(value);
					designRelease.setIndexId(value);
				} else if(GETDesignReleaseConstants.Properties.status.equalsIgnoreCase(key)) {
					if( value != null && value.length()>0 )
					{
					    designRelease.setStatus(value);
					}
					else
					{
						designRelease.setStatus("In Edit");
					}

				} else if(GETDesignReleaseConstants.Properties.autoclose.equalsIgnoreCase(key)) {
					if( value != null && value.length()>0 ){
						if( value.equalsIgnoreCase("True"))	{
							designRelease.setAutoClose(true);
						} else {
							designRelease.setAutoClose(false);
						}
					}
				} else if(GETDesignReleaseConstants.Properties.enggDateChangeReason.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setEngrDateChangeReason(value);
					}
					
				} else if(GETDesignReleaseConstants.Properties.enggComments.equalsIgnoreCase(key)){
					if(!valueList.isEmpty())
					{
						designRelease.setEngrComment(valueList.get(valueList.size()-1));
						
					}
					else
					{
						designRelease.setEngrComment("");
					}
				}
				else if(GETDesignReleaseConstants.Properties.designDateChangeReason.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDesignDateChangeReason(value);
					}
				}
				else if(GETDesignReleaseConstants.Properties.designComments.equalsIgnoreCase(key)){
					if(!valueList.isEmpty())
					{
						designRelease.setDesignComment(valueList.get(valueList.size()-1));
						
					}
					else
					{
						designRelease.setDesignComment("");
					}
				}
				else if(GETDesignReleaseConstants.Properties.ActivityDesc.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDescription(value);
					}
				}else if(GETDesignReleaseConstants.Properties.enggBackOff.equalsIgnoreCase(key)){
					
					if( value != null && value.length()>0 ){
						designRelease.setBackOff(value+"w");
					}
				}else if(GETDesignReleaseConstants.Properties.engrDuration.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setEngrDuration(value+"w");
					}
				}else if(GETDesignReleaseConstants.Properties.desgnDuration.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDesignDuration(value+"w");
					}
				/*	}else if(GETDesignReleaseConstants.Properties.enggSubGroup.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						String[] groupArray = value.split("\\.");
						designRelease.setEngrComponentNo(groupArray[0]);
					}else{
						designRelease.setEngrComponentNo("NWR");
					}
					
				}else if(GETDesignReleaseConstants.Properties.designSubGroup.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						String[] groupArray = value.split("\\.");
						designRelease.setDesignComponentNo(groupArray[0]);
					}else{
						designRelease.setDesignComponentNo("NWR");
					}*/
				}else if(GETDesignReleaseConstants.Properties.mainGroup.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setMainGroup(value);
					}else{
						designRelease.setMainGroup("");
					}
				}else if(GETDesignReleaseConstants.Properties.engrOrgProject.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setEngrOrgProject(value);
					}
					
				}else if(GETDesignReleaseConstants.Properties.designOrgProject.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDesignOrgProject(value);
					}
				}
				else if(GETDesignReleaseConstants.Properties.designResource.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDesignResource(value);
					}
			    }
				else if(GETDesignReleaseConstants.Properties.engrResource.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setEngrResource(value);
					}
			    }
				else if(GETDesignReleaseConstants.Properties.templateName.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setTemplateName(value);
					}
				}
				else if(GETDesignReleaseConstants.Properties.engrPromiseDate.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
					   designRelease.setEngrPromiseDate(dateFormatter1.format(dateFormatter.parse(value)));
					   designRelease.setEngrPromiseDateLabel(designRelease.getEngrPromiseDate()+" ("+commonOp.getFW(designRelease.getEngrPromiseDate())+")");
					} else{
						designRelease.setEngrPromiseDate("");
						designRelease.setEngrPromiseDateLabel("");
					}
				}
				else if(GETDesignReleaseConstants.Properties.desPromiseDate.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						   designRelease.setDesignPromiseDate(dateFormatter1.format(dateFormatter.parse(value)));
						   designRelease.setDesignPromiseDateLabel(designRelease.getDesignPromiseDate()+" ("+commonOp.getFW(designRelease.getDesignPromiseDate())+")");
					} else{
						designRelease.setDesignPromiseDate("");
						designRelease.setDesignPromiseDateLabel("");
					}
				}
				
				else if(GETDesignReleaseConstants.Properties.engrStartDate.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						   designRelease.setEngrStartDate(dateFormatter1.format(dateFormatter.parse(value)));
						   designRelease.setEngrStartDateLabel(designRelease.getEngrStartDate()+" ("+commonOp.getFW(designRelease.getEngrStartDate())+")");
					} else{
						designRelease.setEngrStartDate("");
						designRelease.setEngrStartDateLabel("");
					}
				}else if(GETDesignReleaseConstants.Properties.engrReqDate.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setEngrRequiredDate(dateFormatter1.format(dateFormatter.parse(value)));
						String rqdDateWeek = commonOp.getFW(designRelease.getEngrRequiredDate());
						designRelease.setEngrRequiredDateLabel(designRelease.getEngrRequiredDate()+" ("+ rqdDateWeek +")");
					} else{
						designRelease.setEngrRequiredDate("");
						designRelease.setEngrRequiredDateLabel("");
					}	
				}else if(GETDesignReleaseConstants.Properties.dsgnrReqDate.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDesignRequiredDate(dateFormatter1.format(dateFormatter.parse(value)));
						String rqdDateWeek = commonOp.getFW(designRelease.getDesignRequiredDate());
						designRelease.setDesignRequiredDateLabel(designRelease.getDesignRequiredDate()+" ("+ rqdDateWeek +")");
					}else{
						designRelease.setDesignRequiredDate("");
						designRelease.setDesignRequiredDateLabel("");
					}
				}else if(GETDesignReleaseConstants.Properties.itemId.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDesignReleaseId(value);
					}
				} else if(GETDesignReleaseConstants.Properties.ecr.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setEngrECR(value.substring(0, 10));
					}
				}  else if(GETDesignReleaseConstants.Properties.ecn.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setDesignECN(value.substring(0, 13));
					}
				} else if(GETDesignReleaseConstants.Properties.technicalData.equalsIgnoreCase(key)){
					if( value != null && value.length()>0 ){
						designRelease.setTechnicalData(value.substring(0, value.indexOf("/")+2));
					}
				}
			}
			
			//Calculate State Outside Loop
			String status = designRelease.getStatus();
			if ( status !=null && status.length() > 0 ){
				if ( status.contains( "ECN") ){
					designRelease.setState(commonOp.getColorCode(designRelease.getDesignRequiredDate()));
				} if ( status.contains( "ECR") ){
					designRelease.setState(commonOp.getColorCode(designRelease.getEngrRequiredDate()));
				} else {
					designRelease.setState(commonOp.getColorCode(designRelease.getEngrRequiredDate()));
				}
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return designRelease;
	}
	
	/*
	 * Method to update design release object to teamcenter's data
	 */
	public String updateDesignRelease(String projectId,List<DesignRelease> designReleaseList,String sessionId)throws Exception{
		GETDao dao = getDaoMap(sessionId);
		String response = PLMConstants.designUpdateSuccess;
		try{
			dao.updateDesignRelease(designReleaseList);
		}catch (ServiceException e) 
		{
			e.printStackTrace();
			throw e;
		}
		return response;
	}
	/**
	 * This method retrieves business user and types for the currently logged in User
	 */
	public void logOut(String sessionId)  {
		GETDao dao = getDaoMap(sessionId);
		dao.logout();
	}
	
	public List<String> getProjectList(String sessionId)throws Exception{
		GETDao dao = getDaoMap(sessionId);
		List<String> projList = null;
		
		String[] entries = new String[] { "Project ID"};
		String[] values = new String[] { "*" };
		try {
			projList = new ArrayList<String>();
			projList = dao.getOrgProjectList(entries, values);
		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return projList;
	} 
	
	//@SuppressWarnings("null")
	public List<String> getMainGroupList(String sessionId, String mainGrp)throws Exception{
		GETDao dao = getDaoMap(sessionId);
		List<String> mainGrpList = null;
		List<String> orgList = null;
		Map<String, List<String>> mapGrpList = null;
		mapGrpList = dao.getLOVValues();
		if(mainGrp != null && mainGrp.length() > 0)
		{
			 Iterator it = mapGrpList.entrySet().iterator();
			 orgList = new ArrayList<String>();
			    while (it.hasNext()) {
			        Map.Entry pair = (Map.Entry)it.next();
			        if(pair.getKey().equals(mainGrp))
			        {
			        	orgList.addAll((Collection<? extends String>) pair.getValue());
			        }
			      }
			    return orgList;
		}
		else
		{
			mainGrpList = new ArrayList<String>();
			for (String key : mapGrpList.keySet()) {
				mainGrpList.add(key);
			}
			return mainGrpList;
		}
	}
	
	public List<String> getResourceList(String sessionId, String orgProject, String role)throws Exception{
		GETDao dao = getDaoMap(sessionId);
		List<String> resourceList = null;
		orgProject = (orgProject.split("-")[0]).trim();
		try {
			resourceList = new ArrayList<String>();			
			resourceList = dao.getOrgProjectResourceList(orgProject, role);
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return resourceList;
	}
	
//	public List<String> getSubGroupList(String sessionId)throws Exception{
//		GETDao dao = getDaoMap(sessionId);
//		List<String> groupList = null;
//		try {
//			groupList = new ArrayList<String>();
//			String response = PLMConstants.getGroupList;
//			groupList = dao.getGroupsList();
//		
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		return groupList;
//	}
//	
//	public List<String> getResourceList(String sessionId, String Group, String role)throws Exception{
//		GETDao dao = getDaoMap(sessionId);
//		List<String> groupList = null;
//		try {
//			groupList = new ArrayList<String>();
//			String response = PLMConstants.getGroupList;
//			groupList = dao.getUserList(Group, role);
//			
//			
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		return groupList;
//	}
	
	public String deleteEdot(String sessionId, String[] edot)throws Exception{
		GETDao dao = getDaoMap(sessionId);
		String response = PLMConstants.deletedEdot;
		dao.deleteSelectedEDOTs(edot);
		return response;
	}

	//@Override
	public HSSFWorkbook exportDashboardNew() throws FileNotFoundException, IOException {
		if(designRelList != null && designRelList.size() > 0)
		{
			return ExportToExcel.buildExcelDocumentNew(designRelList);	
		}
		return null;
	}
	
}
