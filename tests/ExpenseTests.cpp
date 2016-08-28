#include "divida_tests.h"

#include <divida/Expense.h>

TEST_CASE("Expense - Construction", "[expense]")
{
	auto payer = std::make_shared<Divida::Person>(Divida::Tests::NAME_GANDALF);
	auto payerWeak = std::weak_ptr<Divida::Person>(payer);
	auto name = std::string("Weapons");
	auto date = Divida::Date::Create(17, 3, 1946);

	Divida::Expense expense(name, date, payer);

	CHECK(name == expense.Name());
	CHECK(date == expense.Date());
	CHECK(payer == expense.Payer());
}

TEST_CASE("Expense - AddAndGetSingleItem", "[expense]")
{
	auto payer = std::make_shared<Divida::Person>(Divida::Tests::NAME_GANDALF);
	auto date = Divida::Date::Create(17, 3, 1946);

	Divida::Expense expense("Weapons", date, payer);

	auto itemName = std::string("Sting");
	auto itemCost = 15.37f;
	auto person = std::make_shared<Divida::Person>(Divida::Tests::NAME_FRODO);
	auto beneficiary = std::make_shared<Divida::Beneficiary>(person);
	auto beneficiaries = std::vector<std::shared_ptr<Divida::Beneficiary>> { beneficiary };

	expense.AddItem(itemName, itemCost, beneficiaries);

	auto items = expense.Items();
	size_t expectedSize = 1;
	CHECK(expectedSize == items.size());
	CHECK(itemName == items[0]->Name());
	CHECK(itemCost == items[0]->Cost());
	CHECK(beneficiaries == items[0]->Beneficiaries());
}

TEST_CASE("Expense - AddAndGetMultipleItems", "[expense]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Expense - SetAndGetDate", "[expense]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Expense - SetAndGetPayer", "[expense]")
{
	// TODO: Unimplemented!
}

TEST_CASE("Expense - Total", "[expense]")
{
	// TODO: Unimplemented!
}
