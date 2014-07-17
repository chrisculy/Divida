#include "pch.h"

#include "Report.h"
#include "ReportXmlSerializer.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <set>
#include <numeric>

namespace Divida
{
	Report::Report(const std::wstring& name) : Object(name)
	{
	}

	void Report::AddPerson(const std::wstring& name)
	{
		m_persons.push_back(std::make_shared<Person>(name));
	}

	const std::shared_ptr<Person> Report::GetPerson(const std::wstring& name) const
	{
		for (auto person : m_persons)
		{
			if (person->Name() == name)
				return person;
		}

		return nullptr;
	}

	const std::shared_ptr<Expense> Report::NewExpense(const std::wstring& name, const Date& date, const std::shared_ptr<Person> payer)
	{
		// TODO: make sure the name is unique (this also has to work even if the name is changed later on from the Expense API).
		// TODO: only insert the expense if it doesn't already exist (related to above).
		std::shared_ptr<Expense> expense = std::make_shared<Expense>(name, date, payer);
		m_expenses.push_back(expense);
		return expense;
	}

	const std::shared_ptr<Expense> Report::GetExpense(const std::wstring& name) const
	{
		for (auto expense : m_expenses)
		{
			if (expense->Name() == name)
				return expense;
		}

		return nullptr;
	}

	const std::vector<std::shared_ptr<Person>>& Report::Persons() const
	{
		return m_persons;
	}

	const std::vector<std::shared_ptr<Expense>>& Report::Expenses() const
	{
		return m_expenses;
	}

	std::vector<std::shared_ptr<Transaction>> Report::CalculateTransactions()
	{
		// Calculate total owing amounts for each person, subtracting the expenses they paid for
		m_owingTotals.clear();
		for (auto expense : m_expenses)
		{
			AddPaymentForPerson(expense->Payer(), expense->Name(), expense->Total());

			for (auto item : expense->Items())
			{
				float totalWeightFactor = 1.0f / std::accumulate<std::vector<std::shared_ptr<Beneficiary>>::const_iterator, float>(item->Beneficiaries().begin(), item->Beneficiaries().end(), 0, 
					[](float total, std::shared_ptr<Beneficiary> current) { return total + current->Weight(); });

				for (auto beneficiary : item->Beneficiaries())
					AddExpenseForPerson(beneficiary->Person(), item->Name(), beneficiary->Weight() * totalWeightFactor, item->Cost());
			}
		}

		// Sort the owing totals in ascending order so the people who should be paid are at the front.
		std::sort(m_owingTotals.begin(), m_owingTotals.end(), [](const std::pair<std::weak_ptr<Person>, float>& a, const std::pair<std::weak_ptr<Person>, float>& b) { return a.second < b.second; });

		// Calculate the needed transactions.
		std::vector<std::shared_ptr<Transaction>> transactions;
		auto payToIter = m_owingTotals.begin();
		auto payFromIter = std::prev(m_owingTotals.end());
		while (true)
		{
			assert(payToIter->second <= 0);
			assert(payFromIter->second >= 0);
				
			float amount = std::min(payFromIter->second, std::abs(payToIter->second));
			transactions.push_back(std::make_shared<Transaction>(payFromIter->first, payToIter->first, amount));

			payFromIter->second -= amount;
			payToIter->second += amount;

			if (payFromIter->second == 0 && payFromIter != m_owingTotals.begin())
			{
				payFromIter--;

				if (payToIter == payFromIter)
					break;
			}

			if (payToIter->second == 0 && payToIter != m_owingTotals.end())
			{
				payToIter++;

				if (payToIter == payFromIter)
					break;
			}
		}

		return transactions;
	}

	const ReportInfo* Report::GetReportInfoForPerson(const std::wstring& name) const
	{
		auto iter = std::find_if(m_info.begin(), m_info.end(), [&name](const std::pair<std::shared_ptr<Person>, ReportInfo>& current) { return current.first->Name() == name; });
		if (iter != m_info.end())
			return &iter->second;

		return nullptr;
	}

	unsigned int Report::GetItemNamePrintWidth() const
	{
		const unsigned int padding = 4;
		unsigned int width = 20;
		for (auto expense : m_expenses)
		{
			for (auto item : expense->Items())
			{
				if (item->Name().length() > width)
					width = item->Name().length();
			}
		}
		
		return width + padding;
	}

	void Report::AddPaymentForPerson(const std::shared_ptr<Person>& person, const std::wstring& name, float amount)
	{
		m_info[person].Payments.push_back(ReportPayment(name, amount));
		UpdateAmount(person, -amount);
	}

	void Report::AddExpenseForPerson(const std::shared_ptr<Person>& person, const std::wstring& name, float weight, float amount)
	{
		m_info[person].Expenses.push_back(ReportExpense(name, weight, amount));
		UpdateAmount(person, weight * amount);
	}

	void Report::UpdateAmount(const std::weak_ptr<Person>& person, float difference)
	{
		Report::OwingTotalsTable::iterator owingTotal = std::find_if(m_owingTotals.begin(), m_owingTotals.end(),
			[&person](const std::pair<std::weak_ptr<Person>, float>& current) { return current.first.lock() == person.lock(); });
		if (owingTotal == m_owingTotals.end())
			m_owingTotals.push_back(std::make_pair(person, difference));
		else
			owingTotal->second += difference;
	}

	ReportExpense::ReportExpense(const std::wstring& name, float weight, float amount) : Name(name), Weight(weight), Amount(amount)
	{
	}

	ReportPayment::ReportPayment(const std::wstring& name, float amount) : Name(name), Amount(amount)
	{
	}
}
