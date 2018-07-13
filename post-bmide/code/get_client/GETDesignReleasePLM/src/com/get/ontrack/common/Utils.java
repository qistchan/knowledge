package com.get.ontrack.common;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpSession;

import com.get.ontrack.model.DesignRelease;
import com.get.ontrack.model.TaskData;


public class Utils {
	
	private GETDesignReleaseCommonOperations commonOp = new GETDesignReleaseCommonOperations();
	public   void createDesignReleaseList(List<DesignRelease> designReleaseList , String[] checkedTemplates , Map<String,List<TaskData>> getTemplatesMap,String templateName , Date p1Date){
		List<TaskData> tList = new ArrayList<>();
		for(String s : checkedTemplates){
			tList = new ArrayList<>();
			String splitStr = s.substring(0,2);
			tList = getTemplatesMap.get(splitStr);
			for(TaskData tData: tList){
				if(s.equalsIgnoreCase(tData.getActivityId())){
					DesignRelease dRelease = new DesignRelease();
					dRelease.setBomLineItemId(trimToEmpty(tData.getActivityId()));
					dRelease.setBackOff(trimToEmpty(tData.getBackOff()));
					dRelease.setDescription(trimToEmpty(tData.getDescription()));
					dRelease.setEngrDuration(trimToEmpty(tData.getEngrDuration()));
					dRelease.setDesignDuration(trimToEmpty(tData.getDesignDuration()));
					dRelease.setIndexId(trimToEmpty(tData.getActivityId()));
					dRelease.setEngrComponentNo(tData.getEngrComponentNo());
					dRelease.setDesignOrgProject(tData.getDesignOrgProject());
					dRelease.setEngrOrgProject(tData.getEngrOrgProject());
					dRelease.setDesignComponentNo(tData.getDesignComponentNo());
					String sEnggStartDate = commonOp.getStartDate(p1Date,tData.getBackOff(), tData.getEngrDuration());
					String sEnggReqDate = commonOp.getEngrRequiredtDate(p1Date, tData.getBackOff());
					String sDesgReqDate = commonOp.getDesignRequiredtDate(p1Date, tData.getBackOff(), tData.getDesignDuration());
					dRelease.setEngrStartDate(sEnggStartDate);
					dRelease.setEngrRequiredDate(sEnggReqDate);
					dRelease.setDesignRequiredDate(sDesgReqDate);
					if ( sEnggStartDate != null && sEnggStartDate.length() > 0 ){
						dRelease.setEngrStartDateLabel(sEnggStartDate+" ("+commonOp.getFW(sEnggStartDate)+")");
					} else {
						dRelease.setEngrStartDateLabel("");
					}
					if ( sEnggReqDate != null && sEnggReqDate.length() > 0 ){
						dRelease.setEngrRequiredDateLabel(sEnggReqDate+" ("+commonOp.getFW(sEnggReqDate)+")");
					} else {
						dRelease.setEngrRequiredDateLabel("");
					}
					if ( sDesgReqDate != null && sDesgReqDate.length() > 0 ){
						dRelease.setDesignRequiredDateLabel(sDesgReqDate+" ("+commonOp.getFW(sDesgReqDate)+")");
					} else {
						dRelease.setDesignRequiredDateLabel("");
					}

					dRelease.setTemplateName(templateName);
					designReleaseList.add(dRelease);
				}
			}
		}
	}
	
