#include "divida_tests.h"

#include <divida/group.h>
#include <divida/person.h>

TEST_CASE("person - Construction", "[person]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);
	auto person = group.person(divida::tests::c_nameFrodo);
				
	CHECK(divida::tests::c_nameFrodo == person->name());
}
