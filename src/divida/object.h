#pragma once

#include <string>

namespace divida
{
	class object
	{
	public:
		explicit object(const std::string& name);
		object(object&& object);

		const std::string& name() const;
		std::string ToString() const;

	private:
		std::string m_name;
	};
}
