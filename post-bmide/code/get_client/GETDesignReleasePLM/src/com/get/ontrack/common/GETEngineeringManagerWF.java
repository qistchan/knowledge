package com.get.ontrack.common;


import com.teamcenter.services.strong.core._2015_10.DataManagement.ReassignParticipantInfo;
import com.teamcenter.services.strong.core._2015_10.DataManagement.ReassignParticipantResponse;
import com.teamcenter.services.strong.core._2007_06.DataManagement.RelationAndTypesFilter;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsData2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsOutput2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsPref2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationsResponse2;
import com.teamcenter.services.strong.core._2007_09.DataManagement.ExpandGRMRelationship;
//import com.get.ontrack.getrans.clientx.GETSession;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.services.strong.core._2008_06.DataManagement.AddParticipantOutput;
import com.teamcenter.services.strong.core._2008_06.DataManagement.ParticipantInfo;
import com.teamcenter.services.strong.core._2008_06.DataManagement.Participants;
import com.teamcenter.services.strong.core._2008_06.DataManagement.AddParticipantInfo;
import com.teamcenter.services.strong.workflow.WorkflowService;
import com.teamcenter.services.strong.workflow._2008_06.Workflow.ContextData;
import com.teamcenter.services.strong.workflow._2008_06.Workflow.CreateSignoffInfo;
import com.teamcenter.services.strong.workflow._2008_06.Workflow.InstanceInfo;
import com.teamcenter.services.strong.workflow._2014_06.Workflow.PerformActionInputInfo;
import com.teamcenter.services.strong.workflow._2008_06.Workflow.CreateSignoffs;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.Property;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.EPMConditionTask;
import com.teamcenter.soa.client.model.strong.EPMDoTask;
import com.teamcenter.soa.client.model.strong.EPMJob;
import com.teamcenter.soa.client.model.strong.EPMPerformSignoffTask;
import com.teamcenter.soa.client.model.strong.EPMReviewTask;
import com.teamcenter.soa.client.model.strong.EPMSelectSignoffTask;
import com.teamcenter.soa.client.model.strong.EPMTask;
import com.teamcenter.soa.client.model.strong.GroupMember;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.soa.client.model.strong.Participant;
import com.teamcenter.soa.client.model.strong.ReleaseStatus;
import com.teamcenter.soa.client.model.strong.Signoff;
import com.teamcenter.soa.client.model.strong.User;
import com.teamcenter.soa.exceptions.NotLoadedException;
import java.util.UUID;

public class GETEngineeringManagerWF {
	
	
	private  final String	EPM_complete_action 		="SOA_EPM_complete_action";
		private  final String EPM_perform_action 		="SOA_EPM_perform_action";
		private  final String EPM_approve 				= "SOA_EPM_approve";
		private  final String EPM_reject 				= "SOA_EPM_reject";
		private  final String EPM_completed 			= "SOA_EPM_completed";
		private  final String EPM_true 					= "SOA_EPM_true";
		private  final String EPM_false 				= "SOA_EPM_false";
		private  final String EPM_Review 				= "SOA_EPM_Review";
		private  final String EPM_Signeoff_Origin_Profile = "SOA_EPM_SIGNOFF_ORIGIN_PROFILE";
		private Connection connection = null;
		//private static GETSession session;
		
		public GETEngineeringManagerWF() {
			this.connection = null;
		}
		
		public GETEngineeringManagerWF(Connection connection) {
			this.connection = connection;
		}
		
		
		public boolean isReleased( ItemRevision revision )
		{
			boolean hasStatus = true;
			try
			{
				DataManagementService dmService = DataManagementService.getService(connection );
				
				//ModelObject[] revs = new ModelObject[]{revision};
				dmService.getProperties(new ModelObject[]{revision}, new String[] { "release_status_list"});
				
				ReleaseStatus[] relStatusList = revision.get_release_status_list();
				if ( relStatusList == null || relStatusList.length == 0 ){
					//if not released - false
					hasStatus = false;
				}

			} catch(NotLoadedException e) {
				e.printStackTrace();
			}
			
			return hasStatus;
		}
	
	
	
