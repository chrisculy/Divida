#include "divida_tests.h"

#include <divida/Item.h>

TEST_CASE("Item - Construction", "[item]")
{
	auto name = std::string("Apples");
	auto cost = 5.23f;

	Divida::Item item(name, cost);

	CHECK(name == item.Name());
	CHECK(cost == item.Cost());
}

TEST_CASE("Item - ConstructionSingleBeneficiary", "[item]")
{
	auto name = std::string("Sting");
	auto cost = 497.82f;
	auto person = std::make_shared<Divida::Person>(Divida::Tests::NAME_FRODO);
	auto beneficiary = std::make_shared<Divida::Beneficiary>(person);
				
	std::vector<std::shared_ptr<Divida::Beneficiary>> beneficiaries;
	beneficiaries.push_back(beneficiary);

	Divida::Item item(name, cost, beneficiaries);

	CHECK(name == item.Name());
	CHECK(cost == item.Cost());				
	CHECK(beneficiaries == item.Beneficiaries());
}

TEST_CASE("Item - ConstructionMultipleBeneficiaries", "[item]")
{
	auto name = std::string("Daggers");
	auto cost = 986631.74f;
	auto frodo = std::make_shared<Divida::Person>(Divida::Tests::NAME_FRODO);
	auto sam = std::make_shared<Divida::Person>(Divida::Tests::NAME_SAM);
	auto merry = std::make_shared<Divida::Person>(Divida::Tests::NAME_MERRY);
	auto pippin = std::make_shared<Divida::Person>(Divida::Tests::NAME_PIPPIN);

	auto beneficiaryFrodo = std::make_shared<Divida::Beneficiary>(frodo);
	auto beneficiarySam = std::make_shared<Divida::Beneficiary>(sam);
	auto beneficiaryMerry = std::make_shared<Divida::Beneficiary>(merry);
	auto beneficiaryPippin = std::make_shared<Divida::Beneficiary>(pippin);

	std::vector<std::shared_ptr<Divida::Beneficiary>> beneficiaries;
	beneficiaries.push_back(beneficiaryFrodo);
	beneficiaries.push_back(beneficiarySam);
	beneficiaries.push_back(beneficiaryMerry);
	beneficiaries.push_back(beneficiaryPippin);

	Divida::Item item(name, cost, beneficiaries);

	CHECK(name == item.Name());
	CHECK(cost == item.Cost());
	CHECK(beneficiaries == item.Beneficiaries());
}
