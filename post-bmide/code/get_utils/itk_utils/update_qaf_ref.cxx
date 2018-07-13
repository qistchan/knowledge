/*=============================================================================
                Copyright (c) 
===============================================================================
File description:

    Filename: update_qaf_ref.c
    Module  : main

        This program contains all the functions that are used for finding
        the Item Revisions, whose dataset(UGMASTER) or Bom View Revision
        have been modified since the specified date.

    USAGE :  update_qaf_ref [-u=<user_id> -p=<password> [-g=<group>]]
                                          -start_date=<DD-MMM-YYYY HH:MM:SS>
                                          [-end_date=<DD-MMM-YYYY HH:MM:SS>]
                                          [-obj_type=<Object type>]
                                          [-out_file=<output_filename>]
                                          [-h]
 */
/****************************************************************************/
/*                      I N C L U D E   F I L E S                           */
/****************************************************************************/
#include <stdio.h>  
#include <string.h>
#include <tc/tc.h>
#include <tc/folder.h>
#include <ict/ict_userservice.h>
#include <tccore/item.h>
#include <tc/tc_util.h>
#include <fclasses/tc_string.h>
#include <ae/dataset.h>
#include <tccore/aom.h>
#include <sa/tcfile_cache.h>
#include <tccore/custom.h>
#include <sa/tcfile.h>
#include <tc/emh.h>
#include <ae/ae.h>
#include <ss/ss_errors.h>
#include <tccore/tctype.h>
#include <stdarg.h>
#include <sa/tcvolume.h>
#include <res/res_itk.h>

#ifdef UNX
#elif linux
#elif __linux__
#elif WIN32
    #include <windows.system.h>
#elif WIN64
    #include <windows.system.h>
#elif WINNT
    #include <windows.system.h>
#endif


#define LOGOUT_AND_RETURN() { ITK_exit_module(true); return EXIT_FAILURE; }
#define IFERR_REPORT(X) (report_error( __FILE__, __LINE__, #X, X, FALSE))
#define IFERR_RETURN(X) if (IFERR_REPORT(X)) return
#define IFERR_RETURN_IT(X) if (IFERR_REPORT(X)) return X
/*****************************************************************************
FUNCTION PROTOTYPES
*****************************************************************************/
static void ECHO(char *format, ...)
{
    char msg[1000];
    va_list args;
    va_start(args, format);
    vsprintf(msg, format, args);
    va_end(args);
    printf(msg);
    TC_write_syslog(msg);
}
static void display_help( void );
static logical validate_arguments_name( int argc, char* argv[] );
static int report_error(char *file, int line, char *call, int status, logical exit_on_error);
static void ask_imanfile_path(tag_t fileTag, char *path);

