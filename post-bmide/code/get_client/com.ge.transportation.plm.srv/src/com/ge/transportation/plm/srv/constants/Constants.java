package com.ge.transportation.plm.srv.constants;

public class Constants {
	
	public class General {
		
		public static final String EMPTY_STRING_VALUE_C = "";
		public static final String JAVA_IO_TMP_DIR = "java.io.tmpdir";

	}
	
	public class Role {
		
		public static final String strSrvEngineerManager = "Services Engineering Manager";
		public static final String strSrvEngineer = "Services Engineer";
		public static final String strEngineer = "Engineer";
		public static final String strDesigner = "Designer";
		public static final String strDBA = "DBA";
	}
	
	public class ManufacturingAttributesDialog {
		
		public static final String strTitle = "Service Attributes";
		public static final String strTitleDesc = "Add/Update Service Attributes";
		public static final String strColumnItemID = "Item ID";
		public static final String strColumnName = "Engine Family";
		public static final String strColumnServiceable = " Serviceable";
		public static final String strColumnSerialize = "Serialized";
		public static final String strColumnRepairable = "Repairable";
		public static final String strColumnPositionTrack = "Position Tracked";
		public static final String strColumnStructureCode = "Service Item Type";
		public static final String strColumnTierType = "Tier Type";
		public static final String strColumnCompID = "Component ID";
		public static final String strIconsPrefix = "resource/icons/";
		public static final String strIconsSuffix = ".png";
		public static final String strManufacturingAttributesSuffix = "Service Attributes";
		public static final String strTrueValue = "True";
		public static final String strFalseValue = "False";
		
	}
	
	public class BusinessObjects {
		
		public static final String strItemIDLabel = "ID:";
		public static final String strItem = "Item";
		public static final String strForm = "Form";
		public static final String strBLItem = "bl_item";
		
        public static final String strGET6MfgPart = "GET9SrvPart";
		public static final String strGET6MechPartRev = "GET6MechPartRevision";
		public static final String strGET6ObsForm = "GET6SupersedureForm";
		public static final String strGET6SrvForm = "GET9SerAttrForm";
		public static final String strGET6ObsRel = "GET6SupersededBy";
		public static final String strGET6SrvAttrForm = "GET9SerAttrForm";
		public static final String strGET6SrvRelation = "GET9ServFormAtt";
		public static final String strGET6SrvPart = "GET9SrvPart"; 
		public static final String strGET6SrvPartRevi = "GET9SrvPartRevision";
		public static final String strGET6Functional = "GET9FnctLvl";
		public static final String strGET6ZonalPart = "GET9ZnlLvl";
		public static final String strGET6SrvPartRev = "Srv Part Revision";
		public static final String strGET6defaultrel = "GET6MechPartRevision_default_relation";
        public static final String strGET6Srvdefaultrel = "GET9SrvPartRevision_default_relation";
		public static final String strGET6MechPart = "GET6MechPart";
		public static final String strGET6MechPartRevision = "GET6MechPartRevision";
		
		public class Properties {
			
			public static final String strObjectTypeVal = "objectType";
			public static final String strSelectionVal = "selection";
			public static final String strRelationVal = "pasteRelation";
			public static final String strParentVal = "parentComponents";
			
			public static final String strObjectName = "object_name";
			public static final String strItemID = "item_id";
			public static final String strObjectString = "object_string";
			public static final String strRevisionList = "revision_list";
			
			public static final String strItemRevId = "item_revision_id";
			public static final String strIPClassification = "ip_classification";
			public static final String strCurrentRevId = "current_revision_id";
			public static final String strObjectTpe = "object_type";
			
			public static final String strget6Serviceable = "get9Serviceable";
			public static final String strget6Repairable = "get9Repairable";
			public static final String strget6Serialize = "get9Serialized";
			public static final String strget6PositionTracked = "get9PositionTracked";
			public static final String strget6ServiceItemType = "get9ServiceItemType";
			public static final String strget6EngineFamily = "get9EngineFamily";
			public static final String strget6TierType = "get9TierType";
			public static final String strget6CompID = "get9ComponentID";
			public static final String strEngrProdLine = "get6EngrProdLine"; 
			public static final String strECCN = "get6ECCN";
			public static final String strECC = "get6ECC";
			public static final String strECCNSource = "get6ECCNSource";
			public static final String strCriticalPart = "get6CriticalPart";
			public static final String strObjEvidence = "get6ObjEvidence";
			public static final String strHomologation = "get6Homologation";
			public static final String strCCC = "get6CCC";
			public static final String strCTQ = "get6CTQ";
			public static final String strDataModel = "get6DataModel";
			public static final String strEngMB = "get6EngMB";
			public static final String strObjWt = "get6ObjWt";
			public static final String strObjWtUOM = "get6ObjWtUOM";
			public static final String strOverallHeight = "get6OverallHeight";
			public static final String strOverallLength = "get6OverallLength";
			public static final String strOverallWidth = "get6OverallWidth";
			public static final String strvOerallUOM = "get6OverallUOM";
			
			public static final String strEngineFamily = "get9EngineFamily";
			public static final String strParentID = "get9ParentID";
			public static final String strPositionTracked = "get9PositionTracked";
			public static final String strRepairable = "get9Repairable";
			public static final String strSerialized = "get9Serialized";
			public static final String strServiceable = "get9Serviceable";
			public static final String strServiceItemType = "get9ServiceItemType"; 
			public static final String strTierType = "get9TierType";
			public static final String strCompID = "get9ComponentID"; 
		}
		public class Relations {
			public static final String strServFormRel = "GET9ServFormAtt";
			public static final String strContents = "contents";
		}	
	}

	public class ServicesDialogUI {
		public static final String strTitle = "Create GET Service Part From Engineering Part";
		public static final String strLabelNameTitle = "Name*  ";
		public static final String strLabelId = "Item ID*  ";
		
		public static final String strMsg1 = "Please Enter Item ID";
		public static final String strMsg2 = "Please Enter Name";
		public static final String strMsg3 = "Created GET Service Part: ";
		public static final String strMsg4 = "GET Service Form is missing under selected Engineering Part revision";
		public static final String strMsg5 = "This operation cannot be perfomed either due to invalid object or invalid group/role";
		public static final String strMsg6 = "Valid Objects is\n	-GET Engineering Part Revision\n \nInvalid Group/Role, Allowed Roles are \n\n	-Services Engineering Manager or Services Engineer";
		public static final String strMsg7 = "Invalid Group/Role, Allowed Roles are \n\n	-Services Engineer\n	-Services Engineering Manager";
		public static final String strMsg8 = "Select an GET Engineering Part";
		public static final String strMsg9 = "Valid Objects are\n -GET Engineering Part Revision\n -GET Service Part Revision" ;
	}
	
}