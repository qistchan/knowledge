#!/bin/sh
##########################################################################################
# Name          : get6DrsPush.sh
# Description   : This script is used to push files to DRS directory
# Who                       When                    What
# TCS Development Team     31-July-2017            Created sh to push files to DRS directory
#
#########################################################################################
echo GET6DrsFilePush Start

echo $PWD
export currentfolder=$PWD
echo $currentfolder

export DISP_ROOT=CHANGEME

export SRCINPUTDIR=$1
echo $SRCINPUTDIR

export SRCOUTPUTDIR=CHANGEME

export ITEMID=$3
echo $ITEMID

export REVID=$4
echo $REVID

export ENVIRONMENT=CHANGEME
echo $ENVIRONMENT

export ResponseCode=0

java -jar $DISP_ROOT/Module/Translators/get6DrsPush/GET6DRSFilePush.jar $SRCINPUTDIR $SRCOUTPUTDIR $ITEMID $REVID $ENVIRONMENT

echo GET6DrsFilePush End

