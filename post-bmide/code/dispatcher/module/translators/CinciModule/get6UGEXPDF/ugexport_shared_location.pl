#! perl

my $tcRoot=$ENV{TC_ROOT};
if (-e $tcRoot)
{
  print "TC_ROOT=$tcRoot\n";
}
else
{
  print "*** Error Invalid TC_ROOT=$tcRoot\n";
  exit;
}

my $tcData=$ENV{TC_DATA};
if (-e $tcRoot)
{
  print "TC_DATA=$tcData\n";
}
else
{
  print "*** Error Invalid TC_DATA=$tcData\n";
  exit;
}
my $nxBaseDir=$ENV{UGII_BASE_DIR};
if (-e $nxBaseDir)
{
  print "UGII_BASE_DIR=$nxBaseDir\n";
}
else
{
  print "*** Error Invalid UGII_BASE_DIR=$nxBaseDir\n";
  exit;
}

my $pathSep="/";
my $shExt=".sh";
my $vbsExt=".vbs";
my $shHeader= "#!/bin/ksh";
my $loginEnv="${TC_LOGIN_STRING}";
my $anarkMode="${ACSCLI_PDF_MODE}";
my $anarkTimeOut="${ACSCLI_TIMEOUT_ARG}";
my $anarkWMMode="${ACSCLI_WM_MODE}";
my $anarkWMOptionalArgs="${ACSCLI_WM_SETTINGS}";
my $anarkRecipe="${ACSCLI_PART_RECIPE}";
my $anarkPartListRecipe="${ACSCLI_ASSY_RECIPE}";
my $anarkTemplate="${ASSY_PDF_TEMPLATE}";
my $anarkPartTemplate="${PART_PDF_TEMPLATE}";
my $anarkOutDir="${ACSCLI_OUT_DIR}";
my $anarkCopyToDir="${ACSCLI_COPYTO_DIR}";
my $anarkInstallDir="${ACSCLI_INSTALL_DIR}";
my $anarkImportData="${ACSCLI_IMPORT_DATA}";
my $zPath="${z_path}";
if ( $^O =~ /MSWin/ )
  {
    $pathSep="\\";
    $shExt=".bat";
	$vbsExt=".vbs";
    $shHeader= "\@echo off";
    $loginEnv="%TC_LOGIN_STRING%";
	$anarkMode="%ACSCLI_PDF_MODE%";
	$anarkTimeOut="%ACSCLI_TIMEOUT_ARG%";
	$anarkWMMode="%ACSCLI_WM_MODE%";
	$anarkWMOptionalArgs="%ACSCLI_WM_SETTINGS%";
	$anarkRecipe="%ACSCLI_PART_RECIPE%";
	$anarkPartListRecipe="%ACSCLI_ASSY_RECIPE%";
	$anarkTemplate="%ASSY_PDF_TEMPLATE%";
	$anarkPartTemplate="%PART_PDF_TEMPLATE%";
	$anarkOutDir="%ACSCLI_OUT_DIR%";
	$anarkCopyToDir="%ACSCLI_COPYTO_DIR%";
	$anarkInstallDir="%ACSCLI_INSTALL_DIR%";
	$anarkImportData="%ACSCLI_IMPORT_DATA%";
    $zPath="%z_path%";
  }
# recipe switch 0 for single_part, 1 for assembly
my $recipeSwitch=0;
my $bctSwitch=0;
my $watermarkSwitch=0;
my $substr="-assembly";
my $nArgs = scalar(@ARGV);
my $i=0;
my $moduleDir=@ARGV[$i++];
print "moduleDir=$moduleDir\n";
my $inputFile=@ARGV[$i++];
print "inputFile=$inputFile\n";
my $outputDir=@ARGV[$i++];
print "outputDir=$outputDir\n";
my $anarkinputFile=$inputFile."_Anark.txt";
print "anarkinputFile=$anarkinputFile\n";
my $anarkwminputFile=$inputFile."_AnarkWM.txt";
print "anark watermark inputFile=$anarkwminputFile\n";

# Skipping over single_part translation argument.
$i++;

#
# Enclose value for input string with "" if it contains any empty whitespace
# This expects input string in form of key=value and will return back value wrapped by "" if needed e.g. key="value"
# This will return input string as it is, if already wrapped with "" or if value doesnot contain any whitespace
# e.g. "-user=eng_user1" or -user="eng_user"
# 
sub processLoginInfo($)
{
    # Assign the argument(s) locally.
    my $str= shift;
    my $pos = 0;
    $pos = index($str, ' ', $pos);
    if($pos != -1){
        # Check if the argument is already wrapped by " " e.g. "-user=eng_user1"
        unless($str =~ /^\".*\"$/){
            # Get argument key and value by looking for '='
            if ($str =~ /([^=]*)\=(.+)$/){
                my $argName = $1;
                my $argVal = $2;
                # Return $argName="argVal" string
                $str= $argName.'='.'"'.$argVal.'"';
            }
        }
    }
    
    return $str;
}

