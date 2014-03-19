#pragma once

#include <string>

namespace Divida
{
	class Object
	{
	public:
		Object(const std::wstring& name);
		Object(Object&& object);

		const std::wstring& Name() const;

	private:
		std::wstring m_name;
	};
}
