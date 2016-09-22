#include "divida_tests.h"

#include <divida/group.h>
#include <divida/item.h>

TEST_CASE("item - Construction", "[item]")
{
	auto name = std::string("Apples");
	auto cost = 5.23f;

	divida::item item(name, cost);

	CHECK(name == item.name());
	CHECK(cost == item.cost());
}

TEST_CASE("item - ConstructionSingleBeneficiary", "[item]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);
	auto name = std::string("Sting");
	auto cost = 497.82f;
	auto person = group.person(divida::tests::c_nameFrodo);
	auto beneficiary = divida::beneficiary(person);
				
	std::vector<divida::beneficiary> beneficiaries;
	beneficiaries.push_back(beneficiary);

	divida::item item(name, cost, beneficiaries);

	CHECK(name == item.name());
	CHECK(cost == item.cost());
	CHECK(beneficiaries == item.beneficiaries());
}

TEST_CASE("item - ConstructionMultipleBeneficiaries", "[item]")
{
	auto group = divida::group(divida::tests::c_nameTestGroup);
	auto name = std::string("Daggers");
	auto cost = 986631.74f;
	auto frodo = group.person(divida::tests::c_nameFrodo);
	auto sam = group.person(divida::tests::c_nameSam);
	auto merry = group.person(divida::tests::c_nameMerry);
	auto pippin = group.person(divida::tests::c_namePippin);

	auto beneficiaryFrodo = divida::beneficiary(frodo);
	auto beneficiarySam = divida::beneficiary(sam);
	auto beneficiaryMerry = divida::beneficiary(merry);
	auto beneficiaryPippin = divida::beneficiary(pippin);

	std::vector<divida::beneficiary> beneficiaries;
	beneficiaries.push_back(beneficiaryFrodo);
	beneficiaries.push_back(beneficiarySam);
	beneficiaries.push_back(beneficiaryMerry);
	beneficiaries.push_back(beneficiaryPippin);

	divida::item item(name, cost, beneficiaries);

	CHECK(name == item.name());
	CHECK(cost == item.cost());
	CHECK(beneficiaries == item.beneficiaries());
}
