#pragma once

#include <pugixml.hpp>

namespace Divida
{
	template<typename T> class IXmlSerializer
	{
	public:
		virtual const std::wstring& ElementName() const = 0;

		virtual T Read(const pugi::xml_node& node) = 0;
		virtual void Write(pugi::xml_document & document, const T& element) = 0;
	};
}