# Extract NxClone login from translation arguments (-username, -password, -group, -encrypted_password).
my $cloneLogin=processLoginInfo(@ARGV[$i]);
$i++;
$cloneLogin="$cloneLogin " . processLoginInfo(@ARGV[$i]);
$i++;
$cloneLogin="$cloneLogin " . processLoginInfo(@ARGV[$i]);
$i++;
$cloneLogin="$cloneLogin " . processLoginInfo(@ARGV[$i]);
$i++;
print "cloneLogin=$cloneLogin\n";

chdir $outputDir;

my $cloneFile=$outputDir.$pathSep."clone".$shExt;
my $postFile=$outputDir.$pathSep."post".$shExt;
my $acscliFile=$outputDir.$pathSep."acscli".$shExt;
my $acscliStatus=$outputDir.$pathSep."acscliStatus".$shExt;
my $acscliLog=$outputDir.$pathSep."acscliLog".$shExt;
my $acscliwmStatus=$outputDir.$pathSep."acscliwmStatus".$shExt;
my $acscliWMFile=$outputDir.$pathSep."acscliWaterMark".$shExt;
my $xcopyFile=$outputDir.$pathSep."xCopy".$shExt;
my $xcopyLogFile=$outputDir.$pathSep."xCopyLog".$shExt;
my $winzipFile=$outputDir.$pathSep."unzip".$shExt;
my $vbsFile=$outputDir.$pathSep."generateXLSX".$vbsExt;
my $saveLog="clone_log.txt";
my $cloneOut="clone_out.txt";
my $postOut="post_out.txt";
my $anark_Out="anark_out.txt";

my $cloneArgs;
my $revIDFlag="-rev=";
my $revID;
my $revIndex=0;
for (; $i<$nArgs; $i++)
  {
    my $arg=@ARGV[$i];
    print "   $arg\n";
    $cloneArgs="$cloneArgs $arg";
  }

if (open (IN_FILE, "< $inputFile"))
  {
    while (my $inputArg = <IN_FILE>)
      {
        chomp ($inputArg);
        print "   $inputArg\n";
        $cloneArgs="$cloneArgs $inputArg";
		$revIndex=rindex($inputArg, $revIDFlag);
		$revID=substr($inputArg,$revIndex+5);
		if (index($inputArg, $substr) != -1) {
			$recipeSwitch=1;
		}
      }
    close IN_FILE;
  }
  
$cloneArgs="$cloneArgs -export_dir=$outputDir";
my $find="-assembly";
my $replace="-part";
$cloneArgs=join( $replace, split($find, $cloneArgs) );

my $index = 0;
my $anarkoutArg;
my $anarklogArg;
my $anarkwmlogArg;
my $anarkcadFileArg;
my $anarkwmTextArg;
my $anarkWMArgs;
my $anarkArgs;
my $anarkEnforceRecipe;
my $UUID;
my $WMUUID;
my $TASKID;
my $srcPart;
my $srcFileName;
my $bctFile;
my $pdfFileName;
my $anarkAttachFileArg;

if($recipeSwitch == 1)
{
	$anarkEnforceRecipe = $anarkPartListRecipe;
}
else
{
	$anarkEnforceRecipe = $anarkRecipe;
	$anarkTemplate = $anarkPartTemplate;
}
if (open (IN_FILE, "< $anarkinputFile"))
  {
    while (my $anarkinputArg = <IN_FILE>)
      {
        chomp ($anarkinputArg);
        print "   $anarkinputArg\n";
	#	if($index < 2)
	#	{
	#		$anarkArgs="$anarkArgs $anarkinputArg";
	#	}
		if($index == 0)
		{
			$UUID = $anarkinputArg;
		}
		if($index==2)
		{
			$TASKID=$anarkinputArg;
			$anarkOutDir = $anarkOutDir.$TASKID.$pathSep."result".$pathSep;
			$anarkoutArg = "-outpdf ".$anarkOutDir.$UUID.".pdf";
			$anarklogArg = "-logfile ".$anarkOutDir.$UUID.".log";
			$anarkImportData="-importData ".$anarkOutDir."PartsList.xlsx";
			print "anarkoutFile=$anarkoutArg\n";
			print "anarklogFile=$anarklogArg\n";
		}
		if($index==3)
		{
			$srcPart=$anarkinputArg;
		}
		if($index==4)
		{
			$srcFileName=$anarkinputArg;
		}
		if($index==5)
		{
			$bctSwitch=1;
			$bctFile=$anarkOutDir.$anarkinputArg;
		}
		$index++;
      }
	  $anarkArgs=$UUID." -cadfile ".$anarkOutDir.$srcFileName;
    close IN_FILE;
  }
  
