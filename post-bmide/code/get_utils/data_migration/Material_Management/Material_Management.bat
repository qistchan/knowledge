
@echo off
ECHO Start Material Management 
set /p TC_ROOT="Enter TC_ROOT: "
cd /d %TC_ROOT%\tc_menu
for /f %%i in ('dir /b /r %TC_ROOT%\tc_menu') do call %%i
ECHO TC Env set


set /p INPUT_FILES="Enter Input File Location: "
set path=%PATH%;%INPUT_FILES%;
call ips_data_upload_tc11_2_64bit_nti_11_4_0_dev_c.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -i=%INPUT_FILES%\create_mtrl.txt -cfg=%INPUT_FILES%\create_mtrl_cfg.txt -mode=items
ECHO Materials are created

call ips_data_upload_tc11_2_64bit_nti_11_4_0_dev_c.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -i=%INPUT_FILES%\create_stk_mtrl.txt -cfg=%INPUT_FILES%\create_stk_mtrl_cfg.txt -mode=forms
ECHO Stock Materials are created

call ips_data_upload_tc11_2_64bit_nti_11_4_0_dev_c.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -i=%INPUT_FILES%\create_stk_mtrl_rel.txt -cfg=%INPUT_FILES%\create_stk_mtrl_rel_cfg.txt -mode=relations
ECHO Stock material relations are created

call ips_data_upload_tc11_2_64bit_nti_11_4_0_dev_c.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -i=%INPUT_FILES%\create_part_to_mtrl_rel.txt -cfg=%INPUT_FILES%\create_part_to_mtrl_rel_cfg.txt -mode=relations
ECHO Parts and Materials are related

call ips_data_upload_tc11_2_64bit_nti_11_4_0_dev_c.exe -u=migration_user -pf=%INPUT_FILES%\pf.txt -g=dba -i=%INPUT_FILES%\create_mfg_form.txt -cfg=%INPUT_FILES%\create_mfg_form_cfg.txt -mode=forms
ECHO Mfg Attribute forms are created

ECHO Updates completed 

cmd /k
