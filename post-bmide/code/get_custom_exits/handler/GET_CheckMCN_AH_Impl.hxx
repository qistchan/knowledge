
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_CheckMCN_AH_Impl.cxx
//
//    Purpose:   Source File defining the Manufacturing Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     18 May, 2017         Adding method attachMfgAttrFormsToTarget()
//  TCS Development Team     27 Jun, 2017         Renamed validateFlipToBuy() to validateFlipToMakeBuy()
//  TCS Development Team     07 Aug, 2017         Added new method validateCheckOutStatus() for validating the the CheckOut Status of Item Rev and Mfg Attr Form
//  TCS Development Team     27 Sep, 2017         MCN restructuring
//  TCS Development Team     27 Sep, 2017         Renamed getMadeFromParts() to recurseMadeFromParts() function
//  TCS Development Team     27 Sep, 2017         Removed GET_TargetsFromBOM()
//  TCS Development Team     27 Sep, 2017         Added resetMfgAttrFormsModValue()
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_CHECKMCN_AH_HXX
#define GET_CHECKMCN_AH_HXX

#include <property/nr.h>
#include <epm/epm_toolkit_tc_utils.h>
#include <epm/epm_task_template_itk.h>

// GET Includes
#include <GET_Form.hxx>
#include <GET_Utils.hxx>
#include <GET_Item.hxx>
#include <GET_Date.hxx>
#include <GET_POM_user.hxx>
#include <GET_BOMWindow.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_SMTP_Mail.hxx>
#include <GET_POM_object.hxx>
#include <GET_EPMTask.hxx>
#include <GET_Errors.hxx>
#include <GET_TC_Types.hxx>
#include <GET_Preferences.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_RuntimeBusinessObject.hxx>
#include <GET_ReleaseStatus.hxx>
#include <GET_BOMViewRevision.hxx>
#include <GET_Site.hxx>

using namespace get;


#define ACCESS_DENIED_ERROR				515001
#define ACCESS_DENIED_ERROR_MSG			525084
#define TARGET_IN_ANOTHER_WORKFLOW		900025
#define TARGET_ALREADY_PRESENT_ERROR	33019

#define NUMBER_OF_ATTACHMENTS			1
#define NUMBER_OF_ITEM_FIND_ATTRIBUTES	2

#define NUMBER_OF_MADE_FROM_PART		1

#define WSO_WHERE_REF_ONE_LEVEL			1
#define NO_OF_SOLUTION_ITEMS			1


#define ERROR_PART_NOT_REL_INDEX		1
#define ERROR_MISSING_ORG_INDEX			2
#define ERROR_MISMATCH_ORG_INDEX		3
#define ERROR_MAKE_BUY_MISMATCH			4
#define ERROR_NO_MAKE_BUY_INDEX			5
#define ERROR_NO_STOCK_MTRL_INDEX		6
#define ERROR_NO_ORG_FORM_INDEX			7
#define ERROR_NO_PRELIM_ASMBLY_INDEX	8
#define ERROR_NO_PRELIM_STATUS_INDEX	9
#define ERROR_UNCONFIGURED_BOMLINE_INDEX 10
#define ERROR_NO_STOCK_MTRL_REL_INDEX	11
#define MIN_NUM_OF_CHARS_ITEM_ID		9
#define ERROR_NOT_VALID_GROUP			2
#define ERROR_NOT_VALID_ITEM			3
#define ERROR_PART_CO_INDEX             12
#define ERROR_MFG_ATTR_FORM_CO_INDEX    13
#define ERROR_ENG_PART_NOT_VERIFIED     14

#define NO_OF_CHARS_FILE_NAME			10

#ifdef WIN32
	#define FILE_SEPERATOR_VALUE	"\\"
#else
	#define FILE_SEPERATOR_VALUE	"/"
#endif // WIN32

#define EMPTY_STRING_VALUE		""
#define EMPTY_SPACE_VALUE		" "
#define INTIAL_REV_ID_VALUE		"0"
#define TAB_SPACE_VALUE			"	"
#define UNDER_SCORE_VALUE		"_"
#define COLON_CHAR_VALUE		":"
#define COMMA_CHAR_VALUE		","
#define EQUAL_CHAR_VALUE		"="
#define OPEN_SQUARE_CHAR_VALUE	"["
#define CLOSE_SQUARE_CHAR_VALUE	"]"
#define FORWARD_SLASH_VALUE		"/"
#define NEW_TAB_VALUE			"\t"
#define NEW_LINE_VALUE			"\n"
#define DOUBLE_QUOTES_VALUE		"\""
#define PIPE_DELIM_VALUE		"|"
#define MAKE_VALUE				"Make"
#define BUY_VALUE				"Buy"
#define NONE_VALUE				"None"
#define REVISION_RULE_PREFIX 	"GET "
#define RELEASED_REV_RULE_SUFF	" Oracle Released"
#define WIP_REV_RULE_SUFF		" Oracle WIP"
#define REVISION_KEYWORD_VALUE  "Revision"
#define OBJECT_ITEM "ITEM"
#define OBJECT_BOM "BOM"
#define OBJECT_SM "SM_MAKE_PART"
#define OBJECT_PMFP "PART_MADE_FROM_PART"
#define PART_NOT_VERIFIED "Engineering Part(assembly) is not verified"
#define PART_ERROR "This Part is unreleased"
#define OBSOLETE_PART_ERROR "Part is Obsolete"
#define PART_INCORRECT_STATUS "Part is having incorrect status"

