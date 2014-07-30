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

	private:
		std::string m_name;
	};
}
