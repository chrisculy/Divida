#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Divida
{
	namespace Tests
	{
		TEST_CLASS(DateTests)
		{
		public:
			TEST_METHOD(Creation)
			{
				int day = 4;
				int month = 7;
				int year = 2013;
				Date date = Date::Create(day, month, year);

				Assert::AreEqual(day, date.Day());
				Assert::AreEqual(month, date.Month());
				Assert::AreEqual(year, date.Year());
			}

			TEST_METHOD(InvalidDay)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(InvalidMonth)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(InvalidYear)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(InvalidDayInMonth)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(ValidDayInMonthInLeapYear)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(InvalidDayInMonthInNonLeapYear)
			{
				Assert::Fail(L"Unimplemented!");
			}
		};
	}
}
