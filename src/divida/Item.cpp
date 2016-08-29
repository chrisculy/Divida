#include "Item.h"
#include "to_string.h"

#include <sstream>

namespace divida
{
	item::item(const std::string& name, float cost) : object(name), m_cost(cost)
	{
	}

	item::item(const std::string& name, float cost, const std::vector<std::shared_ptr<beneficiary>>& beneficiaries) : object(name), m_cost(cost), m_beneficiaries(beneficiaries)
	{
	}

	const std::vector<std::shared_ptr<beneficiary>>& item::beneficiaries() const
	{
		return m_beneficiaries;
	}

	float item::cost() const
	{
		return m_cost;
	}

	void item::add_beneficiary(const std::shared_ptr<beneficiary> beneficiary)
	{
		// TODO: do smart stuff like combining two beneficiaries that reference the same person with different weights
		// TODO: don't add a beneficiary if it is already in the list
		m_beneficiaries.push_back(beneficiary);
	}

	void item::remove_beneficiary(const std::shared_ptr<beneficiary> beneficiary)
	{
		auto iter = std::find(m_beneficiaries.begin(), m_beneficiaries.end(), beneficiary);
		if (iter != m_beneficiaries.end())
			m_beneficiaries.erase(iter);
	}

	std::string item::ToString() const
	{
		std::stringstream s;
		s << c_toStringObjectBeginToken << name() << c_toStringDelimiter << m_cost << c_toStringDelimiter << m_beneficiaries << c_toStringObjectEndToken;
		return s.str();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<item>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<item>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<item>& ptr)
	{
		if (std::shared_ptr<item> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
