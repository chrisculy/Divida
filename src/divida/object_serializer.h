#pragma once

#include "ixml_serializer.h"
#include "object.h"

namespace divida
{
	class object_serializer : public ixml_serializer<object>
	{
	public:
		virtual const std::string& element_name() const override;
		virtual object read(const pugi::xml_node& node) override;
		virtual void write(pugi::xml_document & document, const object& element) override;

	private:
		static const std::string c_elementName;
		static const std::string c_nameAttribute;
	};
}
