#pragma once

#include <filesystem>
#include <boost/json.hpp>
#include <utility>

namespace infrastructure {

namespace json = boost::json;

json::object ParseString(std::string str);

}  // namespace infrastructure
