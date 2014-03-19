#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Divida
{
	namespace Tests
	{
		TEST_CLASS(TransactionTests)
		{
		public:
			TEST_METHOD(Construction)
			{
				auto fromPerson = std::make_shared<Person>(NAME_FRODO);
				auto toPerson = std::make_shared<Person>(NAME_GANDALF);

				auto fromPersonWeak = std::weak_ptr<Person>(fromPerson);
				auto toPersonWeak = std::weak_ptr<Person>(toPerson);
				auto amount = 12.35f;

				Transaction transaction(fromPersonWeak, toPersonWeak, amount);

				Assert::AreEqual(fromPerson, transaction.FromPerson().lock());
				Assert::AreEqual(toPerson, transaction.ToPerson().lock());
				Assert::AreEqual(amount, transaction.Amount());
			}
		};
	}
}
