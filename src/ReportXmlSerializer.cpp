#include "pch.h"
#include "ReportXmlSerializer.h"

namespace
{
	bool VerifyNode(const pugi::xml_node& node, const std::wstring& expectedNodeName)
	{
		std::wstring nodeName = node.name();
		if (nodeName != expectedNodeName)
			return false;

		return true;
	}
}

namespace Divida
{

const std::wstring ReportXmlSerializer::REPORT_ELEMENT = L"report";
	const std::wstring ReportXmlSerializer::PERSONS_ELEMENT = L"persons";
	const std::wstring ReportXmlSerializer::PERSON_ELEMENT = L"person";
	const std::wstring ReportXmlSerializer::EXPENSES_ELEMENT = L"expenses";
	const std::wstring ReportXmlSerializer::EXPENSE_ELEMENT = L"expense";
	const std::wstring ReportXmlSerializer::BENEFICIARIES_ELEMENT = L"beneficiaries";
	const std::wstring ReportXmlSerializer::BENEFICIARY_ELEMENT = L"beneficiary";
	const std::wstring ReportXmlSerializer::ITEMS_ELEMENT = L"items";
	const std::wstring ReportXmlSerializer::ITEM_ELEMENT = L"item";
	const std::wstring ReportXmlSerializer::DATE_ELEMENT = L"date";

	const std::wstring ReportXmlSerializer::NAME_ATTRIBUTE = L"name";
	const std::wstring ReportXmlSerializer::PAYER_ATTRIBUTE = L"payer";
	const std::wstring ReportXmlSerializer::PERSON_ATTRIBUTE = L"person";
	const std::wstring ReportXmlSerializer::WEIGHT_ATTRIBUTE = L"weight";
	const std::wstring ReportXmlSerializer::COST_ATTRIBUTE = L"cost";
	const std::wstring ReportXmlSerializer::DAY_ATTRIBUTE = L"day";
	const std::wstring ReportXmlSerializer::MONTH_ATTRIBUTE = L"month";
	const std::wstring ReportXmlSerializer::YEAR_ATTRIBUTE = L"year";

	Report ReportXmlSerializer::Read(const pugi::xml_node& node)
	{
		if (!VerifyNode(node, REPORT_ELEMENT))
			throw 1;

		auto reportNameAttribute = node.attribute(NAME_ATTRIBUTE.c_str());
		if (reportNameAttribute == nullptr)
			throw 1;

		Report report(reportNameAttribute.value());

		for (auto childNode : node.children())
		{
			std::wstring childNodeName = childNode.name();
			if (childNodeName == PERSONS_ELEMENT)
			{
				for (auto personNode : childNode.children())
				{
					if (!VerifyNode(personNode, PERSON_ELEMENT))
						throw 1;

					std::wstring name;
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
						throw 1;

					std::wstring expenseName;
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

					std::wstring payerName;
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
							throw 1;

						std::wstring itemName;
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
								throw 1;

							std::wstring personName;
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

	bool ReportXmlSerializer::ReadAttribute(const pugi::xml_node& node, const std::wstring& attributeName, std::wstring& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.value();
		return true;
	}

	bool ReportXmlSerializer::ReadAttribute(const pugi::xml_node& node, const std::wstring& attributeName, int& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.as_int();
		return true;
	}

	bool ReportXmlSerializer::ReadAttribute(const pugi::xml_node& node, const std::wstring& attributeName, float& attributeValue)
	{
		auto attribute = node.attribute(attributeName.c_str());
		if (attribute == nullptr)
			return false;

		attributeValue = attribute.as_float();
		return true;
	}

}
