#include "beneficiary.h"

namespace divida
{
	beneficiary::beneficiary(const std::shared_ptr<divida::person> person, float weight)
		: m_person{ person }
		, m_weight{ weight }
	{
	}

	const std::shared_ptr<divida::person>& beneficiary::person() const
	{
		return m_person;
	}

	float beneficiary::weight() const
	{
		return m_weight;
	}

	bool beneficiary::operator==(const beneficiary& other) const
	{
		return m_person == other.m_person && m_weight == other.m_weight;
	}

	bool beneficiary::operator!=(const beneficiary& other) const
	{
		return !(*this == other);
	}
}
