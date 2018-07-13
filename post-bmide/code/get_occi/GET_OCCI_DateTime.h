#ifndef	_GET_DATETIME_H_
#define	_GET_DATETIME_H_

// Oracle Includes
#include <occi.h>
#include <occiCommon.h>

using namespace oracle::occi;

namespace get
{

enum MonthsEnum
{
	jan = 1,
	feb,
	mar,
	apr,
	may,
	jun,
	jul,
	aug,
	sep,
	oct,
	nov,
	dec
};

class GET_OCCI_DateTime
{
private:
	sb2	y;
	MonthsEnum	m;
	ub1 d;
	ub1 h;
	ub1 i;
	ub1 s;

public:
	inline GET_OCCI_DateTime(void){};

	inline GET_OCCI_DateTime(ub1 dd, MonthsEnum mm, ub2 yyyy, ub1 hh = 0, ub1 mi = 0,
		ub1 ss = 0) : y (yyyy), m (mm), d (dd), h (hh), i (mi), s (ss)
		{ };

	inline GET_OCCI_DateTime(const OCIDate& o)
		{ operator = (o); };

public:
	inline ub1 day (void) const { return (d); };
	inline void day (ub1 dd)
	{
		d = dd;
	}

	inline MonthsEnum mon(void) const
	{
		return (m);
	}
	inline void mon(MonthsEnum mm)
	{
		m = mm;
	};

	inline sb2 year (void) const
	{
		return (y);
	}
	inline void year(sb2 yy)
	{
		y = yy;
	}

	inline ub1 hour (void) const
	{
		return (h);
	}
	inline void hour(ub1 hh)
	{
		h = hh;
	}

	inline ub1 minute(void) const
	{
		return (i);
	}
	inline void minute(ub1 mi)
	{
		i = mi;
	}

	inline ub1 sec (void) const
	{
		return (s);
	}
	inline void sec(ub1 ss)
	{
		s = ss;
	}

	inline GET_OCCI_DateTime& operator= (const OCIDate& o)
	{
		y = o.OCIDateYYYY;
		m = (MonthsEnum) (o.OCIDateMM);
		d = o.OCIDateDD;
		h = o.OCIDateTime.OCITimeHH;
		i = o.OCIDateTime.OCITimeMI;
		s = o.OCIDateTime.OCITimeSS;
		return (*this);
	};
	inline void set(OCIDate& o) const
	{
		o.OCIDateYYYY = y;
		o.OCIDateMM = static_cast<ub1> (m);
		o.OCIDateDD = d;
		o.OCIDateTime.OCITimeHH = h;
		o.OCIDateTime.OCITimeMI = i;
		o.OCIDateTime.OCITimeSS = s;
	};

};
}

#endif // _GET_DATETIME_H_
