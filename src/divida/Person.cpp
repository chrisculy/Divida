#include "pch.h"

#include "Person.h"

namespace Divida
{
	Person::Person(const std::string& name) : Object(name)
	{
	}

	std::string Person::ToString() const
	{
		return Object::ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<Person>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Person>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<Person>& ptr)
	{
		if (std::shared_ptr<Person> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
