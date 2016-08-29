#pragma once

#include "object.h"

#include <memory>
#include <string>

namespace divida
{
	class person : public object
	{
	public:
		person(const std::string& name);

		std::string ToString() const;
	};

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<person>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<person>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<person>& ptr);
}
