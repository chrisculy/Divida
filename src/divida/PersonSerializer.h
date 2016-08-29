#pragma once

#include "IXmlSerializer.h"
#include "Person.h"

namespace divida
{
	class person_serializer : public ixml_serializer<person>
	{
	public:
		virtual const std::string& element_name() const override;
		virtual person read(const pugi::xml_node& node) override;
		virtual void write(pugi::xml_document & document, const person& element) override;

	private:
		static const std::string c_elementName;
		static const std::string c_nameAttribute;
	};
}
