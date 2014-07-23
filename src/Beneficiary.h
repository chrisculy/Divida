#pragma once

#include <memory>

#include "Core.h"
#include "Person.h"

namespace Divida
{
	class Beneficiary
	{
	public:
		Beneficiary(const std::shared_ptr<Divida::Person> person, float weight = 1.0f);

		const std::shared_ptr<Divida::Person> Person() const;
		float Weight() const;
		std::wstring ToString() const;

	private:
		const std::shared_ptr<Divida::Person> m_person;
		const float m_weight;
	};

	wide_ostream& operator<<(wide_ostream& o, const std::unique_ptr<Beneficiary>& ptr);
	wide_ostream& operator<<(wide_ostream& o, const std::shared_ptr<Beneficiary>& ptr);
	wide_ostream& operator<<(wide_ostream& o, const std::weak_ptr<Beneficiary>& ptr);
}
