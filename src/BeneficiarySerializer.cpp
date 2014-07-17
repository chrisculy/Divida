#include "pch.h"
#include "BeneficiarySerializer.h"

namespace Divida
{
	const std::wstring BeneficiarySerializer::ELEMENT_NAME = L"beneficiary";
	const std::wstring BeneficiarySerializer::PERSON_ATTRIBUTE = L"person";
	const std::wstring BeneficiarySerializer::WEIGHT_ATTRIBUTE = L"weight";

	const std::wstring& BeneficiarySerializer::ElementName() const
	{
		return ELEMENT_NAME;
	}

	Beneficiary BeneficiarySerializer::Read(const pugi::xml_node& node)
	{
		std::wstring nodeName(node.name());
		if (nodeName == ElementName())
		{
			std::wstring personName;

			auto personAttribute = node.attribute(PERSON_ATTRIBUTE.c_str());
			if (personAttribute != nullptr)
				personName = personAttribute.value();
		}

		throw 1;
	}

	void BeneficiarySerializer::Write(pugi::xml_document & document, const Beneficiary& element)
	{
		auto node = document.append_child(ElementName().c_str());
		if (node == nullptr)
			return;

		if (element.Person() != nullptr)
		{
			auto personAttribute = node.append_attribute(PERSON_ATTRIBUTE.c_str());
			if (personAttribute == nullptr)
				return;

			personAttribute.set_value(element.Person()->Name().c_str());
		}

		if (element.Weight() != 1.0f)
		{
			auto weightAttribute = node.append_attribute(WEIGHT_ATTRIBUTE.c_str());
			if (weightAttribute == nullptr)
				return;

			weightAttribute.set_value(element.Weight());
		}
	}
}
