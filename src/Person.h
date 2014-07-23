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

	wide_ostream& operator<<(wide_ostream& o, const std::unique_ptr<Person>& ptr);
	wide_ostream& operator<<(wide_ostream& o, const std::shared_ptr<Person>& ptr);
	wide_ostream& operator<<(wide_ostream& o, const std::weak_ptr<Person>& ptr);
}
