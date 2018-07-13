@echo off			
			
set SCRIPT_DIRECTORY=%~dp0
cd /d %SCRIPT_DIRECTORY%

goto CHECK_INPUTFILE
:GET_INPUTFILE
set /P INPUTFILE=Enter xmlList File Name: 
:CHECK_INPUTFILE
if not defined INPUTFILE goto GET_INPUTFILE

FOR /F "tokens=1-26 delims=;" %%a IN (%INPUTFILE%) DO echo. && echo Item Id: %%b %%a  && java -jar XMLParserDOM.jar -inTxt="C:\Amit\Utilities\ConvertXML\ConvertXML\InputDwg.txt" -inXml="%%b\%%a.xml" -inXsl="C:\Amit\Utilities\ConvertXML\ConvertXML\start_dwg\Parsexml.xsl" -outFol="C:\Amit\Utilities\ConvertXML\ConvertXML\TransformedXML" && echo ----------------