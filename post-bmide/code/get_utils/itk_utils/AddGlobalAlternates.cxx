/***************************************************************************************
 * File Name		:	Add_Global_Alternate.cpp
 * 
 * Description		:	This utility adds Global Alternatives to the Service Part.
 *						It generates a report file and a log file.						
 *                      TC Version : 11.2
 *   
 * Author			:	Nisarg Shah (Capgemini India)
 * 
 * Creation Date   	:   Oct 2017
 **************************************************************************************/
 
#include <tcinit/tcinit.h>
#include <tccore/item.h>
#include <fclasses/tc_string.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <constants/constants.h>
#include <tc/tc_util.h>
#include <iostream>
#include <stdexcept>
#include <map>
#include <base_utils/IFail.hxx>

// GET Includes

#include <GET_Utils.hxx>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>

/* main function */
using namespace std;
int main( int argc , char* argv[] )
{
	char part_number[128];
	char alt_part_number[128];
	const char *attribute_name[1];
	const char *attribute_value[1];
	string file_text, user_name, password, user_group, input_file;
	string logger = "get.add_global_alternate";
	std::stringstream ss;
	int ret_code			=   ITK_ok;	
	int tkn_count			=	0;
	int n_items;
	int iPos                =   -1;
	int iFail = ITK_ok;
	tag_t *item_tags 		= NULLTAG;
	tag_t item_tag 			= NULLTAG;
	time_t curr_time; //current time stamp
	map<string, string> progArgs;
	FILE* tclog_file;
	FILE* alt_report_file;
	
	try
	{
		/* Command Line Arguments */
		printf("\nReading command line arguments.");
		
		GET_convertToMap ( argc, ( const char** ) argv, progArgs );

        if ( progArgs.find ( "-h" ) != progArgs.end() || progArgs.find ( "-help" ) != progArgs.end() )
        {
            printf("\nAll below four command line arguments are required.\nUsage:\nAddGlobalAlternates -u=<username> -p=<password> -g=<user group> -i=<input file> \n");
            return 0;
        }

		user_name  = progArgs["-u"];
		password   = progArgs["-p"];
		user_group = progArgs["-g"];
		input_file = progArgs["-i"];
		
		/* Checking the arguments */
		if( user_name.length() == 0 || password.length() == 0 || user_group.length() == 0 || input_file.length() == 0)
		{
			printf ("\nAll below four command line arguments are required.\nUsage:\nAddGlobalAlternates -u=<username> -p=<password> -g=<user group> -i=<input file> \n");
			return 0;
		}
		
		/* TC_LOG file */
		tclog_file = fopen("LOG_custom_utility_run.log", "w");
		if (!tclog_file)	
		{
			printf ("\nERROR: Cannot open LOG_custom_utility_run.log file");
			return 0;
		}
		/* Time Stamp */
		curr_time=time(NULL);  
		fprintf(tclog_file,"---------------------------------------------------------------------\nUtility Execution Start Time=%s---------------------------------------------------------------------\n",asctime(localtime(&curr_time)));
		fflush(tclog_file);
		
		/* Alternate Part Update Report file */
		alt_report_file = fopen("Logs/4_LOG_Alternate_Parts_Reoprt.log", "w");
		if (!alt_report_file)	
		{
			THROW ("\nERROR: Cannot open Logs/4_LOG_Alternate_Parts_Reoprt.log file\nPlease make sure there is a \"Logs\" directory present.");
		}	
		fprintf(alt_report_file,"PART_NUMBER|ALTERNATE_PART_NUMBER|STATUS|COMMENTS");
		fflush(alt_report_file);	
		
		/* Login to Teamcenter */
		ret_code = ITK_init_module(user_name.c_str(),password.c_str(),user_group.c_str());
		if(ret_code != ITK_ok)
		{
			ss << "\nLogin to Teamcenter Failed.\nError: " << ret_code << ", Line: " << __LINE__;
			fprintf(tclog_file,"%s",ss.str());
			fflush(tclog_file);			
			THROW (ss.str());
		}
		cout << "\nSuccessfully logged into Teamcenter.";
		fprintf(tclog_file, "\nSuccessfully logged into Teamcenter.");
		fflush(tclog_file);
		/* Time Stamp */
		curr_time=time(NULL);  
		fprintf(tclog_file,"\nLogin time=%s",asctime(localtime(&curr_time)));
		fflush(tclog_file);			

		/* Setting Bypass */
		ret_code = ITK_set_bypass (true);
		if(ret_code  != ITK_ok)
		{
			ss << "\nError while setting bypass: " << ret_code << ", Line: " << __LINE__;		
			THROW (ss.str());
		}
		ret_code = POM_set_env_info (POM_bypass_access_check, true, 0, 0.0, NULLTAG, "" );
		if(ret_code  != ITK_ok)
		{
			ss << "\nError while setting Environment: " << ret_code << ", Line: " << __LINE__;		
			THROW (ss.str());
		}
		cout << "\nSet Bypass successfully.";
		fprintf(tclog_file,"\nSet Bypass successfully.");
		fflush(tclog_file);
		

		//Criteria to serach for alternate part
		attribute_name[0]="item_id";

		/*Opening and Reading Input file line by line*/
		{	
			//Opening the file
			ifstream file(input_file);
			if (!file.is_open())
			{
				ss << "\nError while opening input file : " << input_file << ". Please check.";		
				THROW (ss.str());
			}
				
			//reading each line
			while (getline(file, file_text))
			{
				tkn_count=0;
				
				if (file_text.find("|") != string::npos) 
				{
					cout << "\n**************************************************************************\n";
					fprintf(tclog_file,"\n**************************************************************************\n");
					fflush(tclog_file);
					istringstream iss(file_text);
					string token;
					
					while (getline(iss, token, '|'))
					{
						if(tkn_count == 0)
						{
							strcpy(part_number, token.c_str());
							cout << "\npart_number=" << part_number;
							fprintf(tclog_file,"part_number=%s",part_number);
							fflush(tclog_file);
						}
						if(tkn_count == 1)
						{
							tc_strcpy(alt_part_number, token.c_str());
							cout << "\nalt_part_number=" << alt_part_number;
							fprintf(tclog_file,"\nalt_part_number=%s",alt_part_number);
							fflush(tclog_file);
						}					
						tkn_count++;
					}
					
					//Searching the Item
					ret_code=ITEM_find_item (part_number, &item_tag);
					if(ret_code!=ITK_ok)
					{
						cout << "\nError " << ret_code << " occured while searching for Service Part : " << part_number << ".";
						fprintf(tclog_file,"\nError %d occured while searching for Service Part : %s.",ret_code,part_number);
						fflush(tclog_file);
						fprintf(alt_report_file,"\n%s|%s|Failure|Error %d occured while searching for Service Part",part_number,alt_part_number,ret_code);
						fflush(alt_report_file);
						//READ NEXT_LINE
					}
					else
					{
						if( item_tag != NULLTAG )
						{
							/* Alternate Part Number addition */
							if(tc_strlen(alt_part_number) != 0)
							{
								//Searching the Alternate Part
								attribute_value[0] = alt_part_number;
								ret_code = ITEM_find_items_by_key_attributes(1,attribute_name,attribute_value,&n_items,&item_tags);
								if(ret_code!=ITK_ok)
								{
									fprintf(alt_report_file,"\n%s|%s|Failure|Error %d occured while searching for Alternate Part",part_number,alt_part_number,ret_code);
									fflush(alt_report_file);								
									cout << "\nError " << ret_code << " occured while searching for Alternate Part : " << alt_part_number << ".";
									fprintf(tclog_file,"\nError %d occured while searching for Alternate Part : %s.",ret_code,alt_part_number);
									fflush(tclog_file);	
								}
								else
								{
									if(n_items == 0)
									{
										cout << "\nAlternate Part - No Item found with ItemId = \"" << alt_part_number << "\"";
										fprintf(tclog_file,"\nAlternate Part - No Item found with ItemId = \"%s\"" , alt_part_number);
										fflush(tclog_file);
										fprintf(alt_report_file,"\n%s|%s|Failure|AlternatePart_Not_Found",part_number,alt_part_number);
										fflush(alt_report_file);
									}
									else
									{
										ret_code = ITEM_add_related_global_alternates(item_tag,1,item_tags); //Adding the Alternate Part
										if(ret_code!=ITK_ok)
										{
											cout << "\nError " << ret_code << " occured while adding Alternate Part " << alt_part_number << " to the Service Part : " << part_number <<".";
											fprintf(tclog_file,"\nError %d occured while adding Alternate Part %s to the Service Part : %s.",ret_code,alt_part_number,part_number);
											fflush(tclog_file);	
		
											if(ret_code == 48107)
											{
												//48107 = #define ITEM_duplicate_global_alternate         (EMH_ITEM_error_base + 107)
												cout << "\nPart " << alt_part_number << " is already a Global Alternate for Service Part " << part_number;
												fprintf(tclog_file,"\nPart %s is already a Global Alternate for Service Part %s",alt_part_number,part_number);
												fflush(tclog_file);	
												fprintf(alt_report_file,"\n%s|%s|Failure|Exists_As_An_Alternate_Part",part_number,alt_part_number);
												fflush(alt_report_file);												
											}
											else if(ret_code == 32017)
											{
												//32017 = #define RES_UNABLE_TO_SAVE                      RES_ERROR_BASE + 17
												cout << "\nUnable to Save " << part_number << " Part.";
												fprintf(tclog_file,"\nUnable to Save %s Part.",part_number);
												fflush(tclog_file);	
												fprintf(alt_report_file,"\n%s|%s|Failure|Unable_To_Save_The_Part",part_number,alt_part_number);
												fflush(alt_report_file);												
											}										
											else
											{
												fprintf(alt_report_file,"\n%s|%s|Failure|Error %d occured while adding Alternate Part",part_number,alt_part_number,ret_code);
												fflush(alt_report_file);											
											}
										}
										else
										{
											cout << "\n" << alt_part_number << " is added to " << part_number << " as a Global Alternate Part.";
											fprintf(tclog_file,"\n%s is added to %s as a Global Alternate Part.",alt_part_number,part_number);
											fflush(tclog_file);		
											fprintf(alt_report_file,"\n%s|%s|Success|AlternatePart_Added",part_number,alt_part_number);
											fflush(alt_report_file);
										}
									}
								}
							}
						}
						else
						{
							cout << "\nNo Item found with ItemId = \"" << part_number <<"\"";
							fprintf(tclog_file,"\nNo Item found with ItemId = \"%s\"" , part_number);
							fflush(tclog_file);
							fprintf(alt_report_file,"\n%s|%s|Failure|Primary_Item_Not_Found",part_number,alt_part_number);
							fflush(alt_report_file);						
							//Next line will be read
						}
					}
				} //End of if - for checking '|' symbol
			} //End of while loop - for reading lines from input file
			file.close();
		}	

				/* Time Stamp */
				curr_time=time(NULL);  
				fprintf(tclog_file,"\n---------------------------------------------------------------------\nUtility Execution End Time=%s---------------------------------------------------------------------",asctime(localtime(&curr_time)));
				fflush(tclog_file);
	}
  catch ( const IFail &ex )
    {
        iFail = ex.ifail();
        cout<<endl<<ex.getMessage().c_str()<<endl;
		fprintf(tclog_file,ex.getMessage().c_str());
		fflush(tclog_file);
    }
	catch ( GET_Exception *ex )
    {
        iFail = GET_GENERAL_EXCEPTION;
        cout<<endl<<ex->getErrorMessage().c_str()<<endl;
		fprintf(tclog_file,ex->getErrorMessage().c_str());
		fflush(tclog_file);
        delete ex;
    }
	catch ( ... )
    {
        string sMessage =  string ( argv[0] ) + " failed due to an unexpected error. Please Contact your system administrator";
        iFail = GET_GENERAL_EXCEPTION;
        cout<<endl<<sMessage.c_str()<<endl;
		fprintf(tclog_file,sMessage.c_str());
		fflush(tclog_file);		
    }
	ITK_ERROR:
		//Cleanup 
		if(tclog_file != NULL)
		{
			fclose(tclog_file);
		}
		if(alt_report_file != NULL)
		{
			fclose(alt_report_file);
		}
		MEM_free(item_tags);		
	return 0;
}
