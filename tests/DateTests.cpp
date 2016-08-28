#include "divida_tests.h"

#include <divida/Date.h>

TEST_CASE("Date - Creation", "[date]")
{
	int day = 4;
	int month = 7;
	int year = 2013;
	Divida::Date date = Divida::Date::Create(day, month, year);

	CHECK(day == date.Day());
	CHECK(month == date.Month());
	CHECK(year == date.Year());
}

TEST_CASE("Date - InvalidDay", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Date - InvalidMonth", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Date - InvalidYear", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Date - InvalidDayInMonth", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Date - ValidDayInMonthInLeapYear", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Date - InvalidDayInMonthInNonLeapYear", "[date]")
{
	// TODO: Unimplemented!
}
