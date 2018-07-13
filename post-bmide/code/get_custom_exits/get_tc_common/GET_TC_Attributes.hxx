
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_TC_Attributes.hxx
//
//    Purpose:   Header file for Attribute Names
//
//    History:
//      Who                        Date                    Description
//  TCS Development Team          29 Apr, 2016            Initial creation
//  Capgemini Development Team    23 Jan, 2017            Added GET Abstract Revision attributes
//  Capgemini Development Team    16 Feb, 2017            Added ECR attributes
//  TCS Development Team          04 May, 2017            Moved MADE_FROM_PART_PROP definition from MFG headers to this file
//  TCS Development Team          08 May, 2017            Added attribute definitions for the AWC BOM Index Admin Data Class
//  TCS Development Team          15 May, 2017            Added attribute definitions for ECN Checkmate attributes
//  TCS Development Team          15 May, 2017            Added attribute definitions for UGPART-ATTRIBUTES form
//  TCS Development Team          18 May, 2017            Added attribute definitions for TC_Preferences class
//  TechM Development Team        20 May, 2017            Added attribute definitions for Workflow states
//  TCS Development Team          29 May, 2017            Added handler arguments RELATED_TYPE_ARG, ALLOWED_STATUS_ARG, NONE_ARG_VAL, NULL_ARG_VAL, CREATION_DATE_ATTR
//  TCS Development Team          29 May, 2017            Added query criteria definitions for QUERY_ID_CRITERIA, QUERY_REVISION_CRITERIA, QUERY_CREATED_AFTER_CRITERIA
//  TCS Development Team          31 May, 2017            Consolidated Query related constants
//  TCS Development Team          31 May, 2017            Added preference definition for GET_ECR_ECN_CLOSE_INTERVAL and Workflow template name for SUBMIT_TO_CLOSE_CHANGE_WORKFLOW
//  TCS Development Team          31 May, 2017            Added attribute definition for date released attribute
//  TCS Development Team          01 Jun, 2017            Added preference definition for GET_STOCKMTRL_INVALID_UOM_VALUES
//  TCS Development Team          21 Jun, 2017            Added Attribute definition for TC_Project object
//  TCS Development Team          27 Jun, 2017            Added Workflow argument for Mfg Attr Form Locking usecase
//  TCS Development Team          29 Jun, 2017            Added Workflow handler argument for ALLOWED_CHILD_TYPES_ARG
//  TCS Development Team          20 Jul, 2017            Added ITEM_PUBLISH_DATE attribute definition.
//  TCS Development Team          02 Aug, 2017            Added preference definition for GET6_Project_Propagation_Inclusion_List.
//  TechM Development Team        30 Aug, 2017            Added attribute definition for MOD_DESIGN_CUTIN_ATTR
//  TCS Development Team          01 Sep, 2017            Added attribute definition for CAS_DOWNLOADER_URL_ATTR
//  TechM Development Team        22 Sep, 2017            Added Dispatcher related Handler arguments definition
//  TCS Development Team          27 Sep, 2017            Added attribute definition for Mfg Attr Form modification value
//  Ganesh Ubale                  01 Nov, 2017            Added attribute definition for SERVICE_IMPACT_ATTR
//  TCS Development Team          11 Nov, 2017            Added Workflow handler argument for validating BOM structure
//  TCS Development Team          04 Jun, 2018            Added Workflow handler argument for responsibleParty
//  TCS Development Team          20 Jun, 2018            Added ECN Rev Prop for Multi Org

//   ============================================================================
// ENDFILEDOC   ***/

// Attributes Name
#define PROJECTLIST_ATTR "project_list"
#define RELEASE_STATUS_LIST_ATTR "release_status_list"
#define NAME_ATTR "name"
#define All_WORKFLOWS "fnd0AllWorkflows"
#define REAL_STATE "real_state"
#define REAL_STATE_STARTED "Started"
#define CREATION_DATE_ATTR "creation_date"
#define DATE_RELEASED_ATTR "date_released"
#define ITEM_PUBLISH_DATE "get6ItemPublishDate"
#define GET6_ATTR_PREFIX  "get6"

// POM_object Attributes
#define OWNING_SITE_ATTR "owning_site"

// Item Attributes
#define ITEM_ID_ATTR "item_id"
#define IP_CLASSIFICATION_ATTR "ip_classification"
#define UOM_ATTR "uom_tag"
#define SYMBOL_ATTR "symbol"
#define UOM_TAG_PROP "uom_tag"
#define UOM_RF_VALUE "RF"
#define VERIFIED_ASSEMBLY_PROP  "get6VerifiedPart"

