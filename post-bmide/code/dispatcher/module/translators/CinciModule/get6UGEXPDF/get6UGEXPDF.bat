@echo off

REM # ============================================================================= #
REM   SCRIPT TO RUN NXCLONE
REM # ============================================================================= #

REM # ============================================================================= #
REM   Check following variables
REM # ============================================================================= #

REM Teamcenter Install Root
set TC_ROOT=<CHANGE_ME>

REM Teamcenter Data dir
set TC_DATA=<CHANGE_ME>

REM FMS home
set FMS_HOME=%TC_ROOT%\tccs

REM set SPLM_LICENSE_SERVER for NX 5.0 and later
set SPLM_LICENSE_SERVER=28440@cinlic11.av.ge.com

REM Directory where NX is installed
set UGII_BASE_DIR=C:\Siemens\NX100

REM change UGII_ROOT_DIR if needed
set UGII_ROOT_DIR=%UGII_BASE_DIR%\ugii

REM change NX clone command if needed
set CLONE_COMMAND="%UGII_BASE_DIR%\UGMANAGER\ug_export"

REM set user name/password/group for dba user (if running as different OS user)
REM The user should have access to run in bypass mode
REM e.g. set TC_LOGIN_STRING=-u=infodba -p=<secret> -g=dba
set TC_LOGIN_STRING=-u=infodba -p=infodba -g=dba

REM set the ACSCLI arguments
set ACSCLI_INSTALL_DIR=<CHANGE_ME>
set ACSCLI_PDF_MODE=-generatepdf
REM value to be set below : -waituntildone time_in_minutes
set ACSCLI_TIMEOUT_ARG=
set ACSCLI_WM_MODE=-watermarkpdf
set ACSCLI_WM_SETTINGS=-font Arial -fontsize 144 -txtalign center -scale 0.5 -opacity 0.2 –txtcolor 0;0;0 -rot 45 -fixedprint true
REM DEV START
set ACSCLI_PART_RECIPE=<CHANGE_ME>
set ACSCLI_ASSY_RECIPE=-recipeId <CHANGE_ME>
set ASSY_PDF_TEMPLATE=-pdfTemplate <CHANGE_ME>
set PART_PDF_TEMPLATE=-pdfTemplate <CHANGE_ME>
set ACSCLI_OUT_DIR=<CHANGE_ME>
set ACSCLI_IMPORT_DATA=-importData <CHANGE_ME>
REM DEV END

REM QA START
REM set ACSCLI_PART_RECIPE=-recipeId faf85020-d0b1-4b80-90c0-816d04f74d8a
REM set ACSCLI_ASSY_RECIPE=-recipeId 2f5069cd-3488-4e30-ae93-10a16a0ac24a
REM set ASSY_PDF_TEMPLATE=-pdfTemplate \\eriget3d001qv.logon.ds.ge.com\Anark_Staging\PDFTemplate\GE_Transportation_Assy_Template.pdf
REM set PART_PDF_TEMPLATE=-pdfTemplate \\eriget3d001qv.logon.ds.ge.com\Anark_Staging\PDFTemplate\GE_Transportation_Part_Template.pdf
REM set ACSCLI_OUT_DIR=\\eriget3d001qv.logon.ds.ge.com\Anarak_Staging\ScratchFiles\
REM set ACSCLI_IMPORT_DATA=-importData \\eriget3d001qv.logon.ds.ge.com\Anarak_Staging\ScratchFiles\PartsList.xlsx
REM QA END

set ACSCLI_COPYTO_DIR=<CHANGE_ME>

REM set winzip arguments
set winzip_path=<CHANGE_ME>
REM set zip_output_path=\\eriget3d001qv.logon.ds.ge.com\Anarak_Staging\ScratchFiles\
set zip_output_path=<CHANGE_ME>
set zip_file_name="*.zip"

REM set 7Zip arguments
set z_path=<CHANGE_ME>
REM set zip_output_path=\\eriget3d001qv.logon.ds.ge.com\Anarak_Staging\ScratchFiles\
set zip_output_path=<CHANGE_ME>
set zip_file_name="*.zip"

REM # ============================================================================= #
REM   No user changes required below this line
REM # ============================================================================= #

REM set PL_FILE ugexport.pl in case Staging location of Anark and Dispatcher are to be different. Set to ugexport_shared_location.pl in case Staging location of Anark and Dispatcher are to be same e.g. PL_FILE=%~dp0\ugexport_shared_location.pl

set PL_FILE=%~dp0\<CHANGE_ME>
call %TC_ROOT%\bin\perl -x %PL_FILE% %*
set TC_LOGIN_STRING=

@echo on
EXIT 0
