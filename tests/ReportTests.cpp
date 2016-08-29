#include "divida_tests.h"

#include <divida/Report.h>

namespace
{

const std::string c_reportName = "The Journey to Rivendell";

}

TEST_CASE("report - Construction", "[report]")
{
	divida::report report(c_reportName);

	CHECK(c_reportName == report.name());
}

TEST_CASE("report - AddAndGetPerson", "[report]")
{
	divida::report report(c_reportName);
				
	// TODO: Unimplemented!
}

TEST_CASE("report - NewAndGetExpense", "[report]")
{
	divida::report report(c_reportName);

	// TODO: Unimplemented!
}

TEST_CASE("report - calculate_transactions", "[report]")
{
	divida::report report(c_reportName);

	// TODO: Unimplemented!
}
