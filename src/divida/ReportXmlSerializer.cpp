#include "ReportXmlSerializer.h"

#include "Exception.h"

namespace
{
	bool verify_node(const pugi::xml_node& node, const std::string& expectedNodeName)
	{
		std::string nodeName = node.name();
		if (nodeName != expectedNodeName)
			return false;

		return true;
	}
}

namespace divida
{

	const std::string report_xml_serializer::c_reportElement = "report";
	const std::string report_xml_serializer::c_personsElement = "persons";
	const std::string report_xml_serializer::c_personElement = "person";
	const std::string report_xml_serializer::c_expensesElement = "expenses";
	const std::string report_xml_serializer::c_expenseElement = "expense";
	const std::string report_xml_serializer::c_beneficiariesElement = "beneficiaries";
	const std::string report_xml_serializer::c_beneficiaryElement = "beneficiary";
	const std::string report_xml_serializer::c_itemsElement = "items";
	const std::string report_xml_serializer::c_itemElement = "item";
	const std::string report_xml_serializer::c_dateElement = "date";

	const std::string report_xml_serializer::c_nameAttribute = "name";
	const std::string report_xml_serializer::c_payerAttribute = "payer";
	const std::string report_xml_serializer::c_personAttribute = "person";
	const std::string report_xml_serializer::c_weightAttribute = "weight";
	const std::string report_xml_serializer::c_costAttribute = "cost";
	const std::string report_xml_serializer::c_dayAttribute = "day";
	const std::string report_xml_serializer::c_monthAttribute = "month";
	const std::string report_xml_serializer::c_yearAttribute = "year";

	// TODO: throw legitimate exceptions instead of '1'
	std::unique_ptr<report> report_xml_serializer::read(const pugi::xml_node& node)
	{
		if (!verify_node(node, c_reportElement))
			throw exception{ "Unexpected node type; expected 'report'." };

		auto reportNameAttribute = node.attribute(c_nameAttribute.c_str());
		if (reportNameAttribute == nullptr)
			throw exception{ "Failed to retrieve 'name' attribute for 'report' node." };

		auto report = std::make_unique<divida::report>(reportNameAttribute.value());
		for (auto childNode : node.children())
		{
			std::string childNodeName = childNode.name();
			if (childNodeName == c_personsElement)
			{
				for (auto personNode : childNode.children())
				{
					if (!verify_node(personNode, c_personElement))
						throw exception{ "Unexpected node type; expected 'person'." };;

					std::string name;
					if (!read_attribute(personNode, c_nameAttribute, name))
						throw 1;

					report->add_person(name);
				}
			}
			else if (childNodeName == c_expensesElement)
			{
				for (auto expenseNode : childNode.children())
				{
					if (!verify_node(expenseNode, c_expenseElement))
						throw exception{ "Unexpected node type; expected 'expense'." };;

					std::string expenseName;
					if (!read_attribute(expenseNode, c_nameAttribute, expenseName))
						throw 1;

					auto dateNode = expenseNode.child(c_dateElement.c_str());
					if (dateNode == nullptr)
						throw 1;

					int year;
					if (!read_attribute(dateNode, c_yearAttribute, year))
						throw 1;
					
					int month;
					if (!read_attribute(dateNode, c_monthAttribute, month))
						throw 1;

					int day;
					if (!read_attribute(dateNode, c_dayAttribute, day))
						throw 1;

					std::string payerName;
					if (!read_attribute(expenseNode, c_payerAttribute, payerName))
						throw 1;

					auto payer = report->get_person(payerName);
					if (payer == nullptr)
						throw 1;

					auto expense = report->new_expense(expenseName, date::create(day, month, year), payer);

					auto itemsNode = expenseNode.child(c_itemsElement.c_str());
					if (itemsNode == nullptr)
						throw 1;

					for (auto itemNode : itemsNode.children())
					{
						if (!verify_node(itemNode, c_itemElement))
							throw exception{ "Unexpected node type; expected 'item'." };;

						std::string itemName;
						if (!read_attribute(itemNode, c_nameAttribute, itemName))
							throw 1;

						float cost;
						if (!read_attribute(itemNode, c_costAttribute, cost))
							throw 1;

						auto beneficiariesNode = itemNode.child(c_beneficiariesElement.c_str());
						if (beneficiariesNode == nullptr)
							throw 1;

						std::vector<std::shared_ptr<beneficiary>> beneficiaries;
						for (auto beneficiaryNode : beneficiariesNode.children())
						{
							if (!verify_node(beneficiaryNode, c_beneficiaryElement))
								throw exception{ "Unexpected node type; expected 'beneficiary'." };;

							std::string personName;
							if (!read_attribute(beneficiaryNode, c_personElement, personName))
								throw 1;

							float weight;
							bool useWeightValue = read_attribute(beneficiaryNode, c_weightAttribute, weight);

							if (useWeightValue)
								beneficiaries.push_back(std::make_shared<beneficiary>(report->get_person(personName), weight));
							else
								beneficiaries.push_back(std::make_shared<beneficiary>(report->get_person(personName)));
						}

						expense->add_item(itemName, cost, beneficiaries);
					}
				}
			}
			else
			{
				throw exception("Unrecognized child node of report element.");
			}
		}

		return std::move(report);
	}

