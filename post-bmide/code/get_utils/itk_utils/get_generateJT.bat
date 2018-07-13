@rem  get_generateJT.bat
@rem ##########################################################################################
@rem Name          : get_generateJT.bat
@rem Description   : This script is used to generate the JTs for Piece parts
@rem input arguments: get_generateJT.bat <username> <password> <group> <filename>
@rem Who                       When                    What
@rem TCS Development Team     05-Sept-2017            Created batch file 
@rem #########################################################################################
@rem log files are written to %TMP% location
rem @echo off
@set TC_ROOT=CHANGE_ME
@set TC_DATA=CHANGE_ME
call %TC_DATA%\tc_profilevars

@set TMP=CHANGE_ME

@set FMS_HOME=CHANGE_ME

echo First Argument : "%1"
echo Third Argument : "%3"
echo Fourth Argument : "%4"

@if not exist "%UGII_BASE_DIR%" goto :no_ug
@setlocal

@set PATH=%UGII_BASE_DIR%\UGII;%PATH%
@set UGII_ROOT_DIR=%UGII_BASE_DIR%\UGII
@set JTK_USE_MASTER_NOTATION_PMI_FORMAT=1
@set UGII_PV_TRANS_MODEL_ANN=1
@set UGII_CONFIG_FILE=%UGII_BASE_DIR%\PVTRANS\tessUG.config

@rem This must be set to use the instance ID for CADIDs
@set JTK_XLATR_ENABLE_PERSISTED_INSTANCE_ID=1

@rem provide username, password, group and inputfile 
@"%UGII_BASE_DIR%\PVTRANS\ugtopv.exe" -config="%UGII_CONFIG_FILE%" "-pim=yes" -u=%1 -p=%2 -g=%3 %4

@endlocal
@goto :end

:no_ug
@echo "The environment variable UGII_BASE_DIR is not set"
@echo "Exiting..."
@goto :end

:end
