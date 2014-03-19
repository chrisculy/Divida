#include "pch.h"

#include "ObjectSerializer.h"

namespace Divida
{
	const std::wstring ObjectSerializer::ELEMENT_NAME = L"object";
	const std::wstring ObjectSerializer::NAME_ATTRIBUTE = L"name";

	const std::wstring& ObjectSerializer::ElementName() const
	{
		return ELEMENT_NAME;
	}

	Object ObjectSerializer::Read(const pugi::xml_node& node)
	{
		std::wstring nodeName(node.name());
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

		throw new std::exception("Failed to read Object from XML.");
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