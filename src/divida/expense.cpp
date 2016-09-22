#include "expense.h"

namespace divida
{
	expense::expense(const std::string& name, const divida::date& date, const std::shared_ptr<person> payer)
		: m_name{ name }
		, m_date{ date }
		, m_payer{ payer }
	{
	}

	const divida::date& expense::date() const
	{
		return m_date;
	}

	const std::string& expense::name() const
	{
		return m_name;
	}

	const std::shared_ptr<person> expense::payer() const
	{
		return m_payer;
	}

	float expense::total() const
	{
		float total = 0.0f;
		for (auto item : m_items)
			total += item.cost();

		return total;
	}

	const std::vector<item>& expense::items() const
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
	
	void expense::add_item(item&& item)
	{
		m_items.emplace_back(std::move(item));
	}

	void expense::add_items(const std::vector<std::pair<std::string, float>>& namesAndCosts, const std::vector<beneficiary>& beneficiaries)
	{
		for (auto nameAndCost : namesAndCosts)
			m_items.emplace_back(nameAndCost.first, nameAndCost.second, beneficiaries);
	}
}
