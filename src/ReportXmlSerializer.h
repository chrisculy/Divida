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
		static bool ReadAttribute(const pugi::xml_node& node, const std::wstring& attributeName, std::wstring& attributeValue);
		static bool ReadAttribute(const pugi::xml_node& node, const std::wstring& attributeName, int& attributeValue);
		static bool ReadAttribute(const pugi::xml_node& node, const std::wstring& attributeName, float& attributeValue);
		template<typename T> static bool WriteAttribute(pugi::xml_node& node, const std::wstring& attributeName, const T& attributeValue);

		static const std::wstring REPORT_ELEMENT;
		static const std::wstring PERSONS_ELEMENT;
		static const std::wstring PERSON_ELEMENT;
		static const std::wstring EXPENSES_ELEMENT;
		static const std::wstring EXPENSE_ELEMENT;
		static const std::wstring BENEFICIARIES_ELEMENT;
		static const std::wstring BENEFICIARY_ELEMENT;
		static const std::wstring ITEMS_ELEMENT;
		static const std::wstring ITEM_ELEMENT;
		static const std::wstring DATE_ELEMENT;

		static const std::wstring NAME_ATTRIBUTE;
		static const std::wstring COUNT_ATTRIBUTE;
		static const std::wstring PAYER_ATTRIBUTE;
		static const std::wstring PERSON_ATTRIBUTE;
		static const std::wstring WEIGHT_ATTRIBUTE;
		static const std::wstring COST_ATTRIBUTE;
		static const std::wstring DAY_ATTRIBUTE;
		static const std::wstring MONTH_ATTRIBUTE;
		static const std::wstring YEAR_ATTRIBUTE;
	};

	template<typename T> bool ReportXmlSerializer::WriteAttribute(pugi::xml_node& node, const std::wstring& attributeName, const T& attributeValue)
	{
		auto attribute = node.append_attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		if (!attribute.set_value(attributeValue))
			return false;

		return true;
	}
}
