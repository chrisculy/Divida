#pragma once

#include <memory>

#include "Core.h"
#include "Person.h"

namespace Divida
{
	class Beneficiary
	{
	public:
		Beneficiary(const std::shared_ptr<Person> person, float weight = 1.0f);

		const std::shared_ptr<Person> Person() const;
		const float Weight() const;
		std::wstring ToString() const;

	private:
		const std::shared_ptr<Divida::Person> m_person;
		const float m_weight;
	};

	DECLARE_TO_STRING_SMART_PTRS(Beneficiary);
}
