#include "Transaction.h"

#include <iomanip>
#include <sstream>

namespace divida
{
	transaction::transaction(const std::weak_ptr<person> fromPerson, const std::weak_ptr<person> toPerson, float amount)
		: m_fromPerson(fromPerson), m_toPerson(toPerson), m_amount(amount)
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

	std::string transaction::ToString() const
	{
		std::stringstream s;
		s << m_fromPerson << " pays " << "$" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << m_amount << " to " << m_toPerson;
		return s.str();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<transaction>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<transaction>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<transaction>& ptr)
	{
		if (std::shared_ptr<transaction> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
