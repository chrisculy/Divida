#include "Date.h"

#include <sstream>

namespace divida
{
	date date::create(int day, int month, int year)
	{
		// TODO: validate the date
		return date(day, month, year);
	}

	date::date(int day, int month, int year) : m_day(day), m_month(month), m_year(year)
	{
	}

	int date::day() const
	{
		return m_day;
	}

	int date::month() const
	{
		return m_month;
	}

	int date::year() const
	{
		return m_year;
	}

	date date::operator=(const date& date)
	{
		return date::create(date.day(), date.month(), date.year());
	}
	
	bool date::operator==(const date& date) const
	{
		return m_day == date.m_day && m_month == date.m_month && m_year == date.m_year;
	}

	std::string date::ToString() const
	{
		std::stringstream s;
		s << m_month << '/' << m_day << '/' << m_year;
		return s.str();
	}
}