/****************************************************************************/
/*                                                                          */
/*  Function Name:   ITK_user_main                                          */
/*                                                                          */
/*  Program ID:      update_qaf_ref.c                */
/*                                                                          */
/*  Description:     This is the main function which calls all the other    */
/*                   functions.                                             */
/*                                                                          */
/*  Parameters:      char*  argv[] <I>  - Command Line Arguments            */
/*                   int    argc   <I>  - No of command line arguments.     */
/*                                                                          */
/*  Return Value:    EXIT_SUCCESS on Success                                */
/*                   EXIT_FAILURE on failure                                */
/*                                                                          */
/*  Special Logic Notes:  None                                              */
/*                                                                          */
/****************************************************************************/
int main( int argc , char* argv[] )
{
	int       retcode               = ITK_ok;
	char	  *input_file			= NULL;
	char	  line[256];
	FILE      *ifp;
	char	  *ds_name				= NULL;
	char	  *old_file_name		= NULL;
	char	  *new_file_path		= NULL;
	char	  *orig_file_name       = NULL;
	int		  nDataset				= 0;
	tag_t     ds_tag				= 0;
	tag_t     item_tag				= 0;
	int       ds_nr_count			= 0;
	int       index					= 0;
	char      dataset_name[WSO_name_size_c+1];
	char	  ref_name[AE_reference_size_c + 1];
	tag_t     ref_tag				= 0;
	tag_t	  *ref_obj				= 0;
	AE_reference_type_t     ref_type;
	IMF_file_data_p_t		file_data;
	tag_t	  new_file_tag			= NULLTAG;
	logical	  isQafValid			= FALSE;
	logical   isQafExist			= FALSE;
	logical	  isCheckedOut			= FALSE;
	char	  *pos;
	char	  *msg;
	IMF_file_t file_descriptor;
	char  pathname[SS_MAXPATHLEN];
	(void)argc;
    (void)argv;

    ITK_init_from_cpp ( argc, argv );
	/* Display help if user asked for it */
    if ( ITK_ask_cli_argument("-h") )
    {
        display_help();
        return EXIT_FAILURE;
    }

	//validating the arguments names specified through command line
    //If any of the argumnent name is invalid then user can not proceed
    if ( validate_arguments_name( argc , argv ) == false)
    {
        display_help();
        return EXIT_FAILURE;
    }

	/* Get the dataset name */
    input_file = ITK_ask_cli_argument( "-in_file=" );
	if ( ( input_file == NULL ) || ( strlen ( input_file ) == 0 ) )
    {
        ECHO( "\nError : in_file argument is missing\n");
		display_help();
		return EXIT_FAILURE;
    }

	/* login to Teamcenter */
	ECHO( "\nLogin to Teamcenter ...\n ");
	retcode = ITK_auto_login ();
    if ( retcode != ITK_ok )
    {
        ECHO( "Failed to login to Teamcenter using auto-login with ");
        ECHO(  "error code %d\n\n", retcode);
        return EXIT_FAILURE;
    }
	ECHO( "Login to Teamcenter successfull\n");

	ifp = TC_fopen(input_file,"r");
	while(TC_fgets(line, sizeof(line), ifp))
	{
		ECHO( "\n\nProcessing the line %s ...\n", line);
		ds_name = strtok(line,",");
		new_file_path = strtok(NULL, ",");

		if ((pos=strchr(new_file_path, '\n')) != NULL)
			*pos = '\0';
		/* find the dataset tag */
		retcode = AE_find_dataset2(ds_name, &ds_tag);
		if ( (retcode != ITK_ok) ||  (ds_tag == NULLTAG))
		{
			ECHO( "\nError: Unable to find datasets with name %s\n", ds_name);
			break;
		}
		ECHO( "dataset found with the name %s\n", ds_name);


		AOM_refresh(ds_tag, TRUE);
		//WSOM_ask_name(ds_tag, dataset_name);
		//ECHO( "dataset_name is  %s\n", dataset_name);

	
		/* Get the dataset named reference count */
		retcode = AE_ask_dataset_ref_count(ds_tag, &ds_nr_count);
		if (retcode != ITK_ok) 
		{
			ECHO( "\nError: Unable to get named reference count for %s\n", ds_name);
			return EXIT_FAILURE;
		}
		if (ds_nr_count == 0 )
		{
			ECHO( "No named reference for %s", ds_name);
		}
		else
		{
			isQafExist = FALSE;
			//ECHO( "named reference count for %s is %d\n", ds_name, ds_nr_count);
			for ( index = 0; index < ds_nr_count; index++)
			{
				AE_find_dataset_named_ref(ds_tag, index, ref_name, &ref_type, &ref_tag);
				//ECHO( "named reference name is %s\n", ref_name);
				IMF_ask_original_file_name2(ref_tag,&orig_file_name);
				//ECHO( "original file name is %s\n", orig_file_name);
				if ((strcmp(ref_name, "UG-QuickAccess-Binary")==0) && (strcmp(orig_file_name, "qafmetadata.qaf")==0))
				{		
					isQafExist = TRUE;
					/*RES_is_checked_out(ref_tag, &isCheckedOut);
					if(!isCheckedOut)
					{
						retcode = RES_cancel_checkout(ref_tag, FALSE);
						EMH_get_error_string( NULLTAG , retcode , &msg );
						ECHO( "Error with RES_cancel_checkout: %s\n", msg );
					}*/
					//delete the named reference
					AOM_lock(ds_tag);
					ECHO( "removing the named reference file %s with type %s \n", orig_file_name, ref_name );
					retcode = AE_remove_dataset_named_ref_by_tag(ds_tag, ref_name, ref_tag);
					if ( retcode != ITK_ok )
					{
						EMH_get_error_string( NULLTAG , retcode , &msg );
						ECHO( "Error with AE_remove_dataset_named_ref_by_tag: %s\n", msg );
					}
					AE_save_myself(ds_tag);
					AOM_unlock(ds_tag);
					AOM_lock_for_delete(ref_tag);
					AOM_delete(ref_tag);
				}
				isQafValid = FALSE;
				if ((strcmp(ref_name, "UG-QuickAccess-Text")==0) && (strcmp(orig_file_name, "qafmetadata.qaf")==0))
				{	
					ECHO( "qafmetdata is already with correct reference type %s \n", ref_name );
					isQafExist = TRUE;
					isQafValid = TRUE;
				}
			
			}
			if (!isQafValid || !isQafExist)
			{
				retcode = AOM_refresh(ds_tag, TRUE);

				ECHO( "importing the named reference file %s with type UG-QuickAccess-Text \n", new_file_path );
				retcode = AE_import_named_ref(ds_tag, "UG-QuickAccess-Text", new_file_path, NULL,  SS_TEXT);
				if ( retcode != ITK_ok )
				{
					EMH_get_error_string( NULLTAG , retcode , &msg );
					ECHO( "Error with AE_import_named_ref: %s\n", msg );
				}

				AE_save_myself(ds_tag);
				AOM_refresh(ds_tag, FALSE);
				AOM_unlock(ds_tag);
			}

		}
	}
	fclose ( ifp );
	retcode =  ITK_exit_module(true);
	return ITK_ok;
}

