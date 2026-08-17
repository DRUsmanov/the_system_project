#pragma once

#include <boost/json.hpp>
#include <filesystem>
#include <utility>

namespace infrastructure {

namespace json = boost::json;

json::object parseString(std::string str);

}  // namespace infrastructure
