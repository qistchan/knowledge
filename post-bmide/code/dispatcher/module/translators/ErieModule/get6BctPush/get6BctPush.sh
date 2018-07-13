#!/bin/sh
##########################################################################################
# Name          : get6BctPush.sh
# Description   : This script is used to push files to BCT directory
# Who                       When                    What
# TCS Development Team     31-July-2017            Created sh to push files to BCT directory
#
#########################################################################################

echo GET6BctPushModule Start

echo $PWD
export currentfolder=$PWD
echo $currentfolder

export DISP_ROOT=CHANGEME

export SRCINPUTDIR=$1
echo $SRCINPUTDIR$

export SRCOUTPUTDIR=CHANGEME
echo $SRCOUTPUTDIR

export ITEMID=$3
echo $itemID

export REVID=$4
echo $REVID

export ENVIRONMENT=CHANGEME
echo $Environment

java -jar $DISP_ROOT/Module/Translators/get6BctPush/GET6BctPushModule.jar $SRCINPUTDIR $SRCOUTPUTDIR $ITEMID $REVID $ENVIRONMENT
echo GET6BctPushModule End

