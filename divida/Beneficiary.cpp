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

	std::wstring Beneficiary::ToString() const
	{
		std::wstringstream s;
		s << TO_STRING_OBJECT_BEGIN_TOKEN << m_person << TO_STRING_DELIMITER << m_weight << TO_STRING_OBJECT_END_TOKEN;
		return s.str();
	}
}
