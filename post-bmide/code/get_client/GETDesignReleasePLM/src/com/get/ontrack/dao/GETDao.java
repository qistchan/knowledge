package com.get.ontrack.dao;


import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.UUID;

import org.apache.log4j.Logger;

import com.get.ontrack.common.GETConstants;
import com.get.ontrack.common.GETDesignReleaseConstants;
//import org.apache.log4j.Logger;
import com.get.ontrack.common.GETDesignReleaseWorkflow;
import com.get.ontrack.common.GETOnTrackCommonSoaOperations;
import com.get.ontrack.common.GETOnTrackConstants;
import com.get.ontrack.common.PLMConstants;
import com.get.ontrack.getrans.GETCommon;
import com.get.ontrack.getrans.GETDataManagement;
import com.get.ontrack.getrans.GETFileManagement;
import com.get.ontrack.getrans.GETQuery;
import com.get.ontrack.getrans.clientx.GETSession;
import com.get.ontrack.logger.GELogger;
import com.get.ontrack.model.DesignRelease;
import com.get.ontrack.model.GETUser;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.services.strong.core.ProjectLevelSecurityService;
import com.teamcenter.services.strong.core.SessionService;
import com.teamcenter.services.strong.core._2006_03.DataManagement.Relationship;
import com.teamcenter.services.strong.core._2006_03.Session.GetSessionGroupMemberResponse;
import com.teamcenter.services.strong.core._2007_01.DataManagement.GetItemFromIdPref;
import com.teamcenter.services.strong.core._2007_01.DataManagement.RelationFilter;
import com.teamcenter.services.strong.core._2007_01.DataManagement.VecStruct;
import com.teamcenter.services.strong.core._2007_06.DataManagement.RelationAndTypesFilter;
//import com.teamcenter.services.strong.core._2007_06.LOV;
//import com.teamcenter.services.strong.core._2007_06.LOV.AttachedLOVsResponse;
//import com.teamcenter.services.strong.core._2007_06.LOV.LOVInfo;
//import com.teamcenter.services.strong.core._2007_06.LOV.LOVOutput;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsData2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsOutput2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsPref2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsResponse2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationship;
import com.teamcenter.services.strong.core._2007_09.ProjectLevelSecurity.AssignedOrRemovedObjects;
import com.teamcenter.services.strong.core._2008_06.DataManagement.AddParticipantInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.AddParticipantOutput;
import com.teamcenter.services.strong.core._2008_06.DataManagement.AttrInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.CreateIn;
import com.teamcenter.services.strong.core._2008_06.DataManagement.CreateInput;
import com.teamcenter.services.strong.core._2008_06.DataManagement.CreateOrUpdateRelationsInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.CreateOrUpdateRelationsResponse;
import com.teamcenter.services.strong.core._2008_06.DataManagement.CreateOut;
import com.teamcenter.services.strong.core._2008_06.DataManagement.CreateResponse;
import com.teamcenter.services.strong.core._2008_06.DataManagement.DatasetInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.GetItemAndRelatedObjectsInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.GetItemAndRelatedObjectsResponse;
import com.teamcenter.services.strong.core._2008_06.DataManagement.ItemInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.ParticipantInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.Participants;
import com.teamcenter.services.strong.core._2008_06.DataManagement.RevInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.SecondaryData;
import com.teamcenter.services.strong.core._2009_10.DataManagement.GetItemFromAttributeInfo;
import com.teamcenter.services.strong.core._2009_10.DataManagement.GetItemFromAttributeResponse;
import com.teamcenter.services.strong.core._2012_02.DataManagement.BulkCreIn;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ProjectClientId;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ProjectTeamData;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ProjectTeamsResponse;
import com.teamcenter.services.strong.core._2015_10.DataManagement.ReassignParticipantInfo;
import com.teamcenter.services.strong.core._2015_10.DataManagement.ReassignParticipantResponse;
import com.teamcenter.services.strong.query.SavedQueryService;
import com.teamcenter.services.strong.query._2007_09.SavedQuery.QueryResults;
import com.teamcenter.services.strong.query._2007_09.SavedQuery.SavedQueriesResponse;
import com.teamcenter.services.strong.query._2008_06.SavedQuery.QueryInput;
import com.teamcenter.services.strong.query._2010_04.SavedQuery.FindSavedQueriesCriteriaInput;
import com.teamcenter.services.strong.query._2010_04.SavedQuery.FindSavedQueriesResponse;
import com.teamcenter.services.strong.workflow.WorkflowService;
import com.teamcenter.services.strong.workflow._2008_06.Workflow.ContextData;
import com.teamcenter.services.strong.workflow._2008_06.Workflow.InstanceInfo;
import com.teamcenter.soa.client.FileManagementUtility;
import com.teamcenter.soa.client.GetFileResponse;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.Property;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.Dataset;
import com.teamcenter.soa.client.model.strong.EPMDoTask;
import com.teamcenter.soa.client.model.strong.EPMReviewTask;
import com.teamcenter.soa.client.model.strong.EPMTask;
import com.teamcenter.soa.client.model.strong.Group;
import com.teamcenter.soa.client.model.strong.GroupMember;
import com.teamcenter.soa.client.model.strong.ImanFile;
import com.teamcenter.soa.client.model.strong.ImanQuery;
import com.teamcenter.soa.client.model.strong.ImanRelation;
import com.teamcenter.soa.client.model.strong.Item;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.soa.client.model.strong.ListOfValues;
import com.teamcenter.soa.client.model.strong.ListOfValuesString;
import com.teamcenter.soa.client.model.strong.Participant;
import com.teamcenter.soa.client.model.strong.ReleaseStatus;
import com.teamcenter.soa.client.model.strong.Role;
import com.teamcenter.soa.client.model.strong.TC_Project;
import com.teamcenter.soa.client.model.strong.User;
import com.teamcenter.soa.exceptions.NotLoadedException;

public class GETDao
{
	private  static  GETSession session;
	private String host = PLMConstants.Host;
	private String userName;
	static String itemType = "GET6DsgnRelease";
	static String processTemplate = "GET EDOT Publish-IV";
	final String grpMemberQuery = "__EINT_group_members";
	private DataManagementService dmService;
	
	private String m_userID;
    private String m_password;
    private String m_group;
    private String m_host;
	//private static Logger loger = GELogger.getCurrentLogger();
	private  static Logger logger;// = Logger.getLogger(GETDao.class);

	/*************************************************************************
	 * Method to login to TeamcenterqueryProjectMembres
	 *
	 * @param userID - The String User ID of the Teamcenter User
	 * @param password - The String password of the Teamcenter User
	 * @param groupName - The String groupName of the Teamcenter User
	 ************************************************************************/

	public void login(String userID, String password,GETUser user) throws Exception
	{
		String result = null;
		GELogger.initLogger(GETDao.class);
		logger = GELogger.getCurrentLogger();
		try{
			session = new GETSession(m_host);
			result = session.login(userID, password, null);
			if(result.equals("Success")){
				dmService = DataManagementService.getService(session.getConnection());
				setObjectPolicy();
				this.getSessionGroupAndRole(user);
			}
			else
			{
				throw new Exception(result);
			}
		}catch(Exception e){

			throw new Exception(e.getMessage());
		}
	}
	
	
	public void ssoLogin(GETUser user,String ssoAppId, String ssoURL) throws Exception
	{
		String result = GETOnTrackConstants.Messages.emptyString;
		GELogger.initLogger(GETDao.class);
		logger = GELogger.getCurrentLogger();
		try{
			session = new GETSession( m_host, ssoURL , ssoAppId);
			if(session != null)
			{
				result = session.loginSSO();
				if(result.equals(GETOnTrackConstants.Messages.emptyString)){
					dmService = DataManagementService.getService(session.getConnection());
					setObjectPolicy();
					this.getSessionGroupAndRole(user); 
				}
				else
				{
					throw new Exception(result);
				}
			}
			else
			{
				throw new Exception("Not able to create sso session.");
			}
		}catch(Exception e){
			
			throw new Exception(e.getMessage());
		}
	}
	
	
	  /**
     * Method to login to Teamcenter
     *
     * @return - strErrorMessage - Error message String
     */
    public void ssoLoginWithSessionKey(String ssoAppUserId, String ssoSessionKey,GETUser user,String ssoAppId, String ssoURL) throws Exception
    {
    	String result = GETOnTrackConstants.Messages.emptyString;
		GELogger.initLogger(GETDao.class);
		logger = GELogger.getCurrentLogger();
		try{
			session = new GETSession( m_host, ssoURL, ssoAppId);
			if(session != null)
			{
				result = session.loginSSOWithKey(ssoAppUserId,ssoSessionKey);
				if(result.equals(GETOnTrackConstants.Messages.emptyString)){
					dmService = DataManagementService.getService(session.getConnection());
					setObjectPolicy();
					this.getSessionGroupAndRole(user); 
				}
				else
				{
					throw new Exception(result);
				}
			}
			else
			{
				throw new Exception("Not able to create sso session.");
			}
		}catch(Exception e){
			
			throw new Exception(e.getMessage());
		}
    }


	public void login_test(String userID, String password) throws Exception
	{
		String result = null;
		GELogger.initLogger(GETDao.class);
		logger = GELogger.getCurrentLogger();
		try{
			session = new GETSession(m_host);
			//result = session.loginSSO("123654");
			result = session.login(userID, password, null);
			if(result.equals("Success")){

				//	dmService = DataManagementService.getService(session.getConnection());
				setObjectPolicy();

				//this.getSessionGroupAndRole(user);
				//getProjectGroupData();
				
				//getLOVValues();
				getMainGroupList("Engine");
				
				
				
				//assignEDOTstoECR(new String[]{"EDOT-000028"},"ECR-200001");
			//getTemplateScopeMap (PLMConstants.item, PLMConstants.designReleaseTemplate );
			}
			else
			{
				throw new Exception(result);
			}


		}catch(Exception e){

			throw new Exception(e.getMessage());
		}

	}
	
	
	
    /**
     * Method to set User Id for Teamcenter session 
     * 
     * @param m_userID the m_userID to set
     */
    public void setUserID(String userID)
    {
        m_userID = userID;
    }

    /**
     * Method to set password for Teamcenter session
     * 
     * @param m_password the m_password to set
     */
    public void setPassword(String password)
    {
        m_password = password;
    }

    /**
     * Method to set group for Teamcenter session
     * 
     * @param m_group the m_group to set
     */
    public void setGroup(String group)
    {
        m_group = group;
    }

    /**
     * Method to set Teamcenter host
     * 
     * @param m_host the m_host to set
     */
    public void setHost(String host)
    {
        m_host = host;
    }

    /**
     * Method to get user name of logged in user
     * 
     * @return String - User name of the logged in user
     */
    public String getUserName()
    {
        return session.getCurrentUserName();
    }

    /**
     * Method to get role of logged in user
     * 
     * @return String - Role of the logged in user
     */
    public String getRole()
    {
        return session.getCurrentRole();
    }

    /**
     * Method to get Group of logged in user
     * 
     * @return String - Group of the logged in user
     */
    public String getGroup()
    {
        return session.getCurrentGroup();
    }

    /**
     * Method to get Teamcenter Site Id
     *
     * @return String - Site ID of Teamcenter session
     */
    public String getSiteID()
    {
        return session.getSiteID();
    }


