
/*=============================================================================

                       Copyright (c) 2015 GE Transportation
                       Unpublished - All rights reserved

=============================================================================
File description:

     Filename    : GET5_OCCI.h
     
     Description : Header File for OCCI framework

     Date            Name                         Remarks
     05-APR-2016     TCS                          Created
===========================================================================*/
/*
#ifndef GET_OCCI_H
#define GET_OCCI_H

#ifdef WIN32
    #define DLLEXPORT __declspec(dllexport)
    #define DLLIMPORT __declspec(dllimport)
#elif WIN64
    #define DLLEXPORT __declspec(dllexport)
    #define DLLIMPORT __declspec(dllimport)
#else
    #define DLLEXPORT
    #define DLLIMPORT
#endif

// C++ Includes
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <exception>

// Oracle Includes
#include <occi.h>
#include "GET_OCCI_Includes.h"
#include "GET_ResultSet.h"

#pragma warning(disable:4251)

using namespace std;
using namespace oracle::occi;
using namespace get;

namespace get
{
class DLLEXPORT GET_Statement
{
	friend class GET_OCCI;
	protected:

		shared_ptr<Statement> statement;
	public:
		GET_Statement(){};
		GET_Statement(shared_ptr<Statement> statement);

		virtual ~GET_Statement(){};
		
		void addIteration();
		template <typename T> void setBindValue(int index, T& value, Type type);
		void executePrepared();
};

class DLLEXPORT GET_OCCI
{
	protected:
		shared_ptr<Connection> connection;
		shared_ptr<Environment> environment;
		shared_ptr<GET_Statement> statement;
		shared_ptr<GET_ResultSet> resultSet;

		string user;
		string password;
		string db;

	public:
		GET_OCCI();
		GET_OCCI(string user, string password, string db);
		virtual ~GET_OCCI();

		void setUser(string user);
		void setPassword(string password);
		void setDb(string db);

		virtual void createConnection();
		virtual shared_ptr<Connection> getConnection();
		shared_ptr<GET_ResultSet> executeSelect(string sql);
		void commit();
		void execute(string sql);
		shared_ptr<GET_Statement> prepare(string sql);
};
}
#endif
*/
