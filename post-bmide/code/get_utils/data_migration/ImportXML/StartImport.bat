@echo off			
			
set SCRIPT_DIRECTORY=%~dp0
cd /d %SCRIPT_DIRECTORY%
goto CHECK_TC_ROOT
:GET_TC_ROOT
set /P TC_ROOT=Enter Teamcenter Root directory path(TC_ROOT): 
:CHECK_TC_ROOT
if not defined TC_ROOT goto GET_TC_ROOT

goto CHECK_TC_DATA
:GET_TC_DATA
set /P TC_DATA=Enter Teamcenter Data directory path(TC_DATA): 
:CHECK_TC_DATA
if not defined TC_DATA goto GET_TC_DATA

call %TC_DATA%\tc_profilevars

goto CHECK_TCUSER
:GET_TCUSER
set /P TCUSER=Enter Teamcenter USER(TCUSER): 
:CHECK_TCUSER
if not defined TCUSER goto GET_TCUSER

goto CHECK_TCPASSWORD
:GET_TCPASSWORD
set /P TCPASSWORD=Enter Teamcenter USER Password(TCPASSWORD):
:CHECK_TCPASSWORD
if not defined TCPASSWORD goto GET_TCPASSWORD

goto CHECK_TCGROUP
:GET_TCGROUP
set /P TCGROUP=Enter Teamcenter GROUP(TCGROUP): 
:CHECK_TCGROUP
if not defined TCGROUP goto GET_TCGROUP

goto CHECK_INPUTFILE
:GET_INPUTFILE
set /P INPUTFILE=Enter Input File Name: 
:CHECK_INPUTFILE
if not defined INPUTFILE goto GET_INPUTFILE

FOR /F "tokens=1-26 delims=;" %%a IN (%INPUTFILE%) DO echo. && echo Item Id: %%b %%a  && plmxml_import -u=%TCUSER% -p=%TCPASSWORD% -g=%TCGROUP%  -transfermode=ConfiguredDataImportDefault -import_mode=ignore -xml_file="%%b\%%a.xml"  -log="%%b\%%a.log" && echo ----------------
