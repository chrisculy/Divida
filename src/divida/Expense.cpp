#include "Expense.h"
#include "to_string.h"

#include <sstream>

namespace divida
{
	expense::expense(const std::string& name, const divida::date& date, const std::shared_ptr<person> payer) : object(name), m_date(date), m_payer(payer)
	{
	}

	const divida::date& expense::date() const
	{
		return m_date;
	}

	const std::shared_ptr<person> expense::payer() const
	{
		return m_payer;
	}

	float expense::total() const
	{
		float total = 0.0f;
		for (auto item : m_items)
			total += item->cost();

		return total;
	}

	const std::vector<std::shared_ptr<item>>& expense::items() const
	{
		return m_items;
	}

	void expense::set_date(const divida::date& date)
	{
		// TODO: validate the date.
		m_date = date;
	}

	void expense::set_payer(const std::shared_ptr<person> payer)
	{
		// TODO: validate the payer.
		m_payer = payer;
	}

	void expense::add_item(const std::string& name, float cost, const std::vector<std::shared_ptr<beneficiary>>& beneficiaries)
	{
		m_items.push_back(std::make_shared<item>(name, cost, beneficiaries));
	}

	void expense::add_items(const std::vector<std::pair<std::string, float>>& namesAndCosts, const std::vector<std::shared_ptr<beneficiary>>& beneficiaries)
	{
		for (auto nameAndCost : namesAndCosts)
			m_items.push_back(std::make_shared<item>(nameAndCost.first, nameAndCost.second, beneficiaries));
	}

	std::string expense::ToString() const
	{
		std::stringstream s;
		s << c_toStringObjectBeginToken << name() << c_toStringDelimiter << m_date.ToString() << c_toStringDelimiter << total() << c_toStringDelimiter << m_payer << c_toStringDelimiter << m_items << c_toStringObjectEndToken;
		return s.str();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<expense>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<expense>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<expense>& ptr)
	{
		if (std::shared_ptr<expense> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
