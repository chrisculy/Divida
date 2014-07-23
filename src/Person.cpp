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

	wide_ostream& operator<<(wide_ostream& o, const std::unique_ptr<Person>& ptr)
	{
		return o << ptr->ToString();
	}

	wide_ostream& operator<<(wide_ostream& o, const std::shared_ptr<Person>& ptr)
	{
		return o << ptr->ToString();
	}

	wide_ostream& operator<<(wide_ostream& o, const std::weak_ptr<Person>& ptr)
	{
		if (std::shared_ptr<Person> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
