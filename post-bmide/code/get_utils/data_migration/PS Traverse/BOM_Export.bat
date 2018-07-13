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
set /P TCUSER=Enter Teamcenter USER(TC USER ID): 
:CHECK_TCUSER
if not defined TCUSER goto GET_TCUSER

goto CHECK_TCPASSWORD
:GET_TCPASSWORD
set /P TCPASSWORD=Enter Teamcenter USER Password(TC PASSWORD):
:CHECK_TCPASSWORD
if not defined TCPASSWORD goto GET_TCPASSWORD

goto CHECK_TCGROUP
:GET_TCGROUP
set /P TCGROUP=Enter Teamcenter GROUP(TC GROUP): 
:CHECK_TCGROUP
if not defined TCGROUP goto GET_TCGROUP

goto CHECK_INPUTFILE
:GET_INPUTFILE
set /P INPUTFILE=Enter Input File Name: 
:CHECK_INPUTFILE
if not defined INPUTFILE goto GET_INPUTFILE

goto CHECK_INPUTFILE
:GET_OUTPUTDIR
set /P OUTPUTDIR=Enter Output Folder Path: 
:CHECK_INPUTFILE
if not defined OUTPUTDIR goto GET_OUTPUTDIR

FOR /F "tokens=1-26 delims=;" %%a IN (%INPUTFILE%) DO echo. && echo Item Id: %%a && ps_traverse -u=%TCUSER% -p=%TCPASSWORD% -g=%TCGROUP% -itemid="%%a" -rev="%%b" -revrule="Any Status; Working" -cfg=config.txt -packlines=true -report="%OUTPUTDIR%\%%a_%%b_BOM.txt" -log="%OUTPUTDIR%\%%a_%%b_Exp.log" && echo ----------

::FOR /F "tokens=1-26 delims=;" %%a IN (%INPUTFILE%) DO echo. && echo Item Id: %%a && ps_traverse -u=%TCUSER% -p=%TCPASSWORD% -g=%TCGROUP% -itemid="%%a" -revrule="Any Status; Working" -report="%%b\Output\%%a_BOM.txt" -cfg=ps_config.txt -rev="%%c" -packlines=true&& echo ----------

echo "end script"
:: Convert_files_ps_explosion.pl D:\Ps_Traverse\ManufacturerExplosion\OutputExplosion D:\Ps_Traverse\ManufacturerExplosion\PerlOutput