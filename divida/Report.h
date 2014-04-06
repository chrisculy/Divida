#pragma once

#include <map>
#include <memory>
#include <pugixml.hpp>
#include <string>
#include <vector>

#include "Date.h"
#include "Expense.h"
#include "Person.h"
#include "Transaction.h"

namespace Divida
{
	struct ReportExpense
	{
		ReportExpense(const std::wstring& name, float weight, float amount);

		std::wstring Name;
		float Weight;
		float Amount;
	};

	struct ReportPayment
	{
		ReportPayment(const std::wstring& name, float amount);

		std::wstring Name;
		float Amount;
	};

	struct ReportInfo
	{
		std::vector<ReportPayment> Payments;
		std::vector<ReportExpense> Expenses;
	};

	class Report : public Object
	{
	public:
		Report(const std::wstring& name);

		void AddPerson(const std::wstring& name);
		const std::shared_ptr<Person> GetPerson(const std::wstring& name) const;

		const std::shared_ptr<Expense> NewExpense(const std::wstring& name, const Date& date, const std::shared_ptr<Person> payer);
		const std::shared_ptr<Expense> GetExpense(const std::wstring& name) const;

		const std::vector<std::shared_ptr<Person>>& Persons() const;
		const std::vector<std::shared_ptr<Expense>>& Expenses() const;

		std::vector<std::shared_ptr<Transaction>> CalculateTransactions();
        const ReportInfo* GetReportInfoForPerson(const std::wstring& name) const;
		unsigned int GetItemNamePrintWidth() const;

	private:
		friend class ReportXmlSerializer;

		typedef std::vector<std::pair<std::weak_ptr<Person>, float>> OwingTotalsTable;

		void AddPaymentForPerson(const std::shared_ptr<Person>& person, const std::wstring& name, float amount);
		void AddExpenseForPerson(const std::shared_ptr<Person>& person, const std::wstring& name, float weight, float amount);
		void UpdateAmount(const std::weak_ptr<Person>& person, float difference);

		std::vector<std::shared_ptr<Person>> m_persons;
		std::vector<std::shared_ptr<Expense>> m_expenses;
		OwingTotalsTable m_owingTotals;
		std::map<std::shared_ptr<Person>, ReportInfo> m_info;
	};

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
