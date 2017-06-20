#include "divida_tests.h"

#include <divida/group.h>
#include <divida/transaction.h>

TEST_CASE("transaction - Construction", "[transaction]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);
	auto fromPerson = group.person(divida::tests::c_nameFrodo);
	auto toPerson = group.person(divida::tests::c_nameGandalf);
	auto amount = 12.35f;

	divida::transaction transaction(fromPerson, toPerson, amount);

	CHECK(fromPerson == transaction.from_person());
	CHECK(toPerson == transaction.to_person());
	CHECK(amount == transaction.amount());
}
