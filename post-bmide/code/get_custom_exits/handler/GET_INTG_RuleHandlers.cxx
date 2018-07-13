
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_INT_RuleHandlers.cxx
//
//    Purpose:   Source File defining the Integration Rule Handler Implementations
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     10 July, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_INTG_RuleHandlers.hxx>
#include <GET_Constants.hxx>
#include <GET_HandlerImpl.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Item.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_Exception.hxx>
#include <GET_Errors.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_Preferences.hxx>
#include <GET_sysapi.h>
#include <GET_Utils.hxx>
#include <GET_POM_user.hxx>
#include <GET_OCCI_Includes.h>

// Teamcenter Includes
#include <tc/emh.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// CPP Includes
#include <map>

using namespace get;
using namespace oracle::occi;

// Private Function Prototypes
void GET6_validateItemIDInCCRH_impl ( const tag_t, map<int, vector<tag_t> >&, map<string, string>& );
boolean GET6_checkItemExistsInCC ( Connection* connection, string itemId );
boolean GET6_checkAttributesInCC ( Connection* connection, string drawingId, string attributeType );
string GET6_getDrgIDFromPartList ( string partsListID );

const string logger = "get.handler.GET_INTG_RuleHandlers";

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateItemIDInCCRH()
//
//    Purpose:   Rule Handler to validate the Solution Items exists in Control card and is active during ECN workflow initiation
//
//    Inputs:    tMessage - The Teamcenter Rule Handler Message Structure Input (EPM_rule_message_t)
//
//    Outputs:   none
//
//    Return:    EPM_go/EPM_nogo indicating whether the rule handler validation is passed or not (EPM_decision_t)
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     13 Jul, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
extern EPM_decision_t GET6_validateItemIDInCCRH ( EPM_rule_message_t tMsg )
{
    EPM_decision_t tDecision = EPM_go;

    LOG_TRACE ( logger, "START : GET6_validateItemIDInCCRH" );

    try
    {
        GET_processHandler ( tMsg, GET6_validateItemIDInCCRH_impl );
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_validateItemIDInCCRH" );
       tDecision = EPM_nogo;
    }

    LOG_TRACE ( logger, "END : GET6_validateItemIDInCCRH" );

    return tDecision;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_validateItemIDInCCRH_impl()
//
//    Purpose:   Rule Handler implementation function for GET6_validateParticipants handler
//
//    Inputs:    tTaskTag - The Teamcenter tag of the Root Task or the Task to which this handler is added (tag_t)
//               mAttachmentsMap - Map containing the Workflow attachments (Target, Reference)
//                                 with the Target/Reference type (int) and the vector of tags as value (vector<tag_t>)
//                                 (map<int, vector<tag_t>)
//               mArgumentsMap - Map containing the handler arguments with the argument name as the key and
//                               the argument value as the map value (map<string, string)
//    Outputs:   none
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     20 Jul, 2016         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
void GET6_validateItemIDInCCRH_impl ( const tag_t tTaskTag, map<int, vector<tag_t> > &mAttachmentsMap, map<string, string> &mArgumentsMap )
{   
    char encryptedPwd [MAX_ENCRYPT_PWD_LEN + 1];
    char szUnencryptedPw [MAX_ENCRYPT_PWD_LEN + 1];
    int iReturnVal = 0;
    string sid = "";
    string uName = "";
    string decodedPwd = "";    
    string sGroupName = "";
    unsigned nUnencryptedPwLen = 0;
    
    Environment *environment = NULL;
    Connection *connection = NULL;

    vector<tag_t> vTargetObjects;
    vector <string> vExcludeGroups;
    vector<string> vErrorMessages;    
    vector<string> vPrefValues;
    vector<string> vOutput;
    vector<bool> vPrefValuesLogical;
    GET_ItemRevisionUnqPtr itemRevisionPtr;    

    LOG_TRACE ( logger, "START : GET6_validateItemIDInCCRH_impl" );

    try
    {
        // user should mention one of these arguments
        if ( mArgumentsMap.find ( EXCLUDE_GROUP_ARG ) == mArgumentsMap.end() || mArgumentsMap[EXCLUDE_GROUP_ARG].empty() ) 
        {  
            THROW ( EXCLUDE_GROUP_ARG + string ( "\" has to be provided" ) );
        }
            
        //Get Control card integration turn on or not pref details
        getLogicalPrefValues ( GET_CONTROLCARD_INTEGRATION_ON, vPrefValuesLogical );
        if ( ( vPrefValuesLogical[0] == FALSE ) || ( !vPrefValuesLogical[0] ) )
        {
            LOG_DEBUG ( logger, "GET.INTEGRATION.CONTROLCARD.TURNON preference value is not set/is set to false - Skipping control card validation" );
        }
        else
        {
            //if control card integration is turn on to True the logic below will get called
            //Get RIN schema credentials
            getStringPrefValues ( GET_RINS_CREDENTIALS, vPrefValues );
            if ( !vPrefValues.empty() )
            {
                const string sPrefValue = vPrefValues[0];

                GET_splitString ( sPrefValue, COLON_SEPERATOR , vOutput );
                if ( vOutput.size() == 3 )
                {
                    uName = vOutput[0];
                    tc_strcpy ( encryptedPwd, vOutput[1].c_str() );                 
                    sid = vOutput[2];
                }

                unsigned nEncryptedPwLen = 0;
                nEncryptedPwLen = tc_strlen( encryptedPwd );
                LOG_DEBUG ( logger, "nEncryptedPwLen: " + nEncryptedPwLen );

                iReturnVal = GET_SYSAPI_decode64 ( encryptedPwd,
                                    nEncryptedPwLen,
                                    szUnencryptedPw,
                                    &nUnencryptedPwLen );
                LOG_DEBUG ( logger, "GET_SYSAPI_decode64 Return value: " + iReturnVal );
            }
            else
            {
                string sErrorMessage = "GET.INTEGRATION.RIN.CREDENTIALS value is not set, Please contact system administrator";
                LOG_ERROR ( logger, sErrorMessage );
            }

            // Get the item revision target object
            vector<tag_t> vTargetAttachments = mAttachmentsMap[EPM_target_attachment];
            if ( mArgumentsMap.find ( EXCLUDE_GROUP_ARG ) != mArgumentsMap.end() )
            {
                GET_splitString ( mArgumentsMap[EXCLUDE_GROUP_ARG], COMMA_CHARACTER, vExcludeGroups );
            }
            
            environment = Environment::createEnvironment ( Environment::DEFAULT );
            connection = environment->createConnection ( uName, szUnencryptedPw, sid );

            // Loop through the Target list and find out if any Document Revision's Dataset Named Reference name does not match with its Item ID
            for ( size_t iIndex = 0; iIndex < vTargetAttachments.size(); iIndex++ )
            {
                // Check if the target is an ItemRevision or not
                if ( ! GET_POM_object::isDescendant ( vTargetAttachments[iIndex], ITEMREVISION_CLASS ) )
                {
                    continue;
                }
                //Getting the first found item revision
                itemRevisionPtr = GET_ItemRevision::getInstance ( vTargetAttachments[iIndex] ); 
                // Get the Wso object
                GET_WorkspaceObjectUnqPtr wsoUnqPtr = GET_WorkspaceObject::getInstance ( vTargetAttachments[iIndex] );
                // Get the owing Group Name
                sGroupName = wsoUnqPtr->getOwningGroup()->getGroupFullName();
                LOG_DEBUG ( logger, "Logged in GroupName: " + sGroupName );
                
                //Underground Mining.ENGINEERING.TRANSPORTATION.GE TRANSPORTATION
                if ( ! vExcludeGroups.empty() && GET_isInVector ( vExcludeGroups, sGroupName ) ) 
                {  
                    break;
                }
          
                if ( environment != NULL && connection != NULL )
                {
                    // Get the Object Type
                    string sTypeName = itemRevisionPtr->getType();
                    
                    //Check object type is ECN revision type
                    if ( sTypeName.compare ( ECNREVISION_TYPE ) == 0 )
                    {
                        GET_ItemRevisionShrPtr ecnRevisionShrPtr ( move ( itemRevisionPtr ) );
                        //get the solution items of ECN
                        vector<GET_POM_objectUnqPtr> vSolutionItems = GET_ImanRelation::listRelatedObjects ( ecnRevisionShrPtr, CM_HAS_SOLUTION_ITEMS_PROP, false );
                        for ( size_t iNumSol = 0;  iNumSol < vSolutionItems.size(); iNumSol++ )
                        {
                            //Get the solution item ID
                            GET_ItemRevisionUnqPtr solItemRevisionPtr = GET_ItemRevision::getInstance ( vSolutionItems[iNumSol]->getTag() );
                            string solutionItemRevType = solItemRevisionPtr->getType();
                            GET_ItemUnqPtr solItemPtr = solItemRevisionPtr->getItem();
                            string solItemIdRootNumber = solItemPtr->getId();

                            if ( ( solutionItemRevType.compare ( MECHREV_TYPE ) == 0 ) || ( solutionItemRevType.compare ( ELECREV_TYPE ) == 0 ) )
                            {
                                LOG_DEBUG ( logger, "Checking for Mech and Elec Parts" );
                                //Get the root number from part list ID
                                solItemIdRootNumber = GET6_getDrgIDFromPartList ( solItemIdRootNumber );
                                LOG_DEBUG ( logger, "Root Number : " + solItemIdRootNumber);
                            }
                            if  ( ! solItemIdRootNumber.empty() )
                            { 
                                // Check if the solution item have valid status in CC
                                if ( ! GET6_checkItemExistsInCC ( connection, solItemIdRootNumber ) )
                                {
                                    string sErrorMessage = string ( " The solution item \"" ) + solItemPtr->getId() + "\" in not available in control card for root number: " + solItemIdRootNumber;
                                    vErrorMessages.push_back ( sErrorMessage );
                                    continue;
                                }

                                // Check if IP attribute is filled for solution is filled in CC and it is matched with teamcenter value
                                if ( ! GET6_checkAttributesInCC ( connection, solItemIdRootNumber, IP_CLASSFICATION ) )
                                {
                                    string sErrorMessage = string ( " IP value is not set for Solution Item \"" ) + solItemPtr->getId() + "\" in control card for root number: " + solItemIdRootNumber;
                                    vErrorMessages.push_back ( sErrorMessage );
                                }

                                // Check if ECCN attribute is filled for solution is filled in CC and it is matched with teamcenter value
                                if( ! GET6_checkAttributesInCC ( connection, solItemIdRootNumber, ECCN) )
                                {
                                    string sErrorMessage = string ( " ECCN value is not set for Solution Item \"" ) + solItemPtr->getId() + "\" in control card for root number: " + solItemIdRootNumber;
                                    vErrorMessages.push_back ( sErrorMessage );
                                }
                            }
                        }
                    }
                    else if ( sTypeName.compare( DOCUMENTREV_TYPE ) == 0 )
                    {
                        GET_ItemUnqPtr documentItemPtr = itemRevisionPtr->getItem();
                        string documentItemId  = documentItemPtr->getId();
                        bool bProceed = true;

                        // Check if the solution item have valid status in CC
                        if( !GET6_checkItemExistsInCC ( connection, documentItemId ) )
                        {
                            string sErrorMessage = string ( " The Document \"" ) + documentItemId + "\" in not available in control card ";
                            vErrorMessages.push_back ( sErrorMessage );
                            bProceed = false;
                        }

                        // Check if IP attribute is filled for solution is filled in CC    and it is matched with teamcenter value
                        if( bProceed && !GET6_checkAttributesInCC ( connection, documentItemId, IP_CLASSFICATION ) )
                        {
                            string sErrorMessage = string ( " IP value is not set for Document \"" ) + documentItemId + "\" in control card";
                            vErrorMessages.push_back ( sErrorMessage );
                        }

                        // Check if ECCN attribute is filled for solution is filled in CC and it is matched with teamcenter value
                        if( bProceed && !GET6_checkAttributesInCC ( connection, documentItemId, ECCN) )
                        {
                            string sErrorMessage = string ( " ECCN value is not set for Document \"" ) + documentItemId + "\" in control card";
                            vErrorMessages.push_back ( sErrorMessage );
                        }
                    }
                }
                else
                {
                    string sErrorMessage = "Could not establish connection";
                    vErrorMessages.push_back ( sErrorMessage );
                }
            }
            environment->terminateConnection( connection );
            Environment::terminateEnvironment( environment );
        }
    }
    catch ( exception& ex )
    {
        string sErrorMessage = ex.what();
        vErrorMessages.push_back ( sErrorMessage );
        if ( environment != NULL && connection != NULL )
        {
            environment->terminateConnection( connection );
            Environment::terminateEnvironment( environment );
        }
    }

    if ( vErrorMessages.size() > 0 )
    {
        string sConsolidatedErrorMessage = "\n";

        // Store the errors one by one in the stack
        for ( size_t iIndex = 0; iIndex < vErrorMessages.size(); iIndex++ )
        {
            sConsolidatedErrorMessage += vErrorMessages[iIndex] + "\n";
        }
        // Throw the error to the calling method (Where it will be handled)
        THROW ( sConsolidatedErrorMessage );
    }

    LOG_TRACE ( logger, "END : GET6_validateItemIDInCCRH_impl" );
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkAttributesInCC()
//
//    Purpose:   Method to check whether an attribute is filled in Control card and it is matched with value in teamcenter
//
//    Inputs:    connection        - Sql connection
//               drawingId         - Item ID to be checked (string)
//                 attributeType     - Attribute type to be checked//
//
//    Outputs:   A boolean flag indicating whether the given item exists in the control card
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     20 Jul, 2016         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
boolean GET6_checkAttributesInCC ( Connection* connection, string drawingId, string attributeType )
{
    boolean isAttributeFilled = false;
    string attValue = "";

    LOG_TRACE ( logger, "BEGIN : GET6_checkAttributesInCC" );
    try
    {
        //Prepare the statement to query attributes from root_attributes table
        Statement* statement = NULL;
        ResultSet* rs = NULL;
        GET_ResultSet *resultSet = NULL;
        string drawingAttSelect = string ( "select attribute_value from ROOT_ATTRIBUTES where root_number=" ) + SINGLEQUOTE + drawingId + SINGLEQUOTE + string ( "and attribute_type=" ) + SINGLEQUOTE + attributeType + SINGLEQUOTE;
        statement = connection->createStatement( drawingAttSelect ) ;

        //Execute the statement
        rs = statement->executeQuery() ;
        resultSet = new GET_ResultSet ( rs );
        //Error out if no records found in table
        while ( resultSet->next() )
        {
            isAttributeFilled = true;
            resultSet->getValue( ATTRIBUTE_VALUE, attValue );
            if ( attValue.empty() )
            {
                isAttributeFilled = false;
            }
        }

        statement->closeResultSet(rs);
        connection->terminateStatement(statement);

        if ( resultSet != NULL )
        {
            delete resultSet;
        }
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_checkAttributesInCC" );
    }

    LOG_TRACE ( logger, "END : GET6_checkAttributesInCC" );
    
    return isAttributeFilled;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_checkItemExistsInCC()
//
//    Purpose:   Method to check whether a Item exists in CC
//
//    Inputs:    connection - Sql connection
//               drawingId  - Item ID to be checked (string)
//
//    Outputs:   A boolean flag indicating whether the given item exists in the control card
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     20 Jul, 2016         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/
boolean GET6_checkItemExistsInCC ( Connection* connection, string itemId )
{
    boolean isValidItem = true;
    Statement* statement;
    ResultSet* rs;

    LOG_TRACE ( logger, "START : GET6_checkItemExistsInCC" );
    //Prepare select statement to query drawing_numbers table
    string sStatement = string ( "select * from drawing_numbers where drawing_number=" ) + SINGLEQUOTE + itemId + SINGLEQUOTE;
    statement =  connection->createStatement ( sStatement ) ;

    //Execute the statement
    rs =  statement->executeQuery() ;

    if( !rs->next() )
    {
        isValidItem = false;
    }

    statement->closeResultSet ( rs );
    connection->terminateStatement ( statement );

    LOG_TRACE ( logger, "END : GET6_checkItemExistsInCC" );

    return isValidItem;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   GET6_getDrgIDFromPartList(string itemID) 
//
//    Purpose:   Method to get the root number from item id
//
//    Inputs:    itemID     - Item ID//              
//
//    Outputs:   A string which is root number
//
//    Return:    none
//
//     History:
//      Who                   Date                 Description
//  TCS Development Team     20 Jul, 2016         Initial Creation
//
===========================================================================
//ENDFUNCDOC   ***/


string GET6_getDrgIDFromPartList ( string partsListID )
{
    LOG_TRACE ( logger, "BEGIN : GET6_getDrgIDFromPartList" );
    LOG_DEBUG ( logger, "Parts List ID : " +  partsListID );
    const string subStr = "-";
    const string temStr = "";
    string tempID = partsListID;
    string::size_type index = 0;
    bool isPattern = true;

    try
    {
        while ( ( index = tempID.find ( subStr,index ) ) != string::npos )
        {
            tempID.replace( index, subStr.size(), temStr );
            index += temStr.size();
        }
        const string sSym = "\\s+";
        const string tStr = "";
        string::size_type nSize = 0;
        string rootNumber = "";
        while ( ( nSize = tempID.find ( sSym, nSize ) ) != string::npos )
        {
            tempID.replace ( nSize, sSym.size(), tStr );
            nSize += tStr.size();
        }

        string temPartNum = "";
        if ( tempID.length() < 6 )
        {
            return tempID;
        }
        else
        {
            //check items start with P like P10DEP13
            if ( tempID.substr ( 0, 1 ).compare ( P ) == 0 )
            {
                int i = 1;
                bool bFlag = false;
                while ( i <= tempID.length () )
                {
                    if ( ! GET_SYSAPI_regexMatch ( REGEX_ITEM_ALPNUM_PATTN, tempID.substr ( i, 1 ).c_str()) )                    
                    {
                        LOG_DEBUG ( logger, "regexec isPattern value for not less than P chars " );
                        bFlag = true;
                        break;
                    }
                    i++;
                }
                if ( bFlag )
                {
                    i = 0;
                    while ( i <= tempID.length() )
                    {
                        isPattern = GET_SYSAPI_regexMatch ( REGEX_ITEM_ALPNUM_PATTN, tempID.substr ( i, 1 ).c_str() );

                        if( isPattern == true )
                        {
                            temPartNum += tempID.substr ( i, 1 );
                            LOG_DEBUG ( logger, "regexec temPartNum " + temPartNum  );
                        }
                        i++;
                    }
                    return tempID;
                }
            }

            //check for the root starts with 15
            string tempSub = tempID.substr ( 0, 2 );
            if ( tempSub.compare ( START_WITH_15 ) == 0 )
            {
                return tempID;
            }
            //check for the root starts with 17
            if ( tempSub.compare ( START_WITH_17 ) == 0 )
            {
                return tempID;
            }
            //check for the root starts with B
            if ( tempID.substr ( 0, 1 ).compare ( START_WITH_B ) == 0 )
            {
                return "";
            }
            //check for the root have P or G or H series. for ex: 84C345678P1 then elimanate the P1 then search root in CC
            if ( ( tempID.find ( P ) != string::npos ) || ( tempID.find ( G ) != string::npos )|| ( tempID.find(".") != string::npos ) || ( tempID.find ( H ) != string::npos ))
            {
                int temIndex = 0;
                bool bFlg = false;

                string reversedTemp =  tempID;
                for ( int i=0; i<reversedTemp.length()/2; i++ )
                {
                    char temp1 = reversedTemp[i];
                    reversedTemp[i] = reversedTemp[reversedTemp.length()-i-1];
                    reversedTemp[reversedTemp.length()-i-1] = temp1;
                }

                int tempStrLength = tempID.length();
                int pIndex = reversedTemp.find ( P ); 
                int gIndex = reversedTemp.find ( G );
                int hIndex = reversedTemp.find ( H );
               
                //# The next to the last character is either "P" or "G"  AND AND H
                //# The last character is a letter of the alphabet and NOT  a number then it should not be stripped off.

                string tmpChar = tempID.substr ( tempStrLength - 2, 1 );
                LOG_DEBUG ( logger, "regexec tmpChar REGEX_NON_NUMBER_PATTN " + tmpChar  );
               
                if( ( tmpChar.compare ( P ) == 0 ) || ( tmpChar.compare ( G ) == 0 ) || ( tmpChar.compare ( H ) == 0 ) )
                {
                    if ( tmpChar.compare ( G ) == 0 )
                    {
                        if ( tempID.substr ( tempStrLength - 3, tempStrLength - 2 ).compare ( P ) != 0 )
                        {
                            tmpChar = "";
                            tmpChar = tempID.substr ( ( tempStrLength - 1 ), tempStrLength ); 
                            LOG_DEBUG ( logger, "tempChar " + tmpChar  );
                            isPattern = GET_SYSAPI_regexMatch ( REGEX_NON_NUMBER_PATTN, tmpChar.c_str() );

                            if ( isPattern )
                            {
                                LOG_DEBUG ( logger, "G pattern match" + tempID  );
                                return tempID;
                            }
                        }
                    }
                    else
                    {
                        tmpChar = "";
                        tmpChar = tempID.substr ( ( tempStrLength - 1 ), tempStrLength );
                        LOG_DEBUG ( logger, "tempChar " + tmpChar );  
                        isPattern = GET_SYSAPI_regexMatch ( REGEX_NON_NUMBER_PATTN, tmpChar.c_str() );
                        LOG_DEBUG ( logger, "P pattern match2" + isPattern  ); 
                        if ( isPattern )
                        {
                            LOG_DEBUG ( logger, "P pattern match" + tempID  ); 
                            return tempID;
                        }
                    }
                }
               
                LOG_DEBUG ( logger, "part item id: " + tempID  );
                // Check whether the drawing contain both G and P characters.
                // If Group number exist for a drawing e.g. 84A111405PG2   trim only G2., 84E902393AGP1, 84E902393AGH1 
               
                //84E902393AGH1
                if ( ( hIndex > 0 ) && ( hIndex < gIndex  ) )
                { 
                    temIndex = gIndex;
                    tempID = tempID.substr ( 0, ( tempID.length() - temIndex ));
                    return tempID;
                }
                //84E902393APH1
                if ( ( hIndex > 0 ) && ( hIndex < pIndex  ) )
                {
                    temIndex = pIndex;
                    tempID = tempID.substr ( 0, ( tempID.length() - temIndex ));
                    return tempID;
                }
                if ( ( gIndex > 0 ) && ( gIndex < pIndex  ) )
                {
                    pIndex = -1;
                }
                if ( pIndex != -1 )
                {
                    temIndex = pIndex;
                    bFlg = true;
                } 
                
                if ( !bFlg )
                {
                    pIndex = reversedTemp.find( G );
                    if ( pIndex != -1 )
                    {
                        if ( !bFlg )
                        {
                            temIndex = pIndex;
                            bFlg = true;
                        }
                        else if ( pIndex < temIndex )
                        {
                            temIndex = pIndex;
                        }
                    }

                    if ( !bFlg )
                    {  
                        pIndex = reversedTemp.find ( H );
                        if ( pIndex != -1 )
                        { 
                            if ( !bFlg )
                            {
                                temIndex = pIndex;
                                bFlg = true;
                            }
                            else if ( pIndex < temIndex )
                            {
                                temIndex = pIndex;
                            }
                        }

                        if ( !bFlg )
                        {
                            pIndex = reversedTemp.find ( "." );
                            if ( pIndex != -1 )
                            {
                                if ( !bFlg )
                                {
                                    temIndex = pIndex;
                                    bFlg = true;
                                }
                                else if ( pIndex < temIndex )
                                {
                                    temIndex = pIndex;
                                }
                            }
                        }
                    }
                }

                // If the part number is 84A123456PS  then return it 84A123456PS only.
                if ( ( pIndex == 1 ) && ( tempID.substr ( ( tempID.length()-2 ),2 ).compare ( PS ) == 0 ) )
                {
                    LOG_DEBUG ( logger, "part item id end with PS: " + tempID  );
                    return tempID;
                }
                // If the part number is 84A123456G  then return it 84A123456G only.
                if ( ( temIndex == 0 ) && ( tempID.substr ( ( tempID.length()-1 ), 1 ).compare ( G ) == 0 ) )
                {
                    LOG_DEBUG ( logger, "part item id ends with G: " + tempID  );
                    return tempID;

                }
                // If the part number is like 84A213385CH  then return 84A213385CH only.
                if ( ( temIndex == 0 ) )
                {
                    if ( tempID.substr ( ( tempID.length()-1 ), 1 ) == H )
                    {
                        LOG_DEBUG ( logger, "part item id ends with CH : " + tempID  );
                        return tempID;
                    }
                }
                // If the part number is like 84A213385HT  then return 84A213385HT only.
                if ( ( temIndex == 0 ) && ( tempID.substr ( ( tempID.length()-2), 2 ).compare ( HT ) == 0 ) )
                {
                    LOG_DEBUG ( logger, "part item id ends with HT : " + tempID  );
                    return tempID;
                }
                // if the part number is like 41C666376AP  then return 41C666376AP  only.
                if ( ( temIndex == 0 ) && ( tempID.substr ( ( tempID.length()-1 ), 1 ).compare ( P ) == 0 ) )
                {
                    LOG_DEBUG ( logger, "part item id ends with AP : " + tempID  );
                    return tempID;
                }
                
                rootNumber = tempID.substr ( 0, ( tempID.length() - 1 ) - temIndex ); 
                LOG_DEBUG ( logger, "rootNumber: " + rootNumber  );
                return rootNumber;  
            }
        } 
    }
    catch ( ... )
    {
       catchHandlerExceptions ( "GET6_getDrgIDFromPartList" );
    }

    LOG_TRACE ( logger, "END : GET6_getDrgIDFromPartList" );

    return tempID;
}
