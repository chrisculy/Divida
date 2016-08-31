#pragma once

#include "person.h"

#include <iostream>
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
		std::string ToString() const;

	private:
		const std::shared_ptr<divida::person> m_person;
		const float m_weight;
	};

	std::ostream& operator<<(std::ostream& o, const std::unique_ptr<beneficiary>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::shared_ptr<beneficiary>& ptr);
	std::ostream& operator<<(std::ostream& o, const std::weak_ptr<beneficiary>& ptr);
}
