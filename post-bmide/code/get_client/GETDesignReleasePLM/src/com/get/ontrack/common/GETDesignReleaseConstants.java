
package com.get.ontrack.common;

/**
 * This is a Class for all Custom String Constants
 *
 * @author TCSL
 */
public class GETDesignReleaseConstants
{
    /**
     * Static class for all Business Objects
     * 
     * @author TCSL
     */
	public static class BuinessObjects
	{
		public static String GETDsgnRelease 			= "GET6DsgnRelease";
		public static String GETDsgnReleaseRevision 	= "GET6DsgnReleaseRevision";
		public static String GETDsgnReleasePlan 		= "GET6DsgnRelPlan";
		public static String GETDsgnReleasePlanRevision = "GET6DsgnRelPlanRevision";
		public static String GETProject 				= "GET6Project";
		public static String GETEcr 				    = "GET6ECR"; 
		public static String GETEcn 				    = "GET6ECN"; 
		public static String GETEcrRev 				    = "GET6ECRRevision";
		public static String GETEcnRev 				    = "GET6ECNRevision";
		public static String GETEcrType 				= "Engr Change Request";
		public static String GETTechData 				= "GET6TechData"; 
		
	}
	
	public static class Workflow
	{
		public static String GETEDOTPublish			= "GET EDOT Publish";
		public static String GETEDOTClose			= "GET EDOT Close";
	}

	/**
	 * Static class for all Business Objects Properties
	 * 
	 * @author TCSL
	 *
	 */
	public static class Properties
	{
		public static String revision 				= "revision";
		public static String K1Date 				= "get6AppBuildRefDateSecond";
		public static String P1Date 				= "get6AppBuildRefDatePrimary";
		public static String orderNumber 			= "get6OrderNumber";
		public static String customerName 			= "get6CustomerName";
		public static String pmryProjNum 			= "get6PrimaryProjectNumber";
		public static String engrProductLine		= "get6EngrProdLine";
		public static String salesForceID 			= "get6SalesForceID";
		public static String secProjNum 			= "get6SecondaryProjectNumber";
		public static String enggSubGroup 			= "get6EngrSubGroup";
		public static String designSubGroup 		= "get6DesignSubGroup";
		public static String enggBackOff 			= "get6EngrBackOff";
		public static String desgnDuration 			= "get6DesignDuration";
		public static String engrDuration 			= "get6EngrDuration";
		public static String engrStartDate 			= "get6EngrStartDate";
		public static String engrReqDate 			= "get6EngrRequiredDate";
		public static String dsgnrReqDate 			= "get6DesignRequiredDate";
		public static String ActivityId 			= "get6ActivityId";
		public static String ActivityDesc 			= "get6ActivityDescription";
		public static String templateName 			= "get6SourceTemplate";
		public static String itemId 				= "item_id";
		public static String enggComments 			= "get6EngrComments";
		public static String enggDateChangeReason 	= "get6EngrRqdDateChangeReason";
		public static String designComments 		= "get6DesignComments";
		public static String designDateChangeReason = "get6DsgnRqdDateChangeReason";
		public static String designResource 		= "designResource";
		public static String engrResource 			= "engrResource";
		public static String engrPromiseDate 		= "get6EngrPromiseDate";
		public static String mainGroup 				= "mainGroup";
		public static String status 				= "Status";
		public static String ecr 					= "ECR";
		public static String ecn 					= "ECN";
		public static String technicalData 			= "techData";
		public static String autoclose 				= "get6IsAutoCloseRqd";
		public static String desPromiseDate 		= "get6DesignPromiseDate"; 
		public static String engrOrgProject 		= "get6EngrOrgProject";
		public static String designOrgProject 		= "get6DesignOrgProject"; 
		public static String closure 				= "CMClosure"; 
		public static String disposition 			= "CMDisposition"; 
	}
	
    /**
     * Static class for All ParticipantsType
     * 
     * @author TCSL
     */
	public static class Participants

	{
		public static String engrManager 			= "GET6SubgroupMgr";
		public static String engineer 				= "GET6EngrApproval";
		public static String coordinator 			= "GET6WorkAssignCo";
		public static String designer 				= "GET6Designer";
	}
	
	
	public static class Logger

	{
	public final static String LOG_DIR 				= "log_dir";
	public final static String LOG_DIR_DEFAULT 		= ".";
	}
	/**Static class for all Relation
	 * 
	 * @author TCSL
	 *
	 */
	public static class Relation
	{
		public static String desgnReleasePlanRelation 	= "GET6DsgnReleasePlanRelation";
		public static String desgnReleaseRelation 		= "GET6DsgnReleaseRelation";
		public static String desgnReleaseTechDataRel    = "GET6DsgnReleaseTargetsRel";
		public static String cmImplements				= "CMImplements"; 
		public static String cmImplementedBy			= "CMImplementedBy";  
		public static String cmHasImpItem			    = "CMHasImpactedItem";
		public static String cmHasSolItem			    = "CMHasSolutionItem";
		public static String hasParticipant			    = "HasParticipant";
	}
	
	/**Static class for all TemplateDesign
	 * 
	 * @author TCSL
	 *
	 */
	public static class TemplateScope
	{
		public static String taskData 				= "TaskData";
		public static String activityId 			= "ActivityId";
		public static String description			= "Description";
		public static String designComponentNo 		= "DesignComponentNo";
		public static String engrComponentNo 		= "EngrComponentNo";
		public static String backOff 				= "BackOff";
		public static String engrDuration 			= "EngrDuration";
		public static String designDuration 		= "DesignDuration";
	}
	
	public static class Query
	{
		public static String strgrpMemberQuery 		= "Admin - Group/Role Membership";
		public static String strworkflowQuery 		= "WF - Items In Process";
		public static String strECRQuery	 		= "Change Request Revision...";
	}
	
	public static class LOV
	{
		public static String strGroupProjectLov 	= "GET6GROUP_PROJECT_LOV";
	}
	
	public static class Category
	{
		public static String strEngr 				= "Engr";
		public static String strDesign 				= "Design";
	}
	
	public static class Role
	{
		public static String strDRE 				= "Design Release";
		public static String strEngrManager 		= "Engineering Manager";
		public static String strEngineer 			= "Engineer";
		public static String strDesignCoordinator 	= "Design Coordinator";
		public static String strDesigner 			= "Designer";
	}
	
	public static class ColorCode
	{
		public static String strRed 				= "Red";
		public static String strYellow				= "Yellow";
		public static String strBlue				= "Blue";
		public static String strWhite				= "White";
	}
}