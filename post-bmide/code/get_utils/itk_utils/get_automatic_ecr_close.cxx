
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   get_automatic_ecr_close.cxx
//
//    Purpose:   Utility to close approved ECR, if Implemented ECNs' approved date has crossed the Threshold
//
//    History:
//      Who                           Date                 Description
//  Capgemini Development Team     25 May, 2017         Initial creation
//  TCS Development Team           01 Jun, 2017         Modified the code and corrected all the errors and added functionality to send email to infodba
//  TechM Development Team         23 Aug, 2017         Modified the code to accept the login credentials(-u -p -g) directly from command prompt
//  TCS Development Team           14 May, 2018         Modified the code to calculate date difference in hours
//  TechM Development Team         24 May, 2018         Modified the code to search for the ECR/ECNs based on Closure, Disposition and Maturity values.
//   ============================================================================
// ENDFILEDOC   ***/

// GET Includes
#include <GET_Constants.hxx>
#include <GET_cpp_stl.h>
#include <GET_Date.hxx>
#include <GET_EPMJob.hxx>
#include <GET_Exception.hxx>
#include <GET_ImanQuery.hxx>
#include <GET_ImanRelation.hxx>
#include <GET_Item.hxx>
#include <GET_ItemRevision.hxx>
#include <GET_Person.hxx>
#include <GET_POM_object.hxx>
#include <GET_POM_user.hxx>
#include <GET_Preferences.hxx>
#include <GET_SMTP_Mail.hxx>
#include <GET_sysapi.h>
#include <GET_TC_Attributes.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_TC_Types.hxx>
#include <GET_TC_Utils.hxx>
#include <GET_Utils.hxx>
#include <GET_Util_Common.hxx>

// Teamcenter Includes
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// C++ Includes
#include <vector>
#include <ctime>

// static method declarations
static void displayUsage();

