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

		const std::shared_ptr<divida::person>& person() const;
		float weight() const;

		bool operator==(const beneficiary& other) const;
		bool operator!=(const beneficiary& other) const;

	private:
		std::shared_ptr<divida::person> m_person;
		float m_weight;
	};
}
