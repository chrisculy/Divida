#include "pch.h"

#include "Transaction.h"

namespace Divida
{
	Transaction::Transaction(const std::weak_ptr<Person> fromPerson, const std::weak_ptr<Person> toPerson, float amount)
		: m_fromPerson(fromPerson), m_toPerson(toPerson), m_amount(amount)
	{
	}

	const std::weak_ptr<Person> Transaction::FromPerson() const
	{
		return m_fromPerson;
	}

	const std::weak_ptr<Person> Transaction::ToPerson() const
	{
		return m_toPerson;
	}

	float Transaction::Amount() const
	{
		return m_amount;
	}

	std::string Transaction::ToString() const
	{
		std::stringstream s;
		s << m_fromPerson << " pays " << "$" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << m_amount << " to " << m_toPerson;
		return s.str();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<Transaction>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Transaction>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<Transaction>& ptr)
	{
		if (std::shared_ptr<Transaction> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
