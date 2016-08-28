#include "pch.h"
#include "PersonSerializer.h"

#include "Exception.h"
#include "ObjectSerializer.h"

namespace Divida
{
	const std::string PersonSerializer::ELEMENT_NAME = "person";
	const std::string PersonSerializer::NAME_ATTRIBUTE = "name";

	const std::string& PersonSerializer::ElementName() const
	{
		return ELEMENT_NAME;
	}

	Person PersonSerializer::Read(const pugi::xml_node& node)
	{
		std::string nodeName(node.name());
		if (nodeName == ElementName())
		{
			auto nameAttribute = node.attribute(NAME_ATTRIBUTE.c_str());
			if (nameAttribute != nullptr)
			{
				if (nameAttribute.value() != nullptr)
				{
					return Person(nameAttribute.value());
				}
			}
		}

		throw Exception("Failed to read Person from XML.");
	}

	void PersonSerializer::Write(pugi::xml_document& document, const Person& element)
	{
		auto node = document.append_child(ElementName().c_str());
		if (node == nullptr)
			return;

		auto nameAttribute = node.append_attribute(NAME_ATTRIBUTE.c_str());
		if (nameAttribute == nullptr)
			return;

		if (!nameAttribute.set_value(element.Name().c_str()))
			return;
	}
}
