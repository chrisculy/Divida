#pragma once

#include "Report.h"

#include <pugixml.hpp>

namespace Divida
{
	class ReportXmlSerializer
	{
	public:
		static Report Read(const pugi::xml_node& node);
		static void Write(pugi::xml_node& node, const Report& report);

	private:
		static bool ReadAttribute(const pugi::xml_node& node, const std::string& attributeName, std::string& attributeValue);
		static bool ReadAttribute(const pugi::xml_node& node, const std::string& attributeName, int& attributeValue);
		static bool ReadAttribute(const pugi::xml_node& node, const std::string& attributeName, float& attributeValue);
		template<typename T> static bool WriteAttribute(pugi::xml_node& node, const std::string& attributeName, const T& attributeValue);

		static const std::string REPORT_ELEMENT;
		static const std::string PERSONS_ELEMENT;
		static const std::string PERSON_ELEMENT;
		static const std::string EXPENSES_ELEMENT;
		static const std::string EXPENSE_ELEMENT;
		static const std::string BENEFICIARIES_ELEMENT;
		static const std::string BENEFICIARY_ELEMENT;
		static const std::string ITEMS_ELEMENT;
		static const std::string ITEM_ELEMENT;
		static const std::string DATE_ELEMENT;

		static const std::string NAME_ATTRIBUTE;
		static const std::string COUNT_ATTRIBUTE;
		static const std::string PAYER_ATTRIBUTE;
		static const std::string PERSON_ATTRIBUTE;
		static const std::string WEIGHT_ATTRIBUTE;
		static const std::string COST_ATTRIBUTE;
		static const std::string DAY_ATTRIBUTE;
		static const std::string MONTH_ATTRIBUTE;
		static const std::string YEAR_ATTRIBUTE;
	};

	template<typename T> bool ReportXmlSerializer::WriteAttribute(pugi::xml_node& node, const std::string& attributeName, const T& attributeValue)
	{
		auto attribute = node.append_attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		if (!attribute.set_value(attributeValue))
			return false;

		return true;
	}
}
