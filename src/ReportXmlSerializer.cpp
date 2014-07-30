#include "pch.h"
#include "ReportXmlSerializer.h"

namespace
{
	bool VerifyNode(const pugi::xml_node& node, const std::string& expectedNodeName)
	{
		std::string nodeName = node.name();
		if (nodeName != expectedNodeName)
			return false;

		return true;
	}
}

namespace Divida
{

	const std::string ReportXmlSerializer::REPORT_ELEMENT = "report";
	const std::string ReportXmlSerializer::PERSONS_ELEMENT = "persons";
	const std::string ReportXmlSerializer::PERSON_ELEMENT = "person";
	const std::string ReportXmlSerializer::EXPENSES_ELEMENT = "expenses";
	const std::string ReportXmlSerializer::EXPENSE_ELEMENT = "expense";
	const std::string ReportXmlSerializer::BENEFICIARIES_ELEMENT = "beneficiaries";
	const std::string ReportXmlSerializer::BENEFICIARY_ELEMENT = "beneficiary";
	const std::string ReportXmlSerializer::ITEMS_ELEMENT = "items";
	const std::string ReportXmlSerializer::ITEM_ELEMENT = "item";
	const std::string ReportXmlSerializer::DATE_ELEMENT = "date";

	const std::string ReportXmlSerializer::NAME_ATTRIBUTE = "name";
	const std::string ReportXmlSerializer::PAYER_ATTRIBUTE = "payer";
	const std::string ReportXmlSerializer::PERSON_ATTRIBUTE = "person";
	const std::string ReportXmlSerializer::WEIGHT_ATTRIBUTE = "weight";
	const std::string ReportXmlSerializer::COST_ATTRIBUTE = "cost";
	const std::string ReportXmlSerializer::DAY_ATTRIBUTE = "day";
	const std::string ReportXmlSerializer::MONTH_ATTRIBUTE = "month";
	const std::string ReportXmlSerializer::YEAR_ATTRIBUTE = "year";

	// TODO: throw legitimate exceptions instead of '1'
	Report ReportXmlSerializer::Read(const pugi::xml_node& node)
	{
		if (!VerifyNode(node, REPORT_ELEMENT))
			throw Exception{ "Unexpected node type; expected 'report'." };

		auto reportNameAttribute = node.attribute(NAME_ATTRIBUTE.c_str());
		if (reportNameAttribute == nullptr)
			throw Exception{ "Failed to retrieve 'name' attribute for 'report' node." };

		Report report(reportNameAttribute.value());

		for (auto childNode : node.children())
		{
			std::string childNodeName = childNode.name();
			if (childNodeName == PERSONS_ELEMENT)
			{
				for (auto personNode : childNode.children())
				{
					if (!VerifyNode(personNode, PERSON_ELEMENT))
						throw Exception{ "Unexpected node type; expected 'person'." };;

					std::string name;
					if (!ReadAttribute(personNode, NAME_ATTRIBUTE, name))
						throw 1;

					report.AddPerson(name);
				}
			}
			else if (childNodeName == EXPENSES_ELEMENT)
			{
				for (auto expenseNode : childNode.children())
				{
					if (!VerifyNode(expenseNode, EXPENSE_ELEMENT))
						throw Exception{ "Unexpected node type; expected 'expense'." };;

					std::string expenseName;
					if (!ReadAttribute(expenseNode, NAME_ATTRIBUTE, expenseName))
						throw 1;

					auto dateNode = expenseNode.child(DATE_ELEMENT.c_str());
					if (dateNode == nullptr)
						throw 1;

					int year;
					if (!ReadAttribute(dateNode, YEAR_ATTRIBUTE, year))
						throw 1;
					
					int month;
					if (!ReadAttribute(dateNode, MONTH_ATTRIBUTE, month))
						throw 1;

					int day;
					if (!ReadAttribute(dateNode, DAY_ATTRIBUTE, day))
						throw 1;

					std::string payerName;
					if (!ReadAttribute(expenseNode, PAYER_ATTRIBUTE, payerName))
						throw 1;

					auto payer = report.GetPerson(payerName);
					if (payer == nullptr)
						throw 1;

					auto expense = report.NewExpense(expenseName, Date::Create(day, month, year), payer);

					auto itemsNode = expenseNode.child(ITEMS_ELEMENT.c_str());
					if (itemsNode == nullptr)
						throw 1;

					for (auto itemNode : itemsNode.children())
					{
						if (!VerifyNode(itemNode, ITEM_ELEMENT))
							throw Exception{ "Unexpected node type; expected 'item'." };;

						std::string itemName;
						if (!ReadAttribute(itemNode, NAME_ATTRIBUTE, itemName))
							throw 1;

						float cost;
						if (!ReadAttribute(itemNode, COST_ATTRIBUTE, cost))
							throw 1;

						auto beneficiariesNode = itemNode.child(BENEFICIARIES_ELEMENT.c_str());
						if (beneficiariesNode == nullptr)
							throw 1;

						std::vector<std::shared_ptr<Beneficiary>> beneficiaries;
						for (auto beneficiaryNode : beneficiariesNode.children())
						{
							if (!VerifyNode(beneficiaryNode, BENEFICIARY_ELEMENT))
								throw Exception{ "Unexpected node type; expected 'beneficiary'." };;

							std::string personName;
							if (!ReadAttribute(beneficiaryNode, PERSON_ELEMENT, personName))
								throw 1;

							float weight;
							bool useWeightValue = ReadAttribute(beneficiaryNode, WEIGHT_ATTRIBUTE, weight);

							if (useWeightValue)
								beneficiaries.push_back(std::make_shared<Beneficiary>(report.GetPerson(personName), weight));
							else
								beneficiaries.push_back(std::make_shared<Beneficiary>(report.GetPerson(personName)));
						}

						expense->AddItem(itemName, cost, beneficiaries);
					}
				}
			}
			else
			{
				throw Exception(L"Unrecognized child node of report element.");
			}
		}

		return report;
	}

