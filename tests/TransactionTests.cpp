#include "divida_tests.h"

#include <divida/Transaction.h>

TEST_CASE("Transaction - Construction", "[transaction]")
{
	auto fromPerson = std::make_shared<Divida::Person>(Divida::Tests::NAME_FRODO);
	auto toPerson = std::make_shared<Divida::Person>(Divida::Tests::NAME_GANDALF);

	auto fromPersonWeak = std::weak_ptr<Divida::Person>(fromPerson);
	auto toPersonWeak = std::weak_ptr<Divida::Person>(toPerson);
	auto amount = 12.35f;

	Divida::Transaction transaction(fromPersonWeak, toPersonWeak, amount);

	CHECK(fromPerson == transaction.FromPerson().lock());
	CHECK(toPerson == transaction.ToPerson().lock());
	CHECK(amount == transaction.Amount());
}
