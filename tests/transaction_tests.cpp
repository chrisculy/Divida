#include "divida_tests.h"

#include <divida/transaction.h>

TEST_CASE("transaction - Construction", "[transaction]")
{
	auto fromPerson = std::make_shared<divida::person>(divida::tests::c_nameFrodo);
	auto toPerson = std::make_shared<divida::person>(divida::tests::c_nameGandalf);

	auto fromPersonWeak = std::weak_ptr<divida::person>(fromPerson);
	auto toPersonWeak = std::weak_ptr<divida::person>(toPerson);
	auto amount = 12.35f;

	divida::transaction transaction(fromPersonWeak, toPersonWeak, amount);

	CHECK(fromPerson == transaction.from_person().lock());
	CHECK(toPerson == transaction.to_person().lock());
	CHECK(amount == transaction.amount());
}
