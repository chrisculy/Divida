#include "pch.h"

#include "Item.h"

namespace Divida
{
	Item::Item(const std::wstring& name, float cost) : Object(name), m_cost(cost)
	{
	}

	Item::Item(const std::wstring& name, float cost, const std::vector<std::shared_ptr<Beneficiary>>& beneficiaries) : Object(name), m_cost(cost), m_beneficiaries(beneficiaries)
	{
	}

	const std::vector<std::shared_ptr<Beneficiary>>& Item::Beneficiaries() const
	{
		return m_beneficiaries;
	}

	float Item::Cost() const
	{
		return m_cost;
	}

	void Item::AddBeneficiary(const std::shared_ptr<Beneficiary> beneficiary)
	{
		// TODO: do smart stuff like combining two beneficiaries that reference the same person with different weights
		// TODO: don't add a beneficiary if it is already in the list
		m_beneficiaries.push_back(beneficiary);
	}

	void Item::RemoveBeneficiary(const std::shared_ptr<Beneficiary> beneficiary)
	{
		std::vector<std::shared_ptr<Beneficiary>>::iterator iter = std::find(m_beneficiaries.begin(), m_beneficiaries.end(), beneficiary);
		if (iter != m_beneficiaries.end())
			m_beneficiaries.erase(iter);
	}

	std::wstring Item::ToString() const
	{
		std::wstringstream s;
		s << TO_STRING_OBJECT_BEGIN_TOKEN << Name() << TO_STRING_DELIMITER << m_cost << TO_STRING_DELIMITER << m_beneficiaries << TO_STRING_OBJECT_END_TOKEN;
		return s.str();
	}

	wide_ostream& operator<<(wide_ostream& o, const std::unique_ptr<Item>& ptr)
	{
		return o << ptr->ToString();
	}

	wide_ostream& operator<<(wide_ostream& o, const std::shared_ptr<Item>& ptr)
	{
		return o << ptr->ToString();
	}

	wide_ostream& operator<<(wide_ostream& o, const std::weak_ptr<Item>& ptr)
	{
		if (std::shared_ptr<Item> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
