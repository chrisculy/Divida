#pragma once

#include <string>

namespace divida
{
	class object
	{
	public:
		explicit object(const std::string& name);

		const std::string& name() const;

	private:
		std::string m_name;
	};
}
