#include "to_string.h"

namespace divida
{
	const std::string c_toStringInvalidWeakPointer = "<invalid-weak-pointer>";
	const std::string c_toStringNull = "<null>";
	const std::string c_toStringObjectBegin = "[";
	const std::string c_toStringObjectEnd = "]";
	const std::string c_toStringDelimiter = ", ";
}

std::ostream& operator<<(std::ostream& o, const divida::beneficiary& beneficiary)
{
	return o << divida::c_toStringObjectBegin << beneficiary.person() << divida::c_toStringDelimiter << std::setiosflags(std::ios::fixed) << std::setprecision(2) << beneficiary.weight() << divida::c_toStringObjectEnd;
}

std::ostream& operator<<(std::ostream& o, const divida::date& date)
{
	return o << date.month() << '/' << date.day() << '/' << date.year();
}

std::ostream& operator<<(std::ostream& o, const divida::expense& expense)
{
	return o << divida::c_toStringObjectBegin << expense.name() << divida::c_toStringDelimiter << expense.date() << divida::c_toStringDelimiter << expense.total() << divida::c_toStringDelimiter << expense.payer() << divida::c_toStringDelimiter << expense.items() << divida::c_toStringObjectEnd;
}

std::ostream& operator<<(std::ostream& o, const divida::item& item)
{
	return o << divida::c_toStringObjectBegin << item.name() << divida::c_toStringDelimiter << item.cost() << divida::c_toStringDelimiter << item.beneficiaries() << divida::c_toStringObjectEnd;
}

std::ostream& operator<<(std::ostream& o, const divida::object& object)
{
	return o << divida::c_toStringObjectBegin << object.name() << divida::c_toStringObjectEnd;
}

std::ostream& operator<<(std::ostream& o, const divida::person& person)
{
	return o << divida::c_toStringObjectBegin << person.name() << divida::c_toStringObjectEnd;
}

std::ostream& operator<<(std::ostream& o, const divida::transaction& transaction)
{
	return o << divida::c_toStringObjectBegin << transaction.from_person() << " pays " << "$" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << transaction.amount() << " to " << transaction.to_person() << divida::c_toStringObjectEnd;
}

namespace divida
{
	std::string to_string(const divida::beneficiary& b)
	{
		std::ostringstream stream;
		stream << b;
		return stream.str();
	}

	std::string to_string(const divida::date& date)
	{
		std::ostringstream stream;
		stream << date;
		return stream.str();
	}

	std::string to_string(const divida::expense& expense)
	{
		std::ostringstream stream;
		stream << expense;
		return stream.str();
	}

	std::string to_string(const divida::item& item)
	{
		std::ostringstream stream;
		stream << item;
		return stream.str();
	}

	std::string to_string(const divida::object& object)
	{
		std::ostringstream stream;
		stream << object;
		return stream.str();
	}

	std::string to_string(const divida::person& person)
	{
		std::ostringstream stream;
		stream << person;
		return stream.str();
	}

	std::string to_string(const divida::transaction& transaction)
	{
		std::ostringstream stream;
		stream << transaction;
		return stream.str();
	}
}
