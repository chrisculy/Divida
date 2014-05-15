#include "pch.h"

#include "Person.h"

namespace Divida
{
	Person::Person(const std::wstring& name) : Object(name)
	{
	}

	std::wstring Person::ToString() const
	{
		std::wstringstream s;
		s << Name();
		return s.str();
	}
}
