#pragma once

#include "IXmlSerializer.h"
#include "Person.h"

namespace Divida
{
	class PersonSerializer : public IXmlSerializer<Person>
	{
	public:
		virtual const std::wstring& ElementName() const override;
		virtual Person Read(const pugi::xml_node& node) override;
		virtual void Write(pugi::xml_document & document, const Person& element) override;

	private:
		static const std::wstring ELEMENT_NAME;
		static const std::wstring NAME_ATTRIBUTE;
	};
}
