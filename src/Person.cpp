#include "pch.h"

#include "Person.h"

namespace Divida
{
	Person::Person(const std::wstring& name) : Object(name)
	{
	}

	std::wstring Person::ToString() const
	{
		std::wstringstream s;
		s << Name();
		return s.str();
	}

	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::unique_ptr<Person>& ptr)
	{
		return o << ptr->ToString();
	}

	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::shared_ptr<Person>& ptr)
	{
		return o << ptr->ToString();
	}

	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::weak_ptr<Person>& ptr)
	{
		if (std::shared_ptr<Person> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
