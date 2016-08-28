#include "divida_tests.h"

#include <divida/Beneficiary.h>

TEST_CASE("Beneficiary - Construction", "[beneficiary]")
{
	auto person = std::make_shared<Divida::Person>(Divida::Tests::NAME_FRODO);
	auto weight = 0.75f;

	Divida::Beneficiary beneficiary(person, weight);

	CHECK(person == beneficiary.Person());
	CHECK(weight == Approx(beneficiary.Weight()));// , FLOAT_EPSILON);
}
