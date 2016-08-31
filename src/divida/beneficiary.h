#pragma once

#include "person.h"

#include <memory>
#include <string>

namespace divida
{
	class beneficiary
	{
	public:
		explicit beneficiary(const std::shared_ptr<divida::person> person, float weight = 1.0f);

		const std::shared_ptr<divida::person> person() const;
		float weight() const;

	private:
		const std::shared_ptr<divida::person> m_person;
		const float m_weight;
	};
}