// ItemRevision Attributes
#define ITEM_TAG_ATTR "items_tag"
#define ITEM_REVISION_ID_ATTR "item_revision_id"
#define ITEM_REVISION_ATTR "revision"
#define PARTICIPANTS_ATTR "participants"
#define PSCHILDREN_ATTR "ps_children"
#define MADE_FROM_PART_PROP "GET6MadeFromPart"

// Create Input Attributes
#define SOURCE_OBJECT_TAG "srcObjectTag"

//Participant Attributes
#define PARTICIPANT_ASSIGNEE_ATTR "assignee"

//Relation Attributes
#define CM_HAS_IMPACTED_ITEMS_PROP "CMHasImpactedItem"
#define CM_HAS_PROBLEM_ITEMS_PROP "CMHasProblemItem"
#define CM_HAS_SOLUTION_ITEMS_PROP "CMHasSolutionItem"

// GET Abstract Revision Attributes
#define OVERALL_LENGTH_ATTR "get6OverallLength"
#define OVERALL_WIDTH_ATTR "get6OverallWidth"
#define OVERALL_HEIGHT_ATTR "get6OverallHeight"
#define OVERALL_UOM_ATTR "get6OverallUOM"
#define MAX_DECIMAL_LIMIT 4
#define ME_TARGET "IMAN_METarget"
#define ME_WORKAREA "IMAN_MEWorkArea"

// ECR/ECN Attributes
#define CCC_ATTR "get6CCC"
#define COPIES_ATTR "get6Copies"
#define CRITICAL_PART_ATTR "get6CriticalPart"
#define DESIGNTYPE_ATTR "get6DesignType"
#define ECC_ATTR "get6ECC"
#define ECCN_SOURCE_ATTR "get6ECCNSource"
#define EXP_CONTROL_ATTR "get6ExpControl"
#define HOMOLOGATION_ATTR "get6Homologation"
#define STDPROD_ATTR "get6STDProd"
#define ENGRPRODLINE_ATTR "get6EngrProdLine"
#define ECCN_ATTR "get6ECCN"
#define OBJECTEVIDENCE_ATTR "get6ObjEvidence"
#define IS_NEW_ECN_ATTR "get6IsNew"
#define EXPLOSIVE_ATMOSPHERE_ATTR "get6CCUEA"
#define BYPASS_CHECKMATE "get6BypassCheckmate"
#define BYPASS_COMMENTS "get6BypassComments"
#define BYPASS_REASON "get6BypassReason"
#define MOD_DESIGN_CUTIN_ATTR "get6ModDesignCutIn"
#define CAS_DOWNLOADER_URL_ATTR "get6CASDownloderURL"
#define SERVICE_IMPACT_ATTR "get6IsMatlAtServiceLocn"
#define ECN_ITEM_ORG_LIST "get6ItemOrgFrmProp"
#define ENGG_ITEM_ID "get6EnggItemsID"

// Production Part Attributes
#define ENG_MAKEBUY "get6EngMB"

// Make/Buy Attribute Values
#define ENG_MAKEBUY_NONE_VALUE "None"
#define ENG_MAKEBUY_MAKE_VALUE "Make"
#define ENG_MAKEBUY_BUY_VALUE "Buy"

// PSOccurrence Attributes
#define PARENT_BVR_ATTR "parent_bvr"

// Participant Attributes
#define ASSIGNEE_ATTR "assignee"

// WSO Attributes
#define OBJECT_NAME_ATTR "object_name"
#define OBJECT_TYPE_ATTR "object_type"
#define OBJECT_DESC_ATTR "object_desc"
#define OBJECT_STRING_ATTR "object_string"
#define OWNING_GROUP_ATTR "owning_group"
#define OWNING_USER_ATTR "owning_user"
#define OWNING_PROJECT_ATTR    "owning_project"
#define PROJECT_ID_ATTR "project_id"
#define PROCESS_STAGE_LIST_ATTR "process_stage_list"

// Dataset Attributes
#define REFLIST_ATTR "ref_list"
#define REFNAMES_ATTR "ref_names"

// ImanFile Attributes
#define FILENAME_ATTR "file_name"
#define ORIGINALFILENAME_ATTR "original_file_name"

// Form Attributes
#define DATAFILE_ATTR "data_file"

// UGPARTAttribute Form attributes
#define TITLES_ATTR "titles"
#define VALUES_ATTR "values"
#define GETR_CHECKMATE_STATUS "GETR_CHECKMATE_STATUS"

// POM Attributes
#define PUID_ATTR "puid"

//PROJECT Attributes
#define PROJECT_ATTR "project"
#define PROJECT_IS_ACTIVE_ATTR "is_active"
#define PROJECT_IS_VISIBLE_ATTR "is_visible"
#define PROJ_PROGRAM_SECURITY_ATTR "use_program_security"
#define PROJECT_NAME_ATTR "project_name"
#define PROJECT_DESC_ATTR "project_desc"

