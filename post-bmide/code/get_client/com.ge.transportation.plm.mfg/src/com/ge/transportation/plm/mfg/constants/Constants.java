package com.ge.transportation.plm.mfg.constants;

public class Constants {
	
	public class General {
		
		public static final String EMPTY_STRING_VALUE_C = "";
		public static final String DASH_STRING_VALUE_C = "-";
		public static final String DOT_STRING_VALUE_C = ".";
		public static final String CARET_STRING_VALUE_C = "^";
		public static final String ZERO_STRING_VALUE_C = "0";
		public static final String DOT_DELIMITER_VALUE_C = "\\.";
		public static final String MFG_ITEM_ID_REGEX = "-[a-zA-Z0-9-]{0,21}$";
		public static final String MFG_ITEM_NAME_REGEX = "^[a-zA-Z0-9-]{0,25}$";
		public static final String MFG_ITEM_DESC_REGEX = "^[a-zA-Z0-9-]{0,240}$";
		public static final String MFG_POLICY_FILE = "policy.xml";
		public static final String JAVA_IO_TMP_DIR = "java.io.tmpdir";
		public static final String MFG_POLICY_FILE_PATH = "resource/policy/policy.xml";
		public static final String RELEASE_STATUS_VALUE = "Released";
		
	}
	
	public class Role {
		
		public static final String strDBA = "DBA";
		public static final String strMfgProcessEngineer = "Mfg Process Engineer";
		public static final String strMfgProcessPlanner = "Mfg Process Planner";
		public static final String strMfgChangeControl = "Mfg Change Control";
	}
	
	public class ManufacturingAttributesDialog {
		
		public static final int ITEM_ID_COLUMN = 0;
		public static final int MAKE_BUY_COLUMN = 1;
		public static final int STOCK_MATERIAL_COLUMN = 2;
		public static final int STOCK_MATERIAL_QUANTITY_COLUMN = 3;
		public static final int PLANNING_CODE_COLUMN = 4;
		public static final int STRUCTURE_CODE_COLUMN = 5;
		public static final int iStockMaterialQuantitySpinnerDigit = 3;
		public static final int iStockMaterialQuantityBaseIncrement = 10;
		public static final int iStockMaterialQuantityMaxValue = 999999999;
		public static final int iClearIntProperty = 999999999;
		public static final String strTitle = " Manufacturing Attributes";
		public static final String strTitleDesc = "Items highlighted in green are already sent to Oracle";
		public static final String strColumnItemID = "Item ID";
		public static final String strColumnMakeBuy = " Make/Buy";
		public static final String strColumnStockMaterials = "Stock Material";
		public static final String strColumnStockMaterialQuantity = "Stock Material Quantity";
		public static final String strColumnPlanningCode = "Planning Code";
		public static final String strColumnStructureCode = "Structure Code";
		public static final String strNoneValue = "None";
		public static final String strMakeValue = "Make";
		public static final String strBuyValue = "Buy";
		public static final String strIconsPrefix = "resource/icons/";
		public static final String strIconsSuffix = ".png";
		public static final String strFormTypePrefPrefix = "GET6_";
		public static final String strFormTypePrefSuffix = "_MFG_Attr_Form_Type";
		public static final String strManufacturingAttributesSuffix = " Manufacturing Attributes";
	}
	
	public class StockMaterialAttributesDialog {
		
		public static final String strTitle = " Stock Material Attributes";
		public static final String strTitleDesc = "Set the Preferred Stock Material Value to assign it to Organization";
		public static final String strColumnItemID = "Item ID";
		public static final String strColumnPreferredStockMaterial = "Preferred Stock Material";
		public static final String strColumnStructureCode = "Structure Code";
		public static final String strNoneValue = "None";
		public static final String strTrueValue = "true";
		public static final String strFalseValue = "false";
		public static final String strIconsPrefix = "icons/";
		public static final String strIconsSuffix = ".png";
		public static final String strStockMaterialAttributesSuffix = " Stock Material Attributes";
	}
	
	public class BusinessObjects {
		
		
		public static final String strItemIDLabel = "ID:";
		public static final String strItem = "Item";
		public static final String strForm = "Form";
		public static final String strBLItem = "bl_item";
		public static final String strTCProject = "TC_Project";
		public static final String strGET6MCN = "GET6MCN";
		public static final String strGET6MfgPart = "GET6MfgPart";
		public static final String strGET6ElectPart = "GET6ElectPart";
		public static final String strGET6MechPart = "GET6MechPart";
		public static final String strGET6SoftwarePart = "GET6SoftwarePart";
		public static final String strGET6Operation = "GET6Operation";
		public static final String strGET6Machine = "GET6Machine";
		public static final String strGET6Operator = "GET6Operator";
		public static final String strGET6GenResource = "GET6GenResource";
		public static final String strGET6Process = "GET6Process";
		public static final String strGET6StockMtrl = "GET6StockMtrl";
		public static final String strGET6Material = "GET6Material";
		public static final String strGET6MfgOrgAttrForm = "GET6AbsMfgAttrForm";
		public static final String strGET6PartOrgRelation = "GET6PartOrgRelation";
		public static final String strGET6StockOrgPropsFrm = "GET6StockOrgPropsFrm";
		public static final String strGET6StockHasOrgPropsAttri = "GET6StockHasOrgPropsAttri";
		public static final String strGET6MadeFromMatl = "GET6MadeFromMatl";
		public static final String strGET6HasStockMatl = "GET6HasStockMatl";
		public static final String strMfg0BvrProcess = "Mfg0BvrProcess";
		public static final String strGET6NCMachining = "GET6NCMachining";
		
