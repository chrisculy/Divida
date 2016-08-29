#include "Beneficiary.h"
#include "to_string.h"

#include <sstream>

namespace divida
{
	beneficiary::beneficiary(const std::shared_ptr<divida::person> person, float weight) : m_person(person), m_weight(weight)
	{
	}

	const std::shared_ptr<divida::person> beneficiary::person() const
	{
		return m_person;
	}

	float beneficiary::weight() const
	{
		return m_weight;
	}

	std::string beneficiary::ToString() const
	{
		std::stringstream s;
		s << c_toStringObjectBeginToken << m_person << c_toStringDelimiter << m_weight << c_toStringObjectEndToken;
		return s.str();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<beneficiary>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<beneficiary>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<beneficiary>& ptr)
	{
		if (std::shared_ptr<beneficiary> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
