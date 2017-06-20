#include "json_serialization.h"

#include <divida/group.h>

namespace
{
	const std::string c_typeBeneficiary = "beneficiary";
	const std::string c_typeExpense = "expense";
	const std::string c_typeGroup = "group";
	const std::string c_typeItem = "item";
	const std::string c_typePerson = "person";
	const std::string c_typeReport = "report";
	const std::string c_typeTransaction = "transaction";

	const std::string c_fieldAmount = "amount";
	const std::string c_fieldBeneficiaries = "beneficiaries";
	const std::string c_fieldCost = "cost";
	const std::string c_fieldDate = "date";
	const std::string c_fieldExpenses = "expenses";
	const std::string c_fieldFromPerson = "from_person";
	const std::string c_fieldId = "id";
	const std::string c_fieldItems = "items";
	const std::string c_fieldName = "name";
	const std::string c_fieldPayer = "payer";
	const std::string c_fieldPerson = "person";
	const std::string c_fieldPersons = "persons";
	const std::string c_fieldReports = "reports";
	const std::string c_fieldToPerson = "to_person";
	const std::string c_fieldType = "type";
	const std::string c_fieldWeight = "weight";

	bool has_field(const nlohmann::json& json, const std::string& fieldName)
	{
		return json.find(fieldName) != json.end();
	}

	bool has_type_and_fields(const nlohmann::json& json, const std::string& type, const std::vector<std::string>& fields)
	{
		if (!has_field(json, c_fieldType) || json[c_fieldType] != type)
			return false;

		for (auto& field : fields)
		{
			if (!has_field(json, field))
				return false;
		}

		return true;
	}
}

namespace divida::io
{
	std::unique_ptr<group> readGroup(const nlohmann::json& json)
	{
		if (!has_type_and_fields(json, c_typeGroup, { c_fieldName, c_fieldPersons }))
			return nullptr;

		std::string name = json[c_fieldName];
		auto group = std::make_unique<divida::group>(name);
		for (auto& jsonPerson : json[c_fieldPersons])
		{
			// reading the persons from json will create them using this group
			readPerson(jsonPerson, *group);
		}

		if (has_field(json, c_fieldReports))
		{
			for (auto& jsonReport : json[c_fieldReports])
			{
				// reading the reports from json will create them using this group
				readReport(jsonReport, *group);
			}
		}

		return group;
	}

	std::shared_ptr<person> readPerson(const nlohmann::json& json, divida::group& group)
	{
		if (!has_type_and_fields(json, c_typePerson, { c_fieldId, c_fieldName }))
			return nullptr;

		size_t id = json[c_fieldId];
		std::string name = json[c_fieldName];
		auto person = group.person(name);

		if (person->id() != id)
			return nullptr;

		return person;
	}

	std::shared_ptr<report> readReport(const nlohmann::json& json, divida::group& group)
	{
		if (!has_type_and_fields(json, c_typeReport, { c_fieldName }))
			return nullptr;

		std::string name = json[c_fieldName];
		auto report = group.report(name);

		if (has_field(json, c_fieldExpenses))
		{
			for (auto& jsonExpense : json[c_fieldExpenses])
			{
				auto expense = valueFromJson<std::unique_ptr<divida::expense>>(jsonExpense, group);
				if (expense != nullptr)
					report->add_expense(*expense);
			}
		}

		return report;
	}

	template<> std::unique_ptr<beneficiary> valueFromJson(const nlohmann::json& json, const divida::group& group)
	{
		if (!has_type_and_fields(json, c_typeBeneficiary, { c_fieldPerson }))
			return nullptr;

		size_t id = json[c_fieldPerson];

		if (has_field(json, c_fieldWeight))
			return std::make_unique<beneficiary>(group.person(id), json[c_fieldWeight]);
		else
			return std::make_unique<beneficiary>(group.person(id));
	}

	template<> std::unique_ptr<expense> valueFromJson(const nlohmann::json& json, const divida::group& group)
	{
		if (!has_type_and_fields(json, c_typeExpense, { c_fieldName, c_fieldDate, c_fieldPayer }))
			return nullptr;

		std::string name = json[c_fieldName];
		auto date = divida::date::create(json[c_fieldDate][0], json[c_fieldDate][1], json[c_fieldDate][2]);
		size_t payerId = json[c_fieldPayer];
		auto payer = group.person(payerId);

		auto expense = std::make_unique<divida::expense>(name, date, payer);
		if (has_field(json, c_fieldItems))
		{
			for (auto& jsonItem : json[c_fieldItems])
			{
				auto item = valueFromJson<std::unique_ptr<divida::item>>(jsonItem, group).release();
				if (item != nullptr)
					expense->add_item(std::move(*item));
			}
		}

		return expense;
	}

