#include "pch.h"
#include "ObjectSerializer.h"

#include "Exception.h"

namespace Divida
{
	const std::string ObjectSerializer::ELEMENT_NAME = "object";
	const std::string ObjectSerializer::NAME_ATTRIBUTE = "name";

	const std::string& ObjectSerializer::ElementName() const
	{
		return ELEMENT_NAME;
	}

	Object ObjectSerializer::Read(const pugi::xml_node& node)
	{
		std::string nodeName(node.name());
		if (nodeName == ElementName())
		{
			auto nameAttribute = node.attribute(NAME_ATTRIBUTE.c_str());
			if (nameAttribute != nullptr)
			{
				if (nameAttribute.value() != nullptr)
				{
					return Object(nameAttribute.value());
				}
			}
		}

		throw Exception("Failed to read Object from XML.");
	}

	void ObjectSerializer::Write(pugi::xml_document& document, const Object& element)
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
