#pragma once

#include <divida/beneficiary.h>
#include <divida/expense.h>
#include <divida/item.h>
#include <divida/person.h>
#include <divida/report.h>
#include <divida/transaction.h>

#include <json.hpp>

namespace divida::io
{

std::unique_ptr<group> readGroup(const nlohmann::json& json);
std::shared_ptr<person> readPerson(const nlohmann::json& json, divida::group& group);
std::shared_ptr<report> readReport(const nlohmann::json& json, divida::group& group);

template<typename T>
T valueFromJson(const nlohmann::json& json, const divida::group& group)
{
	static_assert(false, "Unsupported type!");
}

template<> std::unique_ptr<beneficiary> valueFromJson(const nlohmann::json& json, const divida::group& group);
template<> std::unique_ptr<expense> valueFromJson(const nlohmann::json& json, const divida::group& group);
template<> std::unique_ptr<item> valueFromJson(const nlohmann::json& json, const divida::group& group);
template<> std::unique_ptr<transaction> valueFromJson(const nlohmann::json& jso, const divida::group& group);

template<typename T>
nlohmann::json jsonFromValue(const T& value)
{
	static_assert(false, "Unsupported type!");
}

template<> nlohmann::json jsonFromValue(const beneficiary& value);
template<> nlohmann::json jsonFromValue(const expense& value);
template<> nlohmann::json jsonFromValue(const group& value);
template<> nlohmann::json jsonFromValue(const item& value);
template<> nlohmann::json jsonFromValue(const person& value);
template<> nlohmann::json jsonFromValue(const report& value);
template<> nlohmann::json jsonFromValue(const transaction& value);

}
