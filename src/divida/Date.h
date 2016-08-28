#pragma once

#include <string>

namespace Divida
{
	class Date
	{
	public:
		static Date Create(int day, int month, int year);

		int Day() const;
		int Month() const;
		int Year() const;

		Date operator=(const Date& date);
		bool operator==(const Date& date) const;

		std::string ToString() const;

	private:
		Date(int day, int month, int year);

		const int m_day;
		const int m_month;
		const int m_year;
	};
}
