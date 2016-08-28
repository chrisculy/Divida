#pragma once

#include <string>

namespace Divida
{
	class Object
	{
	public:
		Object(const std::string& name);
		Object(Object&& object);

		const std::string& Name() const;
		std::string ToString() const;

	private:
		std::string m_name;
	};
}
