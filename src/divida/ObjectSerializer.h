#pragma once

#include "IXmlSerializer.h"
#include "Object.h"

namespace Divida
{
	class ObjectSerializer : public IXmlSerializer<Object>
	{
	public:
		virtual const std::string& ElementName() const override;
		virtual Object Read(const pugi::xml_node& node) override;
		virtual void Write(pugi::xml_document & document, const Object& element) override;

	private:
		static const std::string ELEMENT_NAME;
		static const std::string NAME_ATTRIBUTE;
	};
}
