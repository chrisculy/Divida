#include "PersonSerializer.h"

#include "Exception.h"
#include "ObjectSerializer.h"

namespace divida
{
	const std::string person_serializer::c_elementName = "person";
	const std::string person_serializer::c_nameAttribute = "name";

	const std::string& person_serializer::element_name() const
	{
		return c_elementName;
	}

	person person_serializer::read(const pugi::xml_node& node)
	{
		std::string nodeName(node.name());
		if (nodeName == element_name())
		{
			auto nameAttribute = node.attribute(c_nameAttribute.c_str());
			if (nameAttribute != nullptr)
			{
				if (nameAttribute.value() != nullptr)
				{
					return person(nameAttribute.value());
				}
			}
		}

		throw exception("Failed to read person from XML.");
	}

	void person_serializer::write(pugi::xml_document& document, const person& element)
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
