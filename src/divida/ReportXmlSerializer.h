#pragma once

#include "Report.h"

#include <pugixml.hpp>

namespace divida
{
	class report_xml_serializer
	{
	public:
		static std::unique_ptr<report> read(const pugi::xml_node& node);
		static void write(pugi::xml_node& node, const report& report);

	private:
		static bool read_attribute(const pugi::xml_node& node, const std::string& attributeName, std::string& attributeValue);
		static bool read_attribute(const pugi::xml_node& node, const std::string& attributeName, int& attributeValue);
		static bool read_attribute(const pugi::xml_node& node, const std::string& attributeName, float& attributeValue);
		template<typename T> static bool write_attribute(pugi::xml_node& node, const std::string& attributeName, const T& attributeValue);

		static const std::string c_reportElement;
		static const std::string c_personsElement;
		static const std::string c_personElement;
		static const std::string c_expensesElement;
		static const std::string c_expenseElement;
		static const std::string c_beneficiariesElement;
		static const std::string c_beneficiaryElement;
		static const std::string c_itemsElement;
		static const std::string c_itemElement;
		static const std::string c_dateElement;

		static const std::string c_nameAttribute;
		static const std::string c_countAttribute;
		static const std::string c_payerAttribute;
		static const std::string c_personAttribute;
		static const std::string c_weightAttribute;
		static const std::string c_costAttribute;
		static const std::string c_dayAttribute;
		static const std::string c_monthAttribute;
		static const std::string c_yearAttribute;
	};

	template<typename T> bool report_xml_serializer::write_attribute(pugi::xml_node& node, const std::string& attributeName, const T& attributeValue)
	{
		auto attribute = node.append_attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		if (!attribute.set_value(attributeValue))
			return false;

		return true;
	}
}
