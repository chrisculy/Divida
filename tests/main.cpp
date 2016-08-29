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
	inline std::string toString(const divida::beneficiary& beneficiary)
	{
		return beneficiary.ToString();
	}

	inline std::string toString(const divida::date& date)
	{
		return date.ToString();
	}

	inline std::string toString(const divida::expense& expense)
	{
		return expense.ToString();
	}

	inline std::string toString(const divida::item& item)
	{
		return item.ToString();
	}

	inline std::string toString(const divida::object& object)
	{
		return object.ToString();
	}

	inline std::string toString(const divida::person& person)
	{
		return person.ToString();
	}

	inline std::string toString(const divida::transaction& transaction)
	{
		return transaction.ToString();
	}
}
