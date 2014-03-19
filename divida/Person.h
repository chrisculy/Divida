#pragma once

#include <memory>
#include <string>

#include "Core.h"
#include "Object.h"

namespace Divida
{
	class Person : public Object
	{
	public:
		Person(const std::wstring& name);

		std::wstring ToString() const;
	};

	DECLARE_TO_STRING_SMART_PTRS(Person);
}
