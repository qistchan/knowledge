package com.ge.transportation.plm.cam.constants;

public class Constants {
	
	public class General {
		
		public static final String EMPTY_STRING_VALUE_C = "";
		public static final String DASH_STRING_VALUE_C = "-";		
	}
	
	public class Role {
		
		public static final String strMfgProcessPlanner = "Mfg Process Planner";		
	}
	
	public class CamUtilsDialogUI {
		public static final String strTitle = "Create New CAM Item";
		public static final String strPasteIcon = "mfgIdPaste.ICON";
		public static final String strFindIcon = "find.ICON";
		public static final String strGRVSite = "GROVECITY";
		
		public static final String strLabelCastingForging = "Enter Casting/Forging Part Number";
		public static final String strLabelFixturePartNumber = "Enter Fixture Part Number";
		public static final String strLabelSetupNumber = "Enter Setup Number*";
		public static final String strLabelMachineId = "Enter Machine ID*";
		public static final String strLabelSelectSite = "Select Site*";
		public static final String strLabelCNCTitle = "Enter CNC Item Title*";
		public static final String strLabelCADModelId = "CAD Model ID*";
		public static final String strLabelRevIdstar = "REVID*";
		public static final String strLabelRevId = "REVID";
		
		public static final String strEnvVar1 = "GETS_CAM_BIN_DIR";
		
		public static final String strMsg1 = "Save the changes before exiting?";
		public static final String strMsg2 = "Please copy anything";
		public static final String strMsg3 = "Nothing On Clipboards";
		public static final String strMsg4 = "Please select site before choosing a machine";
		public static final String strMsg5 = "Please select site";
		public static final String strMsg6 = "Please select Machine ID";
		public static final String strMsg7 = "Please enter Setup Number";
		//public static final String strMsg8 = "Please Enter MFG Item Title"; 
		public static final String strMsg8 = "Please Enter CNC Item Title"; //Modified //Pradeep-20July2017
		public static final String strMsg9 = "exception while getting group and role";
		public static final String strMsg10 = "Unable to get Group & Role";
		public static final String strMsg11 = "UGMASTER Dataset missing under selected Item";
		public static final String strMsg12 = "Manufacturing Item already exists";
		public static final String strMsg13 = "Manufacturing Item already exists in Teamcenter But not in Database. Please contact Admin team";
		public static final String strMsg14 = "Unable to check DB for Manufacturing Item existence";
		public static final String strMsg15 = "UGMASTER Dataset missing under selected Item revision";
		public static final String strMsg16 = "Not in Database, But Item exists in Teamcenter";
		public static final String strMsg17 = "Please select Item/Item Revision";
		public static final String strMsg18 = "Machine ID must follow XX123 format. Where XX - Any Letters. 123 - Any Number";
		public static final String strMsg19 = "Title contains space in between. Please enter Title without space";
		
		public static final String strEnvError1 = "ERROR - GETS_CAM_BIN_DIR Environment variable not set properly. Please check";
	}
	
	public class BusinessObjects {
		
		public static final String strGET6NCMachining = "GET6NCMachining";
		public static final String strGET6NCMachiningRevision = "GET6NCMachiningRevision";
		public static final String strDataset = "Dataset";
		public static final String strUGMaster = "UGMASTER";
		public static final String strGET6MechPart = "GET6MechPart";
		public static final String strGET6MechPartRevision = "GET6MechPartRevision";
		
		public class Properties {
			
			public static final String strObjectTypeVal = "objectType";
			public static final String strObjectName = "object_name";
			public static final String strObjectDesc = "object_desc";
			public static final String strItemID = "item_id";
			public static final String strObjectString = "object_string";
			public static final String strItemRevId = "item_revision_id";
			public static final String strIPClassification = "ip_classification";
			public static final String strCurrentRevId = "current_revision_id";
			public static final String strObjectTpe = "object_type";
			public static final String strReleaseStatusList = "release_status_list";
		}
		
		public class Relations {
			public static final String strSpecification = "IMAN_specification";
			public static final String strContents = "contents";
		}		
		
		public class Operation {
			
			public static final String strCreateOperation = "Create";
		}
		
	}
}