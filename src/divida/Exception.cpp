#include "Exception.h"

namespace Divida
{

Exception::Exception(std::string message) : m_message(message)
{
}

std::string Exception::GetMessage()
{
	return m_message;
}

}
