#include "Exception.h"

namespace Divida
{

Exception::Exception(std::wstring message) : m_message(message)
{
}

std::wstring Exception::GetMessage()
{
	return m_message;
}

}
