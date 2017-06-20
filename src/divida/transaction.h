#pragma once

#include "person.h"

#include <memory>

namespace divida
{
	class transaction
	{
	public:
		transaction(const std::shared_ptr<person> fromPerson, const std::shared_ptr<person> toPerson, float amount);

		const std::shared_ptr<person> from_person() const;
		const std::shared_ptr<person> to_person() const;
		float amount() const;

	private:
		std::shared_ptr<person> m_fromPerson;
		std::shared_ptr<person> m_toPerson;
		float m_amount;
	};
}
