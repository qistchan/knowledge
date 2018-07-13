package com.get.ontrack.service;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;
import java.util.Map;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;

import com.get.ontrack.model.DesignRelease;
import com.get.ontrack.model.EdotLinkedData;
import com.get.ontrack.model.GETUser;
import com.get.ontrack.model.LinkECRData;
import com.get.ontrack.model.TaskData;

public interface GETService {
	public  List<Object> login(GETUser tcUser, String serverURL) throws Exception; 
	public  List<Object> ssoLogin(String serverURL, GETUser getUser, String ssoAppId, String ssoURL) throws Exception;
	public List<Object> getGETProject(GETUser tcUser) throws Exception;
	public void logOut(String sessionId);
	public List<String> getProjects(String sessionId) throws Exception;
	public Map<String,List<String>> getProjectData(String sessionId,String projectId) throws Exception;
	public Map<String,List<TaskData>> getTemplateScope(String sessionId,String template,String scope) throws Exception;
	public Map<String,Map<String,List<TaskData>>> getTemplateScopeFiles(String sessionId,String template,String scope) throws Exception;
	public String saveDesignRelease(String projectId,List<DesignRelease> designReleaseList,String sessionId)throws Exception;
	public String updateDesignRelease(String projectId,List<DesignRelease> designReleaseList,String sessionId)throws Exception;
	public List<DesignRelease> getAssociatedDesignItems(String sessionId,String projectId,List<String> p1DateList,GETUser getuser) throws Exception;
	public List<String> getProjectList(String sessionId)throws Exception;
	public List<String> getResourceList(String sessionId, String Group, String role)throws Exception;
	public String deleteEdot(String sessionId, String[] edot)throws Exception;
	public HSSFWorkbook exportDashboardNew()throws FileNotFoundException, IOException;
	public List<LinkECRData> getEdotData(String sessionId) throws Exception;
	public List<EdotLinkedData> getLinkedECNAndTD(String edot) throws Exception;
	public List<String> getMainGroupList(String id, String mainGrp) throws Exception;
	public List<Object> ssoLoginWithSessionKey(String serverURL, String appUserID, String ssoSessionKey, GETUser getUser, String ssoAppId, String ssoURL) throws Exception;

	
}
