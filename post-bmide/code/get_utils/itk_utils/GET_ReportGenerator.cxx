
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_ReportGenerator.cxx
//
//    Purpose:   Utility to generate reports
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     18 May, 2017         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_ReportGenerator.hxx>
#include <GET_Util_Common.hxx>
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_Utils.hxx>

// Teamcenter Includes
#include <pom/enq/enq.h>

#include <GET_Constants.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>

// Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

//static int POM_enquiry_set_sql_string ( const char*, char* );
static void processInput();
static void buildQuery();
static void executeAndProcessQuery();
static void displayUsage();

map<string, string> progArgs;
string sQueryInputFiles;

struct Query
{
    string sEnqID;
    string sQuery;
    string sOutFile;
    string sQueryHeader;
    vector<string> vDataType;
};

vector <Query> vQuery;

const string logger = "get.GET_ReportGenerator";

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

    int iFail = ITK_ok;

    string sTCUname = "";
    string sTCPassword = "";
    string sTCGroup = "";
    string sFileString = "";

    LOG_TRACE ( logger, "START : main" );

    try
    {
        GET_convertToMap ( iArgc, ( const char** ) pcArgv, progArgs );

        if ( progArgs.find ( "-h" ) != progArgs.end() )
        {
            displayUsage();
            return iFail;
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

        processInput();
        loginToTC ( sTCUname, sTCPassword, sTCGroup );
        executeAndProcessQuery();
        ITK_exit_module( true );
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

void buildQuery (int iVecIndex)
{
    ResultCheck stat;

    LOG_TRACE( logger, "START : buildQuery" );

    stat = POM_enquiry_create ( vQuery[iVecIndex].sEnqID.c_str() );
    char **selectAttrs;

    vector <string> vClassAliasVec;
    size_t nTagAttr = 0;
    size_t nIntAttr = 0;
    size_t nDoubleAttr = 0;
    size_t nDateAttr = 0;
    size_t nStringAttr = 0;
    size_t nLogicalAttr = 0;

    for ( size_t index = 0; index < vQuery[iVecIndex].vDataType.size(); index++ )
    {
        string sClassName = ITEMREVISION_CLASS;
        string sAttr;
        if ( vQuery[iVecIndex].vDataType[index].compare (TAG_TYPE) == 0 )
        {
            if ( nTagAttr++ != 0 )
            {
                sClassName += GET_intToString (nTagAttr);
            }
            sAttr = TAG_ATTR;
        }
        if ( vQuery[iVecIndex].vDataType[index].compare (INT_TYPE) == 0 )
        {
            if ( nTagAttr++ != 0 )
            {
                sClassName += GET_intToString (nIntAttr);
            }
            sAttr = INT_ATTR;
        }
        if ( vQuery[iVecIndex].vDataType[index].compare (DOUBLE_TYPE) == 0 )
        {
            if ( nDoubleAttr++ != 0 )
            {
                sClassName += GET_intToString (nDoubleAttr);
            }
            sAttr = DOUBLE_ATTR;
        }
        if ( vQuery[iVecIndex].vDataType[index].compare (DATE_TYPE) == 0 )
        {
            if ( nDateAttr++ != 0 )
            {
                sClassName += GET_intToString (nDateAttr);
            }
            sAttr = DATE_ATTR;
        }
        if ( vQuery[iVecIndex].vDataType[index].compare (STRING_TYPE) == 0 )
        {
            if ( nStringAttr++ != 0 )
            {
                sClassName += GET_intToString (nStringAttr);
            }
            sAttr = STRING_ATTR;
        }
        if ( vQuery[iVecIndex].vDataType[index].compare (LOGICAL_TYPE) == 0 )
        {
            if ( nLogicalAttr++ != 0 )
            {
                sClassName += GET_intToString (nLogicalAttr);
            }
            sAttr = LOGICAL_ATTR;
        }

        if ( sClassName.compare (ITEMREVISION_CLASS) != 0 )
		{
			bool bIsFound = false;
			for ( size_t iKnx = 0; iKnx < vClassAliasVec.size(); iKnx++ )
			{
				if ( vClassAliasVec[iKnx].compare ( sClassName ) == 0 )
				{
					bIsFound = true;
					break;
				}
			}
			if ( !bIsFound )
			{
				stat = POM_enquiry_create_class_alias ( vQuery[iVecIndex].sEnqID.c_str(), ITEMREVISION_CLASS, true, sClassName.c_str() );
				vClassAliasVec.push_back ( sClassName );
			}
		}
        const char *selectAttrs[] = { sAttr.c_str() };
        stat = POM_enquiry_add_select_attrs ( vQuery[iVecIndex].sEnqID.c_str(), sClassName.c_str(), 1, selectAttrs );
    }

    LOG_TRACE( logger, "END : buildQuery" );
}

void executeAndProcessQuery ()
{
    ResultCheck stat;

    for ( size_t index = 0; index < vQuery.size(); index++ )
    {
        buildQuery( index );

        int iNoRows = 0;
        int iNoCols = 0;
        void ***report = NULL;

        LOG_TRACE( logger, "START : executeAndProcessQuery" );

        //stat = POM_enquiry_set_sql_string ( vQuery[index].sEnqID.c_str(), (char *)vQuery[index].sQuery.c_str() );

        stat = POM_enquiry_execute ( vQuery[index].sEnqID.c_str(), &iNoRows, &iNoCols, &report );

        cout<<"No. of rows for : "<< vQuery[index].sEnqID<<" - "<<iNoRows<<endl;
        if ( report != NULL )
        {
            ofstream fOutFile;
            fOutFile.open ( vQuery[index].sOutFile, ios::trunc );
            fOutFile<<vQuery[index].sQueryHeader<<"\n";

            cout<<"Output File : "<<vQuery[index].sOutFile<<endl;
            for( int i = 0; i < iNoRows; i++ )
            {
                for ( size_t cIndex = 0; cIndex < vQuery[index].vDataType.size(); cIndex++ )
                {
                    if ( vQuery[index].vDataType[cIndex].compare (TAG_TYPE) == 0 )
                    {
                        fOutFile<<(char *)report[i][cIndex];
                    }
                    if ( vQuery[index].vDataType[cIndex].compare (INT_TYPE) == 0 )
                    {
                        fOutFile<<*(int *)report[i][cIndex];
                    }
                    if ( vQuery[index].vDataType[cIndex].compare (DOUBLE_TYPE) == 0 )
                    {
                        fOutFile<<*(double *)report[i][cIndex];
                    }
                    if ( vQuery[index].vDataType[cIndex].compare (DATE_TYPE) == 0 )
                    {
                        fOutFile<<(char *)report[i][cIndex];
                    }
                    if ( vQuery[index].vDataType[cIndex].compare (STRING_TYPE) == 0 )
                    {
                        string tmpValue = (char *)report[i][cIndex];
                        fOutFile<<tmpValue;
                    }
                    if ( vQuery[index].vDataType[cIndex].compare (LOGICAL_TYPE) == 0 )
                    {
                        fOutFile<<*(logical *)report[i][cIndex];
                    }
                    if ( (cIndex + 1) < vQuery[index].vDataType.size() )
                    {
                        fOutFile<<TILDA_CHARACTER;
                    }
                }
                if ( (i + 1) < iNoRows )
                {
                    fOutFile<<"\n";
                }
            }

            fOutFile.close();
        }

        /* Deleting the query */
        stat = POM_enquiry_delete ( vQuery[index].sEnqID.c_str() );

         if( report != NULL )
         {
             MEM_free( report );
         }
    }

    LOG_TRACE( logger, "END : executeAndProcessQuery" );
}

void processInput()
{
    ifstream inputFile;

    string fileString = "";

    LOG_TRACE( logger, "START : processInput" );

    if ( progArgs.find ( ARG_OUT_DIR ) == progArgs.end () )
    {
        string argExceptionMessage = "The mandatory argument " + string ( ARG_OUT_DIR ) + " was not provided";
        cout<<"argExceptionMessage : "<<argExceptionMessage<<endl;
        //displayHelp();
        LOG_ERROR( logger, argExceptionMessage );
        THROW ( argExceptionMessage );
    }

    // Parse the Config File and check if all mandatory arguments are provided
    if ( GET_SYSAPI_check_FileOrDirExists ( progArgs[ARG_OUT_DIR].c_str () ) != 0 )
    {
        string fileExceptionMessage = "Directory: " + progArgs[ARG_OUT_DIR] + " does not exist";
        LOG_ERROR( logger, fileExceptionMessage );
        THROW ( fileExceptionMessage );
    }

    if ( progArgs.find ( ARG_INPUT_FILE) == progArgs.end () )
    {
        string argExceptionMessage = "The mandatory argument " + string ( ARG_INPUT_FILE) + " was not provided";
        cout<<"argExceptionMessage : "<<argExceptionMessage<<endl;
        //displayHelp();
        LOG_ERROR( logger, argExceptionMessage );
        THROW ( argExceptionMessage );
    }

    // Parse the Config File and check if all mandatory arguments are provided
    inputFile.open (progArgs[ARG_INPUT_FILE].c_str ());
    if ( !inputFile.is_open () )
    {
        string fileExceptionMessage = "Unable to open the query input Text file " + progArgs[ARG_INPUT_FILE];
        LOG_ERROR( logger, fileExceptionMessage );
        THROW ( fileExceptionMessage );
    }

    vector <string> vQueryInputFiles;
    while ( !getline (inputFile, fileString).eof () )
    {
        vQueryInputFiles.push_back ( fileString );
    }
    inputFile.close();

    vector <string> vDisallowedQuery;
    vDisallowedQuery.push_back("UPDATE");
    vDisallowedQuery.push_back("INSERT");
    vDisallowedQuery.push_back("DELETE");

    for ( size_t index = 0; index < vQueryInputFiles.size();index++ )
    {
        ifstream fQueryInputFile;
        string fileString = "";
        Query query;

        fQueryInputFile.open ( vQueryInputFiles[index].c_str () );
        if ( !fQueryInputFile.is_open () )
        {
            string fileExceptionMessage = "Unable to open the input input Text file " + vQueryInputFiles[index];
            LOG_ERROR( logger, fileExceptionMessage );
            THROW ( fileExceptionMessage );
        }
        while ( !getline (fQueryInputFile, fileString).eof () )
        {
            string key = "";
            vector<string> fileContentsVector;

            GET_splitString (fileString, "=", fileContentsVector);
            if ( fileContentsVector.size () < 2 )
            {
                continue;
            }

            key = fileContentsVector[0];
            GET_toUpper ( key );

            string value = "";
            for( size_t splitVecIndex = 1; splitVecIndex < fileContentsVector.size(); splitVecIndex++)
            {
                value += fileContentsVector[splitVecIndex];
                if( splitVecIndex + 1 < fileContentsVector.size())
                {
                    value += "=";
                }
            }

            GET_toUpper ( value );
            query.sEnqID = ENQUIRY_ID + GET_intToString ( index );
            if ( key.compare ( CONFIG_QUERYHEADER ) == 0 )
            {
                query.sQueryHeader = value;
            }
            else if ( key.compare ( CONFIG_QUERYOUTPUTTYPES ) == 0 )
            {
                string sOutTypes = value;
                GET_splitString ( value, COMMA_CHARACTER, query.vDataType );
            }
            else if ( key.compare ( CONFIG_QUERYSQL ) == 0 )
            {
                for ( size_t iDisIndex = 0; iDisIndex < vDisallowedQuery.size(); iDisIndex++ )
                {
                    if ( value.find ( vDisallowedQuery [iDisIndex] ) != string::npos )
                    {
                        string argExceptionMessage = "Execution of prohibited query attempted, you shall be prosecuted as per contract and law ";
                        cout<<"argExceptionMessage : "<<argExceptionMessage<<endl;
                        LOG_ERROR( logger, argExceptionMessage );
                        THROW ( argExceptionMessage );
                    }
                }
                query.sQuery = value;
            }

            vector <string> vFileName;
            GET_splitString ( vQueryInputFiles[index], ".", vFileName );
            string sOutFileName = vFileName[0];
            vFileName.clear();
            GET_splitString ( sOutFileName, string ( GET_SYSAPI_getFileSeparator() ), vFileName );
            query.sOutFile = progArgs[ARG_OUT_DIR] + string ( GET_SYSAPI_getFileSeparator() ) + vFileName[vFileName.size() - 1] + OUT_FILE_TYPE;
        }

        vQuery.push_back ( query );

        fQueryInputFile.close();
    }

    LOG_TRACE( logger, "START : processInput" );
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
    cout<<"Usage is: GET_ReportGenerator [-h] [-config=<configuration file>] -file=<input file> -out=<Output Dir>"<<endl;
    cout<<"       -h               displays detailed help information"<<endl;
    cout<<"       -config          input config file"<<endl;
    cout<<"       -file            input file"<<endl;
    cout<<"       -out             output directory"<<endl;
}