my $anarkPartsListFile=$anarkOutDir."PartsList.xlsx";

$pdfFileName = substr($srcFileName, 0, -4);
$pdfFileName=$pdfFileName."_".$revID;
$index = 0;
if (open (IN_FILE, "< $anarkwminputFile"))
{
    while (my $anarkwminputArg = <IN_FILE>)
    {
        chomp ($anarkwminputArg);
        print "   $anarkwminputArg\n";
		if($index==0)
		{
			$WMUUID=$anarkwminputArg;
			$anarkwmlogArg=" -logfile ".$anarkOutDir.$WMUUID.".log";
			print "anark water mark logFile=$anarkwmlogArg\n";
		}
		if($index==1)
		{
			$anarkwmTextArg=$anarkwminputArg;
			$watermarkSwitch=1;
		}
		$index++;
	}
	$anarkWMArgs=$WMUUID." -cadfile ".$anarkOutDir.$UUID.".pdf"." -txt ".$anarkwmTextArg.$anarkwmlogArg;
	close IN_FILE;
}
if(($recipeSwitch == 1) && ($bctSwitch == 1))
{
	$anarkAttachFileArg=" -attachFiles ".$anarkPartsListFile.";".$bctFile;
}
if(($recipeSwitch == 1) && ($bctSwitch == 0))
{
	$anarkAttachFileArg=" -attachFiles ".$anarkPartsListFile;
}
if(($recipeSwitch == 0) && ($bctSwitch == 1))
{
	$anarkAttachFileArg=" -attachFiles ".$bctFile;
}
print "cloneFile=$cloneFile\n";
open (CLONE_FILE, "> $cloneFile") or die "*** Error can't open $cloneFile ! \n";
print CLONE_FILE "$shHeader\n";
print CLONE_FILE "$ENV{CLONE_COMMAND} $loginEnv $cloneArgs  > $cloneOut 2>&1\n";
close CLONE_FILE;

print "postFile=$postFile\n";
open (POST_FILE, "> $postFile") or die "*** Error can't open $postFile ! \n";
print POST_FILE "$shHeader\n";
if ( $^O =~ /MSWin/ )
  {
    print POST_FILE "call %TC_DATA%\\tc_profilevars.bat\n";
    print POST_FILE "%TC_ROOT%\\bin\\tc_nxclone_postprocess $loginEnv $cloneArgs -clone_out=$cloneOut > $postOut 2>&1\n";
  }
else
  {
    print POST_FILE ". \${TC_DATA}/tc_profilevars\n";
    print POST_FILE "\${TC_ROOT}/bin/tc_nxclone_postprocess $loginEnv $cloneArgs -clone_out=$cloneOut > $postOut 2>&1\n";
  }
close POST_FILE;

print "acscliFile=$acscliFile\n";
open (ACSCLI_FILE, "> $acscliFile") or die "*** Error can't open $acscliFile ! \n";
print ACSCLI_FILE "$shHeader\n";
if ( $^O =~ /MSWin/ )
  {
    print ACSCLI_FILE "cd \/D $anarkInstallDir \n";
	if($recipeSwitch == 0)
	{
		print ACSCLI_FILE "ACSCLI.exe $anarkMode $anarkArgs $anarkEnforceRecipe $anarkTemplate $anarkoutArg $anarklogArg $anarkAttachFileArg $anarkTimeOut\n";
	}
	if($recipeSwitch == 1)
	{
		print ACSCLI_FILE "ACSCLI.exe $anarkMode $anarkArgs $anarkEnforceRecipe $anarkTemplate $anarkoutArg $anarklogArg $anarkImportData $anarkAttachFileArg $anarkTimeOut\n";
	}
  }
else
  {
    print ACSCLI_FILE "cd \/D $anarkInstallDir \n";
    if($recipeSwitch == 0)
	{
		print ACSCLI_FILE "ACSCLI.exe $anarkMode $anarkArgs $anarkEnforceRecipe $anarkTemplate $anarkoutArg $anarklogArg $anarkAttachFileArg $anarkTimeOut\n";
	}
	if($recipeSwitch == 1)
	{
		print ACSCLI_FILE "ACSCLI.exe $anarkMode $anarkArgs $anarkEnforceRecipe $anarkTemplate $anarkoutArg $anarklogArg $anarkImportData $anarkAttachFileArg $anarkTimeOut\n";
	}
  }
