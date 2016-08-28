#pragma once

#include <string>

namespace Divida
{
	class Exception
	{
	public:
		Exception(std::string message);
		~Exception() = default;

		std::string GetMessage();

	private:
		std::string m_message;
	};
}
