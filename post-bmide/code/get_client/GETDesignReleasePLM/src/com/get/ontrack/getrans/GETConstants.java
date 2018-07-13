  
package com.get.ontrack.getrans;

/**
 * This is a Class for all OOTB String Constants
 *
 * @author TCSL
 */
public class GETConstants 
{
    /**
     * Static class for all character symbols
     * 
     * @author TCSL
     */
	public static class Symbols
	{
		public static String strDot = ".";
		public static String strNone = "None";
		public static String strEmptyString = "";
		public static String strJavaTempDir = "java.io.tmpdir";
		public static String strForwardSlash = "/";
		public static String strDoubleForwardSlash = "//";
		public static String strColon = ":";
		public static String strHyphenDelimiter = "-";
		public static String strDotSplitDelimiter = "\\.";
		public static String strDoublePipeDelimiter = "||";
		public static String strSingleStarDelimiter = "*";
		public static String strDoubleStarDelimiter = "**";
		public static String strNewLineChar = "\n";
	}

	/**
     * Static class for all OOTB queries
     * 
     * @author TCSL
     */
	public static class Query 
	{
		public static String strItemQuery = "Item...";
		public static String strItemRevisionQuery = "Item Revision...";
		public static String strDatasetQuery = "Dataset...";
		public static String strGeneralQueryName = "General...";
		public static String strGET9PartQuery = "GETDRSItem";
		public static String strGET9ChangeOrder = "GET9ChangeOrder";
		public static String strGET9User = "GET9User";
		public static String strGET9LoggedInUsers = "GET9LoggedInUsers";
		public static String strName = "Name";
		public static String strTypeName = "Type";
		public static String strProjectID = "Project ID";
		public static String EngrSubGroup = "EngineeringSubGroup";
		public static String EngineerResource = "EngineerResource";
		public static String DesignResource = "DesignResource";
		public static String strEdotID = "Edot ID";
		public static String strClassID = "Class ID";
		public static String strItemIDName = "Item ID";
		public static String strDatasetID = "Dataset ID";
		public static String strDateReleasedFrom = "Date Released From";
		public static String strDateReleasedTo = "Date Released To";
		public static String strGET9PartValue = "Part";
		public static String strGET9ChangeOrderValue = "TCM Released";
        public static String userQuery = "__WEB_find_user";
        public static String userId = "User ID";
        public static String personQuery = "__WEB_find_person";
        public static String personName = "Person Name";
        public static String grpByNameQuery = "GroupByName";
        public static String name = "Name";
        public static String roleByNameQuery = "RoleByName";
        public static String grpMemberQuery = "__WEB_group_members";
        public static String activeGrpMemberQuery = "__ACTIVE_group_members";
        public static String queryGroupMember = "__EINT_group_members";
        public static String edotQuery = "GETEDOTQuery";
        public static String group = "Group";
        public static String role = "Role";
        public static String user = "User";
        public static String status = "Status";
        public static String userStatus = "User Status";
        public static String userGroupMemberQuery = "__WEB_user_members";
        public static String userID = "UserID";
	}

	/**
     * Static class for all OOTB preferences
     * 
     * @author TCSL
     */
	public static class Preferences 
	{
		public static String strFMSBootStrapURL = "Fms_BootStrap_Urls";
	}

	/**
     * Static class for all OOTB Business Objects
     * 
     * @author TCSL
     */
	public static class BusinessObjects 
	{
		public static String strPDF = "PDF";
		public static String strText = "Text";
		public static String strRaw = "Raw";
		public static String strPart = "Part";
		public static String strMSWord = "MSWord";
		public static String strMSExcel = "MSExcel";
		public static String strDocument = "Document";
		public static String strMSPowerPoint = "MSPowerPoint";
		public static String strImanFile = "ImanFile";
		public static String strDataset = "Dataset";
		public static String imanType = "ImanType";
		public static String imanRelation = "ImanRelation";
		public static String item = "Item";
		public static String itemRevision = "ItemRevision";
		public static String group = "Group";
		public static String groupMember = "GroupMember";
		public static String role = "Role";
		public static String user = "User";
		public static String epmTask = "EPMTask";
		public static String epmDoTask = "EPMDoTask";
		public static String epmReviewTask = "EPMReviewTask";
		public static String epmPerformTask = "EPMPerformSignoffTask";
		
		public static String releaseStatus = "ReleaseStatus";
//		public static String GET6DesignRelRev = "GET6DsgnReleaseRevision";

		/**
	     * Static class for all OOTB Business Object Properties
	     * 
	     * @author TCSL
	     */
		public static class Properties 
		{
			public static String strItemID = "item_id";
			public static String strCurrentID = "current_id";
			public static String strItemRevID = "item_revision_id";
			public static String strCreationDate = "creation_date";
			public static String strUserName = "user_name";
			public static String strOwningUser = "owning_user";
			public static String strObjectName = "object_name";
			public static String strObjectDesc = "object_desc";
			public static String strLastModDate = "last_mod_date";
			public static String strObjectType = "object_type";
			public static String strRefListName = "ref_list";
			public static String strDatasetType = "dataset_type";
			public static String strRevisionList = "revision_list";
			public static String strDatasetTypeName = "datasettype_name";
			public static String strOriginalFileName = "original_file_name";
			public static String strImanSpecification = "IMAN_specification";
			public static String strImanReference = "IMAN_reference";
			public static String strImanManifestation = "IMAN_manifestation";
			public static String strIMFFileExt = "file_ext";
			//public static String strItemRevisionList = "revision_list";
			public static String strDateReleased = "date_released";
			public static String strPrinterName = "printer_name";
			public static String strName = "name";
			public static String strProviderName = "provider_name";
			public static String strServiceName = "dispatcher_svc_name";
			public static String typeName = "type_name";
			public static String relationType = "relation_type";
			public static String typeString = "type_string";
			public static String itemsTag = "items_tag";
			public static String uomTag = "uom_tag";
			public static String ipClassification = "ip_classification";
            public static String roleName = "role_name";
            public static String person = "person";
            public static String defaultGroup = "default_group";
            public static String displayName = "display_name";
            public static String loginGroup = "login_group";
            public static String strOwningGroup = "owning_group";
            public static String listOfRoles = "list_of_role";
            public static String ipClearance = "ip_clearance";
            public static String status = "status";
            public static String defaultRole = "default_role";
            public static String group = "group";
            public static String role = "role";
            public static String user = "user";
            public static String theGroup = "the_group";
            public static String theRole = "the_role";
            public static String fullName = "full_name";
            public static String uid = "uid";
            public static String newstuff_folder = "newstuff_folder";
            public static String userid = "user_id";
            public static String processStageList = "process_stage_list";
            public static String relList = "release_status_list";
            public static String objectString = "object_string";
             public static String currentName = "current_name";
             public static String taskName = "task_name";
             public static String taskState = "task_state";
             public static String userAllSignoff = "user_all_signoffs";
             
            
		}
	}
}