// TC_Prefenreces Attributes
#define DATA_ATTR "data"
#define OBJECT_TAG_ATTR "object_tag"

// AWC BOM Index Admin Data Attributes
#define AWC_BOMINDEXADMIN_PRODUCT_ATTR "awb0Product"
#define AWC_BOMINDEXADMIN_REVISIONRULE_ATTR "awb0BaseRevisionRule"
#define AWC_BOMINDEXADMIN_INDEXSTATE_ATTR "awb0IndexState"

// Preferences
#define MAIL_SERVER_NAME_PREF "Mail_server_name"
#define GET_ENG_DISALLOWED_REV_IDS "GET_Eng_Disallowed_Rev_IDs"
#define GET_ENG_GENERATE_REV_ID_ITEM_TYPES "GET_Eng_Generate_Rev_Id_Item_Types"
#define GET_ASSIGNED_REV_NON_MODIFIABLE_TYPES "GET_Assigned_Rev_Non_Modifiable_Types"
#define ASSIGNED_ITEM_REV_MODIFIABLE "ASSIGNED_ITEM_REV_MODIFIABLE"
#define GET_STOCKMTRL_INVALID_UOM_VALUES "GET_StockMtrl_Invalid_UOM_Values"
#define GET_PROJECT_PROPAGATION_INCLUSION_LIST "GET6_Project_Propagation_Inclusion_List"
#define GET_WAITTIME_FOR_FILE_TRANSFER "GET_WaitTime_For_File_Transfer"

// CM Yes/No LOV Values
#define CM_LOV_YES_VALUE "Yes"
#define CM_LOV_NO_VALUE "No"

// EC LOV Values
#define ECCN_LR "LR"
#define ECCN_NLR "NLR"

// ECCNSRC LOV Values
#define ECCNSRC_ECDOC "ECDoc"
#define ECCNSRC_ECTAGGER "ECTagger"

// DESIGNTYPE LOV Values
#define DESIGNTYPE_MB "MB"
#define DESIGNTYPE_MC "MC"

// BOP Object Revision Types
#define GET6_BOP_OBJECT_REVISION_TYPES "GET6BOPObjectRevisionTypes"
#define MFG_OBJECT "MBOM"
#define BOP_OBJECT "BOP"

//ProjectObjectRelation Attributes
#define  PROPAGATION_OBJ_LIST_ATTR "propagation_obj_list"

// Handler Arguments
#define EMAIL_PROP_NAME_HANDLER_ARG "emailPropName"
#define RESOURCE_POOL_HANDLER_ARG "resourcePool"
#define RESPONSIBLE_PARTY_HANDLER_ARG "responsibleParty"
#define TO_EMAIL_ID_HANDLER_ARG "toEmailId"
#define TO_EMAIL_PREF_HANDLER_ARG "toEmailPref"
#define SUBJECT_HANDLER_ARG "subject"
#define EMAIL_TITLE_HANDLER_ARG "emailTitle"
#define EMAIL_HEADER_PROPS_HANDLER_ARG "emailHeaderProps"
#define EMAIL_BODY_PROPS_HANDLER_ARG "emailBodyProps"
#define EMAIL_FOOTER1_PROPS_HANDLER_ARG "emailFooter1Props"
#define EMAIL_FOOTER1_TITLE_HANDLER_ARG "emailFooter1Title"
#define BASELINE_PROCESS_TYPE_ARG "process_type"
#define BASELINE_PROCESS_TYPE_VALUE "baseline"
#define PRELIMINARY_PROCESS_TYPE_VALUE "preliminary"
#define BASELINE_TEMPLATE_ARG "template_name"
#define REVISION_RULE_ARG "revision_rule"
#define INCLUDE_TYPE_ARG "include_type"
#define EXCLUDE_TYPE_ARG "exclude_type"
#define ALLOWED_TYPE_ARG "allowed_type"
#define DISALLOWED_TYPE_ARG "disallowed_type"
#define ALLOWED_STATUS_ARG "allowed_status"
#define STATUS_ARG "status"
#define RELATION_ARG "relation"
#define RELATION_TYPE_ARG "relation_type"
#define RELATED_TYPE_ARG "related_type"
#define PROPERTY_ARG "property"
#define VALUE_ARG "value"
#define DATASET_TYPE_ARG "dataset_type"
#define TYPE_ARG "type"
#define USER_ARG "user"
#define ROLE_ARG "role"
#define GROUP_ARG "group"
#define OWNING_GROUP_ARG_VAL "$OWNING_GROUP"
#define OWNING_USER_ARG_VAL "$OWNING_USER"
#define RELEASE_STATUS_LIST_ARG "release_status"
#define SECONDARY_ARG "secondary"
#define PRIMARY_ARG "primary"
#define SOURCE_ARG "source"
#define REFERENCE_TYPE_ARG "reference_type"
#define NUM_ALLOWED_VAL_ARG "num_allowed_val"
#define ERROR_MSG_ARG "error_msg"
#define RELATION_TYPE "Relation_NAME"
#define VALIDATE_COUNT "count"
#define EXCLUDE_GROUP_ARG "exclude_group"
#define INCLUDE_GROUP_ARG "include_group"
#define PREF_ARG "pref_name"
#define TASK_NAME_ARG "task_name"
#define ATTACHMENT_TYPE "attachment"
#define TARGET_ATTACHMENT "target"
#define REFERENCE_ATTACHMENT "reference"
#define PRIMARY_ARG_YES "Yes"
#define PRIMARY_ARG_NO "No"
#define SOURCE_TYPE_ARG "source"
#define PROCESS_OWNER_ATTR "PROCESS_OWNER"
#define REVIEWER_ATTR "REVIEWER"
#define REPORT_HANDLER_ARG "report"
#define TRAVERSE_ARG "traverse"
#define VALIDATE_ARG "validate"
#define SKIP_MFG_ATTR_FORM_ARG "skip_mfg_attr_form"
#define RELEASE_MFG_FORM_ARG "release_mfg_form"
#define UNRELEASE_MFG_FORM_ARG "unrelease_mfg_form"
#define MFG_ATTR_FORM_ARG "mfg_attr_form"
#define FLIP_TO_MAKE_BUY_ARG "flip_make_buy"
#define VALIDATE_UOM "UOM_values"
#define NONE_ARG_VAL "none"
#define NULL_ARG_VAL "null"
#define ANY_ARG_VAL "any"
#define ALLOWED_CHILD_TYPES_ARG "allowed_child_types"
#define	BODY_TABLE_PROPS "bodyTableProps"
#define SAVE_ECN_REPORT_ARG "saveECNReportToTC"
#define	BODY_TABLE_COLUMNS "bodyTableColumns"
#define PARTICIPANTS_ARG "participants"
#define EMAIL_BODY_WORKFLOW_TAB_ARG "signoffs"
#define PROVIDER_NAME_ARG "provider_name"
#define SERVICE_NAME_ARG "service_name"
#define PRIMARY_TYPE_ARG "primary_type"
#define PRIORITY_ARG "priority"
#define TASK_TYPE "task_type"
#define TASK_UNSET_RESULT "Unset"
#define SUMMARY_REPORT "Summary Report"
#define HTML_FILE_EXT ".html"

