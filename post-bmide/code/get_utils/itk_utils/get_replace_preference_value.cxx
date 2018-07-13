
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   get_replace_preference_value.cxx
//
//    Purpose:   Utility to replace preference values for a given scope
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     18 May, 2017         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_Util_Common.hxx>
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_Utils.hxx>
#include <GET_Constants.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_POM_user.hxx>

// Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// C++ Includes
#include <vector>

// static method declarations
static void displayUsage();

const string logger = "get.get_replace_preference_value";

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

    vector<string> vQueryInputFiles;
    vector<string> vPrefValues;
    vector<GET_POM_objectUnqPtr> vPrefInstances;

    LOG_TRACE( logger, "START : main" );

    try
    {
        GET_convertToMap ( iArgc, ( const char** ) pcArgv, progArgs );

        if ( progArgs.find ( "-h" ) != progArgs.end() )
        {
            displayUsage();
            return iFail;
        }

        if ( progArgs.find ( ARG_INPUT_FILE) == progArgs.end ()  || progArgs[ARG_INPUT_FILE].empty() )
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

        // Parse the Input File and get all Preference value details
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
                vPrefValues.push_back ( sFileString );
            }
        }
        inputFile.close();
        if ( vPrefValues.size() == 0 )
        {
            THROW ( "No Preferences provided in the input file for modification" );
        }

        // Teamcenter login
        loginToTC ( sTCUname, sTCPassword, sTCGroup );

        // Get the TC_Preferece class instances
        vPrefInstances = GET_POM_object::getAllInstances ( TC_PREFERENCES_CLASS );
        for ( size_t iIndex = 0; iIndex < vPrefInstances.size(); iIndex++ )
        {
            string sDataValue = "";

            // Check if the preference is a User Preference Instance
            GET_POM_objectUnqPtr objectPtr = vPrefInstances[iIndex]->getPropertyTag ( OBJECT_TAG_ATTR );
            if ( ! GET_POM_object::isDescendant ( objectPtr->getTag(), POM_USER_CLASS ) )
            {
                continue;
            }
            GET_POM_userUnqPtr userPtr = GET_POM_user::getInstance ( objectPtr->getTag() );

            // Get the User Preference PLMXML
            sDataValue = vPrefInstances[iIndex]->getPropertyString ( DATA_ATTR );
            for ( size_t iKnx = 0; iKnx < vPrefValues.size(); iKnx++ )
            {
                vector<string> vSplitVector;

                string sNewDataValue = "";

                GET_splitString ( vPrefValues[iKnx], TILDA_CHARACTER, vSplitVector );
                if ( sDataValue.find ( vSplitVector[0] ) == string::npos )
                {
                    continue;
                }

                sNewDataValue = GET_replaceSubString ( sDataValue, vSplitVector[0], vSplitVector[1] );
                cout<<endl<<"Replacing the old preference value \""<<vSplitVector[0].c_str()<<"\" with the new value \""<<vSplitVector[1].c_str()<<"\" for the user \""<<userPtr->getID().c_str()<<"\" ..."<<endl;
                vPrefInstances[iIndex]->setProperty ( DATA_ATTR, sNewDataValue );
            }
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
    cout<<"Usage is: get_replace_preference_value [-h] [-config=<configuration file>] -file=<input file>"<<endl;
    cout<<"       -h               displays detailed help information"<<endl;
    cout<<"       -config          input config file"<<endl;
    cout<<"       -file            input file"<<endl;
}
