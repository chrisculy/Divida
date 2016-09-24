#include "item.h"

#include <algorithm>

namespace divida
{
	item::item(const std::string& name, float cost)
		: m_name{ name }
		, m_cost{ cost }
	{
	}

	item::item(const std::string& name, float cost, const std::vector<beneficiary>& beneficiaries)
		: m_name{ name }
		, m_cost{ cost }
		, m_beneficiaries{ beneficiaries }
	{
	}

	const std::vector<beneficiary>& item::beneficiaries() const
	{
		return m_beneficiaries;
	}

	const std::string& item::name() const
	{
		return m_name;
	}

	float item::cost() const
	{
		return m_cost;
	}

	void item::add_beneficiary(const beneficiary& beneficiary)
	{
		// TODO: do smart stuff like combining two beneficiaries that reference the same person with different weights
		// TODO: don't add a beneficiary if it is already in the list
		m_beneficiaries.emplace_back(beneficiary);
	}

	void item::remove_beneficiary(const beneficiary& beneficiary)
	{
		auto iter = std::find(m_beneficiaries.begin(), m_beneficiaries.end(), beneficiary);
		if (iter != m_beneficiaries.end())
			m_beneficiaries.erase(iter);
	}

	bool item::operator==(const item& other) const
	{
		if (m_name != other.m_name || m_cost != other.m_cost || m_beneficiaries.size() != other.m_beneficiaries.size())
			return false;

		for (size_t i = 0; i < m_beneficiaries.size(); i++)
		{
			if (m_beneficiaries[i] != other.m_beneficiaries[i])
				return false;
		}

		return true;
	}

	bool item::operator!=(const item& other) const
	{
		return !(*this == other);
	}
}
