#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Divida
{
	namespace Tests
	{
		TEST_CLASS(ObjectTests)
		{
		public:
			TEST_METHOD(Construction)
			{
				auto name = std::wstring(L"The Cube");

				Object object(name);

				Assert::AreEqual(name, object.Name());
			}
		};
	}
}
