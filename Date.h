/***************************************************************************//**

 @file

 @brief Utilities for date and time

*//****************************************************************************/

#ifndef _UTILS_DATE_H_
#define _UTILS_DATE_H_
#include "TypeDefs.h"

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

typedef struct _Date Date;
Date* Date_Create(void);
void  Date_Delete(void);

typedef int 	(*fPtrDiffDate)		(const Date* this, const char* pDate1, const char* pDate2 );
typedef int 	(*fPtrDiffTime)		(const Date* this, const char* pTime1, const char* pTime2 );
typedef bool_t  (*fPtrIsLeapYear)	(const Date* this, const uint16_t nYear );
typedef int 	(*fPtrDaysInMonth)  (const Date* this, const uint16_t nYear, const uint16_t nMonth );

typedef int 	(*fPtrCompareDateTime)	(const Date* this, const char* pDateTime1, const char* pDateTime2 );

typedef int 	(*fPtrIncDate) (const Date* this, char* pDate, int nDays );
typedef int 	(*fPtrIncTime) (const Date* this, char* pTime, int nHours, int nMinutes, int nSeconds );

typedef uint16_t (*fPtrGetYears)(const Date* this, const char* pDate );
typedef uint16_t (*fPtrGetMonths)(const Date* this, const char* pDate );
typedef uint16_t (*fPtrGetDays)(const Date* this, const char* pDate );
typedef void 	 (*fPtrSetYears)(const Date* this, char* pDate, const uint16_t nYear );
typedef void 	 (*fPtrSetMonths(const Date* this, char* pDate, const uint16_t nMonth );
typedef void     (*fPtrSetDays)(const Date* this, char* pDate, const uint16_t nDay );

typedef uint16_t (*fPtrGetHours)(const Date* this, const char* pTime );
typedef uint16_t (*fPtrGetMinutes)(const Date* this, const char* pTime );
typedef uint16_t (*fPtrGetSeconds)(const Date* this, const char* pTime );
typedef void     (*fPtrSetHours)(const Date* this, char* pTime, const uint16_t nHour );
typedef void     (*fPtrSetMinutes)(const Date* this, char* pTime, const uint16_t nMinute );
typedef void     (*fPtrSetSeconds)(const Date* this, char* pTime, const uint16_t nSecond );


////////////////////////////////////////////////////////////////////////////////
// deprecated

typedef uint16_t (*fPtrGetYear)(const Date* this, const uint16_t nDateLen, const char* pDate );
typedef uint16_t (*fPtrGetMonth)(const Date* this, const uint16_t nDateLen, const char* pDate );
typedef uint16_t (*fPtrGetDay)(const Date* this, const uint16_t nDateLen, const char* pDate );
typedef bool_t   (*fPtrSetYear)(const Date* this, const uint16_t nYear, const uint16_t nDateLen, char* pDate );
typedef bool_t   (*fPtrSetMonth)(const Date* this, const uint16_t nMonth, const uint16_t nDateLen, char* pDate );
typedef bool_t   (*fPtrSetDay)(const Date* this, const uint16_t nDay, const uint16_t nDateLen, char* pDate );

typedef uint16_t (*fPtrGetHour)(const Date* this, const uint16_t nTimeLen, const char* pTime );
typedef uint16_t (*fPtrGetMinute)(const Date* this, const uint16_t nTimeLen, const char* pTime );
typedef uint16_t (*fPtrGetSecond)(const Date* this, const uint16_t nTimeLen, const char* pTime );
typedef bool_t   (*fPtrSetHour)(const Date* this, const uint16_t nHour, const uint16_t nTimeLen, char* pTime );
typedef bool_t   (*fPtrSetMinute)(const Date* this, const uint16_t nMinute, const uint16_t nTimeLen, char* pTime );
typedef bool_t   (*fPtrSetSecond)(const Date* this, const uint16_t nSecond, const uint16_t nTimeLen, char* pTime );

#endif // _UTILS_DATE_H_
