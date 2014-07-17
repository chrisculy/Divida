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

	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::unique_ptr<Person>& ptr);
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::shared_ptr<Person>& ptr);
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::weak_ptr<Person>& ptr);
}
