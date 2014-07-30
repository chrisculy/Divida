#include "pch.h"

#include "Beneficiary.h"
#include "Core.h"

namespace Divida
{
	Beneficiary::Beneficiary(const std::shared_ptr<Divida::Person> person, float weight) : m_person(person), m_weight(weight)
	{
	}

	const std::shared_ptr<Divida::Person> Beneficiary::Person() const
	{
		return m_person;
	}

	float Beneficiary::Weight() const
	{
		return m_weight;
	}

	std::string Beneficiary::ToString() const
	{
		std::stringstream s;
		s << TO_STRING_OBJECT_BEGIN_TOKEN << m_person << TO_STRING_DELIMITER << m_weight << TO_STRING_OBJECT_END_TOKEN;
		return s.str();
	}

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<Beneficiary>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Beneficiary>& ptr)
	{
		return o << ptr->ToString();
	}

	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<Beneficiary>& ptr)
	{
		if (std::shared_ptr<Beneficiary> sharedPtr = ptr.lock())
			o << sharedPtr->ToString();

		return o;
	}
}
