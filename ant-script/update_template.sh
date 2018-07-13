#!/bin/ksh
#
#  This script will perform an update of a single BMIDE data model.
#
#  Usage: updatetemplate.sh 
#
#  Set the following environment variables prior to running:
#	TC_ROOT
#	TC_DATA
#	DMDIR		The project's data model directory
#	TEMPLATE	The name of the template
#	TC_USER_PASSWD	The "infodba" user's password

echo "***********************************"
echo "*      Data Model Updater v10.x"
echo "***********************************"

echo "***********************************"
echo "*  Check for required environment variables"
echo "***********************************"

if test -z "${TC_ROOT}"  
then
	echo "ERROR:  TC_ROOT must be set"
	exit 1
fi

if test -z "${TC_DATA}"  
then
	echo "ERROR:  TC_DATA must be set"
	exit 1
fi

if test -z "${DMDIR}"
then
	echo "ERROR:  DMDIR must be set to project's data model directory"
	exit 1
fi
if ! test -d "${DMDIR}"
then
	echo "ERROR:  DMDIR does not exist"
	exit 1
fi


if test -z "${TEMPLATE}"
then
	echo "ERROR:  TEMPLATE must be set to the data model name"
	exit 1
fi

if test -z "${TC_USER_PASSWD}"
then
	echo "TC_USER_PASSWD must be set to infodba's password"
	exit 1
fi

echo "done"


if ! test -f "${TC_DATA}/model/${TEMPLATE}_template.xml"
then
	echo "This template is not currently installed."
	echo "Use TEM to install the template first before updating."
	exit 1
fi




echo "***********************************"
echo "* Setting up environment variables"
echo "***********************************"

TEMPDIR=`pwd`/tmp
UNZIP="${TC_ROOT}/install/install/unzip"
export TC_no_obsolete_message=Y

echo "done"


$UNZIP -l ${DMDIR}/${TEMPLATE}_template.zip | grep "install/${TEMPLATE}/client_${TEMPLATE}.properties" >/dev/null
rtn=$?

if test ${rtn} -eq 0
then
        echo "This script cannot be used for operation-data deploys"
        exit 1
fi






echo "***********************************"
echo "* Unzip files"
echo "***********************************"

${UNZIP} -o -d"${TC_ROOT}" ${DMDIR}/${TEMPLATE}_install.zip 
rtn=$?
if test ${rtn} -ne 0
then
        echo "Unzip failed"
        exit 1
fi

${UNZIP} -o -d"${TC_ROOT}" ${DMDIR}/${TEMPLATE}_template.zip 
rtn=$?
if test ${rtn} -ne 0
then
        echo "Unzip failed"
        exit 1
fi


echo "***********************************"
echo "* Source tc_profilevars"
echo "***********************************"

. ${TC_DATA}/tc_profilevars
echo "done"


echo "Teamcenter version:  `${TC_ROOT}/bin/install -ask_version`"
${TC_ROOT}/bin/install -ask_version|grep "11000.2" >/dev/null

rtn=$?
if test ${rtn} -ne 0
then
        echo "This script only works with Teamcenter 11.2.x"
        exit 1
fi


echo "***********************************"
echo "* Manage model files"
echo "***********************************"

manage_model_files -u=infodba -p=${TC_USER_PASSWD} -g=dba -force=model -option=download
rtn=$?
if test ${rtn} -ne 0
then
	echo "Manage model files: ${rtn}"
	exit 1
fi

echo "***********************************"
echo "* Copy files"
echo "***********************************"

fn=feature_${TEMPLATE}.xml 
if test -f ${DMDIR}/${fn}
then
	echo "Copy ${fn}"
	cp ${DMDIR}/${fn} ${TC_ROOT}/install/install/modules
fi

fn=client_${TEMPLATE}.properties 
if test -f ${DMDIR}/${fn}
then
	echo "Copy ${fn}"
	cp ${DMDIR}/${fn} ${TC_ROOT}/install/${TEMPLATE}
fi