	template<> std::unique_ptr<item> valueFromJson(const nlohmann::json& json, const divida::group& group)
	{
		if (!has_type_and_fields(json, c_typeItem, { c_fieldName, c_fieldCost }))
			return nullptr;

		std::string name = json[c_fieldName];
		float cost = json[c_fieldCost];
		
		if (has_field(json, c_fieldBeneficiaries))
		{
			std::vector<divida::beneficiary> beneficiaries;
			for (auto& jsonBeneficiary : json[c_fieldBeneficiaries])
			{
				auto beneficiary = valueFromJson<std::unique_ptr<divida::beneficiary>>(jsonBeneficiary, group).release();
				if (beneficiary != nullptr)
					beneficiaries.emplace_back(*beneficiary);
			}

			return std::make_unique<divida::item>(name, cost, beneficiaries);
		}

		return std::make_unique<divida::item>(name, cost);
	}
	
	template<> std::unique_ptr<transaction> valueFromJson(const nlohmann::json& json, const divida::group& group)
	{
		if (!has_type_and_fields(json, c_typeTransaction, { c_fieldFromPerson, c_fieldToPerson, c_fieldAmount }))
			return nullptr;

		size_t fromPersonId = json[c_fieldFromPerson];
		size_t toPersonId = json[c_fieldToPerson];
		float amount = json[c_fieldAmount];

		return std::make_unique<transaction>(group.person(fromPersonId), group.person(toPersonId), amount);
	}

	template<> nlohmann::json jsonFromValue(const beneficiary& value)
	{
		nlohmann::json json;
		json[c_fieldType] = c_typeBeneficiary;

		if (value.person() != nullptr)
			json[c_fieldPerson] = value.person()->id();

		if (value.weight() != 1.0f)
			json[c_fieldWeight] = value.weight();

		return json;
	}
	
	template<> nlohmann::json jsonFromValue(const expense& value)
	{
		nlohmann::json json;
		json[c_fieldType] = c_typeExpense;

		json[c_fieldName] = value.name();
		json[c_fieldDate] = { value.date().day(), value.date().month(), value.date().year() };
		json[c_fieldPayer] = value.payer()->id();

		if (!value.items().empty())
		{
			auto jsonItems = nlohmann::json::array();
			for (auto& item : value.items())
				jsonItems.push_back(jsonFromValue(item));

			json[c_fieldItems] = jsonItems;
		}

		return json;
	}

	template<> nlohmann::json jsonFromValue(const group& value)
	{
		nlohmann::json json;
		json[c_fieldType] = c_typeGroup;

		json[c_fieldName] = value.name();

		auto jsonPersons = nlohmann::json::array();
		for (auto& person : value.persons())
			jsonPersons.push_back(jsonFromValue(*person));

		json[c_fieldPersons] = jsonPersons;

		if (!value.reports().empty())
		{
			auto jsonReports = nlohmann::json::array();
			for (auto& report : value.reports())
				jsonReports.push_back(jsonFromValue(*report));

			json[c_fieldReports] = jsonReports;
		}

		return json;
	}
	
	template<> nlohmann::json jsonFromValue(const item& value)
	{
		nlohmann::json json;
		json[c_fieldType] = c_typeItem;

		json[c_fieldName] = value.name();
		json[c_fieldCost] = value.cost();

		if (!value.beneficiaries().empty())
		{
			auto jsonBeneficiaries = nlohmann::json::array();
			for (auto& beneficiary : value.beneficiaries())
				jsonBeneficiaries.push_back(jsonFromValue(beneficiary));

			json[c_fieldBeneficiaries] = jsonBeneficiaries;
		}

		return json;
	}
	
	template<> nlohmann::json jsonFromValue(const person& value)
	{
		nlohmann::json json;
		json[c_fieldType] = c_typePerson;

		json[c_fieldId] = value.id();
		json[c_fieldName] = value.name();

		return json;
	}
	
	template<> nlohmann::json jsonFromValue(const report& value)
	{
		nlohmann::json json;
		json[c_fieldType] = c_typeReport;

		json[c_fieldName] = value.name();

		if (!value.expenses().empty())
		{
			json[c_fieldExpenses] = nlohmann::json::array();
			for (auto& expense : value.expenses())
				json[c_fieldExpenses].push_back(jsonFromValue(expense));
		}

		return json;
	}
	
	template<> nlohmann::json jsonFromValue(const transaction& value)
	{
		nlohmann::json json;
		json[c_fieldType] = c_typeTransaction;

		auto fromPerson = value.from_person();
		auto toPerson = value.to_person();
		if (fromPerson != nullptr && toPerson != nullptr)
		{
			json[c_fieldAmount] = value.amount();
			json[c_fieldFromPerson] = fromPerson->id();
			json[c_fieldToPerson] = toPerson->id();
		}
		
		return json;
	}
}