	/********************************************************************
	 * Method to set load the property of TC objects on start of Session
	 *
	 *********************************************************************/
	private void setObjectPolicy()
	{
		try {
			GETCommon commonObj = GETCommon.getInstance(session.getConnection());

			Map<String, String[]> typePropsMap = new HashMap<String, String[]>();

			typePropsMap.put(GETConstants.BusinessObjects.wsObject, new String[]{
					GETConstants.BusinessObjects.Properties.strObjectName,
					GETConstants.BusinessObjects.Properties.objectString});

			typePropsMap.put(GETConstants.BusinessObjects.item, new String[]{
					GETConstants.BusinessObjects.Properties.strItemID, 
					GETConstants.BusinessObjects.Properties.relList, 
					GETConstants.BusinessObjects.Properties.strRevisionList, 
					GETConstants.BusinessObjects.Properties.strObjectType,
					GETConstants.BusinessObjects.Properties.projectList,
					GETConstants.BusinessObjects.Properties.objectString});

			typePropsMap.put(  GETConstants.BusinessObjects.itemRevision, 
					new String[]{GETConstants.BusinessObjects.Properties.uid, 
							GETConstants.BusinessObjects.Properties.strItemRevID,
							GETConstants.BusinessObjects.Properties.itemsTag, 
							GETConstants.BusinessObjects.Properties.relList, 
							GETConstants.BusinessObjects.Properties.processStageList,
							GETConstants.BusinessObjects.Properties.strItemID,
							GETConstants.BusinessObjects.Properties.currentName,
							GETConstants.BusinessObjects.Properties.strCurrentID,
							GETDesignReleaseConstants.Properties.ActivityId,
							GETDesignReleaseConstants.Properties.ActivityDesc,
							GETDesignReleaseConstants.Properties.enggBackOff,
							GETDesignReleaseConstants.Properties.engrDuration,
							GETDesignReleaseConstants.Properties.desgnDuration,
							GETDesignReleaseConstants.Properties.engrOrgProject,
							GETDesignReleaseConstants.Properties.designOrgProject,
							GETDesignReleaseConstants.Properties.templateName,
							GETDesignReleaseConstants.Properties.engrStartDate,
							GETDesignReleaseConstants.Properties.engrReqDate,
							GETDesignReleaseConstants.Properties.dsgnrReqDate,
							GETDesignReleaseConstants.Properties.enggComments,
							GETDesignReleaseConstants.Properties.enggDateChangeReason,
							GETDesignReleaseConstants.Properties.designComments,
							GETDesignReleaseConstants.Properties.designDateChangeReason,
							GETDesignReleaseConstants.Properties.engrPromiseDate,
							GETDesignReleaseConstants.Properties.desPromiseDate,
							GETDesignReleaseConstants.Properties.autoclose,
							GETDesignReleaseConstants.Properties.ecr,
							GETDesignReleaseConstants.Properties.ecn,
							GETDesignReleaseConstants.Properties.technicalData,
							GETDesignReleaseConstants.Relation.cmImplementedBy,
							GETConstants.BusinessObjects.Properties.projectList,
							GETDesignReleaseConstants.Properties.closure,
							GETDesignReleaseConstants.Properties.disposition,
							GETConstants.BusinessObjects.Properties.strOwningProject,
							GETDesignReleaseConstants.Relation.hasParticipant,
							GETDesignReleaseConstants.Relation.cmImplementedBy,
							GETDesignReleaseConstants.Relation.cmImplements,
							GETDesignReleaseConstants.Relation.desgnReleaseTechDataRel

			});

			typePropsMap.put(GETConstants.BusinessObjects.listOfValues, new String[]{
					GETConstants.BusinessObjects.Properties.lovVal,
					GETConstants.BusinessObjects.Properties.lovFilter,
					GETConstants.BusinessObjects.Properties.lovValDesc});
			
			typePropsMap.put(GETConstants.BusinessObjects.tcProject, new String[]{
					GETConstants.BusinessObjects.Properties.objectString, 	
					GETConstants.BusinessObjects.Properties.tcProjectId, "project_data", "project_team", "awp0ProjectTeamMembers"});


			typePropsMap.put(GETConstants.BusinessObjects.groupMember, new String[]{
					GETConstants.BusinessObjects.Properties.group, 
					GETConstants.BusinessObjects.Properties.role,	
					GETConstants.BusinessObjects.Properties.user,
					GETConstants.BusinessObjects.Properties.theGroup, 
					GETConstants.BusinessObjects.Properties.theUser,	
					GETConstants.BusinessObjects.Properties.theRole
					});


			typePropsMap.put(GETConstants.BusinessObjects.group, new String[]{
					GETConstants.BusinessObjects.Properties.strName, 	
					GETConstants.BusinessObjects.Properties.fullName });

			typePropsMap.put(GETConstants.BusinessObjects.role, new String[]{
					GETConstants.BusinessObjects.Properties.strObjectName,
					GETConstants.BusinessObjects.Properties.roleName});

			typePropsMap.put(GETConstants.BusinessObjects.user, new String[]{
					GETConstants.BusinessObjects.Properties.newstuff_folder, 
					GETConstants.BusinessObjects.Properties.userid, 
					GETConstants.BusinessObjects.Properties.userName, 
					GETConstants.BusinessObjects.Properties.objectString});

			typePropsMap.put(GETDesignReleaseConstants.BuinessObjects.GETProject, new String[]{
					GETConstants.BusinessObjects.Properties.strItemID,
					GETConstants.BusinessObjects.Properties.strObjectName,
					GETDesignReleaseConstants.Properties.K1Date,
					GETDesignReleaseConstants.Properties.P1Date,
					GETDesignReleaseConstants.Properties.orderNumber,
					GETDesignReleaseConstants.Properties.customerName,
					GETDesignReleaseConstants.Properties.pmryProjNum,
					GETDesignReleaseConstants.Properties.salesForceID,
					GETDesignReleaseConstants.Properties.secProjNum,
					GETDesignReleaseConstants.Properties.engrProductLine,
					GETDesignReleaseConstants.Relation.desgnReleasePlanRelation
			});


			typePropsMap.put(GETDesignReleaseConstants.BuinessObjects.GETDsgnReleaseRevision, new String[]{GETConstants.BusinessObjects.Properties.uid,
					GETConstants.BusinessObjects.Properties.itemsTag, 
					GETConstants.BusinessObjects.Properties.strItemRevID,
					GETConstants.BusinessObjects.Properties.relList, 
					GETConstants.BusinessObjects.Properties.processStageList,
					GETDesignReleaseConstants.Properties.ActivityId,
					GETDesignReleaseConstants.Properties.ActivityDesc,
					GETDesignReleaseConstants.Properties.enggBackOff,
					GETDesignReleaseConstants.Properties.engrDuration,
					GETDesignReleaseConstants.Properties.desgnDuration,
					GETDesignReleaseConstants.Properties.templateName,
					GETDesignReleaseConstants.Properties.engrStartDate,
					GETDesignReleaseConstants.Properties.engrReqDate,
					GETDesignReleaseConstants.Properties.dsgnrReqDate,
					GETConstants.BusinessObjects.Properties.strItemID,
					GETDesignReleaseConstants.Properties.enggComments,
					GETDesignReleaseConstants.Properties.enggDateChangeReason,
					GETDesignReleaseConstants.Properties.designComments,
					GETDesignReleaseConstants.Properties.designDateChangeReason,
					GETDesignReleaseConstants.Properties.engrPromiseDate,
					GETDesignReleaseConstants.Properties.desPromiseDate,
					GETDesignReleaseConstants.Properties.autoclose,
					GETDesignReleaseConstants.Properties.ecr,
					GETDesignReleaseConstants.Properties.ecn,
					GETDesignReleaseConstants.Properties.technicalData,
					GETConstants.BusinessObjects.Properties.projectList,
					GETDesignReleaseConstants.Properties.closure,
					GETDesignReleaseConstants.Properties.disposition,
					GETConstants.BusinessObjects.Properties.strOwningProject,
					GETDesignReleaseConstants.Relation.hasParticipant,
					GETDesignReleaseConstants.Relation.cmImplementedBy,
					GETDesignReleaseConstants.Relation.cmImplements,
					GETDesignReleaseConstants.Relation.desgnReleaseTechDataRel
			});

			typePropsMap.put(GETConstants.BusinessObjects.participant, new String[]{GETConstants.BusinessObjects.Properties.uid,
					GETConstants.BusinessObjects.Properties.assignee, 
					GETConstants.BusinessObjects.Properties.assigneeGroupRole
			});

			typePropsMap.put(GETConstants.BusinessObjects.epmPerformTask, new String[]{GETConstants.BusinessObjects.Properties.taskState, GETConstants.BusinessObjects.Properties.userAllSignoff});
			typePropsMap.put(GETConstants.BusinessObjects.epmTask, new String[]{GETConstants.BusinessObjects.Properties.taskName, GETConstants.BusinessObjects.Properties.currentName,GETConstants.BusinessObjects.Properties.objectString, GETConstants.BusinessObjects.Properties.strObjectName});
			typePropsMap.put(GETConstants.BusinessObjects.epmDoTask, new String[]{GETConstants.BusinessObjects.Properties.taskName,
					GETConstants.BusinessObjects.Properties.taskType,
					GETConstants.BusinessObjects.Properties.taskTemplate,
					GETConstants.BusinessObjects.Properties.successors,
					GETConstants.BusinessObjects.Properties.AliasTaskName,
					GETConstants.BusinessObjects.Properties.currentName,
					GETConstants.BusinessObjects.Properties.objectString,
					GETConstants.BusinessObjects.Properties.strObjectName}); 
			
			typePropsMap.put(GETConstants.BusinessObjects.epmReviewTask, new String[]{GETConstants.BusinessObjects.Properties.taskName, GETConstants.BusinessObjects.Properties.currentName,GETConstants.BusinessObjects.Properties.objectString, GETConstants.BusinessObjects.Properties.strObjectName});
			typePropsMap.put(GETConstants.BusinessObjects.releaseStatus, new String[]{GETConstants.BusinessObjects.Properties.strName, GETConstants.BusinessObjects.Properties.strObjectName, GETConstants.BusinessObjects.Properties.objectString, GETConstants.BusinessObjects.Properties.strDateReleased});
			typePropsMap.put(GETConstants.BusinessObjects.strImanFile, new String[]{GETConstants.BusinessObjects.Properties.strOriginalFileName});
			typePropsMap.put(GETConstants.BusinessObjects.strDataset, new String[]{GETConstants.BusinessObjects.Properties.strRefListName, GETConstants.BusinessObjects.Properties.currentName, GETConstants.BusinessObjects.Properties.objectString});

			commonObj.setObjectPolicy(typePropsMap);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}



	/***********************************************************
	 * Description: Method to get the list of all projects
	 * @return ItemIds
	 ***********************************************************/
	public List<String> listGetProjects( String typeName, String[] propName, String propValue ) throws Exception
	{
		List<String> projectIdList = new ArrayList<String>();
		ImanQuery query = findQuery( GETConstants.Query.strItemQuery );
		if ( query != null ){

			QueryInput qryInput = new QueryInput();

			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = new String[] {GETConstants.Query.strItemIDName,GETConstants.Query.strTypeName};
			qryInput.values = new String[] {"*", GETDesignReleaseConstants.BuinessObjects.GETProject};

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				String[] objUids = results[0].objectUIDS;
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof Item ){
							String projectId = ((Item) mObj).get_item_id();
							if ( !projectIdList.contains(projectId) ) {
								projectIdList.add(projectId);
							}
						}
					}
				}
			}
		}

		return projectIdList;
	}

	public ArrayList<String> getGETProjectList( ImanQuery query, String[] strQueryEntrys, String[] strQueryValues  ) throws NotLoadedException 
	{

		ArrayList<String> projectList = new ArrayList<String>();
		QueryInput qryInput = new QueryInput();

		qryInput.clientId = UUID.randomUUID().toString();
		qryInput.limitList = new ModelObject[0];
		qryInput.maxNumToReturn = 0;
		qryInput.query = query;
		qryInput.resultsType = 0;
		qryInput.entries = strQueryEntrys;
		qryInput.values = strQueryValues;

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

		SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

		QueryResults[] results =  qryResp.arrayOfResults;
		if ( results.length > 0 ){
			ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
					ModelObject mObj = sData.getPlainObject(jnx);
					if ( mObj instanceof Item ){
						String projectId = ((Item) mObj).get_item_id();
						if ( !projectList.contains(projectId) ) {
							projectList.add(projectId);
						}
					}
				}
			}
		}
		return projectList;
	}
	
	
	public String getParticipantUser( ImanQuery query, String[] strQueryEntrys, String[] strQueryValues  ) throws NotLoadedException 
	{

		String resource = null;
		QueryInput qryInput = new QueryInput();

		qryInput.clientId = UUID.randomUUID().toString();
		qryInput.limitList = new ModelObject[0];
		qryInput.maxNumToReturn = 0;
		qryInput.query = query;
		qryInput.resultsType = 0;
		qryInput.entries = strQueryEntrys;
		qryInput.values = strQueryValues;

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

		SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

		QueryResults[] results =  qryResp.arrayOfResults;
		if ( results.length > 0 ){
			ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
					ModelObject mObj = sData.getPlainObject(jnx);
					if ( mObj instanceof Participant ){
						Participant participant = (Participant) mObj;
						if ( participant!=null ){
							GroupMember member = (GroupMember) participant.get_assignee();
							resource =  member.get_user().get_object_string();
						}
					}
				}
			}
		}
		return resource;
	}
	
	public Participant getParticipant( ImanQuery query, String[] strQueryEntrys, String[] strQueryValues  ) throws NotLoadedException 
	{

		Participant participant = null;
		QueryInput qryInput = new QueryInput();

		qryInput.clientId = UUID.randomUUID().toString();
		qryInput.limitList = new ModelObject[0];
		qryInput.maxNumToReturn = 0;
		qryInput.query = query;
		qryInput.resultsType = 0;
		qryInput.entries = strQueryEntrys;
		qryInput.values = strQueryValues;

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

		SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

		QueryResults[] results =  qryResp.arrayOfResults;
		if ( results.length > 0 ){
			ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				ModelObject mObj = sData.getPlainObject(0);
				if ( mObj instanceof Participant ){
					participant = (Participant) mObj;
				}
			}
		}
		return participant;
	}
	
	public ListOfValuesString getgroupProjectLov( ImanQuery query, String[] strQueryEntrys, String[] strQueryValues  ) throws Exception 
	{

		ListOfValuesString groupProjectLov = null;
		QueryInput qryInput = new QueryInput();

		qryInput.clientId = UUID.randomUUID().toString();
		qryInput.limitList = new ModelObject[0];
		qryInput.maxNumToReturn = 0;
		qryInput.query = query;
		qryInput.resultsType = 0;
		qryInput.entries = strQueryEntrys;
		qryInput.values = strQueryValues;

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

		SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

		QueryResults[] results =  qryResp.arrayOfResults;
		if ( results.length > 0 ){
			ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				if(sData.sizeOfPlainObjects() > 0){
				
				ModelObject mObj = sData.getPlainObject(0);
				if ( mObj instanceof ListOfValuesString ){
					groupProjectLov = (ListOfValuesString) mObj;
				}
			}
				/*else
				{
					throw new Exception("Project Data not found.");
				}*/
			}
		}
		return groupProjectLov;
	}


	/***********************************************************
	 * Description:Method to get the GET Project data from Teamcenter
	 * @return ItemIds
	 ***********************************************************/
	public Map<ModelObject,Map<String,List<String>>> getProjectsData( String typeName, String[] propName, String propValue ) throws Exception
	{
		Map<ModelObject,Map<String,List<String>>> moObjects = new HashMap<ModelObject,Map<String,List<String>>>() ;
		Map<String,List<String>> itemIds = new HashMap<String,List<String>>();
		ModelObject[] moObject = null;
		GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
		GETQuery.QueriedObjects queriedObjects = queryService1.getQueriedObjs(GETConstants.Query.strGeneralQueryName, new String[] {GETConstants.Query.strTypeName, GETConstants.Query.strName},
				new String[] {typeName, propValue});
		if ( queriedObjects != null )
		{
			moObject = queriedObjects.loadedObjects;
		}
		if(moObject != null && moObject.length > 0)
		{
			GETDataManagement dataMgmt = GETDataManagement.getDMService(session.getConnection());
			dataMgmt.getProperties(moObject, propName);
			for(ModelObject ma : moObject)
			{
				try 
				{	
					for (int iCount = 0 ; iCount < propName.length ; iCount++)
					{		
						itemIds.put ( propName[iCount], dataMgmt.getPropertryValues(ma, propName[iCount], false) );
					}
				} 
				catch (Exception ex) 
				{
					ex.printStackTrace();
				}
				moObjects.put(ma, itemIds);
			}
		}
		return moObjects;
	}

	/***************************************************************
	 * Method to get GET Project properties
	 * @param getProject - Model of GET Project
	 * @return - Map of property name and  List of property values38
	 ***************************************************************/
	public Map<String,List<String>> getProjectProperties( ModelObject getProject )  throws Exception
	{
		Map<String, List<String>> propMap = null;
//		DataManagementService dmService = DataManagementService.getService(session.getConnection());
		try {
//			dmService.unloadObjects(new ModelObject[]{getProject});
//
//			String objUIDs = getProject.getUid();
//			dmService.loadObjects(new String[]{objUIDs});
//
//			GETDataManagement dataMgmt = GETDataManagement.getDMService(session.getConnection());
			propMap = new HashMap<String,List<String>>();

			propMap.put ( GETConstants.BusinessObjects.Properties.strObjectName, getPropertryValues ( getProject, GETConstants.BusinessObjects.Properties.strObjectName ) );
			propMap.put ( GETDesignReleaseConstants.Properties.K1Date, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.K1Date ) );
			propMap.put ( GETDesignReleaseConstants.Properties.P1Date, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.P1Date ) );
			propMap.put ( GETDesignReleaseConstants.Properties.orderNumber, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.orderNumber ) );
			propMap.put ( GETDesignReleaseConstants.Properties.customerName, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.customerName ) );
			propMap.put ( GETDesignReleaseConstants.Properties.pmryProjNum, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.pmryProjNum ) );
			propMap.put ( GETDesignReleaseConstants.Properties.salesForceID, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.salesForceID));
			propMap.put ( GETDesignReleaseConstants.Properties.secProjNum, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.secProjNum ) );
			propMap.put ( GETDesignReleaseConstants.Properties.engrProductLine, getPropertryValues ( getProject, GETDesignReleaseConstants.Properties.engrProductLine ) );
			propMap.put ( GETDesignReleaseConstants.Relation.desgnReleasePlanRelation, getPropertryValues ( getProject, GETDesignReleaseConstants.Relation.desgnReleasePlanRelation ) );

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return propMap;
	}


	/******************************************************************
	 * *Method to convert ItemID (String) to Model Object  
	 * 
	 * @param propValue - Item ID
	 * @return - ModelObject of the corresponding Item
	 * @throws Exception
	 *******************************************************************/
	public ModelObject itemToModelObjects(String propValue) throws Exception
	{
		ModelObject[] moObjects = null;
		ModelObject moObject = null;
		GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
		GETQuery.QueriedObjects queriedObjects = queryService1.getQueriedObjs(GETConstants.Query.strItemIDName, new String[] {GETConstants.Query.strItemIDName},
				new String[] {propValue});
		if ( queriedObjects != null )
		{
			moObjects = queriedObjects.loadedObjects;
		}
		if(moObjects != null && moObjects.length > 0)
		{
			moObject = moObjects[0];
		}
		return moObject;
	}


	/*****************************************************************
	 * Method to get Iman File from the Item
	 * @param typeName
	 * @param itemId
	 * @return Iman file from the dataset
	 ******************************************************************/
	public Map<String,File> getImanFile ( String typeName, String itemId ) throws Exception
	{
		ModelObject[] moObject = null;
		Map<String,File> mFileName = new HashMap<String,File>();
		File file = null;
		Map<ModelObject, Map<ModelObject, Dataset[]>> dataset = new HashMap<ModelObject, Map<ModelObject, Dataset[]>>();
		GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
		GETQuery.QueriedObjects queriedObjects;
		try
		{
			queriedObjects = queryService1.getQueriedObjs(GETConstants.Query.strGeneralQueryName, new String[] {GETConstants.Query.strTypeName, GETConstants.Query.strName},
					new String[] {typeName, itemId});
			if ( queriedObjects != null )
			{
				moObject = queriedObjects.loadedObjects;
			}
			GETDataManagement dataMgmt = GETDataManagement.getDMService(session.getConnection());
			for(ModelObject ma : moObject)
			{
				dataMgmt.getPropertryValues(ma, GETConstants.BusinessObjects.Properties.strObjectType, false);
			}
			dataset = getLatestRevsAndDatasets(moObject,null);
			Iterator<ModelObject> itr  = dataset.keySet().iterator();
			while (itr.hasNext())
			{
				ModelObject key = itr.next();
				Map<ModelObject, Dataset[]> revDataset = dataset.get(key);
				Iterator<ModelObject> moItr = revDataset.keySet().iterator();
				while( moItr.hasNext())
				{
					Dataset[] datasets = revDataset.get(moItr.next());
					for(Dataset datasettemp: datasets)
					{
						List<ImanFile> lImanFile = dataMgmt.getDSNamedRefs(datasettemp);
						for(int iImCount = 0; iImCount < lImanFile.size(); iImCount++)
						{
							dataMgmt.getPropertryValues((ModelObject)lImanFile.get(iImCount),GETConstants.BusinessObjects.Properties.strOriginalFileName, false);
							GETFileManagement fmsService = GETFileManagement.getService(session.getConnection());
							Iterator<ImanFile> iterator = lImanFile.iterator();
							while (iterator.hasNext())
							{
								file = fmsService.getFileFromIMF(iterator.next());
								mFileName.put(lImanFile.get(iImCount).get_original_file_name(),file);

							}
						}
					}
				}

			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
		return mFileName;
	}
	
	
//	/**
//	 * Gets file from the given imanfile
//	 * 
//	 * @param imf - ImanFile object
//	 * @return File object of the ImanFile
//	 */
//	public File getFileFromIMF(ImanFile imf)
//	{
//		//GETCommon getCommon = new GETCommon(connection);
//		File fileObj = null;
//		try
//		{
//			if(imf != null) 
//			{
//				List<String> bootStrapURLList = GETCommon.getInstance(session.getConnection()).getBootStrapURLs();
//				String bootStrapURL = null;
//				if(bootStrapURLList == null || bootStrapURLList.isEmpty())
//				{
//					throw new Exception("No bootstrap URL found");
//				}
//				bootStrapURL = bootStrapURLList.get(0);
//				FileManagementUtility FileManagementUtilityObj = new FileManagementUtility(session.getConnection(),  null,  new String[] { bootStrapURL }, new String[] { bootStrapURL }, System.getProperty(GETConstants.Symbols.strJavaTempDir));
//				GetFileResponse getFileResponseObj = FileManagementUtilityObj.getFiles(new ModelObject[] { imf });
//				if(getFileResponseObj.sizeOfFiles() > 0)
//				{
//					fileObj = getFileResponseObj.getFile(0);
//				}
//			}
//		}
//		catch(Exception ex)
//		{
//			ex.printStackTrace();
//		}
//
//		return fileObj;
//	}
	
	/*****************************************************************
	 * Method to get Iman File from the Item
	 * @param typeName
	 * @param itemId
	 * @return Iman file from the dataset
	 ******************************************************************/
	public Map<String,File> getImanFile_TRY ( String typeName, String itemId ) throws Exception
	{
		
		Map<String,File> mFileName = new HashMap<String,File>();
		try
		{
			List<String> bootStrapURLList = GETCommon.getInstance(session.getConnection()).getBootStrapURLs();
			String bootStrapURL = null;
			if(bootStrapURLList == null || bootStrapURLList.isEmpty())
			{
				throw new Exception("No bootstrap URL found");
			}
			bootStrapURL = bootStrapURLList.get(0);
			FileManagementUtility fmUtility = new FileManagementUtility(session.getConnection(),  null,  new String[] { bootStrapURL }, new String[] { bootStrapURL }, System.getProperty(GETConstants.Symbols.strJavaTempDir));
			
			List<Dataset> datasetList = getDatasetList(itemId, "0");
			for (Dataset dataset : datasetList) {
				ModelObject[] refFileObjs = dataset.get_ref_list();
					if (refFileObjs[0] instanceof ImanFile) {
						ImanFile tcFile = (ImanFile) refFileObjs[0];
						GetFileResponse fileResp = fmUtility.getFiles( new ModelObject[] { tcFile });
						File[] files = fileResp.getFiles();
						if ( files[0] != null ){
							mFileName.put(tcFile.get_original_file_name(),files[0]);
						}
					}
				
			}
			fmUtility.term();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
		return mFileName;
	}
	
//	/*****************************************************************
//	 * Method to get Iman File from the Item
//	 * @param typeName
//	 * @param itemId
//	 * @return Iman file from the dataset
//	 ******************************************************************/
//	public Map<String,File> getImanFile ( String typeName, String itemId ) throws Exception
//	{
//		
//		Map<String,File> mFileName = new HashMap<String,File>();
//		try
//		{
//			String os = System.getProperty("os.name").toLowerCase();
//			if (os.indexOf("nux") >= 0){
//				
//			}
//			
//			FileManagementUtility fmUtility = new FileManagementUtility(session.getConnection());
//			List<ImanFile> imanFileList = getAllNamedRefList(itemId, "0");
//			for (ImanFile imanFile : imanFileList) {
//				GetFileResponse fileResp = fmUtility.getFiles( new ModelObject[] { imanFile });
//				File[] files = fileResp.getFiles();
//				if ( files[0] != null ){
//					mFileName.put(imanFile.get_original_file_name(),files[0]);
//				}
//			}
//			fmUtility.term();
//		} 
//		catch (Exception e) 
//		{
//			e.printStackTrace();
//		}
//		return mFileName;
//	}
	
	
	
	
//	public List<File> getNamedRefFile( Dataset dataset ) {
//
//		List<File> fileList= new ArrayList<File>();
//
//		try {
//			
//			
//			FileManagementUtility fmUtility = new FileManagementUtility(session.getConnection());
//		
//			ModelObject[] refFileObjs = dataset.get_ref_list();
//			for (int inx = 0; inx < refFileObjs.length; inx++) {
//				if (refFileObjs[inx] instanceof ImanFile) {
//					GetFileResponse fileResp = fmUtility.getFiles( new ModelObject[] { refFileObjs[inx] });
//					File[] files = fileResp.getFiles();
//					for (int jnx = 0; jnx < files.length; jnx++) {
//						if ( files[jnx] != null ){
//							fileList.add(files[jnx]);
//						}
//					}
//
//				}
//			}
//			fmUtility.term();
//		} catch ( Exception e) {
//			e.printStackTrace();
//		}
//		return fileList;
//	}
	
	/*****************************************************************
	 * Method to get the template name and scope in a map
	 * @param typeName
	 * @param itemId
	 * @return Map of Template name and associated list of scopes
	 ******************************************************************/
	public Map<String, ArrayList<String>> getTemplateScopeMap ( String typeName, String itemId ) throws Exception
	{

		List<String> datasetNameList = new ArrayList<String>();
		Map<String, ArrayList<String>> templateScopeMap = new HashMap<String, ArrayList<String>>();

		try
		{

			List<Dataset> datasetList = getDatasetList(itemId, "0");
			
			for (Dataset dataset : datasetList) {
				datasetNameList.add( dataset.get_current_name());
			}
			
			for(int i= 0;i < datasetNameList.size(); i++)
			{
				String sKey = datasetNameList.get(i).substring(0, datasetNameList.get(i).indexOf("-"));
				String sValue = datasetNameList.get(i).substring(datasetNameList.get(i).indexOf("-")+1);

				ArrayList<String> tempList = null;
				if (templateScopeMap.containsKey(sKey)) {
					tempList = templateScopeMap.get(sKey);
					if(tempList == null)
						tempList = new ArrayList<String>();
					tempList.add(sValue);  
				} else {
					tempList = new ArrayList<String>();
					tempList.add(sValue);               
				}

				templateScopeMap.put(sKey, tempList);

			}

		} 
		catch (Exception e) 
		{
			//e.printStackTrace();
			throw e;
		}
		return templateScopeMap;
	}
	


//	/*****************************************************************
//	 * Method to get the template name and scope in a map
//	 * @param typeName
//	 * @param itemId
//	 * @return Map of Template name and associated list of scopes
//	 ******************************************************************/
//	public Map<String, ArrayList<String>> getTemplateScopeMap ( String typeName, String itemId ) throws Exception
//	{
//		ModelObject[] moObject = null;
//		List<String> tempListt = new ArrayList<String>();
//		Map<String, ArrayList<String>> templateScopeMap = new HashMap<String, ArrayList<String>>();
//		Map<ModelObject, Map<ModelObject, Dataset[]>> dataset = new HashMap<ModelObject, Map<ModelObject, Dataset[]>>();
////		GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
////		GETQuery.QueriedObjects queriedObjects;
//		try
//		{
////			queriedObjects = queryService1.getQueriedObjs(GETConstants.Query.strGeneralQueryName, new String[] {GETConstants.Query.strTypeName, GETConstants.Query.strName},
////					new String[] {typeName, itemId});
////			if ( queriedObjects != null )
////			{
////				moObject = queriedObjects.loadedObjects;
////			}
////			GETDataManagement dataMgmt = GETDataManagement.getDMService(session.getConnection());
////			for(ModelObject ma : moObject)
////			{
////				dataMgmt.getPropertryValues(ma, GETConstants.BusinessObjects.Properties.strObjectType, false);
////			}
////			ImanQuery query = findQuery(GETConstants.Query.strItemQuery);
//			
//			Item item = getItem(itemId, typeName);
//			
//			dataset = getLatestRevsAndDatasets(new ModelObject[]{ item } , null);
//			Iterator<ModelObject> itr  = dataset.keySet().iterator();
//			while (itr.hasNext())
//			{
//				ModelObject key = itr.next();
//				Map<ModelObject, Dataset[]> revDataset = dataset.get(key);
//				Iterator<ModelObject> moItr = revDataset.keySet().iterator();
//				while( moItr.hasNext())
//				{
//					Dataset[] datasets = revDataset.get(moItr.next());
//
//					for(int dsCount = 0; dsCount < datasets.length; dsCount++)
//					{
//						tempListt.add( datasets[dsCount].get_current_name());
//
//					}
//
//					for(int i= 0;i < tempListt.size(); i++)
//					{
//						String sKey = tempListt.get(i).substring(0, tempListt.get(i).indexOf("-"));
//						String sValue = tempListt.get(i).substring(tempListt.get(i).indexOf("-")+1);
//
//						ArrayList<String> tempList = null;
//						if (templateScopeMap.containsKey(sKey)) {
//							tempList = templateScopeMap.get(sKey);
//							if(tempList == null)
//								tempList = new ArrayList<String>();
//							tempList.add(sValue);  
//						} else {
//							tempList = new ArrayList<String>();
//							tempList.add(sValue);               
//						}
//
//						templateScopeMap.put(sKey, tempList);
//
//					}
//				}
//
//			}
//
//		} 
//		catch (Exception e) 
//		{
//			//e.printStackTrace();
//			throw e;
//		}
//		return templateScopeMap;
//	}
//	
	
	
	 /**
     * Method to get latest created Revisions and associated Datasets of the Revision with the given Relation
     * 
     * @param itemArr - Array of items whose latest revisions are to be retrieved
     * @param relnMap - Map of Relation Type Name and Array of Type of Objects
     * @return - itemLatestRevDatasetMap - Map of Item and Map of Latest Revision and Array of associated Datasets
     */
    public Map<ModelObject, Map<ModelObject, Dataset[]>> getLatestRevsAndDatasets(ModelObject[] itemArr, Map<String, String[]> relnMap)
    {
        Map<ModelObject, Map<ModelObject, Dataset[]>> itemLatestRevDatasetMap = null;

        try
        {
            /*"item_id", "object_type"*/
            GetItemFromAttributeInfo[] attrInfo = new GetItemFromAttributeInfo[itemArr.length];
            GetItemFromIdPref itemFromIdPref = new GetItemFromIdPref();
            int nRev = 1;
            RelationFilter[] relnFilter = null;
            if(relnMap != null && relnMap.size() > 0)
            {
                relnFilter = new RelationFilter[relnMap.size()];
                int relnMapIndex = 0;
                for(Map.Entry<String, String[]> entry : relnMap.entrySet())
                {
                    relnFilter[relnMapIndex] = new RelationFilter();
                    relnFilter[relnMapIndex].relationTypeName = entry.getKey();
                    relnFilter[relnMapIndex++].objectTypeNames = entry.getValue();
                }
                itemFromIdPref.prefs = relnFilter;
            }

        //   getProperties(itemArr, new String[]{GETConstants.BusinessObjects.Properties.strItemID});
           
           for(int itemIndex = 0; itemIndex < itemArr.length; itemIndex++)
           {
        	   Item item = (Item)itemArr[itemIndex]; 
               attrInfo[itemIndex] = new GetItemFromAttributeInfo();
               Map<String, String> itemAttrMap = new HashMap<String, String>();
               itemAttrMap.put(GETConstants.BusinessObjects.Properties.strItemID, (item.get_item_id()));
               itemAttrMap.put(GETConstants.BusinessObjects.Properties.strObjectType, (item.get_object_type()));
               attrInfo[itemIndex].revIds = new String[]{""};
               attrInfo[itemIndex].itemAttributes = itemAttrMap;
           }

           GetItemFromAttributeResponse attrResponse = dmService.getItemFromAttribute(attrInfo, nRev, itemFromIdPref);
           GETCommon.getErrorFromServiceData(attrResponse.serviceData);
           for(int outIndex = 0; outIndex < attrResponse.output.length; outIndex++)
           {
               Map<ModelObject, Dataset[]> latestRevDatasetMap = new HashMap<ModelObject, Dataset[]>();
               for(int revIndex = 0; revIndex < attrResponse.output[outIndex].itemRevOutput.length; revIndex++)
               {
                   latestRevDatasetMap.put(attrResponse.output[outIndex].itemRevOutput[revIndex].itemRevision, attrResponse.output[outIndex].itemRevOutput[revIndex].datasets);
               }
               if(itemLatestRevDatasetMap == null)
               {
                   itemLatestRevDatasetMap = new HashMap<ModelObject, Map<ModelObject, Dataset[]>>();
               }
               itemLatestRevDatasetMap.put(attrResponse.output[outIndex].item, latestRevDatasetMap);
           }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        return itemLatestRevDatasetMap;
    }

	/******************************************************************
	 * Method to create bulk Design Release items
	 * 
	 * @param dRdatas - List Design Release Items
	 * @return -  Created Design Release Model Object is returned
	 ******************************************************************/
	@SuppressWarnings({ "unchecked", "deprecation" })
	public List<ModelObject> createDesignReleaseItems (List<DesignRelease> dRdatas) throws Exception
	{
		DataManagementService dmService = null;
		List<ModelObject> changeItemRevs = new ArrayList<ModelObject>();

		Map<ModelObject, Map<ModelObject, Dataset[]>> itemRevDatasetMap = new HashMap<ModelObject, Map<ModelObject, Dataset[]>>();
		Map<DesignRelease, Map<String,Date>> datePropValueMap = new HashMap<DesignRelease, Map<String,Date>>();
		Map<DesignRelease, Map<String,Integer>> intPropValueMap = new HashMap<DesignRelease, Map<String,Integer>>();
		//		Map<DesignRelease, Map<String,ModelObject>> moPropValueMap = new HashMap<DesignRelease, Map<String,ModelObject>>();
		Map<DesignRelease, ArrayList<ModelObject>> moTcProjectsMap = new HashMap<DesignRelease, ArrayList<ModelObject>>();
		Map<DesignRelease, Map<String,ModelObject>> moProjectValueMap = new HashMap<DesignRelease, Map<String,ModelObject>>();

		GETDataManagement dataMgmt = GETDataManagement.getDMService ( session.getConnection() );
		BulkCreIn[] bulkcreate = new BulkCreIn[dRdatas.size()];

		try
		{
			for(int iDataCount = 0; iDataCount < dRdatas.size(); iDataCount++)
			{

				DesignRelease data = dRdatas.get(iDataCount);
				Map<String, Integer> intPropNameValue = new HashMap<String, Integer>();
				Map<String, Date> datePropNameValue = new HashMap<String, Date>();
				ArrayList<ModelObject> moProjectsList = new ArrayList<ModelObject>();
				Map<String, ModelObject> moProjNameValue = new HashMap<String, ModelObject>();

				//Projects
				String engrProjId = data.getEngrOrgProject();
				if ( engrProjId != null && engrProjId.length() > 0 ){
					moProjNameValue.put(GETDesignReleaseConstants.Category.strEngr, getOrgProject(engrProjId));
				}

				String designProjId = data.getDesignOrgProject();
				if ( designProjId != null && designProjId.length() > 0 ){
					moProjNameValue.put(GETDesignReleaseConstants.Category.strDesign, getOrgProject(designProjId));
				}
				moProjectValueMap.put( data, moProjNameValue );

				//Integer Properties
				intPropNameValue.put( GETDesignReleaseConstants.Properties.enggBackOff, convertToInt(data.getBackOff()) );
				intPropNameValue.put( GETDesignReleaseConstants.Properties.desgnDuration, convertToInt(data.getDesignDuration()) );
				intPropNameValue.put( GETDesignReleaseConstants.Properties.engrDuration, convertToInt(data.getEngrDuration()) );
				intPropValueMap.put(data,intPropNameValue);

				//Date Properties
				String sEnggStartDate = data.getEngrStartDate();
				String sEnggReqDate = data.getEngrRequiredDate();
				String sDesgReqDate = data.getDesignRequiredDate();

				if (sEnggStartDate != null && sEnggStartDate.length() > 0 ){
					Date dEnggStartDate = new Date(sEnggStartDate);
					datePropNameValue.put( GETDesignReleaseConstants.Properties.engrStartDate, dEnggStartDate );
				} else {
					datePropNameValue.put( GETDesignReleaseConstants.Properties.engrStartDate, null );
				}
				if (sEnggReqDate != null && sEnggReqDate.length() > 0 ){
					Date dEnggReqDate = new Date(sEnggReqDate);
					datePropNameValue.put( GETDesignReleaseConstants.Properties.engrReqDate, dEnggReqDate);
				} else {
					datePropNameValue.put( GETDesignReleaseConstants.Properties.engrReqDate, null);
				}
				if (sDesgReqDate != null && sDesgReqDate.length() > 0 ){
					Date dDesgReqDate = new Date(sDesgReqDate);
					datePropNameValue.put( GETDesignReleaseConstants.Properties.dsgnrReqDate,dDesgReqDate);
				} else {
					datePropNameValue.put( GETDesignReleaseConstants.Properties.dsgnrReqDate,null);
				}
				datePropValueMap.put(data, datePropNameValue);

				//Item Definition
				BulkCreIn itemDef = new BulkCreIn();
				itemDef.data.boName = GETDesignReleaseConstants.BuinessObjects.GETDsgnRelease;
				itemDef.folder = session.getCurrentUser().get_newstuff_folder();
				//Item Definition - Properties
				itemDef.data.stringProps.put(GETConstants.BusinessObjects.Properties.strObjectName, data.getBomLineItemId());
				itemDef.data.stringProps.put(GETConstants.BusinessObjects.Properties.strObjectDesc, data.getDescription());

				//Revision Definition
				CreateInput revisionDef = new CreateInput();
				revisionDef.boName = GETDesignReleaseConstants.BuinessObjects.GETDsgnReleaseRevision;
				revisionDef.stringProps.put(GETConstants.BusinessObjects.Properties.strItemRevID, "0");
				//Revision Definition - Properties
				revisionDef.stringProps.put( GETDesignReleaseConstants.Properties.ActivityId, data.getBomLineItemId() );
				revisionDef.stringProps.put( GETDesignReleaseConstants.Properties.ActivityDesc, data.getDescription() );	
				revisionDef.stringProps.put( GETDesignReleaseConstants.Properties.templateName, data.getTemplateName());
				revisionDef.dateProps.put( GETDesignReleaseConstants.Properties.engrStartDate, null );
				revisionDef.dateProps.put( GETDesignReleaseConstants.Properties.engrReqDate, null  );
				revisionDef.dateProps.put( GETDesignReleaseConstants.Properties.dsgnrReqDate, null );

				itemDef.data.compoundCreateInput.put("revision", new CreateInput[]{  revisionDef });
				itemDef.quantity = 1;
				bulkcreate[iDataCount] = itemDef;
			}

			dmService = DataManagementService.getService(session.getConnection());
			CreateResponse createObjResponse = dmService.bulkCreateObjects(bulkcreate);
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(createObjResponse.serviceData))
			{
				for(CreateOut out : createObjResponse.output)
				{
					for(ModelObject mo : out.objects)
					{
						dataMgmt.getProperties(out.objects, new String[]{ GETConstants.BusinessObjects.Properties.strObjectType, GETConstants.BusinessObjects.Properties.strObjectName});
						if(mo instanceof Item)
						{
							Item item = (Item) mo;
							itemRevDatasetMap = getLatestRevsAndDatasets( out.objects, null );
							Iterator<ModelObject> itemRevDatasetMapItr = itemRevDatasetMap.keySet().iterator();
							while(itemRevDatasetMapItr.hasNext())
							{
								ModelObject moItem = itemRevDatasetMapItr.next();
								Map<ModelObject, Dataset[]> revDatasetMap = itemRevDatasetMap.get(moItem);
								Iterator<ModelObject> revDatasetMapItr = revDatasetMap.keySet().iterator();
								while(revDatasetMapItr.hasNext())
								{
									ModelObject moChangeItemRev = revDatasetMapItr.next();
									changeItemRevs.add(moChangeItemRev);
									Iterator<DesignRelease> propItr = datePropValueMap.keySet().iterator();
									while(propItr.hasNext()) 
									{
										DesignRelease key = propItr.next();
										if(key.getBomLineItemId().equalsIgnoreCase((item).get_object_name()))
										{
											Map<String, Date> datePropValues = datePropValueMap.get(key);
											Iterator<String> datePropNameItr = datePropValues.keySet().iterator();
											while(datePropNameItr.hasNext()) 
											{
												String name = datePropNameItr.next();
												setDateProperties(new ModelObject[] {moChangeItemRev}, name, datePropValues.get(name));
											}

											Map<String, Integer> intPropValues = intPropValueMap.get(key);
											Iterator<String> intPropNameItr = intPropValues.keySet().iterator();
											while(intPropNameItr.hasNext()) 
											{
												String name = intPropNameItr.next();
												setIntProperties(new ModelObject[] {moChangeItemRev}, name, intPropValues.get(name));
											}


											Map<String, ModelObject> strProjValues = moProjectValueMap.get(key);
											Iterator<String> strProjItr = strProjValues.keySet().iterator();
											while(strProjItr.hasNext()) 
											{
												String category = strProjItr.next();
												TC_Project project = (TC_Project) strProjValues.get(category);
												assignToProject(new ModelObject[]{item}, new TC_Project[]{project});
												if(category.equalsIgnoreCase(GETDesignReleaseConstants.Category.strEngr)){
													GroupMember engrManager = getEngrManager(project);
													assignParticipantResource( (ItemRevision)moChangeItemRev, engrManager, GETDesignReleaseConstants.Participants.engrManager);
													//Set to Owning Project
													setOwningProject(new ModelObject[] {moChangeItemRev}, GETConstants.BusinessObjects.Properties.strOwningProject, project);
												} else {
													GroupMember coordinator = getCoordinator(project);
													assignParticipantResource( (ItemRevision)moChangeItemRev, coordinator, GETDesignReleaseConstants.Participants.coordinator);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}else{
				throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(createObjResponse.serviceData));
			}
		}
		catch (Exception e) 
		{
			//e.printStackTrace();
			throw e;// new Exception(e.getMessage());
		}
		return changeItemRevs;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public GroupMember getEngrManager( TC_Project project ) throws Exception
	{

		GroupMember engrManager = null;

		try {

			ProjectClientId projClientId = new ProjectClientId();
			projClientId.clientId = UUID.randomUUID().toString();
			projClientId.tcProject = project;

			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection()  );
			ProjectTeamsResponse teamResp = projSecurityService.getProjectTeams(new ProjectClientId[]{ projClientId });
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(teamResp.serviceData)) {
				ProjectTeamData[] projectTeamData = teamResp.projectTeams;
				for (ProjectTeamData teamData : projectTeamData) {
					ModelObject[] teamAdmins = teamData.regularMembers;
					for (ModelObject modelObj : teamAdmins) {
						if ( modelObj instanceof GroupMember){
							engrManager = (GroupMember)modelObj;
							Role role = (Role) engrManager.get_role();
							if ( role.get_role_name().equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)){
								return engrManager;
							}

						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			throw e;
		}
		return engrManager;
	}
	
	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public GroupMember getCoordinator( TC_Project project ) throws Exception
	{

		GroupMember coordinator = null;

		try {

			ProjectClientId projClientId = new ProjectClientId();
			projClientId.clientId = UUID.randomUUID().toString();
			projClientId.tcProject = project;

			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection()  );
			ProjectTeamsResponse teamResp = projSecurityService.getProjectTeams(new ProjectClientId[]{ projClientId });
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(teamResp.serviceData)) {
				ProjectTeamData[] projectTeamData = teamResp.projectTeams;
				for (ProjectTeamData teamData : projectTeamData) {
					ModelObject[] teamAdmins = teamData.regularMembers;
					for (ModelObject modelObj : teamAdmins) {
						if ( modelObj instanceof GroupMember){
							coordinator = (GroupMember)modelObj;
							Role role = (Role) coordinator.get_role();
							if ( role.get_role_name().equalsIgnoreCase(GETDesignReleaseConstants.Role.strDesignCoordinator)){
								return coordinator;
							}

						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			throw e;
		}
		return coordinator;
	}
	
	
//	public ArrayList<String> getTcProjRegularMembers( TC_Project project, String role ) throws Exception
//	{
//		ArrayList<String> userList = new ArrayList<String>();
//
//		try {
//		
//			ProjectClientId projClientId = new ProjectClientId();
//			projClientId.clientId = UUID.randomUUID().toString();
//			projClientId.tcProject = project;
//
//			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection() );
//			ProjectTeamsResponse teamResp = projSecurityService.getProjectTeams(new ProjectClientId[]{ projClientId });
//			if (!GETOnTrackCommonSoaOperations.ServiceDataError(teamResp.serviceData)) {
//				DataManagementService dmService = DataManagementService.getService( session.getConnection() );
//				ProjectTeamData[] projectTeamData = teamResp.projectTeams;
//				for (ProjectTeamData teamData : projectTeamData) {
//					ModelObject[] nonPrivMembers = teamData.regularMembers;
//					for (ModelObject modelObj : nonPrivMembers) {
//						if ( modelObj instanceof GroupMember){
//							GroupMember member = (GroupMember)modelObj;
//							Role memberRole = member.get_role();
//							if ( memberRole.get_role_name().equalsIgnoreCase(role)){
//								User user = (User) member.get_user();
//								userList.add( user.get_object_string()) ;
//							}
//						}
//					}
//				}
//			}
//		} 
//		catch (Exception e)
//		{
//			//e.printStackTrace();
//			throw e;
//		}
//		return userList;
//	}
	
	
	public GroupMember getProjectMember( TC_Project project, String user, String role ) throws Exception
	{
		GroupMember member = null;
		
		if ( user.contains("(") && user.contains(")") ){
			user =  user.substring(user.indexOf("(") + 1, user.indexOf(")"));
		}

		try {
			ProjectClientId projClientId = new ProjectClientId();
			projClientId.clientId = UUID.randomUUID().toString();
			projClientId.tcProject = project;

			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection() );
			ProjectTeamsResponse teamResp = projSecurityService.getProjectTeams(new ProjectClientId[]{ projClientId });
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(teamResp.serviceData)) {
				ProjectTeamData[] projectTeamData = teamResp.projectTeams;
				for (ProjectTeamData teamData : projectTeamData) {
					ModelObject[] nonPrivMembers = teamData.regularMembers;
					for (ModelObject modelObj : nonPrivMembers) {
						if ( modelObj instanceof GroupMember){
							member = (GroupMember)modelObj;
							String RoleName = member.get_role().get_role_name();
							String userId = member.get_user().get_user_id();
							if ( RoleName.equalsIgnoreCase(role) && userId.equalsIgnoreCase(user)){
								return member;
							}
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			//e.printStackTrace();
			throw e;
		}
		return member;
	}



	public ArrayList<Item> getItemsBulk( String itemType, ArrayList<String> itemIdList ){

		ArrayList<Item> itemsList = null;
		DataManagementService dmService = DataManagementService.getService( session.getConnection() );

		GetItemAndRelatedObjectsInfo[] itemAndRelObjInfo = new GetItemAndRelatedObjectsInfo[itemIdList.size()];

		for (int inx = 0; inx < itemIdList.size(); inx++) {

			//Item Info
			ItemInfo itemInfo = new ItemInfo();
			AttrInfo[] attrInfo = new AttrInfo[2];
			attrInfo[0] = new AttrInfo(); 
			attrInfo[0].name = "item_id";
			attrInfo[0].value = itemIdList.get(inx);
			attrInfo[1] = new AttrInfo(); 
			attrInfo[1].name = "object_type";
			attrInfo[1].value = itemType;

			itemInfo.ids =  attrInfo;
			itemInfo.clientId = UUID.randomUUID().toString();
			itemInfo.uid = "";
			itemInfo.useIdFirst = true;

			//Revision Info
			RevInfo revInfo = new RevInfo();
			revInfo.processing="None";

			//Dataset Info
			DatasetInfo datasetInfo = new DatasetInfo();
			datasetInfo.filter.processing = "None";  //Valid values are All, Min, or None. 

			itemAndRelObjInfo[inx] = new GetItemAndRelatedObjectsInfo();
			itemAndRelObjInfo[inx].itemInfo = itemInfo;
			itemAndRelObjInfo[inx].revInfo = revInfo;
			itemAndRelObjInfo[inx].datasetInfo = datasetInfo;
			itemAndRelObjInfo[inx].clientId = UUID.randomUUID().toString();

		}

		GetItemAndRelatedObjectsResponse retResp = dmService.getItemAndRelatedObjects( itemAndRelObjInfo );
		ServiceData sData = retResp.serviceData;
		itemsList = new ArrayList<Item>();
		if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
			for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
				ModelObject mObj = sData.getPlainObject(jnx);
				if (mObj instanceof Item) {
					itemsList.add( (Item) mObj );
				}
			}
		}

		return itemsList;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public boolean assignToProject( ModelObject[] assignObjects, TC_Project[] projects ) throws Exception
	{
		boolean isAssigned = false;

		try {

			AssignedOrRemovedObjects assignedObj = new AssignedOrRemovedObjects();
			assignedObj.objectToAssign = assignObjects;
			assignedObj.projects = projects;

			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection() );
			ServiceData sData = projSecurityService.assignOrRemoveObjects( new AssignedOrRemovedObjects[] {assignedObj} );
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				isAssigned = true;
			}
		} 
		catch (Exception e)
		{
			throw e;
		}
		return isAssigned;
	}




	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public boolean removeFromProject( ModelObject[] removeObjects, TC_Project[] projects ) throws Exception
	{
		boolean isAssigned = false;

		try {

			AssignedOrRemovedObjects assignedObj = new AssignedOrRemovedObjects();
			assignedObj.objectToRemove = removeObjects;
			assignedObj.projects = projects;

			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection() );
			ServiceData sData = projSecurityService.assignOrRemoveObjects( new AssignedOrRemovedObjects[] {assignedObj} );
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				isAssigned = true;
			}
		} 
		catch (Exception e)
		{
			throw e;
		}
		return isAssigned;
	}
	

	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public boolean assignToAndRemoveFromProject( ModelObject[] assignObjects, ModelObject[] removeObjects, TC_Project[] projects ) throws Exception
	{
		boolean isAssigned = false;

		try {

			AssignedOrRemovedObjects assignedObj = new AssignedOrRemovedObjects();
			assignedObj.objectToAssign = assignObjects;
			assignedObj.objectToRemove = removeObjects;
			assignedObj.projects = projects;

			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection() );
			ServiceData sData = projSecurityService.assignOrRemoveObjects( new AssignedOrRemovedObjects[] {assignedObj} );
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				isAssigned = true;
			}
		} 
		catch (Exception e)
		{
			throw e;
		}
		return isAssigned;
	}


	public ArrayList<ItemRevision> getItemsRevisionBulk( String itemType, ArrayList<String> itemIdList ){

		ArrayList<ItemRevision> itemsRevList = null;
		DataManagementService dmService = DataManagementService.getService( session.getConnection() );

		GetItemAndRelatedObjectsInfo[] itemAndRelObjInfo = new GetItemAndRelatedObjectsInfo[itemIdList.size()];

		for (int inx = 0; inx < itemIdList.size(); inx++) {

			//Item Info
			ItemInfo itemInfo = new ItemInfo();
			AttrInfo[] attrInfo = new AttrInfo[2];
			attrInfo[0] = new AttrInfo(); 
			attrInfo[0].name = "item_id";
			attrInfo[0].value = itemIdList.get(inx);
			attrInfo[1] = new AttrInfo(); 
			attrInfo[1].name = "object_type";
			attrInfo[1].value = itemType;

			itemInfo.ids =  attrInfo;
			itemInfo.clientId = UUID.randomUUID().toString();
			itemInfo.uid = "";
			itemInfo.useIdFirst = true;

			//Revision Info
			//Rev Info
			RevInfo revInfo = new RevInfo();
			revInfo.clientId = UUID.randomUUID().toString();
			revInfo.id = "0";
			revInfo.nRevs = 1;
			revInfo.processing = "Ids"; // All - all rvs, None - no revs, Ids - uses Rev Id or UID
			revInfo.uid ="";
			revInfo.useIdFirst = true;

			//Dataset Info
			DatasetInfo datasetInfo = new DatasetInfo();
			datasetInfo.filter.processing = "None";  //Valid values are All, Min, or None. 

			itemAndRelObjInfo[inx] = new GetItemAndRelatedObjectsInfo();
			itemAndRelObjInfo[inx].itemInfo = itemInfo;
			itemAndRelObjInfo[inx].revInfo = revInfo;
			itemAndRelObjInfo[inx].datasetInfo = datasetInfo;
			itemAndRelObjInfo[inx].clientId = UUID.randomUUID().toString();

		}

		GetItemAndRelatedObjectsResponse retResp = dmService.getItemAndRelatedObjects( itemAndRelObjInfo );
		ServiceData sData = retResp.serviceData;
		itemsRevList = new ArrayList<ItemRevision>();
		if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
			for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
				ModelObject mObj = sData.getPlainObject(jnx);
				if (mObj instanceof ItemRevision) {
					itemsRevList.add( (ItemRevision) mObj );
				}
			}
		}

		return itemsRevList;
	}

	/********************************************************************
	 * Method to convert string to int
	 * 
	 * @param sintCalculation
	 * @return
	 *********************************************************************/
	public Integer convertToInt(String sintCalculation) throws Exception
	{
		int propvalue = 0;
		Integer value = null;

		try {
			if ( sintCalculation != null && sintCalculation.length() > 0 ){
				if ( sintCalculation.endsWith("w") || sintCalculation.endsWith("W")){
					sintCalculation = sintCalculation.substring(0, sintCalculation.length()-1);
				}
				propvalue = Integer.valueOf(sintCalculation);
				value  = Integer.valueOf(propvalue);
			} else {
				value  = Integer.valueOf("0");
				return value;
			}
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return value;
	}

	/***********************************************************************
	 * Method to set String properties for the given Model Object
	 * 
	 * @param moObject
	 * @param PropertyName
	 * @param propertyValue
	 ***********************************************************************/
	protected void setStringProperties(ModelObject[] moObject, String PropertyName, String propertyValue) throws Exception
	{
		Map<String,VecStruct> propMap = new HashMap<String,VecStruct>();
		try 
		{
			VecStruct propAttr = new VecStruct();
			propAttr.stringVec = new String[] {propertyValue};
			{
				DataManagementService dmService = DataManagementService.getService(session.getConnection());
				if (propertyValue != null)
				{
					propMap.put(PropertyName, propAttr);
					dmService.setProperties(moObject, propMap);
				}
			}
		} 
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	/**************************************************************************
	 * Method to set Date properties for the given Model Object
	 * 
	 * @param moObject
	 * @param PropertyName68
	 * @param dDateValue
	 ***************************************************************************/
	protected boolean setDateProperties(ModelObject[] moObject, String key, Date dDateValue) throws Exception
	{
		Map<String,VecStruct> propMap = new HashMap<String,VecStruct>();
		boolean isUpdated = true;
		String errorMessage = null;
		ServiceData sData;
		try 
		{

			VecStruct vecStructDate = new VecStruct();
			vecStructDate.stringVec = new String[] {Property.toDateString(dDateValue)};
			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			if (dDateValue != null)
			{
				propMap.put(key, vecStructDate);
				sData = dmService.setProperties(moObject, propMap);
			}
			else
			{
				vecStructDate.stringVec = new String[] {""};
				propMap.put(key, vecStructDate);
				sData = dmService.setProperties(moObject, propMap);
			}
			errorMessage = getErrorFromServiceData(sData);

		}
		catch (Exception e)
		{
			isUpdated = false;
			throw new Exception("Error in updating Date value :" + e);
		}
		if (errorMessage != null && !errorMessage.isEmpty())
		{
			isUpdated = false;
			throw new Exception(errorMessage);
		}
		return isUpdated;
	}

	/****************************************************************************
	 * Method to give model object of the group
	 * 
	 * @param groupName
	 *            - Group name to found
	 * @return
	 * @throws Exception
	 ***************************************************************************/
	protected Group getGroup(String groupName) throws Exception {
		ModelObject[] moObjects = null;
		Group group = null;

		GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
		GETQuery.QueriedObjects queriedObjects = queryService1.getQueriedObjs(GETConstants.Query.grpByNameQuery,
				new String[] { GETConstants.Query.strName }, new String[] { groupName });

		if (queriedObjects != null) {
			moObjects = queriedObjects.loadedObjects;
			if (moObjects != null && moObjects.length > 0) {
				if (moObjects[0] instanceof Group) {
					group = (Group) moObjects[0];
				}
			}
		}

		return group;

	}



	/****************************************************************************
	 * Method to get teh EDOT Resource Id
	 * 
	 * @param ItemRevision edotObj
	 * @return
	 * @throws Exception
	 ***************************************************************************/

	public   String getEdotResourceId ( ItemRevision edotObj, String resourceProperty ) throws Exception{

		String resourceId = null;
		try {

			DataManagementService.getService( session.getConnection() );

			Property prop = edotObj.getPropertyObject( resourceProperty );
			ModelObject modelObj = prop.getModelObjectValue();
			if ( modelObj != null && modelObj instanceof User ){
				User resource = (User) modelObj;
				resourceId = resource.get_user_id();
			}

		} catch (NotLoadedException e) {
		}

		return resourceId;
	}

	/****************************************************************************
	 * Method to get the EDOT Group name
	 * 
	 * @param ItemRevision edotObj
	 * @return
	 * @throws Exception
	 ***************************************************************************/
	public   String getEdotGroupName( ItemRevision edotObj, String groupProperty ) throws Exception{

		String groupName = null;
		try {

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ModelObject[] edotObjs = new ModelObject[]{ edotObj };	
			dmService.getProperties( edotObjs, new String[] {groupProperty} );
			Property prop = edotObj.getPropertyObject( groupProperty );
			ModelObject modelObj = prop.getModelObjectValue();
			if ( modelObj != null &&  modelObj instanceof Group ){
				Group group = (Group) modelObj;
				groupName = group.get_name();
			}

		} catch (NotLoadedException e) {

		}

		return groupName;
	}

	/****************************************************************************
	 * Method to get User
	 * 
	 * @param String UserName
	 * @return
	 * @throws Exception
	 ***************************************************************************/
	public User getUser( String UserName) throws Exception
	{
		ModelObject[] moObjects = null;
		User user = null;

		if ( UserName.contains("(") && UserName.contains(")") ){
			UserName =  UserName.substring(UserName.indexOf("(") + 1, UserName.indexOf(")"));
		}

		GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
		GETQuery.QueriedObjects queriedObjects = queryService1.getQueriedObjs(GETConstants.Query.userQuery, new String[] {GETConstants.Query.userId},
				new String[] {UserName});

		if ( queriedObjects != null )
		{
			moObjects = queriedObjects.loadedObjects;
			if(moObjects != null && moObjects.length > 0)
			{
				if ( moObjects[0] instanceof User ) 	
					user = (User) moObjects[0];
			}
		}

		return user;
	}


	/****************************************************************
	 * Method to set Integer properties for the given Model Object
	 * 
	 * @param moObject
	 * @param PropertyName
	 * @param iIntValue
	 ***************************************************************/
	protected void setIntProperties(ModelObject[] moObject, String key, int iIntValue) throws Exception
	{
		Map<String,VecStruct> propMap = new HashMap<String,VecStruct>();
		try 
		{
			{
				VecStruct vecStructIntValues = new VecStruct();
				vecStructIntValues.stringVec = new String[] {Property.toIntString(iIntValue)};
				DataManagementService dmService = DataManagementService.getService(session.getConnection());
				if (iIntValue != 0)
				{
					propMap.put(key, vecStructIntValues);
					dmService.setProperties(moObject, propMap);
				}
				else
				{
					vecStructIntValues.stringVec = new String[] {Property.toIntString(0)};
					propMap.put(key, vecStructIntValues);
					dmService.setProperties(moObject, propMap);
				}
			}
		} 
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}


	/******************************************************************
	 * Method to set Boolean properties for the given Model Object
	 * 
	 * @param moObject
	 * @param PropertyName
	 * @param iIntValue
	 *****************************************************************/
	protected void setbooleanProperties(ModelObject[] moObject, String key, boolean bvalue) throws Exception
	{
		Map<String,VecStruct> propMap = new HashMap<String,VecStruct>();
		try 
		{
			VecStruct vecStructboolean = new VecStruct();
			vecStructboolean.stringVec = new String[] {Property.toBooleanString(bvalue)};
			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			propMap.put(key, vecStructboolean);
			dmService.setProperties(moObject, propMap);
		} 
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	
	

	
	/*****************************************************************
	 * Method to set Reference properties for the given Model Object
	 * 
	 * @param moObject
	 * @param propertyName
	 * @param moValue
	 *****************************************************************/
	protected boolean setOwningProject(ModelObject[] moObject, String key, ModelObject moValue) throws Exception
	{
		
		Map<String,VecStruct> propMap = new HashMap<String,VecStruct>();
		String errorMessage = null;
		boolean isUpdated = true;
		ServiceData sData;
		try 
		{
			VecStruct vecStructRef= new VecStruct();
			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			if (moValue != null)
			{
				vecStructRef.stringVec = new String[] {Property.toModelObjectString(moValue)};
				propMap.put(key, vecStructRef);
				sData = dmService.setProperties(moObject, propMap);
			}
			else
			{

				vecStructRef.stringVec = new String[] {""};
				propMap.put(key, vecStructRef);
				sData = dmService.setProperties(moObject, propMap);
			}
			errorMessage = getErrorFromServiceData(sData);

		}
		catch (Exception e)
		{
			isUpdated = false;
			throw new Exception("Error in updating Reference value :" + e);
		}
		if (errorMessage != null && !errorMessage.isEmpty())
		{
			isUpdated = false;
			throw new Exception(errorMessage);
		}
		//}
		return isUpdated;

	}


	/*****************************************************************
	 * Method to set Reference properties for the given Model Object
	 * 
	 * @param moObject
	 * @param propertyName
	 * @param moValue
	 *****************************************************************/
	protected boolean setRefProperties(ModelObject[] moObject, String key, ModelObject moValue) throws Exception
	{
		Map<String,VecStruct> propMap = new HashMap<String,VecStruct>();
		String errorMessage = null;
		boolean isUpdated = true;
		ServiceData sData;
		try 
		{

			VecStruct vecStructRef= new VecStruct();
			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			if (moValue != null)
			{
				vecStructRef.stringVec = new String[] {Property.toModelObjectString(moValue)};
				propMap.put(key, vecStructRef);
				sData = dmService.setProperties(moObject, propMap);
			}
			else
			{

				vecStructRef.stringVec = new String[] {""};
				propMap.put(key, vecStructRef);
				sData = dmService.setProperties(moObject, propMap);
			}
			errorMessage = getErrorFromServiceData(sData);

		}
		catch (Exception e)
		{
			isUpdated = false;
			throw new Exception("Error in updating Reference value :" + e);
		}
		if (errorMessage != null && !errorMessage.isEmpty())
		{
			isUpdated = false;
			throw new Exception(errorMessage);
		}
		//}
		return isUpdated;

	}



	/*****************************************************************
	 * Method to attach Primary and Secondary Item in the given relation
	 * 
	 * @param primaryItem
	 * @param secondaryItem
	 * @param relation
	 *****************************************************************/
	public String attachDesignReleaseToProject(ModelObject primaryItem, List<ModelObject> secondaryItem, String relation ) throws Exception
	{

		DataManagementService dmService = null;
		ServiceData sData = null;
		try{
			if( primaryItem != null &&  secondaryItem != null ) {
				dmService = DataManagementService.getService(session.getConnection());

				SecondaryData secData[] = new SecondaryData[ secondaryItem.size() ];
				for(int iSecDataCount = 0; iSecDataCount < secondaryItem.size(); iSecDataCount++ )
				{
					secData[ iSecDataCount ] = new SecondaryData();
					secData[ iSecDataCount ].secondary = secondaryItem.get(iSecDataCount);
				}
				CreateOrUpdateRelationsInfo crOrUpRelInfo[] = new CreateOrUpdateRelationsInfo[ 1 ];
				crOrUpRelInfo[ 0 ] = new CreateOrUpdateRelationsInfo();
				crOrUpRelInfo[ 0 ].primaryObject = primaryItem; 
				crOrUpRelInfo[ 0 ].relationType = relation;
				crOrUpRelInfo[ 0 ].secondaryData = secData;
				CreateOrUpdateRelationsResponse createRelResponse = dmService.createOrUpdateRelations( crOrUpRelInfo, false );
				sData = createRelResponse.serviceData;
				if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData))	{

				}else{
					return GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData);
				}
			}
		}catch(Exception e){
			throw e;
		}
		return "Success";
	}


	/******************************************************************
	 * Method to get Associated Design Items
	 * 
	 * @param primaryObj
	 * @return - Returns Design Items and  its property with property Name and property Value as list
	 * @throws Exception 
	 ******************************************************************/
	public Map<ModelObject, Map<String, List<String>>> getDesignReleaseData(String projectId, GETUser getUser) throws Exception
	{

		Map<String,List<String>> propString = null;
		Map<ModelObject, Map<String, List<String>>> designItemPropMap = null;

		DataManagementService dmService = DataManagementService.getService(session.getConnection());//GETDataManagement.getDMService(session.getConnection());
		String sessionUserId = getUser.getUserID();
		String sessionGroup = getUser.getuserGroup();
		String sessionRole = getUser.getRole();

		ArrayList<ItemRevision> edotRevList = new ArrayList<ItemRevision>();

		if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE ) ){
			edotRevList = getDesignReleaseList(  new String[] {GETConstants.Query.strProjectID,GETConstants.Query.strEdotID}, new String[] {projectId, "EDOT*"});
		} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager) ){
			edotRevList = getDesignReleaseList(  new String[] {GETConstants.Query.strProjectID, GETConstants.Query.EngrManagerResource, GETConstants.Query.strEdotID}, new String[] {projectId, sessionUserId + "*", "EDOT*"});
		}  else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer) ){
			edotRevList = getDesignReleaseList( new String[] {GETConstants.Query.strProjectID, GETConstants.Query.EngineerResource, GETConstants.Query.strEdotID}, new String[] {projectId, sessionUserId + "*", "EDOT*"});
		}  else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDesignCoordinator ) ){
			edotRevList = getDesignReleaseList(  new String[] {GETConstants.Query.strProjectID, GETConstants.Query.Coordinator, GETConstants.Query.strEdotID}, new String[] {projectId, sessionUserId + "*", "EDOT*"});
		}
		

		if ( edotRevList != null ) {
			designItemPropMap = new HashMap<ModelObject, Map<String, List<String>>>();
			ArrayList<String> objList = new ArrayList<>();		
			for (int jj = 0; jj < edotRevList.size(); jj++) {
				objList.add(edotRevList.get(jj).getUid());
			}

			dmService.unloadObjects(edotRevList.toArray(new ItemRevision[edotRevList.size()]));
			dmService.loadObjects(objList.toArray(new String[objList.size()]));

			for (int inx = 0; inx < edotRevList.size(); inx++) {
				
				ItemRevision edotRev =   edotRevList.get(inx);
				propString = new HashMap<String,List<String>>(); 
				List<String> statusLit = new ArrayList<String>();
				
				if ( !sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE) &&  !isEdotPublished(edotRev) )
				{
					continue;
				}	

				List<String> engrProject = new ArrayList<String>();
				List<String> designProject = new ArrayList<String>();	

				//Group
				GroupMember engrManager = getPartipantMember( edotRev,  GETDesignReleaseConstants.Participants.engrManager );
				List<String> mainGroup = new ArrayList<String>();
				if ( engrManager != null ){
					mainGroup.add(engrManager.get_group().get_name());
				}

				//Engr & Design Projects
				List<TC_Project> projectsList= getEdotOrgProjects(edotRev);
				if ( projectsList.size() == 1 ){
					TC_Project project = (TC_Project) projectsList.get(0);
					engrProject.add(project.get_object_string());
					designProject.add(project.get_object_string());

				} else if ( projectsList.size() == 2 ){
					TC_Project owningProject = edotRev.get_owning_project();
					TC_Project project = (TC_Project) projectsList.get(0);
					if (owningProject.getUid().equalsIgnoreCase(project.getUid())){
						engrProject.add( project.get_object_string() );
						designProject.add( ((TC_Project) projectsList.get(1)).get_object_string());
					} else {
						engrProject.add( ((TC_Project) projectsList.get(1)).get_object_string());
						designProject.add( project.get_object_string() );
					}
				}

				//Engineer Resource
				List<String> engrResourceList = new ArrayList<String>();
				GroupMember engineer = getPartipantMember( edotRev,  GETDesignReleaseConstants.Participants.engineer);
				if ( engineer != null ){
					User user = (User) engineer.get_the_user();
					engrResourceList.add(user.get_object_string());
				}
				
				//Design Resource
				List<String> designResourceList = new ArrayList<String>();
				GroupMember coordinator = getPartipantMember( edotRev, GETDesignReleaseConstants.Participants.coordinator);
				if ( coordinator!=null ){
					User user = (User) coordinator.get_the_user();
					designResourceList.add(user.get_object_string());
				}
								
				List<String> ecrList = null;
				List<String> ecrReleaseDateList = null;
				List<ItemRevision> ecrRevList = getSecondaryRevisions(edotRev, GETDesignReleaseConstants.Relation.cmImplementedBy);
				if ( ecrRevList != null && ecrRevList.size() > 0 ){
					String ecr = ecrRevList.get(0).get_item_id();
					ecrList = new ArrayList<String>();
					ecrList.add(ecr);
					//Get ECR Release Date
//					ReleaseStatus[] relStatus = ecrRevList.get(0).get_release_status_list();
//					if (relStatus != null && relStatus.length > 0 ){
//						ecrReleaseDateList =  new ArrayList<String>();
//						DateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
//						String releaseDate = dateFormat.format(relStatus[0].get_date_released().getTime());
//						ecrReleaseDateList.add(releaseDate);
//					}
				}

				
				//Technical Data 	
				List<String> techDataList = null;
				List<String> ecnList = null;
				String ecnID  = null;
				List<ItemRevision> techDataRevList = getSecondaryRevisions(edotRev, GETDesignReleaseConstants.Relation.desgnReleaseTechDataRel);
				if ( techDataRevList != null && techDataRevList.size() > 0 ){
					techDataList = new ArrayList<String>();
					techDataList.add( techDataRevList.get(0).get_item_id() + "/" + techDataRevList.get(0).get_item_revision_id() );
					ecnID = getPrimaryObjectID( techDataRevList.get(0), GETDesignReleaseConstants.Relation.cmHasSolItem);
					if ( ecnID != null && ecnID.length() > 0 ){
						ecnList = new ArrayList<String>();
						ecnList.add(ecnID);
					}
				}
				
				//Status
				String status = null;
				String closure = edotRev.getPropertyDisplayableValue(GETDesignReleaseConstants.Properties.closure);
				
				if (closure != null && closure.equalsIgnoreCase("Open")){
					if ( ecnList != null && ecnList.size() > 0 ){
						if ( techDataRevList != null && techDataRevList.size() > 0 ){
							ReleaseStatus[] relStatus = techDataRevList.get(0).get_release_status_list();
							if (relStatus != null && relStatus.length > 0 ){
								status = "TD Released";
							} else {
								status = "In ECN";
							}
						} else {
							status = "In ECN";
						}
					} else if ( ecrList != null && ecrList.size() > 0 ){
						status =  "In ECR";
					} else {
						ModelObject[] stageList = edotRev.get_process_stage_list();
						if ( stageList.length == 0 )
						{
							status = "In Edit";
						} else {
							for(ModelObject stageObj : stageList)
							{
								if(stageObj instanceof EPMReviewTask  || stageObj instanceof EPMDoTask)
								{
									EPMTask task = (EPMTask) stageObj;
									status = task.get_object_string();
								}
							}
						}
					}
				} else if (closure != null && closure.equalsIgnoreCase("Closed")){
					ReleaseStatus[] relStatus = edotRev.get_release_status_list();
					if (relStatus != null && relStatus.length > 0 ){
						status = relStatus[0].get_object_string();
					} else {
						status = "Closed";
					}
				}

				statusLit.add(status);
				

				propString.put( GETConstants.BusinessObjects.Properties.strItemID, getPropertryValues(edotRev, GETConstants.BusinessObjects.Properties.strItemID ) );
				propString.put( GETDesignReleaseConstants.Properties.ActivityId, getPropertryValues( edotRev, GETDesignReleaseConstants.Properties.ActivityId) );
				propString.put( GETDesignReleaseConstants.Properties.ActivityDesc, getPropertryValues( edotRev, GETDesignReleaseConstants.Properties.ActivityDesc ) );
				propString.put( GETDesignReleaseConstants.Properties.mainGroup, mainGroup );
				propString.put( GETDesignReleaseConstants.Properties.templateName, getPropertryValues( edotRev, GETDesignReleaseConstants.Properties.templateName ) );
				propString.put( GETDesignReleaseConstants.Properties.autoclose, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.autoclose ) );
				propString.put( GETDesignReleaseConstants.Properties.status, statusLit );

				propString.put(	GETDesignReleaseConstants.Properties.engrDuration, getPropertryValues(edotRev, GETDesignReleaseConstants.Properties.engrDuration));
				propString.put( GETDesignReleaseConstants.Properties.enggBackOff, getPropertryValues( edotRev, GETDesignReleaseConstants.Properties.enggBackOff ) );
				propString.put( GETDesignReleaseConstants.Properties.engrStartDate, getPropertryValues( edotRev, GETDesignReleaseConstants.Properties.engrStartDate ) );
				propString.put( GETDesignReleaseConstants.Properties.engrReqDate, getPropertryValues( edotRev, GETDesignReleaseConstants.Properties.engrReqDate ) );
				propString.put( GETDesignReleaseConstants.Properties.engrPromiseDate, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.engrPromiseDate ) );
				propString.put( GETDesignReleaseConstants.Properties.enggDateChangeReason, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.enggDateChangeReason ) );
				propString.put( GETDesignReleaseConstants.Properties.engrOrgProject, engrProject );
				propString.put( GETDesignReleaseConstants.Properties.engrResource, engrResourceList );
				propString.put( GETDesignReleaseConstants.Properties.enggComments, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.enggComments ) );
				
				propString.put( GETDesignReleaseConstants.Properties.desgnDuration, getPropertryValues( edotRev, GETDesignReleaseConstants.Properties.desgnDuration ) );
				propString.put( GETDesignReleaseConstants.Properties.dsgnrReqDate, getPropertryValues(edotRev, GETDesignReleaseConstants.Properties.dsgnrReqDate));
				propString.put( GETDesignReleaseConstants.Properties.desPromiseDate, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.desPromiseDate ) );
				propString.put( GETDesignReleaseConstants.Properties.designDateChangeReason, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.designDateChangeReason ) );
				propString.put( GETDesignReleaseConstants.Properties.designOrgProject, designProject );
				propString.put( GETDesignReleaseConstants.Properties.designResource, designResourceList );
				propString.put( GETDesignReleaseConstants.Properties.designComments, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.designComments ) );
				
				propString.put( GETDesignReleaseConstants.Properties.ecr, ecrList );
				propString.put( GETDesignReleaseConstants.Properties.ecn, ecnList );
				propString.put( GETDesignReleaseConstants.Properties.technicalData, techDataList );


				designItemPropMap.put(edotRev, propString);
			}

		}
		return designItemPropMap;
	}

	/*********************************************************************
	 * Method to get property values
	 * 
	 * @param ModelObject mo
	 * @return - Returns Lst of properties
	 * @throws Exception 
	 *********************************************************************/

	public List<String> getPropertryValues(ModelObject mo, String attr) throws Exception
	{
		List<String> result = null;

		try
		{

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
	
	
	public GroupMember getPartipantMember( ModelObject mObj, String participantType ) throws Exception
	{
		GroupMember member = null;

		try
		{
			Property prop = mObj.getPropertyObject(GETDesignReleaseConstants.Relation.hasParticipant);
			if(prop.getPropertyDescription().isArray())
			{
				ModelObject[] mobjParticipants = prop.getModelObjectArrayValue();
				for ( ModelObject modelObject : mobjParticipants ) {
					if ( modelObject instanceof ModelObject ){
						Participant participant = (Participant) modelObject;
						if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
							member = (GroupMember) participant.get_assignee();
						}
					}
				}
			}
			else
			{
				ModelObject modelObject = prop.getModelObjectValue();
				if ( modelObject instanceof ModelObject ){
					Participant participant = (Participant) modelObject;
					if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
						member = (GroupMember) participant.get_assignee();
					}
				}
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			throw ex;
		}

		return member;
	} 
	
	
//	public ItemRevision getSecondaryRevisions( ModelObject edotRev, String property ) throws Exception
//	{
//		ItemRevision secondaryRev = null;
//
//		try
//		{
//			Property prop = edotRev.getPropertyObject(property);
//			if(prop.getPropertyDescription().isArray())
//			{
//				ModelObject mObj = prop.getModelObjectValue();
//				if ( mObj instanceof ItemRevision ){
//					secondaryRev = (ItemRevision) mObj;
//				}
//			}
//			else
//			{
//				ModelObject mObj = prop.getModelObjectValue();
//				if ( mObj instanceof ItemRevision ){
//					secondaryRev = (ItemRevision) mObj;
//				}
//			}
//		}
//		catch(Exception ex)
//		{
//			ex.printStackTrace();
//			throw ex;
//		}
//
//		return secondaryRev;
//	} 
	
	
	public List<ItemRevision> getSecondaryRevisions( ModelObject edotRev, String property ) throws Exception
	{
		List<ItemRevision> secRevs = new ArrayList<ItemRevision>();

		try
		{
			Property prop = edotRev.getPropertyObject(property);
			if(prop.getPropertyDescription().isArray())
			{
				ModelObject[] mObjs = prop.getModelObjectArrayValue();
				for (ModelObject modelObject : mObjs) {
					if ( modelObject instanceof ItemRevision ){
						secRevs.add((ItemRevision) modelObject);
					}
				}

			} else {
				ModelObject mObj = prop.getModelObjectValue();
				if ( mObj instanceof ItemRevision ){
					secRevs.add((ItemRevision) mObj);
				}
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			throw ex;
		}

		return secRevs;
	} 
	
	/*********************************************************************
	 * Method to get property values
	 * 
	 * @param ModelObject mo
	 * @return - Returns Lst of properties
	 * @throws Exception 
	 *********************************************************************/

	public String getPropertryValue(ModelObject modelObj, String property) throws Exception
	{
		String propValue = null;
		try
		{
			Property prop = modelObj.getPropertyObject(property);
			
			if(!prop.getPropertyDescription().isArray())
			{
				propValue = modelObj.getPropertyDisplayableValue(property);
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			throw ex;
		}

		return propValue;
	} 


	/*********************************************************************
	 * Method to get property values
	 * 
	 * @param ModelObject mo
	 * @return - Returns Lst of properties
	 * @throws Exception 
	 *********************************************************************/

	public List<TC_Project> getEdotOrgProjects( ModelObject modelObj ) throws Exception
	{
		List<TC_Project> projects = null;
		try
		{
			Property prop = modelObj.getPropertyObject( GETConstants.BusinessObjects.Properties.projectList );
			List<ModelObject> modelObjects = prop.getModelObjectListValue();
			projects = new ArrayList<TC_Project>();
			for (ModelObject mObj : modelObjects) {
				if (mObj instanceof TC_Project){
					projects.add((TC_Project) mObj);
				}
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			throw ex;
		}

		return projects;
	} 
	
	
	public TC_Project getEngrOrgProject ( ItemRevision edotRev )throws Exception
	{
		TC_Project project = null;
		
		try
		{
			Participant participant = getParticipant( edotRev,  GETDesignReleaseConstants.Participants.engrManager );
			if ( participant!=null ){

				//Main Group
				GroupMember engrManager = (GroupMember) participant.get_assignee();
				
				List<TC_Project> projectsList= getEdotOrgProjects(edotRev);
				//Engr & Design Projects
				if ( projectsList.size() == 1 ){
					project = (TC_Project) projectsList.get(0);
	
				} else if ( projectsList.size() == 2 ){
					GroupMember manager =	getEngrManager((TC_Project) projectsList.get(0));
					if ( engrManager.getUid().equalsIgnoreCase(manager.getUid())){
						project = (TC_Project) projectsList.get(0);
					} else {
						project = (TC_Project) projectsList.get(1);
					}
				}
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			throw ex;
		}
		return project;
	}




	/***************************************************************
	 * Method to create Design Release Plan Item
	 * 
	 * @param ItemName
	 * @param ItemDescription
	 * @return - Created Design Release Plan Item is returned
	 ******************************************************************/
	@SuppressWarnings("unchecked")
	public ModelObject createDesignReleasePlanItem( String projectId, String projectName) throws Exception 
	{
		CreateIn designItemDef = new CreateIn();
		CreateInput designRevisionDef = new CreateInput();
		DataManagementService dmService = null;
		ModelObject DesignPlanItem = null;

		try
		{
			designItemDef.data.boName = GETDesignReleaseConstants.BuinessObjects.GETDsgnReleasePlan;
			designRevisionDef.boName = GETDesignReleaseConstants.BuinessObjects.GETDsgnReleasePlanRevision;
			designItemDef.data.stringProps.put( GETConstants.BusinessObjects.Properties.strItemID, projectId + "PLAN" );
			designItemDef.data.stringProps.put( GETConstants.BusinessObjects.Properties.strObjectName, projectName );
			designItemDef.data.stringProps.put( GETConstants.BusinessObjects.Properties.strObjectDesc, "Design Release Schedule" );
			designRevisionDef.stringProps.put( GETConstants.BusinessObjects.Properties.strItemRevID, "0" );
			designItemDef.data.compoundCreateInput.put( GETDesignReleaseConstants.Properties.revision, new CreateInput[]{  designRevisionDef } );
			dmService = DataManagementService.getService( session.getConnection() );

			CreateResponse createObjResponse = dmService.createObjects( new CreateIn[] { designItemDef } );
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(createObjResponse.serviceData))	{
				for(CreateOut out : createObjResponse.output)
				{
					for(ModelObject mo : out.objects)
					{
						if(mo instanceof Item)
						{
							DesignPlanItem = mo;
						}
					}

				} 
			}else{
				throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(createObjResponse.serviceData));
			}
		}
		catch (ServiceException e) 
		{
			//e.printStackTrace();
			throw e;
		}
		return DesignPlanItem;
	}
	
	
	/***************************************************************
	 * Method to create Design Release Plan Item
	 * 
	 * @param ItemName
	 * @param ItemDescription
	 * @return - Created Design Release Plan Item is returned
	 ******************************************************************/

	public boolean updateBasedOnRole( Map<String, List<String>> mapEdotDataList, String action)  throws Exception
	{
		boolean status = false;
		String promDate = null;
		String comment = null;
		String orgProject = null;
		String resourceName = null;

		DateFormat df = new SimpleDateFormat("MM/dd/yyyy"); 

		if( mapEdotDataList != null ) {

			if(action.equalsIgnoreCase("assign")) {    // Engr Manager - Promise Date - NULL (No Change), Comment - Optional & Resource - Must

				for (Map.Entry<String, List<String>> mapentry : mapEdotDataList.entrySet())	{

					try {
						ItemRevision edotRev = getItemRevision(mapentry.getKey(),itemType);
						List<String> propValue = mapentry.getValue();
						if(!propValue.isEmpty())
						{
							//propValue.get(0) if for Promisse Date which is null, no need to update
							comment = propValue.get(1);
							resourceName = propValue.get(2);

							if( comment != null && comment.length()> 0 )
							{
								status = updateComments(edotRev, comment, "");
							}

							if( resourceName != null && resourceName.length()> 0 )
							{
								GroupMember member = getProjectMember( getEngrOrgProject (edotRev), resourceName, GETDesignReleaseConstants.Role.strEngineer);
								status =	assignParticipantResource( edotRev, member, GETDesignReleaseConstants.Participants.engineer);
							}
						}
					} 
					catch (Exception e) 
					{
						//e.printStackTrace();
						status = false;
						throw e;
					}

				}

			} else if(action.equalsIgnoreCase("dreReassign")) {    // Promise Date - NULL (No Change), Comment - Optional & Resource - Must

				for (Map.Entry<String, List<String>> mapentry : mapEdotDataList.entrySet())	{

					try {
						ItemRevision edotRev = getItemRevision(mapentry.getKey(),itemType);
						List<String> propValue = mapentry.getValue();
						if(!propValue.isEmpty())
						{
							orgProject = propValue.get(0);
							comment = propValue.get(1);
							resourceName = propValue.get(2);

							if( orgProject != null && orgProject.length()> 0 )
							{
								removeFromProject(new ModelObject[]{edotRev.get_items_tag()}, new TC_Project[]{ getEngrOrgProject (edotRev) });
								TC_Project engrOrgProject = getOrgProject( orgProject );
								status = assignToProject(new ModelObject[]{ edotRev.get_items_tag() }, new TC_Project[]{engrOrgProject});
								assignParticipantResource( edotRev, getEngrManager(engrOrgProject), GETDesignReleaseConstants.Participants.engrManager);
							}

							if( comment != null && comment.length()> 0 )
							{
								status = updateComments(edotRev, comment, "");
								//status = true;
							}

							if( resourceName != null && resourceName.length()> 0 )
							{
								GroupMember member = getProjectMember( getEngrOrgProject (edotRev), resourceName, GETDesignReleaseConstants.Role.strEngineer);
								status = assignParticipantResource( edotRev, member, GETDesignReleaseConstants.Participants.engineer);
							}

						}
					} 
					catch (Exception e) 
					{

						status = false;
						throw e;
					}

				}

			}else if(action.equalsIgnoreCase("accept")) {    // Promise Date - Add (First Time), Comment - Optional & Resource - No Change

				for (Map.Entry<String, List<String>> mapentry : mapEdotDataList.entrySet())	{

					try {
						ItemRevision edotRev = getItemRevision(mapentry.getKey(),itemType);
						List<String> propValue = mapentry.getValue();
						if(!propValue.isEmpty())
						{
							promDate = propValue.get(0);
							comment = propValue.get(1);

							if( promDate != null && promDate.length()> 0 )
							{
								Date edotDate = df.parse( promDate );
								status = setDateProperties( new ModelObject[] { edotRev }, GETDesignReleaseConstants.Properties.engrPromiseDate, edotDate);

							}

							if( comment != null && comment.length()> 0 )
							{
								status = updateComments(edotRev, comment, "");
								//status = true;
							}

						}
					} 
					catch (Exception e) 
					{

						status = false;
						throw e;
					}

				}


			}  else if(action.equalsIgnoreCase("updateDC")) {    // Promise Date - Add (First Time), Comment - Optional & Resource - No Change

				for (Map.Entry<String, List<String>> mapentry : mapEdotDataList.entrySet())	{

					try {
						ItemRevision edotRev = getItemRevision(mapentry.getKey(),itemType);
						List<String> propValue = mapentry.getValue();
						if(!propValue.isEmpty())
						{
							promDate = propValue.get(0);
							comment = propValue.get(1);

							if( promDate != null && promDate.length()> 0 )
							{
								Date edotDate = df.parse( promDate );
								status =  setDateProperties( new ModelObject[] { edotRev }, GETDesignReleaseConstants.Properties.desPromiseDate, edotDate);

							}

							if( comment != null && comment.length()> 0 )
							{
								status = updateComments(edotRev, "", comment);
							}
						}
					} 
					catch (Exception e) 
					{
						//e.printStackTrace();
						status = false;
						throw e;
					}
				}
			} 
			else if(action.equalsIgnoreCase("reassign")) {  // Promise Date - Change to NULL, Comment - Optional & Resource - Must

				for (Map.Entry<String, List<String>> mapentry : mapEdotDataList.entrySet())	{

					try {
						ItemRevision edotRev = getItemRevision(mapentry.getKey(),itemType);
						List<String> propValue = mapentry.getValue();
						if(!propValue.isEmpty())
						{
							promDate = propValue.get(0);
							comment = propValue.get(1);
							resourceName = propValue.get(2);

							if( promDate != null && promDate.length()> 0 )
							{
								status = setDateProperties( new ModelObject[] { edotRev }, GETDesignReleaseConstants.Properties.engrPromiseDate, null);  //Pass null to clear the Ref Obj
								//status = true;
							}

							if( comment != null && comment.length()> 0 )
							{
								status = updateComments(edotRev, comment, "");
							}

							if( resourceName != null && resourceName.length()> 0 )
							{
								GroupMember member = getProjectMember( getEngrOrgProject (edotRev), resourceName, GETDesignReleaseConstants.Role.strEngineer);
								status =	assignParticipantResource( edotRev, member, GETDesignReleaseConstants.Participants.engineer);
							}
						}
					} 
					catch (Exception e) 
					{
						status = false;
						throw e;
					}
				}


			} else if(action.equalsIgnoreCase("closure") || action.equalsIgnoreCase("eng_reject") || action.equalsIgnoreCase("reject") || action.equalsIgnoreCase("dre_reject") || action.equalsIgnoreCase("dre_closure")) { // Promise Date - NULL (No Change), Comment - Optional & Resource - No Change

				for (Map.Entry<String, List<String>> mapentry : mapEdotDataList.entrySet())	{

					try {
						ItemRevision edotRev = getItemRevision(mapentry.getKey(),itemType);
						List<String> propValue = mapentry.getValue();
						if(!propValue.isEmpty())
						{
							comment = propValue.get(1);					

							if( comment != null && comment.length()> 0 )
							{

								status = updateComments(edotRev, comment, "");
								//status = true;
							}

						}
					} 
					catch (Exception e) 
					{

						status = false;
						throw e;
					}
				}

			} 
		}


		return status;
	}


	/****************************************************************************
	 * Description: Method to update design release object from teamcenter's data
	 * Returns: Void
	 * 
	 ****************************************************************************/
	@SuppressWarnings("deprecation")
	public void updateDesignRelease(List<DesignRelease> designReleaseList) throws Exception
	{
		try{

			//Collect all EDOT Revisions through Bulk Retrieval
			ArrayList<String> itemIdList = new ArrayList<String>();
			for(DesignRelease designRelease : designReleaseList)
			{
				itemIdList.add(designRelease.getDesignReleaseId());
			}

			ArrayList<ItemRevision> edotList = getItemsRevisionBulk(GETDesignReleaseConstants.BuinessObjects.GETDsgnRelease, itemIdList);

			for (ItemRevision revision : edotList) {

				for(DesignRelease designRelease : designReleaseList) {

					if ( designRelease.getDesignReleaseId().equalsIgnoreCase(revision.get_item_id()) ){
						
						Item item = revision.get_items_tag();

//						System.out.println(revision.get_item_id());

						Map<String, Integer> intPropNameValue = new HashMap<String, Integer>();
						Map<String, Date> datePropNameValue = new HashMap<String, Date>();
						Map<String, String> stringPropNameValue = new HashMap<String, String>();
						Map<String, ModelObject> moPropNameValue = new HashMap<String, ModelObject>();

						if( designRelease.getEngrDuration() != null && designRelease.getEngrDuration().length() > 0 )
						{
							intPropNameValue.put(GETDesignReleaseConstants.Properties.engrDuration, Integer.valueOf(designRelease.getEngrDuration()));
						} else 	{
							intPropNameValue.put(GETDesignReleaseConstants.Properties.engrDuration, Integer.valueOf(0));
						}

						if( designRelease.getBackOff() != null  && designRelease.getBackOff().length() > 0 )
						{
							intPropNameValue.put(GETDesignReleaseConstants.Properties.enggBackOff, Integer.valueOf(designRelease.getBackOff()));
						} else {
							intPropNameValue.put(GETDesignReleaseConstants.Properties.enggBackOff, Integer.valueOf(0));
						}

						if(designRelease.getDesignDuration() != null  && designRelease.getDesignDuration().length() > 0)
						{
							intPropNameValue.put(GETDesignReleaseConstants.Properties.desgnDuration, Integer.valueOf(designRelease.getDesignDuration()));
						} else 	{
							intPropNameValue.put(GETDesignReleaseConstants.Properties.desgnDuration, Integer.valueOf(0));
						}

						String sEnggStartDate = designRelease.getEngrStartDate();					
						if( sEnggStartDate != null  && sEnggStartDate.length() > 0 )
						{
							Date dEnggStartDate = new Date(sEnggStartDate);
							datePropNameValue.put( GETDesignReleaseConstants.Properties.engrStartDate, dEnggStartDate );
						} else {
							datePropNameValue.put( GETDesignReleaseConstants.Properties.engrStartDate, null );
						}

						String sEnggReqDate = designRelease.getEngrRequiredDate();
						if( sEnggReqDate != null && sEnggReqDate.length() > 0  )
						{
							Date dEnggReqDate = new Date(sEnggReqDate);
							datePropNameValue.put( GETDesignReleaseConstants.Properties.engrReqDate, dEnggReqDate);
						} else {
							datePropNameValue.put( GETDesignReleaseConstants.Properties.engrReqDate, null);
						}

						String sDesgReqDate = designRelease.getDesignRequiredDate();
						if( sDesgReqDate != null && sDesgReqDate.length() > 0 )
						{
							Date dDesgReqDate = new Date(sDesgReqDate);
							datePropNameValue.put( GETDesignReleaseConstants.Properties.dsgnrReqDate,dDesgReqDate);
						} else {
							datePropNameValue.put( GETDesignReleaseConstants.Properties.dsgnrReqDate, null);
						}

						stringPropNameValue.put ( GETDesignReleaseConstants.Properties.enggDateChangeReason, designRelease.getEngrDateChangeReason());
						stringPropNameValue.put ( GETDesignReleaseConstants.Properties.designDateChangeReason, designRelease.getDesignDateChangeReason());
						stringPropNameValue.put ( GETDesignReleaseConstants.Properties.ActivityDesc, designRelease.getDescription());

					
						//Projects and Resources to be set
						
						TC_Project engrOrgProject = getOrgProject(designRelease.getEngrOrgProject());
						String designProjectName = designRelease.getDesignOrgProject();
						TC_Project designOrgProject = null;
						if ( designProjectName != null && designProjectName.length() > 0 ){
							designOrgProject = getOrgProject(designRelease.getDesignOrgProject());
						}
						
						List<TC_Project> projectsList = getEdotOrgProjects(revision.get_items_tag());
						TC_Project[] projects = projectsList.toArray(new TC_Project[projectsList.size()]);
						
						//Remove EDOTs from Projects
						removeFromProject(new ModelObject[]{item}, projects);
						
						if (designOrgProject != null ){
							if ( engrOrgProject.getUid().equalsIgnoreCase(designOrgProject.getUid())){
								assignToProject(new ModelObject[]{item}, new TC_Project[]{engrOrgProject});
							} else {
								assignToProject(new ModelObject[]{item}, new TC_Project[]{engrOrgProject, designOrgProject});
							}	
						} else {
							assignToProject(new ModelObject[]{item}, new TC_Project[]{engrOrgProject});
						}
						
						setOwningProject(new ModelObject[] {revision}, GETConstants.BusinessObjects.Properties.strOwningProject, engrOrgProject);

						
						GroupMember engrManager = getEngrManager(engrOrgProject);
						assignParticipantResource( revision, engrManager, GETDesignReleaseConstants.Participants.engrManager);
						
						GroupMember member = null;
						if ( designRelease.getEngrResource() != null && designRelease.getEngrResource().length() > 0 ) {
							member = getProjectMember( engrOrgProject, designRelease.getEngrResource(), GETDesignReleaseConstants.Role.strEngineer);
							assignParticipantResource( revision, member, GETDesignReleaseConstants.Participants.engineer);
						} else {
							removeParticipant(revision, GETDesignReleaseConstants.Participants.engineer);
						}
						
						if ( designRelease.getDesignResource() != null && designRelease.getDesignResource().length() > 0 ) {
							member = getProjectMember( designOrgProject, designRelease.getDesignResource(), GETDesignReleaseConstants.Role.strDesignCoordinator);
							assignParticipantResource( revision, member, GETDesignReleaseConstants.Participants.coordinator);
						} else {
							removeParticipant(revision, GETDesignReleaseConstants.Participants.coordinator);
						}


						updateComments( revision, designRelease.getEngrComment().toString(), designRelease.getDesignComment().toString() );
						setbooleanProperties( new ModelObject[] { revision }, GETDesignReleaseConstants.Properties.autoclose, designRelease.getAutoClose());

						for (Map.Entry<String, Integer> mapentry : intPropNameValue.entrySet())
						{
							setIntProperties( new ModelObject[] { revision }, mapentry.getKey(), mapentry.getValue());
						}

						for(Map.Entry<String, Date> mapentry : datePropNameValue.entrySet()) 
						{
							setDateProperties( new ModelObject[] { revision }, mapentry.getKey(), mapentry.getValue());
						}
						for(Map.Entry<String, String> mapentry : stringPropNameValue.entrySet()) 
						{
							setStringProperties( new ModelObject[] { revision }, mapentry.getKey(), mapentry.getValue());
						}

						for(Map.Entry<String, ModelObject> mapentry : moPropNameValue.entrySet()) 
						{
							setRefProperties( new ModelObject[] { revision }, mapentry.getKey(), mapentry.getValue());
						}
						break;
					}

				}
			}

		}catch (ServiceException e) 
		{
			e.printStackTrace();
			throw e;
		}
	}



	/****************************************************************************
	 * Description: Method to update Comments
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public boolean updateComments(ItemRevision moRevision,String engComment, String desComment ) throws Exception
	{
		boolean isUpdated = false;
		DataManagementService dmService = DataManagementService.getService(session.getConnection());
		try {
			dmService.getProperties(new ModelObject[] {moRevision}, new String[] { GETDesignReleaseConstants.Properties.enggComments,GETDesignReleaseConstants.Properties.designComments});
			Property engComntProp=  moRevision.getPropertyObject(GETDesignReleaseConstants.Properties.enggComments);
			String[] engComnts = engComntProp.getStringArrayValue();

			if((engComnts != null) && (engComnts.length > 0)){
				String  engComnt = engComnts[(int) ((engComnts.length)-1l)];

				if(engComnt.matches(engComment))
				{
					isUpdated = true;
				}
				else
				{
					if(engComment != null && engComment.length() > 0  )
					{
						isUpdated = updateArrayProperties(moRevision, GETDesignReleaseConstants.Properties.enggComments, engComment);
					}
				}
			}
			else
			{
				if(engComment != null && engComment.length() > 0  )
				{
					isUpdated = updateArrayProperties(moRevision, GETDesignReleaseConstants.Properties.enggComments, engComment);
				}
				else
				{
					isUpdated = true;
				}
			}

			Property desComntProp=  moRevision.getPropertyObject(GETDesignReleaseConstants.Properties.designComments);
			String[] desComnts = desComntProp.getStringArrayValue();
			if((desComnts != null) && (desComnts.length > 0 ))
			{
				String  desComnt = desComnts[(int) ((desComnts.length)-1l)];

				if(desComnt.matches(desComment))
				{
					isUpdated = true;
				}
				else
				{

					if(desComment != null && desComment.length() > 0  )
					{
						isUpdated = updateArrayProperties(moRevision, GETDesignReleaseConstants.Properties.designComments,desComment);
					}
				}
			}
			else
			{
				if(desComment != null && desComment.length() > 0  )
				{
					isUpdated = updateArrayProperties(moRevision, GETDesignReleaseConstants.Properties.designComments, desComment);
				}
				else
				{
					isUpdated = true;
				}
			}
		} catch (NotLoadedException e) {

			throw e;
		} catch (Exception e) {

			throw e;
		}

		return isUpdated;
	}


	/****************************************************************************
	 * Description: Method to get EDOt Revs
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public ItemRevision getItemRevision ( String itemId,String itemType ) throws Exception{

		ItemRevision rev = null;
		try {

			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			GetItemAndRelatedObjectsInfo infos = new GetItemAndRelatedObjectsInfo();

			//Item Info
			ItemInfo itemInfo = new ItemInfo();
			itemInfo.clientId = "itemInfo";
			itemInfo.uid = "";
			itemInfo.useIdFirst = true;
			AttrInfo[] attrInfo = new AttrInfo[2];
			attrInfo[0] = new AttrInfo(); 
			attrInfo[0].name = "item_id";
			attrInfo[0].value = itemId;
			attrInfo[1] = new AttrInfo(); 
			attrInfo[1].name = "object_type";
			attrInfo[1].value = itemType;//Engr Change Request
			itemInfo.ids =  attrInfo ;

			//Rev Info
			RevInfo revInfo = new RevInfo();
			revInfo.clientId = "revInfo";
			revInfo.id = "0";
			revInfo.nRevs = 1;
			revInfo.processing = "Ids"; // All - all rvs, None - no revs, Ids - uses Rev Id or UID
			revInfo.uid ="";
			revInfo.useIdFirst = true;

			//Dataset Info
			DatasetInfo datasetInfo = new DatasetInfo();
			datasetInfo.filter.processing = "None";  //Valid values are All, Min, or None. 

			infos.itemInfo = itemInfo;
			infos.revInfo = revInfo;
			infos.datasetInfo = datasetInfo;

			GetItemAndRelatedObjectsResponse retResp = dmService.getItemAndRelatedObjects( new GetItemAndRelatedObjectsInfo[]{ infos });
			ServiceData sData = retResp.serviceData;
			if ( !GETOnTrackCommonSoaOperations.ServiceDataError( sData ) ) {
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int inx = 0; inx < sData.sizeOfPlainObjects(); inx++) {
						ModelObject mObj = sData.getPlainObject(inx);
						if (mObj instanceof ItemRevision) {
							rev = (ItemRevision) mObj;
						}	
					}
				}
			}
		} catch (Exception e) {

			throw e;
		}
		return rev;
	}
	
	
	/****************************************************************************
	 * Description: Method to get EDOt Revs
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public List<Dataset> getDatasetList ( String itemId, String revId ) throws Exception{

		Dataset dataSet  = null;
		List<Dataset> dataSetList = null;
		try {

			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			GetItemAndRelatedObjectsInfo infos = new GetItemAndRelatedObjectsInfo();
			
			//Item Info
			ItemInfo itemInfo = new ItemInfo();
			itemInfo.clientId = "itemInfo";
			itemInfo.uid = "";
			itemInfo.useIdFirst = false;
			AttrInfo attrInfo = new AttrInfo();
			attrInfo.name = "item_id";
			attrInfo.value = itemId;
			itemInfo.ids = new AttrInfo[] { attrInfo };

			//Rev Info
			RevInfo revInfo = new RevInfo();
			revInfo.clientId = "revInfo";
			revInfo.id = revId;
			revInfo.nRevs = 1;
			revInfo.processing = "Ids"; // All - all rvs, None - no revs, Ids - uses Rev Id or UID
			revInfo.uid ="";
			revInfo.useIdFirst = true;

			//Dataset Info
			DatasetInfo datasetInfo = new DatasetInfo();
			datasetInfo.clientId = "clientId";
			datasetInfo.filter.processing = "All";  //Valid values are All, Min, or None. 

			infos.itemInfo = itemInfo;
			infos.revInfo = revInfo;
			infos.datasetInfo = datasetInfo;

			GetItemAndRelatedObjectsResponse retResp = dmService.getItemAndRelatedObjects( new GetItemAndRelatedObjectsInfo[]{ infos });
			ServiceData sData = retResp.serviceData;
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				dataSetList = new ArrayList<Dataset>();
				for (int inx = 0; inx < sData.sizeOfPlainObjects(); inx++) {
					ModelObject mObj = sData.getPlainObject(inx);
					if (mObj instanceof Dataset) {
						dataSet  = (Dataset) mObj;
						dataSetList.add( dataSet );
					}	
				}
			}
			
		} catch (Exception e) {

			throw e;
		}
		return dataSetList;
	}
	
	
	public List<ImanFile> getAllNamedRefList ( String itemId, String revId ) throws Exception{

		Dataset dataSet  = null;
		List<ImanFile> imanFileList = null;
		try {

			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			GetItemAndRelatedObjectsInfo infos = new GetItemAndRelatedObjectsInfo();
			
			//Item Info
			ItemInfo itemInfo = new ItemInfo();
			itemInfo.clientId = "itemInfo";
			itemInfo.uid = "";
			itemInfo.useIdFirst = false;
			AttrInfo attrInfo = new AttrInfo();
			attrInfo.name = "item_id";
			attrInfo.value = itemId;
			itemInfo.ids = new AttrInfo[] { attrInfo };

			//Rev Info
			RevInfo revInfo = new RevInfo();
			revInfo.clientId = "revInfo";
			revInfo.id = revId;
			revInfo.nRevs = 1;
			revInfo.processing = "Ids"; // All - all rvs, None - no revs, Ids - uses Rev Id or UID
			revInfo.uid ="";
			revInfo.useIdFirst = true;

			//Dataset Info
			DatasetInfo datasetInfo = new DatasetInfo();
			datasetInfo.clientId = "clientId";
			datasetInfo.filter.processing = "All";  //Valid values are All, Min, or None. 

			infos.itemInfo = itemInfo;
			infos.revInfo = revInfo;
			infos.datasetInfo = datasetInfo;

			GetItemAndRelatedObjectsResponse retResp = dmService.getItemAndRelatedObjects( new GetItemAndRelatedObjectsInfo[]{ infos });
			ServiceData sData = retResp.serviceData;
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				imanFileList = new ArrayList<ImanFile>();
				for (int inx = 0; inx < sData.sizeOfPlainObjects(); inx++) {
					ModelObject mObj = sData.getPlainObject(inx);
					if (mObj instanceof Dataset) {
						dataSet  = (Dataset) mObj;
						ModelObject[] namedRefList = dataSet.get_ref_list();
						for (ModelObject mObject : namedRefList) {
							if ( mObject instanceof ImanFile){
								imanFileList.add( (ImanFile) mObject );
							}
						}

					}	
				}
			}
			
		} catch (Exception e) {

			throw e;
		}
		return imanFileList;
	}


	/****************************************************************************
	 * Description: Method to get EDOt Revs
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	//	public ItemRevision getItem ( String itemId,String itemType ) throws Exception{
	public Item getItem ( String itemId, String itemType) throws Exception{

		Item item = null;
		try {

			DataManagementService dmService = DataManagementService.getService(session.getConnection());
			GetItemAndRelatedObjectsInfo infos = new GetItemAndRelatedObjectsInfo();

			//Item Info
			ItemInfo itemInfo = new ItemInfo();
			itemInfo.clientId = "itemInfo";
			itemInfo.uid = "";
			itemInfo.useIdFirst = true;
			AttrInfo[] attrInfo = new AttrInfo[2];
			attrInfo[0] = new AttrInfo(); 
			attrInfo[0].name = "item_id";
			attrInfo[0].value = itemId;
			attrInfo[1] = new AttrInfo(); 
			attrInfo[1].name = "object_type";
			attrInfo[1].value = itemType;//Engr Change Request
			itemInfo.ids =  attrInfo ;

			//Rev Info
			RevInfo revInfo = new RevInfo();
			revInfo.clientId = "revInfo";
			revInfo.id = "0";
			revInfo.nRevs = 1;
			revInfo.processing = "Ids"; // All - all rvs, None - no revs, Ids - uses Rev Id or UID
			revInfo.uid = "";
			revInfo.useIdFirst = true;

			//Dataset Info
			DatasetInfo datasetInfo = new DatasetInfo();
			datasetInfo.filter.processing = "None";  //Valid values are All, Min, or None. 

			infos.itemInfo = itemInfo;
			infos.revInfo = revInfo;
			infos.datasetInfo = datasetInfo;

			GetItemAndRelatedObjectsResponse retResp = dmService.getItemAndRelatedObjects( new GetItemAndRelatedObjectsInfo[]{ infos });
			ServiceData sData = retResp.serviceData;
			if ( !GETOnTrackCommonSoaOperations.ServiceDataError( sData ) ) {
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int inx = 0; inx < sData.sizeOfPlainObjects(); inx++) {
						ModelObject mObj = sData.getPlainObject(inx);
						if (mObj instanceof Item) {
							item = (Item) mObj;
						}	
					}
				}
			}
		} catch (Exception e) {

			throw e;
		}
		return item;
	}


	/****************************************************************************
	 * Description: Method to get EDOt list for selected ECR
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public  ArrayList<String> getEdotsForSelectedECR(String ecrID) throws Exception {
		// TODO Auto-generated method stub
		ArrayList<String> edotList = new ArrayList<String>();
		ItemRevision ecrRev = getItemRevision(ecrID,GETDesignReleaseConstants.BuinessObjects.GETEcr);//"get6ECR"); Engr Change Request
		if(ecrRev != null)
		{
			edotList= getSecondaryObjectsID(ecrRev,GETDesignReleaseConstants.Relation.cmImplements);//GETOnTrackConstants.Relation.desgnReleasePlanRelation
		}


		return edotList;

	}

	/****************************************************************************
	 * Description: Method to get ECR List
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/

	public ArrayList<String> getECRList( String[] entries, String[] values ) throws Exception
	{

		ArrayList<String> ecrList = new ArrayList<String>();
		String queryECR = GETDesignReleaseConstants.Query.strECRQuery;
		ImanQuery query = findQuery(queryECR);

		QueryInput qryInput = new QueryInput();

		qryInput.clientId = UUID.randomUUID().toString();
		qryInput.limitList = new ModelObject[0];
		qryInput.maxNumToReturn = 1000;
		qryInput.query = query;
		qryInput.resultsType = 0;
		qryInput.entries = entries;
		qryInput.values = values;

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		SavedQueryService queryService = SavedQueryService.getService( session.getConnection());

		SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

		try {
			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof ItemRevision ){
							String ecrItemId = ((ItemRevision) mObj).get_item_id();
							if ( !ecrList.contains(ecrItemId) ) {
								ecrList.add(ecrItemId);
							}
						}
					}
				}
				else
				{
					throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
				}
			}

		} catch (NotLoadedException e) {
			e.printStackTrace();
			throw e;
		}

		return ecrList;
	}


	/****************************************************************************
	 * Description: Method to get ECN List
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/

	public ArrayList<String> getECNList(String ecrID ) throws Exception
	{

		ArrayList<String> ecnList = new ArrayList<String>();
		ItemRevision ecrRev = getItemRevision(ecrID,GETDesignReleaseConstants.BuinessObjects.GETEcr);//"get6ECR"); Engr Change Request
		if(ecrRev != null)
		{
			ecnList= getSecondaryObjectsID(ecrRev,GETDesignReleaseConstants.Relation.cmImplementedBy);
		}

		return ecnList;
	}

	/****************************************************************************
	 * Description: Method to get Technical Data for selected ECN
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/

	public ArrayList<String> getTDForSelectedECN(String ecnID ) throws Exception
	{

		ArrayList<String> tdList = new ArrayList<String>();
		ItemRevision ecnRev = getItemRevision(ecnID,GETDesignReleaseConstants.BuinessObjects.GETEcn);
		if(ecnRev != null)
		{
			tdList= getSecondaryObjectsID(ecnRev,GETDesignReleaseConstants.Relation.cmHasSolItem);
		}

		return tdList;
	} 

	/****************************************************************************
	 * Description: Method to assign selected EDOTs to ECR
	 * Returns: String
	 * 
	 ****************************************************************************/
	public String  linkTDandECNtoEDOt(String edot,String ecnID, String techData) throws Exception 
	{
		String status = PLMConstants.fail;

		ItemRevision ecnRev = null;
		ItemRevision techDataRev = null;
		ItemRevision edotRev = getItemRevision(  edot,itemType);
		if(edotRev != null)
		{
			ecnRev = getItemRevision(  ecnID,GETDesignReleaseConstants.BuinessObjects.GETEcn);
			techDataRev = getItemRevision(  techData,GETDesignReleaseConstants.BuinessObjects.GETTechData);

		}
		else
		{
			throw new Exception("Not able to get the edot "+edot+"  revision.");
		}
		if(null != edotRev && null != ecnRev && null != techDataRev)
		{
			setRefProperties(new ModelObject[]{edotRev},  GETDesignReleaseConstants.Properties.ecn, ecnRev.get_items_tag());//(edotRevList.get(j), GETOnTrackConstants.Properties.ecr, ecrID);
			setRefProperties(new ModelObject[]{edotRev},  GETDesignReleaseConstants.Properties.technicalData, techDataRev);//(edotRevList.get(j), GETOnTrackConstants.Properties.ecr, ecrID);
			status =  PLMConstants.success;

		}

		return status;

	}

	/****************************************************************************
	 * Description: Method to remove selected EDOTs from ECR
	 * Returns: String
	 * 
	 ****************************************************************************/
	public String  removeTDandECNtoEDOt(String edot,String ecnID, String techData) throws Exception 
	{

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		String status = PLMConstants.fail;
		boolean isUpdated = false;
		ItemRevision edotRev = getItemRevision(  edot, itemType);

		isUpdated = setRefProperties(new ModelObject[]{edotRev},  GETDesignReleaseConstants.Properties.ecn, null);
		if(!isUpdated)
		{
			throw new Exception("Unable to remove the reference for Technical Data.");
		}
		isUpdated = setRefProperties(new ModelObject[]{edotRev},  GETDesignReleaseConstants.Properties.technicalData, null);
		if(!isUpdated)
		{
			throw new Exception("Technical Data Reference not removed.");
		}
		return status;

	}

	/****************************************************************************
	 * Description: Method to assign selected EDOTs to ECR
	 * Returns: String
	 * 
	 ****************************************************************************/
	public Map<String, List<String>>  getLinkedECNAndTD(String edot) throws Exception 
	{
		Map<String,List<String>> propString =  new HashMap<String,List<String>>();
		ItemRevision edotRev = getItemRevision(  edot,itemType);
		if(edotRev != null)
		{
			propString.put( GETDesignReleaseConstants.Properties.ecn, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.ecn ) );
			propString.put( GETDesignReleaseConstants.Properties.technicalData, getPropertryValues ( edotRev, GETDesignReleaseConstants.Properties.technicalData ) );

		}
		else
		{
			throw new Exception("Not able to get the edot "+edot+"  revision.");
		}


		return propString;

	}

	/****************************************************************************
	 * Description: Method to assign selected EDOTs to ECR
	 * Returns: String
	 * 
	 ****************************************************************************/
	public boolean  getLinkedECRToEdot(String edot) throws Exception 
	{
		boolean isEdotImplemented = false;
		List<String> ecrList = new ArrayList<String>();
		//DataManagementService dmService = DataManagementService.getService(session.getConnection());//GETDataManagement.getDMService(session.getConnection());

		ItemRevision edotRev = getItemRevision(  edot,itemType);
		if(edotRev != null)
		{

			//dmService.getProperties(new ModelObject[]{edotRev}, new String[]{GETDesignReleaseConstants.Relation.cmImplementedBy});
			ecrList = edotRev.getPropertyDisplayableValues(GETDesignReleaseConstants.Relation.cmImplementedBy);

			if(ecrList != null && ecrList.size() > 0 ) 
			{
				isEdotImplemented = true;
			}
		}
		return isEdotImplemented;

	}



	/****************************************************************************
	 * Description: Method to assign selected EDOTs to ECR
	 * Returns: String
	 * 
	 ****************************************************************************/
	public String  assignEDOTstoECR(String[] edot,String ecrID) throws Exception   
	{
		String status = "Fail";
		ItemRevision edotRev;
		List<ItemRevision> edotRevList = new ArrayList<ItemRevision>();
		ItemRevision ecrRev = getItemRevision(  ecrID, GETDesignReleaseConstants.BuinessObjects.GETEcr);
		if(ecrRev != null)
		{
			List<String> edotList = Arrays.asList(edot); 

			for (int inx = 0; inx < edotList.size(); inx++) {
				edotRev  = getItemRevision( edot[inx], itemType);
				edotRevList.add(edotRev);
			}
		}
		if(null != edotRevList && edotRevList.size() > 0)
		{
			status = attachEdotsToEcr(ecrRev, edotRevList, GETDesignReleaseConstants.Relation.cmImplements);
			if(!status.equals(PLMConstants.success))
			{
				status = "Assignment of EDOTs to ECR Failed";
			}

		}

		return status;

	}
	/****************************************************************************
	 * Description: Method to remove selected EDOTs from ECR
	 * Returns: String
	 * 
	 ****************************************************************************/
	public String  removeEdotFromECR(String[] edot,String ecrID) throws Exception 
	{

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		String status = PLMConstants.fail;
		boolean isUpdated = false;
		ItemRevision ecrRev = getItemRevision(  ecrID, GETDesignReleaseConstants.BuinessObjects.GETEcr);

		RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
		typeFilter.relationTypeName = GETDesignReleaseConstants.Relation.cmImplements; 
		typeFilter.otherSideObjectTypes = new String[] {GETDesignReleaseConstants.BuinessObjects.GETDsgnReleaseRevision};// GET6ECRRevision

		ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
		relationPref.expItemRev = false;
		relationPref.returnRelations = true;
		relationPref.info = new RelationAndTypesFilter[]{ typeFilter }; 

		ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary(new ModelObject[]{ ecrRev },relationPref);
		if(!GETOnTrackCommonSoaOperations.ServiceDataError(relationResp.serviceData)) {
			for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
				for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
					ExpandGRMRelationship relations[] =  relationData.relationshipObjects;
					for(int k = 0;k < relations.length; k++){
						ExpandGRMRelationship relation = relations[k];

						if(relation.relation instanceof ImanRelation) {
							ImanRelation paramReq = (ImanRelation)relation.relation;
							ItemRevision edotRev =(ItemRevision) relation.otherSideObject;
							String edotId = edotRev.get_current_id();

							for(int nEdots = 0; nEdots < edot.length; nEdots++)
							{
								if(edotId.equals(edot[nEdots]))
								{
									dmService.deleteObjects(new ModelObject[]{paramReq});
									status =  PLMConstants.success;
								}
							}
						}
					}
				}
			}
		}

		return status;

	}



	/****************************************************************************
	 * Description: Method to remove attach EDOTs from ECR
	 * Returns: String
	 * 
	 ****************************************************************************/

	public String attachEdotsToEcr( ItemRevision ecrRev, List<ItemRevision> edotList, String relation ) throws Exception
	{

		String status = PLMConstants.success;
		DataManagementService dmService = null;
		ServiceData sData = null;
		try{
			if( ecrRev != null &&  edotList != null ) {
				dmService = DataManagementService.getService( session.getConnection() );

				SecondaryData secData[] = new SecondaryData[ edotList.size() ];
				for(int count = 0; count < edotList.size(); count++ )
				{
					secData[ count ] = new SecondaryData();
					secData[ count ].secondary = edotList.get(count);
				}
				CreateOrUpdateRelationsInfo crOrUpRelInfo = new CreateOrUpdateRelationsInfo();
				crOrUpRelInfo.clientId = UUID.randomUUID().toString();
				crOrUpRelInfo.primaryObject = ecrRev; 
				crOrUpRelInfo.relationType = relation;
				crOrUpRelInfo.secondaryData = secData;
				CreateOrUpdateRelationsResponse createRelResponse = dmService.createOrUpdateRelations( new CreateOrUpdateRelationsInfo[] {crOrUpRelInfo}, false );
				sData = createRelResponse.serviceData;
				if(GETOnTrackCommonSoaOperations.ServiceDataError(sData))	
				{
					status =  GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData);

				}

			}
		}catch(Exception e){
			throw e;
		}
		return status;
	}

	/****************************************************************************
	 * Description: Method to handle the Workflow execution based on action performed on the UI
	 * Returns: boolean
	 * 
	 ****************************************************************************/

	public boolean executePublishWorkFlow(String edotId, String OrgProject, GETUser getUser, String action)
			throws Exception {

		boolean response = false;
		ImanQuery query = null;
		Participant participant = null;
		GroupMember engrManagerMember = null;
		GroupMember dreMember = null;
		GroupMember engineerMember = null;
		String closure = null;
		String disposition = null;

		try {

			ItemRevision edotRev = getItemRevision(edotId, itemType);
			DataManagementService.getService(session.getConnection());

			GETDesignReleaseWorkflow edotWorkflow = new GETDesignReleaseWorkflow(session.getConnection());

			query = findQuery(GETConstants.Query.queryGroupMember);

			//Engr Manager
			engrManagerMember = getPartipantMember( edotRev,  GETDesignReleaseConstants.Participants.engrManager);

			//Engineer
			engineerMember = getPartipantMember( edotRev,  GETDesignReleaseConstants.Participants.engineer);

			closure = edotRev.getPropertyDisplayableValue(GETDesignReleaseConstants.Properties.closure);
			disposition = edotRev.getPropertyDisplayableValue(GETDesignReleaseConstants.Properties.disposition);

			if (closure.equalsIgnoreCase("Open") && disposition.equalsIgnoreCase("None")) {

				if (edotRev.get_process_stage_list().length == 0) {

					if (engrManagerMember != null) {
						// Initiate Publish Workflow
						String workflowName = edotRev.get_item_id() + "-" + edotRev.get_current_name();
						response = createNewProcess(GETDesignReleaseConstants.Workflow.GETEDOTPublish, edotRev.getUid(), workflowName);
					}
				} else { //In Workflow

					String sessionUserId = getUser.getUserID(); // Session User Id
					String sessionRole = getUser.getRole(); // Session User Role
					String sessionGroup = getUser.getuserGroup();

					// Get Design Release Member
					if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
						dreMember = getGroupMember(query, 
								new String[] { GETConstants.Query.group, GETConstants.Query.role, GETConstants.Query.user },
								new String[] { sessionGroup + "*", sessionRole, sessionUserId });
					}

					//Engr Manager Assigns Engineer Participant
					if (action.equalsIgnoreCase("assign")
							&& sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)) // Engr Manager
					{
						if (engineerMember != null) {
							response = edotWorkflow.edotApproval(edotRev, engrManagerMember);
						} else {
							throw new Exception("Engineer Participant is not assigned...!!! !");
						}

					} else if (action.equalsIgnoreCase("accept") && sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer)) {// Engineer

						response = edotWorkflow.edotApproval(edotRev, engineerMember);

					} else if (action.equalsIgnoreCase("reject")) {

						if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)) {
							response = edotWorkflow.edotReject(edotRev, engrManagerMember);
							if (response == true) {
								response = edotWorkflow.engrManagerRejectClosure(edotRev, false);
							} else {
								throw new Exception("Unable to Reject EDOT !");
							}

						} else if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
							response = edotWorkflow.edotReject(edotRev, dreMember);
						}

					} else if ((action.equalsIgnoreCase("eng_reject")) || (action.equalsIgnoreCase("dre_reject"))) {

						if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer)) {
							response = edotWorkflow.edotReject(edotRev, engineerMember);
						} else if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
							response = edotWorkflow.edotReject(edotRev, dreMember);
						}

					} else if ((action.equalsIgnoreCase("closure")) || (action.equalsIgnoreCase("dre_closure"))) { // Both

						if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)) {
							response = edotWorkflow.edotReject(edotRev, engrManagerMember);
							if (response == true) {
								response = edotWorkflow.engrManagerRejectClosure(edotRev, true);
							} else {
								throw new Exception("Unable to close EDOT !");
							}

						} else if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer)) {
							response = edotWorkflow.edotReject(edotRev, engineerMember);
						} else if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
							response = edotWorkflow.edotApproval(edotRev, dreMember);
						}
					// Engineer delegates to another Engineer
					} else if (action.equalsIgnoreCase("reassign")) {
						response = edotWorkflow.delegateEngineer(edotRev, engineerMember);

						if (!response) {
							throw new Exception("Unable to Reassign New Engineer !");
						}

					} else if (action.equalsIgnoreCase("dreReassign")) {

						response = edotWorkflow.completeReassign(edotRev);

						if (!response) {
							throw new Exception("Unable to Reassign New Sug Group Manager !");
						}
					}
				}

			} else if (closure.equalsIgnoreCase("Open") && disposition.equalsIgnoreCase("Approved")) {
				// Initiate Closure Workflow
				List<ItemRevision> techDataRevList = getSecondaryRevisions(edotRev, GETDesignReleaseConstants.Relation.desgnReleaseTechDataRel);
				ReleaseStatus[] relStatus = techDataRevList.get(0).get_release_status_list();
				if (relStatus != null && relStatus.length > 0 ){
					String workflowName = edotRev.get_item_id() + "-" + edotRev.get_current_name();
					response = createNewProcess(GETDesignReleaseConstants.Workflow.GETEDOTClose, edotRev.getUid(), workflowName);
					if (!response) {
						throw new Exception("Unable to Close EDOT !");
					}
				}
			}

		} catch (Exception e) {
			// e.printStackTrace();
			throw e;
		}

		return response;
	}
	