echo "Copy language files..."
if ! test -d ${TC_ROOT}/install/${TEMPLATE}/lang
then
	mkdir ${TC_ROOT}/install/${TEMPLATE}/lang 
fi

for lang in en_US zh_CN zh_TW de_DE fr_FR ja_JP it_IT ko_KR es_ES ru_RU pl_PL cs_CZ
do
	fn=${TEMPLATE}Bundle_${lang}.xml
	if test -f ${DMDIR}/${fn}
	then
		echo "Copy ${fn}"
		cp ${DMDIR}/${fn} ${TC_ROOT}/install/${TEMPLATE}/lang/${fn}
	fi
done


echo "***********************************"
echo "* Update TC_DATA/model"
echo "***********************************"

echo "TC ROOT - ${TC_ROOT}"
echo "TC DATA - ${TC_DATA}"
echo "TC DATA MODEL Path - ${TC_DATA_MODEL}"

fn=${TEMPLATE}_template.xml
if test -f ${TC_ROOT}/install/${TEMPLATE}/${fn}
then
	echo "Copy ${fn}"
	cp ${TC_ROOT}/install/${TEMPLATE}/${fn} ${TC_DATA_MODEL}
fi

fn=${TEMPLATE}_dependency.xml
if test -f ${TC_ROOT}/install/${TEMPLATE}/${fn}
then
	echo "Copy ${fn}"
	cp ${TC_ROOT}/install/${TEMPLATE}/${fn} ${TC_DATA_MODEL}
fi

fn=${TEMPLATE}_tcbaseline.xml
if test -f ${TC_ROOT}/install/${TEMPLATE}/${fn}
then
	echo "Copy ${fn}"
	cp ${TC_ROOT}/install/${TEMPLATE}/${fn} ${TC_DATA_MODEL}/baselines
fi

fn=client_${TEMPLATE}.properties
if test -f ${TC_ROOT}/install/${TEMPLATE}/${fn}
then
	echo "Copy ${fn}"
	cp ${TC_ROOT}/install/${TEMPLATE}/${fn} ${TC_DATA_MODEL}
fi

echo "Copy language files"
cp ${TC_ROOT}/install/${TEMPLATE}/lang/* ${TC_DATA_MODEL}/lang



echo "***********************************"
echo "* Running update_runner"
echo "***********************************"

update_runner.sh -u=infodba -p=${TC_USER_PASSWD} -g=dba -templates=${TEMPLATE} -isLiveUpdate=false -log=${TC_ROOT}/logs/update_runner.log
rtn=$?
if test ${rtn} -ne 0
then
	echo "Updating template failed: ${rtn}"
	exit 1
fi


echo "***********************************"
echo "* Update PLM XML schema"
echo "***********************************"

bmide_generatetcplmxmlschema.sh -u=infodba -p=${TC_USER_PASSWD} -g=dba
rtn=$?
if test ${rtn} -ne 0
then
	echo "Generating PLMXML schema failed: ${rtn}"
	exit 1
fi

echo "***********************************"
echo "* Update knowledge base"
echo "***********************************"

bmide_setupknowledgebase.sh -u=infodba -p=${TC_USER_PASSWD} -g=dba -regen=false
rtn=$?
if test ${rtn} -ne 0
then
	echo "Update of the knowledge base failed: ${rtn}"
	exit 1
fi

echo "***********************************"
echo "* Regenerating metadata cache"
echo "***********************************"
generate_metadata_cache -u=infodba -p=${TC_USER_PASSWD} -g=dba -force
rtn=$?
if test ${rtn} -ne 0
then
	echo "Command failed: ${rtn}"
	exit 1
fi

echo "***********************************"
echo "* Regenerating client meta cache"
echo "***********************************"
#
#  If your site does not use client meta cache, then change "generate all" to "delete" in 
#  the following command
#
generate_client_meta_cache generate all -u=infodba -p=${TC_USER_PASSWD} -g=dba
rtn=$?
if test ${rtn} -ne 0
then
	echo "Command failed: ${rtn}"
	exit 1
fi

echo "Update complete"
