#pragma once

#include "Exception.h"

#include <memory>
#include <string>
#include <vector>

namespace Divida
{
	template<typename T> std::wstring ToString(const std::unique_ptr<T>&)
	{
		throw Exception(L"Unimplemented ToString for type.");
	}

	template<typename T> std::wstring ToString(const std::shared_ptr<T>&)
	{
		throw Exception(L"Unimplemented ToString for type.");
	}

	template<typename T> std::wstring ToString(const std::weak_ptr<T>&)
	{
		throw Exception(L"Unimplemented ToString for type.");
	}
}

#define DECLARE_TO_STRING_SMART_PTRS(type) \
	template<> std::wstring ToString<type>(const std::unique_ptr<type>& ptr) { return ptr->ToString(); } \
	template<> std::wstring ToString<type>(const std::shared_ptr<type>& ptr) { return ptr->ToString(); } \
	template<> std::wstring ToString<type>(const std::weak_ptr<type>& ptr) \
	{ \
		std::wstring output; \
		std::shared_ptr<type> sharedPtr = ptr.lock(); \
		if (sharedPtr != nullptr) \
			output = sharedPtr->ToString(); \
		return output; \
	}

extern const wchar_t* TO_STRING_OBJECT_BEGIN_TOKEN;
extern const wchar_t* TO_STRING_OBJECT_END_TOKEN;
extern const wchar_t* TO_STRING_DELIMITER;

template<typename T> static std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream < wchar_t, std::char_traits < wchar_t >> &o, const std::vector<T>& vector)
{
	o << TO_STRING_OBJECT_BEGIN_TOKEN;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		o << vector[i] << (i == vector.size() - 1 ? TO_STRING_OBJECT_END_TOKEN : TO_STRING_DELIMITER);
	}

	return o;
}

template<typename T> static std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream < wchar_t, std::char_traits < wchar_t >> &o, const std::unique_ptr<T>& ptr)
{
	return o << Divida::ToString(ptr);
}

template<typename T> static std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream < wchar_t, std::char_traits < wchar_t >> &o, const std::shared_ptr<T>& ptr)
{
	return o << Divida::ToString(ptr);
}

template<typename T> static std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream < wchar_t, std::char_traits < wchar_t >> &o, const std::weak_ptr<T>& ptr)
{
	if (std::shared_ptr<T> sharedPtr = ptr.lock())
		o << Divida::ToString(sharedPtr);

	return o;
}