//	/****************************************************************************
//	 * Description: Method to handle the Workflow execution based on action performed on the UI
//	 * Returns: boolean
//	 * 
//	 ****************************************************************************/
//
//	public  boolean executePublishWorkFlow( String edotId, String subgroup,  GETUser getUser, String action) throws Exception{
//
//		boolean response = false;
//		ImanQuery query = null;
//		GroupMember engrManagerMember = null;
//		GroupMember dreMember = null;
//		GroupMember engineerMember = null;
//
//		try {
//
//			ItemRevision edotRev = getItemRevision( edotId,itemType );
//			DataManagementService.getService( session.getConnection() );
//
//			GETDesignReleaseWorkflow edotWorkflow = new GETDesignReleaseWorkflow( session.getConnection() );
//
//			query = findQuery(GETConstants.Query.queryGroupMember);
//
//			if ( !edotWorkflow.isReleased(edotRev) ){
//
//				//Get Group Name and Resource Id from EDOT Revision
//				String engrGroupName = getEdotGroupName(edotRev, GETDesignReleaseConstants.Properties.enggSubGroup);
//				String engrResource = getEdotResourceId(edotRev, GETDesignReleaseConstants.Properties.engrResource);	
//
//				if ( edotRev.get_process_stage_list().length == 0){
//
//					//Assign Group Manager Participant
//					engrManagerMember = getGroupMember(query, new String[] {GETConstants.Query.group,GETConstants.Query.role}, new String[] {engrGroupName+"*", GETDesignReleaseConstants.Role.strEngrManager});
//					if ( engrManagerMember != null ){
//						if ( isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engrManager) ){
//							response = removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engrManager);
//						}
//						response = assignParticipant(edotRev, engrManagerMember, GETDesignReleaseConstants.Participants.engrManager);
//					} else {
//						System.out.println("queriedObjects returned null");
//					}
//
//					//Assign Engineer Participant
//					if ( engrResource != null && engrResource.length() > 0 ){
//
//						engineerMember = getGroupMember(query, new String[] {GETConstants.Query.user, GETConstants.Query.group,GETConstants.Query.role}, 
//								new String[] {engrResource, engrGroupName+"*", GETDesignReleaseConstants.Role.strEngineer});
//						if ( engineerMember != null ){
//							if ( isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
//								response = removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engineer);
//							}
//							response = assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
//						} else {
//							System.out.println("queriedObjects returned null");
//						}
//					}
//
//					if ( response ) {
//						//Initiate Publish Workflow
//						String workflowName = edotRev.get_item_id()+"-"+ edotRev.get_current_name() ;
//						response = createNewProcess( GETDesignReleaseConstants.Workflow.GETEDOTPublish, edotRev.getUid(), workflowName );
//					}
//				} else {  //In Workflow
//
//					String sessionUserId = getUser.getUserID(); // Session User Id
//					String sessionRole = getUser.getRole();  //Session User Role
//					String sessionGroup = getUser.getuserGroup();
//
//					//Get DRE Member
//					if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)){
//						dreMember = getGroupMember(query, new String[] {GETConstants.Query.group,GETConstants.Query.role,GETConstants.Query.user},
//								new String[] {sessionGroup + "*", sessionRole, sessionUserId });
//					}
//
//					//Get Engr Manager Member
//					engrManagerMember = getGroupMember(query, new String[] {GETConstants.Query.group,GETConstants.Query.role}, new String[] {engrGroupName+"*", GETDesignReleaseConstants.Role.strEngrManager});
//
//					//Get Engineer Member
//					if ( engrResource != null && engrResource.length() > 0 ){
//						engineerMember = getGroupMember(query,  new String[] {GETConstants.Query.group, GETConstants.Query.role, GETConstants.Query.user},
//								new String[] {engrGroupName+"*", GETDesignReleaseConstants.Role.strEngineer, engrResource });
//					}
//
//
//					//For Engineering Manager Assigns Engineer Participant from EDOT Engr Resource
//					if( action.equalsIgnoreCase("assign") && sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager) )  //Engr Manager
//					{
//						if ( engrResource != null && engrResource.length() > 0 ){
//
//							if ( isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
//								response = removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engineer);
//							}
//							response = assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
//							if(response == true)
//							{
//								response = edotWorkflow.edotApproval( edotRev, engrManagerMember );
//							}
//							else
//							{
//								throw new Exception("Unable to assign Engineer !");
//							}
//
//						}
//
//					} else if( action.equalsIgnoreCase("accept") && sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer) )  {//Engineer accept 
//
//						response = edotWorkflow.edotApproval( edotRev, engineerMember );
//
//					} else if(action.equalsIgnoreCase("reject") ) {
//
//						if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)){
//							response = edotWorkflow.edotReject( edotRev, engrManagerMember );
//							if(response == true)
//							{
//								response = edotWorkflow.engrManagerRejectClosure( edotRev, false );
//							}
//							else
//							{
//								throw new Exception("Unable to Reject EDOT !");
//							}
//
//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
//							response = edotWorkflow.edotReject( edotRev, dreMember );
//						} 
//
//					} else if( (action.equalsIgnoreCase("eng_reject")) ||  (action.equalsIgnoreCase("dre_reject")) ) {
//
//						if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer)){
//							response = edotWorkflow.edotReject( edotRev, engineerMember );
//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
//							response = edotWorkflow.edotReject( edotRev, dreMember );
//						} 
//
//					} else if((action.equalsIgnoreCase("closure")) || (action.equalsIgnoreCase("dre_closure"))) { //Both Engr Manager & Engineer Closure
//
//						if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)){
//							response = edotWorkflow.edotReject( edotRev, engrManagerMember );
//							if(response == true)
//							{
//								response = edotWorkflow.engrManagerRejectClosure( edotRev, true );
//							}
//							else
//							{
//								throw new Exception("Unable to close EDOT !");
//							}
//
//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer)) {
//							response = edotWorkflow.edotReject( edotRev, engineerMember );
//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
//							response = edotWorkflow.edotApproval( edotRev, dreMember );
//						} 
//
//					} else if(action.equalsIgnoreCase("reassign"))  {//Engineer Reassign new Engr Resource
//
//						if ( isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
//							response = reassignParticipant(edotRev, GETDesignReleaseConstants.Role.strEngineer, engineerMember, GETDesignReleaseConstants.Participants.engineer);
//						} else {
//							response = assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
//						}
//
//						if(response == true)
//						{
//							response = edotWorkflow.deligateEngineer( edotRev, engineerMember );
//						} else {
//							throw new Exception("Unable to Reassign New Engineer !");
//						}
//
//					}
//					else if(action.equalsIgnoreCase("dreReassign"))  {
//
//						//Reassign new Engr Manager
//						if ( isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engrManager) ){
//							response = reassignParticipant(edotRev, GETDesignReleaseConstants.Role.strEngrManager, engrManagerMember, GETDesignReleaseConstants.Participants.engrManager);
//						} else {
//							response = assignParticipant(edotRev, engrManagerMember, GETDesignReleaseConstants.Participants.engrManager);
//						}
//
//						if ( engrResource != null && engrResource.length() > 0 ){
//
//							//Assign Engineer Participant
//							engineerMember = getGroupMember(query,  new String[] {GETConstants.Query.group, GETConstants.Query.role, GETConstants.Query.user},
//									new String[] {engrGroupName+"*", GETDesignReleaseConstants.Role.strEngineer, engrResource });
//
//							if ( engineerMember != null ){
//								if ( isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
//									response = removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engineer);
//								}
//								response = assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
//							}
//						}
//
//						if(response == true)
//						{
//							response = edotWorkflow.completeReassign(edotRev);
//						} else {
//							throw new Exception("Unable to Reassign New Sug Group Manager !");
//						}
//					}
//				}
//			}
//			else
//			{
//				//Initiate Publish Workflow
//				String workflowName = edotRev.get_item_id()+"-"+ edotRev.get_current_name() ;
//				response = createNewProcess( GETDesignReleaseConstants.Workflow.GETEDOTClosure, edotRev.getUid(), workflowName );
//				//				throw new Exception("The EDOT is already released.");
//			}
//
//		} catch (Exception e) {
//			//e.printStackTrace();
//			throw e;
//		}
//
//		return response;
//	}
	
	
	public boolean assignParticipantResource(ItemRevision edotRev, GroupMember groupMember, String participantType ) throws Exception
	{

		boolean isParticipantUpdated = false;

		try {
			RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
			typeFilter.relationTypeName = "HasParticipant";

			ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
			relationPref.expItemRev = false;
			relationPref.returnRelations = false;
			relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );		     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(relationResp.serviceData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
								if ( participant != null ){
									if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){  //GET6SubgroupMgr, Requestor
										GroupMember participantMember = (GroupMember) participant.get_assignee();
										ReassignParticipantInfo reassignParticipantInfo = new ReassignParticipantInfo();
										reassignParticipantInfo.allParticipantTypes = false;
										reassignParticipantInfo.clientId = UUID.randomUUID().toString();
										reassignParticipantInfo.participantTypes = new String[]{ participantType };
										reassignParticipantInfo.itemRevs = new ItemRevision[]{edotRev};
										reassignParticipantInfo.fromAssignee = participantMember;
										reassignParticipantInfo.toAssignee = groupMember;
										ReassignParticipantResponse reassignResp = dmService.reassignParticipants( new ReassignParticipantInfo[]{ reassignParticipantInfo } );
										if(!GETOnTrackCommonSoaOperations.ServiceDataError(reassignResp.serviceData)){
											isParticipantUpdated = true;
											break;
										}
										else
										{
											throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(reassignResp.serviceData));
										}
									}
								}
							}
						}
					}
				}
				
				if ( isParticipantUpdated == false ){
					
					AddParticipantInfo addPartcipantInfo = new AddParticipantInfo();
			
					ParticipantInfo partcipantInfo = new ParticipantInfo();
					partcipantInfo.assignee = groupMember;
					partcipantInfo.participantType = participantType;
					partcipantInfo.clientId = UUID.randomUUID().toString();;
			
					ParticipantInfo[] partipantsInfo = new ParticipantInfo[]{partcipantInfo};
					addPartcipantInfo.itemRev = edotRev;
					addPartcipantInfo.participantInfo = partipantsInfo;
			
					AddParticipantOutput participantOutput = dmService.addParticipants(new AddParticipantInfo[]{ addPartcipantInfo });
					ServiceData sData = participantOutput.serviceData;
					if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
						isParticipantUpdated = true;
					}
					else
					{
						throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
					}
				}
			}

		} catch (NotLoadedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			throw e;
		}
		return isParticipantUpdated;
	}


	public boolean assignParticipant( ItemRevision rev, GroupMember groupMember, String participantType ) throws Exception
	{
		boolean isParticipantAdded = false;

		try
		{

			AddParticipantInfo addPartcipantInfo = new AddParticipantInfo();

			ParticipantInfo partcipantInfo = new ParticipantInfo();
			partcipantInfo.assignee = groupMember;
			partcipantInfo.participantType = participantType;
			partcipantInfo.clientId = UUID.randomUUID().toString();;

			ParticipantInfo[] partipantsInfo = new ParticipantInfo[]{partcipantInfo};
			addPartcipantInfo.itemRev = rev;
			addPartcipantInfo.participantInfo = partipantsInfo;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			AddParticipantOutput participantOutput = dmService.addParticipants(new AddParticipantInfo[]{ addPartcipantInfo });
			ServiceData sData = participantOutput.serviceData;
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				isParticipantAdded = true;
			}
			else
			{
				throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
			}

		}
		catch(Exception e)
		{
			e.printStackTrace();
			throw e;
		}

		return isParticipantAdded;
	}

	public boolean isParticipantAssigned( ItemRevision edotRev, String participantType )
	{
		boolean isExist = false;
		ServiceData sData = null;

		try {
			RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
			typeFilter.relationTypeName = "HasParticipant";

			ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
			relationPref.expItemRev = false;
			relationPref.returnRelations = false;
			relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );
			sData = relationResp.serviceData;				     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
								if ( participant != null){
									if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
										isExist = true;
										break;
									}
								}
							}
						}
					}
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return isExist;
	}


	public Participant getParticipant( ItemRevision edotRev, String participantType )
	{
		Participant member = null;
		ServiceData sData = null;

		try {
			RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
			typeFilter.relationTypeName = "HasParticipant";

			ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
			relationPref.expItemRev = false;
			relationPref.returnRelations = false;
			relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );
			sData = relationResp.serviceData;				     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
								if ( participant != null){
									if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
										member = participant;
										break;
									}
								}
							}
						}
					}
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return member;
	}


	public boolean removeParticipant( ItemRevision edotRev, String participantType )
	{
		boolean isCompleted = false;
		ServiceData sData = null;

		try {
			RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
			typeFilter.relationTypeName = "HasParticipant";

			ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
			relationPref.expItemRev = false;
			relationPref.returnRelations = false;
			relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );
			sData = relationResp.serviceData;				     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
								if ( participant != null){
									if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
										Participants dmParticipant = new Participants();
										dmParticipant.itemRev = edotRev;
										dmParticipant.participant = new Participant[]{ participant };
										sData = dmService.removeParticipants( new Participants[]{ dmParticipant });
										if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
											System.out.println("Participant Removed");
											isCompleted = true;
										}
									}
								}
							}
						}
					}
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return isCompleted;
	}


	public boolean reassignParticipant(ItemRevision edotRev, String roleName, GroupMember groupMember, String participantType ) throws Exception
	{

		boolean isParticipantUpdated = false;

		try {
			RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
			typeFilter.relationTypeName = "HasParticipant";

			ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
			relationPref.expItemRev = false;
			relationPref.returnRelations = false;
			relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );		     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(relationResp.serviceData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
								if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
									GroupMember participantMember = (GroupMember) participant.get_assignee();
									ReassignParticipantInfo reassignParticipantInfo = new ReassignParticipantInfo();

									reassignParticipantInfo.allParticipantTypes = false;
									reassignParticipantInfo.clientId = UUID.randomUUID().toString();
									reassignParticipantInfo.participantTypes = new String[]{ participantType };
									reassignParticipantInfo.itemRevs = new ItemRevision[]{edotRev};
									reassignParticipantInfo.fromAssignee = participantMember;
									reassignParticipantInfo.toAssignee = groupMember;

									ReassignParticipantResponse reassignResp = dmService.reassignParticipants( new ReassignParticipantInfo[]{ reassignParticipantInfo } );

									if(!GETOnTrackCommonSoaOperations.ServiceDataError(reassignResp.serviceData)){
										isParticipantUpdated = true;
										//System.out.println("Participant Removed");
									}
									else
									{
										throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(reassignResp.serviceData));
									}
								}

							}
						}
					}
				}
			}

		} catch (NotLoadedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			throw e;
		}
		return isParticipantUpdated;
	}


	//	/****************************************************************************
	//	 * Description: Method to handle the Workflow execution based on action performed on the UI
	//	 * Returns: boolean
	//	 * 
	//	 ****************************************************************************/
	//
	//	public  boolean executePublishWorkFlow( String edotId, String subgroup,  GETUser getUser, String action) throws Exception{
	//
	//		boolean response = false;
	//		ModelObject[] moObjects = null;
	//		GroupMember engrManagerMember = null;
	//		GroupMember dreMember = null;
	//		GroupMember engineerMember = null;
	//		GETQuery.QueriedObjects queriedObjects = null;
	//
	//		try {
	//			ItemRevision edotRev = getItemRevision( edotId,itemType );
	//			DataManagementService.getService( session.getConnection() );
	//
	//			GETDesignReleaseWorkflow getEngManagerWF = new GETDesignReleaseWorkflow( session.getConnection() );
	//			GETQuery queryService = GETQuery.getInstance(session.getConnection());
	//
	//			if ( !getEngManagerWF.isReleased(edotRev) ){
	//
	//				//Get Group Name and Resource Id from EDOT Revision
	//				String engrGroupName = getEdotGroupName(edotRev, GETDesignReleaseConstants.Properties.enggSubGroup);
	//				String engrResource = getEdotResourceId(edotRev, GETDesignReleaseConstants.Properties.engResource);	
	//
	//				if ( edotRev.get_process_stage_list().length == 0){
	//
	//					//Assign Group Manager Participant
	//					queriedObjects = queryService.getQueriedObjs(GETConstants.Query.queryGroupMember, new String[] {GETConstants.Query.group,GETConstants.Query.role}, new String[] {engrGroupName+"*", GETDesignReleaseConstants.Role.strEngrManager});
	//					if ( queriedObjects != null ) {
	//						moObjects = queriedObjects.loadedObjects;
	//						if ( moObjects[0] instanceof GroupMember ){
	//							engrManagerMember = (GroupMember) moObjects[0];
	//
	//							if ( getEngManagerWF.isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engrManager) ){
	//								response = getEngManagerWF.removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engrManager);
	//							}
	//							response = getEngManagerWF.assignParticipant(edotRev, engrManagerMember, GETDesignReleaseConstants.Participants.engrManager);
	//						}
	//						else
	//						{
	//							System.out.println("queriedObjects returned null");
	//						}
	//					}
	//
	//					if ( engrResource != null && engrResource.length() > 0 ){
	//
	//						//Assign Engineer Participant
	//						queriedObjects = queryService.getQueriedObjs(GETConstants.Query.queryGroupMember, new String[] {GETConstants.Query.user, GETConstants.Query.group,GETConstants.Query.role}, new String[] {engrResource, engrGroupName+"*", GETDesignReleaseConstants.Role.strEngineer});
	//						if ( queriedObjects != null )
	//						{
	//							moObjects = queriedObjects.loadedObjects;
	//							if ( moObjects[0] instanceof GroupMember ){
	//								engineerMember = (GroupMember) moObjects[0];
	//
	//								if ( getEngManagerWF.isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
	//									response = getEngManagerWF.removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engineer);
	//								}
	//								response = getEngManagerWF.assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
	//							}
	//						}
	//					}
	//
	//					if ( response ) {
	//						//Initiate Publish Workflow
	//						response = createNewProcess( processTemplate, edotRev.getUid(), edotRev.get_item_id()+"-"+ edotRev.get_current_name());
	//					}
	//				} else {  //In Workflow
	//
	//					String sessionUserId = getUser.getUserID(); // Session User Id
	//					String sessionRole = getUser.getRole();  //Session User Role
	//					String sessionGroup = getUser.getuserGroup();
	//
	//					if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)){
	//
	//						//Get DRE Member
	//						queriedObjects = queryService.getQueriedObjs(GETConstants.Query.queryGroupMember, new String[] {GETConstants.Query.group,GETConstants.Query.role,GETConstants.Query.user},
	//								new String[] {sessionGroup + "*", sessionRole, sessionUserId });
	//						if ( queriedObjects != null ) {
	//							moObjects = queriedObjects.loadedObjects;
	//							if ( moObjects[0] instanceof GroupMember ){
	//								dreMember = (GroupMember) moObjects[0];
	//							}
	//						}
	//					}
	//
	//					//Get Engr Manager Member
	//					queriedObjects = queryService.getQueriedObjs(GETConstants.Query.queryGroupMember, new String[] {GETConstants.Query.group,GETConstants.Query.role}, new String[] {engrGroupName+"*", GETDesignReleaseConstants.Role.strEngrManager});
	//					if ( queriedObjects != null ) {
	//						moObjects = queriedObjects.loadedObjects;
	//						if ( moObjects[0] instanceof GroupMember ){
	//							engrManagerMember = (GroupMember) moObjects[0];
	//						}
	//					}
	//
	//					if ( engrResource != null && engrResource.length() > 0 ){
	//						//Get Engineer Member
	//						queriedObjects = queryService.getQueriedObjs(GETConstants.Query.queryGroupMember, new String[] {GETConstants.Query.group,GETConstants.Query.role,GETConstants.Query.user},
	//								new String[] {engrGroupName+"*", GETDesignReleaseConstants.Role.strEngineer, engrResource });
	//
	//						if ( queriedObjects != null )
	//						{
	//							moObjects = queriedObjects.loadedObjects;
	//							if ( moObjects[0] instanceof GroupMember ){
	//								engineerMember = (GroupMember) moObjects[0];
	//							}
	//						}
	//					}
	//
	//
	//					//For Engineering Manager Assigns Engineer Participant from EDOT Engr Resource
	//					if( action.equalsIgnoreCase("assign") && sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager) )  //Engr Manager
	//					{
	//
	//						if ( engrResource != null && engrResource.length() > 0 ){
	//
	//							if ( getEngManagerWF.isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
	//								response = getEngManagerWF.removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engineer);
	//							}
	//							response = getEngManagerWF.assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
	//							if(response == true)
	//							{
	//								response = getEngManagerWF.edotApproval( edotRev, engrManagerMember );
	//							}
	//							else
	//							{
	//								throw new Exception("Unable to assign Engineer !");
	//							}
	//
	//						}
	//
	//					} else if( action.equalsIgnoreCase("accept") && sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer) )  {//Engineer accept 
	//
	//						response = getEngManagerWF.edotApproval( edotRev, engineerMember );
	//
	//					} else if(action.equalsIgnoreCase("reject") ) {
	//
	//						if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)){
	//							response = getEngManagerWF.edotReject( edotRev, engrManagerMember );
	//							if(response == true)
	//							{
	//								response = getEngManagerWF.engrManagerRejectClosure( edotRev, false );
	//							}
	//							else
	//							{
	//								throw new Exception("Unable to Reject EDOT !");
	//							}
	//
	//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
	//							response = getEngManagerWF.edotReject( edotRev, dreMember );
	//						} 
	//
	//					} else if( (action.equalsIgnoreCase("eng_reject")) ||  (action.equalsIgnoreCase("dre_reject")) ) {
	//
	//						if (sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer)){
	//							response = getEngManagerWF.edotReject( edotRev, engineerMember );
	//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
	//							response = getEngManagerWF.edotReject( edotRev, dreMember );
	//						} 
	//
	//					} else if((action.equalsIgnoreCase("closure")) || (action.equalsIgnoreCase("dre_closure"))) { //Both Engr Manager & Engineer Closure
	//
	//						if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager)){
	//							response = getEngManagerWF.edotReject( edotRev, engrManagerMember );
	//							if(response == true)
	//							{
	//								response = getEngManagerWF.engrManagerRejectClosure( edotRev, true );
	//							}
	//							else
	//							{
	//								throw new Exception("Unable to close EDOT !");
	//							}
	//
	//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer)) {
	//							response = getEngManagerWF.edotReject( edotRev, engineerMember );
	//						} else if ( sessionRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE)) {
	//							response = getEngManagerWF.edotApproval( edotRev, dreMember );
	//						} 
	//
	//					} else if(action.equalsIgnoreCase("reassign"))  {//Engineer Reassign new Engr Resource
	//
	//						if ( getEngManagerWF.isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
	//							response = getEngManagerWF.reassignParticipant(edotRev, GETDesignReleaseConstants.Role.strEngineer, engineerMember, GETDesignReleaseConstants.Participants.engineer);
	//						} else {
	//							response = getEngManagerWF.assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
	//						}
	//
	//						if(response == true)
	//						{
	//							response = getEngManagerWF.deligateEngineer( edotRev, engineerMember );
	//						}
	//						else
	//						{
	//							throw new Exception("Unable to Reassign New Engineer !");
	//						}
	//
	//					}
	//					else if(action.equalsIgnoreCase("dreReassign"))  {
	//
	//						//Reassign new Engr Manager
	//						if ( getEngManagerWF.isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engrManager) ){
	//							response = getEngManagerWF.reassignParticipant(edotRev, GETDesignReleaseConstants.Role.strEngrManager, engrManagerMember, GETDesignReleaseConstants.Participants.engrManager);
	//						} else {
	//							response = getEngManagerWF.assignParticipant(edotRev, engrManagerMember, GETDesignReleaseConstants.Participants.engrManager);
	//						}
	//
	//						if ( engrResource != null && engrResource.length() > 0 ){
	//
	//							//Assign Engineer Participant
	//							queriedObjects = queryService.getQueriedObjs(GETConstants.Query.queryGroupMember, new String[] {GETConstants.Query.user, GETConstants.Query.group,GETConstants.Query.role}, new String[] {engrResource, engrGroupName+"*", GETDesignReleaseConstants.Role.strEngineer});
	//							if ( queriedObjects != null )
	//							{
	//								moObjects = queriedObjects.loadedObjects;
	//								if ( moObjects[0] instanceof GroupMember ){
	//									engineerMember = (GroupMember) moObjects[0];
	//
	//									if ( getEngManagerWF.isParticipantAssigned(edotRev, GETDesignReleaseConstants.Participants.engineer) ){
	//										response = getEngManagerWF.removeParticipant(edotRev, GETDesignReleaseConstants.Participants.engineer);
	//									}
	//									response = getEngManagerWF.assignParticipant(edotRev, engineerMember, GETDesignReleaseConstants.Participants.engineer);
	//								}
	//							}
	//						}
	//						
	//						if(response == true)
	//						{
	//							response = getEngManagerWF.completeReassign(edotRev);
	//						}
	//						else
	//						{
	//							throw new Exception("Unable to Reassign New Sug Group Manager !");
	//						}
	//
	//					}
	//
	//				}
	//			}
	//			else
	//			{
	//				throw new Exception("The EDOT is already released.");
	//			}
	//
	//		} catch (Exception e) {
	//			//e.printStackTrace();
	//			throw e;
	//		}
	//
	//		return response;
	//	}

	/****************************************************************************
	 * Description: Method to update Array Properties
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public boolean updateArrayProperties( ItemRevision edotObj, String propertyName, String propertyValue )  throws Exception {

		//String lastComment = null;
		boolean isUpdated = true;
		String errorMessage  = null;
		try
		{

			Map<String, DataManagementService.VecStruct> properties = new HashMap<String, DataManagementService.VecStruct>();
			new  DataManagementService.VecStruct();


			//Get array Property Values
			Property prop = edotObj.getPropertyObject( propertyName );
			String[] propValues = prop.getStringArrayValue();
			propValues = addNewValue( propValues, propertyValue );

			DataManagementService.VecStruct propertyValues = new DataManagementService.VecStruct();
			// propertyValues.stringVec = new String[]{lastComment};
			propertyValues.stringVec = propValues;
			properties.put( propertyName, propertyValues );

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ServiceData sData = dmService.setProperties( new ModelObject[]{ edotObj }, properties);
			errorMessage = getErrorFromServiceData(sData);


		}
		catch (Exception e)
		{
			isUpdated = false;
			throw new Exception("Error in updating comments :" + e);
		}
		if (errorMessage != null && !errorMessage.isEmpty())
		{
			isUpdated = false;
			throw new Exception(errorMessage);
		}
		return isUpdated;
	}

	/****************************************************************************
	 * Description: Method to get Error From ServiceData
	 * Returns: String
	 * 
	 ****************************************************************************/
	public static String getErrorFromServiceData(ServiceData serviceData)
	{
		String errorMessage = null;
		if (serviceData != null && serviceData.sizeOfPartialErrors() > 0)
		{
			StringBuffer messageBuffer = new StringBuffer();
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


	/****************************************************************************
	 * Description: Method to Add New Value to existing Array
	 * Returns: String[]
	 * 
	 ****************************************************************************/
	private String[] addNewValue(String[] values, String newValue)  throws Exception {
		values  = Arrays.copyOf(values, values.length + 1);
		values[values.length - 1] = newValue;
		return values;
	}



	/****************************************************************************
	 * Description: Method to Create Publish Workflow instance
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public  boolean createNewProcess( String Template, String edotUid, String workflowName) throws Exception
	{
		ContextData contextData = new ContextData();
		String observerKey = "";
		String name = workflowName;
		String subject = "createInstance";
		String description = workflowName;

		contextData.processTemplate = Template;
		contextData.subscribeToEvents = false;
		contextData.subscriptionEventCount = 0;
		contextData.attachmentCount = 1;
		contextData.attachments = new String[]{ edotUid };
		contextData.attachmentTypes = new int[]{EPM_attachement.target.value() }; 

		WorkflowService wfService = WorkflowService.getService( session.getConnection() );

		InstanceInfo instanceInfo = wfService.createInstance(true,observerKey, name, subject, description, contextData);
		ServiceData sData = instanceInfo.serviceData;
		if(GETOnTrackCommonSoaOperations.ServiceDataError(sData) == false)
		{		
			return true;
		}
		else if(sData.sizeOfPartialErrors() > 0)
		{
			for(int i = 0; i < sData.sizeOfPartialErrors(); i++)
			{
				int code =sData.getPartialError(i).getErrorValues()[0].getCode();
					System.out.println(code);
					if(code == 515155 || code == 710041)
					{
						return true;	
					}
			}
		}

		return false;
	}



	public enum EPM_attachement
	{
		target			(1),
		reference		(3),
		signoff 		(4),
		release_status	(5),
		comment 		(6),
		instruction		(7),
		interprocess	(8),
		project_task	(9);

		private final int value;

		EPM_attachement(int value) { this.value = value; }

		public int value() { return value; }
	}

	/****************************************************************************
	 * Description: Method to logout of Teamcenter
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public void logout()
	{
		if ( null != session ) 
		{
			session.logout();
		}
	}

	/*public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}*/
	/****************************************************************************
	 * Description: Method to get Groups List
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public ArrayList<String> getGroupsList_old( ) throws Exception
	{
		ArrayList<String> groupList = new ArrayList<String>();
		Group group = null;
		ModelObject[] moObjects = null;
		try 
		{

			GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
			GETQuery.QueriedObjects queriedObjects;
			GETDataManagement.getDMService(session.getConnection());

			queriedObjects = queryService1.getQueriedObjs(GETConstants.Query.grpByNameQuery, new String[] { GETConstants.Query.strName },
					new String[] { "38*" });
			if ( queriedObjects != null )
			{
				moObjects = queriedObjects.loadedObjects;
			}
			for( ModelObject moObject:  moObjects)
			{
				if ( moObject instanceof Group )
				{
					group = (Group) moObject;
					groupList.add( group.get_name().trim()) ;
				}
			}
			if ( groupList.size() > 0 )
			{
				groupList.add("NWR");
			}
		}
		catch (Exception e) 
		{
			//e.printStackTrace();
			throw e;
		}
		return groupList;
	}


	/****************************************************************************
	 * Description: Method to get Groups List
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public ArrayList<String> getGroupsList( ) throws Exception
	{
		ArrayList<String> groupList = new ArrayList<String>();
		try 
		{
			ImanQuery query = findQuery(GETConstants.Query.grpByNameQuery);

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = new String[] { GETConstants.Query.strName };
			qryInput.values = new String[] {  "38*" };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof Group ){
							Group group = (Group) mObj;
							groupList.add( group.get_name()) ;
						}
					}
				}
			}
		}
		catch (Exception e) 
		{
			//e.printStackTrace();
			throw e;
		}
		return groupList;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public ArrayList<String> getUserList( String groupName, String role ) throws Exception
	{
		ArrayList<String> userList = new ArrayList<String>();

		try {

			ImanQuery query = findQuery(GETConstants.Query.queryGroupMember);

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = new String[] { GETConstants.Query.group,GETConstants.Query.role };
			qryInput.values = new String[] {groupName + "*", role };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof GroupMember ){
							GroupMember member = (GroupMember) mObj;
							User user = (User) member.get_user();
							//								dmService.getProperties(new ModelObject[]{user}, new String[]{GETConstants.BusinessObjects.Properties.objectString});
							userList.add( user.get_object_string()) ;
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			//e.printStackTrace();
			throw e;
		}

		return userList;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public ArrayList<String> getOrgProjectList( String[] entries, String[] values ) throws Exception
	{
		ArrayList<String> tcProjectList = new ArrayList<String>();

		try {

			ImanQuery query = findQuery(GETConstants.Query.queryTcProject);

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = entries;
			qryInput.values = values;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof TC_Project ){
							TC_Project project = (TC_Project) mObj;
							tcProjectList.add( project.get_object_string()) ;
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			//e.printStackTrace();
			throw e;
		}

		return tcProjectList;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public TC_Project getOrgProject( String orgProjectId ) throws Exception
	{
		TC_Project orgProject = null;

		try {
			/*if ( orgProjectId.startsWith("TSE")){
				orgProjectId = (orgProjectId.split("-")[0]).trim();
				
			}*/
			orgProjectId = (orgProjectId.split("-")[0]).trim();
			ImanQuery query = findQuery(GETConstants.Query.queryTcProject);

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = new String[]{ "Project ID" };
			qryInput.values = new String[]{ orgProjectId };

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof TC_Project ){
							orgProject = (TC_Project) mObj;
							break;
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			//e.printStackTrace();
			throw e;
		}

		return orgProject;
	}


