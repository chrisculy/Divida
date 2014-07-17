#pragma once

#include "Exception.h"

#include <memory>
#include <string>
#include <vector>

#if 0
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
#endif

#if 0
#define DECLARE_TO_STRING_SMART_PTRS(type) \
	template<> std::wstring ToString<>(const std::unique_ptr<type>& ptr) { return ptr->ToString(); } \
	template<> std::wstring ToString<>(const std::shared_ptr<type>& ptr) { return ptr->ToString(); } \
	template<> std::wstring ToString<>(const std::weak_ptr<type>& ptr) \
	{ \
		std::wstring output; \
		std::shared_ptr<type> sharedPtr = ptr.lock(); \
		if (sharedPtr != nullptr) \
			output = sharedPtr->ToString(); \
		return output; \
	}
#endif

extern const std::wstring TO_STRING_OBJECT_BEGIN_TOKEN;
extern const std::wstring TO_STRING_OBJECT_END_TOKEN;
extern const std::wstring TO_STRING_DELIMITER;

namespace Divida
{
template<typename T> void WriteVectorToStream(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::vector<T>& vector)
{
	o << TO_STRING_OBJECT_BEGIN_TOKEN;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		o << vector[i] << (i == vector.size() - 1 ? TO_STRING_OBJECT_END_TOKEN : TO_STRING_DELIMITER);
	}
}

template<typename T> std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::vector<T>& vector)
{
	o << TO_STRING_OBJECT_BEGIN_TOKEN;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		o << vector[i] << (i == vector.size() - 1 ? TO_STRING_OBJECT_END_TOKEN : TO_STRING_DELIMITER);
	}

	return o;
}

#if 0
std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::unique_ptr<type>& ptr);
std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::shared_ptr<type>& ptr);
std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::weak_ptr<type>& ptr);

std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::unique_ptr<type>& ptr)
{
	return o << ptr->ToString();
}

std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::shared_ptr<type>& ptr)
{
	return o << ptr->ToString();
}

std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::weak_ptr<type>& ptr)
{
	if (std::shared_ptr<type> sharedPtr = ptr.lock())
		o << sharedPtr->ToString();

	return o;
}

#define DECLARE_OSTREAM_OPERATORS(type) \
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::unique_ptr<type>& ptr) \
	{ \
		return o << ptr->ToString(); \
	} \
	\
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::shared_ptr<type>& ptr) \
	{ \
		return o << ptr->ToString(); \
	} \
	 \
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::weak_ptr<type>& ptr) \
	{ \
		if (std::shared_ptr<type> sharedPtr = ptr.lock()) \
			o << sharedPtr->ToString(); \
	\
		return o; \
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
#endif
}
