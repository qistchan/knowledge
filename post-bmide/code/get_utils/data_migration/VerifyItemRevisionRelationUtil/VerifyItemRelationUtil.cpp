
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   VerifyItemRelationUtil.cpp
//
//   Purpose :   To verify whether the particular relation exist or not.
//
//   History :
//      Who                             Date                 Description
//   TCS Data migration team         9 Sep, 2016           Initial creation
//   ============================================================================
// ENDFILEDOC   ***/

#include <tccore/item.h>
#include <tcinit/tcinit.h>
#include <tccore/grm.h>
#include <epm/epm_task_template_itk.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void displayUsageMessage()

{
    cout<<"******************************************************************\n";

    cout<<"Usage-1:\nTo Verify the item revision Relation\n";
    cout<<"\ncreateUtility.exe -u=<user id> -p=<password> [-g=<group>] -input_file=<input File> -output_file=<output File> -relation=<Name of the relation>";
    cout<<"\n\nInput file format\n";
    cout<<"\n<Item ID>\n";
}

int main( int argc, char *argv[] )
{
    int iFail = ITK_ok;

    char * szUserid            = NULL;
    char * szUserPwd           = NULL;
    char * szUserGroup         = NULL;
    char * szRelation          = NULL;
    char * szInputFile         = NULL;
    char * szOutputFile        = NULL;
    char *  text               = NULL;
    string input_line          = "";

    ifstream input_file;
    ofstream output_file;

    vector<string> inputVector;
    inputVector.clear();

    /*Ask help argument*/
    if(ITK_ask_cli_argument ("-h") != NULL)
    {
        displayUsageMessage();
        return (ITK_ok);
    }

    /*Initialize Teamcenter Environment*/
    ITK_init_from_cpp(argc, argv);
    ITK_initialize_text_services(0);

    /*Get user arguments*/
    szUserid    = ITK_ask_cli_argument("-u=");

    szUserPwd   = ITK_ask_cli_argument("-p=");

    szUserGroup = ITK_ask_cli_argument("-g=");

    szRelation  = ITK_ask_cli_argument("-relation=");

    /*Login to Teamcenter*/
    if ((strcmp(szUserid,"")!=0) && (strcmp(szUserPwd,"")!=0)  && (strcmp(szUserGroup,"")!=0) )
    {
        iFail = ITK_init_module( szUserid,szUserPwd,szUserGroup );

        if(iFail== ITK_ok)
        {
            cout<<"Successfully Logged into Teamcenter"<<endl;
        }
        else
        {
            EMH_ask_error_text(iFail, &text);
            cout<<"Not able to login into Teamcenter with error code "<<iFail<<"Message:"<<text<<endl;
            MEM_free(text);
            return iFail;
        }

        /*Set bypass if dba logged in*/
        if(strcmp(szUserGroup,"dba")==0)

        iFail = ITK_set_bypass(true);

        if(iFail!= ITK_ok)
        {
            EMH_ask_error_text(iFail, &text);
            cout<<"Set ByPass failed with Error code: "<<iFail<<"Message:"<<text<<endl;
            MEM_free(text);
            return iFail;
        }
        else
        {
            cout<<"Set ByPass is ON - dba login"<<endl;
        }
    }
    else
    {
        cout<<"Not able to login into Teamcenter"<<endl;
        return iFail;
    }

    /*Get RelationType Tag*/
     tag_t  itemRelationType = NULLTAG;
    if(iFail == ITK_ok)
    {
        iFail = GRM_find_relation_type (szRelation, &itemRelationType);

        if (itemRelationType == NULL)
        {
            cout<<"Relation search failed, Check the Relation name entered "<<iFail<<endl;
            return 0;
        }
        else if(itemRelationType != NULL)
        {
            cout<<"Relation search Successful"<<endl;
        }
    }
    if(iFail== ITK_ok)
    {
        /*Get the input File*/
        szInputFile = ITK_ask_cli_argument("-input_file=");
        if(szInputFile == NULL)
        {
            cout<<"ERROR: Please enter an input file name and path"<<endl;
            displayUsageMessage();
            return(ITK_ok);
        }

        /*Get the output File*/
        szOutputFile = ITK_ask_cli_argument("-output_file=");
        if(szOutputFile == NULL)
        {
            cout<<"ERROR: Please enter an output file Path"<<endl;
            displayUsageMessage();
            return(ITK_ok);
        }
    }

        /*Read input file*/
        input_file.open(szInputFile);
        bool endOfFile                                = false;
        if(input_file==NULL)
        {
            cout<<"ERROR: Cannot open input file"<<endl;
            return(ITK_ok);
        }
        while (!endOfFile)
        {
            if ( getline( input_file, input_line ).eof() )
            {
            endOfFile = true;
            }
            inputVector.push_back(input_line);
        }
        cout<<"Total no of vector elements"<<(inputVector.size() -1)<<endl;
        input_file.close();

    if(inputVector.size() > 0)
    {
        /*Open output file*/
        output_file.open(szOutputFile);
        if(output_file!= NULL)
        {
            cout<<"********************Output****************"<<endl;
        }

        int iSearchCount            = 0;
        int itemRelationCount       = 0;
        tag_t * ptItemAttachments   = NULL;
        tag_t tOutTag              = NULLTAG;
        tag_t tItemRev              = NULLTAG;

        for(size_t i = 0; i < (inputVector.size() -1);  i++)
        {
            if(i == 0)
            {
                cout<<"****************Start of Item Search**************************"<<endl;
            }
            else if(i ==  inputVector.size()  )
            {
                cout<<"The vector count is :"<<inputVector.size()<<endl;
            }

            /*Find the item */
            iFail = ITEM_find_item(inputVector[i].c_str(), &tOutTag);
            if(tOutTag == NULLTAG)
            {
                cout<<"Item not found, search failed "<<iFail<<endl;
                cout<<"ItemID "<<inputVector[i].c_str()<<endl;
                output_file<<inputVector[i].c_str()<<";Not Found in Teamcenter"<<endl;

                continue;
            }
            else if(tOutTag != NULL)
            {
                cout<<"Item search Successful"<<endl;
            }

            /*Ask latest Item revision */
            if(tOutTag !=NULL && iFail == ITK_ok)
            {
                iFail = ITEM_ask_latest_rev(tOutTag, &tItemRev);

                if(iFail != ITK_ok)
                {
                    cout<< "ItemRevision search failed "<<iFail<<endl;
                }
                else if(tItemRev != NULL)
                {
                    cout<< "ItemRevision search Successful"<<endl;
                }
            }

            iFail = GRM_list_secondary_objects_only(tItemRev, itemRelationType, &itemRelationCount, &ptItemAttachments);

            if(iFail != ITK_ok)
            {
                cout<<"secondary objects_only search failed"<< iFail<<endl;
            }
            else
            {
                cout<<"secondary objects list with "<<szRelation<<" relation Exist"<<endl;
            }

            if(itemRelationCount > 0)
            {
                output_file<<inputVector[i].c_str()<<";Yes\n";
            }
            else
            {
                output_file<<inputVector[i].c_str()<<";No\n";
            }
        }
    }
    output_file.close();
}