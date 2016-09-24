#include "io.h"

#include "json_serialization.h"

#include <divida/exception.h>

#include <json.hpp>

#include <fstream>

namespace divida::io
{

std::unique_ptr<divida::group> readGroupFromJsonFile(const std::string& filename)
{
	std::ifstream in(filename);
	if (!in)
		return nullptr;

	nlohmann::json json;
	in >> json;

	return readGroup(json);
}

void writeGroupToJsonFile(const divida::group& group, const std::string& filename)
{
	auto json = jsonFromValue(group);

	std::ofstream out(filename);
	if (!out)
		throw exception("Unable to open file for output.");

	out << std::setw(4) << json;
}

}
