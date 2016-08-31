#include "object.h"

namespace divida
{
	object::object(const std::string& name) : m_name(name)
	{
	}

	const std::string& object::name() const
	{
		return m_name;
	}
}
