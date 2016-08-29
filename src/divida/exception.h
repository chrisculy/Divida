#pragma once

#include <string>

namespace divida
{
	class exception
	{
	public:
		exception(std::string message);
		~exception() = default;

		std::string message();

	private:
		std::string m_message;
	};
}
