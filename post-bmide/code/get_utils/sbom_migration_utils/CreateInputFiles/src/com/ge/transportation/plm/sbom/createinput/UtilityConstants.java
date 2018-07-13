/***************************************************************************************
 * File Name		:	UtilityConstants.java
 * 
 * Description		:	This class set various Global Constants for the CreateInputFiles
 * 						class.
 *    
 * Author			:	Nisarg Shah (Capgemini India)
 * 
 * Creation Date   	:   Oct 2017
 **************************************************************************************/
package com.ge.transportation.plm.sbom.createinput;

import java.io.Writer;
import java.util.Arrays;
import java.util.List;

import org.apache.poi.ss.usermodel.DataFormatter;

/**
 * This class set various Global Constants for the CreateInputFiles class.
 */
public class UtilityConstants
{
	protected static final String INPUT_FILES_DIR = "Input_Files\\";
	protected static final String INPUT_DIR_NAME = "Input_Files";
	protected static final String LOGS_DIR_NAME = "Logs";
	protected static final String DIR_CREATION_ERROR = "\nError while creating directory : ";
	protected static final String DUPLICATE_ENTRY = "\n##### Duplicate Entry : ";
	
	//protected static final String INPUT_FILE_NAME = INPUT_FILES_DIR + "DataLoader.xlsx";
	protected static final String DEL = "|";
	protected static final String ZERO = "0";
	protected static final String ONE = "1";
	protected static final String BLANK = "";
	protected static final String SEMICOLON = ";";
	protected static final String COMMA = ",";
	protected static final String SPACE = " ";
	protected static final String SEMICOLON_SPACE = "; ";
	protected static final String SPACE_SEMICOLON = " ;";
	protected static final String TIER = "Tier";
	protected static final String NEW_LINE = "\r\n";
	protected static final String HASH_SIGN = "#";
	protected static final String EXCEPTION = "Exception : ";
	protected static final String STR_INPUT_FILE_NAME = "Input File Name:";
	protected static final String STR_OWNING_USER = "Owning User:";
	protected static final String STR_OWNING_GROUP = "Owning Group:";
	protected static final List<String> HELP_ARGS = Arrays.asList("-help","-h","-Help","-H","-HELP",BLANK);
	protected static final String INPUT_FILES_DIR_CREATON_ERROR = "\nError : Could not create directory:"
			+ INPUT_FILES_DIR + "\nPlease create it manually.";
	protected static final String EACH = "each";
	protected static final String MODEL_BASED = "Model Based";
	protected static final String MB = "MB";
	protected static final String MODEL_CENTRIC = "Model Centric";
	protected static final String MC = "MC";
	protected static final String TOTAL_SERVICE_PARTS = "\nTotal Service Parts = ";
	protected static final String TOTAL_DOCUMENTS_TO_ATTACH = "Total Documents to attach = ";
	protected static final String TOTAL_DRAWINGS_TO_ATTACH = "Total Drawings to attach = ";
	protected static final String TOTAL_PURCHSPEC_TO_ATTACH = "Total PurchSpecs to attach = ";
	protected static final String TOTAL_MADEFROM_TO_ATTACH = "Total MadeFrom to attach = ";
	protected static final String TOTAL_ALTERNATE_PARTS_TO_ADD = "Total Alternate Parts to add = ";
	protected static final String TOTAL_ENG_PARTS_FOR_SERVICE_FORM_CREATON = "Total Engineering Parts for Service Form Creation = ";
	protected static final String START_TIME = "Utility Start Time = ";
	protected static final String END_TIME = "Utility End Time = ";
	protected static final String STRUCTURE_START_TIME = "Structure Start Time = ";
	protected static final String TOTAL_STRUCTURES = "Total Structures = ";
	protected static final String STRUCTURE_END_TIME = "Structure End Time = ";
	protected static final String ERROR_STRING = "######## Error ########";
	protected static final String LINE_SEPERATOR = NEW_LINE
			+ "====================================================================" + NEW_LINE;
	protected static final int AVOID_COLUMNS[] = { 7, 8, 9, 10, 11, 14, 34, 39, 44, 49 };
	protected static final int SERVICE_PART_COLUMNS[] = { 8, 9, 10, 11, 12, 15, 35, 40, 45, 50 };
	/* Line Types */
	protected static final String EXISTING_ENG_PART = "Existing Engineering Part";
	protected static final String NEW_SERVICE_PART = "New Service Part";
	protected static final String PART_BULLETIN_BOM_ITEM = "Part Bulletin BOM Item";

