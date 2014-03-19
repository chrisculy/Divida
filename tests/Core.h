#pragma once

#include <string>
#include <vector>

#include "Beneficiary.h"
#include "Date.h"
#include "Expense.h"
#include "Item.h"
#include "Object.h"
#include "Person.h"
#include "Report.h"
#include "Transaction.h"

using namespace Divida;

namespace Divida
{
	namespace Tests
	{
		const float FLOAT_EPSILON = 0.00001f;

		const std::wstring NAME_GANDALF = std::wstring(L"Gandalf");
		const std::wstring NAME_FRODO = std::wstring(L"Frodo");
		const std::wstring NAME_SAM = std::wstring(L"Sam");
		const std::wstring NAME_MERRY = std::wstring(L"Merry");
		const std::wstring NAME_PIPPIN = std::wstring(L"Pippin");
		const std::wstring NAME_ARAGORN = std::wstring(L"Aragorn");
		const std::wstring NAME_LEGOLAS = std::wstring(L"Legolas");
		const std::wstring NAME_GIMLI = std::wstring(L"Gimli");

		template<typename T> bool AreEqual(const std::vector<T>& a, const std::vector<T>& b)
		{
			if (a.size() != b.size())
				return false;

			std::vector<T>::const_iterator aIter;
			std::vector<T>::const_iterator bIter;
			for (aIter = a.begin(), bIter = b.begin(); aIter != a.end(); ++aIter, ++bIter)
			{
				if (*aIter != *bIter)
					return false;
			}

			return true;
		}
	}
}

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<Date>(const Date& date)
			{
				return date.ToString();
			}

			template<> static std::wstring ToString<Beneficiary>(const Beneficiary& beneficiary)
			{
				return beneficiary.ToString();
			}

			template<> static std::wstring ToString<Expense>(const Expense& expense)
			{
				return expense.ToString();
			}

			template<> static std::wstring ToString<Item>(const Item& item)
			{
				return item.ToString();
			}

			template<> static std::wstring ToString<Person>(const Person& person)
			{
				return person.ToString();
			}

			template<> static std::wstring ToString<Transaction>(const Transaction& transaction)
			{
				return transaction.ToString();
			}
		}
	}
}
