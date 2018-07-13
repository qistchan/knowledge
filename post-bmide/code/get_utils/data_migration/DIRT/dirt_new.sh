# *****************************************************
# DIRT QUERIES
# 
# Add any query file to SQL folder with extension .sql and it will be executed and output will
# be stored in OUTPUT folder
# Use tnsnames.ora and ora_env.sh to configure Oracle paths and login/password for a read only account access to infodba account
# 
# 
# Location : /package/ugiman/ug/utilities
# *****************************************************
#**********************************************************
#******************************************************
# *****************************************************
#******************************************************
date
echo	"**********************************************************"
echo 	"*****          Procedure DIRT Started                 ******"
echo 	"**********************************************************"
DIRT_ROOT=/package/ugiman/ug/utilities; export DIRT_ROOT
DIRT_HOME=$DIRT_ROOT/DIRT; export DIRT_HOME
DIRT_SQL=$DIRT_HOME/SQL; export DIRT_SQL
. $DIRT_HOME/ora_env.sh
#. ora_env.sh

# FILE='/package/ugiman/ug/utilities/DIRT/empty_dataset.txt'
cd $DIRT_SQL
for sqlfile in $DIRT_SQL/*.sql
do
# "$file"
# $ORACLE_HOME/bin/sqlplus sso212441909/test1234@getcmigd <<ENDOFINPUT
$ORACLE_HOME/bin/sqlplus<<ENDOFSQL
$ORACLE_UID/$ORACLE_PWD@getcmigd
set echo off;
set space 0;
set pagesize 50000
set feedback off;
set trimspool on;
set verify off;
set term off;
column PITEM_ID FORMAT A30;
column ITEM2 FORMAT A30;
column POBJECT_NAME FORMAT A40;
column PUID format A20;
column PITEM_REVISION_ID format a20
column POBJECT_TYPE format a30
column POS_USERNAME format a20
column PNAME format a20   
spool $DIRT_HOME/OUTPUT/$(basename "$sqlfile" .sql).txt
@"$sqlfile"
spool off;
ENDOFSQL
done
exit;