	protected static final String TYPE_REAL_NAME = "GET9SrvPart"; // ServicePart
	protected static final String DEFAULT_REVISION_ID = "0";
	protected static final String UTF8 = "utf-8";
	protected static DataFormatter FORMATTER = new DataFormatter();

	protected static final String INPUT_FILE_PIPE_DELIMITED = "input_pipe_delimited.txt";
	protected static Writer INPUT_FORMAT_WRITER;

	/* Log File */
	protected static final String LOG_FILE = "LOG_CreateInputFiles_Run.log";
	protected static Writer LOG_WRITER;

	/* Service Part Creation */
	protected static Writer SERVICE_PART_WRITER;
	protected static final String SERVICE_PARTS_CREATION_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_ServiceParts_Creation.txt";
	protected static final String SERVICE_PART_CREATION_CONFIG = "#### New operation Creation cfg ####\r\n#============================================ \r\n# General options\r\n#============================================\r\n\r\nSET BYPASS        =  ON\r\nCREATE ITEMS                        =  ON\r\nCREATE REVS                         =  ON\r\nTC DATE FORMAT          =  %d-%b-%Y %H:%M\r\n\r\n!|ItemID|ItemName|RevID|ItemType|Uom|I:ip_classification|R:get6ObjWt|R:get6ObjWtUOM|I:get6EngrProdLine|R:get6DataModel|I:get6ECCN|I:get6ECCNSource|I:get6ObjEvidence|R:get6CTQ|I:get6CCC|I:get6ECC|I:get6Homologation|I:get6CriticalPart|R:get6EngMB\r\n";

	/* Service Form Properties */
	protected static Writer SERVICE_FORM_WRITER;
	protected static final String SERVICE_FORM_PROPERTIES_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_SP_ServiceForm_Properties_Update.txt";
	protected static final String SERVICE_FORM_UPDATE_CONFIG = "#### New operation Creation cfg ####\r\n#============================================ \r\n# General options\r\n#============================================\r\n\r\nSET BYPASS        =  ON\r\nUPDATE LATEST REV    =  ON\r\nRELATION NAME                         =  GET9ServFormAtt\r\nRELATION PARENT TYPE                        =  REV          \r\nFORM TYPE                         =  GET9SerAttrForm\r\n\r\n!|Name|ParentID|F:get9ComponentID|F:get9Serviceable|F:get9Repairable|F:get9Serialized|F:get9PositionTracked|F:get9ServiceItemType|F:get9TierType|F:get9EngineFamily|F:get9CatalogNo\r\n";

	/* Service Structures Creation - PS_UPLOAD format */
	protected static Writer PS_STRUCTURE_WRITER;
	protected static final String PS_STRUCTURE_CREATION_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_PS_Service_Assemblies.txt";
	protected static final String PS_STRUCTURE_CREATION_CONFIG = "#DELIMITER |\r\n#COL item rev type Level Seq Qty\r\n";

	/* Service Structures Creation */
	protected static Writer STRUCTURE_WRITER;
	protected static final String STRUCTURE_CREATION_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_Service_Assemblies.txt";
	protected static final String STRUCTURE_CREATION_CONFIG = "#### New operation Creation cfg ####\r\n#============================================ \r\n# General options\r\n#============================================\r\n#ITEM TYPE = GET9SrvPart\r\nUPDATE LATEST REV			=  ON\r\nSET BYPASS  				=  ON\r\nCREATE ITEMS                =  OFF\r\nCREATE REVS                 =  OFF\r\nUPDATE ITEMS                =  ON\r\nUPDATE REVS                 =  ON\r\nCREATE REV SEQS             =  ON\r\nUPDATE REV SEQS             =  ON\r\nSET PREV REV SEQ IMMUNE     =  ON\r\nUpdate CICO                 =  ON\r\nBOM UPDATE ID FIELDS        =  ON\r\nBOM UPDATE SEQ FIELDS       =  ON\r\nBOM REV RULE = GET Working, GET Baselined, GET Released\r\n\r\n!|ParentID|ChildID|Qty|BL:bl_sequence_no\r\n";

