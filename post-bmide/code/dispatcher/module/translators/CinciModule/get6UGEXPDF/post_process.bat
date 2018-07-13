@echo off
call %TC_DATA%\tc_profilevars.bat
%TC_ROOT%\bin\tc_nxclone_postprocess %TC_LOGIN_STRING% %COMMAND_ARGS% -clone_out=clone_out.txt > post_out.txt 2>&1 
