@echo off

REM # ==================================================================== #
REM # SCRIPT TO RUN GET6BomIndex TRANSLATOR
REM # ==================================================================== #

echo GET6BomIndexModule Start
setlocal

echo %~dp0
set currentfolder=%~dp0
echo %currentfolder%

set SRCINPUTDIR=%1
echo %SRCINPUTDIR%

set ITEMID=%3
echo %itemID%

cd %SRCINPUTDIR%

for /r %SRCINPUTDIR% %%a in (*) do if "%%~nxa"=="%itemID%.txt" set p=%%~dpnxa
if defined p (
echo %p%
) else (
echo File not found
)

SET TC_ROOT=ChangeMe
SET TC_DATA=ChangeMe
call %TC_DATA%\tc_profilevars.bat 

echo %TC_ROOT%
start %TC_ROOT%\bin\bomindex_admin.exe -u=ChangeMe -p=ChangeMe -g=ChangeMe -inputfile=%p% -function=create -logfile=ChangeMe.log

rem touch %SRCINPUTDIR%\\result\\DummyFile.txt
type nul > %SRCINPUTDIR%\result\DummyFile.txt
echo dummy file Created

echo GET6BomIndexModule End