	/* Engineering Parts' Service Form Creation and Attachment */
	protected static Writer EP_SERVICE_FORM_WRITER;
	protected static final String EP_SERVICE_FORM_CREATION_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_EP_ServiceForms_Creation.txt";
	protected static final String EP_SERVICE_FORM_CREATION_CONFIG = "#### New operation Creation cfg ####\r\n#============================================ \r\n# General options\r\n#============================================\r\n\r\nSET BYPASS        =  ON\r\nRELATION NAME        =  GET9ServFormAtt\r\nRELATION PARENT TYPE =  REV          \r\nFORM TYPE            =  GET9SerAttrForm\r\nUPDATE LATEST REV    =  ON\r\n\r\n!|Name|F:get9ComponentID|F:get9Serviceable|F:get9Repairable|F:get9Serialized|F:get9PositionTracked|F:get9ServiceItemType|F:get9TierType|F:get9EngineFamily|F:get9CatalogNo|ParentID\r\n";
	protected static final String EP_SERVICE_FORM_RELATION_NAME = "GET9ServFormAtt";
	
	/* Service Parts' Global Alternate */
	protected static Writer SP_GLOBAL_ALT_WRITER;
	protected static final String SP_GLOBAL_ALT_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_AlternateParts.txt";

	/* Service Parts' Owning Group update */
	protected static Writer SP_GROUP_ID_WRITER;
	protected static final String SP_GROUP_ID_INPUT_FILE = INPUT_FILES_DIR + "INPUT_GroupId.txt";
	protected static String OWNING_USER = "sg_migration_user";
	protected static String OWNING_GROUP = "SERVICES.TRANSPORTATION.GE TRANSPORTATION";
	protected static String SP_GROUP_ID_UPDATE_CONFIG = "#============================================ \r\n# General options\r\n#============================================\r\n\r\nSET BYPASS          =  ON\r\nCREATE ITEMS        =  OFF\r\nCREATE REVS         =  OFF\r\nUPDATE ITEMS        =  ON\r\nUPDATE REVS         =  ON\r\nUPDATE LATEST REV   =  ON\r\nDEFAULT OWNER     =     " + OWNING_USER + "\r\nDEFAULT GROUP       =  " + OWNING_GROUP + "\r\n!|ItemID\r\n";


	/* Relate EngParts to Service Parts */
	protected static Writer ENG_PARTS_TO_SERVICE_PARTS_RELATION_WRITER;
	protected static final String ENG_PARTS_TO_SERVICE_PARTS_RELATION_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_Relate_EngParts_ServiceParts.txt";
	protected static final String ENG_PARTS_TO_SERVICE_PARTS_RELATION_CONFIG = "#### New operation Creation cfg ####\r\n#============================================ \r\n# General options\r\n#============================================\r\n\r\nUPDATE LATEST REV     =  ON\r\nSET BYPASS        =  ON\r\nCREATE ITEMS                        =  OFF\r\nCREATE REVS                         =  OFF\r\nUPDATE ITEMS                        =  ON\r\nUPDATE REVS                         =  ON\r\n\r\n!|ParentID|RevID|ChildID|RelationName\r\n\r\n";
	protected static final String EP_TO_SP_RELATION_NAME = "EP_SP_Relation";

