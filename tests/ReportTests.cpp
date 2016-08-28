#include "divida_tests.h"

#include <divida/Report.h>

namespace
{

const std::string c_reportName = "The Journey to Rivendell";

}

TEST_CASE("Report - Construction", "[report]")
{
	Divida::Report report(c_reportName);

	CHECK(c_reportName == report.Name());
}

TEST_CASE("Report - AddAndGetPerson", "[report]")
{
	Divida::Report report(c_reportName);
				
	// TODO: Unimplemented!
}

TEST_CASE("Report - NewAndGetExpense", "[report]")
{
	Divida::Report report(c_reportName);

	// TODO: Unimplemented!
}

TEST_CASE("Report - CalculateTransactions", "[report]")
{
	Divida::Report report(c_reportName);

	// TODO: Unimplemented!
}
