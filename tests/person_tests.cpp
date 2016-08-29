#include "divida_tests.h"

#include <divida/person.h>

TEST_CASE("person - Construction", "[person]")
{
	divida::person person(divida::tests::c_nameFrodo);
				
	CHECK(divida::tests::c_nameFrodo == person.name());
}
