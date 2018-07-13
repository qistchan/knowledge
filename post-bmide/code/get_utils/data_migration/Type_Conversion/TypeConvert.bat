
@echo off
ECHO Start Type Conversion 
set /p TC_ROOT="Enter TC_ROOT: "
cd /d %TC_ROOT%\tc_menu
for /f %%i in ('dir /b /r %TC_ROOT%\tc_menu') do call %%i
ECHO TC Env set


set /p INPUT_FILES="Enter Input File Location: "
set path=%PATH%;%INPUT_FILES%;
cd /d %TC_ROOT%\bin
call item_to_part_design.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -file=%INPUT_FILES%\convert_type.txt -mode=item_id_based -rf=%INPUT_FILES%\convert_type_rep.txt
ECHO Type conversion Done

cmd /k
