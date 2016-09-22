#pragma once

#include <catch.hpp>

#include <string>

namespace divida::tests
{
	const std::string c_nameGandalf = "Gandalf";
	const std::string c_nameFrodo = "Frodo";
	const std::string c_nameSam = "Sam";
	const std::string c_nameMerry = "Merry";
	const std::string c_namePippin = "Pippin";
	const std::string c_nameTestGroup = "Test Group";
	const float c_moneyEpsilon = 0.005f;

	std::string resolve_path(const std::string& filename);
}
