#include "divida_tests.h"

#include <divida/beneficiary.h>
#include <divida/group.h>

TEST_CASE("beneficiary - Construction", "[beneficiary]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);
	auto person = group.person(divida::tests::c_nameFrodo);
	auto weight = 0.75f;

	divida::beneficiary beneficiary(person, weight);

	CHECK(person == beneficiary.person());
	CHECK(weight == Approx(beneficiary.weight()));
}
