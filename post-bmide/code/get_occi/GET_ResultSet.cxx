/*=============================================================================

 Copyright (c) 2015 GE Transportation
 Unpublished - All rights reserved

 =============================================================================
 File description:

 Filename    : GET_ResultSet.cpp

 Description : Result Set Class CPP File

 Date            Name                         Remarks
 05-Apr-2016     TCS                          Created
 ===========================================================================*/

// C++ Includes
#include <algorithm>
#include <fstream>
#include <sstream>

#include <stdexcept>

#include "GET_OCCI_Includes.h"
#include "GET_ResultSet.h"

using namespace get;
using namespace oracle::occi;

GET_ResultSet::GET_ResultSet(ResultSet* resultSet)
{
	this->resultSet = resultSet;
	describe();
	isDescribed = true;
	isDefined = false;
}

size_t GET_ResultSet::noOfColumns()
{
	return resultSet->getColumnListMetaData().size();
}

size_t GET_ResultSet::rowsCount ()
{
	size_t rowCount;
	//to do
	return rowCount;
}

bool GET_ResultSet::next (void)
{
	// prerequisites
	ASSERT (isDescribed);

	return resultSet->next();
}
void GET_ResultSet::describe ()
{
    if (resultSet)
    {
		vector<MetaData> metaDataVector = resultSet->getColumnListMetaData();
		for ( size_t index = 0; index < metaDataVector.size(); index++ )
		{
			string columnName = metaDataVector[index].getString ( MetaData::ATTR_NAME );
			unsigned short columnType = metaDataVector[index].getInt(MetaData::ATTR_DATA_TYPE);
			unsigned short size = metaDataVector[index].getInt(MetaData::ATTR_DATA_SIZE);
			columnTypeMap[index + 1] = columnType;
			columnIndexMap[columnName] = ( index + 1 );

		}
    }

	isDescribed = true;
}
