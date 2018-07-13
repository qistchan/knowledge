#!/bin/ksh
###################################################################################################
### Program	: Script for importing plmxml files
###
### Requirements
###
### export TCROOT, TCDATA TCUSER TCPASSWORD TCGROUP
####################################################################################################
CURRENT_DIR=`pwd`; export CURRENT_DIR
SCRIPT_DIR=`dirname $0`
SCRIPT_DIR=`cd $SCRIPT_DIR;pwd`; export SCRIPT_DIR


while [ -z "$TCUSER" ]; do
	echo "Enter Teamcenter USER(TCUSER):"
	read TCUSER
	export TCUSER
done

while [ -z "$TCPASSWORD" ]; do
	echo "Enter Teamcenter USER Password(TCPASSWORD):"
	read TCPASSWORD
	export TCPASSWORD
done

while [ -z "$TCGROUP" ]; do
	echo "Enter Teamcenter GROUP(TCGROUP):"
	read TCGROUP
	export TCGROUP
done

echo "Sourcing the profilevars ..."
. $TC_DATA/tc_profilevars

while [ -z "$XMLFILE" ]; do
	echo "Enter XML File Name:"
	read XMLFILE
	export XMLFILE
done

INPUTFILE=$XMLFILE
if [ ! -f "$INPUTFILE" ]; then
	echo "***ERROR: input file $INPUTFILE doesn't exist"
	exit 1
fi

while read line
do
	foldername=`echo $line|awk -F';' '{print $2}'`
	folderpath=$SCRIPT_DIR/$foldername
	file=`echo $line|awk -F';' '{print $1}'`
	echo "$foldername/$file".xml
	plmxml_import -u=$TCUSER -p=$TCPASSWORD -g=$TCGROUP -transfermode=ConfiguredDataImportDefault -import_mode=ignore -xml_file="$foldername/$file".xml -log="$foldername/$file".log
done < $INPUTFILE
