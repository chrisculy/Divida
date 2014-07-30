#pragma once

#include "Exception.h"

#include <memory>
#include <string>
#include <vector>

extern const std::string TO_STRING_OBJECT_BEGIN_TOKEN;
extern const std::string TO_STRING_OBJECT_END_TOKEN;
extern const std::string TO_STRING_DELIMITER;

namespace Divida
{

template<typename T> std::ostream& operator<<(std::ostream& o, const std::vector<T>& vector)
{
	o << TO_STRING_OBJECT_BEGIN_TOKEN;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		o << vector[i] << (i == vector.size() - 1 ? TO_STRING_OBJECT_END_TOKEN : TO_STRING_DELIMITER);
	}

	return o;
}

}
