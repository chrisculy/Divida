#include "pch.h"

#include "Core.h"
#include "Expense.h"

namespace Divida
{
	Expense::Expense(const std::wstring& name, const Divida::Date& date, const std::shared_ptr<Person> payer) : Object(name), m_date(date), m_payer(payer)
	{
	}

	const Date& Expense::Date() const
	{
		return m_date;
	}

	const std::shared_ptr<Person> Expense::Payer() const
	{
		return m_payer;
	}

	const float Expense::Total() const
	{
		float total = 0.0f;
		for (auto item : m_items)
			total += item->Cost();

		return total;
	}

	const std::vector<std::shared_ptr<Item>>& Expense::Items() const
	{
		return m_items;
	}

	void Expense::SetDate(const Divida::Date& date)
	{
		// TODO: validate the date.
		m_date = date;
	}

	void Expense::SetPayer(const std::shared_ptr<Person> payer)
	{
		// TODO: validate the payer.
		m_payer = payer;
	}

	void Expense::AddItem(const std::wstring& name, float cost, const std::vector < std::shared_ptr < Beneficiary >> &beneficiaries)
	{
		m_items.push_back(std::make_shared<Item>(name, cost, beneficiaries));
	}

	void Expense::AddItems(const std::vector<std::pair<std::wstring, float>>& namesAndCosts, const std::vector<std::shared_ptr<Beneficiary>>& beneficiaries)
	{
		for (auto nameAndCost : namesAndCosts)
			m_items.push_back(std::make_shared<Item>(nameAndCost.first, nameAndCost.second, beneficiaries));
	}

	std::wstring Expense::ToString() const
	{
		std::wstringstream s;
		s << TO_STRING_OBJECT_BEGIN_TOKEN << Name() << TO_STRING_DELIMITER << m_date.ToString() << TO_STRING_DELIMITER << Total() << TO_STRING_DELIMITER << m_payer << TO_STRING_DELIMITER << m_items << TO_STRING_OBJECT_END_TOKEN;
		return s.str();
	}

	IMPLEMENT_TO_STRING_SMART_PTRS(Expense);
}