const string logger = "get.get_automatic_ecr_close";

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
//      Who                           Date                 Description
//  Capgemini Development Team     25 May, 2017         Initial creation
//  TCS Development Team           01 Jun, 2017         Modified the code and corrected all the errors and added functionality to send email to infodba
//  TechM Development Team         23 Aug, 2017         Modified the code to accept the login credentials(-u -p -g) directly from command prompt
//  TechM Development Team         10 Apr, 2018         Modified the code to accept the Canceled State
//  TCS Development Team           14 May, 2018         Modified the code to calculate date difference in hours
===========================================================================
//ENDFUNCDOC   ***/
int main ( int iArgc, char *pcArgv[] )
{
    int iFail = ITK_ok;

    string sErrorMessage = "";
  
    map<string, string> progArgs;

    vector<string> vEmailIDs;

    LOG_TRACE( logger, "START : main" );

    try
    {
        string sTCUname = "";
        string sTCPassword = "";
        string sTCGroup = "";

        vector<GET_POM_objectUnqPtr> vECRInstances;
        vector<GET_POM_objectShrPtr> vECRToBeReleased;
        vector<int> vServerPrefValues;
        vector<string> vEntries;
        vector<string> vValues;

        int iNoOfHoursDiffValue = 1;

        GET_ItemRevisionUnqPtr ecRevisionPtr;

        GET_convertToMap ( iArgc, ( const char** ) pcArgv, progArgs );

        // Validate the input arguments
        if ( progArgs.find ( ARG_HELP ) != progArgs.end() || progArgs.find ( ARG_USERID ) == progArgs.end() || progArgs[ARG_USERID].empty() )
        {
            displayUsage();
            return iFail;
        }
        if ( progArgs.find ( ARG_PASSWORD ) != progArgs.end() && ! progArgs[ARG_PASSWORD].empty() )
        {
            sTCPassword = progArgs[ARG_PASSWORD];
        }
        if ( progArgs.find ( ARG_GROUP ) != progArgs.end() && ! progArgs[ARG_GROUP].empty() )
        {
            sTCGroup = progArgs[ARG_GROUP];
        }
        sTCUname = progArgs[ARG_USERID];

        // Teamcenter login
        loginToTC ( sTCUname, sTCPassword, sTCGroup );

        // Get the GET_ECR_ECN_CLOSE_INTERVAL preference value
        getIntPrefValues ( GET_ECR_ECN_CLOSE_INTERVAL, vServerPrefValues );

        //Check if the Preference value is Zero, if yes then default it to 1
        if ( vServerPrefValues.size() > 0 && vServerPrefValues[0] != 0 )
        {
            iNoOfHoursDiffValue = vServerPrefValues[0];
            cout<<endl<<"The configured value for the difference in hours between the current date and the last approved ECN is : "<<iNoOfHoursDiffValue<<endl;
        }
        else
        {
            cout<<endl<<"Preference "<<GET_ECR_ECN_CLOSE_INTERVAL<<" not defined or does not have a valid value. Using the default value : "<<iNoOfHoursDiffValue<<endl;
        }

        //User Entries for the Query
        /*vEntries.push_back ( QUERY_TYPE_ENTRY );
        vEntries.push_back ( QUERY_STATUS_ENTRY );

        //User Values for the Query
        vValues.push_back ( ECRREVISION_TYPE );
        vValues.push_back ( APPROVED ); */

        //User Entries for the Query
        vEntries.push_back ( "ECR Closure" );
        vEntries.push_back ( "ECR Disposition" );
        vEntries.push_back ( "ECR Maturity" );
        vEntries.push_back ( QUERY_STATUS_ENTRY );

        //User Values for the Query
        vValues.push_back ( "Open" );
        vValues.push_back ( "Approved" );
        vValues.push_back ( "Reviewing" );
        vValues.push_back ( APPROVED );


        GET_DateUnqPtr currentDate = GET_Date::getCurrentDate();
        string sCurrentDate = currentDate->toString();

        //Query to find list of Approved ECR Revisions
        //vECRInstances = GET_ImanQuery::executeQuery ( ITEM_REVISION_QUERY, vEntries, vValues );
        vECRInstances = GET_ImanQuery::executeQuery ( "GET ECR Revisions", vEntries, vValues );
        for ( size_t iIndex = 0; iIndex < vECRInstances.size(); iIndex++ )
        {
            bool bBreakOuterLoop = false;

            vector<GET_WorkspaceObjectUnqPtr> vECNRevisions;

            GET_ItemRevisionShrPtr ecRevisionPtr ( move ( GET_ItemRevision::getInstance ( vECRInstances[iIndex]->getTag() ) ) );

            // List attached ECN Revisions with 'Implements' relation
            vECNRevisions = GET_ImanRelation::listRelatedWsObjects ( ecRevisionPtr, CMIMPLEMENTS, ECNREVISION_TYPE, true );

            if ( vECNRevisions.size() == 0 )
            {
                continue;
            }
            for ( size_t iJIndex = 0; iJIndex < vECNRevisions.size(); iJIndex++ )
            {
                double dDifferenceInHours = 0;
				GET_ItemRevisionShrPtr ECNRevisionPtr ( move ( GET_ItemRevision::getInstance ( vECNRevisions[iJIndex]->getTag() ) ) );
                //Check for Approved ECN Revisions
                if ( ! vECNRevisions[iJIndex]->hasReleaseStatus ( APPROVED ) && ! vECNRevisions[iJIndex]->hasReleaseStatus ( GET6CANCELED ) )
                {
                    bBreakOuterLoop = true;
                    break;
                }

                GET_DateUnqPtr ecnReleaseDateUnqPtr = vECNRevisions[iJIndex]->getPropDate ( DATE_RELEASED_ATTR );
                GET_DateShrPtr ecnReleaseDate ( move ( ecnReleaseDateUnqPtr ) );
                dDifferenceInHours = currentDate->getDifferenceInDays ( ecnReleaseDate ) * 24;
                // Skip the ECR Revision, if threshold is not crossed
                if ( dDifferenceInHours < iNoOfHoursDiffValue )
                {
                    bBreakOuterLoop = true;
                    break;
                }
            }
            if ( bBreakOuterLoop )
            {
            	continue;
            }
            vECRToBeReleased.push_back ( ecRevisionPtr );
        }

        // Initiate the Workflow on those ECRs that satisfy the criteria
        if ( vECRToBeReleased.size() > 0 )
        {
            cout<<endl<<"Found "<<vECRToBeReleased.size()<<" ECRs for closure. Initiating the \"" + string ( SUBMIT_TO_CLOSE_CHANGE_WORKFLOW ) + "\" WF on these ECRs..."<<endl;
            // Release ECR Revisions which has ECN Revision with Approved Date beyond Threshold
            string sProcessName = SUBMIT_TO_CLOSE_CHANGE_WORKFLOW + string ( HYPHEN_SEPERATOR ) + sCurrentDate;
            string sProcessDesc = "Workflow initiated through " + string ( pcArgv[0] ) + " utility, to close ECR Revisions.";

            GET_EPMJobUnqPtr processInstance = GET_EPMJob::createEPMProcess ( SUBMIT_TO_CLOSE_CHANGE_WORKFLOW, sProcessName, sProcessDesc, vECRToBeReleased, EPM_target_attachment );
        }
        else
        {
            cout<<endl<<"No ECRs found for closure"<<endl;
        }
    }
    catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        sErrorMessage = ex.getMessage();
        LOG_ERROR ( logger, sErrorMessage );
    }
    catch ( GET_Exception *ex )
    {
        iFail = GET_GENERAL_EXCEPTION;
        sErrorMessage = ex->getErrorMessage();
        LOG_ERROR ( logger, sErrorMessage );
        delete ex;
    }
    catch ( ... )
    {
        sErrorMessage =  string ( pcArgv[0] ) + " failed due to an unexpected error. Please Contact your system administrator";
        LOG_ERROR ( logger, sErrorMessage );
        iFail = GET_GENERAL_EXCEPTION;
    }

    if ( ! sErrorMessage.empty() )
    {
        string sEmailId = "";

        cout<<endl<<sErrorMessage.c_str()<<endl;
        GET_PersonUnqPtr personPtr = GET_Person::find ( "infodba" );
		sEmailId = personPtr->getEmailId();
		if ( ! sEmailId.empty() && sEmailId.find ( "@" ) != string::npos && sEmailId.find ( ".com" ) != string::npos )
        {
             vEmailIDs.push_back ( sEmailId );
		}	
        if ( personPtr.get() == NULL )
        {
            cout<<endl<<"Unable to find the Teamcenter infodba person object"<<endl;
        }
        else
        {
            string sBodyContent = "<html>The execution of " + string ( pcArgv[0] ) + " failed with the below error message.<br/><br/>" + sErrorMessage + "<br/><br/>Please check the logs and take necessary action.</html>";
            sendMailAsHtml ( vEmailIDs, string ( "Error executing " ) + pcArgv[0], sBodyContent );
        }
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
//      Who                           Date                 Description
//  Capgemini Development Team     25 May, 2017         Initial creation
//  TechM Development Team         23 Aug, 2017         Updated display usage
//
===========================================================================
//ENDFUNCDOC   ***/
static void displayUsage()
{
    cout<<"Usage is: get_automatic_ecr_close [-h] [-u=<userid> -p=<password> -g=<group>] "<<endl;
    cout<<"       -h               displays detailed help information"<<endl;
    cout<<"       -u               userid"<<endl;
    cout<<"       -p               password"<<endl;
    cout<<"       -g               group"<<endl;
}