	public   void updateDesignReleaseList(List<DesignRelease> designReleaseList , String[] checkedTemplates , Map<String,List<TaskData>> getTemplatesMap,String templateName , Date p1Date){
		List<TaskData> tList = new ArrayList<>();
		for(DesignRelease dRelease : designReleaseList){
			String bomLineItem = dRelease.getBomLineItemId();
			int a =  Arrays.binarySearch(checkedTemplates, bomLineItem);
			if(a > -1 ){
					tList = new ArrayList<>();
					String splitStr = bomLineItem.substring(0,2);
					tList = getTemplatesMap.get(splitStr);
					for(TaskData tData: tList){
						if(bomLineItem.equalsIgnoreCase(tData.getActivityId())){
							dRelease.setBomLineItemId(trimToEmpty(tData.getActivityId()));
							dRelease.setBackOff(trimToEmpty(tData.getBackOff()));
							dRelease.setDescription(trimToEmpty(tData.getDescription()));
							dRelease.setEngrDuration(trimToEmpty(tData.getEngrDuration()));
							dRelease.setDesignDuration(trimToEmpty(tData.getDesignDuration()));
							dRelease.setIndexId(trimToEmpty(tData.getActivityId()));
							dRelease.setEngrComponentNo(tData.getEngrComponentNo());
							dRelease.setDesignComponentNo(tData.getDesignComponentNo());
							dRelease.setDesignOrgProject(tData.getDesignOrgProject());
							dRelease.setEngrOrgProject(tData.getEngrOrgProject());
							
							dRelease.setEngrResource(tData.getEngrResource());
							dRelease.setDesignResource(tData.getDesignResource());
							String sEnggStartDate = commonOp.getStartDate(p1Date,tData.getBackOff(), tData.getEngrDuration());
							String sEnggReqDate = commonOp.getEngrRequiredtDate(p1Date, tData.getBackOff());
							String sDesgReqDate = commonOp.getDesignRequiredtDate(p1Date, tData.getBackOff(), tData.getDesignDuration());
							dRelease.setEngrStartDate(sEnggStartDate);
							dRelease.setEngrRequiredDate(sEnggReqDate);
							dRelease.setDesignRequiredDate(sDesgReqDate);
							dRelease.setEngrStartDateLabel(sEnggStartDate+" ("+commonOp.getFW(sEnggStartDate)+")");
							dRelease.setEngrRequiredDateLabel(sEnggReqDate+" ("+commonOp.getFW(sEnggReqDate)+")");
							dRelease.setDesignRequiredDateLabel(sEnggReqDate+" ("+commonOp.getFW(sDesgReqDate)+")");
							dRelease.setTemplateName(templateName);
						}
					}
			}
		}
	}
	
	public   void addToDesignReleaseList(List<DesignRelease> designReleaseList , String[] checkedTemplates , Map<String,List<TaskData>> getTemplatesMap,String templateName , Date p1Date){
		List<TaskData> tList = new ArrayList<>();
		for(String s : checkedTemplates){
			tList = new ArrayList<>();
			String splitStr = s.substring(0,2);
			tList = getTemplatesMap.get(splitStr);
			for(TaskData tData: tList){
				if(s.equalsIgnoreCase(tData.getActivityId())){
					DesignRelease dRelease = new DesignRelease();
					dRelease.setBomLineItemId(trimToEmpty(tData.getActivityId()));
					dRelease.setBackOff(trimToEmpty(tData.getBackOff()));
					dRelease.setDescription(trimToEmpty(tData.getDescription()));
					dRelease.setEngrDuration(trimToEmpty(tData.getEngrDuration()));
					dRelease.setDesignDuration(trimToEmpty(tData.getDesignDuration()));
					dRelease.setIndexId(trimToEmpty(tData.getActivityId()));
					dRelease.setEngrComponentNo(tData.getEngrComponentNo());
					dRelease.setDesignOrgProject(tData.getDesignOrgProject());
					dRelease.setEngrOrgProject(tData.getEngrOrgProject());
					dRelease.setDesignComponentNo(tData.getDesignComponentNo());
					String sEnggStartDate = commonOp.getStartDate(p1Date,tData.getBackOff(), tData.getEngrDuration());
					String sEnggReqDate = commonOp.getEngrRequiredtDate(p1Date, tData.getBackOff());
					String sDesgReqDate = commonOp.getDesignRequiredtDate(p1Date, tData.getBackOff(), tData.getDesignDuration());
					dRelease.setEngrStartDate(sEnggStartDate);
					dRelease.setEngrRequiredDate(sEnggReqDate);
					dRelease.setDesignRequiredDate(sDesgReqDate);
					dRelease.setEngrStartDateLabel(sEnggStartDate+" ("+commonOp.getFW(sEnggStartDate)+")");
					dRelease.setEngrRequiredDateLabel(sEnggReqDate+" ("+commonOp.getFW(sEnggReqDate)+")");
					dRelease.setDesignRequiredDateLabel(sEnggReqDate+" ("+commonOp.getFW(sDesgReqDate)+")");
					dRelease.setTemplateName(templateName);
					designReleaseList.add(dRelease);
				}
			}
		}
	}
	
