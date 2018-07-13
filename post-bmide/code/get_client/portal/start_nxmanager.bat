@echo off
rem
rem File Name:  START_NXMANAGER.BAT
rem 
rem ************************************************************************
rem
rem This script will set the appropriate variables and then run NX/Manager
rem without workspace.
rem
rem Copyright (c) 1995-1999
rem Unigraphics Solutions, Cypress, CA 90630
rem All Rights Reserved
rem
rem Input Parameters:
rem
rem Command line parameters will be passed through to Unigraphics.
rem
rem NOTE: You MUST use a colon "" for key=value pairs
rem       N-tier argument should always be at last.
rem       For example:
rem       start_nxmanager test.bkm -opts "-u=tom" "-p=tom" n-tier
rem
rem ************************************************************************
rem Revision History:
rem
rem REV   AUTHOR      DATE      COMMENT
rem ===   ======      =======   =======
rem 31-Jul-2001  rupert                  Add UGII_BASE_DIR
rem 01-Oct-2001  brownch                 Fixed PR4338228.
rem 16-Dec-2005  yang                    4-tier NX Manager
rem 08-Jan-2006  Mathieu Sarrazy         Merge from CVG_P10.0.1.5
rem 10-Jan-2007  Mayur Deshpande         Changes regarding common start_nxmanager for 2T/4T
rem 20-Mar-2018  Parashuraman REV		 Modified for NX custom Apps Automatic Installer
rem $HISTORY$
rem ************************************************************************
 
rem Get the n-tier argument which is last in the argument list
set NTIER_ARG=
:setArg
 shift
 if ""%1""=="""" goto doneSetArg
 set NTIER_ARG=%1
 goto setArg
:doneSetArg

if "%NTIER_ARG%"=="2-tier" goto :2-tier
if "%NTIER_ARG%"=="4-tier" goto :4-tier
goto :ntier_error

:2-tier
rem Set the pdi corba library.
rem This expects this library to be found in UGII_LIB_PATH
set UGII_UGMGR_EXTERNAL_COMMS_LIB=pdi_corba_client
goto :common

:4-tier
rem set the communication mode
set UGII_UGMGR_COMMUNICATION=HTTP
goto :common

:common
rem set the UGII_BASE_DIR
set UGII_BASE_DIR=C:\Siemens\NX100
set UGII_ROOT_DIR=%UGII_BASE_DIR%\ugii
rem Check whether UGII_BASE_DIR is set
if NOT EXIST "%UGII_BASE_DIR%" goto :nx_error
rem
rem Disable the flash
set UGII_DISABLE_FLASH=YES
rem
rem set the UGII_UGMGR_SOA_ENABLED
set UGII_UGMGR_SOA_ENABLED=TRUE
rem
rem Figure out the startup directory
rem The order of precedence is: API_DEFAULT_DIR, HOME, TC_TMP_DIR, UGII_TMP_DIR, TEMP
rem Otherwise we might end up in trouble if the current working
rem directory we were started up from is not writable.
rem
set START_DIR=%API_DEFAULT_DIR%
if "%START_DIR%"=="" set START_DIR=%HOME%
if "%START_DIR%"=="" set START_DIR=%TC_TMP_DIR%
if "%START_DIR%"=="" set START_DIR=%UGII_TMP_DIR%
if "%START_DIR%"=="" set START_DIR=%TEMP%
rem

::***************************************************************************************************************************************************************
::Query the current TC enviornment on which NX is launching
TITLE *** NX Custom Apps version validation ***

IF "%UGII_UGMGR_HTTP_URL%" == "http://vdcgld02589.ics.cloud.ge.com:8080/tc" (
    set TC_Env=intdev
) ELSE IF "%UGII_UGMGR_HTTP_URL%" == "http://vdcgld03041.ics.cloud.ge.com:8080/tc" (
    set TC_Env=dev
) ELSE IF "%UGII_UGMGR_HTTP_URL%" == "http://alpgetsws001qp.corporate.ge.com:8080/tc" (
    set TC_Env=qa
) ELSE IF "%UGII_UGMGR_HTTP_URL%" == "https://plm.trans.ge.com/tc" (
    set TC_Env=prod
) ELSE IF "%UGII_UGMGR_HTTP_URL%" == "http://cingetsws001pp.corporate.ge.com:8080/tc" (
    set TC_Env=prod
) ELSE (
    set TC_Env=prod
)

IF "%TC_Env%" == "dev" (
	set TC_PORTAL_DIR=C:\Siemens\tranplm_tc11_%TC_Env%\portal
) ELSE (
	set TC_PORTAL_DIR=C:\Siemens\transplm_tc11_%TC_Env%\portal
)


::Copy NXclient_update.bat file to C:\temp and execute
%SystemRoot%\System32\cscript "%TC_PORTAL_DIR%\downloadNXclientUpdate.vbs"


::echo "%UGII_UGMGR_HTTP_URL%"
::echo "%TC_Env%"
::echo "%TC_PORTAL_DIR%"
echo "You are connected to Teamcenter %TC_Env% envrionment %UGII_UGMGR_HTTP_URL%"
echo "NX Client Update downloading from Installation server"
TIMEOUT /T 5

::Execute NXclient_update.bat to validate NX Custom Apps version at Client
call c:\temp\NXclient_update.bat
echo %errorlevel%
if %errorlevel%==6 goto:nx_hold 

:: *** NX Apps Selectgor ***
call "C:\Siemens\NX100_Cust_tools_%TC_Env%\TransPLM\NX_Apps_Selector.bat"

cd /d %START_DIR%

rem Start Unigraphics through the launcher program
tasklist | findstr ugraf.exe
if %ERRORLEVEL%==0 goto:MULTI_NX_SESSION
start "Teamcenter Integration for NX" /B %UGII_ROOT_DIR%\ugs_router -ugm -enable_cancel -message="Connecting to NX10 TRANS PLM Environment" -version=V28.0 %*
goto:DONE

:MULTI_NX_SESSION
%SystemRoot%\System32\cscript "C:\Siemens\NX100_Cust_tools_%TC_Env%\TransPLM\win\ug\Config\MultiNXsessionWarning.vbs"
cls
@echo.
@echo ****** Launching Additional NX session *****
@echo.
%UGII_ROOT_DIR%\ugraf.exe -pim=yes %*

:DONE
::***************************************************************************************************************************************************************

goto :ENDOFFILE

:nx_error
echo UGII_BASE_DIR must be set
pause
goto :ENDOFFILE

:ntier_error
echo Missing n-tier parameter
pause
goto :ENDOFFILE

:nx_hold
color 4F
echo .
echo **********************************************************************************************
echo ***  NOTE: NX session launch has been terminated to assist NX Custom Tool package download ***
echo **********************************************************************************************
pause
goto :ENDOFFILE

:ENDOFFILE

@echo on