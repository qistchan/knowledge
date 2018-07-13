
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_CheckMCN_AH_Impl.hxx
//
//    Purpose:   Header File defining the Manufacturing Action Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     11 May, 2017         Modified checkStockMaterial() to validate release status
//  TCS Development Team     18 May, 2017         Adding method attachMfgAttrFormsToTarget()
//  TCS Development Team     25 May, 2017         Allowing multiple items in solution folder for FlipToBuy workflow
//  TCS Development Team     26 May, 2017         Implemented common method for comparing the date for Item Publish Date and BOM Publish Date
//  TCS Development Team     26 May, 2017         Modified checkStockMaterial() to validate release status
//  TCS Development Team     26 May, 2017         Modified UOM validation for UOM RF
//  TCS Development Team     27 Jun, 2017         Modified validateFlipToMakeBuy() function to add FlipToMake operation
//  TCS Development Team     20 Jul, 2017         Fix for handling unconfigured BOMLine during BOM Traversal logic
//  TCS Development Team     07 Aug, 2017         Added new method validateCheckOutStatus() for validating the the CheckOut Status of Item Rev and Mfg Attr Form
//  TCS Development Team     07 Aug, 2017         Modified warning message for UOM Item in assembly as per Defect 1093.
//  TCS Development Team     27 Sep, 2017         MCN restructuring
//  TCS Development Team     27 Sep, 2017         Renamed getMadeFromParts() to recurseMadeFromParts() function
//  TCS Development Team     27 Sep, 2017         Removed GET_TargetsFromBOM()
//  TCS Development Team     27 Sep, 2017         Added resetMfgAttrOracleXferPropValue()
//  TCS Development Team     11 Nov, 2017         Added Workflow handler argument for validating BOM structure
//  TCS Development Team     27 Nov, 2017         Updated recurse logic for getting all errornous data validated upfront
//  TCS Development Team     27 Nov, 2017         Added Checkout validation logic for Prelim workflow
//  TCS Development Team     29 Nov, 2017         Corrected the HTML syntex for error email notification
//  TCS Development Team     09 May, 2018         Updated recurseMfg() and recurseMadeFromParts() to get the latest released MFP and SM
//  TCS Development Team     09 May, 2018         Fix for validate Stock Material, moved validateCheckOutStatus() at bottom
//   ============================================================================
// ENDFILEDOC   ***/

#include <GET_CheckMCN_AH_Impl.hxx>
#include <GET_MFG_ActionHandlers.hxx>
#include <algorithm>

const string logger = "get.handler.GET_CheckMCN_AH_Impl";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET_CheckMCN_AH_Impl()
//
//    Purpose:   Action Handler to validate the MCN
//
//    Inputs:    tMessage - The Teamcenter Action Handler Message Structure Input (GET6_CheckMCNAH)
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
GET_CheckMCN_AH_Impl::GET_CheckMCN_AH_Impl(const tag_t p_tTaskTag, map<int, vector<tag_t>>& p_vAttachments, map<string, string>& p_vArguments) {
	
	this->m_istatus = ITK_ok;
	this->m_vArguments = p_vArguments;
	this->m_vAttachments = p_vAttachments;
	this->m_mapErrorMsg.clear();
	this->m_vValidMCNObjects.clear();
	this->m_tTaskTag = p_tTaskTag;
}

GET_CheckMCN_AH_Impl::~GET_CheckMCN_AH_Impl() {
}

void GET_CheckMCN_AH_Impl::logErrorMessage ( int p_index, string p_strErrorMsg )
{
    if ( ! this->m_mapErrorMsg.empty() )
    {
        this->m_ErrorMsgItr = this->m_mapErrorMsg.find(p_index);
        if(this->m_ErrorMsgItr != this->m_mapErrorMsg.end())
        {
            this->m_ErrorMsgItr->second.push_back(p_strErrorMsg);
        }
        else
        {
            vector<string> vErrorMessage;
            vErrorMessage.push_back(p_strErrorMsg);
            this->m_mapErrorMsg[p_index] =  vErrorMessage;
        }
    }
    else
    {
        vector<string> vErrorMessage;
        vErrorMessage.push_back(p_strErrorMsg);
        this->m_mapErrorMsg[p_index] =  vErrorMessage;
    }
}

//To send warning mail
int GET_CheckMCN_AH_Impl::sendUOMWarningEMail ( vector<string> vWarningMessages )
{
    int iNumResourcePoolUsers = 0;

    string strSubject      = EMPTY_STRING_VALUE;
    string strContent      = EMPTY_STRING_VALUE;
    string sSiteID         = EMPTY_STRING_VALUE;
    string sUOMContent     = EMPTY_STRING_VALUE;
    string sEmailId        = EMPTY_STRING_VALUE;

    vector<string> vPipeSplitted;
    vector<string> vGroupRole;
    vector<string> vEmailIDs;

    sSiteID = getSiteID();

    LOG_TRACE ( logger, "Entering...sendUOMWarningEMail" );
	
	// Split the input recipient argument into Group and role filed
    GET_splitString ( this->m_strRecipientID, COLON_CHAR_VALUE, vGroupRole );
    if ( vGroupRole.size() != 2 )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RECIPIENT_ARGUMENT_VALUE )
                       + "\"  is not in required format, Format must be Group:Role ";
        THROW ( sMsg );
    }

    strSubject = this->m_strSubject +" "+ this->m_strMCNID + " : WARNING MESSAGE " + sSiteID;

    strContent = "<html><h3 style=\"color: #2e6c80;\">Dear User,</h3>";
    strContent = strContent  + "<p style=\"color:#2035E5\"><strong style=\"color: #2e6c80;\"> " + this->m_strMCNID + "</strong> has Items in assembly with UOM value as <b>&#34RF&#34</b></p><ul>";
    strContent = strContent  + "<p style=\"color:#2035E5\">This is just a <strong style=\"color: #65A31F;\"> " + "WARNING" + "</strong>, not an ERROR. It is for your information only as these parts will NOT be sent to Oracle. </p><ul>";

    strContent = strContent  + "<li style=\"color:#2035E5\">Following Part(s) in BOM Assembly have UOM value as <b>&#34RF&#34</b></li><br/>";
    strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Parent Name</td></tr>";

    for ( int iInx = 0; iInx < vWarningMessages.size(); iInx++ )
    {
        vPipeSplitted.clear();

        GET_splitString ( vWarningMessages[iInx], PIPE_DELIM_VALUE, vPipeSplitted );

        sUOMContent = "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td></tr>";
        strContent = strContent  + sUOMContent ;
    }
    strContent = strContent  + "</tbody></table><br/>";

    LOG_TRACE ( logger, "vGroupRole[0]-->" + vGroupRole[0] );
	LOG_TRACE ( logger, "vGroupRole[1]-->" + vGroupRole[1] );
	vector<GET_GroupMemberUnqPtr> vGroupMemberUnqPtr = GET_GroupMember::find ( vGroupRole[0], vGroupRole[1] );

    // Loop through each group member and send email
    for ( int iInx = 0; iInx < vGroupMemberUnqPtr.size(); iInx++ )
    {
        GET_POM_userShrPtr pUser = vGroupMemberUnqPtr[iInx]->getUser();
        GET_PersonUnqPtr person = pUser->getPerson();
        sEmailId = person->getEmailId();
        if ( ! sEmailId.empty() && sEmailId.find ( "@" ) != string::npos && sEmailId.find ( ".com" ) != string::npos )
        {
            vEmailIDs.push_back ( sEmailId );
        }
    }
    if ( vEmailIDs.size() > 0 )
    {
        sendMailAsHtml ( vEmailIDs, strSubject, strContent );
    }
    return this->m_istatus;
}

int GET_CheckMCN_AH_Impl::sendEMail()
{
    int iNumResourcePoolUsers = 0;

    tag_t* ptUsers = NULL;
    char* pszEmailID = NULL;

    string strSubject   = EMPTY_STRING_VALUE;
    string strContent   = EMPTY_STRING_VALUE;
    string strPartNR    = EMPTY_STRING_VALUE;
    string strMisOrg    = EMPTY_STRING_VALUE;
    string strMisMatMB  = EMPTY_STRING_VALUE;
    string strMissingSM = EMPTY_STRING_VALUE;
    string strSystemCMD = EMPTY_STRING_VALUE;
    string strNoAssmbly = EMPTY_STRING_VALUE;
    string strMissStatus= EMPTY_STRING_VALUE;
    string strUnConfigured= EMPTY_STRING_VALUE;
    string sUnRelStockMatl= EMPTY_STRING_VALUE;
    string sUOMRFItem     = EMPTY_STRING_VALUE;
    string sSiteID=         EMPTY_STRING_VALUE;
    string strPartCO      = EMPTY_STRING_VALUE;
    string strMfgAttrFormCO    = EMPTY_STRING_VALUE;
	string strVerifyAssembly = EMPTY_STRING_VALUE;

    sSiteID = getSiteID();

    vector<string> vEmailIDs;

    LOG_TRACE(logger, "Entering...sendEMail");
	
    try {
        for (this->m_ErrorMsgItr = this->m_mapErrorMsg.begin(); this->m_ErrorMsgItr != this->m_mapErrorMsg.end(); ++this->m_ErrorMsgItr)
        {
           int iIndex = this->m_ErrorMsgItr->first;

           switch(iIndex) {
			case ERROR_ENG_PART_NOT_VERIFIED:
			{
				for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) 
				{
					if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE )
					{
						vector<string> vPipeSplitted;
                        GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);	
                        strVerifyAssembly = strVerifyAssembly + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td><td>" + vPipeSplitted[4] + "</td></tr>";			
					}
				}
				break;
			}
            case  ERROR_PART_NOT_REL_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strPartNR = strPartNR + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td></tr>";
                        }
                    }
                   break;
               }
            case  ERROR_PART_CO_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strPartCO = strPartCO + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td><td>" + vPipeSplitted[4] + "</td></tr>";
                        }
                    }
                   break;
               }
            case  ERROR_MFG_ATTR_FORM_CO_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strMfgAttrFormCO = strMfgAttrFormCO + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td></tr>";
                        }
                    }
                   break;
               }
            case  ERROR_MISSING_ORG_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {

                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strMisOrg = strMisOrg + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td></tr>";
                        }
                    }
                   break;
               }
             case  ERROR_MAKE_BUY_MISMATCH:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strMisMatMB = strMisMatMB + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td></tr>";
                        }
                    }
                   break;
               }
             case  ERROR_NO_STOCK_MTRL_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strMissingSM = strMissingSM + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td></tr>";
                        }
                    }
                   break;
               }
             case  ERROR_NO_PRELIM_ASMBLY_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strNoAssmbly = strNoAssmbly + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td></tr>";
                        }
                   }
                   break;
               }
             case  ERROR_NO_PRELIM_STATUS_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                            vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strMissStatus = strMissStatus + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><tr>";
                        }
                   }
                   break;
               }
              case  ERROR_UNCONFIGURED_BOMLINE_INDEX:
               {
                   for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                        if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {
							vector<string> vPipeSplitted;
                            GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                            strUnConfigured = strUnConfigured + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td></tr>";
                        }
                   }
                   break;
               }
              case  ERROR_NO_STOCK_MTRL_REL_INDEX:
               {
                 for(int inx = 0;  inx < this->m_ErrorMsgItr->second.size();  inx++) {
                      if(this->m_ErrorMsgItr->second[inx] != EMPTY_STRING_VALUE) {

                          vector<string> vPipeSplitted;
                          GET_splitString(this->m_ErrorMsgItr->second[inx], PIPE_DELIM_VALUE, vPipeSplitted);
                          sUnRelStockMatl = sUnRelStockMatl + "<tr><td>" + vPipeSplitted[0] + "</td><td>" + vPipeSplitted[1] + "</td><td>" + vPipeSplitted[2] + "</td><td>" + vPipeSplitted[3] + "</td><td>" + vPipeSplitted[4] + "</td><td>" + vPipeSplitted[5] + "</td></tr>";
                      }
                }
                 break;
             }
			 
           }
        }

        strSubject = this->m_strSubject +" " + this->m_strMCNID + " : Has been sent back for correction!" + sSiteID;

        strContent = "<html><h3 style=\"color: #2e6c80;\">Dear User,</h3>";
        strContent = strContent  + "<p style=\"color:#2035E5\"><strong style=\"color: #2e6c80;\"> " + this->m_strMCNID + "</strong> has been sent back for the following corrections</p><ul>";

        if(tc_strcmp(EMPTY_STRING_VALUE, strVerifyAssembly.c_str())) {
			strContent = strContent  + "<li style=\"color:#2035E5\">Following Engineering parts are not verified .</li><br/>";
            strContent = strContent  +  strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Verified Part</td><td>Reason</td></tr>";
            strContent = strContent  + strVerifyAssembly ;
            strContent = strContent  + "</tbody></table><br/>";
        }
		
		if(tc_strcmp(EMPTY_STRING_VALUE, strUnConfigured.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Parts in BOM Assembly are Un-Configured, please try the following solutions</li><ul><li style=\"color:#2035E5\">Remove un-configured line from structure</li></ul><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td></tr>";
            strContent = strContent  + strUnConfigured ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strPartNR.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Parts in MBOM Assembly are not Released or carrying invalid Release status, please try the following solutions</li><ul><li style=\"color:#2035E5\">Paste newly created Manufacturing parts from structure to Solution Items folder</li><li style=\"color:#2035E5\">Paste only Released Engineering Parts in Solution Items folder</li></ul><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Reason</td></tr>";
            strContent = strContent  + strPartNR ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strPartCO.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Parts in MBOM Assembly are Checked-Out, please try the following solutions</li><ul><li style=\"color:#2035E5\">Check-in the Object, if it is checked-out by you</li><li style=\"color:#2035E5\">Contact the User who has checked-out</li><li style=\"color:#2035E5\">Contact the Administrator</li></ul><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item RevID</td><td>Item Name</td><td>Item Type</td><td>Checked-Out User</td></tr>";
            strContent = strContent  + strPartCO ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strMfgAttrFormCO.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Mfg Attr Form in MBOM Assembly are Checked-Out, please try the following solutions</li><ul><li style=\"color:#2035E5\">Check-in the Object, if it is checked-out by you</li><li style=\"color:#2035E5\">Contact the User who has checked-out</li><li style=\"color:#2035E5\">Contact the Administrator</li></ul><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Checked-Out User</td></tr>";
            strContent = strContent  + strMfgAttrFormCO ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strMisOrg.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Parts are not associated to Parent Make Organization - " + this->m_strSelectedOrg + "<ul><li style=\"color:#2035E5\">Please assign Make/Buy Value in " + this->m_strSelectedOrg + " to associate them to " + this->m_strSelectedOrg + "</li></ul></li><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Organization ID</td></tr>";
            strContent = strContent  + strMisOrg ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strMisMatMB.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Parts having Engineering Make/Buy conflicting with Manufacturing Make/Buy</li><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Organization ID</td></tr>";
            strContent = strContent  + strMisMatMB ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strMissingSM.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Parts are missing one of the following information <ul><li>Stock Material </li><li>Made From Part </li></ul></li><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Organization ID</td></tr>";
            strContent = strContent  + strMissingSM ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strNoAssmbly.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Part does not have Assembly <ul><li>For Preliminary Release GET Manufacturing Item should have children.</li>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>Organization ID</td></tr>";
            strContent = strContent  + strNoAssmbly ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, strMissStatus.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Following Parts in Preliminary Assembly are not Released or carrying invalid Release status</li><ul><li style=\"color:#2035E5\">Paste only newly created Manufacturing parts from structure to Solution Items folder</li><li style=\"color:#2035E5\">Only Released Item Revision are allowed in Preliminary Assembly/Structure</li></ul><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td></tr>";
            strContent = strContent  + strMissStatus ;
            strContent = strContent  + "</tbody></table><br/>";
        }

        if(tc_strcmp(EMPTY_STRING_VALUE, sUnRelStockMatl.c_str())) {
            strContent = strContent  + "<li style=\"color:#2035E5\">Stock Materials attach to following Engineering parts are not Released.</li><br/>";
            strContent = strContent  + "<table style=\"width: 50%; border-collapse: collapse;\" border=\"1\"><tbody><tr style=\"width: 50%; border-collapse: collapse; background-color: #2e6c80; color: white;\"><td>Item ID</td><td>Item Name</td><td>Item Type</td><td>StockMaterial ID</td><td>StockMaterial Name</td><td>StockMaterial Type</td></tr>";
            strContent = strContent  + sUnRelStockMatl ;
            strContent = strContent  + "</tbody></table><br/>";
        }
		
		strContent =  strContent  + "</ul><br/><p style=\"color:#2035E5\">Please correct the above errors,<br/><h3 style=\"color: #2e6c80;\">Thanks.</h3></p></html>";
        LOG_TRACE(logger, "strContent-->" + strContent);
		
		// Split the input recipient argument into Group and role filed
        vector<string> vGroupRole;
        GET_splitString ( this->m_strRecipientID, COLON_CHAR_VALUE, vGroupRole );

        if ( vGroupRole.size() != 2 )
        {
            string sMsg = "The Workflow handler argument \"" + string ( RECIPIENT_ARGUMENT_VALUE )
                           + "\"  is not in required format, Format must be Group:Role ";
            THROW ( sMsg );
        }

        LOG_TRACE(logger, "vGroupRole[0]-->" + vGroupRole[0]);
		LOG_TRACE(logger, "vGroupRole[1]-->" + vGroupRole[1]);
		
		vector<GET_GroupMemberUnqPtr> vGroupMemberUnqPtr = GET_GroupMember::find( vGroupRole[0], vGroupRole[1] );

        // Loop through each group member and send email
        for ( int iInx = 0; iInx < vGroupMemberUnqPtr.size(); iInx++ )
        {
            GET_POM_userShrPtr pUser = vGroupMemberUnqPtr[iInx]->getUser();
            GET_PersonUnqPtr person = pUser->getPerson();
            vEmailIDs.push_back ( person->getEmailId() );
        }
        if ( vEmailIDs.size() > 0 )
        {
           sendMailAsHtml ( vEmailIDs, strSubject, strContent );
        }
    }
    catch (GET_Exception *ex)
    {
		string sMessage = "sendEMail failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR(logger, sMessage);
        LOG_ERROR(logger, ex->getErrorMessage());
        EMH_store_error_s1(EMH_severity_user_error, GET_general_exception, sMessage.c_str());
    }

    LOG_TRACE(logger, "Exiting...sendEMail");
	
	return this->m_istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   validateMCN()
