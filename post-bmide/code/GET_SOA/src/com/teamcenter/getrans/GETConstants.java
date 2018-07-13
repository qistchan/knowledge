
package com.teamcenter.getrans;

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
		public static final String strDot = ".";
		public static final String strNone = "None";
		public static final String strEmptyString = "";
		public static final String strJavaTempDir = "java.io.tmpdir";
		public static final String strForwardSlash = "/";
		public static final String strDoubleForwardSlash = "//";
		public static final String strColon = ":";
		public static final String strHyphenDelimiter = "-";
		public static final String strDotSplitDelimiter = "\\.";
		public static final String strDoublePipeDelimiter = "||";
		public static final String strSingleStarDelimiter = "*";
		public static final String strDoubleStarDelimiter = "**";
		public static final String strNewLineChar = "\n";
	}

	/**
     * Static class for all OOTB queries
     * 
     * @author TCSL
     */
	public static class Query 
	{
		public static final String strItemQuery = "Item...";
		public static final String strItemRevisionQuery = "Item Revision...";
		public static final String strDatasetQuery = "Dataset...";
		public static final String strGeneralQueryName = "General...";
		public static final String strProjectsQueryName = "Projects...";
		public static final String userGroupMemberQuery = "__WEB_user_members";
		public static final String strGET9PartQuery = "GETDRSItem";
		public static final String strGET9ChangeOrder = "GET9ChangeOrder";
		public static final String strGET9User = "GET9User";
		public static final String strGET9LoggedInUsers = "GET9LoggedInUsers";
		public static final String strName = "Name";
		public static final String strTypeName = "Type";
		public static final String strClassID = "Class ID";
		public static final String strItemIDName = "Item ID";
		public static final String strDatasetID = "Dataset ID";
		public static final String strDateReleasedFrom = "Date Released From";
		public static final String strDateReleasedTo = "Date Released To";
		public static final String strGET9PartValue = "Part";
		public static final String strGET9ChangeOrderValue = "TCM Released";
        public static final String userQuery = "__WEB_find_user";
        public static final String userId = "User ID";
        public static final String personQuery = "__WEB_find_person";
        public static final String personName = "Person Name";
        public static final String grpByNameQuery = "GroupByName";
        public static final String name = "Name";
        public static final String roleByNameQuery = "RoleByName";
        public static final String grpMemberQuery = "__WEB_group_members";
        public static final String activeGrpMemberQuery = "__ACTIVE_group_members";
        public static final String group = "Group";
        public static final String role = "Role";
        public static final String user = "User";
        public static final String status = "Status";
        public static final String userStatus = "User Status";
        public static final String userID = "UserID";
        public static final String projectId = "Project ID";
	}

	/**
     * Static class for all OOTB preferences
     * 
     * @author TCSL
     */
	public static class Preferences 
	{
		public static final String strFMSBootStrapURL = "Fms_BootStrap_Urls";
	}

	/**
     * Static class for all Teamcenter Groups
     * 
     * @author TCSL
     */
	public static class Groups
	{
	    public static final String strEngineeringGroup = "Engineering";
	}

    /**
     * Static class for all Teamcenter Groups
     * 
     * @author TCSL
     */
    public static class Roles
    {
        public static final String strDesignerRole = "Designer";
    }

    /**
     * Static class for all LOV Values
     * 
     * @author TCSL
     */
    public static class LOV
    {
        /**
         * IP Classification LOV Values
         */
        public static final String IP_CLASS_INTERNAL_LOV_VALUE = "GE - Internal";
        public static final String IP_CLASS_CONFIDENTIAL_LOV_VALUE = "GE - Confidential";
        public static final String IP_CLASS_RESTRICTED_LOV_VALUE = "GE - Restricted";
    }

	/**
     * Static class for all OOTB Business Objects
     * 
     * @author TCSL
     */
	public static class BusinessObjects 
	{
		public static final String strPDF = "PDF";
		public static final String strText = "Text";
		public static final String strRaw = "Raw";
		public static final String strPart = "Part";
		public static final String strMSWord = "MSWord";
		public static final String strMSExcel = "MSExcel";
		public static final String strDocument = "Document";
		public static final String strMSPowerPoint = "MSPowerPoint";
		public static final String strImanFile = "ImanFile";
		public static final String strDataset = "Dataset";
		public static final String imanType = "ImanType";
		public static final String imanRelation = "ImanRelation";
		public static final String item = "Item";
		public static final String itemRevision = "ItemRevision";
		public static final String group = "Group";
		public static final String groupMember = "GroupMember";
		public static final String person = "Person";
		public static final String role = "Role";
		public static final String user = "User";
		/**
	     * Static class for all OOTB Business Object Properties
	     * 
	     * @author TCSL
	     */
		public static class Properties 
		{
			public static final String strItemID = "item_id";
			public static final String strItemRevID = "item_revision_id";
			public static final String strCreationDate = "creation_date";
			public static final String strUserID = "user_id";
			public static final String strUserName = "user_name";
			public static final String strOwningUser = "owning_user";
			public static final String strObjectName = "object_name";
			public static final String strObjectDesc = "object_desc";
			public static final String strLastModDate = "last_mod_date";
			public static final String strObjectType = "object_type";
			public static final String strObjectString = "object_string";
			public static final String strRefListName = "ref_list";
			public static final String strDatasetType = "dataset_type";
			public static final String strRevisionList = "revision_list";
			public static final String strDatasetTypeName = "datasettype_name";
			public static final String strOriginalFileName = "original_file_name";
			public static final String strImanSpecification = "IMAN_specification";
			public static final String strImanReference = "IMAN_reference";
			public static final String strImanManifestation = "IMAN_manifestation";
			public static final String strIMFFileExt = "file_ext";
			public static final String strItemRevisionList = "revision_list";
			public static final String strLastModUser = "last_mod_user";
			public static final String strDateReleased = "date_released";
			public static final String strPrinterName = "printer_name";
			public static final String strName = "name";
			public static final String strProviderName = "provider_name";
			public static final String strPA5 = "PA5";
			public static final String strPA9 = "PA9";
			public static final String strServiceName = "dispatcher_svc_name";
			public static final String typeName = "type_name";
			public static final String relationType = "relation_type";
			public static final String typeString = "type_string";
			public static final String itemsTag = "items_tag";
			public static final String uomTag = "uom_tag";
			public static final String ipClassification = "ip_classification";
            public static final String roleName = "role_name";
            public static final String person = "person";
            public static final String defaultGroup = "default_group";
            public static final String displayName = "display_name";
            public static final String loginGroup = "login_group";
            public static final String strOwningGroup = "owning_group";
            public static final String listOfRoles = "list_of_role";
            public static final String ipClearance = "ip_clearance";
            public static final String status = "status";
            public static final String defaultRole = "default_role";
            public static final String group = "group";
            public static final String role = "role";
            public static final String user = "user";
            public static final String theGroup = "the_group";
            public static final String theRole = "the_role";
            public static final String fullName = "full_name";
            public static final String projectId = "project_id";
            public static final String projectName = "project_name";
            public static final String projectDesc = "project_desc";
            public static final String isActive = "is_active";
            public static final String isVisible = "is_visible";
            public static final String useProgramSecurity = "use_program_security";
		}
	}
}
