#pragma once

#include <string>

namespace divida
{
	class date
	{
	public:
		static date create(int day, int month, int year);

		int day() const;
		int month() const;
		int year() const;

		date operator=(const date& other);
		bool operator==(const date& other) const;
		bool operator!=(const date& other) const;

	private:
		date(int day, int month, int year);

		const int m_day;
		const int m_month;
		const int m_year;
	};
}
