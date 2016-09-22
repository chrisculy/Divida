#include "date.h"

namespace divida
{
	date date::create(int day, int month, int year)
	{
		// TODO: validate the date
		return date(day, month, year);
	}

	date::date(int day, int month, int year)
		: m_day{ day }
		, m_month{ month }
		, m_year{ year }
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

	date date::operator=(const date& other)
	{
		return date::create(other.day(), other.month(), other.year());
	}
	
	bool date::operator==(const date& other) const
	{
		return m_day == other.m_day && m_month == other.m_month && m_year == other.m_year;
	}

	bool date::operator!=(const date& other) const
	{
		return !(*this == other);
	}
}
