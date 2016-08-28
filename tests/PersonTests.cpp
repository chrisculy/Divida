#include "divida_tests.h"

#include <divida/Person.h>

TEST_CASE("Person - Construction", "[person]")
{
	Divida::Person person(Divida::Tests::NAME_FRODO);
				
	CHECK(Divida::Tests::NAME_FRODO == person.Name());
}