	public   void cloneDesignReleaseObject(DesignRelease source , DesignRelease destination){
			destination.setBackOff(trimToEmpty(source.getBackOff()));
			destination.setDescription(trimToEmpty(source.getDescription()));
			destination.setEngrDuration(trimToEmpty(source.getEngrDuration()));
			destination.setDesignDuration(trimToEmpty(source.getDesignDuration()));
			destination.setIndexId(trimToEmpty(source.getBomLineItemId()));
			destination.setEngrComponentNo(source.getEngrComponentNo());
			destination.setDesignComponentNo(source.getDesignComponentNo());
			destination.setDesignOrgProject(source.getDesignOrgProject());
			destination.setEngrOrgProject(source.getEngrOrgProject());
			destination.setEngrStartDate(source.getEngrStartDate());
			destination.setEngrRequiredDate(source.getEngrRequiredDate());
			destination.setDesignRequiredDate(source.getDesignRequiredDate());
			destination.setEngrStartDateLabel(source.getEngrStartDateLabel());
			destination.setEngrRequiredDateLabel(source.getEngrRequiredDateLabel());
			destination.setDesignRequiredDateLabel(source.getDesignRequiredDateLabel());
			destination.setTemplateName(source.getTemplateName());
	}
	
	public   void deleteFromDesignReleaseList(List<DesignRelease> designReleaseList , String[] checkedTemplates){
		List<DesignRelease> tempList = new ArrayList<DesignRelease>();
		for(String s : checkedTemplates){
			for(DesignRelease tData: designReleaseList){
				if(s.equalsIgnoreCase(tData.getBomLineItemId())){
					tempList.add(tData);
				}
			}
		}
		for(DesignRelease tData: tempList){
			designReleaseList.remove(tData);
		}
	}
	
	public  boolean existInDesignReleaseList(List<DesignRelease> designReleaseList , String[] checkedTemplates){
		for(String s : checkedTemplates){
			for(DesignRelease tData: designReleaseList){
				if(s.equalsIgnoreCase(tData.getBomLineItemId())){
					return true;
				}
			}
		}
		return false;
	}
	
	public   void updateTemplatesMap(Map<String,List<TaskData>> getTemplatesMap , List<String> tempDesignReleaseStrList , List<String> tempDesignReleaseScopeList){
		for(Map.Entry<String,List<TaskData>> entry : getTemplatesMap.entrySet()){
			List<TaskData> tDataList = entry.getValue();
			for(TaskData tData : tDataList){
				if(tempDesignReleaseStrList.contains(tData.getActivityId())){
					tData.setExist(true);
				}else{
					tData.setExist(false);
				}
				if(tempDesignReleaseScopeList.contains(tData.getActivityId())){
					tData.setChecked(true);
				}else{
					tData.setChecked(false);
				}
			}
		}
	}
	
	private   String trimToEmpty(String str){
		if(null != str){
			return str;
		}else{
			return "";
		}
	}
	
//	private String validateEDOT() throws Exception 
//	{
//		
//		
//		
//		return null;
//		
//	}
	
	public  void removeAttributesInSession(HttpSession httpSession){
		httpSession.removeAttribute(PLMConstants.Objects.templatesMap);
		httpSession.removeAttribute(PLMConstants.Objects.templatesName);
		httpSession.removeAttribute(PLMConstants.Objects.projectsDataMap);
		httpSession.removeAttribute(PLMConstants.Objects.templatesFiles);
		httpSession.removeAttribute(PLMConstants.Objects.tempDesignReleaseList);
	}
}

