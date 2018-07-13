#!/bin/sh
##########################################################################################
# Name          : get_automatic_ecr_close.ksh
# Description   : This script is used to CR auto close process automatically once CR is approved by the final reviewer
# Who                       When                    What
# TCS Development Team     02-June-2017            Created Ksh to call the get_automatic_ecr_close executable to close the CRs
#
#########################################################################################

export base_dir=CHANGE_ME

export MAIL_LIST=CHANGE_ME

#Source tc_local_setup
export TC_ROOT=CHANGE_ME
export TC_DATA=CHANGE_ME
. $TC_DATA/tc_profilevars

#Some basic constants
export LOGFILE="${base_dir}/get_automatic_ecr_close_runlog"


echo "***************" >> $LOGFILE
echo `date` >> $LOGFILE 
echo "" >> $LOGFILE

if [ $NO_OF_INPUTS -le 0 ]; then {
     echo "None to process" >> $LOGFILE
     echo `date` >> $LOGFILE
     exit
};fi 


#Do not start the cron job if previous process is running
i=`/usr/bin/pgrep -x get_automatic_ecr_close |wc -l`

if [ $i -gt 1 ]
then
	time=`date +%H:%M:%S`
	mailx -s "One or More than one get_automatic_ecr_close is running at $time" $MAIL_LIST  
        echo "One or More than one get_automatic_ecr_close is running at $time" >> $LOGFILE
	echo `date` >> $LOGFILE
	exit
fi

#call the utility
${base_dir}/get_automatic_ecr_close -u=CHANGE_ME -p=CHANGE_ME -g=dba >> $LOGFILE
if [ $? -ne 0 ]
then
	retcode=1
	time=`date +%H:%M:%S`
	mailx -s "Error: get_automatic_ecr_close process returned $retcode at $time" $MAIL_LIST 
else
	retcode=0
fi

echo "" >> $LOGFILE
echo `date` >> $LOGFILE
echo "" >> $LOGFILE
