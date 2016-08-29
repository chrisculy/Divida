#pragma once

#include <pugixml.hpp>

namespace divida
{
	template<typename T> class ixml_serializer
	{
	public:
		virtual const std::string& element_name() const = 0;

		virtual T read(const pugi::xml_node& node) = 0;
		virtual void write(pugi::xml_document & document, const T& element) = 0;
	};
}
