#include "pch.h"

#include "Object.h"

namespace Divida
{
	Object::Object(const std::string& name) : m_name(name)
	{
	}

	Object::Object(Object&& object)
	{
		m_name = std::move(object.m_name);
	}

	const std::string& Object::Name() const
	{
		return m_name;
	}

	std::string Object::ToString() const
	{
		return Name();
	}
}