// Extension Arguments
#define OPERATION_TYPE_ARG "operationType"
#define CREATE_OPN_TYPE_ARG_VAL "CREATE"
#define REVISE_OPN_TYPE_ARG_VAL "REVISE"
#define SAVEAS_OPN_TYPE_ARG_VAL "SAVEAS"

// TRUE/FALSE values
#define TRUE_VALUE "TRUE"
#define FALSE_VALUE "FALSE"

//Review Task Decision Values
#define APPROVED_DECISION_ATTR "Approved"
#define REJECT_DECISION_ATTR "Rejected"
#define NO_DECISION_ATTR "No Decision"

//Manufacturing Attributes
#define MFG_MAKEBUY_MAKE_VALUE "Make"
#define STOCK_MATERIAL_ATTR    "get6StockMaterial"
#define MFG_ATTR_FORM_ORACLE_XFER_ATTR    "get6isMfgAttrModT4OXfer"
#define MFG_ATTR_FORM_ORACLE_XFER_VALUE   "True"
#define STRUCTURE_CODE_PROP "get6StructureCode"
#define OBJECT_ITEM "ITEM"

//MCN Attributes
#define ITEM_PUBLISH_DATE_PROP  "get6ItemPublishDate"
#define BOM_PUBLISH_DATE_PROP   "get6BOMPublishDate"
#define MBOM_EFF_START_DATE_PROP "get6MBOMEffStartDate"
#define BOP_EFF_START_DATE_PROP  "get6BOPEffStartDate"
#define AFFECT_BOP_DECISION_PROP "get6AffectsBOP"
#define EFF_DECISION_PROP        "get6EffectivityDecision"
#define MCN_FLIP_TO_MAKE_PROP    "get6MCNFlipToBuy"
#define MBOM_EFF_END_DATE_PROP   "get6MBOMEffEndDate"
#define BOP_EFF_END_DATE_PROP    "get6BOPEffEndDate"

//MCN WF Task Names
#define AFFECTS_BOP_TASK "Affect BOP?"
#define EFFECTIVITY_DECISION_TASK "Effectivity Decision"

// MCN True/False LOV Values
#define MCN_LOV_TRUE_VALUE "True"
#define MCN_LOV_FALSE_VALUE "False"

// MCN Org List Preference
#define MCN_ORG_LIST "GET6_Derive_MCN_For_Projects"

