#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <divida/beneficiary.h>
#include <divida/date.h>
#include <divida/expense.h>
#include <divida/item.h>
#include <divida/object.h>
#include <divida/person.h>
#include <divida/report.h>
#include <divida/transaction.h>

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
