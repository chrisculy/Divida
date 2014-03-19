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
		const float Amount() const;
		std::wstring ToString() const;

	private:
		const std::weak_ptr<Person> m_fromPerson;
		const std::weak_ptr<Person> m_toPerson;
		const float m_amount;
	};

	DECLARE_TO_STRING_SMART_PTRS(Transaction);
}
