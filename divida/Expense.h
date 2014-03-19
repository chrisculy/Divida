#pragma once

#include <memory>
#include <vector>

#include "Beneficiary.h"
#include "Core.h"
#include "Date.h"
#include "Item.h"
#include "Object.h"
#include "Person.h"

namespace Divida
{
	class Expense : public Object
	{
	public:
		Expense(const std::wstring& name, const Date& date, const std::shared_ptr<Person> payer);

		const Date& Date() const;
		const std::shared_ptr<Person> Payer() const;
		const float Total() const;
		const std::vector<std::shared_ptr<Item>>& Items() const;

		void SetDate(const Divida::Date& date);
		void SetPayer(const std::shared_ptr<Person> payer);

		void AddItem(const std::wstring& name, float cost, const std::vector < std::shared_ptr < Beneficiary >> &beneficiaries);
		void AddItems(const std::vector<std::pair<std::wstring, float>>& namesAndCosts, const std::vector<std::shared_ptr<Beneficiary>>& beneficiaries);

		std::wstring ToString() const;

	private:
		Divida::Date m_date;
		std::shared_ptr<Person> m_payer;
		std::vector<std::shared_ptr<Item>> m_items;
	};

	DECLARE_TO_STRING_SMART_PTRS(Expense);
}
