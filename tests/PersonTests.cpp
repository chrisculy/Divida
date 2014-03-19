#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Divida
{
	namespace Tests
	{
		TEST_CLASS(PersonTests)
		{
		public:
			TEST_METHOD(Construction)
			{				
				Person person(NAME_FRODO);
				
				Assert::AreEqual(NAME_FRODO, person.Name());
			}
		};
	}
}
