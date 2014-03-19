#pragma once

#include <vector>

#include "Beneficiary.h"
#include "Core.h"
#include "Object.h"

namespace Divida
{
	class Item : public Object
	{
	public:
		Item(const std::wstring& name, float cost);
		Item(const std::wstring& name, float cost, const std::vector<std::shared_ptr<Beneficiary>>& beneficiaries);

		const std::vector<std::shared_ptr<Beneficiary>>& Beneficiaries() const;
		float Cost() const;

		void AddBeneficiary(const std::shared_ptr<Beneficiary> beneficiary);
		void RemoveBeneficiary(const std::shared_ptr<Beneficiary> beneficiary);

		std::wstring ToString() const;
	private:
		float m_cost;
		std::vector<std::shared_ptr<Beneficiary>> m_beneficiaries;
	};

	DECLARE_TO_STRING_SMART_PTRS(Item);
}
