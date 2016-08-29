#include "divida_tests.h"

#include <divida/date.h>

TEST_CASE("date - Creation", "[date]")
{
	int day = 4;
	int month = 7;
	int year = 2013;
	divida::date date = divida::date::create(day, month, year);

	CHECK(day == date.day());
	CHECK(month == date.month());
	CHECK(year == date.year());
}

TEST_CASE("date - InvalidDay", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("date - InvalidMonth", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("date - InvalidYear", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("date - InvalidDayInMonth", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("date - ValidDayInMonthInLeapYear", "[date]")
{
	// TODO: Unimplemented!
}

TEST_CASE("date - InvalidDayInMonthInNonLeapYear", "[date]")
{
	// TODO: Unimplemented!
}