	/* Relation to Three types of Documents */
	protected static Writer SP_ATTACHMENT_WRITER;
	protected static final String SP_ATTACHMENT_INPUT_FILE = INPUT_FILES_DIR
			+ "INPUT_ServiceParts_Attachments.txt";
	protected static final String SP_ATTACHMENT_CONFIG = "#### New operation Creation cfg ####\r\n#============================================ \r\n# General options\r\n#============================================\r\n\r\nUPDATE LATEST REV					=  ON\r\nSET BYPASS  						=  ON\r\nCREATE ITEMS                        =  OFF\r\nCREATE REVS                         =  OFF\r\nUPDATE ITEMS                        =  ON\r\nUPDATE REVS                         =  ON\r\n\r\n!|ParentID|RevID|ChildID|RelationName\r\n";
	protected static final String SP_DOC_RELATION_NAME = "GET6DocumentRel";
	protected static final String SP_DWG_RELATION_NAME = "GET6DrawingRel";
	protected static final String SP_PURCHSPEC_RELATION_NAME = "GET6SpecRel";
	
	/* Made From Relation */
	protected static Writer MADE_FROM_RELATION_WRITER;
	protected static final String MADE_FROM_REL_INPUT_FILE = INPUT_FILES_DIR + "INPUT_MadeFrom_Relation_Creation.txt";
	protected static final String MADE_FROM_REL_CONFIG = "#### New operation Creation cfg ####\r\n#============================================ \r\n# General options\r\n#============================================\r\n\r\nUPDATE LATEST REV					=  ON\r\nSET BYPASS  						=  ON\r\nCREATE ITEMS                        =  OFF\r\nCREATE REVS                         =  OFF\r\nUPDATE ITEMS                        =  ON\r\nUPDATE REVS                         =  ON\r\n\r\n!|ParentID|ChildID|RelationName\r\n";
	protected static final String SP_MADEFROM_RELATION_NAME = "GET6MadeFromPart";

	/* Column Indexes */
	protected static final int SR = 0;
	protected static final int INFO = 1;
	protected static final int LINE_TYPE = 2;
	protected static final int PARENT_ID = 3;
	protected static final int LEVEL = 4;
	protected static final int SEQ = 5;
	protected static final int QTY = 6;
	protected static final int NA1 = 7;
	protected static final int CMP_ID_FROM_BOM = 8;
	protected static final int NEW_SRV_CLS = 9;
	protected static final int PART_BULLETIN = 10;
	protected static final int NA2 = 11;
	protected static final int GLOBAL_ALT = 12;
	protected static final int NA3 = 13;
	protected static final int ITEM_ID = 14;
	protected static final int ITEM_NAME = 15;
	protected static final int REVISION = 16;
	protected static final int OWN_GROUP = 17;
	protected static final int UOM = 18;
	protected static final int IP_CLASS = 19;
	protected static final int ENG_PRODUCT_LINE = 20;
	protected static final int DATA_MODEL = 21;
	protected static final int ECCN = 22;
	protected static final int ECCN_SOURCE = 23;
	protected static final int OBJ_EVI = 24;
	protected static final int CTQ = 25;
	protected static final int CCC = 26;
	protected static final int ECC = 27;
	protected static final int HOMOLOGATION = 28;
	protected static final int CRITICAL_PART = 29;
	protected static final int ENG_MAKE_BUY = 30;
	protected static final int OBJ_WEIGHT = 31;
	protected static final int OBJ_WEIGHT_UOM = 32;
	protected static final int NA4 = 33;
	protected static final int SERVICE_CMP_ID = 34;
	protected static final int SERVICEABLE = 35;
	protected static final int REPAIRABLE = 36;
	protected static final int SERIALIZED = 37;
	protected static final int POS_TRACKED = 38;
	//protected static final int POS_TRACK_VALUES = 39;
	protected static final int SERVICE_ITEM_TYPE = 39;
	protected static final int TIER_TYPE = 40;
	protected static final int ENGINE_FAMILY = 41;
	protected static final int CATALOG_ITEM = 42;
	protected static final int NA5 = 43;
	protected static final int LINK_DOC = 44;
	protected static final int LINK_DWG = 45;
	protected static final int LINK_PURCHSPEC = 46;
	protected static final int LINK_MADEFROM = 47;
	protected static final int NA6 = 48;
	
	/**
	 * Prints usage of the utility
	 */
	static void printHelp()
	{
		System.out
				.println("\nUtility usage : java -jar CreateInputFiles.jar -i=<Data Loader file path> \nNo other argument is accepted.");
	}
}
