#pragma once

#include <memory>

#include "Core.h"
#include "Person.h"

namespace Divida
{
	class Transaction
	{
	public:
		Transaction(const std::weak_ptr<Person> fromPerson, const std::weak_ptr<Person> toPerson, float amount);

		const std::weak_ptr<Person> FromPerson() const;
		const std::weak_ptr<Person> ToPerson() const;
		float Amount() const;
		std::wstring ToString() const;

	private:
		const std::weak_ptr<Person> m_fromPerson;
		const std::weak_ptr<Person> m_toPerson;
		const float m_amount;
	};

	wide_ostream& operator<<(wide_ostream& o, const std::unique_ptr<Transaction>& ptr);
	wide_ostream& operator<<(wide_ostream& o, const std::shared_ptr<Transaction>& ptr);
	wide_ostream& operator<<(wide_ostream& o, const std::weak_ptr<Transaction>& ptr);
}
