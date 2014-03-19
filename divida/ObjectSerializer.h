#pragma once

#include "IXmlSerializer.h"
#include "Object.h"

namespace Divida
{
	class ObjectSerializer : public IXmlSerializer<Object>
	{
	public:
		virtual const std::wstring& ElementName() const;
		virtual Object Read(const pugi::xml_node& node);
		virtual void Write(pugi::xml_document & document, const Object& element);

	private:
		static const std::wstring ELEMENT_NAME;
		static const std::wstring NAME_ATTRIBUTE;
	};
}
