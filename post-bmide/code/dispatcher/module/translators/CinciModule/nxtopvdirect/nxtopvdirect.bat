@echo off

REM # ============================================================================= #
REM   SCRIPT TO RUN NXTOPVDIRECT TRANSLATOR
REM # ============================================================================= #

REM Replace CHANGE_ME with correct values as shown in Example
REM  Set TC_ROOT To Directory where TeamCenter is installed
REM   Example set TC_ROOT=d:\Tceng0910
REM  Check if TC_DATA is valid.
set TC_ROOT=CHANGE_ME
set TC_DATA=CHANGE_ME

REM  By default the variables below will be set as environment variables when Nx is 
REM  installed. Set these values below in case the environment variables are not set.
REM
REM  Set UGII_BASE_DIR To Directory where Unigraphics is installed
REM   Example set UGII_BASE_DIR=D:\Progra~1\UGS\UNIGRA~1.0
REM  For Nx5 and above - set SPLM_LICENSE_SERVER To UG license 
REM   Example set SPLM_LICENSE_SERVER=2100@sol001
REM
set UGII_BASE_DIR=C:\Siemens\NX100
set SPLM_LICENSE_SERVER=28440@cinlic11.av.ge.com;28440@cinlic12.av.ge.com

setlocal

@set PARAM1=%1

if x%PARAM1% == x  goto help
if %1==-help goto help

goto setenv

:help
echo Usage:
echo   Using Text File
echo     nxtopvdirect.bat -nonsingle_part defaultconfig d:\temp\DBStrings.txt
echo       Where 
echo         ARG1 takes translator type
echo           -nonsingle_part - If text file with @DB strings is used.
echo         ARG2 takes tessUG.config file location.
echo           "defaultconfig" - To point to default configuration location %UGII_BASE_DIR%\PVTRANS\tessUG.config or
echo           "TessUG.config file" - Full Path to the tessUG.config file location.
echo         ARG3 takes
echo           "Text file"     - Full path to input text file with @DB strings.
echo   Using -single_part option  
echo     nxtopvdirect.bat -single_part d:\temp\TessUG.config defaultdef @DB:ITEM:REV
echo       Where 
echo         ARG1 takes translator type
echo           -single_part - For Single part option.
echo         ARG2 takes tessUG.config file location.
echo           "defaultconfig" - To point to default configuration location %UGII_BASE_DIR%\PVTRANS\tessUG.config or
echo           "TessUG.config file" - Full Path to the tessUG.config file location.
echo         ARG3 takes default file location
echo           defaultdef      - If no def file needs to be set for -single_part option. or
echo           "Def file" - Full path to the def file to be used for -single_part option.
echo         ARG4 takes
echo           @DB String - If using -single_part option.
echo   Using copy release status  
echo     nxtopvdirect.bat copyugrelstatus "-dataset_tag=gZEJMIW4xh0KTB"
echo       Where 
echo         ARG1 takes translator type
echo           copyugrelstatus - To copy release status
echo         ARG2 takes
echo           "-dataset_tag=Dataset Uid" - "-dataset_tag" takes the dataset uid.
endlocal
goto :EOF

:setenv

if "%UGII_BASE_DIR%"=="" (
 echo UGII_BASE_DIR is not set.
 EXIT 1
)

if "%SPLM_LICENSE_SERVER%"=="" (
 echo SPLM_LICENSE_SERVER is not set.
 EXIT 1
)

set UGII_ROOT_DIR=%UGII_BASE_DIR%\UGII
set UGII_PV_TRANS_MODEL_ANN=1
set UGII_GENERATE_MULTI_CAD_JT=1
set JTK_USE_MASTER_NOTATION_PMI_FORMAT=1
set JTK_XLATR_ENABLE_PERSISTED_INSTANCE_ID=1

set GETS_LOC_DIR=C:\Siemens\NX100_Cust_Tools\TransPLM
set UGII_CONFIG_FILE=%GETS_LOC_DIR%\win\ug\CustomAddOns\PVTRANS\tessUG.config
rem set UGII_CONFIG_FILE=%UGII_BASE_DIR%\PVTRANS\tessUG.config

if %2==defaultconfig goto setenv
set UGII_CONFIG_FILE=%2

:setenv

set OLDPATH=%PATH%

if "%TC_ROOT%"=="CHANGE_ME" (
 echo set TC_ROOT
 EXIT 1
)

set PATH=%UGII_ROOT_DIR%;%PATH%;

if %1==-single_part goto single_part
if %1==copyugrelstatus goto copyugrelstatus

echo ***Checking for UGII_CONFIG_FILE env setting ***
echo %UGII_CONFIG_FILE%
REM 
REM Using text file with @DB Strings
REM 
rem "%UGII_BASE_DIR%\PVTRANS\run_ugtopv.bat" -config="%UGII_CONFIG_FILE%" -noupdate "-pim=yes" %3 %4 %5 %6 %7 %8 %9
"%GETS_LOC_DIR%\win\ug\CustomAddOns\PVTRANS\run_ugtopv.bat" -config="%UGII_CONFIG_FILE%" -noupdate "-pim=yes" %3 %4 %5 %6 %7 %8 %9
goto done

REM 
REM Using single part option with individual @DB strings
REM 
:single_part
set UGII_DEFAULTS_FILE=%3
if %3==defaultdef set UGII_DEFAULTS_FILE=
set UGII_LOAD_OPTIONS=
rem "%UGII_BASE_DIR%\PVTRANS\run_ugtopv.bat" -single_part -config="%UGII_CONFIG_FILE%" -noupdate "-pim=yes" %4 %5 %6 %7 %8 %9
"%GETS_LOC_DIR%\win\ug\CustomAddOns\PVTRANS\run_ugtopv.bat" -single_part -config="%UGII_CONFIG_FILE%" -noupdate "-pim=yes" %4 %5 %6 %7 %8 %9
goto done

REM 
REM Copying latest UG release status.
REM 
:copyugrelstatus
call %TC_DATA%\tc_profilevars
"%TC_ROOT%\bin\tc_workflow_postprocess.exe" %2 %3 %4 %5 %6 %7 %8 %9
goto done

:done
set EXITVALUE=%ERRORLEVEL%

set PATH=%OLDPATH%

:end

endlocal

@echo on

EXIT %EXITVALUE%