		public class Properties {
			
			public static final String strObjectTypeVal = "objectType";
			public static final String strSelectionVal = "selection";
			public static final String strOwningProject = "owning_project";
			public static final String strget6EngMakeBuy = "get6EngMB";
			public static final String strget6MakeBuy = "get6MakeBuy";
			public static final String strget6OrgPreferredStock = "get6OrgPreferredStock";
			public static final String strget6PlanningCode = "get6PlanningCode";
			public static final String strget6StockMaterial = "get6StockMaterial";
			public static final String strget6StockMaterialQuantity = "get6StockMtrlConsumedQty";
			public static final String strget6StructureCode = "get6StructureCode";
			public static final String strget6ItemPublishDate = "get6ItemPublishDate";
			public static final String strget6BOMPublishDate = "get6BOMPublishDate";
			public static final String strget6IsMfgAttrModT4OXfer = "get6isMfgAttrModT4OXfer";
			public static final String strObjectName = "object_name";
			public static final String strItemID = "item_id";
			public static final String strProjectID = "project_id";
			public static final String strProjectList = "project_list";
			public static final String strProjectName = "project_name";
			public static final String strObjectString = "object_string";
			public static final String strRevisionList = "revision_list";
			public static final String strRelStatus = "release_status_list";
			public static final String strProcessStage = "process_stage";
		}
		
		public class lov {
			
			public static final String strListOfValues = "ListOfValues";
			public static final String strMakeBuy = "Make Buy";
		}
		
		public class Operation {
			
			public static final String strCreateOperation = "Create";
		}
	}
		
	public class ReportStockBOM
	{
		
		public static final String ITEMIDS = "item_id";
		public static final String FINDNO = "bl_sequence_no";
		public static final String MATERIALTRELN = "GET6MadeFromMatl";
		public static final String BOMWINDOW = "BOMWindow";
		public static final String QTY = "bl_quantity";
		public static final String PACKCOUNT = "bl_pack_count";
		public static final String REV = "item_revision_id";
		public static final String PARTNAME = "object_name";
		public static final String PARENTDETAILS = "bl_formatted_parent_name";
		public static final String UOM = "uom_tag";
		public static final String ENGMAKEBUY = "get6EngMB";
		public static final String RELEASESTATUS = "release_status_list";
		public static final String REVTYPE = "object_type";
		public static final String MANUFATTRFORMRELN = "GET6PartOrgRelation";
		public static final String PROJMAKEBUY = "get6MakeBuy";
		public static final String STRCODE = "get6StructureCode";
		public static final String STOCKMATERIALTRELN = "GET6HasStockMatl";
		public static final String SEP = "?";
		public static final String NA = "NA";
		public static final String MADEFROMPARTRELN = "GET6MadeFromPart";
		public static final String REVRULES = "Revision Rule";
		public static final String ITEMIDREVID = "ItemId/Rev";
		public static final String BOMLINE = "bl_indented_title";
		public static final String STOKMATERIALPROP = "get6StockMaterial";
		public static final String YES = "Yes";
		public static final String NO = "No";
		public static final String PROJNAME = "object_string";
		public static final String OWNINGPROJ = "owning_project";
		public static final String HOME = "Home";
		public static final String LEVEL = "Level";
		public static final String REVS = "Rev";
		public static final String QTYS = "Qty";
		public static final String PARTNAMES = "Part Name";
		public static final String FINDNOS = "Find No";
		public static final String PACKCOUNTS = "Pack Count";
		public static final String PARENTREVNAME = "Parent/Rev-Name";
		public static final String UOMS = "Uom";
		public static final String ENGMAKEBUYS = "Eng-Make/Buy";
		public static final String RELSTAT = "Release Status";
		public static final String PROJMAKEBUYS = "-Make/Buy";
		public static final String ITEMTYPE = "Rev Type";
		public static final String STRCODES = "Structure Code";
		public static final String ITEMID = "Item Id";
		public static final String BOMSTOCK = "Report_MBOM_LOCAL";
		public static final String BOMLINES = "BOM Line";
		public static final String RULECONF = "Rule Configured";
		public static final String GRR = "GRR-Grove City Engine Remanufacturi";
		public static final String GRRID = "GRR";
		public static final String GRVID = "GRV";
		public static final String GRV = "GRV-Grove City Engine Manufacturing";
		public static final String ISMADEFROMPART = "Is Made From Part";
		public static final String GRVWIP = "GET GRV WIP";
		public static final String ENGREVTYPE = "GET Engineering Part Revision";
		public static final String MFGREVTYPE = "GET Manufacturing Part Revision";
		public static final String STQTY = "get6StockMtrlConsumedQty";
		public static final String TEMPDIR = "java.io.tmpdir";
		public static final String STOCKBOMTITLE = "GET BOM STOCKMTL Report";
	}
		
}