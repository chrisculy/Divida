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
		Person(const std::string& name);

		std::string ToString() const;
	};

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<Person>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Person>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<Person>& ptr);
}
