#include "json_formater/json_formater.h"

#include <boost/json.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace infrastructure {

using namespace std::literals;
namespace json = boost::json;
namespace sys = boost::system;

json::object parseString(std::string str) {
    return json::parse(str).as_object();
}

std::string serializeObject(json::object object) {
    return json::serialize(object);
}

}  // namespace infrastructure
