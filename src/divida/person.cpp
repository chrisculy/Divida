#include "person.h"

namespace divida
{
	person::person(size_t id, const std::string& name)
		: m_id{id}
		, m_name{name}
	{
	}

	size_t person::id() const
	{
		return m_id;
	}

	const std::string& person::name() const
	{
		return m_name;
	}

	bool person::operator==(const person& other) const
	{
		return m_id == other.m_id && m_name == other.m_name;
	}

	bool person::operator!=(const person& other) const
	{
		return !(*this == other);
	}
}
