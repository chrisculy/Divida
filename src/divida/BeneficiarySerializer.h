#pragma once

#include "Beneficiary.h"
#include "IXmlSerializer.h"

namespace divida
{
	class beneficiary_serializer : public ixml_serializer<beneficiary>
	{
	public:
		virtual const std::string& element_name() const override;
		virtual beneficiary read(const pugi::xml_node& node) override;
		virtual void write(pugi::xml_document & document, const beneficiary& element) override;

	private:
		static const std::string c_elementName;
		static const std::string c_personAttribute;
		static const std::string c_weightAttribute;
	};
}
