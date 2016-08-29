#include "person.h"

namespace divida
{
	person::person(const std::string& name) : object(name)
	{
	}

	std::string person::ToString() const
	{
		return object::ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<person>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<person>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<person>& ptr)
	{
		if (std::shared_ptr<person> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
