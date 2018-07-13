
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Dataset.cxx
//
//    Purpose:   Class for dealing with the Date class
//    
//    History:
//      Who                          Date                 Description
//  TCS Development Team           26 Mar, 2016         Initial creation
//  Capgemini Development Team     29 Mar, 2017         Added new method definitions for getCurrentDate, compareTo, getDayDifferent method
//  TCS Development Team           31 May, 2017         Renamed the compareTo method to compare and getDayDifference to getDifferenceInDays
//
//   ============================================================================
// ENDFILEDOC   ***/

// GE Includes
#include <GET_Date.hxx>
#include <GET_cpp_stl.h>
#include <GET_Exception.hxx>
#include <GET_TC_Logger.hxx>
#include <GET_Utils.hxx>
#include <GET_sysapi.h>
#include <base_utils/ResultCheck.hxx>
#include <base_utils/IFail.hxx>

// TC Includes
#include <fclasses/tc_date.h>
#include <unidefs.h>
#include <property/prop_errors.h>
#include <tc/tc_startup.h>

// Include files related to date & time functionality
#include <time.h>
#include <ctime>

const string logger = "get.get_tc_common.GET_Date";

namespace get
{
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_Date()
    //
    //   Purpose :   Constructor for the GET_Date class
    //
    //   Inputs  :   dtDate - The Teamcenter Date structure (date_t)
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     30 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_Date::GET_Date ( const date_t dtDate )
    {
        this->dtTCDate = dtDate;
    };

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   GET_Date()
    //
    //   Purpose :   Destructor for the GET_Date class
    //
    //   Inputs  :   none
    //
    //   Outputs :   none
    //
    //   Return  :   none
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     30 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_Date::~GET_Date() {};

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:  toString()
     //
     //   Purpose :  Converts a date_t structure into a text representation.
     //              The date is formatted according to the DefaultDateFormat string defined in time.uil.
     //
     //   Inputs  :  none
     //
     //   Outputs :  none
     //
     //   Return  :  the date_t structure formatted
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     30 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_Date::toString() const
    {
        char *pcDateString = NULL;

        ResultCheck stat;

        string sDateString = "";

        LOG_TRACE ( logger, "START : GET_Date::toString" );

        stat = ITK_date_to_string ( dtTCDate, &pcDateString );

        if ( pcDateString != NULL )
        {
            sDateString = pcDateString;
            MEM_free ( pcDateString );
        }

        LOG_TRACE ( logger, "END : GET_Date::toString" );

        return sDateString;
    }

