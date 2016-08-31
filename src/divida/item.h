#pragma once

#include "beneficiary.h"
#include "object.h"

#include <vector>

namespace divida
{
	class item : public object
	{
	public:
		item(const std::string& name, float cost);
		item(const std::string& name, float cost, const std::vector<std::shared_ptr<beneficiary>>& beneficiaries);

		const std::vector<std::shared_ptr<beneficiary>>& beneficiaries() const;
		float cost() const;

		void add_beneficiary(const std::shared_ptr<beneficiary> beneficiary);
		void remove_beneficiary(const std::shared_ptr<beneficiary> beneficiary);

	private:
		float m_cost;
		std::vector<std::shared_ptr<beneficiary>> m_beneficiaries;
	};
}
