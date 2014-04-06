#pragma once

#include <string>

namespace Divida
{
    class Exception
    {
    public:
        Exception(std::wstring message);
        ~Exception() = default;

        std::wstring GetMessage();

    private:
        std::wstring m_message;
    };
}
