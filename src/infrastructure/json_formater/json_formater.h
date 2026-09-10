#pragma once

#include <boost/json.hpp>
#include <filesystem>
#include <string>
#include <utility>

namespace infrastructure {

namespace json = boost::json;

json::object parseString(std::string str);
std::string serializeObject(json::object object);

}  // namespace infrastructure
