package com.get.ontrack.common;


public class PLMConstants {
	
	
	public static String GET_Part = "GET Part";
	
	public static String User = "User";
	public static String Person = "Person";
	public static String ListOfValuesTagExtent = "ListOfValuesTagExtent";
	public static String person = "person";
	public static String PA6 = "PA6";
	public static String USER_NAME = "USER_NAME";
	
	public static String current_id = "current_id";
	public static String owning_user = "owning_user";
	public static String current_name = "current_name";
	public static String creation_date = "creation_date";
	public static String success = "Success";
	public static String fail = "Fail";
	public static String designAttachSuccess = "Design Release attached successfully";
	public static String designUpdateSuccess = "Design Release updated successfully";
	public static String getGroupList ="Group List Populated";
	public static String deletedEdot ="Edot Deleted";
	public static String getProject = "GET Project";
	public static String item = "Item";
	public static String lovVal = "lov_values";
	public static String designReleaseTemplate = "Design Release Template";
	public static String designReleaseTemplateID = "DESIGN_RELEASE_TEMPLATE";
	public static String designRelease= "Design Release Deleted"; 
	public static String designReleaseError= "Problem with deletion of Design Release";
	
	
//	public static String Host = "http://g2ua5392t8ge.logon.ds.ge.com:8090/tc"; //Local 
//	public static String Host = "http://cingetplm025bc.cloud.ge.com:8080/tc"; //PROTO-10
//	public static String Host ="http://vdcgld02589.ics.cloud.ge.com:8080/tc/"; // DEV-INT
//	public static String Host = "http://vdcgld03041.ics.cloud.ge.com:8080/tc"; //SIT
	
	public static String Host = "http://vdcald04459.ics.cloud.ge.com:8080/tc"; //SSO host http://Vdcald04459.ics.cloud.ge.com/tc
	public static String ssoURL = "http://vdcald04459.ics.cloud.ge.com/tc_sso_login"; //Dev
	public static String ssoAPPID = "Teamcenter"; //Dev
	
		
	/**Static class for all RequestMappings
	 * 
	 * @author TCSL
	 *
	 */
	public static class RequestMappings
	{
		public static String login = "/login";
	}
	
	/**Static class for all Controller objects
	 * 
	 * @author TCSL
	 *
	 */
	public static class Objects
	{
		public static String user = "user";
		public static String userHome = "UserHome";
		public static String engManageruserHome = "EngManagerHome";
		public static String enguserHome = "EngHome";
		public static String designcorduserHome = "DesigncordHome";
		public static String projectsList = "projectsList";
		public static String username = "username";
		public static String templatesMap = "templatesMap";
		public static String templatesName = "templatesName";
		public static String projectsDataMap = "projectsDataMap";
		public static String templateScopeMap = "templateScopeMap";
		public static String response = "response";
		public static String GETUser = "GETUser";
		public static String home = "Home";
		public static String home1 = "Home1";
		public static String p1Date = "Sat Jun 25 11:39:37 EDT 2016";
		public static String pleaseSelect = "Please Select";
		public static String pleaseSelectValue = "-1";
		public static String error = "Error";
		public static String templatesFiles = "templatesFiles";
		public static String tempDesignReleaseList = "tempDesignReleaseList";
		public static String group = "group";
		public static String role = "role";
		
	}
}

