/***************************************************************************//**

 @file

 @brief Utilities for date and time

*//****************************************************************************/
#include <string.h>

#include "TypeDefs.h"
#include "Convert.h"
#include "Date.h"


#define TIME_DATE_LEN  12 // YYMMDDhhmmss
#define DAYS_IN_YEAR 365
#define NUMBER_OF_MONTHS 12


uint8_t s_nDaysPerMonth[ NUMBER_OF_MONTHS ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

typedef struct _Date
{
	fPtrDiffDate   			DiffDate;
	fPtrDiffTime			DiffTime;
	fPtrIsLeapYear			IsLeapYear;
	fPtrDaysInMonth			DaysInMonth;
	
	fPtrCompareDateTime		CompareDateTime;
	
	fPtrIncDate				IncDate;	
	fPtrIncTime				IncTime;	
	fPtrGetYears			GetYears;
	fPtrGetMonths			GetMonths;
	fPtrGetDays				GetDays;
	fPtrSetYears			SetYears;
	fPtrSetMonths			SetMonths;
	fPtrSetDays				SetDays;
	
	fPtrGetHours			GetHours;
	fPtrGetMinutes			GetMinutes;
	fPtrGetSeconds			GetSeconds;
	fPtrSetHours			SetHours;
	fPtrSetMinutes			SetMinutes;
	fPtrSetSeconds			SetSeconds;
	
	fPtrGetYear				GetYear;
	fPtrGetMonth			GetMonth;
	fPtrGetDay				GetDay;
	fPtrSetYear				SetYear;
	fPtrSetMonth			SetMonth;
	fPtrSetDay				SetDay;
	
	fPtrGetHour				GetHour;
	fPtrGetMinute			GetMinute;
	fPtrGetSecond			GetSecond;
	fPtrSetHour				SetHour;
	fPtrSetMinute			SetMinute;
	fPtrSetSecond			SetSecond;
	
	fPtrDelete				Delete;
	
}Date;


Date* Date_Create(void)
{
	Date* dateObj;
	dateObj = (Date*)malloc(sizeof(Date));
	if (dateObj == NULL)
	{
		return NULL;
	}
	
	dateObj->DiffDate   	 =	Date_DiffDate;
	dateObj->DiffTime		 =	Date_DiffTime;
	dateObj->IsLeapYear		 =	Date_IsLeapYear;
	dateObj->DaysInMonth	 =	Date_DaysInMonth;
	
	dateObj->CompareDateTime =	Date_CompareDateTime;
	
	dateObj->IncDate		 =	Date_IncDate;	
	dateObj->IncTime		 =	Date_IncTime;	
	dateObj->GetYears		 =	Date_GetYears;
	dateObj->GetMonths		 =	Date_GetMonths;
	dateObj->GetDays		 =	Date_GetDays;
	dateObj->SetYears		 =	Date_SetYears;
	dateObj->SetMonths		 =	Date_SetMonths;
	dateObj->SetDays		 =	Date_SetDays;
	
	dateObj->GetHours		 =	Date_GetHours;
	dateObj->GetMinutes		 =	Date_GetMinutes;
	dateObj->GetSeconds		 =	Date_GetSeconds;
	dateObj->SetHours		 =	Date_SetHours;
	dateObj->SetMinutes		 =	Date_SetMinutes;
	dateObj->SetSeconds		 =	Date_SetSeconds;
	
	dateObj->GetYear		 =	Date_GetYear;
	dateObj->GetMonth		 =	Date_GetMonth;
	dateObj->GetDay			 =	Date_GetDay;
	dateObj->SetYear		 =	Date_SetYear;
	dateObj->SetMonth		 =	Date_SetMonth;
	dateObj->SetDay			 =	Date_SetDay;
	
	dateObj->GetHour		 =	Date_GetHour;
	dateObj->GetMinute		 =	Date_GetMinute;
	dateObj->GetSecond		 =	Date_GetSecond;
	dateObj->SetHour		 =	Date_SetHour;
	dateObj->SetMinute		 =	Date_SetMinute;
	dateObj->SetSecond		 =	Date_SetSecond;
	
	dateObj->Delete			 =	Date_Delete;
}

/**
 * @brief Calculates if year is leap year
 */
bool_t Date_IsLeapYear(const Date* this, const uint16_t nYear )
{
  // Year is leap year if:
  // a) it is divisible by 4 and not divisible by 100
  // b) it is divisible by 400
  return ( ( ( ( nYear & 0x03 ) == 0 ) && ( ( nYear % 100 ) != 0 ) ) || ( ( nYear % 400 ) == 0 ) );
}


/**
 * @brief Calculates difference of two dates in days.
 *
 * @retval pDate1-pDate2 Number of days as difference between two dates
 */
int Date_DiffDate (
	const Date* this,
    const char* pDate1, ///< Pointer to buffer containing date stored as in YYMMDD format
    const char* pDate2  ///< Pointer to buffer containing date stored as in YYMMDD format
    )
{
  int16_t nYear;
  int16_t nMonth;

  int16_t nYear1 = (int16_t)Asc2i( pDate1 + 0, 2 ) + 2000;
  int16_t nMonth1 = (int16_t)Asc2i( pDate1 + 2, 2 );
  int16_t nDay1 = (int16_t)Asc2i( pDate1 + 4, 2 );

  int16_t nYear2 = (int16_t)Asc2i( pDate2 + 0, 2 ) + 2000;
  int16_t nMonth2 = (int16_t)Asc2i( pDate2 + 2, 2 );
  int16_t nDay2 = (int16_t)Asc2i( pDate2 + 4, 2 );

  int16_t nDiff = 0;

  bool_t bSwap = ( ( (nYear1 << 9) + (nMonth1 << 5) + nDay1 ) < ( (nYear2 << 9) + (nMonth2 << 5) + nDay2 ) );

  if ( bSwap )
  {
    int16_t nTmp;

    nTmp = nYear1;
    nYear1 = nYear2;
    nYear2 = nTmp;

    nTmp = nMonth1;
    nMonth1 = nMonth2;
    nMonth2 = nTmp;

    nTmp = nDay1;
    nDay1 = nDay2;
    nDay2 = nTmp;
  }

  //for( nYear = nYear2; nYear < nYear1; ++nYear )
  for(nYear = nYear2; nYear < nYear1; ++nYear )
  {
    nDiff += ((int16_t)DAYS_IN_YEAR) + ((int16_t)(this->IsLeapYear( nYear ) ? 1 : 0));
  }

  //for( nMonth = 1; nMonth < nMonth1; ++nMonth )
  for(nMonth = 1; nMonth < nMonth1; ++nMonth )
  {
    nDiff += s_nDaysPerMonth[ nMonth - 1 ];
    if (nMonth == 2 && this->IsLeapYear( nYear1 ) )
    {
      nDiff++;
    }
  }

  for( nMonth = 1; nMonth < nMonth2; ++nMonth )
  {
    nDiff -= s_nDaysPerMonth[ nMonth - 1 ];
    if ( nMonth == 2 && this->IsLeapYear( nYear2 ) )
    {
      nDiff--;
    }
  }

  nDiff += ( nDay1 - nDay2 );

  if ( bSwap )
  {
    return -nDiff;
  }
  else
  {
    return nDiff;
  }
}

/**
 * @brief Calculates difference of two times in seconds.
 *
 * @retval Number of seconds pTime1 - pTime2
 */
int Date_DiffTime(const Date* this, const char* pTime1, const char* pTime2 )
{
  int nHoursDiff   = this->GetHours(pTime1)   - this->GetHours(pTime2);
  int nMinutesDiff = this->GetMinutes(pTime1) - this->GetMinutes(pTime2);
  int nSecondsDiff = this->GetSeconds(pTime1) - this->GetSeconds(pTime2);

  return (nHoursDiff * 60 + nMinutesDiff) * 60 + nSecondsDiff;
}

/**
 * @brief Returns number of days in month for given year and month
 */
int Date_DaysInMonth(const Date* this, const uint16_t nYear, const uint16_t nMonth)
{
  if ( nMonth > 0 && nMonth <= NUMBER_OF_MONTHS )
  {
    uint16_t nExtraDays = (nMonth == 2 && this->IsLeapYear( nYear )) ? 1 : 0;
    return s_nDaysPerMonth[ nMonth - 1 ] + nExtraDays;
  }
  else
  {
    return 0;
  }
}

/**
 * Function compares two buffers with date and time in YYMMDDhhmmss format
 * @param pDateTime1 First date and time in YYMMDDhhmmss format
 * @param pDateTime2 Second date and time in YYMMDDhhmmss format
 *
 * @return 0 if equal, positive if dateTime1 > dateTime2, negative if dateTime1 < dateTime2
 */
int Date_CompareDateTime(const Date* this, const char* pDateTime1,  const char* pDateTime2 )
{
  return memcmp(pDateTime1, pDateTime2, TIME_DATE_LEN);
}

#define YEAR_LENGTH 2
#define MONTH_LENGTH 2
#define DAY_LENGTH 2

#define HOUR_LENGTH 2
#define MINUTE_LENGTH 2
#define SECOND_LENGTH 2

int Date_IncDate(const Date* this, char* pDate, int nNewDays )
{
  int carry   = 0;
  int nDays   = this->GetDays(pDate) + nNewDays;
  int nMonths = this->GetMonths(pDate);
  int nYears  = this->GetYears(pDate);

  while( true )
  {
    int nDaysInMonth = this->DaysInMonth( nYears, nMonths );
    if ( nDays >= 1 && nDays <= nDaysInMonth )
    {
      break;
    }
    else if ( nDays <= 0 ) {
      --nMonths;
      if ( nMonths <= 0 )
      {
        nMonths = 12;
        if (nYears <= 2000)
        {
          --carry;
        }
        --nYears;
      }
      nDaysInMonth = this->DaysInMonth( nYears, nMonths );
      nDays += nDaysInMonth;
    }
    else
    {
      nDays -= nDaysInMonth;
      ++nMonths;
      if ( nMonths > 12 )
      {
        nMonths = 1;
        ++nYears;
      }
    }
  }

  this->SetYears ( pDate, nYears );
  this->SetMonths( pDate, nMonths );
  this->SetDays  ( pDate, nDays );
  return carry;
}


/**
 *
 * @return Number of days carried
 */
int Date_IncTime(const Date* this, char* pTime, int nNewHours, int nNewMinutes, int nNewSeconds )
{
  int nCarry = 0;

  int nSeconds = this->GetSeconds(pTime) + nNewSeconds;
  int nMinutes = this->GetMinutes(pTime) + nNewMinutes;
  int nHours   = this->GetHours(pTime)   + nNewHours;

  nMinutes += nSeconds / 60;
  nSeconds = nSeconds % 60;

  nHours += nMinutes / 60;
  nMinutes = nMinutes % 60;

  nCarry = nHours / 24;
  nHours = nHours % 24;

  this->SetHours  ( pTime, nHours );
  this->SetMinutes( pTime, nMinutes );
  this->SetSeconds( pTime, nSeconds );

  return nCarry;
}




/**
 * @brief Returns year from date in YYMMDD format
 */
uint16_t Date_GetYears(
	const Date* this,
    const char* pDate  ///< Pointer to date data
    )
{
  return Asc2i( pDate, YEAR_LENGTH );
}

/**
 * @brief Returns month from date in YYMMDD format
 */
uint16_t Date_GetMonths(
	const Date* this,
    const char* pDate  ///< Pointer to date data
    )
{
  return Asc2i( pDate + YEAR_LENGTH, MONTH_LENGTH );
}

/**
 * @brief Returns day from date in YYMMDD format
 */
uint16_t Date_GetDays(
	const Date* this,
    const char* pDate  ///< Pointer to date data
    )
{
  return Asc2i( pDate + YEAR_LENGTH + MONTH_LENGTH, DAY_LENGTH );
}

/**
 * @brief Sets day in date (YYMMDD)
 */
void Date_SetYears(
	const Date* this,
    char* pDate,  ///< Pointer to date data
    const uint16_t nYear  ///< Year to set
    )
{
  I2Asc( nYear, pDate, YEAR_LENGTH, 10 );
}

/**
 * @brief Sets month in date (YYMMDD)
 */
void Date_SetMonths(
	const Date* this,
    char* pDate,  ///< Pointer to date data
    const uint16_t nMonth  ///< Month to set
    )
{
  I2Asc( nMonth, pDate + YEAR_LENGTH, MONTH_LENGTH, 10 );
}

/**
 * @brief Sets day in date (YYMMDD)
 */
void Date_SetDays(
	const Date* this,
    char* pDate,  ///< Pointer to date data
    const uint16_t nDay  ///< Day to set
    )
{
  I2Asc( nDay, pDate + YEAR_LENGTH + MONTH_LENGTH, DAY_LENGTH, 10 );
}


/**
 * @brief Returns hour from time in HHMMSS format
 */
uint16_t Date_GetHours(
	const Date* this,
    const char* pTime  ///< Pointer to time data
    )
{
  return Asc2i( pTime, HOUR_LENGTH );
}

/**
 * @brief Returns minute from time in HHMMSS format
 */
uint16_t Date_GetMinutes(
	const Date* this,
    const char* pTime  ///< Pointer to time data
    )
{
  return Asc2i( pTime + HOUR_LENGTH, MINUTE_LENGTH );
}

/**
 * @brief Returns second from time in HHMMSS format
 */
uint16_t Date_GetSeconds(
	const Date* this,
    const char* pTime  ///< Pointer to time data
    )
{
  return Asc2i( pTime + HOUR_LENGTH + MINUTE_LENGTH, SECOND_LENGTH );
}

/**
 * @brief Sets second in time (HHMMSS)
 */
void Date_SetHours(
	const Date* this,
    char* pTime,  ///< Pointer to time data
    const uint16_t nHour  ///< Hour to set
    )
{
  I2Asc( nHour, pTime, HOUR_LENGTH, 10 );
}

/**
 * @brief Sets minute in time (HHMMSS)
 */
void Date_SetMinutes(
	const Date* this,
    char* pTime,  ///< Pointer to time data
    const uint16_t nMinute  ///< Minute to set
    )
{
  I2Asc( nMinute, pTime + HOUR_LENGTH, MINUTE_LENGTH, 10 );
}

/**
 * @brief Sets second in time (HHMMSS)
 */
void Date_SetSeconds(
	const Date* this,
    char* pTime,  ///< Pointer to time data
    const uint16_t nSecond  ///< Second to set
    )
{
  I2Asc( nSecond, pTime + HOUR_LENGTH + MINUTE_LENGTH, SECOND_LENGTH, 10 );
}




////////////////////////////////////////////////////////////////////////////////
// deprecated

/**
 * @brief Returns year from date in YYMMDD format
 */
uint16_t Date_GetYear(
	const Date* this,
    const uint16_t nDateLen,  ///< Length of date
    const char* pDate  ///< Pointer to date data
    )
{

  if( nDateLen >= YEAR_LENGTH )
  {
    return Asc2i( pDate, YEAR_LENGTH );
  }
  else
  {
   return 0;
  }
}

/**
 * @brief Returns month from date in YYMMDD format
 */
uint16_t Date_GetMonth(
	const Date* this,
    const uint16_t nDateLen,  ///< Length of date
    const char* pDate  ///< Pointer to date data
    )
{

  if( nDateLen >= YEAR_LENGTH + MONTH_LENGTH )
  {
    return Asc2i( pDate + YEAR_LENGTH, MONTH_LENGTH );
  }
  else
  {
   return 0;
  }
}

/**
 * @brief Returns day from date in YYMMDD format
 */
uint16_t Date_GetDay(
	const Date* this,
    const uint16_t nDateLen,  ///< Length of date
    const char* pDate  ///< Pointer to date data
    )
{

  if( nDateLen >= YEAR_LENGTH + MONTH_LENGTH + DAY_LENGTH )
  {
    return Asc2i( pDate + YEAR_LENGTH + MONTH_LENGTH, DAY_LENGTH );
  }
  else
  {
   return 0;
  }
}

/**
 * @brief Sets day in date (YYMMDD)
 */
bool_t Date_SetYear(
	const Date* this,
    const uint16_t nYear,  ///< Year to set
    const uint16_t nDateLen,  ///< Length of date
    char* pDate  ///< Pointer to date data
    )
{
  if( nDateLen >= YEAR_LENGTH )
  {
    I2Asc( nYear, pDate, YEAR_LENGTH, 10 );
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Sets month in date (YYMMDD)
 */
bool_t Date_SetMonth(
	const Date* this,
    const uint16_t nMonth,  ///< Month to set
    const uint16_t nDateLen,  ///< Length of date
    char* pDate  ///< Pointer to date data
    )
{
  if( nDateLen >= YEAR_LENGTH + MONTH_LENGTH )
  {
    I2Asc( nMonth, pDate + YEAR_LENGTH, MONTH_LENGTH, 10 );
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Sets day in date (YYMMDD)
 */
bool_t Date_SetDay(
	const Date* this,
    const uint16_t nDay,  ///< Day to set
    const uint16_t nDateLen,  ///< Length of date
    char* pDate  ///< Pointer to date data
    )
{
  if( nDateLen >= YEAR_LENGTH + MONTH_LENGTH + DAY_LENGTH )
  {
    I2Asc( nDay, pDate + YEAR_LENGTH + MONTH_LENGTH, DAY_LENGTH, 10 );
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Returns hour from time in HHMMSS format
 */
uint16_t Date_GetHour(
	const Date* this,
    const uint16_t nTimeLen,  ///< Length of time
    const char* pTime  ///< Pointer to time data
    )
{

  if( nTimeLen >= HOUR_LENGTH )
  {
    return Asc2i( pTime, HOUR_LENGTH );
  }
  else
  {
   return 0;
  }
}

/**
 * @brief Returns minute from time in HHMMSS format
 */
uint16_t Date_GetMinute(
	const Date* this,
    const uint16_t nTimeLen,  ///< Length of time
    const char* pTime  ///< Pointer to time data
    )
{

  if( nTimeLen >= HOUR_LENGTH + MINUTE_LENGTH )
  {
    return Asc2i( pTime + HOUR_LENGTH, MINUTE_LENGTH );
  }
  else
  {
   return 0;
  }
}

/**
 * @brief Returns second from time in HHMMSS format
 */
uint16_t Date_GetSecond(
	const Date* this,
    const uint16_t nTimeLen,  ///< Length of time
    const char* pTime  ///< Pointer to time data
    )
{

  if( nTimeLen >= HOUR_LENGTH + MINUTE_LENGTH + SECOND_LENGTH )
  {
    return Asc2i( pTime + HOUR_LENGTH + MINUTE_LENGTH, SECOND_LENGTH );
  }
  else
  {
   return 0;
  }
}

/**
 * @brief Sets second in time (HHMMSS)
 */
bool_t Date_SetHour(
	const Date* this,
    const uint16_t nHour,  ///< Hour to set
    const uint16_t nTimeLen,  ///< Length of time
    char* pTime  ///< Pointer to time data
    )
{
  if( nTimeLen >= HOUR_LENGTH )
  {
    I2Asc( nHour, pTime, HOUR_LENGTH, 10 );
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Sets minute in time (HHMMSS)
 */
bool_t Date_SetMinute(
	const Date* this,
    const uint16_t nMinute,  ///< Minute to set
    const uint16_t nTimeLen,  ///< Length of time
    char* pTime  ///< Pointer to time data
    )
{
  if( nTimeLen >= HOUR_LENGTH + MINUTE_LENGTH )
  {
    I2Asc( nMinute, pTime + HOUR_LENGTH, MINUTE_LENGTH, 10 );
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Sets second in time (HHMMSS)
 */
bool_t Date_SetSecond(
	const Date* this,
    const uint16_t nSecond,  ///< Second to set
    const uint16_t nTimeLen,  ///< Length of time
    char* pTime  ///< Pointer to time data
    )
{
  if( nTimeLen >= HOUR_LENGTH + MINUTE_LENGTH + SECOND_LENGTH )
  {
    I2Asc( nSecond, pTime + HOUR_LENGTH + MINUTE_LENGTH, SECOND_LENGTH, 10 );
    return true;
  }
  else
  {
    return false;
  }
}







