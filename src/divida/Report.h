#pragma once

#include "Date.h"
#include "Expense.h"
#include "Person.h"
#include "Transaction.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace divida
{
	struct report_expense
	{
		report_expense(const std::string& name, float weight, float amount);

		std::string name;
		float weight;
		float amount;
	};

	struct report_payment
	{
		report_payment(const std::string& name, float amount);

		std::string name;
		float amount;
	};

	struct report_info
	{
		std::vector<report_payment> payments;
		std::vector<report_expense> expenses;
	};

	class report : public object
	{
	public:
		report(const std::string& name);

		void add_person(const std::string& name);
		const std::shared_ptr<person> get_person(const std::string& name) const;

		const std::shared_ptr<expense> new_expense(const std::string& name, const date& date, const std::shared_ptr<person> payer);
		const std::shared_ptr<expense> get_expense(const std::string& name) const;

		const std::vector<std::shared_ptr<person>>& persons() const;
		const std::vector<std::shared_ptr<expense>>& expenses() const;

		std::vector<std::shared_ptr<transaction>> calculate_transactions();
		const report_info* get_report_info_for_person(const std::string& name) const;
		unsigned int get_item_name_print_width() const;

	private:
		friend class report_xml_serializer;

		typedef std::vector<std::pair<std::weak_ptr<person>, float>> owing_totals_table;

		void add_payment_for_person(const std::shared_ptr<person>& person, const std::string& name, float amount);
		void add_expense_for_person(const std::shared_ptr<person>& person, const std::string& name, float weight, float amount);
		void update_amount(const std::weak_ptr<person>& person, float difference);

		std::vector<std::shared_ptr<person>> m_persons;
		std::vector<std::shared_ptr<expense>> m_expenses;
		owing_totals_table m_owingTotals;
		std::map<std::shared_ptr<person>, report_info> m_info;
	};
}
