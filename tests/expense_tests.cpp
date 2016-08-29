#include "divida_tests.h"

#include <divida/expense.h>

TEST_CASE("expense - Construction", "[expense]")
{
	auto payer = std::make_shared<divida::person>(divida::Tests::NAME_GANDALF);
	auto payerWeak = std::weak_ptr<divida::person>(payer);
	auto name = std::string("Weapons");
	auto date = divida::date::create(17, 3, 1946);

	divida::expense expense(name, date, payer);

	CHECK(name == expense.name());
	CHECK(date == expense.date());
	CHECK(payer == expense.payer());
}

TEST_CASE("expense - AddAndGetSingleItem", "[expense]")
{
	auto payer = std::make_shared<divida::person>(divida::Tests::NAME_GANDALF);
	auto date = divida::date::create(17, 3, 1946);

	divida::expense expense("Weapons", date, payer);

	auto itemName = std::string("Sting");
	auto itemCost = 15.37f;
	auto person = std::make_shared<divida::person>(divida::Tests::NAME_FRODO);
	auto beneficiary = std::make_shared<divida::beneficiary>(person);
	auto beneficiaries = std::vector<std::shared_ptr<divida::beneficiary>> { beneficiary };

	expense.add_item(itemName, itemCost, beneficiaries);

	auto items = expense.items();
	size_t expectedSize = 1;
	CHECK(expectedSize == items.size());
	CHECK(itemName == items[0]->name());
	CHECK(itemCost == items[0]->cost());
	CHECK(beneficiaries == items[0]->beneficiaries());
}

TEST_CASE("expense - AddAndGetMultipleItems", "[expense]")
{
	// TODO: Unimplemented!
}

TEST_CASE("expense - SetAndGetDate", "[expense]")
{
	// TODO: Unimplemented!
}

TEST_CASE("expense - SetAndGetPayer", "[expense]")
{
	// TODO: Unimplemented!
}

TEST_CASE("expense - total", "[expense]")
{
	// TODO: Unimplemented!
}
