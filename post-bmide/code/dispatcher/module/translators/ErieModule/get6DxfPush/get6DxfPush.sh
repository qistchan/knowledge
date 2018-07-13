#!/bin/sh
##########################################################################################
# Name          : get6DxfPush.sh
# Description   : This script is used to push files to DXF directory
# Who                       When                    What
# TCS Development Team     31-July-2017            Created sh to push files to DXF directory
#
#########################################################################################

echo GET6DxfFilePush Start


echo $PWD
export currentfolder=$PWD
echo currentfolder

export DISP_ROOT=CHANGEME
export SRCINPUTDIR=$1
echo SRCINPUTDIR

export SRCOUTPUTDIR=CHANGEME

java -jar $DISP_ROOT/Module/Translators/get6DxfPush/GET6DxfFilePush.jar $SRCINPUTDIR $SRCOUTPUTDIR
echo GET6DxfFilePush End