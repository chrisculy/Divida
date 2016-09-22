#pragma once

#include "date.h"
#include "expense.h"
#include "person.h"
#include "transaction.h"

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

	class report
	{
	public:
		const std::string& name() const;
		void set_name(const std::string& name);
		
		const expense& add_expense(std::unique_ptr<expense> expense);

		const std::vector<std::unique_ptr<expense>>& expenses() const;

		std::vector<std::shared_ptr<transaction>> run();
		const report_info* get_report_info_for_person(const std::string& name) const;
		unsigned int get_item_name_print_width() const;

		bool operator==(const report& other) const;
		bool operator!=(const report& other) const;

	private:
		friend class group;

		explicit report(const std::string& name);

		typedef std::vector<std::pair<std::weak_ptr<person>, float>> owing_totals_table;

		void add_payment_for_person(const std::shared_ptr<person>& person, const std::string& name, float amount);
		void add_expense_for_person(const std::shared_ptr<person>& person, const std::string& name, float weight, float amount);
		void update_amount(const std::weak_ptr<person>& person, float difference);

		std::string m_name;
		std::vector<std::unique_ptr<expense>> m_expenses;
		owing_totals_table m_owingTotals;
		std::map<std::shared_ptr<person>, report_info> m_info;
	};
}
