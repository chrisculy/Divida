#pragma once

#include "Beneficiary.h"
#include "Date.h"
#include "Item.h"
#include "Object.h"
#include "Person.h"

#include <memory>
#include <vector>

namespace divida
{
	class expense : public object
	{
	public:
		expense(const std::string& name, const divida::date& date, const std::shared_ptr<person> payer);

		const divida::date& date() const;
		const std::shared_ptr<person> payer() const;
		float total() const;
		const std::vector<std::shared_ptr<item>>& items() const;

		void set_date(const divida::date& date);
		void set_payer(const std::shared_ptr<person> payer);

		void add_item(const std::string& name, float cost, const std::vector<std::shared_ptr<beneficiary>>& beneficiaries);
		void add_items(const std::vector<std::pair<std::string, float>>& namesAndCosts, const std::vector<std::shared_ptr<beneficiary>>& beneficiaries);

		std::string ToString() const;

	private:
		divida::date m_date;
		std::shared_ptr<person> m_payer;
		std::vector<std::shared_ptr<item>> m_items;
	};

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<expense>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<expense>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<expense>& ptr);
}
