#pragma once

#include <vector>

#include "Beneficiary.h"
#include "Core.h"
#include "Object.h"

namespace Divida
{
	class Item : public Object
	{
	public:
		Item(const std::wstring& name, float cost);
		Item(const std::wstring& name, float cost, const std::vector<std::shared_ptr<Beneficiary>>& beneficiaries);

		const std::vector<std::shared_ptr<Beneficiary>>& Beneficiaries() const;
		float Cost() const;

		void AddBeneficiary(const std::shared_ptr<Beneficiary> beneficiary);
		void RemoveBeneficiary(const std::shared_ptr<Beneficiary> beneficiary);

		std::wstring ToString() const;
	private:
		float m_cost;
		std::vector<std::shared_ptr<Beneficiary>> m_beneficiaries;
	};

	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::unique_ptr<Item>& ptr);
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::shared_ptr<Item>& ptr);
	std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t>>& o, const std::weak_ptr<Item>& ptr);
}
