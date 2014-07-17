#pragma once

#include "IXmlSerializer.h"
#include "Person.h"

namespace Divida
{
	class PersonSerializer : public IXmlSerializer<Person>
	{
	public:
		virtual const std::wstring& ElementName() const;
		virtual Person Read(const pugi::xml_node& node);
		virtual void Write(pugi::xml_document & document, const Person& element);

	private:
		static const std::wstring ELEMENT_NAME;
		static const std::wstring NAME_ATTRIBUTE;
	};
}
