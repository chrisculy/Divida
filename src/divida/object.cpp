#include "object.h"

namespace divida
{
	object::object(const std::string& name) : m_name(name)
	{
	}

	object::object(object&& object)
	{
		m_name = std::move(object.m_name);
	}

	const std::string& object::name() const
	{
		return m_name;
	}
}
