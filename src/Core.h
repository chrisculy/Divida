#pragma once

#include "Exception.h"

#include <memory>
#include <string>
#include <vector>

using wide_ostream = std::basic_ostream<wchar_t, std::char_traits<wchar_t>>;

extern const std::wstring TO_STRING_OBJECT_BEGIN_TOKEN;
extern const std::wstring TO_STRING_OBJECT_END_TOKEN;
extern const std::wstring TO_STRING_DELIMITER;

namespace Divida
{

template<typename T> wide_ostream& operator<<(wide_ostream& o, const std::vector<T>& vector)
{
	o << TO_STRING_OBJECT_BEGIN_TOKEN;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		o << vector[i] << (i == vector.size() - 1 ? TO_STRING_OBJECT_END_TOKEN : TO_STRING_DELIMITER);
	}

	return o;
}

}
