/*=============================================================================

 Copyright (c) 2015 GE Transportation
 Unpublished - All rights reserved

 =============================================================================
 File description:

 Filename    : GET_OCCI.cpp

 Description : OCCI Class CPP File

 Date            Name                         Remarks
 05-Apr-2016     TCS                          Created
 ===========================================================================*/
/*
// C++ Includes
#include <algorithm>
#include <fstream>
#include <sstream>

#include <stdexcept>

#include "GET_OCCI.h"

using namespace get;

GET_OCCI::GET_OCCI(string user, string password, string db) : user(user), password(password), db(db)
{

}

GET_OCCI::~GET_OCCI()
{
	// Terminate the Staging DB Connection and the OCCI environment
    if ( environment != NULL && connection != NULL )
    {
		environment->terminateConnection ( connection.get() );
		Environment::terminateEnvironment ( environment.get() );
    }
}

void GET_OCCI::setUser(string user)
{
	this->user = user;
}

void GET_OCCI::setPassword(string password)
{
	this->password = password;
}

void GET_OCCI::setDb(string db)
{
	this->db = db;
}

shared_ptr<Connection> GET_OCCI::getConnection()
{
	return shared_ptr<Connection> ( this->connection );
}

void GET_OCCI::createConnection()
{
	try 
	{ 
		//environment = shared_ptr<Environment>( Environment::createEnvironment( Environment::DEFAULT ) );
		//environment = Environment::createEnvironment( Environment::DEFAULT );
		Environment *environment;
		environment = Environment::createEnvironment ( Environment::DEFAULT );
		cout<<"user name : "<<user<<"\npassword: "<<password<<"\ndb: "<<db<<endl;
		connection = shared_ptr<Connection>( environment->createConnection( user.c_str(), password.c_str(), db.c_str() ) );
	}
	catch ( exception& ex ) 
	{
		cout<<"error is : "<<ex.what()<<endl;
		int no;
		cin>>no;
		throw ex;
    }
}

shared_ptr<GET_ResultSet> GET_OCCI::executeSelect( string sql )
{
  unique_ptr<Statement> statement; 
  shared_ptr<ResultSet> rs;
  shared_ptr<GET_ResultSet> resSet;
  cout<<"Inside executeSelect"<<endl;
  try
  { 
    statement = unique_ptr<Statement>( connection->createStatement( sql ) ); 
  } 
  catch ( SQLException& ex ) 
  {
    cout << ex.getMessage(); 
  }

  if (statement) 
  { 
    try 
    {
		rs = shared_ptr<ResultSet>( statement->executeQuery() );

		resSet = shared_ptr<GET_ResultSet> ( new GET_ResultSet( rs.get() ) );
    }
    catch (SQLException& ex) 
    { 
		cout << ex.getMessage(); 
    }

	ASSERT(rs);

	statement->closeResultSet( rs.get() );

    connection->terminateStatement( statement.get() );
  }
  return resSet;

}

void GET_OCCI::commit()
{
	connection->commit();
}

void GET_OCCI::execute(string sql)
{
	unique_ptr<Statement> statement;
	try
	{
		statement->setSQL(sql);
		statement->execute();
	}
	catch(SQLException &ex)
	{
		throw ex;
	}
}


shared_ptr<GET_Statement> GET_OCCI::prepare(string sql)
{
	statement->statement->setSQL(sql);
	return this->statement;
}

template <typename T> void GET_Statement::setBindValue(int index, T& value, Type type)
{
	switch (type)
	{
	case OCCIINT:
	case OCCIUNSIGNED_INT:
	case OCCI_SQLT_LNG:
	case OCCI_SQLT_NUM:

	case OCCIFLOAT:
	case OCCIBFLOAT:
	case OCCIIBFLOAT:

	case OCCIBDOUBLE:
	case OCCIIBDOUBLE:

	case OCCI_SQLT_VNU:
	case OCCI_SQLT_PDN:
		statement->setNumber(index, value);
		break;

	case OCCI_SQLT_ODT:
	case OCCI_SQLT_DATE:
		statement->setDate(index, value);
		break;

	 case OCCI_SQLT_CHR:
	 case OCCI_SQLT_STR:
	 case OCCI_SQLT_VCS:
	 case OCCI_SQLT_AFC:
	 case OCCI_SQLT_AVC:
	 case OCCI_SQLT_VST:
		 statement->setString(index, value);
		 break;

	/*case OCCI_SQLT_NON: SQLT_NON,
	 case OCCI_SQLT_RID: SQLT_RID,
	 case OCCI_SQLT_DAT: SQLT_DAT,
	 case OCCI_SQLT_VBI: SQLT_VBI,
	 case OCCI_SQLT_BIN: SQLT_BIN,
	 case OCCI_SQLT_LBI: SQLT_LBI,
	 
	 case OCCI_SQLT_SLS: SQLT_SLS,
	 case OCCI_SQLT_LVC: SQLT_LVC,
	 case OCCI_SQLT_LVB: SQLT_LVB,
	
	 case OCCI_SQLT_CUR: SQLT_CUR,
	 case OCCI_SQLT_RDD: SQLT_RDD,
	 case OCCI_SQLT_LAB: SQLT_LAB,
	 case OCCI_SQLT_OSL: SQLT_OSL,
	 case OCCI_SQLT_NTY: SQLT_NTY,
	 case OCCI_SQLT_REF: SQLT_REF,
	 case OCCI_SQLT_CLOB: SQLT_CLOB,
	 case OCCI_SQLT_BLOB: SQLT_BLOB,
	 case OCCI_SQLT_BFILEE: SQLT_BFILEE,
	 case OCCI_SQLT_CFILEE: SQLT_CFILEE,
	 case OCCI_SQLT_RSET: SQLT_RSET,
	 case OCCI_SQLT_NCO:SQLT_NCO,
	 ,
	 
	 //case OCCI_SQLT_TIME: SQLT_TIME,
	 //case OCCI_SQLT_TIME_TZ: SQLT_TIME_TZ,
	 //case OCCI_SQLT_TIMESTAMP: SQLT_TIMESTAMP,
	 //case OCCI_SQLT_TIMESTAMP_TZ: SQLT_TIMESTAMP_TZ,
	 //case OCCI_SQLT_INTERVAL_YM: SQLT_INTERVAL_YM,
	 //case OCCI_SQLT_INTERVAL_DS: SQLT_INTERVAL_DS,
	 //case OCCI_SQLT_TIMESTAMP_LTZ: SQLT_TIMESTAMP_LTZ,
	 //case OCCI_SQLT_FILE: SQLT_FILE,
	 //case OCCI_SQLT_CFILE: SQLT_CFILE,
	 //case OCCI_SQLT_BFILE: SQLT_BFILE
	}
}

void GET_Statement::executePrepared()
{
	statement->executeUpdate();
}

void GET_Statement::addIteration()
{
	statement->addIteration();
}

GET_Statement::GET_Statement(shared_ptr<Statement> statement)
{
	this->statement = statement;
}
*/
