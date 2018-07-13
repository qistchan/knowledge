
@echo off
ECHO Start Attributes Update 
set /p TC_ROOT="Enter TC_ROOT: "
cd /d %TC_ROOT%\tc_menu
for /f %%i in ('dir /b /r %TC_ROOT%\tc_menu') do call %%i
ECHO TC Env set


set /p INPUT_FILES="Enter Input File Location: "
set path=%PATH%;%INPUT_FILES%;
call ips_data_upload_tc11_2_64bit_nti_11_4_0_dev_c.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -i=%INPUT_FILES%\attr_update.txt -cfg=%INPUT_FILES%\attr_update_cfg.txt -mode=items
ECHO Attributes are updated


call ips_data_upload_tc11_2_64bit_nti_11_4_0_dev_c.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -i=%INPUT_FILES%\ownership.txt -cfg=%INPUT_FILES%\ownership_cfg.txt -mode=items
ECHO Items updated with ownership information

ECHO Updates completed 

cmd /k