//	/****************************************************************************
//	 * Description: Method to get user list
//	 * Returns: ArrayList
//	 * 
//	 ****************************************************************************/
//	public ArrayList<String> getOrgProjectResourceList( String[] entries, String[] values ) throws Exception
//	{
//		ArrayList<String> userList = new ArrayList<String>();
//
//		try {
//
//			ImanQuery query = findQuery(GETConstants.Query.queryProjectMembres);
//
//			QueryInput qryInput = new QueryInput();
//			qryInput.clientId = UUID.randomUUID().toString();
//			qryInput.limitList = new ModelObject[0];
//			qryInput.maxNumToReturn = 0;
//			qryInput.query = query;
//			qryInput.resultsType = 0;
//			qryInput.entries = entries;
//			qryInput.values = values;
//
//			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
//			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );
//
//			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });
//
//			QueryResults[] results =  qryResp.arrayOfResults;
//			if ( results.length > 0 ){
//				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
//				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
//					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
//						ModelObject mObj = sData.getPlainObject(jnx);
//						if ( mObj instanceof GroupMember ){
//							GroupMember member = (GroupMember) mObj;
//							User user = (User) member.get_user();
//							String userName = user.get_object_string();
//							if ( !userList.contains(userName)){
//								userList.add( userName) ;
//							}
//						}
//					}
//				}
//			}
//		} 
//		catch (Exception e)
//		{
//			throw e;
//		}
//
//		return userList;
//	}
	
	
	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public ArrayList<String> getOrgProjectResourceList( String ProjectID, String role ) throws Exception
	{
		ArrayList<String> userList = new ArrayList<String>();

		try {
		
			ProjectClientId projClientId = new ProjectClientId();
			projClientId.clientId = UUID.randomUUID().toString();
			if(null != ProjectID && ProjectID.length() > 0)
			{
			projClientId.tcProject = getOrgProject(ProjectID);	
			ProjectLevelSecurityService projSecurityService = ProjectLevelSecurityService.getService( session.getConnection() );
			ProjectTeamsResponse teamResp = projSecurityService.getProjectTeams(new ProjectClientId[]{ projClientId });
			if (!GETOnTrackCommonSoaOperations.ServiceDataError(teamResp.serviceData)) {
				DataManagementService dmService = DataManagementService.getService( session.getConnection() );
				ProjectTeamData[] projectTeamData = teamResp.projectTeams;
				for (ProjectTeamData teamData : projectTeamData) {
					ModelObject[] nonPrivMembers = teamData.regularMembers;
					for (ModelObject modelObj : nonPrivMembers) {
						if ( modelObj instanceof GroupMember){
							GroupMember member = (GroupMember)modelObj;
							Role memberRole = member.get_role();
							if ( memberRole.get_role_name().equalsIgnoreCase(role)){
								String userName = ((User) member.get_user()).get_object_string();
								if ( !userList.contains(userName) ){
									userList.add( userName) ;
								}
							}
						}
					}
				}
			}
		}
		} 
		catch (Exception e)
		{
			//e.printStackTrace();
			throw e;
		}
		return userList;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public Group getOrgProjectDefaultGroup( String[] entries, String[] values ) throws Exception
	{
		Group defaultGroup = null;

		try {

			ImanQuery query = findQuery(GETConstants.Query.queryProjectMembres);

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = entries;
			qryInput.values = values;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof GroupMember ){
							GroupMember member = (GroupMember) mObj;
							defaultGroup = (Group) member.get_group();
							break;
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			throw e;
		}

		return defaultGroup;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public GroupMember getOrgProjectMember( String[] entries, String[] values ) throws Exception
	{
		GroupMember projectMember = null;

		try {

			ImanQuery query = findQuery(GETConstants.Query.queryProjectMembres);

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = entries;
			qryInput.values = values;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof GroupMember ){
							projectMember = (GroupMember) mObj;
							break;
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			throw e;
		}

		return projectMember;
	}


	/****************************************************************************
	 * Description: Method to get user list
	 * Returns: ArrayList
	 * 
	 ****************************************************************************/
	public GroupMember getGroupMember( ImanQuery query, String[] entries, String[] values ) throws Exception
	{
		GroupMember member = null;

		try {

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = entries;
			qryInput.values = values;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof GroupMember ){
							member = (GroupMember) mObj;
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			//e.printStackTrace();
			throw e;
		}

		return member;
	}


	//	/****************************************************************************
	//	 * Description: Method to get user list
	//	 * Returns: ArrayList
	//	 * 
	//	 ****************************************************************************/
	//	public ArrayList<String> getUserList( String GroupName, String role ) throws Exception
	//	{
	//		ArrayList<String> userList = new ArrayList<String>();
	//		GroupMember grpMember = null;
	//
	//		ModelObject[] moObjects = null;
	//
	//		GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
	//		GETQuery.QueriedObjects queriedObjects;
	//		GETDataManagement dmService = GETDataManagement.getDMService(session.getConnection());
	//
	//		try {
	//			queriedObjects = queryService1.getQueriedObjs( GETOnTrackConstants.Query.strgrpMemberQuery , new String[] { GETConstants.Query.group, GETConstants.Query.role },
	//					new String[] { (GroupName + "*"), role});
	//
	//			if ( queriedObjects != null )
	//			{
	//				moObjects = queriedObjects.loadedObjects;
	//
	//				for( ModelObject moObject:  moObjects)
	//				{
	//					if ( moObject instanceof GroupMember ){
	//						grpMember = (GroupMember) moObject;
	//						User user = (User) grpMember.get_user();
	//						dmService.getProperties(new ModelObject[]{user}, new String[]{"object_string"});
	//						userList.add( user.get_object_string()) ;
	//					}
	//				}
	//			}
	//		} 
	//		catch (Exception e)
	//		{
	//			//e.printStackTrace();
	//			throw e;
	//		}
	//
	//		return userList;
	//	}
	/****************************************************************************
	 * Description: Method to delete Selected EDOTs
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public boolean deleteSelectedEDOTs( String[] itemIdList ) throws Exception
	{
		boolean status = false;


		DataManagementService.getService( session.getConnection() );
		ModelObject[] moArray = itemToArrayModelObjects(itemIdList);
		if(moArray != null && moArray.length > 0)
		{
			for(ModelObject mo: moArray)
			{
				Item item = (Item) mo;
				ModelObject[] mObjs = item.get_revision_list();
				if ( mObjs.length > 0 )
				{
					status = getPrimaryObjectAndDeleteRelation(mObjs);
					if(status == true)
					{
						status = deleteObjects( new ModelObject[] { mo });
					}
					else
					{
						throw new Exception("Unable to delete attached relations.Can not delete EDOT.");
					}

				} 
			}
		}
		else
		{
			throw new Exception("Unable to get the model objects list .");
		}

		return status;
	}


	/****************************************************************************
	 * Description: Method to  get Primary Object UID
	 * Returns: String
	 * 
	 ****************************************************************************/
	public String getPrimaryObjectUID(ModelObject secondaryObject, String relation )
	{
		ServiceData sData = null;
		String uid = null;

		RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
		typeFilter.relationTypeName = relation;

		ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
		relationPref.expItemRev = false;
		relationPref.returnRelations = false;
		relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForSecondary( new ModelObject[]{ secondaryObject },relationPref );
		sData = relationResp.serviceData;				     
		if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
			for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
				for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
					for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
						if(tcRelation.otherSideObject instanceof ItemRevision) {
							uid = tcRelation.otherSideObject.getUid();
						}
					}
				}
			}
		}
		return uid;
	}

	/****************************************************************************
	 * Description: Method to  get Primary Object ID
	 * Returns: String
	 * @throws NotLoadedException 
	 * 
	 ****************************************************************************/
	public String getPrimaryObjectID(ModelObject secondaryObject, String relation ) throws NotLoadedException
	{
		ServiceData sData = null;
		String itemId = null;

		RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
		typeFilter.relationTypeName = relation;

		ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
		relationPref.expItemRev = false;
		relationPref.returnRelations = false;
		relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

		try {
			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForSecondary( new ModelObject[]{ secondaryObject },relationPref );
			sData = relationResp.serviceData;				     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof ItemRevision) {
								ItemRevision edotRev = (ItemRevision) tcRelation.otherSideObject;
								itemId = edotRev.get_item_id();
							}
						}
					}
				}
			}
		} catch (NotLoadedException e) {
			//e.printStackTrace();
			throw e;
		}
		return itemId;
	}

	/****************************************************************************
	 * Description: Method to  get Secondary Object ID UID
	 * Returns: String
	 * 
	 ****************************************************************************/
	public ArrayList<String> getSecondaryObjectsUID(ModelObject primaryObject, String relation ) throws Exception
	{
		ArrayList<String> secondaryObjsList = null;
		ServiceData sData = null;
		String uid = null;

		RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
		typeFilter.relationTypeName = relation;

		ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
		relationPref.expItemRev = false;
		relationPref.returnRelations = false;
		relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ primaryObject },relationPref );
		sData = relationResp.serviceData;				     
		if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
			secondaryObjsList = new ArrayList<String>();
			for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
				for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
					for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
						//if(tcRelation.otherSideObject instanceof ItemRevision) {   //GET6ECRRevision
						uid = tcRelation.otherSideObject.getUid();
						secondaryObjsList.add(uid);
						//}
					}
				}
			}
		}
		return secondaryObjsList;
	}

	/****************************************************************************
	 * Description: Method to  get Secondary Object ID
	 * Returns: String
	 * 
	 ****************************************************************************/

	public ArrayList<String> getSecondaryObjectsID(ModelObject primaryObject, String relation ) throws NotLoadedException
	{
		ArrayList<String> secondaryObjsList = null;

		RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
		typeFilter.otherSideObjectTypes = new String[]{GETDesignReleaseConstants.BuinessObjects.GETDsgnReleaseRevision,
				GETDesignReleaseConstants.BuinessObjects.GETEcnRev,
				GETDesignReleaseConstants.BuinessObjects.GETEcrRev};
		typeFilter.relationTypeName = relation;

		ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
		relationPref.expItemRev = false;
		relationPref.returnRelations = false;
		relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ primaryObject },relationPref );		     
		if(!GETOnTrackCommonSoaOperations.ServiceDataError(relationResp.serviceData)){
			secondaryObjsList = new ArrayList<String>();
			for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
				for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
					for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
						if(tcRelation.otherSideObject instanceof ItemRevision) {   //GET6ECRRevision
							ItemRevision itemRev = (ItemRevision) tcRelation.otherSideObject;
							secondaryObjsList.add(itemRev.get_item_id());
						}
					}
				}
			}
		}
		return secondaryObjsList;
	}
	
	
	/****************************************************************************
	 * Description: Method to  get Secondary Object ID
	 * Returns: String
	 * 
	 ****************************************************************************/

	public ItemRevision getTechnicalData(ModelObject edotRev, String relation ) throws NotLoadedException
	{
		ItemRevision technicalData = null;

		RelationAndTypesFilter typeFilter = new RelationAndTypesFilter();
		typeFilter.otherSideObjectTypes = new String[]{GETDesignReleaseConstants.BuinessObjects.GETDsgnReleaseRevision,
				GETDesignReleaseConstants.BuinessObjects.GETEcnRev,
				GETDesignReleaseConstants.BuinessObjects.GETEcrRev};
		typeFilter.relationTypeName = relation;

		ExpandGRMRelationsPref2 relationPref = new ExpandGRMRelationsPref2();
		relationPref.expItemRev = false;
		relationPref.returnRelations = false;
		relationPref.info = new RelationAndTypesFilter[]{ typeFilter };

		DataManagementService dmService = DataManagementService.getService( session.getConnection() );
		ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );		     
		if(!GETOnTrackCommonSoaOperations.ServiceDataError(relationResp.serviceData)){
			for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
				for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
					for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
						if(tcRelation.otherSideObject instanceof ItemRevision) {   //GET6ECRRevision
							technicalData = (ItemRevision) tcRelation.otherSideObject;
							break;
						}
					}
				}
			}
		}
		return technicalData;
	}
	

	/****************************************************************************
	 * Description: Method to ge tPrimaryObjec tAnd Delete Relation
	 * Returns: void
	 * 
	 ****************************************************************************/

	public boolean getPrimaryObjectAndDeleteRelation( ModelObject[] secObject) throws Exception
	{
		DataManagementService dmService = DataManagementService.getService( session.getConnection() );

		ExpandGRMRelationsPref2 relPref = new ExpandGRMRelationsPref2();
		boolean isRelDeleted = false;


		RelationAndTypesFilter relType = new RelationAndTypesFilter(); 
		relType.otherSideObjectTypes = new String[] {GETDesignReleaseConstants.BuinessObjects.GETDsgnReleasePlan};
		relType.relationTypeName = GETDesignReleaseConstants.Relation.desgnReleaseRelation;
		relPref.expItemRev = false;
		relPref.info = new RelationAndTypesFilter[] { relType };
		relPref.returnRelations = true ;
		ExpandGRMRelationsResponse2 grmResponse = dmService.expandGRMRelationsForSecondary(secObject, relPref);
		if (!GETOnTrackCommonSoaOperations.ServiceDataError(grmResponse.serviceData)) {
			for(ExpandGRMRelationsOutput2 output: grmResponse.output)
			{
				for(ExpandGRMRelationsData2 primaryobj: output.relationshipData)
				{
					for(ExpandGRMRelationship relationShip: primaryobj.relationshipObjects)
					{
						ModelObject primaryMO = relationShip.otherSideObject;

						Relationship relation = new Relationship();
						relation.clientId = "ID:" + relation.hashCode();
						relation.primaryObject = primaryMO;
						relation.secondaryObject = secObject[0];
						relation.relationType = GETDesignReleaseConstants.Relation.desgnReleaseRelation;
						ServiceData sd = dmService.deleteRelations(new Relationship[]{relation});
						if (GETOnTrackCommonSoaOperations.ServiceDataError(sd)) {
							throw new Exception("Unable to delete relation.");
						}
						else
						{
							isRelDeleted = true;
						}
					}
				}
			}

		}
		else
		{
			throw new Exception("Unable to get the secondary objects for edot.");
		}

		return isRelDeleted;
	}
	/****************************************************************************
	 * Description: Method to delete objects
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public boolean deleteObjects( ModelObject[] modelObjects ) throws Exception
	{
		boolean status = false;

		try {
			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			dmService.deleteObjects( modelObjects );
			status = true;

		} catch (Exception e) {
			// TODO Auto-generated catch block
			status = true;
			System.out.println("Some Exception occured during delete-->"+e.getMessage());

		}

		return status;
	}

	/****************************************************************************
	 * Description: Method to convert items to model object array
	 * Returns: ModelObject[]
	 * 
	 ****************************************************************************/
	public ModelObject[] itemToArrayModelObjects(String[] propValue)
			throws Exception {

		ModelObject[] moObjects = null;

		String propValues = "";
		try {
			for (String strvalue : propValue) {
				if(propValue.length == 1)
				{
					propValues = strvalue;
				}
				else
				{
					propValues = propValues + strvalue + ";";
				}

			}
			if(propValue.length != 1)
			{
				propValues = propValues.substring(0, propValues.length()-1);
			}

			GETQuery queryService1 = GETQuery.getInstance(session.getConnection());
			GETQuery.QueriedObjects queriedObjects = queryService1.getQueriedObjs(
					GETConstants.Query.strItemIDName,
					new String[] { GETConstants.Query.strItemIDName },
					new String[] { propValues });
			if (queriedObjects != null) {
				moObjects = queriedObjects.loadedObjects;
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			throw e;
		}

		return moObjects;
	}


	/****************************************************************************
	 * Description: Method to Get Session Group And Role
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public void getSessionGroupAndRole(GETUser getUser) throws Exception
	{
		GroupMember groupMember = null;
		try {
			SessionService sessionService = SessionService.getService(session.getConnection());
			DataManagementService.getService( session.getConnection() );

			GetSessionGroupMemberResponse sessionMemberResp = sessionService.getSessionGroupMember();
			ServiceData sData = sessionMemberResp.serviceData;

			if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
				groupMember = sessionMemberResp.groupMember;
				User user = (User)groupMember.get_the_user();
				Group group = (Group)groupMember.get_the_group();
				Role role = (Role)groupMember.get_the_role(); 

				getUser.setUserID(user.get_user_id());
				getUser.setUserName(user.get_user_name());// .getUser.
				getUser.setuserGroup(group.get_name());
				getUser.setRole(role.get_role_name());

			}
		} catch (ServiceException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			throw e;
		} catch (NotLoadedException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			throw e;
		}
	}	
	/****************************************************************************
	 * Description: Method to Get user Group And Role
	 * Returns: boolean
	 * 
	 ****************************************************************************/

	public Map<String, List<String>> getUserGroupAndRole(String UserId) throws Exception{//change in this method for loading the group and Role selection 
		GETQuery queryService = GETQuery.getInstance(session.getConnection());
		GETDataManagement dataMgmt = GETDataManagement.getDMService(session.getConnection());

		String roleName = null;
		String groupName = null;

		Map<String, List<String>> groupRole = new HashMap<String, List<String>>();
		ModelObject[] foundObjs;
		try {
			foundObjs = queryService.queryObject(GETConstants.Query.activeGrpMemberQuery,
					new String[] { GETConstants.BusinessObjects.user },
					new String[] { UserId });

			if (foundObjs != null && foundObjs.length > 0) 
			{
				for (ModelObject mo : foundObjs) 
				{
					GroupMember grpMember = (GroupMember) mo;
					dataMgmt.getProperties(new ModelObject[] { grpMember },new String[] {
							GETConstants.BusinessObjects.Properties.group,
							GETConstants.BusinessObjects.Properties.theRole });
					Group grp = (Group) grpMember.get_group();
					Role roleObject = (Role) grpMember.get_the_role();
					dataMgmt.getProperties(new ModelObject[] { grp },new String[] { GETConstants.BusinessObjects.Properties.fullName });
					groupName = grp.get_full_name();
					System.out.println("groupName-->"+groupName);
					if (groupName != null && !(groupName.isEmpty())) 
					{
						//boolean geGroup = groupName.contains("GE TRANSPORTATION");
						boolean geGroup = groupName.contains("ENGINEERING");
						if (geGroup) 
						{
							int groupNameSubStringCount = groupName.indexOf(".");
							groupName = groupName.substring(0,groupNameSubStringCount);

							if ((Role) grpMember.get_the_role() != null)
							{
								List<String> role = new ArrayList<String>();
								grpMember.get_the_role();
								roleName = roleObject.get_object_name();
								role.add(roleName);
								if(groupRole.size() > 0)
								{
									boolean IsSameGroup = false;
									for (Map.Entry<String, List<String>> mapentry : groupRole.entrySet())
									{
										if(mapentry.getKey().equalsIgnoreCase(groupName))
										{
											List <String> replaceRole = mapentry.getValue();
											replaceRole.add(roleName);
											groupRole.put(mapentry.getKey(), replaceRole);
											IsSameGroup = true;
										}

									}
									if(!IsSameGroup)
									{
										groupRole.put(groupName, role);
									}
								}
								else
								{
									groupRole.put(groupName, role);
								}
							}
						}
					}
				}
			}
		} catch (Exception e) {
			//e.printStackTrace();
			throw e;
		}
		return groupRole;
	}



	public ArrayList<String> getOrgProjectFromEDOT( String edot ) throws Exception
	{
		ArrayList<String> tcProjectList = new ArrayList<String>();

		try {

			ImanQuery query = findQuery(GETConstants.Query.queryTcProject);

			QueryInput qryInput = new QueryInput();
			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			//qryInput.entries = entries;
			//qryInput.values = values;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof TC_Project ){
							TC_Project project = (TC_Project) mObj;
							tcProjectList.add( project.get_object_string()) ;
						}
					}
				}
			}
		} 
		catch (Exception e)
		{
			//e.printStackTrace();
			throw e;
		}

		return tcProjectList;
	}


	/****************************************************************************
	 * Description: Method to handle the Workflow execution based on action performed on the UI
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public boolean setSessionGroupAndRole(String userId, String groupName, String roleName) throws Exception {

		boolean isGroupRoleChanged = false;
		ImanQuery query = null;
		GroupMember grpMember = null;

		try {
			String[] entries = new String[]{ GETConstants.BusinessObjects.group, GETConstants.BusinessObjects.role, GETConstants.BusinessObjects.user  };
			String[] values = new String[]{ groupName + "*", roleName, userId };
			query = findQuery(GETConstants.Query.queryGroupMember);
			if ( query != null ){
				grpMember = getGroupMember(query, entries, values);
				try {
					SessionService sessionService = SessionService.getService(session.getConnection());
					ServiceData sData = sessionService.setSessionGroupMember(grpMember);
					if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
						isGroupRoleChanged = true;
					}
				} catch (ServiceException e) {
					throw e;
				}
			}

		} catch (Exception e) {
			//e.printStackTrace();
			throw e;
		}
		return isGroupRoleChanged;
	}



	public ArrayList<ItemRevision> getDesignReleaseList( String[] qryEntries, String[] qryValues  )
	{
		ArrayList<ItemRevision> edotList  = null;

		ImanQuery query = findQuery(GETConstants.Query.edotQuery);

		if ( query != null ){

			QueryInput qryInput = new QueryInput();

			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = qryEntries;
			qryInput.values = qryValues;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				edotList = new ArrayList<ItemRevision>();
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS);
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof ItemRevision ){
							ItemRevision edot = (ItemRevision) mObj;
							if ( !edotList.contains(edot) ) {
								edotList.add(edot);

							}
						}
					}
				}
			}
		}



		return edotList;
	}


	public ItemRevision getItemRevisionfromUid ( String uid ){

		ItemRevision rev = null;

		try {
			DataManagementService dmService = DataManagementService.getService(session.getConnection() );
			ServiceData sData = dmService.loadObjects(new String[] { uid });
			ModelObject modelObj = sData.getPlainObject(0);
			if ( modelObj instanceof ItemRevision ){
				rev = (ItemRevision) modelObj;
			}

		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			throw e;
		}
		return rev;
	}


	/****************************************************************************
	 * Description: Method to handle the Workflow execution based on action performed on the UI
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public String getDesignReleaseStatus( ItemRevision edotRev  ) throws Exception
	{

		String taskStatus = null;
		String closure = edotRev.getPropertyDisplayableValue(GETDesignReleaseConstants.Properties.closure);
		String disposition = edotRev.getPropertyDisplayableValue(GETDesignReleaseConstants.Properties.disposition);
		
		if (closure != null && closure.equalsIgnoreCase("Open")){
			
			if ( disposition != null && disposition.equalsIgnoreCase("None") )
			{
				ModelObject[] stageList = edotRev.get_process_stage_list();
				if ( stageList.length == 0 )
				{
					return "In Edit";
				} else {
					for(ModelObject stageObj : stageList)
					{
						if(stageObj instanceof EPMReviewTask  || stageObj instanceof EPMDoTask)
						{
							EPMTask task = (EPMTask) stageObj;
							return task.get_object_string();
						}
					}
				}

			} else if (disposition != null && disposition.equalsIgnoreCase("Approved")) {
				List<ItemRevision> ecrRev = getSecondaryRevisions(edotRev, GETDesignReleaseConstants.Relation.cmImplementedBy);
				if ( ecrRev != null && ecrRev.size() > 0 ){
					List<ItemRevision> ecnRev  = getSecondaryRevisions( ecrRev.get(0), GETDesignReleaseConstants.Relation.cmImplementedBy);
					if ( ecnRev != null && ecnRev.size() > 0  ){
						return "In ECN";
					} else {
						return "In ECR";
					}
				} else {
					ModelObject[] stageList = edotRev.get_process_stage_list();
					for(ModelObject stageObj : stageList)
					{
						if(stageObj instanceof EPMReviewTask  || stageObj instanceof EPMDoTask)
						{
							EPMTask task = (EPMTask) stageObj;
							return task.get_object_string();
						}

					}
				}
			} 
			
		} else if (closure != null && closure.equalsIgnoreCase("Closed")){

			return "Closed";
				
		}
		return taskStatus;
	}
	
	
	/****************************************************************************
	 * Description: Method to handle the Workflow execution based on action performed on the UI
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public boolean isEdotPublished( ItemRevision edotRev  ) throws Exception
	{

		boolean isPublished = true;
		String closure = edotRev.getPropertyDisplayableValue(GETDesignReleaseConstants.Properties.closure);
		String disposition = edotRev.getPropertyDisplayableValue(GETDesignReleaseConstants.Properties.disposition);
		
		if (closure != null && closure.equalsIgnoreCase("Open")){
			
			if ( disposition != null && disposition.equalsIgnoreCase("None") )
			{
				ModelObject[] stageList = edotRev.get_process_stage_list();
				if ( stageList.length == 0 )
				{
					isPublished = false;
				} 
			}
		}
		return isPublished;
	}


	/****************************************************************************
	 * Description: Method to get the new subtask id in DRE Build page 
	 * Returns: boolean
	 * 
	 ****************************************************************************/

	public static String getEditDREBuild(ArrayList<String> bomList, String selectedBom) 
	{
		List <String> listClone = new ArrayList<String>(); 
		for (String string : bomList) {
			if(string.startsWith(selectedBom)){
				listClone.add(string);
			}
		}
		return getNextbomitem(listClone, selectedBom);

	}

	/****************************************************************************
	 * Description: Method to get the new subtask suffix(A-Z, excluding I and O) in DRE Build page 
	 * Returns: boolean
	 * 
	 ****************************************************************************/
	public static String getNextbomitem(List<String> listClone,String str)
	{
		String lastChar, nextBomline;
		int lastCharval;
		int prevCharval = 0;
		int nextCharval;
		Collections.sort(listClone);
		for(String newStr : listClone)
		{
			lastChar = newStr.substring(newStr.length()-1);
			lastCharval = String.valueOf(lastChar).charAt(0);
			if(lastCharval >= 65 && lastCharval <= 90)
			{
				if(lastCharval > prevCharval)
				{
					prevCharval = lastCharval;
				}
			}
			else
			{
				prevCharval = 64;
			}
		}
		nextCharval = prevCharval+1;
		if(nextCharval == 73 || nextCharval == 79)
		{
			nextBomline = str+(char)(nextCharval+1);
		}
		else
		{
			nextBomline = str+(char)(nextCharval);
		}

		return nextBomline;
	}



	/*************************************************************************
	 * This method checks for availability of the Item based on part type
	 * @param itemID  - The String itemID to check  availability of Item is required
	 * @param partTypeName -  The String Part type to check  availability of Item is required
	 * @return item
	 ************************************************************************/
	public  Item getItemfromItemId(String itemID) throws Exception
	{

		Item tcItem = null;
		ImanQuery itemQry = null;

		SavedQueryService savedQueryService = SavedQueryService	.getService(session.getConnection());

		itemQry = findQuery("Item...");


		if ( null != itemQry ) 
		{
			String[] fields = { "Item ID"};
			String[] values = { itemID };
			QueryInput queryInput = new QueryInput();
			queryInput.query = itemQry;
			queryInput.entries = fields;
			queryInput.values = values;
			queryInput.maxNumToReturn = 100;

			SavedQueriesResponse queryResponse = savedQueryService.executeSavedQueries(new QueryInput[] { queryInput });
			
			QueryResults[] results =  queryResponse.arrayOfResults;
			if ( results.length > 0 ){
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS );
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof Item ){
							tcItem =  (Item) mObj;
						}
					}
				}
			}
		}


		return tcItem;
	}

	/************************************************************************
	 * This method checks for availability of the Item based on part type
	 * @param itemID  - The String itemID to check  availability of Item is required
	 * @param partTypeName -  The String Part type to check  availability of Item is required
	 * @return item
	 ************************************************************************/
	public  ArrayList<ModelObject> getItems(String[] fields, String[] values ) 
	{

		ImanQuery itemQry = null;

		ArrayList<ModelObject> listItems = new ArrayList<ModelObject>();

		try {
			SavedQueryService savedQueryService = SavedQueryService	.getService(session.getConnection());

			itemQry = findQuery(GETDesignReleaseConstants.Query.strECRQuery);


			if ( null != itemQry ) 
			{

				QueryInput queryInput = new QueryInput();
				queryInput.query = itemQry;
				queryInput.entries = fields;
				queryInput.values = values;
				queryInput.maxNumToReturn = 100;

				SavedQueriesResponse queryResponse = savedQueryService.executeSavedQueries(new QueryInput[] { queryInput });

				if ( null != queryResponse && null != queryResponse.arrayOfResults
						&& queryResponse.arrayOfResults.length > 0
						&& null != queryResponse.arrayOfResults[0].objectUIDS
						&& queryResponse.arrayOfResults[0].objectUIDS.length > 0 ) 
				{
					ServiceData serviceData = DataManagementService.getService(session.getConnection()).loadObjects(queryResponse.arrayOfResults[0].objectUIDS);
					if ( serviceData.sizeOfPlainObjects() > 0 )// Add more validation
					{
						serviceData.getPlainObject(0);
						for(int noOfItems=0; noOfItems < serviceData.sizeOfPlainObjects(); noOfItems++)
						{
							listItems.add(serviceData.getPlainObject(noOfItems));

						}

					}
				}
			}
		} catch (Exception e) {
			//e.printStackTrace();
			throw e;
		}

		return listItems;
	}

	/*************************************************************************
	 * Returns the query in TC for the input query name
	 * 
	 * @param  String strQueryName 
	 * @return ImanQuery query
	 ************************************************************************/
	public ImanQuery findQuery(String strQueryName) 
	{
		ImanQuery query = null;

		if ( null != strQueryName && strQueryName.length() > 0 ) 
		{
			try 
			{
				FindSavedQueriesCriteriaInput queryInput = new FindSavedQueriesCriteriaInput();
				queryInput.queryNames = new String[] { strQueryName };

				SavedQueryService savedQueryService = SavedQueryService.getService(session.getConnection());
				FindSavedQueriesResponse findResponse = savedQueryService.findSavedQueries(new FindSavedQueriesCriteriaInput[] { queryInput });

				if ( null != findResponse.savedQueries && findResponse.savedQueries.length > 0 ) 
				{
					query = findResponse.savedQueries[0];
				}
			} catch ( ServiceException e ) {
				e.printStackTrace();
			}
		}

		return query;
	}

	/**
	 * 
	 * @return
	 * @throws NotLoadedException
	 */

	public ArrayList<ItemRevision> getProjectGroupData( ) throws NotLoadedException
	{
		ArrayList<ItemRevision> edotList  = null;

		ImanQuery query = findQuery("GET Project Members");
		//	new String[] {GETConstants.Query.strProjectID, GETConstants.Query.EngineerResource, GETConstants.Query.strEdotID}, new String[] {projectId, sessionUserId+"*", "EDOT*"});
		String[] entries = {"Project ID","Project Name"};
		String[] values = {"ES*","Engine Mechanical System"};



		if ( query != null ){

			QueryInput qryInput = new QueryInput();

			qryInput.clientId = UUID.randomUUID().toString();
			qryInput.limitList = new ModelObject[0];
			qryInput.maxNumToReturn = 0;
			qryInput.query = query;
			qryInput.resultsType = 0;
			qryInput.entries = entries;
			qryInput.values = values;

			DataManagementService dmService = DataManagementService.getService( session.getConnection() );
			SavedQueryService queryService = SavedQueryService.getService( session.getConnection() );

			SavedQueriesResponse qryResp = queryService.executeSavedQueries(new QueryInput[]{ qryInput });

			QueryResults[] results =  qryResp.arrayOfResults;
			if ( results.length > 0 ){
				edotList = new ArrayList<ItemRevision>();
				ServiceData sData = dmService.loadObjects( results[0].objectUIDS);
				if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
					for (int jnx = 0; jnx < sData.sizeOfPlainObjects(); jnx++) {
						ModelObject mObj = sData.getPlainObject(jnx);
						if ( mObj instanceof GroupMember ){
							GroupMember grpMember = (GroupMember) mObj;
							dmService.getProperties(new ModelObject[]{grpMember},new String[]{"user_name"});
							System.out.println("grpMember.get_role().get_object_name()-->"+grpMember.get_user_name());
						}
					}
				}
			}
		}



		return edotList;
	}
	
	
	public Map<String, List<String>> getLOVValues() throws Exception
	{

		List<String> lovList = null;
		Map<String,List<String>> mapLov  = new HashMap<String,List<String>>();

		try {

			ImanQuery groupProjectQuery = findQuery(GETConstants.Query.groupProjectQuery);

			String[] queryEntries = new String[]{GETConstants.Query.groupProjectLovName};
			String[] queryValues = new String[]{GETDesignReleaseConstants.LOV.strGroupProjectLov};
			
			ListOfValuesString groupProjectLov =  getgroupProjectLov(groupProjectQuery, queryEntries, queryValues);
			String[] str =  groupProjectLov.get_lov_values();
			String lovDesc = null;

			for(int m=0;m<str.length;m++)
			{
				lovList = new ArrayList<String>();
				ListOfValues[] lovs = groupProjectLov.get_value_filters();
				if(lovs.length > 0)
				{
					ListOfValuesString lovs1 = (ListOfValuesString)lovs[m];
					String[] str1 = lovs1.get_lov_values();
					String[] strDesc = lovs1.get_lov_value_descriptions();
					for(int n=0;n<str1.length;n++)
					{
						lovDesc = str1[n].toString()+"-"+strDesc[n].toString();
						lovList.add(lovDesc) ;
					}

				}
				mapLov.put(str[m].toString(), lovList);
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		

        return mapLov;
    }
	
	

   
//	public Map<String, List<String>> getLOVValues1() throws Exception
//    {
//        List<String> lovList = null;
//        Map<String,List<String>> mapLov  = new HashMap<String,List<String>>();
//        SessionService sesion = SessionService.getService(session.getConnection());
//        PropertyDescriptor uomPropDescriptor = null;
//        List<PropertyDescriptor> propDescriptors = sesion.getTypeDescriptions(new String[]{GETOnTrackConstants.BuinessObjects.GETProject}).getTypes().get(0).getPropertyDescriptors();
//        for (PropertyDescriptor propDesc : propDescriptors)
//        {
//        	//System.out.println("propDesc-->"+propDesc.getName());
//            if (propDesc.getName().compareTo(GETOnTrackConstants.Properties.SecProjNumber) == 0)
//            {
//                uomPropDescriptor = propDesc;
//                break;
//            }
//        }
//       
//			try {
//				if (uomPropDescriptor != null)
//				{
//				    GETDataManagement dmService = GETDataManagement.getDMService(session.getConnection());
//				    
//				    String lovUID = uomPropDescriptor.getLovs().get(0).getLovUid();
//				    ListOfValuesString lovString = (ListOfValuesString) dmService.loadObjects(new String[]{lovUID})[0];
//				     
//				    
//				     String[] str =  lovString.get_lov_values();
//				     String lovDesc = null;
//				     
//					 for(int m=0;m<str.length;m++)
//					{
//						lovList = new ArrayList<String>();
//						 ListOfValues[] lovs = lovString.get_value_filters();
//						 if(lovs.length > 0)
//						 {
//							 ListOfValuesString lovs1 = (ListOfValuesString)lovs[m];
//							 String[] str1 = lovs1.get_lov_values();
//							 String[] strDesc = lovs1.get_lov_value_descriptions();
//							 for(int n=0;n<str1.length;n++)
//							 {
//								lovDesc = str1[n].toString()+"-"+strDesc[n].toString();
//								lovList.add(lovDesc) ;
//							 }
//							
//						 }
//						 mapLov.put(str[m].toString(), lovList);
//						
//					}
//					 
//				}
//			} catch (Exception e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
//		
//
//        return mapLov;
//    }
    
	
	//@SuppressWarnings("null")
	public List<String> getMainGroupList( String mainGrp)throws Exception{
		//GETDao dao = getDaoMap(sessionId);
		List<String> mainGrpList = null;
		List<String> orgList = null;
		Map<String, List<String>> mapGrpList = null;
		mapGrpList = getLOVValues();
		
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
		
		
		//return null;
	}
 
    

}
/*************************************************************************
 *************************End of class************************************
 *************************************************************************/
