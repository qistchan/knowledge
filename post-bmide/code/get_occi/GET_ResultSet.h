#ifndef	__GET_RESULTSET_H__
#define	__GET_RESULTSET_H__

// C++ Includes
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <exception>

// Oracle Includes
#include <occi.h>
#include <occiCommon.h>
#include <assert.h>
#ifndef	ASSERT
#	define	ASSERT	assert
#endif


#pragma warning(disable:4251)

using namespace std;
using namespace oracle::occi;

namespace get
{
class DLLEXPORT GET_ResultSet
{
friend class GET_OCCI;

private:
	bool isDescribed;
	bool isDefined;

private:
	GET_ResultSet();

	void describe();
	size_t rowsCount();
	size_t noOfColumns();
	map<string, int> columnIndexMap;
	map<int, int> columnTypeMap;
	ResultSet* resultSet;

public:
	~GET_ResultSet(){};
	GET_ResultSet(ResultSet* resultSet);

	// skip to next row; returns false if current one is the last
	inline bool operator++ ()
	{
		return(next() );
	};
	bool next (void);
	template <typename T> void getValue(int index, T& value);
	template <typename T> void getValue(const string columnName, T& value);
};

template <typename T>
void GET_ResultSet::getValue(int index, T& value)
{
	int type = columnTypeMap[index];

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
		value = resultSet->getNumber( index );
		break;

	case OCCI_SQLT_ODT:
	case OCCI_SQLT_DATE: //value = resultSet->getDate( index );break;

	 case OCCI_SQLT_CHR:
	 case OCCI_SQLT_STR:
	 case OCCI_SQLT_VCS:
	 case OCCI_SQLT_AFC:
	 case OCCI_SQLT_AVC:
	 case OCCI_SQLT_VST: value = resultSet->getString( index );
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
	 //case OCCI_SQLT_BFILE: SQLT_BFILE*/
	}
}

template <typename T>
void GET_ResultSet::getValue(const string columnName, T& value)
{
	getValue( columnIndexMap[columnName], value);

}
}


#endif	// __GET_RESULTSET_H__