     /*STARTFUNCDOC ***
     //
     ===========================================================================
     //   Function:  toString ( sDateFormat )
     //
     //   Purpose :  Converts a date_t structure into a text representation as per
     //              the format required
     //
     //   Inputs  :  sDateFormat - The Date Format required
     //
     //   Outputs :  none
     //
     //   Return  :  the date_t structure formatted into a string
     //
     //   History :
     //      Who                   Date                 Description
     //  TCS Development Team     30 Mar, 2016         Initial creation
     //
     ===========================================================================
     //ENDFUNCDOC   ***/
    string GET_Date::toString ( const string sDateFormat ) const
    {
        char *pcDateString = NULL;

        ResultCheck stat;

        string sDateString = "";

        LOG_TRACE ( logger, "START : GET_Date::toString(sDateFormat)" );

        stat = DATE_date_to_string ( dtTCDate, sDateFormat.c_str(), &pcDateString);

        if ( pcDateString != NULL )
        {
            sDateString = pcDateString;
            MEM_free ( pcDateString );
        }

        LOG_TRACE ( logger, "END : GET_Date::toString(sDateFormat)" );

        return sDateString;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function: compare ( datePtr )
    //
    //   Purpose : Compares two dates for equality
    //
    //   Inputs  : datePtr - GET_Date smart pointer instance to be compared with
    //
    //   Outputs : none
    //
    //   Return  : 0 if dates are equal
    //             1 if this date is later than given date
    //             -1 if this date is earlier than given date
    //
    //   History :
    //      Who                           Date                 Description
    //  Capgemini Development Team     27 May, 2017         Initial creation
    //  TCS Development Team           31 May, 2017         Renamed the method to compare
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    int GET_Date::compare ( const GET_DateShrPtr datePtr )
    {
        ResultCheck stat;

        int iRetValue = -2;

        LOG_TRACE ( logger, "START : GET_Date::compareTo" );

        stat = POM_compare_dates ( dtTCDate, datePtr->getDate(), &iRetValue );

        LOG_TRACE ( logger, "END : GET_Date::compareTo" );

        return iRetValue;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:  getDifferenceInDays ( datePtr )
    //
    //   Purpose :  Get the difference in days between this date and the given date
    //
    //   Inputs  :  datePtr - Date
    //
    //   Outputs :  none
    //
    //   Return  :  (double) Difference in days between two dates
    //
    //   History :
    //      Who                           Date                 Description
    //  Capgemini Development Team     29 May, 2017         Initial creation
    //  TCS Development Team           31 May, 2017         Renamed the method to getDifferenceInDays
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    double GET_Date::getDifferenceInDays ( const GET_DateShrPtr datePtr )
    {
        date_t dtDate = NULLDATE;

        double dDifferenceInDays = 0;

        int iRelativeYear = 0;
        int iCompareDate = 0;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Date::getDayDifference(const GET_DateShrPtr datePtr)" );

        iCompareDate = compare ( datePtr );
        if ( iCompareDate != 0 )
        {
            iRelativeYear = dtTCDate.year - 1900;
            struct tm timeOne = { 0, dtTCDate.minute, dtTCDate.hour, dtTCDate.day, dtTCDate.month, iRelativeYear };

            iRelativeYear = datePtr->getDate().year - 1900;
            struct tm timeTwo = { 0, datePtr->getDate().minute, datePtr->getDate().hour, datePtr->getDate().day, datePtr->getDate().month, iRelativeYear };

            //Find difference in days between two dates
            time_t totalTimeOne = mktime ( &timeOne );
            time_t totalTimeTwo = mktime ( &timeTwo );
            if ( totalTimeOne != (time_t)(-1) && totalTimeTwo != (time_t)(-1) )
            {
                dDifferenceInDays = difftime ( totalTimeOne, totalTimeTwo ) / ( 60 * 60 * 24 );
            }
        }

        LOG_TRACE ( logger, "END : GET_Date::getDayDifference(const GET_DateShrPtr datePtr)" );

        return dDifferenceInDays;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function: getInstance ( dtDate )
    //
    //   Purpose : Get the Teamcenter Date Instance for the given date
    //
    //   Inputs  : dtDate - The Teamcenter date_t structure
    //
    //   Outputs : none
    //
    //   Return  : The GET_Date Smart Pointer object
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     30 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DateUnqPtr GET_Date::getInstance ( const date_t dtDate )
    {
        return make_unique<GET_Date> ( dtDate );
    };

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:  getInstance ( sDateString )
    //
    //   Purpose :  Get the Teamcenter Date Instance for the given date using the default date format
    //
    //   Inputs  :  sDateString - The string to be convert as date
    //
    //   Outputs :  none
    //
    //   Return  :  The GET_Date Smart Pointer object
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     30 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DateUnqPtr GET_Date::getInstance ( const string sDateString )
    {
        date_t dtDate = NULLDATE;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Date::getInstance(sDateString)" );

        stat = ITK_string_to_date ( sDateString.c_str(), &dtDate );

        LOG_TRACE ( logger, "END : GET_Date::getInstance(sDateString)" );

        return getInstance ( dtDate );
    };

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:  getInstance ( sDateString, sDateFormat )
    //
    //   Purpose :  Get the Teamcenter Date Instance for the given date string and format
    //
    //   Inputs  :  sDateString - The string to be convert as date
    //              sDateFormat - The format of the input date
    //
    //   Outputs :  none
    //
    //   Return  :  The GET_Date Smart Pointer object
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     30 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DateUnqPtr GET_Date::getInstance ( const string sDateString, const string sDateFormat )
    {
        date_t dtDate = NULLDATE;

        int      month      = 0;          // Month
        int      day        = 0;          // Day
        int      year       = 0;          // Year
        int      hour       = 0;          // Hour
        int      minute     = 0;          // Minutes
        int      second     = 0;          // Seconds

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Date::getInstance(sDateString, sDateFormat)" );

        // Converts a date_t structure into the format specified
        stat = DATE_string_to_date ( sDateString.c_str(), sDateFormat.c_str(), &month, &day,
                                        &year, &hour, &minute, &second);

        dtDate.year = year;
        dtDate.month = month;
        dtDate.day = day;
        dtDate.hour = hour;
        dtDate.minute = minute;
        dtDate.second = second;

        LOG_TRACE ( logger, "END : GET_Date::getInstance(sDateString, sDateFormat)" );

        return getInstance ( dtDate );
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:  getInstance ( year, month, day, hour, minute, second )
    //
    //   Purpose :  Get the Teamcenter Date Instance for the year, month, day, hour, minute, second values
    //
    //   Inputs  :  iYear   - The integer corresponding to Year
    //              iMonth  - The integer corresponding to Month
    //              iDay    - The integer corresponding to Day
    //              iHour   - The integer corresponding to Hour
    //              iMinute -The integer corresponding to Minute
    //              iSecond - The integer corresponding to Second
    //
    //   Outputs :  none
    //
    //   Return :   The GET_Date Smart Pointer object
    //
    //  History :
    //      Who                   Date                 Description
    //  TCS Development Team     30 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DateUnqPtr GET_Date::getInstance ( const int iYear, const int iMonth, const int iDay, const int iHour, const int iMinute, const int iSecond )
    {
        date_t dtDate = NULLDATE;

        dtDate.year = iYear;
        dtDate.month = iMonth;
        dtDate.day = iDay;
        dtDate.hour = iHour;
        dtDate.minute = iMinute;
        dtDate.second = iSecond;

        return getInstance ( dtDate );
    };

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function: isValid ( sDateString, sDateFormat )
    //
    //   Purpose : Checks whether the given date matches the format provided
    //
    //   Inputs  : sDateString - The string form of the date to be checked
    //             sDateFormat - The format of the input date
    //
    //   Outputs : none
    //
    //   Return  : boolean indicating valid or not (true/false)
    //
    //   History :
    //      Who                   Date                 Description
    //  TCS Development Team     30 Mar, 2016         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    bool GET_Date::isValid ( const string sDateString, const string sDateFormat )
    {
        bool bIsDateValid = true;

        int      iYear       = 0;          // Year
        int      iMonth      = 0;          // Month
        int      iDay        = 0;          // Day
        int      iHour       = 0;          // Hour
        int      iMinute     = 0;          // Minutes
        int      iSecond     = 0;          // Seconds

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Date::isValid" );

        try
        {
            // Converts a date_t structure into the format specified
            stat = DATE_string_to_date ( sDateString.c_str(), sDateFormat.c_str(), &iMonth, &iDay,
                                            &iYear, &iHour, &iMinute, &iSecond );
        }
        catch ( IFail &ex )
        {
            if ( ex.ifail() == PROP_invalid_date_format )
            {
                bIsDateValid = false;
            }
            else
            {
                throw ex;
            }
        }

        LOG_TRACE ( logger, "END : GET_Date::isValid" );

        return bIsDateValid;
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function: getCurrentDate( )
    //
    //   Purpose : Get the Current System Date
    //
    //   Inputs  : none
    //
    //   Outputs : none
    //
    //   Return  : GET_Date smart pointer instance of the current date
    //
    //   History :
    //      Who                           Date                 Description
    //  Capgemini Development Team     27 May, 2017         Initial creation
    //
    ===========================================================================
    //ENDFUNCDOC   ***/
    GET_DateUnqPtr GET_Date::getCurrentDate()
    {
        char *pcCurrentDate = NULL;

        IFail *exception = NULL;

        GET_DateUnqPtr currentDatePtr;

        ResultCheck stat;

        LOG_TRACE ( logger, "START : GET_Date::getCurrentDate" );

        try
        {
            date_t dtCurrentDate = NULLDATE;

            // Get the Current System Date
            stat = ITK_ask_default_date_format ( &pcCurrentDate );
            stat = ITK_string_to_date ( pcCurrentDate, &dtCurrentDate );
            currentDatePtr = getInstance ( dtCurrentDate );
        }
        catch ( IFail &ex )
        {
            exception = &ex;
        }
        
        // Free Memory
        MEM_free ( pcCurrentDate );

        if ( exception != NULL )
        {
            throw exception;
        }

        LOG_TRACE ( logger, "END : GET_Date::getCurrentDate" );

        return currentDatePtr;
    }
}
