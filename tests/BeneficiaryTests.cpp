#include "divida_tests.h"

#include <divida/Beneficiary.h>

TEST_CASE("beneficiary - Construction", "[beneficiary]")
{
	auto person = std::make_shared<divida::person>(divida::Tests::NAME_FRODO);
	auto weight = 0.75f;

	divida::beneficiary beneficiary(person, weight);

	CHECK(person == beneficiary.person());
	CHECK(weight == Approx(beneficiary.weight()));// , FLOAT_EPSILON);
}
