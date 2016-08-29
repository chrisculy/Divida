#pragma once

#include <string>
#include <vector>

namespace divida
{

extern const std::string c_toStringObjectBeginToken;
extern const std::string c_toStringObjectEndToken;
extern const std::string c_toStringDelimiter;

template<typename T> std::ostream& operator<<(std::ostream& o, const std::vector<T>& vector)
{
	o << c_toStringObjectBeginToken;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		o << vector[i] << (i == vector.size() - 1 ? c_toStringObjectEndToken : c_toStringDelimiter);
	}

	return o;
}

}
