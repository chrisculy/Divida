#include "divida_tests.h"

#include <divida/expense.h>
#include <divida/group.h>

TEST_CASE("expense - Construction", "[expense]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);
	auto payer = group.person(divida::tests::c_nameGandalf);
	auto name = std::string("Weapons");
	auto date = divida::date::create(17, 3, 1946);

	divida::expense expense(name, date, payer);

	CHECK(name == expense.name());
	CHECK(date == expense.date());
	CHECK(payer == expense.payer());
}

TEST_CASE("expense - AddAndGetSingleItem", "[expense]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);
	auto payer = group.person(divida::tests::c_nameGandalf);
	auto date = divida::date::create(17, 3, 1946);

	divida::expense expense("Weapons", date, payer);

	auto itemName = std::string("Sting");
	auto itemCost = 15.37f;
	auto person = group.person(divida::tests::c_nameFrodo);
	auto beneficiary = divida::beneficiary(person);
	auto beneficiaries = std::vector<divida::beneficiary> { beneficiary };

	expense.add_item(divida::item(itemName, itemCost, beneficiaries));

	auto items = expense.items();
	size_t expectedSize = 1;
	CHECK(expectedSize == items.size());
	CHECK(itemName == items[0].name());
	CHECK(itemCost == items[0].cost());
	CHECK(beneficiaries == items[0].beneficiaries());
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
