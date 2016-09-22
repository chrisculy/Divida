#pragma once

#include "beneficiary.h"

#include <vector>

namespace divida
{
	class item
	{
	public:
		item(const std::string& name, float cost);
		item(const std::string& name, float cost, const std::vector<beneficiary>& beneficiaries);

		const std::vector<beneficiary>& beneficiaries() const;
		const std::string& name() const;
		float cost() const;

		void add_beneficiary(const beneficiary& beneficiary);
		void remove_beneficiary(const beneficiary& beneficiary);

	private:
		std::string m_name;
		float m_cost;
		std::vector<beneficiary> m_beneficiaries;
	};
}
