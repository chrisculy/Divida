#pragma once

#include <map>
#include <memory>

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
}
