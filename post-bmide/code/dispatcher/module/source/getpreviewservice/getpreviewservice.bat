@echo off

REM # ==================================================================== #
REM # SCRIPT TO RUN PREVIEWSERVICE TRANSLATOR
REM # NOTE: Set the license file and TC VVCP directory path.
REM # ==================================================================== #
setlocal

REM example set LM_LICENSE_FILE=7204@sol001
REM example set TC_VVCP=C:/PROGRA~1/UGS/TcVis/5_0/VVCP

set LM_LICENSE_FILE=28440@cinlic11.av.ge.com
set TC_VVCP=E:\app\TcVis\VVCP

@set PARAM1=%1

if x%PARAM1%== x goto help
if %1== -help goto help

goto setenv

:help
echo Usage:
echo  Translator executable name: %0
echo  Command String is:
echo    "%0 InputDir OutputDir Outformat <Size value> [-combine] [-f <file name>]"
echo  Where Seven parameters are passed:
echo    Param 1) Input directory name to translate with complete path
echo    Param 2) Output directory name to place putput files with complete path
echo    Param 3) Output type of Translator. Values are CGM, TIF, HPG, PDF, JPG, CGM_AND_JPG, CGM_AND_PDF or JPG_AND_PDF
echo    Param 4) Size of the image.
echo    Param 5) Combine the result in a single output file. Values can be -combine. Optional parameter
echo    Param 6) "-f" Option to translate specific file followed by file name in InputDir. Optional parameter
echo    Param 7) Input file name if "-f" parameter specified. Optional parameter.
echo    Parameters after the above defined are passed directly to prepare.exe.
echo    Example:-
echo       %0 d:\test\ d:\test\result PDF 500x500px -combine -f d:\test\xyz.doc
EXIT /B 1

:setenv
if "%LM_LICENSE_FILE%"=="CHANGE_ME" (
  echo set LM License File
  EXIT /B 2
 )

if "%TC_VVCP%"=="CHANGE_ME" (
  echo set VVCP Path
  EXIT /B 3
 )
 
set SRCDIRPATH=%1
set DSTDIRPATH=%2
set OUTPUT_TYPE=-%3
set SIZE_VALUE=%4
set ARG_COUNT=4 
set EXTVAR=*.ps *.pdf *.hpgl *.cgm *.dxf *.dwg *.prt *.dft *.doc *.xls *.ppt *.calcomp *.txt *.igs *.docx *.xlsx *.pptx

if "%5"=="-combine" (
  set COMBINE=%5
  set ARG_COUNT=5 
 )

if "%5"=="-f" (
   REM Dont add files with .jt extensions.
   echo %6 | find /i ".jt" > nul 
     if errorlevel 1 (
        set EXTVAR=%6
     )        
  set ARG_COUNT=6 
  goto :next
 )

if "%6"=="-f" (
   REM Dont add files with .jt extensions.
   echo %7 | find /i ".jt" > nul 
     if errorlevel 1 (
        set EXTVAR=%7
     )                
  set ARG_COUNT=7 
 )
:next

for /f "tokens=*" %%a in ('cd') do set CURRDIR=%%~sa
cd /d %SRCDIRPATH%

REM Invocation of Jt2jpeg Translator if JT file exists and JPG is asked
set JTVAR=%SRCDIRPATH%\*.jt
set JT_TO_JPG=0

IF not exist %JTVAR% goto :endjt
IF /I "%OUTPUT_TYPE%"=="-JPG" set JT_TO_JPG=1
IF /I "%OUTPUT_TYPE%"=="-JPG_AND_PDF" set JT_TO_JPG=1

IF %JT_TO_JPG%==0 goto :endjt

"%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -JPG -jtindir %SRCDIRPATH% -jtoutdir %DSTDIRPATH% -jtimage 3 -jtview 0 -jtsize %SIZE_VALUE% -jtbg 0 -jtvtype 1 -jtquality 100 -jtbomfile jt2jpeg.bom -jtlogfile jt2jpeg.log
set EXITVALUE=%ERRORLEVEL%
:endjt

REM Build a list of files to be translated
IF exist files del files
for %%F IN ( %EXTVAR% ) DO echo %%~F,>>files

REM check for existence of files
IF exist files goto :filesexist

goto :endext

:filesexist
 
for /L %%G IN (1,1,%ARG_COUNT%) DO shift 

:rep
shift
set REST_OF_COMMAND=%REST_OF_COMMAND% %0
if not "%1"=="" goto rep

IF /I "%OUTPUT_TYPE%"=="-JPG_AND_PDF" (
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -PDF %COMBINE% "%%f" -out %DSTDIRPATH% %REST_OF_COMMAND%
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -JPG "%%f" -out %DSTDIRPATH% -size %SIZE_VALUE% %REST_OF_COMMAND%
) ELSE IF /I "%OUTPUT_TYPE%"=="-CGM_AND_PDF" (
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -CGM "%%f" -out %DSTDIRPATH% %REST_OF_COMMAND%
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -PDF %COMBINE% "%%f" -out %DSTDIRPATH% %REST_OF_COMMAND%
) ELSE IF /I "%OUTPUT_TYPE%"=="-CGM_AND_JPG" (
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -CGM "%%f" -out %DSTDIRPATH% %REST_OF_COMMAND%
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -JPG "%%f" -out %DSTDIRPATH% -size %SIZE_VALUE% %REST_OF_COMMAND%
) ELSE IF /I "%OUTPUT_TYPE%"=="-JPG" (
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" -JPG "%%f" -out %DSTDIRPATH% -size %SIZE_VALUE% %REST_OF_COMMAND%
) ELSE (
  for /F "delims=," %%f IN ( files ) DO "%TC_VVCP%\nogui" "%TC_VVCP%\prepare" %OUTPUT_TYPE% %COMBINE% "%%f" -out %DSTDIRPATH% -size %SIZE_VALUE% %REST_OF_COMMAND%
)

:endext
endlocal
set EXITVALUE=%ERRORLEVEL%
cd /d %CURRDIR%
EXIT /B %EXITVALUE%
