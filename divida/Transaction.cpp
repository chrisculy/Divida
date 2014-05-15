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

	std::wstring Transaction::ToString() const
	{
		std::wstringstream s;
		s << m_fromPerson << L" pays " << L"$" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << m_amount << L" to " << m_toPerson;
		return s.str();
	}
}
