
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_Date.hxx
//
//    Purpose:   Header  class for dealing with the date class
//    
//    History:
//      Who                          Date                 Description
//  TCS Development Team           27 Mar, 2016         Initial creation
//  Capgemini Development Team     29 May, 2017         Added new method declarations for getCurrentDate, compareTo, getDayDifferent method
//  TCS Development Team           31 May, 2017         Renamed the compareTo method to compare and getDayDifference to getDifferenceInDays
//
//   ============================================================================
// ENDFILEDOC   ***/


#ifndef GET_DATE_HXX_
#define GET_DATE_HXX_

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_TC_Logger.hxx>

// Teamcenter Includes
#include <fclasses/tc_date.h>
#include <unidefs.h>
#include <tc/tc_startup.h>
#include <fclasses/tc_basic.h>
#include <tc/tc.h>

// Smart Pointer Definition
namespace get
{
    #define GET_DateUnqPtr unique_ptr<GET_Date>
    #define GET_DateShrPtr shared_ptr<GET_Date>
}

namespace get 
{
    /**
     * Model Date using TC's date_t structure
     */
    class DLLEXPORT GET_Date
    {
        private:
            date_t dtTCDate;

        public:
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
            GET_Date ( const date_t dtDate );

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
            virtual ~GET_Date();


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
            string toString() const;

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
            string toString ( const string ) const;

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:  getDate ( sDateFormat )
            //
            //   Purpose :  Method to get Date
            //
            //   Inputs  :  none
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
            date_t getDate() const
            {
                return dtTCDate;
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
            int compare ( const GET_DateShrPtr );

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
            double getDifferenceInDays ( const GET_DateShrPtr datePtr );

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
            static GET_DateUnqPtr getInstance ( const date_t dtDate );

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
            static GET_DateUnqPtr getInstance ( const string sDateString );

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
            static GET_DateUnqPtr getInstance ( const string sDateString, const string sDateFormat );

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
            static GET_DateUnqPtr getInstance ( const int year, const int month, const int day,
                                                const int iHour, const int iMinute, const int iSecond );

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
            static bool isValid ( const string sDateString, const string sDateFormat );
            
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
            static GET_DateUnqPtr getCurrentDate();
    };
}

#endif //GET_DATE_HXX
