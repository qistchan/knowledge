
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   get_rename_revisionrule.cxx
//
//   Purpose :   Utility to rename Teamcenter Revision Rules
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     16 May, 2017         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Incudes
#include <GET_Util_Common.hxx>
#include <GET_sysapi.h>
#include <GET_Utils.hxx>
#include <GET_Constants.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_RevisionRule.hxx>

// Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

const string logger = "get.get_rename_revisionrule";

// static method declarations
static void displayUsage();

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   main
//
//   Purpose :   The main method for this program.
//
//   Inputs  :   iArgc - The integer specifying the number of command line arguments passed to the program
//               pcArgv - The input character double pointer containing the command line input values
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
int main ( int iArgc, char *pcArgv[] )
{
    bool bEndOfFile = false;

    ifstream configFile;
    ifstream inputFile;

    int iFail = ITK_ok;

    map<string, string> progArgs;

    ResultCheck stat;

    string sTCUname = "";
    string sTCPassword = "";
    string sTCGroup = "";
    string sFileString = "";

    vector<string> vRevRuleInput;

    LOG_TRACE ( logger, "START : main" );

    try
    {
        GET_convertToMap ( iArgc, ( const char** ) pcArgv, progArgs );

        if ( progArgs.find ( "-h" ) != progArgs.end() )
        {
            displayUsage();
            return iFail;
        }

        if ( progArgs.find ( ARG_INPUT_FILE) == progArgs.end()  || progArgs[ARG_INPUT_FILE].empty() )
        {
            THROW ( "The argument " + string ( ARG_INPUT_FILE ) + " was not provided or has empty value" );
        }

        if ( progArgs.find ( ARG_CONFIG_FILE ) != progArgs.end() && ! progArgs[ARG_CONFIG_FILE].empty() )
        {
            // Parse the Config File and check if all mandatory arguments are provided
            configFile.open ( progArgs[ARG_CONFIG_FILE].c_str() );
            if ( ! configFile.is_open() )
            {
                THROW ( "Unable to open the configuration file " + progArgs[ARG_CONFIG_FILE] );
            }
            while ( ! bEndOfFile )
            {
                string sKey = "";
                string sValue = "";
                vector<string> vFileContentsVector;

                if ( getline ( configFile, sFileString ).eof() )
                {
                    bEndOfFile = true;
                }

                GET_strtrim ( sFileString );
                GET_splitString ( sFileString, "=", vFileContentsVector );
                if ( vFileContentsVector.size () < 2 )
                {
                    continue;
                }

                sKey = vFileContentsVector[0];
                sValue = vFileContentsVector[1];
                GET_toUpper ( sKey );
                GET_strtrim ( sKey );
                GET_strtrim ( sValue );
                if ( sKey.compare ( CONFIG_TC_USERNAME ) == 0 )
                {
                    sTCUname = sValue;
                }
                else if ( sKey.compare ( CONFIG_TC_PASSWORD ) == 0 )
                {
                    sTCPassword = sValue;
                }
                else if ( sKey.compare ( CONFIG_TC_GROUP ) == 0 )
                {
                    sTCGroup = sValue;
                }
            }
            configFile.close();
        }

        // Parse the Input File and get all Revision Rule Inputs
        bEndOfFile = false;
        inputFile.open ( progArgs[ARG_INPUT_FILE].c_str() );
        if ( ! inputFile.is_open() )
        {
            THROW ( "Unable to open the configuration file " + progArgs[ARG_INPUT_FILE] );
        }
        while ( ! bEndOfFile )
        {
            if ( getline ( inputFile, sFileString ).eof() )
            {
                bEndOfFile = true;
            }
            if ( sFileString.find ( TILDA_CHARACTER ) != string::npos )
            {
                GET_strtrim ( sFileString );
                vRevRuleInput.push_back ( sFileString );
            }
        }
        inputFile.close();

        // Teamcenter login
        loginToTC ( sTCUname, sTCPassword, sTCGroup );

        // Change the Revision Rule Name for each rule
        for ( size_t iIndex = 0; iIndex < vRevRuleInput.size(); iIndex++ )
        {
            GET_RevisionRuleUnqPtr getRevRuleUnqPtr;

            vector<string> vSplitVector;

            GET_splitString ( vRevRuleInput[iIndex], TILDA_CHARACTER, vSplitVector );

            try
            {
                getRevRuleUnqPtr = GET_RevisionRule::find ( vSplitVector[0] );
            }
            catch ( const IFail &exp )
            {
                if ( exp.ifail() != 710041 )
                {
                    throw exp;
                }
            }
            if ( getRevRuleUnqPtr.get() == NULL )
            {
                cout<<endl<<"WARNING !!! No Revision Rule with the name \""<<vSplitVector[0].c_str()<<"\" found in Teamcenter"<<endl;
                continue;
            }
            cout<<endl<<"Updating the Revision Rule from the old name \""<<vSplitVector[0].c_str()<<"\" to the new name \""<<vSplitVector[1].c_str()<<"\" ..."<<endl;
            getRevRuleUnqPtr->setName ( vSplitVector[1] );
            getRevRuleUnqPtr->save();
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        LOG_ERROR ( logger, ex.getMessage() );
        cout<<endl<<ex.getMessage().c_str()<<endl;
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_GENERAL_EXCEPTION;
        LOG_ERROR ( logger, ex->getErrorMessage() );
        cout<<endl<<ex->getErrorMessage().c_str()<<endl;
        delete ex;
    }
    catch ( ... )
    {
        string sMessage =  string ( pcArgv[0] ) + " failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sMessage );
        iFail = GET_GENERAL_EXCEPTION;
        cout<<endl<<sMessage.c_str()<<endl;
    }

    LOG_TRACE ( logger, "END : main" );

    return iFail;
}

/*STARTFUNCDOC ***
//
===========================================================================
//   Function:   displayUsage
//
//   Purpose :   Method to display the help/usage information
//
//   Inputs  :   none
//
//   Outputs :   none
//
//   Return  :   none
//
//   History :
//      Who                   Date                 Description
//  TCS Development Team     18 May, 2017         Initial creation
//
===========================================================================
//ENDFUNCDOC   ***/
static void displayUsage()
{
    cout<<"Usage is: get_rename_revisionrule [-h] [-config=<configuration file>] -file=<input file>"<<endl;
    cout<<"       -h               displays detailed help information"<<endl;
    cout<<"       -config          input config file"<<endl;
    cout<<"       -file            input file"<<endl;
}