#define SOURCE_HANDLER_ARG		"source"
#define TARGET_HANDLER_ARG		"target"

#define GRV_PROJECT				"GRV"
#define FOLDER_BO				"Folder"
#define GET_MFG_REV_BO			"GET6MfgPartRevision"
#define GET_MCN_BO				"GET6MCN"
#define GET_ECN_REV_BO			"GET6ECNRevision"
#define GET_MCN_REV_BO			"GET6MCNRevision"
#define GET_PART_ORG_ATTR_BO	"GET6PartOrgRelation"
#define GET_ELECT_PART_REV_BO	"GET6ElectPartRevision"
#define GET_MECH_PART_REV_BO	"GET6MechPartRevision"
#define GET_SOFT_PART_REV_BO	"GET6SoftwarePartRevision"
#define BOM_VIEW_REVISION_TYPE	"view"

#define ENG_MAKE_BUY_PROP		"get6EngMB"
#define MAKE_BUY_PROP			"get6MakeBuy"
#define CREATION_DATE_PROP		"creation_date"
#define LAST_MOD_DATE_PROP		"last_mod_date"
#define OWNING_USER_PROP		"owning_user"
#define OWNING_PROJECT_PROP		"owning_project"
#define PROJECT_ID_PROP			"project_id"
#define BVR_OCCURRENCE_PROP		"bvr_occurrences"
#define MADE_FROM_MATL_PROP		"GET6MadeFromMatl"
#define HAS_STOCK_MATL_PROP		"GET6HasStockMatl"
#define MADE_FROM_PART_PROP		"GET6MadeFromPart"
#define STOCK_MATERIAL_PROP		"get6StockMaterial"
#define CM_IMPLEMENTS_PROP		"CMImplements"
#define CM_HAS_IMITEMS_PROP		"CMHasImpactedItem"
#define CM_HAS_PMITEMS_PROP		"CMHasProblemItem"
#define CM_HAS_SLITEMS_PROP		"CMHasSolutionItem"
#define STRUCT_LAST_MOD_PROP	"struct_last_mod_date"

#define CM_DERIVE_CHANGE_PREF	"CM_"
#define CM_DERIVE_CHANGE_SUFF	"Revision_Relations_To_Propagate"
#define CM_MCN_ORG_PROJ_PREF 	"GET6_Derive_MCN_For_Projects"
#define T4O_ITEMTYPES_LIST_PREF	"T4O_ItemTypeList"
#define CM_VALID_MCN_OBJECTS    "GET6_Valid_MCN_Solution_Items"
#define GET_MCN_PROCESS_WF 		"GET MCN Process"
#define OBJECT_TYPE				"object_type"
#define RFUOM                   "RF"

#define NAMING_PATTERN_PREFIX			"\""
#define NAMING_PATTERN_SUFFIX			"-MCN-\"NNNNNN"
#define GET6_PREFIX_VALUE				"GET6"
#define RELEASED_SUFFIX_VALUE			"Released"
#define GET6_RELEASED_VALUE				"GET6Released"
#define OBSOLETE_VALUE				    "Obsolete"
#define GET6_PRELIMINARY_VALUE			"GET6Preliminary"
#define GET6_ANYSTATUS_NOWORKING		"Any Status; No Working"
#define RECIPIENT_ARGUMENT_VALUE		"recipient"
#define WORKFLOW_TYPE_NAME				"workflow"
#define SOLUTION_ITEMS_FOLDER			"Solution Items"
#define PROBLEM_ITEMS_FOLDER			"Problem Items"
#define MCN_HAS_BEEN_SENT_BACK_ERROR	"MCN has been sent back for error"
#define INVALID_OBJECT_TYPE_ERROR		"Invalid Object Type Found"
#define NO_ORG_IN_PARENT_ERROR			"No Org is attached in Parent"
#define NO_MAKE_BUY_SET_ERROR			"No Make/Buy Value is Set"
#define CANNOT_REMOVE_ORG_ERROR			" - Cannot Modify/Remove Org for Item sent to Oracle"
#define CANNOT_MODIFY_ORG_ERROR			" - The current Group/Role is not allowed to modify this Org"
#define CANNOT_CREATE_ITEM_ERROR		" - Cannot create Item as it has Invalid characters/Exceeded the character limit"
#define CANNOT_MODIFY_RAW_MTRL_ERROR	" - The current Group/Role is not allowed to add/remove Raw Material"
#define WORKFLOW_ERROR_MESSAGE			" Workflow"
#define MANY_RAW_MTRL_ERROR_MESSAGE		"More than one Alternate Raw Material found for - "
#define NO_ORG_ID_ERROR_MESSAGE			"No Org ID found in the Alternate Raw Material"
#define WRONG_OBJECT_ERROR_MESSAGE		" - Cannot assign Org to this Item Type \n Allowed types are GET Part, GET Raw Material and GET Manufacturing Item"
#define WORKFLOW_NAME_MCN				"MCN"
#define WORKFLOW_NAME_PRELIM			"Prelim"
#define ARG_REVISION_RULE				"RevisionRule"
#define MCN_DERIVED_DECISION_ARG        "DerivedDecision"
#define AFFECT_BOP_DECISION_ARG         "AffectBOP"
#define EFF_DECISION_ARG                "EffDecision"
#define EFF_DATE_CHECK_ARG              "EffDate"