	void report_xml_serializer::write(pugi::xml_node& node, const report& report)
	{
		auto reportNode = node.append_child(c_reportElement.c_str());
		if (reportNode == nullptr)
			return;

		if (!write_attribute(reportNode, c_nameAttribute, report.name().c_str()))
			return;

		auto personsNode = reportNode.append_child(c_personsElement.c_str());
		if (personsNode == nullptr)
			return;

		for (auto person : report.m_persons)
		{
			auto personNode = personsNode.append_child(c_personElement.c_str());
			if (personNode == nullptr)
				return;

			if (!write_attribute(personNode, c_nameAttribute, person->name().c_str()))
				return;
		}
		
		auto expensesNode = reportNode.append_child(c_expensesElement.c_str());
		if (expensesNode == nullptr)
			return;

		for (auto expense : report.m_expenses)
		{
			auto expenseNode = expensesNode.append_child(c_expenseElement.c_str());
			if (expenseNode == nullptr)
				return;

			if (!write_attribute(expenseNode, c_nameAttribute, expense->name().c_str()))
				return;

			if (!write_attribute(expenseNode, c_payerAttribute, expense->payer()->name().c_str()))
				return;

			auto dateNode = expenseNode.append_child(c_dateElement.c_str());
			if (dateNode == nullptr)
				return;

			if (!write_attribute(dateNode, c_yearAttribute, expense->date().year()))
				return;

			if (!write_attribute(dateNode, c_monthAttribute, expense->date().month()))
				return;

			if (!write_attribute(dateNode, c_dayAttribute, expense->date().day()))
				return;

			auto itemsNode = expenseNode.append_child(c_itemsElement.c_str());
			if (itemsNode == nullptr)
				return;

			auto items = expense->items();
			for (auto item : items)
			{
				auto itemNode = itemsNode.append_child(c_itemElement.c_str());
				if (itemNode == nullptr)
					return;

				if (!write_attribute(itemNode, c_nameAttribute, item->name().c_str()))
					return;

				if (!write_attribute(itemNode, c_costAttribute, item->cost()))
					return;

				auto beneficiariesNode = itemNode.append_child(c_beneficiariesElement.c_str());
				if (beneficiariesNode == nullptr)
					return;

				auto beneficiaries = item->beneficiaries();
				for (auto beneficiary : beneficiaries)
				{
					auto beneficiaryNode = beneficiariesNode.append_child(c_beneficiaryElement.c_str());
					if (beneficiaryNode == nullptr)
						return;

					if (!write_attribute(beneficiaryNode, c_personAttribute, beneficiary->person()->name().c_str()))
						return;

					if (beneficiary->weight() != 1.0f)
					{
						if (!write_attribute(beneficiaryNode, c_weightAttribute, beneficiary->weight()))
							return;
					}
				}
			}
		}
	}

	bool report_xml_serializer::read_attribute(const pugi::xml_node& node, const std::string& attributeName, std::string& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.value();
		return true;
	}

	bool report_xml_serializer::read_attribute(const pugi::xml_node& node, const std::string& attributeName, int& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.as_int();
		return true;
	}

	bool report_xml_serializer::read_attribute(const pugi::xml_node& node, const std::string& attributeName, float& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.as_float();
		return true;
	}

}
