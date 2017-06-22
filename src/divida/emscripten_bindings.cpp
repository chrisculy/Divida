#include "beneficiary.h"
#include "date.h"
#include "expense.h"
#include "group.h"
#include "item.h"
#include "person.h"
#include "report.h"
#include "to_string.h"
#include "transaction.h"

#include <emscripten/bind.h>

using namespace emscripten;

namespace divida
{
	std::string transaction_to_string(divida::transaction& transaction)
	{
		return divida::to_string(transaction);
	}
}

EMSCRIPTEN_BINDINGS(divida)
{
	class_<divida::beneficiary>("beneficiary")
		.constructor<const std::shared_ptr<divida::person>, float>()
		.function("person", &divida::beneficiary::person)
		.function("weight", &divida::beneficiary::weight)
		.function("equals", &divida::beneficiary::operator==);

	register_vector<divida::beneficiary>("beneficiary_vector");

	class_<divida::date>("date")
		.class_function("create", &divida::date::create)
		.function("day", &divida::date::day)
		.function("month", &divida::date::month)
		.function("year", &divida::date::year)
		.function("equals", &divida::date::operator==);

	class_<divida::expense>("expense")
		.constructor<const std::string&, const divida::date&, const std::shared_ptr<divida::person>>()
		.property("date", &divida::expense::date, &divida::expense::set_date)
		.property("payer", &divida::expense::payer, &divida::expense::set_payer)
		.function("name", &divida::expense::name)
		.function("total", &divida::expense::total)
		.function("items", &divida::expense::items)
		.function("add_item", &divida::expense::add_item)
		.function("add_items", &divida::expense::add_items)
		.function("equals", &divida::expense::operator==);

	using person_from_name_function = std::shared_ptr<divida::person>(divida::group::*)(const std::string&);

	class_<divida::group>("group")
		.constructor<std::string>()
		.function("person", static_cast<person_from_name_function>(&divida::group::person))
		.function("report", &divida::group::report)
		.function("persons", &divida::group::persons)
		.function("reports", &divida::group::reports)
		.property("name", &divida::group::name, &divida::group::set_name);

	class_<std::pair<std::string, float>>("name_cost_pair")
		.constructor<std::string, float>();
		
	register_vector<std::pair<std::string, float>>("name_cost_pair_vector");

	class_<divida::item>("item")
		.constructor<const std::string&, float>()
		.constructor<const std::string&, float, const std::vector<divida::beneficiary>&>()
		.function("beneficiaries", &divida::item::beneficiaries)
		.function("name", &divida::item::name)
		.function("cost", &divida::item::cost)
		.function("add_beneficiary", &divida::item::add_beneficiary)
		.function("remove_beneficiary", &divida::item::remove_beneficiary)
		.function("equals", &divida::item::operator==);

	class_<divida::person>("person")
		.smart_ptr<std::shared_ptr<divida::person>>("person")
		.function("id", &divida::person::id)
		.function("name", &divida::person::name)
		.function("equals", &divida::person::operator==);

	class_<divida::report>("report")
		.smart_ptr<std::shared_ptr<divida::report>>("report")
		.property("name", &divida::report::name, &divida::report::set_name)
		.function("add_expense", &divida::report::add_expense)
		.function("expenses", &divida::report::expenses)
		.function("run", &divida::report::run);

	class_<divida::transaction>("transaction")
		.function("from_person", &divida::transaction::from_person)
		.function("to_person", &divida::transaction::to_person)
		.function("amount", &divida::transaction::amount);

	function("transaction_to_string", &divida::transaction_to_string);

	register_vector<divida::transaction>("transaction_vector");
}
