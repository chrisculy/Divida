#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Divida
{
	namespace Tests
	{
		TEST_CLASS(ExpenseTests)
		{
		public:
			TEST_METHOD(Construction)
			{
				auto payer = std::make_shared<Person>(NAME_GANDALF);
				auto payerWeak = std::weak_ptr<Person>(payer);
				auto name = std::wstring(L"Weapons");
				auto date = Date::Create(17, 3, 1946);

				Expense expense(name, date, payer);

				Assert::AreEqual(name, expense.Name());
				Assert::AreEqual(date, expense.Date());
				Assert::AreEqual(payer, expense.Payer());
			}

			TEST_METHOD(AddAndGetSingleItem)
			{
				auto payer = std::make_shared<Person>(NAME_GANDALF);
				auto date = Date::Create(17, 3, 1946);

				Expense expense(L"Weapons", date, payer);

				auto itemName = std::wstring(L"Sting");
				auto itemCost = 15.37f;
				auto person = std::make_shared<Person>(NAME_FRODO);
				auto beneficiary = std::make_shared<Beneficiary>(person);
				auto beneficiaries = std::vector<std::shared_ptr<Beneficiary>> { beneficiary };

				expense.AddItem(itemName, itemCost, beneficiaries);

				auto items = expense.Items();
				Assert::AreEqual((size_t)1, items.size());
				Assert::AreEqual(itemName, items[0]->Name());
				Assert::AreEqual(itemCost, items[0]->Cost());
				AreEqual(beneficiaries, items[0]->Beneficiaries());
			}

			TEST_METHOD(AddAndGetMultipleItems)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(SetAndGetDate)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(SetAndGetPayer)
			{
				Assert::Fail(L"Unimplemented!");
			}

			TEST_METHOD(Total)
			{
				Assert::Fail(L"Unimplemented!");
			}
		};
	}
}