	/* This method is designed to create a New Process as if you used the Rich client interface New Process dialog <ctrl-p>. */
	public boolean createNewProcess( String Template, String targetUid, String workflowName)
	{
		ContextData contextData = new ContextData();
		String observerKey = "";
		String name = workflowName;
		String subject = "createInstance";
		String description = workflowName;
		
		contextData.processTemplate = Template; // update with your own Process Template.
		contextData.subscribeToEvents = false;
		contextData.subscriptionEventCount = 0;
		contextData.attachmentCount = 1;
		contextData.attachments = new String[]{ targetUid };
		try {
			contextData.attachmentTypes = new int[]{EPM_attachement.target.value() }; 
			// (1 == 'EPM_target_attachment') - AttachmentTypes are defined in include/epm/epm.h
			
			WorkflowService wfService = WorkflowService.getService( this.connection );

			InstanceInfo instanceInfo = wfService.createInstance(true,observerKey, name, subject, description, contextData);
			ServiceData sData = instanceInfo.serviceData;
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData))
			{
				//System.out.println("New WorkFlow Instance:");
			//	System.out.println(" instanceKey: " + instanceInfo.instanceKey);
				
				return true;
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return false;
	}
	
	// Values for EPM_Attachement taken from epm/epm.h (Attachment Types)
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
	
	
	public boolean edotApproval( ItemRevision edotRev, GroupMember grpMember )
	{
		boolean isCompleted = false;
		try
		{
//			DataManagementService dmService = DataManagementService.getService( this.connection );
			WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = edotRev.get_process_stage_list();

			for(ModelObject stageObj : stageList)
			{

				if(stageObj instanceof EPMPerformSignoffTask)
				{
					Signoff signOff = null;
					isCompleted = false;
					EPMPerformSignoffTask performSignOffTask = (EPMPerformSignoffTask)stageObj;	
			//		dmService.getProperties(new ModelObject[]{performSignOffTask}, new String[] { "task_state", "user_all_signoffs" });
					if (performSignOffTask.get_task_state().equalsIgnoreCase("Started")){
						ModelObject[] signOffs = performSignOffTask.get_user_all_signoffs();
						for (int inx = 0; inx < signOffs.length; inx++) {
							if ( signOffs[inx] != null ){
								signOff = (Signoff) signOffs[inx];
								break;
							}
						}
						if(signOff != null)
						{
							PerformActionInputInfo actionInputInfo = new PerformActionInputInfo();
							actionInputInfo.action = EPM_perform_action;
							actionInputInfo.actionableObject = performSignOffTask;
							actionInputInfo.supportingValue = EPM_approve;
							actionInputInfo.supportingObject = signOff;
							actionInputInfo.clientId = UUID.randomUUID().toString();

							ServiceData sData = wfService.performAction3( new PerformActionInputInfo[]{ actionInputInfo });
							if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
								isCompleted = true;
							}
						}

					}			
				}

				if (isCompleted) break;
			}
		}

		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}

		return isCompleted;
	}
	
	public boolean edotReject( ItemRevision edotRev, GroupMember grpMember )
	{
		boolean isCompleted = false;
		try
		{
			DataManagementService dmService = DataManagementService.getService( this.connection );
			WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = edotRev.get_process_stage_list();

			dmService.getProperties(stageList, new String[] {"child_tasks" });

			for(ModelObject stageObj : stageList)
			{
				if( stageObj instanceof EPMPerformSignoffTask )
				{
					Signoff signOff = null;
					isCompleted = false;
					EPMPerformSignoffTask performSignOffTask = (EPMPerformSignoffTask)stageObj;	

					if (performSignOffTask.get_task_state().equalsIgnoreCase("Started")){
					//dmService.getProperties(new ModelObject[]{performSignOffTask}, new String[] {"task_state", "user_all_signoffs" });
						ModelObject[] signOffs = performSignOffTask.get_user_all_signoffs();
						for (int inx = 0; inx < signOffs.length; inx++) {
							if ( signOffs[inx] != null ){
								signOff = (Signoff) signOffs[inx];
								break;
							}
						}
						if(signOff != null)
						{
							PerformActionInputInfo actionInputInfo = new PerformActionInputInfo();
							actionInputInfo.action = EPM_perform_action;
							actionInputInfo.actionableObject = performSignOffTask;
							actionInputInfo.supportingValue = EPM_reject;
							actionInputInfo.supportingObject = signOff;
							actionInputInfo.clientId = UUID.randomUUID().toString();

							ServiceData sData = wfService.performAction3( new PerformActionInputInfo[]{ actionInputInfo });
							if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
								isCompleted = true;
							}
						}
					}
				}

				if (isCompleted) break;
			}
		}

		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}

		return isCompleted;
	}

	
	public boolean edotApproval_ORIG( ItemRevision edotRev, GroupMember grpMember )
	{
		boolean isCompleted = false;
		try
		{
			DataManagementService dmService = DataManagementService.getService( this.connection );
	    	WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = edotRev.get_process_stage_list();
			
			dmService.getProperties(stageList, new String[] {"child_tasks" });
		
			for(ModelObject stageObj : stageList)
			{
				if(stageObj instanceof EPMReviewTask)
				{
					EPMReviewTask task = (EPMReviewTask)stageObj;
					Signoff signOff = null;
					
					dmService.loadObjects(new String[]{task.getUid()});
					dmService.getProperties(new ModelObject[]{task}, new String[] {"child_tasks" });
					ModelObject[] childTasks =task.get_child_tasks();
					dmService.getProperties(childTasks, new String[] { "signoff_profiles", "task_state", "valid_signoffs", "user_all_signoffs"  });
					
					for(ModelObject child : childTasks)
					{
												
						if(child instanceof EPMPerformSignoffTask)
						{
							isCompleted = false;
							EPMPerformSignoffTask performSignOffTask = (EPMPerformSignoffTask)child;	
							dmService.getProperties(new ModelObject[]{performSignOffTask}, new String[] {"task_state", "user_all_signoffs" });
							if (performSignOffTask.get_task_state().equalsIgnoreCase("Started")){
								
//								ModelObject[] signOffs = performSignOffTask.get_valid_signoffs();
								ModelObject[] signOffs = performSignOffTask.get_user_all_signoffs();
								for (int inx = 0; inx < signOffs.length; inx++) {
									if ( signOffs[inx] != null ){
										signOff = (Signoff) signOffs[inx];
										break;
									}
								}
								if(signOff != null)
								{
									
									PerformActionInputInfo actionInputInfo = new PerformActionInputInfo();
									actionInputInfo.action = EPM_perform_action;
									actionInputInfo.actionableObject = performSignOffTask;
									actionInputInfo.supportingValue = EPM_approve;
									actionInputInfo.supportingObject = signOff;
									actionInputInfo.clientId = UUID.randomUUID().toString();
									
									ServiceData sData = wfService.performAction3( new PerformActionInputInfo[]{ actionInputInfo });
									if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
										isCompleted = true;
									}
								}

							}
							dmService.unloadObjects(new ModelObject[]{performSignOffTask});						
						}
					}
					dmService.unloadObjects(new ModelObject[]{task});
				}
				if (isCompleted) break;
			}
		}

		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}
		
		return isCompleted;
	}
	
	public boolean edotReject_ORIG( ItemRevision edotRev, GroupMember grpMember )
	{
		boolean isCompleted = false;
		try
		{
			DataManagementService dmService = DataManagementService.getService( this.connection );
	    	WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = edotRev.get_process_stage_list();
			
			dmService.getProperties(stageList, new String[] {"child_tasks" });
		
			for(ModelObject stageObj : stageList)
			{
				if(stageObj instanceof EPMReviewTask)
				{
					EPMReviewTask task = (EPMReviewTask)stageObj;
					Signoff signOff = null;
					
					ModelObject[] childTasks =task.get_child_tasks();
					dmService.getProperties(childTasks, new String[] { "signoff_profiles", "task_state", "valid_signoffs", "user_all_signoffs"  });
					
					for(ModelObject child : childTasks)
					{
												
						if(child instanceof EPMPerformSignoffTask)
						{
							isCompleted = false;
							EPMPerformSignoffTask performSignOffTask = (EPMPerformSignoffTask)child;	
							
							if (performSignOffTask.get_task_state().equalsIgnoreCase("Started")){
								
//								ModelObject[] signOffs = performSignOffTask.get_valid_signoffs();
								ModelObject[] signOffs = performSignOffTask.get_user_all_signoffs();
								for (int inx = 0; inx < signOffs.length; inx++) {
									if ( signOffs[inx] != null ){
										signOff = (Signoff) signOffs[inx];
										break;
									}
								}
								if(signOff != null)
								{
									
									PerformActionInputInfo actionInputInfo = new PerformActionInputInfo();
									actionInputInfo.action = EPM_perform_action;
									actionInputInfo.actionableObject = performSignOffTask;
									actionInputInfo.supportingValue = EPM_reject;
									actionInputInfo.supportingObject = signOff;
									actionInputInfo.clientId = UUID.randomUUID().toString();
									
									ServiceData sData = wfService.performAction3( new PerformActionInputInfo[]{ actionInputInfo });
									if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
										isCompleted = true;
									}
								}

							}
													
						}
					}
				}
				if (isCompleted) break;
			}
		}

		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}
		
		return isCompleted;
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
			
			DataManagementService dmService = DataManagementService.getService( this.connection );
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

			DataManagementService dmService = DataManagementService.getService( this.connection );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );
			sData = relationResp.serviceData;				     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
								if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
									isExist = true;
									break;

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

			DataManagementService dmService = DataManagementService.getService( this.connection );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );
			sData = relationResp.serviceData;				     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
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

			DataManagementService dmService = DataManagementService.getService( this.connection );
			ExpandGRMRelationsResponse2 relationResp =dmService.expandGRMRelationsForPrimary( new ModelObject[]{ edotRev },relationPref );		     
			if(!GETOnTrackCommonSoaOperations.ServiceDataError(relationResp.serviceData)){
				for(ExpandGRMRelationsOutput2 relationOut : relationResp.output){
					for(ExpandGRMRelationsData2 relationData : relationOut.relationshipData) {
						for(ExpandGRMRelationship tcRelation : relationData.relationshipObjects ) {
							if(tcRelation.otherSideObject instanceof Participant) {
								Participant participant = (Participant) tcRelation.otherSideObject;
								
								if ( participantType.equalsIgnoreCase(participant.getTypeObject().getName())){
									ModelObject[] participants = new ModelObject[]{ participant };	
									dmService.getProperties( participants, new String[] { "assignee"} ); 
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
																
								
//								ModelObject[] participants = new ModelObject[]{ participant };	
//								dmService.getProperties( participants, new String[] {"fnd0AssigneeRole", "assignee", "object_string"} ); 
//								Role participantRole = (Role) participant.get_fnd0AssigneeRole();
//								ModelObject[] participantRoles = new ModelObject[]{ participantRole };	
//								dmService.getProperties( participantRoles, new String[] {"role_name"} ); 
//								String participantRoleName = participantRole.get_role_name();
//								
//								if ( participantRoleName.equalsIgnoreCase(roleName)){
//									
//									GroupMember participantMember = (GroupMember) participant.get_assignee();
//									ReassignParticipantInfo reassignParticipantInfo = new ReassignParticipantInfo();
//									
//									reassignParticipantInfo.allParticipantTypes = false;
//									reassignParticipantInfo.clientId = UUID.randomUUID().toString();
//									reassignParticipantInfo.participantTypes = new String[]{ participantType };
//									reassignParticipantInfo.itemRevs = new ItemRevision[]{edotRev};
//									reassignParticipantInfo.fromAssignee = participantMember;
//									reassignParticipantInfo.toAssignee = groupMember;
//									
//									ReassignParticipantResponse reassignResp = dmService.reassignParticipants( new ReassignParticipantInfo[]{ reassignParticipantInfo } );
//									
//									if(!GETOnTrackCommonSoaOperations.ServiceDataError(reassignResp.serviceData)){
//										isParticipantUpdated = true;
//										//System.out.println("Participant Removed");
//									}
//									else
//									{
//										throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(reassignResp.serviceData));
//									}
//
//								}
								
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
	
	
	
	public User getResourceProperty ( ItemRevision edotObj, String resourceProperty ){

		User resource = null;
		try {

			DataManagementService dmService = DataManagementService.getService( this.connection );
			ModelObject[] edotObjs = new ModelObject[]{ edotObj };	
			dmService.getProperties( edotObjs, new String[] {resourceProperty} );
			Property prop = edotObj.getPropertyObject( resourceProperty );
			ModelObject modelObj = prop.getModelObjectValue();
			if ( modelObj == null ){
				return null;
			} else {
				if ( modelObj instanceof User ){
					resource = (User) modelObj;
				}	
			}

		} catch (NotLoadedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return resource;
	}
	
	
	//To be Replace by add participant- Prasad
	public boolean edotPerformSelectSignOff( ItemRevision rev, GroupMember grpMember ) throws Exception
	{
		boolean isCompleted = false;
		try
		{
			DataManagementService dmService = DataManagementService.getService( this.connection );
	    	WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = rev.get_process_stage_list();
			
			dmService.getProperties(stageList, new String[] {"child_tasks" });
		
			for(ModelObject stageObj : stageList)
			{
				
				if(stageObj instanceof EPMReviewTask)
				{
					EPMReviewTask task = (EPMReviewTask)stageObj;
					Signoff signOff = null;
					
					ModelObject[] childTasks =task.get_child_tasks();
					dmService.getProperties(childTasks, new String[] { "signoff_profiles", "task_state", "valid_signoffs", "user_all_signoffs"  });
					
					for(ModelObject child : childTasks)
					{
												
						if(child instanceof EPMSelectSignoffTask)
						{
							isCompleted = false;
							
							EPMSelectSignoffTask selectSignOffTask =(EPMSelectSignoffTask) child;	
							
							//Validate Select SignOff Task status
							if (selectSignOffTask.get_task_state().equalsIgnoreCase("Completed")){
								continue;
							}
							
							ModelObject[] signOffs = selectSignOffTask.get_valid_signoffs();
							
							//Create SignOff
							if ( signOffs == null ||  signOffs.length == 0 ){
								getProcessOwner(rev);
								signOff = createProfileSignOff( selectSignOffTask, grpMember );
							} else {
								signOff = (Signoff) signOffs[0];
							}
														
							if(signOff != null){
								PerformActionInputInfo actionInputInfo = new PerformActionInputInfo();
								actionInputInfo.action = EPM_complete_action;
								actionInputInfo.actionableObject = selectSignOffTask;
								actionInputInfo.supportingValue = EPM_completed;
								actionInputInfo.supportingObject = signOff;
								actionInputInfo.clientId = UUID.randomUUID().toString();
								
								ServiceData sData = wfService.performAction3( new PerformActionInputInfo[]{ actionInputInfo });
								if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
									isCompleted = true;
								}
								else
								{
									throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
								}
							}			
											
						}
					}
				}
			}
		}

		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}
		
		return isCompleted;
	}

	
	//After calling engrManagerReject, Call the below function for Closure Operation
	//Group Member should be Engineering Manager
	public boolean engrManagerRejectClosure( ItemRevision rev, boolean decision ) throws Exception
	{
		try
		{
			DataManagementService dmService = DataManagementService.getService( this.connection );
			WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = rev.get_process_stage_list();

			dmService.getProperties(stageList, new String[] {"child_tasks" });


			for(ModelObject stageObj : stageList)
			{

				if(stageObj instanceof EPMConditionTask)
				{
					EPMConditionTask conditionTask = (EPMConditionTask)stageObj;

					PerformActionInputInfo actionInputInfo = new PerformActionInputInfo();
					actionInputInfo.action = EPM_complete_action;
					actionInputInfo.actionableObject = conditionTask;
					if (decision)
						actionInputInfo.supportingValue = EPM_true;
					else 
						actionInputInfo.supportingValue = EPM_false;
					actionInputInfo.clientId = UUID.randomUUID().toString();

					ServiceData sData = wfService.performAction3( new PerformActionInputInfo[]{ actionInputInfo });
					if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
						//System.out.println("Perform SignOff Completed");
						return true;
					}
					else
					{
						throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
					}
					
					//return true;

				}
			}
		}

		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}

		return false;
	}
	
	//To Create SignOff Profile	
	protected Signoff createProfileSignOff( EPMTask selectSignOffTask, GroupMember grpMember ) throws Exception
	{
		try
		{
			ModelObject[] signoffProfiles =selectSignOffTask.get_signoff_profiles();
			
			
			if(signoffProfiles != null && signoffProfiles.length > 0)
			{
				CreateSignoffInfo profileInfo = new CreateSignoffInfo();
				CreateSignoffs signoff = new CreateSignoffs();
				
				profileInfo.signoffAction = EPM_Review;
				profileInfo.origin = signoffProfiles[0];
				profileInfo.originType =EPM_Signeoff_Origin_Profile;
				profileInfo.signoffMember = grpMember;
				
				signoff.signoffInfo = new CreateSignoffInfo[]{profileInfo };
				signoff.task = selectSignOffTask;
				
			 	WorkflowService wfService = WorkflowService.getService( this.connection );
				ServiceData sData = wfService.addSignoffs(new CreateSignoffs[]{ signoff });
				
				if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData))
				{
					if(sData.sizeOfCreatedObjects() > 0)
					{
						ModelObject obj =sData.getCreatedObject(0);
						
						if(obj instanceof Signoff)
							return (Signoff)obj;
					}
				}
				else
				{
					throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
				}
			}
		}
		catch(ServiceException e)
		{
			e.printStackTrace();
		}
		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	public boolean deligateEngineer( ItemRevision rev, GroupMember engineerGroupMember ) throws Exception
	{
		boolean isDeligated = false;
		
		try
		{

			DataManagementService dmService = DataManagementService.getService( this.connection );
	    	WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = rev.get_process_stage_list();	
			dmService.getProperties(stageList, new String[] {"child_tasks" });
			
		
			ModelObject[] revs = new ModelObject[]{rev};
			dmService.getProperties(revs, new String[] { "release_status_list"});
	
			for(ModelObject stageObj : stageList)
			{
				
				if(stageObj instanceof EPMReviewTask)
				{
					EPMReviewTask task = (EPMReviewTask)stageObj;
					Signoff signOff = null;
					
					ModelObject[] childTasks =task.get_child_tasks();
					dmService.getProperties(childTasks, new String[] { "valid_signoffs", "user_all_signoffs" });

					for(ModelObject child : childTasks)
					{					
						if(child instanceof EPMPerformSignoffTask){
							EPMPerformSignoffTask performSignOffTask = (EPMPerformSignoffTask)child;										
							ModelObject[] signOffs = performSignOffTask.get_valid_signoffs();						
							signOff = (Signoff) signOffs[0];

							if(signOff != null)
							{
																
								ServiceData sData = wfService.delegateSignoff(engineerGroupMember, signOff);
								if (!GETOnTrackCommonSoaOperations.ServiceDataError(sData)) {
									isDeligated = true;
									//System.out.println("Perform SignOff Completed");
								}
								else
								{
									throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
								}
								

							}
						}
					}
				}
			}
		}

		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}
		
		return isDeligated;
	}
	
	
	public boolean completeReassign( ItemRevision edot ) throws Exception
	{
		
		
		boolean isCompleted = false;
		try
		{
			DataManagementService dmService = DataManagementService.getService( this.connection );
	    	WorkflowService wfService = WorkflowService.getService( this.connection );
			ModelObject[] stageList = edot.get_process_stage_list();

			
			for(ModelObject stageObj : stageList)
			{
				if(stageObj instanceof EPMDoTask)
				{
					EPMDoTask doTask = (EPMDoTask)stageObj;
					ModelObject[] doTasks = new ModelObject[]{ doTask };
					dmService.getProperties( doTasks, new String[]{"task_type","task_template", "task_template", "successors", "fnd0AliasTaskName"} );

						
					PerformActionInputInfo actionInputInfo = new PerformActionInputInfo();
					actionInputInfo.action = EPM_complete_action;
					actionInputInfo.actionableObject = doTask;
					actionInputInfo.supportingValue = EPM_completed;
					actionInputInfo.clientId = UUID.randomUUID().toString();
					
					ServiceData sData = wfService.performAction3( new PerformActionInputInfo[]{ actionInputInfo });
					if(!GETOnTrackCommonSoaOperations.ServiceDataError(sData))
					{
						isCompleted = true;
					}
					else
					{
						throw new Exception(GETOnTrackCommonSoaOperations.ServiceDataErrorMsg(sData));
					}
				}
			}

		}
		catch(NotLoadedException e)
		{
			e.printStackTrace();
		}
		return isCompleted;
	}
	
	public String getProcessOwner( ItemRevision edotRev  )
	{
		
		String userId = null;
		try
		{
			DataManagementService dmService = DataManagementService.getService( this.connection );			
			ModelObject[] edotRevs = new ModelObject[]{ edotRev };	
			dmService.getProperties( edotRevs, new String[] {"fnd0AllWorkflows" } );
			ModelObject[] allWorkflows = edotRev.get_fnd0AllWorkflows();	

			if(allWorkflows[0] instanceof EPMTask)
			{
				
				EPMTask task = (EPMTask) allWorkflows[0];
				ModelObject[] tasks = new ModelObject[]{ task };	
				dmService.getProperties( tasks, new String[] {"parent_process"} );
				EPMJob job = (EPMJob) task.get_parent_process();
				
				ModelObject[] jobs = new ModelObject[]{ job };	
				dmService.getProperties( jobs, new String[] {"root_task()"} );
				
				EPMTask rootTask = (EPMTask) job.get_root_task();
				ModelObject[] rootTasks = new ModelObject[]{ task };	
				dmService.getProperties( rootTasks, new String[] { "owning_user"} );
				User user = (User) rootTask.get_owning_user();			
				userId = user.get_user_id();	

				//System.out.println("User ID : " + userId );
			}

		} catch(NotLoadedException e)
		{
			e.printStackTrace();
		}
		
		return userId;

	}

}