close ACSCLI_FILE;

print "acscliStatusFile=$acscliStatus\n";
open (ACSCLISTATUS_FILE, "> $acscliStatus") or die "*** Error can't open $acscliStatus ! \n";
print ACSCLISTATUS_FILE "$shHeader\n";
if ( $^O =~ /MSWin/ )
  {
    print ACSCLISTATUS_FILE "cd \/D $anarkInstallDir \n";
    print ACSCLISTATUS_FILE "ACSCLI.exe -status $UUID $anarklogArg\n";
  }
else
  {
    print ACSCLISTATUS_FILE "cd \/D $anarkInstallDir \n";
    print ACSCLISTATUS_FILE "ACSCLI.exe -status $UUID $anarklogArg\n";
  }
close ACSCLISTATUS_FILE;


print "acscliLogFile=$acscliLog\n";
open (ACSCLILOG_FILE, "> $acscliLog") or die "*** Error can't open $acscliLog ! \n";
print ACSCLILOG_FILE "$shHeader\n";
if ( $^O =~ /MSWin/ )
  {
    print ACSCLILOG_FILE "cd \/D $anarkInstallDir \n";
    print ACSCLILOG_FILE "ACSCLI.exe -log $UUID $anarklogArg\n";
  }
else
  {
    print ACSCLILOG_FILE "cd \/D $anarkInstallDir \n";
    print ACSCLILOG_FILE "ACSCLI.exe -log $UUID $anarklogArg\n";
  }
close ACSCLILOG_FILE;

if($watermarkSwitch==1)
{
	print "watermark acscliFile=$acscliWMFile\n";
	open (ACSCLI_WM_FILE, "> $acscliWMFile") or die "*** Error can't open $acscliWMFile ! \n";
	print ACSCLI_WM_FILE "$shHeader\n";
	if ( $^O =~ /MSWin/ )
	  {
		print ACSCLI_WM_FILE "cd \/D $anarkInstallDir \n";
		print ACSCLI_WM_FILE "ACSCLI.exe $anarkWMMode $anarkWMArgs $anarkWMOptionalArgs\n";
	  }
	else
	  {
		print ACSCLI_WM_FILE "cd \/D $anarkInstallDir \n";
		print ACSCLI_WM_FILE "ACSCLI.exe $anarkWMMode $anarkWMArgs $anarkWMOptionalArgs\n";
	  }
	close ACSCLI_WM_FILE;
	
	print "acscliwmStatusFile=$acscliwmStatus\n";
	open (ACSCLIWMSTATUS_FILE, "> $acscliwmStatus") or die "*** Error can't open $acscliwmStatus ! \n";
	print ACSCLIWMSTATUS_FILE "$shHeader\n";
	if ( $^O =~ /MSWin/ )
	  {
		print ACSCLIWMSTATUS_FILE "cd \/D $anarkInstallDir \n";
		print ACSCLIWMSTATUS_FILE "ACSCLI.exe -status $WMUUID $anarkwmlogArg\n";
	  }
	else
	  {
		print ACSCLIWMSTATUS_FILE "cd \/D $anarkInstallDir \n";
		print ACSCLIWMSTATUS_FILE "ACSCLI.exe -status $WMUUID $anarkwmlogArg\n";
	  }
	close ACSCLIWMSTATUS_FILE;
}

my $srcFile=$anarkOutDir.$UUID.".pdf";
#my $dstFile=$outputDir.$pathSep.$TASKID.".pdf";
$dstFile=$pdfFileName.".pdf";
my $srclogFile=$anarkOutDir.$UUID.".log";
my $dstlogFile=$outputDir.$pathSep.$TASKID.".log";
print "xcopyFile=$xcopyFile\n";
open (XCOPY_FILE, "> $xcopyFile") or die "*** Error can't open $xcopyFile ! \n";
print XCOPY_FILE "$shHeader\n";
if ( $^O =~ /MSWin/ )
  {
    print XCOPY_FILE "copy \/y $srcFile $dstFile \n";
	print XCOPY_FILE "copy \/y $srclogFile $dstlogFile \n";
  }
else
  {
    print XCOPY_FILE "copy \/y $srcFile $dstFile \n";
	print XCOPY_FILE "copy \/y $srclogFile $dstlogFile \n";
  }
close XCOPY_FILE;

