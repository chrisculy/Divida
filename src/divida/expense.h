#pragma once

#include "beneficiary.h"
#include "date.h"
#include "item.h"
#include "person.h"

#include <memory>
#include <vector>

namespace divida
{
	class expense
	{
	public:
		expense(const std::string& name, const divida::date& date, const std::shared_ptr<person> payer);

		const divida::date& date() const;
		const std::string& name() const;
		const std::shared_ptr<person> payer() const;
		float total() const;
		const std::vector<item>& items() const;

		void set_date(const divida::date& date);
		void set_payer(const std::shared_ptr<person> payer);

		void add_item(item&& item);
		void add_items(const std::vector<std::pair<std::string, float>>& namesAndCosts, const std::vector<beneficiary>& beneficiaries);

	private:
		std::string m_name;
		divida::date m_date;
		std::shared_ptr<person> m_payer;
		std::vector<item> m_items;
	};
}
