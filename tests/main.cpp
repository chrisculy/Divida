#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <divida/Beneficiary.h>
#include <divida/Date.h>
#include <divida/Expense.h>
#include <divida/Item.h>
#include <divida/Object.h>
#include <divida/Person.h>
#include <divida/Report.h>
#include <divida/Transaction.h>

namespace Catch
{
	inline std::string toString(const Divida::Beneficiary& beneficiary)
	{
		return beneficiary.ToString();
	}

	inline std::string toString(const Divida::Date& date)
	{
		return date.ToString();
	}

	inline std::string toString(const Divida::Expense& expense)
	{
		return expense.ToString();
	}

	inline std::string toString(const Divida::Item& item)
	{
		return item.ToString();
	}

	inline std::string toString(const Divida::Object& object)
	{
		return object.ToString();
	}

	inline std::string toString(const Divida::Person& person)
	{
		return person.ToString();
	}

	inline std::string toString(const Divida::Transaction& transaction)
	{
		return transaction.ToString();
	}
}
