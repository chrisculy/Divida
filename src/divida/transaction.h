#pragma once

#include "person.h"

#include <memory>

namespace divida
{
	class transaction
	{
	public:
		transaction(const std::weak_ptr<person> fromPerson, const std::weak_ptr<person> toPerson, float amount);

		const std::weak_ptr<person> from_person() const;
		const std::weak_ptr<person> to_person() const;
		float amount() const;

	private:
		const std::weak_ptr<person> m_fromPerson;
		const std::weak_ptr<person> m_toPerson;
		const float m_amount;
	};
}