/****************************************************************************/
/*                                                                          */
/*  Function Name:   display_help                                           */
/*                                                                          */
/*  Program ID:      update_qaf_ref.c                */
/*                                                                          */
/*  Description:     This function displays the help on this utility to the */
/*                   standard output.                                       */
/*                                                                          */
/*  Return Value:    None                                                   */
/*                                                                          */
/*  Special Logic Notes:  None                                              */
/*                                                                          */
/****************************************************************************/
static void display_help( void )
{
	ECHO( "\n" );
    ECHO( "\nUsage:\n\n" );
    ECHO( "update_qaf_ref \n\t[-u=<user_id>] [{-p=<password> | -pf=<password file>}]\n" );
    ECHO( "\t[-g=<group>] -in_file=<input file name>\n" );
    ECHO( "\t[-h]\n" );

    ECHO( "\nWhere:\n\n" );
    ECHO( "  -u          - Teamcenter user ID. If -u= is used without\n");
    ECHO( "                providing the <user_id> value, then\n");
    ECHO( "                operating system username is used as\n");
    ECHO( "                the user ID\n\n");

    ECHO( "  -p          - Teamcenter password associated with the\n");
    ECHO( "                -u=<user_id>. This is optional. If\n");
    ECHO( "                -p= is used without providing the\n");
    ECHO( "                <password> value, then a NULL value\n");
    ECHO( "                is used as password. If this is not\n");
    ECHO( "                specified, then the <user_id> value\n");
    ECHO( "                is used as password\n\n");

    ECHO( "  -pf         - Teamcenter password in file.\n\n");
    ECHO( "  -g          - Teamcenter group associated with the \n");
    ECHO( "                <user_id>. If this option is not\n");
    ECHO( "                specified, then the default Teamcenter\n");
    ECHO( "                group is used as user group\n\n");

    ECHO( "  -in_file    - The path of the input file containing \n" );
    ECHO( "                dataset name and path of the named \n" );
	ECHO( "                reference file to import. Each line \n"); 
	ECHO( "                of the file should be in format \n");
	ECHO( "                <dataset name>,<path of the file> \n" );
	ECHO( "                example: Y2K111555P1-0,C:\\temp\\qafmetadata.qaf \n \n");

    ECHO( "  -h          - Displays help\n\n" );
}

