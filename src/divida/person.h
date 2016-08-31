#pragma once

#include "object.h"

#include <string>

namespace divida
{
	class person : public object
	{
	public:
		explicit person(const std::string& name);
	};
}
