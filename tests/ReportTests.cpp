#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Divida
{
	namespace Tests
	{
		TEST_CLASS(ReportTests)
		{
		public:
			TEST_CLASS_INITIALIZE(ClassInitialize)
			{
				
			}

			TEST_METHOD(Construction)
			{
				Report report(m_name);

				Assert::AreEqual(m_name, report.Name());
			}

			TEST_METHOD(AddAndGetPerson)
			{
				Report report(m_name);
				
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(NewAndGetExpense)
			{
				Report report(m_name);

				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(CalculateTransactions)
			{
				Report report(m_name);

				Assert::Fail(L"Unimplemented!");
			}

		private:
			static const std::wstring m_name;
		};

		const std::wstring ReportTests::m_name = std::wstring(L"The Journey to Rivendell");
	}
}