	void ReportXmlSerializer::Write(pugi::xml_node& node, const Report& report)
	{
		auto reportNode = node.append_child(REPORT_ELEMENT.c_str());
		if (reportNode == nullptr)
			return;

		if (!WriteAttribute(reportNode, NAME_ATTRIBUTE, report.Name().c_str()))
			return;

		auto personsNode = reportNode.append_child(PERSONS_ELEMENT.c_str());
		if (personsNode == nullptr)
			return;

		for (auto person : report.m_persons)
		{
			auto personNode = personsNode.append_child(PERSON_ELEMENT.c_str());
			if (personNode == nullptr)
				return;

			if (!WriteAttribute(personNode, NAME_ATTRIBUTE, person->Name().c_str()))
				return;
		}
		
		auto expensesNode = reportNode.append_child(EXPENSES_ELEMENT.c_str());
		if (expensesNode == nullptr)
			return;

		for (auto expense : report.m_expenses)
		{
			auto expenseNode = expensesNode.append_child(EXPENSE_ELEMENT.c_str());
			if (expenseNode == nullptr)
				return;

			if (!WriteAttribute(expenseNode, NAME_ATTRIBUTE, expense->Name().c_str()))
				return;

			if (!WriteAttribute(expenseNode, PAYER_ATTRIBUTE, expense->Payer()->Name().c_str()))
				return;

			auto dateNode = expenseNode.append_child(DATE_ELEMENT.c_str());
			if (dateNode == nullptr)
				return;

			if (!WriteAttribute(dateNode, YEAR_ATTRIBUTE, expense->Date().Year()))
				return;

			if (!WriteAttribute(dateNode, MONTH_ATTRIBUTE, expense->Date().Month()))
				return;

			if (!WriteAttribute(dateNode, DAY_ATTRIBUTE, expense->Date().Day()))
				return;

			auto itemsNode = expenseNode.append_child(ITEMS_ELEMENT.c_str());
			if (itemsNode == nullptr)
				return;

			auto items = expense->Items();
			for (auto item : items)
			{
				auto itemNode = itemsNode.append_child(ITEM_ELEMENT.c_str());
				if (itemNode == nullptr)
					return;

				if (!WriteAttribute(itemNode, NAME_ATTRIBUTE, item->Name().c_str()))
					return;

				if (!WriteAttribute(itemNode, COST_ATTRIBUTE, item->Cost()))
					return;

				auto beneficiariesNode = itemNode.append_child(BENEFICIARIES_ELEMENT.c_str());
				if (beneficiariesNode == nullptr)
					return;

				auto beneficiaries = item->Beneficiaries();
				for (auto beneficiary : beneficiaries)
				{
					auto beneficiaryNode = beneficiariesNode.append_child(BENEFICIARY_ELEMENT.c_str());
					if (beneficiaryNode == nullptr)
						return;

					if (!WriteAttribute(beneficiaryNode, PERSON_ATTRIBUTE, beneficiary->Person()->Name().c_str()))
						return;

					if (beneficiary->Weight() != 1.0f)
					{
						if (!WriteAttribute(beneficiaryNode, WEIGHT_ATTRIBUTE, beneficiary->Weight()))
							return;
					}
				}
			}
		}
	}

	bool ReportXmlSerializer::ReadAttribute(const pugi::xml_node& node, const std::string& attributeName, std::string& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.value();
		return true;
	}

	bool ReportXmlSerializer::ReadAttribute(const pugi::xml_node& node, const std::string& attributeName, int& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.as_int();
		return true;
	}

	bool ReportXmlSerializer::ReadAttribute(const pugi::xml_node& node, const std::string& attributeName, float& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.as_float();
		return true;
	}

}
