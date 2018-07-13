#!/bin/sh
# Set Oracle Home
ORACLE_HOME=/opt/oracle/product/10.2.0; export ORACLE_HOME
TNS_ADMIN=/package/ugiman/ug/utilities/DIRT; export TNS_ADMIN

# Set LD Library Path
LD_LIBRARY_PATH=${ORACLE_HOME}/lib:${LD_LIBRARY_PATH}; export LD_LIBRARY_PATH

# Database Name

# Development
#ORACLE_SID=tsimdev1; export ORACLE_SID
# DM1
ORACLE_SID=getplmd22; export ORACLE_SID

# Oracle User Name

ORACLE_UID=sso212441909; export ORACLE_UID

# Oracle Password

ORACLE_PWD=<passwordneeded>; export ORACLE_PWD

