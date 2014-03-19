#include "pch.h"

#include "Object.h"

namespace Divida
{
	Object::Object(const std::wstring& name) : m_name(name)
	{
	}

	Object::Object(Object&& object)
	{
		m_name = object.m_name;
	}

	const std::wstring& Object::Name() const
	{
		return m_name;
	}
}
