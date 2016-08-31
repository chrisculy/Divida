#include "exception.h"

namespace divida
{
	exception::exception(std::string message) : m_message(message)
	{
	}

	std::string exception::message()
	{
		return m_message;
	}
}