//
//    Purpose:   Function to Validate MCN objects
//
//    Inputs:    none
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     21 Aug, 2017         MCN restructuring
//
===========================================================================
//ENDFUNCDOC   ***/
int GET_CheckMCN_AH_Impl::validateMCN()
{
    string sFlipToMake = EMPTY_STRING_VALUE;

    vector<GET_ItemRevisionShrPtr>  getItemRevList;
    vector<GET_ItemRevisionShrPtr>  getBOMRevList;
    vector<GET_ItemRevisionShrPtr>  getStockMaterialList;
    vector<GET_ItemRevisionShrPtr>  getPartMadeFromPartList;
    vector<GET_POM_objectShrPtr>    getPOMObjShrPtr;

    LOG_TRACE(logger, "Entering....validateMCN");
	
    // Get the all MCN allowed object type revisions from the preference
    getStringPrefValues ( CM_VALID_MCN_OBJECTS, this->m_vValidMCNObjects );
    if ( this->m_vValidMCNObjects.size() == 0 )
    {
        string sMessage = "The Preference " + string( CM_VALID_MCN_OBJECTS ) + " is not defined or does not have a value";
        THROW ( sMessage );
    }

    // Validate the arguments supplied
    if ( this->m_vArguments.find ( RELATION_TYPE ) == this->m_vArguments.end () || this->m_vArguments[RELATION_TYPE].empty() )
    {
        string sMsg = "The Workflow handler argument \"" + string ( RELATION_TYPE ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( this->m_vArguments.find ( WORKFLOW_TYPE_NAME ) == this->m_vArguments.end () || this->m_vArguments[WORKFLOW_TYPE_NAME].empty () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( WORKFLOW_TYPE_NAME ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( this->m_vArguments.find ( ARG_REVISION_RULE ) == this->m_vArguments.end () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( ARG_REVISION_RULE ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }
    if ( this->m_vArguments.find ( SUBJECT_HANDLER_ARG ) == this->m_vArguments.end () )
    {
        string sMsg = "The Workflow handler argument \"" + string ( SUBJECT_HANDLER_ARG ) + "\"  is missing or is empty";
        THROW ( sMsg );
    }

    // Get Revision Rule as workflow argument for Preliminary Release Workflow.
    this->m_strRevisionRule = this->m_vArguments[ARG_REVISION_RULE];
    this->m_strSubject = this->m_vArguments[SUBJECT_HANDLER_ARG];
    
    // Read the recipient id from workflow argument
    for ( this->m_vArgumentsItr = this->m_vArguments.begin(); this->m_vArgumentsItr != this->m_vArguments.end(); ++this->m_vArgumentsItr )
    {
        if ( this->m_vArgumentsItr->first == RECIPIENT_ARGUMENT_VALUE )
        {
            this->m_strRecipientID = this->m_vArgumentsItr->second;
            break;
        }
    }

    if ( ( this->m_vArguments[WORKFLOW_TYPE_NAME].compare ( WORKFLOW_NAME_MCN ) == 0 ) && ( this->m_strRevisionRule.compare(EMPTY_STRING_VALUE ) == 0 ) )
    {
        
		// Code for GET MCN Process Workflow
        for ( size_t iTargetIndex = 0; iTargetIndex < this->m_vAttachments[ EPM_target_attachment ].size(); iTargetIndex++ )
        {
            // Validate if MCN Revision is found in target object
            if ( ! GET_POM_object::isDescendant ( this->m_vAttachments[EPM_target_attachment][iTargetIndex], GET_MCN_REVISION_CLASS ) )
            {
                continue;
            }
            
            GET_ItemRevisionUnqPtr getItemRevUnqPtr = GET_ItemRevision::getInstance ( this->m_vAttachments [ EPM_target_attachment ][iTargetIndex] );
            LOG_TRACE ( logger, "getItemRevUnqPtr->getType()-->" + getItemRevUnqPtr->getType() );
            GET_ItemRevisionShrPtr mcnRevShrPtr ( move ( getItemRevUnqPtr ) );

            // Check if MCN is for FlipToMake operation
            sFlipToMake = mcnRevShrPtr->getPropString ( MCN_FLIP_TO_MAKE_PROP );

            if ( sFlipToMake.compare ( MCN_LOV_TRUE_VALUE ) == 0 )
            {
                sFlipToMake = EMPTY_STRING_VALUE;
                mcnRevShrPtr->setProp ( MCN_FLIP_TO_MAKE_PROP, sFlipToMake );
                string sMsg = "MCN is for Flip To Make operation, Please update Make/Buy value and complete Add MBOM task";
                THROW ( sMsg );
            }
            
            this->m_strSelectedOrg = mcnRevShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
            LOG_TRACE ( logger, "this->m_strSelectedOrg-->" + this->m_strSelectedOrg );
			
            this->m_strMCNID = mcnRevShrPtr->getItem()->getId();
            LOG_TRACE(logger, "this->m_strMCNID-->" + this->m_strMCNID);
			
            vector<GET_POM_objectUnqPtr> vSolutionItems = mcnRevShrPtr->getPropTags ( this->m_vArguments[RELATION_TYPE] );
            for( size_t iSolIndex = 0; iSolIndex < vSolutionItems.size(); iSolIndex++ )
            {
                string solObjType = vSolutionItems[iSolIndex]->getPropertyString ( OBJECT_TYPE );

                // Check the Solution Item object type
                if ( GET_isInVector ( this->m_vValidMCNObjects, solObjType ) )
                {
                    GET_ItemRevisionUnqPtr getItemRevUnqPtr = GET_ItemRevision::getInstance ( vSolutionItems[iSolIndex]->getTag() );
                    GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( getItemRevUnqPtr ) );
                    this->m_vSolutionItems.push_back ( getItemRevShrPtr );
				}
            }

            // MCN Revision found in Target, so break the loop
            break;
        }
        LOG_TRACE ( logger, "Count of Valid Target object List from MCN Solution Items => " + this->m_vSolutionItems.size() );
		
		for ( size_t iValidSolIndex = 0; iValidSolIndex < this->m_vSolutionItems.size(); iValidSolIndex++ )
        {
            GET_BOMViewRevisionShrPtr getBOMViewRevisionShrPtr;
            GET_BOMWindowUnqPtr getBOMWindowUnqPtr = GET_BOMWindow::create();

            getBOMWindowUnqPtr->setRevisionRule ( this->getManufacturingRevisionRule ( false ) );
            GET_BOMWindowShrPtr getBOMWindowShrPtr( move ( getBOMWindowUnqPtr ) );

            GET_BOMLineUnqPtr getBOMLineUnqPtr = getBOMWindowShrPtr->setTopLine( this->m_vSolutionItems[iValidSolIndex], getBOMViewRevisionShrPtr );
            GET_BOMLineShrPtr getBOMLineShrPtr ( move ( getBOMLineUnqPtr ) );
           
            // Call recurseMFG method to traverse to its BOMLine components
            this->m_istatus = this->recurseMFG ( getBOMLineShrPtr, getItemRevList, getBOMRevList, getStockMaterialList, getPartMadeFromPartList );
		}
    }
    else if ( ( this->m_vArguments[WORKFLOW_TYPE_NAME].compare ( WORKFLOW_NAME_PRELIM ) == 0 ) && ( this->m_strRevisionRule.compare(EMPTY_STRING_VALUE) != 0 ) )
    {
        // Code for Preliminary Release Workflow.
        this->m_istatus = this->validatePreliminaryMCN();
    }

    if ( ! this->vWarningMessages.empty() )
    {
        this->m_istatus = this->sendUOMWarningEMail ( this->vWarningMessages );
    }

    if ( ! this->m_mapErrorMsg.empty() )
    {
        this->m_istatus = this->sendEMail();
        THROW ( MCN_HAS_BEEN_SENT_BACK_ERROR );
    }

    if ( this->vWarningMessages.empty() && this->m_mapErrorMsg.empty() )
    {
        LOG_TRACE ( logger, "MBOM Traversal and Validation Logic Completed" );
		LOG_TRACE ( logger, "Creation of Workflow Reference Folder in progress" );
		
		// Adding Items to ITEM Folder
        if ( getItemRevList.size() > 0 )
        {
            this->m_istatus = addObjectsToRefFolder ( getItemRevList, FOLDERTYPE, OBJECT_ITEM,
                    "Holds Child Items to be Transfered to Oracle", getPOMObjShrPtr );
        }
        // Adding Part Items to PartMadeFromPart Folder
        if ( getPartMadeFromPartList.size() > 0 )
        {
            this->m_istatus = addObjectsToRefFolder ( getPartMadeFromPartList, FOLDERTYPE, OBJECT_PMFP,
                    "Holds Child Items to be Transfered to Oracle", getPOMObjShrPtr );
        }
        // Adding SM Items to STOCK_MATERIAL Folder
        if ( getStockMaterialList.size() > 0 )
        {
            this->m_istatus = addObjectsToRefFolder ( getStockMaterialList, FOLDERTYPE, OBJECT_SM,
                    "Holds Child Items to be Transfered to Oracle", getPOMObjShrPtr );
        }
        // Adding objects to BOM Folder
        if ( getBOMRevList.size() > 0 )
        {
            this->m_istatus = addObjectsToRefFolder ( getBOMRevList, FOLDERTYPE, OBJECT_BOM,
                    "Holds Child Items to be Transfered to Oracle", getPOMObjShrPtr );
        }

        //Adding folders to to EPM Task
        GET_EPMTaskUnqPtr getEPMTaskUnqPtr = GET_EPMTask::getInstance ( this->m_tTaskTag );
        getEPMTaskUnqPtr->addAttachments ( EPM_reference_attachment, getPOMObjShrPtr );

        getItemRevList.clear();
        getBOMRevList.clear();
        getStockMaterialList.clear();
        getPartMadeFromPartList.clear();
    }

    LOG_TRACE ( logger, "Exiting....validateMCN" );
	return this->m_istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   recurseMFG()
//
//    Purpose:   Function to recurse Mfg objects
//
//    Inputs:    BOMLine
//
//    Outputs:   Vector of Item, BOM, Stock Material and Made From Part
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     21 Aug, 2017         MCN restructuring
//  TCS Development Team     11 Nov, 2017         Added Workflow handler argument for validating BOM structure
//  TCS Development Team     27 Nov, 2017         Updated recurse logic for getting all errornous data validated upfront
//
===========================================================================
//ENDFUNCDOC   ***/
int GET_CheckMCN_AH_Impl::recurseMFG ( GET_BOMLineShrPtr p_getBOMLineShrPtr , vector<GET_ItemRevisionShrPtr>& vItemRevList,
        vector<GET_ItemRevisionShrPtr>& vBOMRevList, vector<GET_ItemRevisionShrPtr>& vSMRevList, vector<GET_ItemRevisionShrPtr>& vPartMadeFromPartRevList )
{
    string sUOMValue = EMPTY_STRING_VALUE;

    LOG_TRACE(logger, "Entering...recurseMFG");
	GET_ItemRevisionUnqPtr getParentItemRevUnqPtr = p_getBOMLineShrPtr->getItemRevision();

    // Check whether BOMLine is configured or unconfigured
    if ( getParentItemRevUnqPtr == NULL || getParentItemRevUnqPtr.get() == NULL )
    {
        GET_ItemUnqPtr getItemUnqPtr = p_getBOMLineShrPtr->getItem();
		this->logErrorMessage ( ERROR_UNCONFIGURED_BOMLINE_INDEX, getItemUnqPtr->getId() + string(PIPE_DELIM_VALUE) + getItemUnqPtr->getName() + string(PIPE_DELIM_VALUE) + getItemUnqPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) );
	}
    else
    {
        GET_ItemRevisionShrPtr getParentItemRevShrPtr ( move ( getParentItemRevUnqPtr ) );
       
        // Check if Item is already processed, if not then only process
        if ( ! ( std::find ( this->m_vProcessedItems.begin(), this->m_vProcessedItems.end(), getParentItemRevShrPtr->getTag() ) != this->m_vProcessedItems.end() ) )
        {
			this->m_vProcessedItems.push_back ( getParentItemRevShrPtr->getTag() );
            
            // Check if BOMline object is allowed object type
            if ( GET_isInVector ( this->m_vValidMCNObjects, getParentItemRevShrPtr->getType() ) )
            {
                sUOMValue = getParentItemRevShrPtr->getItem()->getPropValueAsString ( UOM_TAG_PROP );
               
                // Check for UOM value
                if ( sUOMValue.compare ( UOM_RF_VALUE ) == 0 )
                {
                    string sParentName = p_getBOMLineShrPtr->getStringProperty ( bomAttr_formattedParentName );
                    string sContent = getParentItemRevShrPtr->getId() + string ( PIPE_DELIM_VALUE ) + getParentItemRevShrPtr->getName() + string ( PIPE_DELIM_VALUE ) + getParentItemRevShrPtr->getPropValueAsString ( OBJECT_TYPE_ATTR ) + string ( PIPE_DELIM_VALUE ) + sParentName + string ( PIPE_DELIM_VALUE );
                    vWarningMessages.push_back ( sContent );
                }
                else
                {
                    vector<GET_FormShrPtr> vSecondaryFormObjs = this->getOrgItems ( getParentItemRevShrPtr );

                    // Validate the Structure only if -validate workflow handler arg is provided,
                    // otherwise no need to validate the BOM, just BOM traversal is needed
                    if ( this->m_vArguments.find ( VALIDATE_ARG ) != this->m_vArguments.end() )
                    {
                        this->m_istatus = this->checkVerifiedAssembly ( p_getBOMLineShrPtr );
						this->m_istatus = this->checkReleaseStatus ( getParentItemRevShrPtr );
						this->m_istatus = this->validateCheckOutStatus ( getParentItemRevShrPtr );
						this->m_istatus = this->checkParentOrgItem ( getParentItemRevShrPtr, vSecondaryFormObjs );
						this->m_istatus = this->checkStockMaterial ( getParentItemRevShrPtr, vSecondaryFormObjs );
					}

                    // Check last modified date is greater than oracle publish date - Item
                    if ( this->checkItemPublishDate ( getParentItemRevShrPtr, vSecondaryFormObjs )  && GET_ExistsInVector ( vItemRevList, getParentItemRevShrPtr ) == false )
                    {
                        // Adding valid Item to ITEM folder
                        vItemRevList.push_back ( getParentItemRevShrPtr );
					}

                    if ( this->hasMakeOrgItem ( getParentItemRevShrPtr ) )
                    {
                       vector<GET_BOMLineUnqPtr> vBOMLineChildren = p_getBOMLineShrPtr->getChildren();

                        // If Item has children continue for BOM Publish Date validation except for MFP part
                        if ( vBOMLineChildren.size() > 0 )
                        {
							for ( int inx = 0; inx < vBOMLineChildren.size(); inx++ )
                            {
                                GET_BOMLineShrPtr getBOMLineShrPtr ( move ( vBOMLineChildren[inx] ) );
                                this->m_istatus = this->recurseMFG ( getBOMLineShrPtr, vItemRevList, vBOMRevList, vSMRevList, vPartMadeFromPartRevList );
							}
                            if ( this->checkBOMPublishDate ( getParentItemRevShrPtr, vSecondaryFormObjs ) && GET_ExistsInVector ( vBOMRevList, getParentItemRevShrPtr ) == false )
                            {
                            	vBOMRevList.push_back ( getParentItemRevShrPtr );
							}
                        }

                        if ( this->checkItemPublishDate ( getParentItemRevShrPtr, vSecondaryFormObjs ) )
                        {
                            // If no BOM component found, check for Made From Part or Stock Material
                            if ( vBOMLineChildren.size() == 0 && ( getParentItemRevShrPtr->getType().compare( MECHREV_TYPE ) == 0
                                    || getParentItemRevShrPtr->getType().compare( ELECREV_TYPE ) == 0 || getParentItemRevShrPtr->getType().compare( SOFTREV_TYPE ) == 0 ) )
                            {
                                
								// Check for Part Made From Part
                                vector<GET_POM_objectUnqPtr> getMadeFromPartUnqPtr = getParentItemRevShrPtr->getItem()->getPropTags ( MADE_FROM_PART_PROP );
                                LOG_TRACE( logger, "getMadeFromPart -->" + GET_intToString ( getMadeFromPartUnqPtr.size() ) );
								
								// If Part Made From Part found
                                if ( getMadeFromPartUnqPtr.size() > 0 && GET_ExistsInVector ( vPartMadeFromPartRevList, getParentItemRevShrPtr ) == false )
                                {
                                    vPartMadeFromPartRevList.push_back ( getParentItemRevShrPtr );

                                    GET_ItemUnqPtr partMadeFromPartItemUnqPtr = GET_Item::getInstance ( getMadeFromPartUnqPtr[0]->getTag() );
                                    GET_ItemRevisionUnqPtr partMadeFromPartRevUnqPtr = partMadeFromPartItemUnqPtr->getLatestReleasedRevision();

                                    if ( partMadeFromPartRevUnqPtr.get() != NULL && partMadeFromPartRevUnqPtr->getTag() != NULLTAG )
                                    {
										GET_ItemRevisionShrPtr partMadeFromPartRevShrPtr ( move ( partMadeFromPartRevUnqPtr ) );

										// Call function to get recurse Part Made From Part
										recurseMadeFromParts ( partMadeFromPartRevShrPtr, vItemRevList, vBOMRevList, vSMRevList, vPartMadeFromPartRevList );
                                    }
                                    else
                                    {
                                    	// If the initital revision itself is working then error out
                                    	GET_ItemRevisionUnqPtr partMadeFromPartRevUnqPtr = partMadeFromPartItemUnqPtr->getLatestRevision();
                                    	GET_ItemRevisionShrPtr partMadeFromPartRevShrPtr ( move ( partMadeFromPartRevUnqPtr ) );
                                    	this->m_istatus = this->checkReleaseStatus ( partMadeFromPartRevShrPtr );
                                    	this->m_istatus = this->validateCheckOutStatus ( partMadeFromPartRevShrPtr );
                                    }
								}

                                // If Part Made From Part not found, check for Stock Material
                                if ( getMadeFromPartUnqPtr.size() == 0 )
                                {
                                    // Check for Part with Stock Material
                                    vector<GET_POM_objectUnqPtr> getMaterialObject = getParentItemRevShrPtr->getItem()->getPropTags ( MADE_FROM_MATL_PROP );
                                    LOG_TRACE ( logger, "getMaterialObject -->" + GET_intToString ( getMaterialObject.size() ) );
									
                                    //GET_FormShrPtr makeOrgFormShrPtr = this->getOrgForm ( getParentItemRevShrPtr );
                                    GET_FormShrPtr makeOrgFormShrPtr = getSameOrgForm ( getParentItemRevShrPtr, this->m_strSelectedOrg );
                                    if ( makeOrgFormShrPtr.get() != NULL && makeOrgFormShrPtr->getTag() != NULLTAG )
                                    {
                                        // Get all objects from Solution folder
                                        GET_POM_objectUnqPtr stockMaterialUnqPtr = makeOrgFormShrPtr->getPropTag ( STOCK_MATERIAL_PROP );
										if ( stockMaterialUnqPtr.get() != NULL && stockMaterialUnqPtr->getTag() != NULLTAG )
                                        {
                                            // Adding Make piece part to Stock Material folder
                                            if ( GET_ExistsInVector ( vSMRevList, getParentItemRevShrPtr ) == false )
                                            {
                                                vSMRevList.push_back( getParentItemRevShrPtr );
                                            }
                                            
                                            GET_ItemUnqPtr stockMaterialItemUnqPtr = GET_Item::getInstance ( stockMaterialUnqPtr->getTag() );
                                            GET_ItemRevisionUnqPtr stockMaterialRevUnqPtr = stockMaterialItemUnqPtr->getLatestReleasedRevision();

                                            if ( stockMaterialRevUnqPtr.get() != NULL && stockMaterialRevUnqPtr->getTag() != NULLTAG )
                                            {
                                            	GET_ItemRevisionShrPtr stockMaterialRevShrPtr ( move ( stockMaterialRevUnqPtr ) );

                                            	// Adding Stock Material to ITEM folder list
												if ( GET_ExistsInVector ( vItemRevList, stockMaterialRevShrPtr ) == false )
												{
												   vItemRevList.push_back( stockMaterialRevShrPtr );
												}
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    LOG_TRACE(logger, "Exiting...recurseMFG");
	return this->m_istatus;
}

int GET_CheckMCN_AH_Impl::recurseMadeFromParts ( GET_ItemRevisionShrPtr getItemRevShrPtr, vector<GET_ItemRevisionShrPtr>& vItemRevList,
    vector<GET_ItemRevisionShrPtr>& vBOMRevList, vector<GET_ItemRevisionShrPtr>& vSMRevList, vector<GET_ItemRevisionShrPtr>& vPartMadeFromPartRevList )
{
    int iStatus = ITK_ok;

    LOG_TRACE ( logger, "START: recurseMadeFromParts method" );
	
	if ( getItemRevShrPtr->getType().compare( MECHREV_TYPE ) == 0 || getItemRevShrPtr->getType().compare( ELECREV_TYPE ) == 0
        || getItemRevShrPtr->getType().compare( SOFTREV_TYPE ) == 0 )
    {
        vector<GET_FormShrPtr> vOrgFormObjs = this->getOrgItems ( getItemRevShrPtr );

        this->m_istatus = this->checkReleaseStatus ( getItemRevShrPtr );
        this->m_istatus = this->validateCheckOutStatus ( getItemRevShrPtr );
        this->m_istatus = this->checkParentOrgItem ( getItemRevShrPtr, vOrgFormObjs );
        this->m_istatus = this->checkStockMaterial ( getItemRevShrPtr, vOrgFormObjs );

        if ( this->hasMakeOrgItem ( getItemRevShrPtr ) )
        {
            vector<GET_POM_objectUnqPtr> vChildObjectsList = getItemRevShrPtr->getPropTags ( PSCHILDREN_ATTR );

            // Check ITEM Publish date
            if ( this->checkItemPublishDate ( getItemRevShrPtr, vOrgFormObjs ) && GET_ExistsInVector ( vItemRevList, getItemRevShrPtr ) == false )
            {
                vItemRevList.push_back ( getItemRevShrPtr );
            }

			// Process if MadeFromPart Item is not an assembly
			if ( vChildObjectsList.size() == 0 )
			{
				// Make Item found - continue for Made From Another Part to next Made From Another Part
				vector<GET_POM_objectUnqPtr> getMadeFromPartUnqPtr = getItemRevShrPtr->getItem()->getPropTags ( MADE_FROM_PART_PROP );
				LOG_TRACE(logger, "getMadeFromPart -->" + GET_intToString( getMadeFromPartUnqPtr.size() ) );
				
				if ( getMadeFromPartUnqPtr.size() > 0 )
				{
					// Check ITEM Publish date
					if ( this->checkItemPublishDate ( getItemRevShrPtr, vOrgFormObjs ) && GET_ExistsInVector ( vPartMadeFromPartRevList, getItemRevShrPtr ) == false )
					{
						vPartMadeFromPartRevList.push_back ( getItemRevShrPtr );
					}

					GET_ItemUnqPtr partMadeFromPartItemUnqPtr = GET_Item::getInstance ( getMadeFromPartUnqPtr[0]->getTag() );
					GET_ItemRevisionUnqPtr partMadeFromPartRevUnqPtr = partMadeFromPartItemUnqPtr->getLatestReleasedRevision();

					if ( partMadeFromPartRevUnqPtr.get() != NULL && partMadeFromPartRevUnqPtr->getTag() != NULLTAG )
					{
						GET_ItemRevisionShrPtr partMadeFromPartRevShrPtr ( move ( partMadeFromPartRevUnqPtr ) );

						// Call recurse method
						recurseMadeFromParts ( partMadeFromPartRevShrPtr, vItemRevList, vBOMRevList, vSMRevList, vPartMadeFromPartRevList );
					}
					else
					{
						// If the initital revision itself is working then error out
						GET_ItemRevisionUnqPtr partMadeFromPartRevUnqPtr = partMadeFromPartItemUnqPtr->getLatestRevision();
						GET_ItemRevisionShrPtr partMadeFromPartRevShrPtr ( move ( partMadeFromPartRevUnqPtr ) );
						this->m_istatus = this->checkReleaseStatus ( partMadeFromPartRevShrPtr );
						this->m_istatus = this->validateCheckOutStatus ( partMadeFromPartRevShrPtr );
					}
				}

				//Stock material
				if ( getMadeFromPartUnqPtr.size() == 0 )
				{
					// Check ITEM Publish date
					if ( this->checkItemPublishDate ( getItemRevShrPtr, vOrgFormObjs ) )
					{
						// get stock material and end Made from another part
						vector<GET_POM_objectUnqPtr> getMaterialObject = getItemRevShrPtr->getItem()->getPropTags ( MADE_FROM_MATL_PROP );
						LOG_TRACE ( logger, "getMaterialObject -->" + GET_intToString ( getMaterialObject.size() ) );
						
						//GET_FormShrPtr makeOrgFormShrPtr = this->getOrgForm ( getItemRevShrPtr );
						GET_FormShrPtr makeOrgFormShrPtr = getSameOrgForm ( getItemRevShrPtr, this->m_strSelectedOrg );
						if ( makeOrgFormShrPtr.get() != NULL && makeOrgFormShrPtr->getTag() != NULLTAG )
						{
							GET_POM_objectUnqPtr stockMaterialUnqPtr = makeOrgFormShrPtr->getPropTag ( STOCK_MATERIAL_PROP );
							if ( stockMaterialUnqPtr.get() != NULL && stockMaterialUnqPtr->getTag() != NULLTAG )
							{
								// Adding Make piece part to Stock Material folder
								if ( GET_ExistsInVector ( vSMRevList, getItemRevShrPtr ) == false )
								{
									vSMRevList.push_back ( getItemRevShrPtr );
								}

								GET_ItemUnqPtr stockMaterialItemUnqPtr = GET_Item::getInstance ( stockMaterialUnqPtr->getTag() );
								GET_ItemRevisionUnqPtr stockMaterialRevUnqPtr = stockMaterialItemUnqPtr->getLatestReleasedRevision();

								if ( stockMaterialRevUnqPtr.get() != NULL && stockMaterialRevUnqPtr->getTag() != NULLTAG )
								{
									GET_ItemRevisionShrPtr stockMaterialRevShrPtr ( move ( stockMaterialRevUnqPtr ) );

									// Adding Stock Material to ITEM folder list
									if ( GET_ExistsInVector ( vItemRevList, stockMaterialRevShrPtr ) == false )
									{
									   vItemRevList.push_back( stockMaterialRevShrPtr );
									}
								}
							}
						}
					}
				}
			}
        }
        else if ( this->checkItemPublishDate ( getItemRevShrPtr, vOrgFormObjs ) && GET_ExistsInVector ( vItemRevList, getItemRevShrPtr ) == false )
        {
            vItemRevList.push_back ( getItemRevShrPtr );
        }
    }

    LOG_TRACE ( logger, "END: recurseMadeFromParts method" );
	
	return iStatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   addObjectsToRefFolder()
//
//    Purpose:   Function to add the objects to Workflow Reference folder
//
//    Inputs:    Vector of objects to be added to Reference folder, Object Type, Folder Name, Folder Description
//
//    Outputs:   Vector of POM Folder object
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     17 Jun, 2016         Initial creation
//  TCS Development Team     27 Sep, 2017         MCN restructuring
//
===========================================================================
//ENDFUNCDOC   ***/
int GET_CheckMCN_AH_Impl::addObjectsToRefFolder ( vector<GET_ItemRevisionShrPtr> vObjectRevList, string sObjectType, string sfolderName, string sfolderDecs, vector<GET_POM_objectShrPtr>& vPOMObjShrPtr )
{
    LOG_TRACE(logger, "START : addObjectsToRefFolder method");
	
	GET_FolderUnqPtr getFolderUnqPtr = GET_Folder::create ( sObjectType, sfolderName, sfolderDecs );

    for( size_t iObjRevIndex = 0; iObjRevIndex < vObjectRevList.size(); iObjRevIndex++ )
    {
        GET_WorkspaceObjectShrPtr getWSObjShrPtr ( move ( GET_WorkspaceObject::getInstance ( vObjectRevList[iObjRevIndex]->getTag() ) ) );
        getFolderUnqPtr->insertInto ( getWSObjShrPtr, iObjRevIndex );
    }

    // convert folder object in proper format to add in EPM Task
    GET_POM_objectShrPtr getPOMITEMFolderObjShrPtr ( move ( GET_POM_object::getInstance ( getFolderUnqPtr->getTag() ) ) );
    vPOMObjShrPtr.push_back ( getPOMITEMFolderObjShrPtr );

    LOG_TRACE(logger, "Exiting...addObjectsToRefFolder");
	return this->m_istatus;
}

string GET_CheckMCN_AH_Impl::getManufacturingRevisionRule(bool p_isReleasedRule) {

	LOG_TRACE(logger, "Entering...getManufacturingRevisionRule");
	string strRevisionRule = string(REVISION_RULE_PREFIX) + this->m_strSelectedOrg + string((p_isReleasedRule)?RELEASED_REV_RULE_SUFF:WIP_REV_RULE_SUFF);
	LOG_TRACE(logger, "strRevisionRule-->" + strRevisionRule);
	LOG_TRACE(logger, "Exiting...getManufacturingRevisionRule");
	return strRevisionRule;
}

vector<GET_FormShrPtr> GET_CheckMCN_AH_Impl::getOrgItems(GET_ItemRevisionShrPtr p_getItemRevShrPtr) {

	vector<GET_FormShrPtr> vSecondaryOrgForms;

	LOG_TRACE(logger, "Entering...getOrgItems");
	vector<GET_POM_objectUnqPtr> vPOMSecondaryOrgForms = p_getItemRevShrPtr->getItem()->getPropTags(GET_PART_ORG_ATTR_BO);
	
	for(int inx = 0; inx < vPOMSecondaryOrgForms.size(); inx++) {

		GET_POM_objectShrPtr getPOMObjectShrPtr(move(vPOMSecondaryOrgForms[inx]));
		GET_FormUnqPtr getFormUnqPtr = GET_Form::getInstance(getPOMObjectShrPtr->getTag());
		GET_FormShrPtr getFormShrPtr(move(getFormUnqPtr));
		vSecondaryOrgForms.push_back(getFormShrPtr);
	}
    
	LOG_TRACE(logger, "Exiting...getOrgItems");
	
	return vSecondaryOrgForms;
}

vector<string> GET_CheckMCN_AH_Impl::getOrgIDs(vector<GET_FormShrPtr> p_vPartToOrgAttributesForm) {

	string strMakeBuy = EMPTY_STRING_VALUE;
	string strOwningProjectID = EMPTY_STRING_VALUE;
	vector<string> vOrgItemIDs;

	LOG_TRACE(logger, "Entering...getOrgIDs");
	
	for(int inx = 0; inx < p_vPartToOrgAttributesForm.size(); inx++) {
		
		strMakeBuy = p_vPartToOrgAttributesForm[inx]->getPropString(MAKE_BUY_PROP);
		strOwningProjectID = p_vPartToOrgAttributesForm[inx]->getPropertyTag(OWNING_PROJECT_PROP)->getPropertyString(PROJECT_ID_PROP);
		LOG_TRACE(logger, "strOwningProjectID-->" + strOwningProjectID);
		
		if((strMakeBuy != EMPTY_STRING_VALUE) && (strMakeBuy != NONE_VALUE)) {
			vOrgItemIDs.push_back(strOwningProjectID);
		}
	}

	LOG_TRACE(logger, "Exiting...getOrgIDs");
	return vOrgItemIDs;
}

bool GET_CheckMCN_AH_Impl::hasMakeOrgItem(GET_ItemRevisionShrPtr p_getItemRevShrPtr) {

	bool isMakeOrg = false;
	bool isFormFound = false;
	string strMakeBuy = EMPTY_STRING_VALUE;
	string strEngMakeBuy = EMPTY_STRING_VALUE;
	string strOwningProjectID = EMPTY_STRING_VALUE;

	LOG_TRACE(logger, "Entering...hasMakeOrgItem");
	try {

		vector<GET_FormShrPtr> vPartToOrgAttributesForm = this->getOrgItems(p_getItemRevShrPtr);

		for(int inx = 0; inx < vPartToOrgAttributesForm.size(); inx++) {
			strOwningProjectID = vPartToOrgAttributesForm[inx]->getPropertyTag(OWNING_PROJECT_PROP)->getPropertyString(PROJECT_ID_PROP);
			LOG_TRACE(logger, "strOwningProjectID-->" + strOwningProjectID);
			if(this->m_strSelectedOrg == strOwningProjectID) {
				isFormFound = true;
				strMakeBuy = vPartToOrgAttributesForm[inx]->getPropString(MAKE_BUY_PROP);
				LOG_TRACE(logger, "strMakeBuy-->" + strMakeBuy);
				
				if((strMakeBuy != EMPTY_STRING_VALUE) && (strMakeBuy != NONE_VALUE)) 
				{
					if(strMakeBuy == MAKE_VALUE) {
						isMakeOrg = true;
					}

					if((p_getItemRevShrPtr->getType() == GET_ELECT_PART_REV_BO) || (p_getItemRevShrPtr->getType() == GET_MECH_PART_REV_BO) || (p_getItemRevShrPtr->getType() == GET_SOFT_PART_REV_BO)) 
					{
						strEngMakeBuy = p_getItemRevShrPtr->getPropString(ENG_MAKE_BUY_PROP);
						if(strEngMakeBuy == BUY_VALUE) {

							if(strMakeBuy != BUY_VALUE) {
								this->logErrorMessage(ERROR_MAKE_BUY_MISMATCH, (p_getItemRevShrPtr->getId() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getName() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) + strOwningProjectID + string(PIPE_DELIM_VALUE)));
								isMakeOrg = false;
							}
						}
					}
				} 
				else 
				{
					isMakeOrg = true;
				}

				break;
			}
		}

		if(!isFormFound) {
			isMakeOrg = true;
		}

	} catch(...) {

        string sMessage = "getMakeOrgItemIDs failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR(logger, sMessage);
        EMH_store_error_s1(EMH_severity_user_error, GET_general_exception, sMessage.c_str());
		isMakeOrg = false;
    }

	LOG_TRACE(logger, "Exiting...hasMakeOrgItem");
	return isMakeOrg;
}

int GET_CheckMCN_AH_Impl::checkReleaseStatus ( GET_ItemRevisionShrPtr p_getItemRevShrPtr ) {

	bool isValid 		= false;
	int istatus 		= ITK_ok;
	string strItemType 	= EMPTY_STRING_VALUE;
	vector<string> vReleaseStatusList;
	string strRelease = EMPTY_STRING_VALUE;

	LOG_TRACE ( logger, "Entering...checkReleaseStatus" );
	try 
	{
		GET_WorkspaceObjectShrPtr getWorkspaceShrPtr ( move(GET_WorkspaceObject::getInstance ( p_getItemRevShrPtr->getTag() )));
		vReleaseStatusList = getWorkspaceShrPtr->getReleaseStatusList();

		strItemType = getWorkspaceShrPtr->getType();
		if(!vReleaseStatusList.size()) 
		{
			if ( strItemType.compare ( GET_MFG_REV_BO ) ) 
			{
				//isValid = false;
				strRelease = PART_ERROR;
			} 
			else 
			{
				for(int inx = 0; inx < this->m_vSolutionItems.size(); inx++) 
				{
					if(p_getItemRevShrPtr->getTag() == this->m_vSolutionItems[inx]->getTag()) 
					{
						isValid = true;
						break;
					}
					else
					{
						strRelease = PART_ERROR;
					}
				}
			}
		} 
		else 
		{
			if ( !strItemType.compare ( GET_ELECT_PART_REV_BO ) || !strItemType.compare ( GET_MECH_PART_REV_BO ) || !strItemType.compare ( GET_SOFT_PART_REV_BO )) 
			{
				for(int inx = 0; inx < vReleaseStatusList.size(); inx++) 
				{

                 if ( !( vReleaseStatusList[inx].compare ( GET6_RELEASED_VALUE ) )&& !( p_getItemRevShrPtr->hasReleaseStatus ( OBSOLETE_VALUE ) ) )
					{
						isValid = true;
						break;
					}
					else 
					{
						strRelease = OBSOLETE_PART_ERROR;
					}
				}
			} 
			else if ( !strItemType.compare ( GET_MFG_REV_BO ) ) 
			{
				isValid = true;
			}
		}

		if ( !isValid ) 
		{
			
			this->logErrorMessage ( ERROR_PART_NOT_REL_INDEX, p_getItemRevShrPtr->getId() 
		           + string ( PIPE_DELIM_VALUE ) + p_getItemRevShrPtr->getName() 
				   + string ( PIPE_DELIM_VALUE ) + p_getItemRevShrPtr->getPropValueAsString ( OBJECT_TYPE_ATTR ) 
				   + string ( PIPE_DELIM_VALUE ) + strRelease + string ( PIPE_DELIM_VALUE ) );
			
		}

	} catch(...) {

        string sMessage = "checkReleaseStatus failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR(logger, sMessage);
        EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }

	LOG_TRACE ( logger, "Exiting...checkReleaseStatus" );
	return istatus;
}

int GET_CheckMCN_AH_Impl::validateCheckOutStatus ( GET_ItemRevisionShrPtr p_getItemRevShrPtr )
{
	int istatus 		= ITK_ok;

	LOG_TRACE ( logger, "Entering...validateCheckOutStatus" );
	
	GET_WorkspaceObjectShrPtr getWorkspaceShrPtr ( move ( GET_WorkspaceObject::getInstance ( p_getItemRevShrPtr->getTag() ) ) );

	// Verify if Object is Checkout
	if ( getWorkspaceShrPtr->isCheckedOut() )
	{
		GET_POM_userUnqPtr userUnqPtr = getWorkspaceShrPtr->findWhoCheckedOut();
		string sUserName = userUnqPtr->getName();
		
		this->logErrorMessage ( ERROR_PART_CO_INDEX, p_getItemRevShrPtr->getId() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getRevId() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getName() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) + sUserName + string(PIPE_DELIM_VALUE) );
	}

	if ( ( p_getItemRevShrPtr->getType() == GET_ELECT_PART_REV_BO ) || ( p_getItemRevShrPtr->getType() == GET_MECH_PART_REV_BO ) || ( p_getItemRevShrPtr->getType() == GET_SOFT_PART_REV_BO ) || ( p_getItemRevShrPtr->getType() == GET_MFG_REV_BO ) )
	{
		// Get the Form which is associated to the Object for corresponding MCN Org
		GET_FormShrPtr makeOrgFormShrPtr = getSameOrgForm ( p_getItemRevShrPtr, this->m_strSelectedOrg );

		// Process further only when Mfg Attr Form is not NULL
		if ( ( makeOrgFormShrPtr != NULL )  &&  ( makeOrgFormShrPtr.get() != NULL ) )
		{
			// Verify if Object is Checkout
			GET_WorkspaceObjectShrPtr mfgAttrFormWorkspaceShrPtr ( move ( GET_WorkspaceObject::getInstance ( makeOrgFormShrPtr->getTag() ) ) );

			// Verify if Mfg Attr Form is Checkout
			if ( mfgAttrFormWorkspaceShrPtr->isCheckedOut() )
			{
				GET_POM_userUnqPtr userUnqPtr = mfgAttrFormWorkspaceShrPtr->findWhoCheckedOut();
				string sUserName = userUnqPtr->getName();

				this->logErrorMessage ( ERROR_MFG_ATTR_FORM_CO_INDEX, p_getItemRevShrPtr->getId() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getName() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) + sUserName + string(PIPE_DELIM_VALUE) );
			}
		}
	}

	LOG_TRACE ( logger, "Exiting...validateCheckOutStatus" );
	return istatus;
}

int GET_CheckMCN_AH_Impl::checkParentOrgItem(GET_ItemRevisionShrPtr p_getItemRevShrPtr, vector<GET_FormShrPtr> p_vSecondaryFormObjs) {

	bool isMatch	= false;

	LOG_TRACE(logger, "Entering...checkParentOrgItem");
	try {
		vector<string> vOrgIDs = this->getOrgIDs(p_vSecondaryFormObjs);
        for(int inx = 0; inx < vOrgIDs.size(); inx++) {
			LOG_TRACE(logger, "vOrgIDs[inx]-->" + vOrgIDs[inx]);
			if(vOrgIDs[inx] == this->m_strSelectedOrg) {
				isMatch = true;
				break;
			}
		}

		if(!isMatch) {
			this->logErrorMessage(ERROR_MISSING_ORG_INDEX, (p_getItemRevShrPtr->getId() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getName() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) + this->m_strSelectedOrg + string(PIPE_DELIM_VALUE)));
		}

	} catch(...) {

        string sMessage = "checkParentOrgItem failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR(logger, sMessage);
        EMH_store_error_s1(EMH_severity_user_error, GET_general_exception, sMessage.c_str());
    }

	LOG_TRACE(logger, "Exiting...checkParentOrgItem");
	return this->m_istatus;
}

int GET_CheckMCN_AH_Impl::checkStockMaterial ( GET_ItemRevisionShrPtr p_getItemRevShrPtr, vector<GET_FormShrPtr> p_vSecondaryFormObjs )
{
    bool isValidCondition   = false;
    bool bStockMaterialReleasedFlag = false;
    GET_ItemRevisionUnqPtr stockMaterialItemRevUnqPtr;
    string strMakeBuy       = EMPTY_STRING_VALUE;
    GET_POM_objectUnqPtr    stockMaterialObjectUnqPtr;
    LOG_TRACE(logger, "Entering...checkStockMaterial");
	
	if ( ( p_getItemRevShrPtr->getType() == GET_ELECT_PART_REV_BO ) || ( p_getItemRevShrPtr->getType() == GET_MECH_PART_REV_BO ) || ( p_getItemRevShrPtr->getType() == GET_SOFT_PART_REV_BO ) )
	{
		for ( int inx = 0; inx < p_vSecondaryFormObjs.size(); inx++ )
        {
            string strOwningProject = p_vSecondaryFormObjs[inx]->getPropertyTag( OWNING_PROJECT_PROP )->getPropertyString( PROJECT_ID_PROP );
            LOG_TRACE ( logger, "strOwningProject-->" + strOwningProject );

            if ( this->m_strSelectedOrg == strOwningProject )
            {
                strMakeBuy = p_vSecondaryFormObjs[inx]->getPropString( MAKE_BUY_PROP );
                LOG_TRACE ( logger, "strMakeBuy-->" + strMakeBuy );
				
				if ( strMakeBuy != BUY_VALUE )
                {
                    LOG_TRACE ( logger, "Its not an assembly -->" + p_getItemRevShrPtr->getName() );
					
                    vector<GET_POM_objectUnqPtr> getMaterialObject = p_getItemRevShrPtr->getItem()->getPropTags( MADE_FROM_MATL_PROP );
                    LOG_TRACE ( logger, "getMaterialObject -->" + GET_intToString(getMaterialObject.size() ) );
					
					if ( getMaterialObject.size() )
                    {
                        //Code changes to check release status of Stock Material
                        stockMaterialObjectUnqPtr = p_vSecondaryFormObjs[inx]->getPropTag ( STOCK_MATERIAL_PROP );

                        if ( ( stockMaterialObjectUnqPtr != NULL ) || ( stockMaterialObjectUnqPtr.get() != NULL ) )
                        {
                            isValidCondition = true;
                            LOG_TRACE ( logger, "Stock Material is assigned for -->" + p_getItemRevShrPtr->getName() );
							
							GET_ItemUnqPtr stockMaterialItemUnqPtr = GET_Item::getInstance ( stockMaterialObjectUnqPtr->getTag() );
							stockMaterialItemRevUnqPtr = stockMaterialItemUnqPtr->getLatestReleasedRevision();

							if ( stockMaterialItemRevUnqPtr.get() != NULL && stockMaterialItemRevUnqPtr->getTag() != NULLTAG )
							{
								bStockMaterialReleasedFlag = true;
							}
							else
							{
								bStockMaterialReleasedFlag = false;

								// If the initital revision itself is working then error out
								stockMaterialItemRevUnqPtr = stockMaterialItemUnqPtr->getLatestRevision();
							}
                        }
                    }

					if ( !isValidCondition )
					{
						vector<GET_POM_objectUnqPtr> getMadeFromPart = p_getItemRevShrPtr->getItem()->getPropTags ( MADE_FROM_PART_PROP );
						LOG_TRACE(logger, "getMadeFromPart -->" + GET_intToString( getMadeFromPart.size() ) );
						
						if ( getMadeFromPart.size() == NUMBER_OF_MADE_FROM_PART )
						{
							isValidCondition = true;
							LOG_TRACE ( logger, "Made from Part is assigned for -->" + p_getItemRevShrPtr->getName() );

						}
						else
						{
							GET_BOMViewRevisionUnqPtr getBVR = p_getItemRevShrPtr->getBVR ( BOM_VIEW_REVISION_TYPE );
							if ( getBVR.get() )
							{
								vector<GET_POM_objectUnqPtr> getAssemblyChildren = getBVR->getPropTags ( BVR_OCCURRENCE_PROP );
								if ( getAssemblyChildren.size() )
								{
									isValidCondition = true;
									LOG_TRACE ( logger, "Its an assembly -->" + p_getItemRevShrPtr->getName() );
								}
							}
						}
					}

					if ( !isValidCondition )
					{
						LOG_TRACE(logger, "Make Item without any of the specified condition -->" + p_getItemRevShrPtr->getName());
						this->logErrorMessage(ERROR_NO_STOCK_MTRL_INDEX, (p_getItemRevShrPtr->getId() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getName() + string(PIPE_DELIM_VALUE) + p_getItemRevShrPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) + this->m_strSelectedOrg + string(PIPE_DELIM_VALUE)));
					}

					if( ( ( stockMaterialObjectUnqPtr != NULL ) || ( stockMaterialObjectUnqPtr.get() != NULL ) )  && ( bStockMaterialReleasedFlag == false ) )
					{
						LOG_TRACE( logger, "Unrelease StockMaterial  -->" + stockMaterialItemRevUnqPtr->getName() );
						this->logErrorMessage( ERROR_NO_STOCK_MTRL_REL_INDEX, (p_getItemRevShrPtr->getId() + string(PIPE_DELIM_VALUE) +
																	  p_getItemRevShrPtr->getName() + string(PIPE_DELIM_VALUE) +
																	  p_getItemRevShrPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) +
																	  stockMaterialItemRevUnqPtr->getId() + string(PIPE_DELIM_VALUE) +
																	  stockMaterialItemRevUnqPtr->getName() + string(PIPE_DELIM_VALUE) +
																	  stockMaterialItemRevUnqPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) ) );
					}

					//Check if Stock Material revision is checked out
					GET_ItemRevisionShrPtr stockMaterialItemRevShrPtr ( move ( stockMaterialItemRevUnqPtr ) );
					this->m_istatus = this->validateCheckOutStatus ( stockMaterialItemRevShrPtr );
                }

				// Mfg Attr form same as MCN org found, break the loop
				break;
            }
        }
	}

    LOG_TRACE(logger, "Exiting...checkStockMaterial");
	
	return this->m_istatus;
}

int GET_CheckMCN_AH_Impl::checkItemPublishDate ( GET_ItemRevisionShrPtr p_getItemRevShrPtr, vector<GET_FormShrPtr> p_vSecondaryFormObjs )
{
    int iItemRevCreDateFlag     = 0;
    int iFormLastModDateFlag    = 0;

    LOG_TRACE ( logger, "Entering...checkItemPublishDate" );
	

    GET_DateShrPtr getItemRevCreDateShrPtr ( move ( p_getItemRevShrPtr->getPropDate ( CREATION_DATE_PROP ) ) );
    LOG_TRACE ( logger, "getItemRevCreationDatePtr-->" + getItemRevCreDateShrPtr->toString() );
	

    for ( int inx = 0; inx  < p_vSecondaryFormObjs.size(); inx++ )
    {
        string strOwningProject = p_vSecondaryFormObjs[inx]->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
        LOG_TRACE ( logger, "strOwningProject-->" + strOwningProject );
		
		// Check if Owning project of Item Rev is same as MCN Org
        if ( strOwningProject != this->m_strSelectedOrg )
        {
            continue;
        }

        GET_DateShrPtr getItemPublishDateShrPtr ( move ( p_vSecondaryFormObjs[inx]->getPropDate ( ITEM_PUBLISH_DATE_PROP ) ) );

        if ( getItemPublishDateShrPtr->toString() != "" )
        {
            // Compare Item Revision Creation Date with Item Publish Date
            iItemRevCreDateFlag = getItemRevCreDateShrPtr->compare ( getItemPublishDateShrPtr );

            string isFormModify = p_vSecondaryFormObjs[inx]->getPropValueAsString ( MFG_ATTR_FORM_ORACLE_XFER_ATTR );
            LOG_TRACE ( logger, "isFormModify-->" + isFormModify );
			
			if ( iItemRevCreDateFlag > 0 || isFormModify.compare ( MFG_ATTR_FORM_ORACLE_XFER_VALUE ) == 0 )
            {
                this->m_istatus = 1;
            }
            else
            {
                this->m_istatus = 0;
            }
        }
        else
        {
            LOG_TRACE ( logger, "getItemPublishDateShrPtr is empty-->" + getItemPublishDateShrPtr->toString() );
			this->m_istatus = 1;
        }

        // Mfg Attr Form found same as MCN Org so break the loop
        break;
    }

    LOG_TRACE ( logger, "Exiting...checkItemPublishDate" );
	return this->m_istatus;
}

int GET_CheckMCN_AH_Impl::checkBOMPublishDate(GET_ItemRevisionShrPtr p_getItemRevShrPtr, vector<GET_FormShrPtr> p_vSecondaryFormObjs)
{
    bool bMfgMake	= false;

    int iStructLastModDateFlag  = 0;
    int iFormLastModDateFlag    = 0;

    map<string, GET_BOMViewRevisionShrPtr>::iterator mapBVRIterator;

    LOG_TRACE ( logger, "Entering...checkBOMPublishDate" );
	map<string, GET_BOMViewRevisionShrPtr> mapBOMViewRevisions = p_getItemRevShrPtr->getBVRs();

    // Process only if its an assembly, otherwise return 0
    if ( mapBOMViewRevisions.size() > 0 )
    {
        for ( mapBVRIterator = mapBOMViewRevisions.begin(); mapBVRIterator != mapBOMViewRevisions.end(); mapBVRIterator++ )
        {
            GET_DateUnqPtr getStructLastModDate = mapBVRIterator->second->getPropDate ( LAST_MOD_DATE_PROP );
            LOG_TRACE ( logger, "getStructLastModDate-->" + getStructLastModDate->toString() );
			
			for ( int inx = 0; inx < p_vSecondaryFormObjs.size(); inx++ )
            {
                string strOwningProject = p_vSecondaryFormObjs[inx]->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
                LOG_TRACE ( logger, "strOwningProject-->" + strOwningProject );
				
				// Check if Owning project of Item Rev is same as MCN Org
                if ( strOwningProject != this->m_strSelectedOrg )
                {
                    continue;
                }

                string strMakeBuy = p_vSecondaryFormObjs[inx]->getPropString ( MAKE_BUY_PROP );
                LOG_TRACE ( logger, "strMakeBuy-->" + strMakeBuy );
				
				if ( strMakeBuy.compare ( BUY_VALUE ) == 0 )
                {
                    break;
                }

                // Process only when Make value found for Mfg Org Form same as MCN Org
                GET_DateShrPtr getBOMPublishDateShrPtr ( move ( p_vSecondaryFormObjs[inx]->getPropDate ( BOM_PUBLISH_DATE_PROP ) ) );

                if ( getBOMPublishDateShrPtr->toString() != "" )
                {
                    // Compare Item Revision Creation Date with Item Publish Date
                    iStructLastModDateFlag = getStructLastModDate->compare ( getBOMPublishDateShrPtr );

                    // Set return value to 1 if Structure Last Modified Date is greater than BOM Publish Date
                    if ( iStructLastModDateFlag > 0 )
                    {
                        this->m_istatus = 1;
                    }
                    else
                    {
                        this->m_istatus = 0;
                    }
                }
                else
                {
                    LOG_TRACE(logger, "getBOMPublishDateShrPtr is empty-->"+ getBOMPublishDateShrPtr->toString());
					this->m_istatus = 1;
                }

                // Mfg Attr Form found same as MCN Org so break the loop
                break;
            }
        }
    }

    LOG_TRACE(logger, "Exiting...checkBOMPublishDate");
	return this->m_istatus;
}

bool GET_CheckMCN_AH_Impl::GET_ExistsInVector( vector<GET_ItemRevisionShrPtr> TargetItemRevVector, GET_ItemRevisionShrPtr ItemRevVector )
{
    bool isTrue = false;
    string Itemid = ItemRevVector->getId();

    for( size_t inx=0; inx<TargetItemRevVector.size(); inx++ )
    {
        string targetID =  TargetItemRevVector[inx]->getId();
        if( strcmp( targetID.c_str(), Itemid.c_str() ) == 0 )
        {
            isTrue = true;
            break;
        }
    }
    return isTrue;
}

bool GET_CheckMCN_AH_Impl::hasRFUOM(GET_ItemRevisionShrPtr getItemRevShrPtr)
{
    bool isTrue = false;
    string strUOMObjSymbol = "";

    LOG_TRACE ( logger, "START : hasRFUOM method" );
	
	GET_ItemUnqPtr getItemUnqPtr = getItemRevShrPtr->getItem();

    GET_POM_objectUnqPtr getPOMObjUnqPtr = getItemUnqPtr->getPropTag( UOM_ATTR );

    if( getPOMObjUnqPtr.get() != NULL )
    {
         strUOMObjSymbol = getPOMObjUnqPtr->getPropertyString ( SYMBOL_ATTR );
    }

    if( strUOMObjSymbol.compare ( RFUOM ) == 0 )
    {
        isTrue=true;
    }

    LOG_TRACE ( logger, "END : hasRFUOM method" );
	return isTrue;
}

int GET_CheckMCN_AH_Impl::validatePreliminaryMCN()
{
	LOG_TRACE(logger, "Entering....validatePreliminaryMCN");
	vector <tag_t> vTargetAttachments = m_vAttachments[EPM_target_attachment];

	for(int iPrelim=0; iPrelim < vTargetAttachments.size(); iPrelim++)
	{
		//Check if given part is Item revision or not
		if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iPrelim], ITEMREVISION_CLASS ) )
		 {
			continue;
		 }

		GET_ItemRevisionUnqPtr itemRevisionUnqPtr = GET_ItemRevision::getInstance (vTargetAttachments[iPrelim] );
		GET_ItemRevisionShrPtr itemRevShrPtr ( move ( itemRevisionUnqPtr ) );

		LOG_TRACE(logger, "itemRevShrPtr->getType()-->" + itemRevShrPtr->getType());
		
		if ( itemRevShrPtr->getType() == GET_MCN_REV_BO )
		{
			//Get the Owning Project of MCN
			this->m_strSelectedOrg = itemRevShrPtr->getPropertyTag(OWNING_PROJECT_PROP)->getPropertyString(PROJECT_ID_PROP);
			LOG_TRACE(logger, "this->m_strSelectedOrg-->" + this->m_strSelectedOrg);
			this->m_strMCNID = itemRevShrPtr->getItem()->getId();
			LOG_TRACE(logger, "this->m_strMCNID-->" + this->m_strMCNID);
		}
		if ( itemRevShrPtr->getType() == GET_MFG_REV_BO )
		{
            // Storing Mfg Part revision share pointer
            vMfgPartVector.push_back(itemRevShrPtr);
		}
	}

	for(int jnx = 0; jnx < this->vMfgPartVector.size(); jnx++)
	{
		this->m_istatus = this->validatePreliminaryStructure(this->vMfgPartVector[jnx]);
	}

	LOG_TRACE(logger, "Exiting....validatePreliminaryMCN");
	return m_istatus;
}

int GET_CheckMCN_AH_Impl::validatePreliminaryStructure(GET_ItemRevisionShrPtr parentMfgPartRevShrPtr)
{
	LOG_TRACE(logger, "Entering....validatePreliminaryStructure");
	
	// Boolean to indicate whether the current target is an assembly or not
	bool bIsAssembly = false;
	try
	{
	    // Validate checkout status of object
	    this->m_istatus = this->validateCheckOutStatus ( parentMfgPartRevShrPtr );

        // Validate Parent for Make/Buy condition
        vector<GET_FormShrPtr> vParentFormObjs = this->getOrgItems(parentMfgPartRevShrPtr);
        this->m_istatus = this->checkParentOrgItem(parentMfgPartRevShrPtr, vParentFormObjs);
        if (this->hasMakeOrgItem(parentMfgPartRevShrPtr) )
        {
            // Check if the MfgPartRevision is an assembly or not
            vector<GET_POM_objectUnqPtr> childObjectsVector = parentMfgPartRevShrPtr->getPropTags ( PSCHILDREN_ATTR );

             if ( childObjectsVector.size() > 0 )
             {
                 bIsAssembly = true;

                //Create a BOM Window for traversing the structure
                GET_BOMWindowUnqPtr bomWindowUnqPtr = GET_BOMWindow::create();
                bomWindowUnqPtr->setRevisionRule (this->m_strRevisionRule);
                GET_BOMViewRevisionShrPtr bomViewShrPtr;
                GET_BOMLineUnqPtr topBOMLineUnqPtr = bomWindowUnqPtr->setTopLine ( parentMfgPartRevShrPtr, bomViewShrPtr );
                GET_BOMLineShrPtr topBOMLineShrPtr(move(topBOMLineUnqPtr));

                //Calling recurse function
                this->m_istatus = this->recursePrelimMFG(topBOMLineShrPtr);
             }

             if(bIsAssembly==false)
             {
                this->logErrorMessage(ERROR_NO_PRELIM_ASMBLY_INDEX, (parentMfgPartRevShrPtr->getId() + string(PIPE_DELIM_VALUE) + parentMfgPartRevShrPtr->getName() + string(PIPE_DELIM_VALUE) + parentMfgPartRevShrPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE) + this->m_strSelectedOrg + string(PIPE_DELIM_VALUE)));
             }
        }
	}
	 catch(...)
	 {
		string sMessage = "validatePreliminaryStructure failed due to an unexpected error. Please Contact your system administrator";
		LOG_ERROR(logger, sMessage);
		EMH_store_error_s1(EMH_severity_user_error, GET_general_exception, sMessage.c_str());
	 }

	LOG_TRACE(logger, "Exiting....validatePreliminaryStructure");
	return m_istatus;
}

int GET_CheckMCN_AH_Impl::validatePrelimStatus(GET_ItemRevisionShrPtr childItemRevShPtr)
{
	LOG_TRACE(logger, "Entering...validatePrelimStatus");
	
	bool bOnlyReleasedStatus = true;
	int istatus = ITK_ok;
	try
	{
		//Checking if the item revision is released.
		//Released status should be GET6Released.
		//comment below if loop.
		if(childItemRevShPtr->isReleased())
		{
			if ( childItemRevShPtr->hasReleaseStatus ( GET6PRELIMINARY ) || childItemRevShPtr->hasReleaseStatus ( OBSOLETE_VALUE ) )
			{
				bOnlyReleasedStatus = false;
			}
		}
		else
		{
			bOnlyReleasedStatus = false;
		}

		if(bOnlyReleasedStatus==false)
		{
			this->logErrorMessage(ERROR_NO_PRELIM_STATUS_INDEX, childItemRevShPtr->getId() +
					string(PIPE_DELIM_VALUE) + childItemRevShPtr->getName() +
					string(PIPE_DELIM_VALUE) + childItemRevShPtr->getPropValueAsString(OBJECT_TYPE_ATTR) + string(PIPE_DELIM_VALUE));
		}

	}

	catch(...)
	{
		string sMessage = "validatePrelimStatus failed due to an unexpected error. Please Contact your system administrator";
		LOG_ERROR(logger, sMessage);
		EMH_store_error_s1(EMH_severity_user_error, GET_general_exception, sMessage.c_str());
	}

	LOG_TRACE(logger, "Exiting...validatePrelimStatus");
	return istatus;
}

int GET_CheckMCN_AH_Impl::recursePrelimMFG(GET_BOMLineShrPtr p_getBOMLineShrPtr)
{
	LOG_TRACE(logger, "Entering...recursePrelimMFG");
	try
	{
		GET_ItemRevisionShrPtr getParentItemRevShrPtr(move(p_getBOMLineShrPtr->getItemRevision()));
		vector<GET_BOMLineUnqPtr> vBOMLineChildren = p_getBOMLineShrPtr->getChildren();

        for(int inx = 0; inx < vBOMLineChildren.size(); inx++)
        {
            GET_BOMLineShrPtr getBOMLineShrPtr(move(vBOMLineChildren[inx]));
            GET_ItemRevisionShrPtr getChildItemRevShrPtr(move(getBOMLineShrPtr->getItemRevision()));
            //GET the Form assoicated to Item.
            vector<GET_FormShrPtr> vChildSecondaryFormObjs = this->getOrgItems(getChildItemRevShrPtr);

            // Validate checkout status of object
            this->m_istatus = this->validateCheckOutStatus ( getChildItemRevShrPtr );
            //Validate the Released status
            this->m_istatus = this->validatePrelimStatus(getChildItemRevShrPtr);
            // Check Owning Project of Item Revision
            this->m_istatus = this->checkParentOrgItem(getChildItemRevShrPtr, vChildSecondaryFormObjs);
            //Validate Stock Material conditions
            this->m_istatus = this->checkStockMaterial(getChildItemRevShrPtr, vChildSecondaryFormObjs);

            //Check if Make/Buy is set, traverse further only when Make if found
            if ( this->hasMakeOrgItem(getChildItemRevShrPtr) )
            {
                this->m_istatus = this->recursePrelimMFG( getBOMLineShrPtr );
            }
        }
	}

	catch(...)
	{

        string sMessage = "recursePrelimMFG failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR(logger, sMessage);
        EMH_store_error_s1(EMH_severity_user_error, GET_general_exception, sMessage.c_str());
    }

	LOG_TRACE(logger, "Exiting...recursePrelimMFG");
	return this->m_istatus;
}

int GET_CheckMCN_AH_Impl::validateFlipToMakeBuy()
{
    int istatus = ITK_ok;

    bool isMCNOrgFormFound  = false;
    bool isErrorFound       = false;

    string strOwningProjectID = EMPTY_STRING_VALUE;
    string sConsolidatedErrorMessage = EMPTY_STRING_VALUE;

    LOG_TRACE ( logger, "START: validateFlipToMakeBuy method" );
	
	if ( ( this->m_vArguments.find ( FLIP_TO_MAKE_BUY_ARG ) == this->m_vArguments.end() ) || ( this->m_vArguments[FLIP_TO_MAKE_BUY_ARG].empty() ) )
	{
		THROW ( string ( "The argument \"" ) + FLIP_TO_MAKE_BUY_ARG + string ( "\" is not provided or has empty value" ) );
	}
	
	//get the handler arguments from map into string
    string sFlipMakeBuyArgValue = this->m_vArguments[FLIP_TO_MAKE_BUY_ARG];

    // Clear the existing error stack
    istatus = EMH_clear_errors();

    // Loop through each target objects
    for ( int iTargetIndex = 0; iTargetIndex < this->m_vAttachments[EPM_target_attachment].size(); iTargetIndex++ )
    {
        // Validate if MCN Revision is found in target object
        if (! GET_POM_object::isDescendant ( this->m_vAttachments[EPM_target_attachment][iTargetIndex], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getTargetShrPtr( move ( GET_ItemRevision::getInstance ( this->m_vAttachments[EPM_target_attachment][iTargetIndex] )));
        LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getTargetShrPtr->getType() );
		
		// Get the Owning Project of MCN
        this->m_strSelectedOrg = getTargetShrPtr->getPropertyTag(OWNING_PROJECT_PROP)->getPropertyString(PROJECT_ID_PROP);
        LOG_TRACE ( logger, "Owning Project of MCN is ..." + this->m_strSelectedOrg );
		
		// Get all objects from Solution folder
        vector <GET_POM_objectUnqPtr> vSolutionItemsUnqPtr = getTargetShrPtr->getPropTags( CM_HAS_SLITEMS_PROP );
        LOG_TRACE ( logger, "Size of vSolutionItemsUnqPtr vector is ..." + vSolutionItemsUnqPtr.size() );
		
		// Loop through each objects in Solution Item folder
        for ( size_t iSolIndex=0; iSolIndex < vSolutionItemsUnqPtr.size(); iSolIndex++ )
        {
            GET_ItemRevisionShrPtr p_getItemRevShrPtr ( move ( GET_ItemRevision::getInstance( vSolutionItemsUnqPtr[iSolIndex]->getTag() )));

            // Get the associated Org form
            vector<GET_FormShrPtr> vPartToOrgAttributesForm = this->getOrgItems ( p_getItemRevShrPtr );
            LOG_TRACE ( logger, "Number of Org Forms found is ..." + vPartToOrgAttributesForm.size() );
			
			if ( vPartToOrgAttributesForm.size() == 0 )
            {
                sConsolidatedErrorMessage.append ("\n");
                sConsolidatedErrorMessage.append ( "No Org form found for Object [" + p_getItemRevShrPtr->getId() + "]" );
                isErrorFound = true;

                continue;
            }

            for (int iFormCount = 0; iFormCount < vPartToOrgAttributesForm.size(); iFormCount++)
            {
                strOwningProjectID = vPartToOrgAttributesForm[iFormCount]->getPropertyTag(OWNING_PROJECT_PROP)->getPropertyString(PROJECT_ID_PROP);
                LOG_TRACE(logger, "strOwningProjectID-->" + strOwningProjectID);
				
				// Process only when Mfg form is found for Org same as the Owning Project of MCN
                if ( this->m_strSelectedOrg != strOwningProjectID )
                {
                    LOG_TRACE ( logger, "Org Mismatch found for object ..." + p_getItemRevShrPtr->getId() );
					continue;
                }

                isMCNOrgFormFound = true;

                // Check the Item Publish Date, Perform FlipToMakeBuy only if particular Part has been already transferred to Oracle
                GET_DateShrPtr getItemPublishDateShrPtr ( move ( vPartToOrgAttributesForm[iFormCount]->getPropDate ( ITEM_PUBLISH_DATE_PROP ) ) );
                LOG_TRACE ( logger, "getItemPublishDateShrPtr-->" + getItemPublishDateShrPtr->toString() );
				
				if ( getItemPublishDateShrPtr->toString() == "" )
                {
                    sConsolidatedErrorMessage.append ("\n");
                    sConsolidatedErrorMessage.append ( "Object [" + p_getItemRevShrPtr->getId() + "] is not available in Oracle EBS, MakeBuy can be changed only for already transferred Parts" );
                    isErrorFound = true;

                    continue;
                }

                string strMakeBuy = vPartToOrgAttributesForm[iFormCount]->getPropString ( MAKE_BUY_PROP );
                LOG_TRACE(logger, "strMakeBuy-->" + strMakeBuy);
				
				// If workflow process is for Flip to Buy
                if ( sFlipMakeBuyArgValue.compare ( BUY_VALUE ) == 0 )
                {
                    // Only Make value can be flip to Buy, if its Buy then error out
                    if ( strMakeBuy.compare ( BUY_VALUE ) == 0 )
                    {
                        sConsolidatedErrorMessage.append ("\n");
                        sConsolidatedErrorMessage.append ( "Mfg Make/Buy value for Object [" + p_getItemRevShrPtr->getId() + "] is Buy, it can be initiated only on Make value" );
                        isErrorFound = true;

                        continue;
                    }
                }
                else if ( sFlipMakeBuyArgValue.compare ( MAKE_VALUE ) == 0 ) // If workflow process is for Flip to Make
                {
                    // Only Buy value can be flip to Make, if its Make then error out
                    if ( strMakeBuy.compare ( MAKE_VALUE ) == 0 )
                    {
                        sConsolidatedErrorMessage.append ("\n");
                        sConsolidatedErrorMessage.append ( "Mfg Make/Buy value for Object [" + p_getItemRevShrPtr->getId() + "] is Make, it can be initiated only on Buy value" );
                        isErrorFound = true;

                        continue;
                    }

                    // Check for Eng MakeBuy
                    if ( ( p_getItemRevShrPtr->getType() == GET_ELECT_PART_REV_BO ) || ( p_getItemRevShrPtr->getType() == GET_MECH_PART_REV_BO ) || ( p_getItemRevShrPtr->getType() == GET_SOFT_PART_REV_BO ) )
                    {
                        string strEngMakeBuy = p_getItemRevShrPtr->getPropString ( ENG_MAKE_BUY_PROP );

                        // If Eng MakeBuy is "Buy" then Mfg MakeBuy cannot be flip to "Make"
                        if ( strEngMakeBuy == BUY_VALUE )
                        {
                            sConsolidatedErrorMessage.append ("\n");
                            sConsolidatedErrorMessage.append ( "Eng MakeBuy value for Object [" + p_getItemRevShrPtr->getId() + "] is Buy, Mfg MakeBuy cannot be flip to Make" );
                            isErrorFound = true;

                            continue;
                        }
                    }
                }
            }

            // Throw error if no Mfg Form found for Org same as the Owning Project of MCN
            if ( ! isMCNOrgFormFound )
            {
                sConsolidatedErrorMessage.append ("\n");
                sConsolidatedErrorMessage.append ( "Org mismatch found, MCN Org and Mfg form Org are not same for Object [" + p_getItemRevShrPtr->getId() + "]" );
                isErrorFound = true;

                continue;
            }
        }

        // Throw error to User if "No Org form found" or "If Buy value found" or "Org mismatch found"
        if ( isErrorFound )
        {
            THROW ( sConsolidatedErrorMessage );
        }
    }

    LOG_TRACE(logger, "Exiting....validateFlipToMakeBuy");
	return m_istatus;
}

// Method to get the Site ID.
string GET_CheckMCN_AH_Impl::getSiteID ()
{
	int iSiteId = 0;
	string sSiteName = "";
	iSiteId	= GET_Site::getLocalID();

	if( iSiteId )
	{
		GET_SiteUnqPtr siteUnqPtr = GET_Site::find ( iSiteId );
		if( siteUnqPtr != NULL)
		{
			sSiteName = siteUnqPtr->getName();
		}
	}

	sSiteName = string ( OPEN_SQUARE_CHAR_VALUE ) + sSiteName + string ( CLOSE_SQUARE_CHAR_VALUE ) ;

	return sSiteName;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   attachMfgAttrFormsToTarget()
//
//    Purpose:   Implementation to attaching Mfg Attribute Forms to target
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
int GET_CheckMCN_AH_Impl::attachMfgAttrFormsToTarget()
{
    string skip_mfg_attr_form = "none";

    vector<GET_FormShrPtr>              vFormsShrPtr;
    vector<GET_POM_objectShrPtr>        vFormsToBeAttachedPOMShrPtr;

    LOG_TRACE(logger, "Entering...attachMfgAttrFormsToTarget");
	
	getStringPrefValues ( CM_VALID_MCN_OBJECTS, this->m_vValidMCNObjects );

    if ( ( this->m_vArguments.find ( RELATION_TYPE ) == this->m_vArguments.end() ) || ( this->m_vArguments[RELATION_TYPE].empty() ) )
	{
		THROW ( string ( "The argument \"" ) + RELATION_TYPE + string ( "\" is not provided or has empty value" ) );
	}

    if ( this->m_vValidMCNObjects.size() == 0 )
    {
        string sMessage = "The Preference " + string( CM_VALID_MCN_OBJECTS ) + " is not defined or does not have a value";
        THROW ( sMessage );
    }

    if ( this->m_vArguments.find ( SKIP_MFG_ATTR_FORM_ARG ) != this->m_vArguments.end() )
    {
        skip_mfg_attr_form = this->m_vArguments[SKIP_MFG_ATTR_FORM_ARG];
    }

    // Loop through each target objects
    for ( size_t iTargetObj=0; iTargetObj < this->m_vAttachments[EPM_target_attachment].size(); iTargetObj++ )
    {
        // Validate if MCN Revision is found in target object
        if (! GET_POM_object::isDescendant ( this->m_vAttachments[EPM_target_attachment][iTargetObj], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getMCNRevShrPtr ( move ( GET_ItemRevision::getInstance ( this->m_vAttachments[EPM_target_attachment][iTargetObj] )));
        LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getMCNRevShrPtr->getType() );
		

        // Get the Owning project of MCN
        this->m_strSelectedOrg = getMCNRevShrPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );
        LOG_TRACE ( logger, "Owning project of MCN is ..." + this->m_strSelectedOrg );
		

        vector<GET_POM_objectUnqPtr> vSolutionItems = getMCNRevShrPtr->getPropTags ( this->m_vArguments[RELATION_TYPE] );

        // Loop through each objects in Solution Item folder
        for( size_t iSolIndex=0; iSolIndex < vSolutionItems.size(); iSolIndex++ )
        {
            GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( GET_ItemRevision::getInstance ( vSolutionItems[iSolIndex]->getTag() )));
            LOG_TRACE(logger, "getItemRevShrPtr->getType()-->" + getItemRevShrPtr->getType());
			
			if ( GET_isInVector ( this->m_vValidMCNObjects, getItemRevShrPtr->getType() ))
            {
                this->m_vSolutionItems.push_back( getItemRevShrPtr );
            }
        }

        // Loop through each valid target items
        for ( size_t iSolItemIndex = 0; iSolItemIndex < this->m_vSolutionItems.size(); iSolItemIndex++ )
        {
            GET_BOMViewRevisionShrPtr getBOMViewRevisionShrPtr;
            GET_BOMWindowUnqPtr getBOMWindowUnqPtr = GET_BOMWindow::create();

            getBOMWindowUnqPtr->setRevisionRule ( this->getManufacturingRevisionRule ( false ) );
            GET_BOMWindowShrPtr getBOMWindowShrPtr( move ( getBOMWindowUnqPtr ) );

            GET_BOMLineUnqPtr getBOMLineUnqPtr = getBOMWindowShrPtr->setTopLine( this->m_vSolutionItems[iSolItemIndex], getBOMViewRevisionShrPtr );
            GET_BOMLineShrPtr getBOMLineShrPtr ( move ( getBOMLineUnqPtr ) );

            this->m_istatus = this->recurseMfgAttrForms ( getBOMLineShrPtr, vFormsShrPtr );
        }

        // Convert to Form Object to Workspace Object for passing it to addStatus() method
        for ( size_t iFormIndex = 0; iFormIndex < vFormsShrPtr.size(); iFormIndex++ )
        {
			GET_POM_objectShrPtr getPOMShrPtr ( move ( GET_POM_object::getInstance ( vFormsShrPtr[iFormIndex]->getTag() )));
			
			// Skip of Mfg Attr Form if its UnReleased
            if ( skip_mfg_attr_form.compare ( UNRELEASE_MFG_FORM_ARG ) == 0 )
            {
                if ( ! vFormsShrPtr[iFormIndex]->isReleased() )
                {
                    continue;
                }
            }

            // Skip of Mfg Attr Form if its Released
            if ( skip_mfg_attr_form.compare ( RELEASE_MFG_FORM_ARG ) == 0 )
			{
				if ( vFormsShrPtr[iFormIndex]->isReleased() )
				{
					continue;
				}
			}

			// Check if the Mfg Attr Form is already in workflow target,
			// Add to the vector of Forms ToBe added to target only if its not in target already
			vector<GET_POM_objectUnqPtr> vFormProcessStageListUnqPtr = vFormsShrPtr[iFormIndex]->getPropTags ( PROCESS_STAGE_LIST_ATTR );
			if ( vFormProcessStageListUnqPtr.size() == 0 )
			{
			    vFormsToBeAttachedPOMShrPtr.push_back ( getPOMShrPtr );
			}
        }

        if ( vFormsToBeAttachedPOMShrPtr.size() > 0 )
        {
			// Forms to be added to Workflow target as attachment for further updating via Workflow ACL
			GET_EPMTaskUnqPtr getEPMTaskUnqPtr = GET_EPMTask::getInstance( this->m_tTaskTag );
			getEPMTaskUnqPtr->addAttachments ( EPM_target_attachment, vFormsToBeAttachedPOMShrPtr );
        }
    }

    LOG_TRACE (logger, "Exiting...attachMfgAttrFormsToTarget");
	return this->m_istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   recurseMfgAttrForms()
//
//    Purpose:   Implementation to recurse the Mfg Attribute Forms
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    ITK Status
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
int GET_CheckMCN_AH_Impl::recurseMfgAttrForms (GET_BOMLineShrPtr p_getBOMLineShrPtr, vector<GET_FormShrPtr>& vFormsShrPtr )
{
    LOG_TRACE ( logger, "START : recurseMfgAttrForms method" );
	
	GET_ItemRevisionShrPtr getItemRevShrPtr( move ( p_getBOMLineShrPtr->getItemRevision() ) );

    string sUOMValue = getItemRevShrPtr->getItem()->getPropValueAsString ( UOM_TAG_PROP );

    // Check UOM value, process only if RF UOM not found
    if ( sUOMValue.compare ( UOM_RF_VALUE ) != 0 )
    {
        // Check if BOMline object is allowed object type
        if ( GET_isInVector ( this->m_vValidMCNObjects, getItemRevShrPtr->getType() ) )
        {
            // Check if Item is already processed, if not then only process
            if ( ! (std::find(this->m_vProcessedItems.begin(), this->m_vProcessedItems.end(), getItemRevShrPtr->getTag()) != this->m_vProcessedItems.end() ) )
            {
                this->m_vProcessedItems.push_back ( getItemRevShrPtr->getTag() );

                // Get the Form which is associated to the Object for corresponding MCN Org
                //GET_FormShrPtr makeOrgFormShrPtr = this->getOrgForm ( getItemRevShrPtr );
                GET_FormShrPtr makeOrgFormShrPtr = getSameOrgForm ( getItemRevShrPtr, this->m_strSelectedOrg );

                // Process further only when Mfg Attr Form is not NULL
                if ( ( makeOrgFormShrPtr != NULL )  &&  ( makeOrgFormShrPtr.get() != NULL ) )
                {
                    vFormsShrPtr.push_back ( makeOrgFormShrPtr );

                    // Traverse to children if (-traverse) argument is found in workflow handler
                    // For example in "GET MCN Process" workflow, we need -traverse argument for traversing to its Children
                    if ( this->m_vArguments.find ( TRAVERSE_ARG ) != this->m_vArguments.end() )
                    {
                        // Process its children only if its a Make Part
                        if ( this->hasMakeOrgItem ( getItemRevShrPtr ) )
                        {
                            // Get the Children of Make Part
                            vector<GET_BOMLineUnqPtr> vBOMLineChildren = p_getBOMLineShrPtr->getChildren();

                            // Loop through each children
                            for (size_t iChildIndex = 0; iChildIndex < vBOMLineChildren.size(); iChildIndex++ )
                            {
                                GET_BOMLineShrPtr getBOMLineShrPtr ( move ( vBOMLineChildren[iChildIndex] ));
                                GET_ItemRevisionShrPtr getChildItemRevShrPtr ( move ( getBOMLineShrPtr->getItemRevision() ));

                                this->m_istatus = this->recurseMfgAttrForms ( getBOMLineShrPtr, vFormsShrPtr );
                            }
                        }
                    }
                }
            }
        }
    }

    LOG_TRACE ( logger, "END : recurseMfgAttrForms method" );
	
	return this->m_istatus;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   resetMfgAttrOracleXferPropValue()
//
//    Purpose:   Implementation to reset the Oracle transfer flag of Mfg Attribute Forms
//
//    Inputs:    from Implementation functions
//
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team      29 Aug, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET_CheckMCN_AH_Impl::resetMfgAttrOracleXferPropValue()
{
    vector<GET_ItemRevisionShrPtr>  processedItemRevList;
    vector<GET_POM_objectShrPtr>    vFormsToBeAttachedPOMShrPtr;
    vector<GET_FormShrPtr>          vSameOrgFormShrPtr;

    LOG_TRACE ( logger, "Entering...resetMfgAttrOracleXferPropValue" );
	
	// Loop through each target objects
    for ( size_t iTargetObj=0; iTargetObj < this->m_vAttachments[EPM_target_attachment].size(); iTargetObj++ )
    {
        // Validate if MCN Revision is found in target object
        if (! GET_POM_object::isDescendant ( this->m_vAttachments[EPM_target_attachment][iTargetObj], GET_MCN_REVISION_CLASS ) )
        {
            continue;
        }

        GET_ItemRevisionShrPtr getItemRevUnqPtr ( move ( GET_ItemRevision::getInstance ( this->m_vAttachments[EPM_target_attachment][iTargetObj] ) ) );
        LOG_TRACE ( logger, "getTargetShrPtr->getType()-->" + getItemRevUnqPtr->getType() );
		
		// Get Owning project of MCN
        this->m_strSelectedOrg = getItemRevUnqPtr->getPropertyTag ( OWNING_PROJECT_PROP )->getPropertyString ( PROJECT_ID_PROP );

        GET_EPMTaskUnqPtr getEPMTaskUnqPtr = GET_EPMTask::getInstance ( this->m_tTaskTag );
        vector<GET_POM_objectUnqPtr> vReferenceObjUnqPtr = getEPMTaskUnqPtr->askAttachments ( EPM_reference_attachment );
        LOG_TRACE ( logger, "List of objects attached under References =>" + vReferenceObjUnqPtr.size() );
		
		for ( size_t iRefObjs=0; iRefObjs < vReferenceObjUnqPtr.size(); iRefObjs++ )
        {
            // Process only if Reference object type is a Folder
            if ( vReferenceObjUnqPtr [ iRefObjs ]->getPropertyString ( OBJECT_TYPE_ATTR ).compare ( FOLDERTYPE ) != 0 )
            {
                continue;
            }

            string foldername = vReferenceObjUnqPtr[ iRefObjs ]->getPropertyString ( OBJECT_NAME_ATTR );
            LOG_TRACE ( logger, "Name of the folder => " + foldername );
			
			// Process only for ITEM Ref folder
            if ( foldername.compare ( OBJECT_ITEM ) != 0 )
            {
                continue;
            }

            vector<GET_POM_objectUnqPtr> vFolderContents = vReferenceObjUnqPtr[ iRefObjs ]->getPropertyTags ( CONTENTS );

            // Loop through each contents of ITEM folder
            for ( size_t iContentIndex=0; iContentIndex < vFolderContents.size(); iContentIndex++ )
            {
                GET_ItemRevisionShrPtr getItemRevShrPtr ( move ( GET_ItemRevision::getInstance ( vFolderContents [iContentIndex]->getTag() ) ) );

                // Process only if Item is Released
                if ( ! getItemRevShrPtr->isReleased() )
                {
                    continue;
                }

                // Check object types
                if ( ( GET_ExistsInVector ( processedItemRevList, getItemRevShrPtr ) == false )
                        && ( getItemRevShrPtr->getType().compare ( MFGREV_TYPE ) == 0 || getItemRevShrPtr->getType().compare ( MECHREV_TYPE ) == 0
                        || getItemRevShrPtr->getType().compare ( ELECREV_TYPE ) == 0 || getItemRevShrPtr->getType().compare ( SOFTREV_TYPE ) == 0 ) )
                {
                    processedItemRevList.push_back ( getItemRevShrPtr );

                    // Get the Form which is associated to the Object for corresponding MCN Org
                    GET_FormShrPtr sameOrgFormShrPtr = getSameOrgForm ( getItemRevShrPtr, this->m_strSelectedOrg );

                    // Process further only when Mfg Attr Form is not NULL
                    if ( ( sameOrgFormShrPtr != NULL )  &&  ( sameOrgFormShrPtr.get() != NULL ) )
                    {
                        // Get the get6isMfgAttrModT4OXfer prop value of Mfg Attr Form
                        string isFormModify = sameOrgFormShrPtr->getPropValueAsString ( MFG_ATTR_FORM_ORACLE_XFER_ATTR );

                        if ( isFormModify.compare ( MFG_ATTR_FORM_ORACLE_XFER_VALUE ) == 0 )
                        {
                            GET_POM_objectShrPtr getPOMShrPtr ( move ( GET_POM_object::getInstance ( sameOrgFormShrPtr->getTag() ) ) );
                            vFormsToBeAttachedPOMShrPtr.push_back ( getPOMShrPtr );
                            vSameOrgFormShrPtr.push_back ( sameOrgFormShrPtr );
                        }
                    }
                }
            }

            // Since ITEM folder found, break the loop
            break;
        }

        // Attach the Forms to Target to give write access for resetting the value
        getEPMTaskUnqPtr->addAttachments ( EPM_target_attachment, vFormsToBeAttachedPOMShrPtr );

        for ( size_t iFormIndex=0; iFormIndex < vSameOrgFormShrPtr.size(); iFormIndex++ )
        {
            bool isFormModifyReset = false;
            vSameOrgFormShrPtr[iFormIndex]->setProp ( MFG_ATTR_FORM_ORACLE_XFER_ATTR, isFormModifyReset );
        }

        vReferenceObjUnqPtr.clear();

        // Since MCN Revision found, break the loop
        break;
    }

    LOG_TRACE ( logger, "Exiting...resetMfgAttrOracleXferPropValue" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   checkVerifiedAssembly()
//
//    Purpose:   Checks whether the Engineering part is verified by Engineer
//
//    Inputs:    part revision
//
//    Outputs:   none
//
//    Return:    none
//
===========================================================================
//ENDFUNCDOC   ***/
int GET_CheckMCN_AH_Impl::checkVerifiedAssembly ( GET_BOMLineShrPtr p_getBOMLineShrPtr )
{
	LOG_TRACE(logger, "Entering...checkVerifiedAssembly");
	bool isVerified = true;
	vector<string> vReleaseStatusList;
	GET_ItemUnqPtr getItemUnqPtr;
	
	try
    {
		//get item revision pointer
		GET_ItemRevisionUnqPtr getItemRevUnqPtr = p_getBOMLineShrPtr->getItemRevision();
		if ( getItemRevUnqPtr->getType() == GET_MECH_PART_REV_BO )
		{
			vector<GET_BOMLineUnqPtr> vBOMLineChildren = p_getBOMLineShrPtr->getChildren();
			
			//Verify only if revision is assembly
			if ( vBOMLineChildren.size() > 0 )
			{
				isVerified = false;
				
				//get the Item
				getItemUnqPtr = p_getBOMLineShrPtr->getItem();
				
				//check whether the verified attribute is set to true
				isVerified = getItemUnqPtr->getPropertyLogical ( VERIFIED_ASSEMBLY_PROP );
			}
		}
		if ( !isVerified )
		{
			LOG_TRACE(logger, "Engineering part assembly is not verified -->" + getItemRevUnqPtr->getName());
				
			this->logErrorMessage ( ERROR_ENG_PART_NOT_VERIFIED, ( getItemRevUnqPtr->getId() +
			string ( PIPE_DELIM_VALUE ) + getItemRevUnqPtr->getName() +
			string ( PIPE_DELIM_VALUE ) + getItemRevUnqPtr->getPropValueAsString ( OBJECT_TYPE_ATTR ) 
			+ string ( PIPE_DELIM_VALUE ) + FALSE_VALUE + string ( PIPE_DELIM_VALUE ) + PART_NOT_VERIFIED + string ( PIPE_DELIM_VALUE )));
					
		}
	}
	catch(...)
    {
		string sMessage = "checkVerifiedAssembly failed due to an unexpected error. Please Contact your system administrator";
		LOG_ERROR(logger, sMessage);
		EMH_store_error_s1 ( EMH_severity_user_error, GET_general_exception, sMessage.c_str() );
    }
	
	LOG_TRACE ( logger, "Exit...checkVerifiedAssembly" );
	
	return this->m_istatus;
}
