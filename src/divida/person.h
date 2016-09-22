#pragma once

#include <string>

namespace divida
{
	class person
	{
	public:
		size_t id() const;
		const std::string& name() const;

		bool operator==(const person& other) const;
		bool operator!=(const person& other) const;

	private:
		friend class group;

		person(size_t id, const std::string& name);
		
		size_t m_id;
		std::string m_name;
	};
}
