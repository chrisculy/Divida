#include "pch.h"

#include "Date.h"

namespace Divida
{
	Date Date::Create(int day, int month, int year)
	{
		// TODO: validate the date
		return Date(day, month, year);
	}

	Date::Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year)
	{
	}

	int Date::Day() const
	{
		return m_day;
	}

	int Date::Month() const
	{
		return m_month;
	}

	int Date::Year() const
	{
		return m_year;
	}

	Date Date::operator=(const Date& date)
	{
		return Date::Create(date.Day(), date.Month(), date.Year());
	}
	
	bool Date::operator==(const Date& date) const
	{
		return m_day == date.m_day && m_month == date.m_month && m_year == date.m_year;
	}

	std::wstring Date::ToString() const
	{
		std::wstringstream s;
		s << m_month << L'/' << m_day << L'/' << m_year;
		return s.str();
	}
}
