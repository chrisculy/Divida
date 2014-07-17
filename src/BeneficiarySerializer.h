#pragma once

#include "Beneficiary.h"
#include "IXmlSerializer.h"

namespace Divida
{
	class BeneficiarySerializer : public IXmlSerializer<Beneficiary>
	{
	public:
		virtual const std::wstring& ElementName() const;
		virtual Beneficiary Read(const pugi::xml_node& node);
		virtual void Write(pugi::xml_document & document, const Beneficiary& element);

	private:
		static const std::wstring ELEMENT_NAME;
		static const std::wstring PERSON_ATTRIBUTE;
		static const std::wstring WEIGHT_ATTRIBUTE;
	};
}
