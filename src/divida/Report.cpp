#include "Report.h"
#include "ReportXmlSerializer.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <set>
#include <numeric>

namespace divida
{
	report::report(const std::string& name) : object(name)
	{
	}

	void report::add_person(const std::string& name)
	{
		m_persons.push_back(std::make_shared<person>(name));
	}

	const std::shared_ptr<person> report::get_person(const std::string& name) const
	{
		for (auto person : m_persons)
		{
			if (person->name() == name)
				return person;
		}

		return nullptr;
	}

	const std::shared_ptr<expense> report::new_expense(const std::string& name, const date& date, const std::shared_ptr<person> payer)
	{
		// TODO: make sure the name is unique (this also has to work even if the name is changed later on from the Expense API).
		// TODO: only insert the expense if it doesn't already exist (related to above).
		auto expense = std::make_shared<divida::expense>(name, date, payer);
		m_expenses.push_back(expense);
		return expense;
	}

	const std::shared_ptr<expense> report::get_expense(const std::string& name) const
	{
		for (auto expense : m_expenses)
		{
			if (expense->name() == name)
				return expense;
		}

		return nullptr;
	}

	const std::vector<std::shared_ptr<person>>& report::persons() const
	{
		return m_persons;
	}

	const std::vector<std::shared_ptr<expense>>& report::expenses() const
	{
		return m_expenses;
	}

	std::vector<std::shared_ptr<transaction>> report::calculate_transactions()
	{
		// Calculate total owing amounts for each person, subtracting the expenses they paid for
		m_owingTotals.clear();
		for (auto expense : m_expenses)
		{
			add_payment_for_person(expense->payer(), expense->name(), expense->total());

			for (auto item : expense->items())
			{
				float totalWeightFactor = 1.0f / std::accumulate<std::vector<std::shared_ptr<beneficiary>>::const_iterator, float>(item->beneficiaries().begin(), item->beneficiaries().end(), 0, 
					[](float total, std::shared_ptr<beneficiary> current) { return total + current->weight(); });

				for (auto beneficiary : item->beneficiaries())
					add_expense_for_person(beneficiary->person(), item->name(), beneficiary->weight() * totalWeightFactor, item->cost());
			}
		}

		// Sort the owing totals in ascending order so the people who should be paid are at the front.
		std::sort(m_owingTotals.begin(), m_owingTotals.end(), [](const std::pair<std::weak_ptr<person>, float>& a, const std::pair<std::weak_ptr<person>, float>& b) { return a.second < b.second; });

		// Calculate the needed transactions.
		std::vector<std::shared_ptr<transaction>> transactions;
		auto payToIter = m_owingTotals.begin();
		auto payFromIter = std::prev(m_owingTotals.end());
		while (true)
		{
			assert(payToIter->second <= 0);
			assert(payFromIter->second >= 0);
				
			float amount = std::min(payFromIter->second, std::abs(payToIter->second));
			transactions.push_back(std::make_shared<transaction>(payFromIter->first, payToIter->first, amount));

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

	const report_info* report::get_report_info_for_person(const std::string& name) const
	{
		auto iter = std::find_if(m_info.begin(), m_info.end(), [&name](const std::pair<std::shared_ptr<person>, report_info>& current) { return current.first->name() == name; });
		if (iter != m_info.end())
			return &iter->second;

		return nullptr;
	}

	unsigned int report::get_item_name_print_width() const
	{
		const unsigned int padding = 4;
		unsigned int width = 20;
		for (auto expense : m_expenses)
		{
			for (auto item : expense->items())
			{
				if (item->name().length() > width)
					width = item->name().length();
			}
		}
		
		return width + padding;
	}

	void report::add_payment_for_person(const std::shared_ptr<person>& person, const std::string& name, float amount)
	{
		m_info[person].payments.push_back(report_payment(name, amount));
		update_amount(person, -amount);
	}

	void report::add_expense_for_person(const std::shared_ptr<person>& person, const std::string& name, float weight, float amount)
	{
		m_info[person].expenses.push_back(report_expense(name, weight, amount));
		update_amount(person, weight * amount);
	}

	void report::update_amount(const std::weak_ptr<person>& person, float difference)
	{
		report::owing_totals_table::iterator owingTotal = std::find_if(m_owingTotals.begin(), m_owingTotals.end(),
			[&person](const std::pair<std::weak_ptr<divida::person>, float>& current) { return current.first.lock() == person.lock(); });
		if (owingTotal == m_owingTotals.end())
			m_owingTotals.push_back(std::make_pair(person, difference));
		else
			owingTotal->second += difference;
	}

	report_expense::report_expense(const std::string& name, float weight, float amount) : name(name), weight(weight), amount(amount)
	{
	}

	report_payment::report_payment(const std::string& name, float amount) : name(name), amount(amount)
	{
	}
}