static void GET_CheckMCN_AH_impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);

class GET_CheckMCN_AH_Impl {
private:
	
	int m_istatus;
	string m_strMCNID;
	string m_strSelectedOrg;
	string m_strRecipientID;
	string m_strRevisionRule;
	string m_strSubject;
	vector<tag_t> m_vProcessedItems;
	vector<string> m_vValidMCNObjects;
	vector<string> vWarningMessages;
	vector<GET_ItemRevisionShrPtr> m_vSolutionItems;
	vector<GET_ItemRevisionShrPtr> vMfgPartVector;
	map<string, string> m_vArguments;
	map<int, vector<tag_t>> m_vAttachments;
	map<int, vector<string> > m_mapErrorMsg;
	map<string, string>::iterator m_vArgumentsItr;
	map<int, vector<tag_t> >::iterator m_AttachmentsItr;
	map<int, vector<string> >::iterator m_ErrorMsgItr;
	tag_t m_tTaskTag;

	int sendEMail(void);
	int sendUOMWarningEMail ( vector<string> );
	int recurseMFG(GET_BOMLineShrPtr, vector<GET_ItemRevisionShrPtr>&, vector<GET_ItemRevisionShrPtr>&, vector<GET_ItemRevisionShrPtr>&, vector<GET_ItemRevisionShrPtr>& );
	int recurseMfgAttrForms(GET_BOMLineShrPtr p_getBOMLineShrPtr, vector<GET_FormShrPtr>& vFormsToBeRelease );
	
	int checkReleaseStatus(GET_ItemRevisionShrPtr);
	int validateCheckOutStatus(GET_ItemRevisionShrPtr);
	int checkParentOrgItem(GET_ItemRevisionShrPtr, vector<GET_FormShrPtr>);
	int checkStockMaterial(GET_ItemRevisionShrPtr, vector<GET_FormShrPtr>);
	int checkBOMPublishDate(GET_ItemRevisionShrPtr, vector<GET_FormShrPtr>);
	int checkItemPublishDate(GET_ItemRevisionShrPtr, vector<GET_FormShrPtr>);
	int checkVerifiedAssembly(GET_BOMLineShrPtr );

	void logErrorMessage(int, string);
	bool GET_ExistsInVector( vector<GET_ItemRevisionShrPtr>, GET_ItemRevisionShrPtr );
	bool hasMakeOrgItem(GET_ItemRevisionShrPtr);
	bool hasRFUOM(GET_ItemRevisionShrPtr);
	string getManufacturingRevisionRule(bool);
	vector<string> getOrgIDs(vector<GET_FormShrPtr>);
	vector<GET_FormShrPtr> getOrgItems(GET_ItemRevisionShrPtr);
	int recurseMadeFromParts(GET_ItemRevisionShrPtr, vector<GET_ItemRevisionShrPtr>&, vector<GET_ItemRevisionShrPtr>&, vector<GET_ItemRevisionShrPtr>&, vector<GET_ItemRevisionShrPtr>& );
	int addObjectsToRefFolder ( vector<GET_ItemRevisionShrPtr>, string, string, string, vector<GET_POM_objectShrPtr>& );
			
	int recursePrelimMFG(GET_BOMLineShrPtr);
	int validatePreliminaryStructure(GET_ItemRevisionShrPtr);
	int validatePrelimStatus(GET_ItemRevisionShrPtr);

public:
	GET_CheckMCN_AH_Impl(const tag_t, map<int, vector<tag_t>>&, map<string, string>&);
	~GET_CheckMCN_AH_Impl();

	int validateMCN(void);
	int validatePreliminaryMCN();
	int validateFlipToMakeBuy(void);
	int attachMfgAttrFormsToTarget(void);
	void resetMfgAttrOracleXferPropValue(void);
	string getSiteID();
};

#endif
