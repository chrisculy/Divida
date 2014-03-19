#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Divida
{
	namespace Tests
	{
		TEST_CLASS(ItemTests)
		{
		public:
			TEST_METHOD(Construction)
			{
				auto name = std::wstring(L"Apples");
				auto cost = 5.23f;

				Item item(name, cost);

				Assert::AreEqual(name, item.Name());
				Assert::AreEqual(cost, item.Cost());
			}

			TEST_METHOD(ConstructionSingleBeneficiary)
			{
				auto name = std::wstring(L"Sting");
				auto cost = 497.82f;
				auto person = std::make_shared<Person>(NAME_FRODO);
				auto beneficiary = std::make_shared<Beneficiary>(person);
				
				std::vector<std::shared_ptr<Beneficiary>> beneficiaries;
				beneficiaries.push_back(beneficiary);

				Item item(name, cost, beneficiaries);

				Assert::AreEqual(name, item.Name());
				Assert::AreEqual(cost, item.Cost());
				
				AreEqual(beneficiaries, item.Beneficiaries());
			}

			TEST_METHOD(ConstructionMultipleBeneficiaries)
			{
				auto name = std::wstring(L"Daggers");
				auto cost = 986631.74f;
				auto frodo = std::make_shared<Person>(NAME_FRODO);
				auto sam = std::make_shared<Person>(NAME_SAM);
				auto merry = std::make_shared<Person>(NAME_MERRY);
				auto pippin = std::make_shared<Person>(NAME_PIPPIN);

				auto beneficiaryFrodo = std::make_shared<Beneficiary>(frodo);
				auto beneficiarySam = std::make_shared<Beneficiary>(sam);
				auto beneficiaryMerry = std::make_shared<Beneficiary>(merry);
				auto beneficiaryPippin = std::make_shared<Beneficiary>(pippin);

				std::vector<std::shared_ptr<Beneficiary>> beneficiaries;
				beneficiaries.push_back(beneficiaryFrodo);
				beneficiaries.push_back(beneficiarySam);
				beneficiaries.push_back(beneficiaryMerry);
				beneficiaries.push_back(beneficiaryPippin);

				Item item(name, cost, beneficiaries);

				Assert::AreEqual(name, item.Name());
				Assert::AreEqual(cost, item.Cost());

				AreEqual(beneficiaries, item.Beneficiaries());

				Assert::Fail(L"Implement == operators for all classes!");
			}
		};
	}
}
