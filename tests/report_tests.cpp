#include "divida_tests.h"

#include <divida/group.h>
#include <divida/report.h>

namespace
{

const std::string c_reportName = "The Journey to Rivendell";

}

TEST_CASE("report - Construction", "[report]")
{
	divida::group group(divida::tests::c_nameTestGroup);
	auto report = group.report(c_reportName);

	CHECK(c_reportName == report->name());
}

TEST_CASE("report - AddAndGetPerson", "[report]")
{
	divida::group group(divida::tests::c_nameTestGroup);
	auto report = group.report(c_reportName);
				
	// TODO: Unimplemented!
}

TEST_CASE("report - NewAndGetExpense", "[report]")
{
	divida::group group(divida::tests::c_nameTestGroup);
	auto report = group.report(c_reportName);

	// TODO: Unimplemented!
}

TEST_CASE("report - Run", "[report]")
{
	divida::group group(divida::tests::c_nameTestGroup);
	auto report = group.report(c_reportName);

	// TODO: Unimplemented!
}
