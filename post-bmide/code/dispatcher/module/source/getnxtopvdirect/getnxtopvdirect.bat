rem @echo off
set TC_ROOT=E:\app\tc11\tcroot
set TC_DATA=E:\tc\tcdata

set UGII_BASE_DIR=C:\Siemens\NX100
set SPLM_LICENSE_SERVER=28440@cinlic11.av.ge.com

setlocal

@set PARAM1=%1

rem if x%PARAM1% == x  goto help
rem if %1==-help goto help

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

echo First Argument : "%1"
echo Second Argument : "%2"
echo Third Argument : "%3"
echo Fourth Argument : "%4"
echo Fifth Argument : "%5"
echo Sixth Argument : "%6"
echo Seventh Argument : "%7"
echo Eighth Argument : "%8"

if "%UGII_BASE_DIR%"=="" (
 echo UGII_BASE_DIR is not set.
 EXIT 1
)

if "%SPLM_LICENSE_SERVER%"=="" (
 echo SPLM_LICENSE_SERVER is not set.
 EXIT 1
)

set UGII_ROOT_DIR=%UGII_BASE_DIR%\UGII
set UGII_CONFIG_FILE=%UGII_BASE_DIR%\PVTRANS\tessUG.config

if x%2==xdefaultconfig goto setenv
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

REM 
REM Using text file with @DB Strings
REM 
"%UGII_BASE_DIR%\PVTRANS\run_ugtopv.bat" -config="%UGII_CONFIG_FILE%" -noupdate "-pim=yes" %3 %4 %5 %6 %7 %8 %9
goto done

REM 
REM Using single part option with individual @DB strings
REM 
:single_part
set UGII_DEFAULTS_FILE=%3
if %3==defaultdef set UGII_DEFAULTS_FILE=
set UGII_LOAD_OPTIONS=
"%UGII_BASE_DIR%\PVTRANS\run_ugtopv.bat" -single_part -config="%UGII_CONFIG_FILE%" -noupdate "-pim=yes" %4 %5 %6 %7 %8 %9
goto done

REM 
REM Copying latest UG release status.
REM 
:copyugrelstatus
call %TC_DATA%\tc_profilevars
echo "%TC_ROOT%\bin\tc_workflow_postprocess.exe" %2 %3 %4 %5 %6 %7 %8 %9
"%TC_ROOT%\bin\tc_workflow_postprocess.exe" %2 %3 %4 %5 %6 %7 %8 %9
goto done

:done
set EXITVALUE=%ERRORLEVEL%

set PATH=%OLDPATH%

:end

endlocal

@echo on

EXIT %EXITVALUE%