print "xcopyLogFile=$xcopyLogFile\n";
open (XCOPY_LOGFILE, "> $xcopyLogFile") or die "*** Error can't open $xcopyLogFile ! \n";
print XCOPY_LOGFILE "$shHeader\n";
if ( $^O =~ /MSWin/ )
  {
	print XCOPY_LOGFILE "copy \/y $srclogFile $dstlogFile \n";
  }
else
  {
	print XCOPY_LOGFILE "copy \/y $srclogFile $dstlogFile \n";
  }
close XCOPY_LOGFILE;

if($recipeSwitch == 1)
{
	print "vbsFile=$vbsFile\n";
	open (VBS_FILE, "> $vbsFile") or die "*** Error can't open $vbsFile ! \n";
	if ( $^O =~ /MSWin/ )
	{
		print VBS_FILE "Set objExcel = CreateObject(\"Excel.Application\") \n";
		print VBS_FILE "objExcel.Application.Run \"'$outputDir\\PartsList.xlsm'!ThisWorkbook.CreateXLSX\" \n";
		print VBS_FILE "objExcel.DisplayAlerts = False \n";
		print VBS_FILE "objExcel.Application.Quit \n";
		print VBS_FILE "Set objExcel = Nothing \n";
	}
	else
	{
		print VBS_FILE "Set objExcel = CreateObject(\"Excel.Application\") \n";
		print VBS_FILE "objExcel.Application.Run \"'$outputDir\\PartsList.xlsm'!ThisWorkbook.CreateXLSX\" \n";
		print VBS_FILE "objExcel.DisplayAlerts = False \n";
		print VBS_FILE "objExcel.Application.Quit \n";
		print VBS_FILE "Set objExcel = Nothing \n";
	}
	close VBS_FILE;
}

#
# Run vb script to generate PartList.xlsx
#
if($recipeSwitch == 1)
{
	print "executing generateXLSX vb script...\n";
	chmod (0755, $vbsFile);
	system($vbsFile);
}

#
# Run NX clone command
#
print "executing clone...\n";
print "$cloneArgs\n";
chmod (0755, $cloneFile);
system($cloneFile);

#
# Run PostProcess command
#
print "executing post_process...\n";
print "$postArgs\n";
chmod (0755, $postFile);
#system($postFile);

#
# Run ACSCLI command
#
print "executing 3D PDF generation process...\n";
print "$anarkArgs\n";
chmod (0755, $acscliFile);
my $returnCode=system($acscliFile);
print "ACSCLI Return Code = $returnCode\n";
if ( $returnCode != 0 ) 
{
	die "Failed executing [$acscliFile]\n"; 
}
else
{
	my $statusCode=0;
	print "executing 3D PDF query process...\n";
	chmod (0755, $acscliStatus);
	$statusCode=system($acscliStatus);
	print "Status Code = $statusCode\n";
	# return code 1024 corresponds to code 5 , return code 512 corresponds to code 3 in Anark
	while(($statusCode == 1024) || ($statusCode == 512))
	{
		print "loop executing 3D PDF query process...\n";
		$statusCode=system($acscliStatus);
		sleep(20);
		print "In Loop Status Code = $statusCode\n";
	}
	# return code 256 corresponds to code 1 in Anark, return code 1536 RunCompletedwithwarnings
	if(($statusCode == 256) || ($statusCode == 1536))
	{
		#
		# Watermark PDF
		#
		if($watermarkSwitch==1)
		{
			print "executing 3D PDF Watermark process...\n";
			chmod (0755, $acscliWMFile);
			$returnCode=system($acscliWMFile);
			print "Return Code = $returnCode\n";
			if( $returnCode != 0 ) 
			{
				die "Failed executing [$acscliWMFile]\n"; 
			}
			else
			{
				my $statCode=0;
				print "executing 3D PDF query process...\n";
				chmod (0755, $acscliwmStatus);
				$statCode=system($acscliwmStatus);
				print "Status Code = $statCode\n";
				# return code 1024 corresponds to code 5 , return code 512 corresponds to code 3 in Anark
				while(($statCode == 1024) || ($statCode == 512))
				{
					print "loop executing 3D PDF query process...\n";
					$statCode=system($acscliwmStatus);
					sleep(5);
					print "In Loop Status Code = $statCode\n";
				}
			}
		}
		#
		# Run copy command
		#
		print "executing copy process...\n";
		system($xcopyFile);
	}
	else
	{
		# Generate Log file for failure
		print "loop executing 3D PDF query process...\n";
		$statusCode=system($acscliLog);
		print "Log file status = $statusCode\n";
		
		#
		# Run copy command for logs
		#
		print "executing copy logs process...\n";
		system($xcopyLogFile);
	}
}

