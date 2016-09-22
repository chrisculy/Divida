#include "divida_tests.h"

#include <divida/beneficiary.h>
#include <divida/date.h>
#include <divida/expense.h>
#include <divida/group.h>
#include <divida/item.h>
#include <divida/person.h>
#include <divida/report.h>
#include <divida/to_string.h>
#include <divida/transaction.h>

TEST_CASE("to_string - divida types", "[to_string]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);

	SECTION("beneficiary")
	{
		auto beneficiary = divida::beneficiary(group.person(divida::tests::c_nameFrodo), 1.0f);
		CHECK("[[Frodo], 1.00]" == divida::to_string(beneficiary));
	}
	SECTION("date")
	{
		auto date = divida::date::create(21, 4, 2012);
		CHECK("4/21/2012" == divida::to_string(date));
	}
	SECTION("expense")
	{
		auto payer = group.person(divida::tests::c_nameGandalf);
		auto payerWeak = std::weak_ptr<divida::person>(payer);
		auto name = std::string("Weapons");
		auto date = divida::date::create(17, 3, 1946);

		auto expense = divida::expense(name, date, payer);
		auto itemName = std::string("Sting");
		auto itemCost = 15.37f;
		auto person = group.person(divida::tests::c_nameFrodo);
		auto beneficiary = divida::beneficiary(person);
		auto beneficiaries = std::vector<divida::beneficiary>{ beneficiary };
		expense.add_item(divida::item(itemName, itemCost, beneficiaries));
		CHECK("[Weapons, 3/17/1946, 15.37, [Gandalf], [[Sting, 15.37, [[[Frodo], 1.00]]]]]" == divida::to_string(expense));
	}
	SECTION("item")
	{
		auto item = divida::item("Peanuts", 1.27f);
		CHECK("[Peanuts, 1.27, []]" == divida::to_string(item));
	}
	SECTION("person")
	{
		auto person = group.person(divida::tests::c_nameFrodo);
		auto s = divida::to_string(person);
		CHECK("[Frodo]" == divida::to_string(person));
	}
	SECTION("transaction")
	{
		auto fromPerson = group.person(divida::tests::c_nameFrodo);
		auto toPerson = group.person(divida::tests::c_nameGandalf);

		auto fromPersonWeak = std::weak_ptr<divida::person>(fromPerson);
		auto toPersonWeak = std::weak_ptr<divida::person>(toPerson);
		auto amount = 12.35f;

		auto transaction = divida::transaction(fromPersonWeak, toPersonWeak, amount);
		CHECK("[[Frodo] pays $12.35 to [Gandalf]]" == divida::to_string(transaction));
	}
}

TEST_CASE("to_string - STL pointer types", "[to_string]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);

	SECTION("unique_ptr")
	{
		SECTION("non-null pointer")
		{
			auto person = group.person(divida::tests::c_nameGandalf);
			CHECK("[Gandalf]" == divida::to_string(person));
		}
		SECTION("null pointer")
		{
			std::unique_ptr<divida::person> person;
			CHECK(divida::c_toStringNull == divida::to_string(person));
		}
	}
	SECTION("shared_ptr")
	{
		SECTION("non-null pointer")
		{
			auto person = group.person(divida::tests::c_nameMerry);
			CHECK("[Merry]" == divida::to_string(person));
		}
		SECTION("null pointer")
		{
			std::shared_ptr<divida::person> person;
			CHECK(divida::c_toStringNull == divida::to_string(person));
		}
	}
	SECTION("weak_ptr")
	{
		SECTION("non-null pointer")
		{
			auto person = group.person(divida::tests::c_nameFrodo);
			CHECK("[Frodo]" == divida::to_string(person));
		}
		SECTION("invalid pointer")
		{
			std::weak_ptr<divida::date> date;
			{
				auto specialDate = std::make_shared<divida::date>(divida::date::create(4, 2, 2016));
				date = specialDate;
				CHECK("2/4/2016" == divida::to_string(date));
			}
			CHECK(divida::c_toStringInvalidWeakPointer == divida::to_string(date));
		}
	}
}