static logical validate_arguments_name( int argc, char* argv[] )
{
    int index = 0;
    char  arg_name[255];
    char* arg_value;
    int arg_name_length;
    logical is_arg_valid = false;
    int index1 = 0;
    char* valid_arg_list[] = { "-u", "-p", "-pf", "-g", "-in_file"};
    int valid_args = sizeof(valid_arg_list) / sizeof(char*);
    logical is_all_arg_valid = true;

    //comparing the passed argument to the valild argument supported by the utility
    //we are skipping the first argument because it is name of the executable
    for ( index = 1; index < argc; index++ )
    {
        is_arg_valid = false;
        arg_name_length = 0;
        //argument will in form of -argname=value ex. -u=infodba
        arg_value = strchr( argv [ index ], '=');

        
        if ( arg_value != NULL )
        {
            arg_name_length = tc_strlen( argv [ index ] ) - tc_strlen( arg_value );
        }
        //if argument do not contains '=' then it is the invalid argument
        //if the argument name length is larger than 254 then also it is invalid 
        if ( arg_name_length >= 255 || arg_value == NULL)
        {
            is_all_arg_valid = false;
            ECHO( "\nError : The argument <%s> specified through command line is not recognized.\n", argv[index] );
            continue;
        }
        //getting the name of argument example in "-u=infodba" in this argument name will be "-u"
        tc_strncpy( arg_name, argv[index], arg_name_length );
        arg_name[arg_name_length] = '\0';
        
        //comparing the argument name to the valid argument name supported by this utility
        for ( index1 = 0; index1 < valid_args; index1++ )
        {
            if ( tc_strcasecmp ( valid_arg_list[index1], arg_name) == 0 )
            {
                is_arg_valid = true;
                break;
            }
        }
        //if argument is invalid giving error to user
        if ( is_arg_valid == false )
        {
            is_all_arg_valid = false;
            ECHO( "\nError : The argument <%s> specified through command line is not recognized.\n", argv[index] );
        }
    }

    return is_all_arg_valid;
}

static void ask_imanfile_path(tag_t fileTag, char *path)
{
    int
        machine_type;
    tag_t
        volume;

    IFERR_RETURN(IMF_ask_volume(fileTag, &volume));
    IFERR_RETURN(VM_ask_machine_type(volume, &machine_type));
    IFERR_RETURN(IMF_ask_file_pathname(fileTag, machine_type, path));
}

static int report_error(char *file, int line, char *call, int status, logical exit_on_error)
{
    if (status != ITK_ok)
    {
        int
            n_errors = 0,
            *severities = NULL,
            *statuses = NULL;
        char
            **messages;

        EMH_ask_errors(&n_errors, (const int **)&severities, (const int **)&statuses, (const char ***)&messages);
        if (n_errors > 0)
        {
            ECHO("\n%s\n", messages[n_errors-1]);
            EMH_clear_errors();
        }
        else
        {
            char *error_message_string;
            EMH_get_error_string (NULLTAG, status, &error_message_string);
            ECHO("\n%s\n", error_message_string);
        }

        ECHO("error %d at line %d in %s\n", status, line, file);
        ECHO("%s\n", call);

        if (exit_on_error)
        {
            ECHO("Exiting program!\n");
            exit (status);
        }
    }

    return status;
}
