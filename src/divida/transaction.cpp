#include "transaction.h"

namespace divida
{
	transaction::transaction(const std::weak_ptr<person> fromPerson, const std::weak_ptr<person> toPerson, float amount)
		: m_fromPerson{ fromPerson }
		, m_toPerson{ toPerson }
		, m_amount{ amount }
	{
	}

	const std::weak_ptr<person> transaction::from_person() const
	{
		return m_fromPerson;
	}

	const std::weak_ptr<person> transaction::to_person() const
	{
		return m_toPerson;
	}

	float transaction::amount() const
	{
		return m_amount;
	}
}
