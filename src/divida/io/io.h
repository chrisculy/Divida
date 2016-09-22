#pragma once

#include <divida/group.h>

#include <memory>
#include <string>

namespace divida::io
{

std::unique_ptr<divida::group> readGroupFromJsonFile(const std::string& filename);
void writeGroupToJsonFile(const group& value, const std::string& filename);

}
