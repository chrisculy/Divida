#include "divida_tests.h"

#include <divida/beneficiary.h>
#include <divida/date.h>
#include <divida/expense.h>
#include <divida/group.h>
#include <divida/item.h>
#include <divida/person.h>
#include <divida/report.h>

TEST_CASE("Integration Test", "[integration]")
{
	auto group = divida::group("Camping Friends");

	auto arav = group.person("Arav Jindal");
	auto marco = group.person("Marco Sanchez");
	auto grace = group.person("Grace Yun");
	auto maggie = group.person("Maggie McDonald");

	auto expenseFood = std::make_unique<divida::expense>("Food", divida::date::create(12, 7, 2009), grace);
	expenseFood->add_items(
		{ { "Apples", 4.67f },
		{ "Hot dogs", 8.55f },
		{ "Hot dog buns", 4.36f },
		{ "Beans", 3.79f },
		{ "Trail mix", 9.82f },
		{ "Potato chips", 5.03f } },
		{ divida::beneficiary{ arav }, divida::beneficiary{ marco }, divida::beneficiary{ grace }, divida::beneficiary{ maggie } }
	);

	auto expenseCampsites = std::make_unique<divida::expense>("Campsites", divida::date::create(13, 7, 2009), arav);
	expenseCampsites->add_item({ "Campsite permit", 183.45f, { divida::beneficiary{ arav, 4.0f }, divida::beneficiary{ marco, 3.0f }, divida::beneficiary{ grace, 4.0f }, divida::beneficiary{ maggie, 4.0f } } });

	auto expenseCampingSupplies = std::make_unique<divida::expense>("Camping supplies", divida::date::create(10, 7, 2009), maggie);
	expenseCampingSupplies->add_item({ "Two person tent", 95.78f,{ divida::beneficiary{ maggie }, divida::beneficiary{ grace } } });
	expenseCampingSupplies->add_item({ "Headlamp", 14.56f, { divida::beneficiary{ marco } } });
	expenseCampingSupplies->add_item({ "Tarp", 7.60f, { divida::beneficiary{ arav } } });
	expenseCampingSupplies->add_item({ "Hiking boots", 32.14f, { divida::beneficiary{ maggie } } });
	expenseCampingSupplies->add_item({ "Firewood", 12.00f, { divida::beneficiary{ arav }, divida::beneficiary{ marco }, divida::beneficiary{ grace, 5.0 }, divida::beneficiary{ maggie } } });

	auto report = group.report("Pacific Crest Trail Camping Trip");

	report->add_expense(std::move(expenseFood));
	report->add_expense(std::move(expenseCampsites));
	report->add_expense(std::move(expenseCampingSupplies));

	auto transactions = report->run();

	CHECK(transactions.size() == 3);

	CHECK(transactions[0]->from_person().lock() == grace);
	CHECK(transactions[0]->to_person().lock() == arav);
	CHECK(transactions[0]->amount() == Approx(77.15f).epsilon(divida::tests::c_moneyEpsilon));

	CHECK(transactions[1]->from_person().lock() == marco);
	CHECK(transactions[1]->to_person().lock() == arav);
	CHECK(transactions[1]->amount() == Approx(39.23f).epsilon(divida::tests::c_moneyEpsilon));
	
	CHECK(transactions[2]->from_person().lock() == marco);
	CHECK(transactions[2]->to_person().lock() == maggie);
	CHECK(transactions[2]->amount() == Approx(22.57f).epsilon(divida::tests::c_moneyEpsilon));
}
