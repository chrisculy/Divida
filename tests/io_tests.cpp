#include "divida_tests.h"

#include <divida/beneficiary.h>
#include <divida/date.h>
#include <divida/expense.h>
#include <divida/group.h>
#include <divida/item.h>
#include <divida/person.h>
#include <divida/report.h>
#include <divida/io/io.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

namespace
{
	const std::string c_goldFile = "gold.json";
	const std::string c_temporaryFile = "tmp.json";

	std::unique_ptr<divida::group> create_test_group()
	{
		auto group = std::make_unique<divida::group>("Camping Friends");

		auto arav = group->person("Arav Jindal");
		auto marco = group->person("Marco Sanchez");
		auto grace = group->person("Grace Yun");
		auto maggie = group->person("Maggie McDonald");

		auto expenseFood = std::make_unique<divida::expense>("Food", divida::date::create(12, 7, 2009), grace);
		expenseFood->add_items(
			{ { "Apples", 4.67f },
			{ "Hot dogs", 8.55f },
			{ "Hot dog buns", 4.36f },
			{ "Beans", 3.79f },
			{ "Trail mix", 9.82f },
			{ "Potato chips", 5.03f } },
			{ divida::beneficiary{ arav }, divida::beneficiary{ marco }, divida::beneficiary{ grace }, divida::beneficiary{ maggie } }
		);

		auto expenseCampsites = std::make_unique<divida::expense>("Campsites", divida::date::create(13, 7, 2009), arav);
		expenseCampsites->add_item({ "Campsite permit", 183.45f, { divida::beneficiary{ arav, 4.0f }, divida::beneficiary{ marco, 3.0f }, divida::beneficiary{ grace, 4.0f }, divida::beneficiary{ maggie, 4.0f } } });

		auto expenseCampingSupplies = std::make_unique<divida::expense>("Camping supplies", divida::date::create(10, 7, 2009), maggie);
		expenseCampingSupplies->add_item({ "Two person tent", 95.78f,{ divida::beneficiary{ maggie }, divida::beneficiary{ grace } } });
		expenseCampingSupplies->add_item({ "Headlamp", 14.56f, { divida::beneficiary{ marco } } });
		expenseCampingSupplies->add_item({ "Tarp", 7.60f, { divida::beneficiary{ arav } } });
		expenseCampingSupplies->add_item({ "Hiking boots", 32.14f, { divida::beneficiary{ maggie } } });
		expenseCampingSupplies->add_item({ "Firewood", 12.00f, { divida::beneficiary{ arav }, divida::beneficiary{ marco }, divida::beneficiary{ grace, 5.0 }, divida::beneficiary{ maggie } } });

		auto report = group->report("Pacific Crest Trail Camping Trip");

		report->add_expense(std::move(expenseFood));
		report->add_expense(std::move(expenseCampsites));
		report->add_expense(std::move(expenseCampingSupplies));

		return std::move(group);
	}
}

TEST_CASE("readGroupFromJsonFile", "[io]")
{
	auto group = create_test_group();
	auto goldGroup = divida::io::readGroupFromJsonFile(divida::tests::resolve_path(c_goldFile));

	CHECK(goldGroup->name() == group->name());

	auto& goldPersons = goldGroup->persons();
	auto& persons = group->persons();
	REQUIRE(goldPersons.size() == persons.size());
	for (auto i = 0; i < goldPersons.size(); i++)
		CHECK(*goldPersons[i] == *persons[i]);

	auto& goldReports= goldGroup->reports();
	auto& reports = group->reports();
	REQUIRE(goldReports.size() == reports.size());
	for (auto i = 0; i < goldReports.size(); i++)
		CHECK(*goldReports[i] == *reports[i]);
}

TEST_CASE("writeGroupToJsonFile", "[io]")
{
	auto temporaryFilePath = divida::tests::resolve_path(c_temporaryFile);
	auto goldFilePath = divida::tests::resolve_path(c_goldFile);

	auto group = create_test_group();
	divida::io::writeGroupToJsonFile(*group, temporaryFilePath);

	// read in the temporary file and the gold file line by line and compare them
	{
		std::ifstream goldFile(goldFilePath);
		REQUIRE(goldFile.good());

		std::ifstream temporaryFile(temporaryFilePath);
		REQUIRE(temporaryFile.good());

		std::string goldFileLine;
		std::string temporaryFileLine;
		while (std::getline(goldFile, goldFileLine) && std::getline(temporaryFile, temporaryFileLine))
		{
			CHECK(goldFileLine == temporaryFileLine);
		}

		CHECK(goldFile.eof());
		CHECK(temporaryFile.eof());
	}

	std::remove(temporaryFilePath.c_str());
}
