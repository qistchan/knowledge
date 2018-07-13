@echo off

REM /*
REM *   Copyright © 2016 Anark Corporation
REM *   All rights reserved.
REM *
REM *   This software is Anark Corporation proprietary
REM *   and is not to be reproduced or transmitted in any form or by any means
REM *   or used in manner except as authorized in writing by the owner.
REM */

REM # ================================================================================= #
REM   SCRIPT TO ENCRYPT USER NAME/PASSWORD IN ACSCLI CONFIG FILE
REM # ================================================================================= #

REM # ================================================================================= #
REM   This bat file can be used to encrypt the user name and password in the config file
REM   using the /encrypt parameter. ACSCLI config file should be in the same folder
REM   as this bat file. To use the ACSCLI application with the encrypted config file on
REM   another machine, export the key using /exportkey parameter (on the machine where
REM   encryption was done) and import the key on the other machine using /importkey
REM   parameter. Specify the user who will be running the ACSCLI when running the bat
REM   file for encryption and for importing the key.
REM   Delete the keys file (ACSCLI_SecurityKeys.xml) after importing the key.
REM # ================================================================================= #

set inArg=%1
set acscliUser=%2

set PATH=C:\Windows\Microsoft.NET\Framework64\v4.0.30319;%PATH%

if [%inArg%]==[] goto usage
if [%acscliUser%]==[] set acscliUser=%USERDOMAIN%\%USERNAME%

if /i %inArg% equ /encrypt goto encrypt
if /i %inArg% equ /exportkey goto exportkey
if /i %inArg% equ /importkey goto importkey

:usage
echo Usage:
echo use /encrypt to encrypt username and password specified in ACSCLI.exe.config file
echo use /exportkey to export the encryption key to use it on another machine
echo use /importkey to import the encryption key on another machine
goto end

:encrypt

echo ENCRYPTING...
echo GIVING PERMISSIONS TO ACSCLI USER:  %acscliUser%

REM Create a machine level RSA Key container 
aspnet_regiis.exe -pc "ACSCLIEncKeys" -exp

REM Give permissions
aspnet_regiis.exe -pa "ACSCLIEncKeys" %acscliUser%

set configdir=%~dp0
set configdir=%configdir:~0,-1%

REM Rename the config file
move /y "%~dp0\ACSCLI.exe.config" "%~dp0\web.config"

REM Encrypt the user name/password
aspnet_regiis.exe -pef "applicationSettings/Anark.Core.Client.CoreSOAClient.AuthenticationSettings" "%configdir%" -prov "AppEncryptionProvider"

REM Rename the file to the original name
move /y "%~dp0\web.config" "%~dp0\ACSCLI.exe.config"
goto end

:exportkey

echo EXPORTING...

REM Export the key to be used in another machine. 
aspnet_regiis -px "ACSCLIEncKeys" "%~dp0\ACSCLI_SecurityKeys.xml" -pri
goto end


:importkey

echo IMPORTING...
echo GIVING PERMISSIONS TO ACSCLI USER:  %acscliUser%

REM Import the key 
aspnet_regiis -pi "ACSCLIEncKeys" "%~dp0\ACSCLI_SecurityKeys.xml"

REM Give permissions
aspnet_regiis.exe -pa "ACSCLIEncKeys" %acscliUser%
goto end

:end
