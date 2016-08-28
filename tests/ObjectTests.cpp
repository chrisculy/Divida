#include "divida_tests.h"

#include <divida/Object.h>

TEST_CASE("Object - Construction", "[object]")
{
	auto name = std::string("The Object");
	Divida::Object object(name);

	CHECK(name == object.Name());
}
