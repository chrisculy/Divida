#pragma once

#include "beneficiary.h"
#include "date.h"
#include "expense.h"
#include "item.h"
#include "person.h"
#include "transaction.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace divida
{
	extern const std::string c_toStringInvalidWeakPointer;
	extern const std::string c_toStringNull;
	extern const std::string c_toStringObjectBegin;
	extern const std::string c_toStringObjectEnd;
	extern const std::string c_toStringDelimiter;
}

// output stream operators for generic common types
template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& vector)
{
	o << divida::c_toStringObjectBegin;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		o << vector[i];
		if (i < vector.size() - 1)
			o << divida::c_toStringDelimiter;
	}
	o << divida::c_toStringObjectEnd;

	return o;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::unique_ptr<T>& ptr)
{
	if (ptr != nullptr)
		return o << *ptr;
	else
		return o << divida::c_toStringNull;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::shared_ptr<T>& ptr)
{
	if (ptr != nullptr)
		return o << *ptr;
	else
		return o << divida::c_toStringNull;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::weak_ptr<T>& ptr)
{
	if (auto sharedPtr = ptr.lock())
		return o << sharedPtr;
	else
		return o << divida::c_toStringInvalidWeakPointer;
}

// output stream operators for divida types
std::ostream& operator<<(std::ostream& o, const divida::beneficiary& beneficiary);
std::ostream& operator<<(std::ostream& o, const divida::date& date);
std::ostream& operator<<(std::ostream& o, const divida::expense& expense);
std::ostream& operator<<(std::ostream& o, const divida::item& item);
std::ostream& operator<<(std::ostream& o, const divida::person& person);
std::ostream& operator<<(std::ostream& o, const divida::transaction& transaction);

namespace divida
{
	template<typename T>
	std::string to_string(const std::unique_ptr<T>& ptr)
	{
		std::ostringstream s;
		s << ptr;
		return s.str();
	}

	template<typename T>
	std::string to_string(const std::shared_ptr<T>& ptr)
	{
		std::ostringstream s;
		s << ptr;
		return s.str();
	}

	template<typename T>
	std::string to_string(const std::weak_ptr<T>& ptr)
	{
		std::ostringstream s;
		s << ptr;
		return s.str();
	}

	std::string to_string(const divida::beneficiary& beneficiary);
	std::string to_string(const divida::date& date);
	std::string to_string(const divida::expense& expense);
	std::string to_string(const divida::item& item);
	std::string to_string(const divida::person& person);
	std::string to_string(const divida::transaction& transaction);
}
