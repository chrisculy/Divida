#include "BeneficiarySerializer.h"

namespace divida
{
	const std::string beneficiary_serializer::c_elementName = "beneficiary";
	const std::string beneficiary_serializer::c_personAttribute = "person";
	const std::string beneficiary_serializer::c_weightAttribute = "weight";

	const std::string& beneficiary_serializer::element_name() const
	{
		return c_elementName;
	}

	beneficiary beneficiary_serializer::read(const pugi::xml_node& node)
	{
		std::string nodeName(node.name());
		if (nodeName == element_name())
		{
			std::string personName;

			auto personAttribute = node.attribute(c_personAttribute.c_str());
			if (personAttribute != nullptr)
				personName = personAttribute.value();
		}

		throw 1;
	}

	void beneficiary_serializer::write(pugi::xml_document & document, const beneficiary& element)
	{
		auto node = document.append_child(element_name().c_str());
		if (node == nullptr)
			return;

		if (element.person() != nullptr)
		{
			auto personAttribute = node.append_attribute(c_personAttribute.c_str());
			if (personAttribute == nullptr)
				return;

			personAttribute.set_value(element.person()->name().c_str());
		}

		if (element.weight() != 1.0f)
		{
			auto weightAttribute = node.append_attribute(c_weightAttribute.c_str());
			if (weightAttribute == nullptr)
				return;

			weightAttribute.set_value(element.weight());
		}
	}
}
