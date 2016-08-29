#include "divida_tests.h"

#include <divida/person.h>

TEST_CASE("person - Construction", "[person]")
{
	divida::person person(divida::Tests::NAME_FRODO);
				
	CHECK(divida::Tests::NAME_FRODO == person.name());
}
