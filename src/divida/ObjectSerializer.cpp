#include "ObjectSerializer.h"

#include "Exception.h"

namespace divida
{
	const std::string object_serializer::c_elementName = "object";
	const std::string object_serializer::c_nameAttribute = "name";

	const std::string& object_serializer::element_name() const
	{
		return c_elementName;
	}

	object object_serializer::read(const pugi::xml_node& node)
	{
		std::string nodeName(node.name());
		if (nodeName == element_name())
		{
			auto nameAttribute = node.attribute(c_nameAttribute.c_str());
			if (nameAttribute != nullptr)
			{
				if (nameAttribute.value() != nullptr)
				{
					return object(nameAttribute.value());
				}
			}
		}

		throw exception("Failed to read object from XML.");
	}

	void object_serializer::write(pugi::xml_document& document, const object& element)
	{
		auto node = document.append_child(element_name().c_str());
		if (node == nullptr)
			return;

		auto nameAttribute = node.append_attribute(c_nameAttribute.c_str());
		if (nameAttribute == nullptr)
			return;

		if (!nameAttribute.set_value(element.name().c_str()))
			return;
	}
}
