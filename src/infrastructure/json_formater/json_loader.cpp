#include "json_loader.h"

#include <boost/json.hpp>
#include <iterator>
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <optional>
#include <sstream>
#include <chrono>
#include <fstream>
#include <chrono>
#include <iostream>

namespace infrastructure {

using namespace std::literals;
namespace json = boost::json;
namespace sys = boost::system;

// ##### KEYS #####
const std::string ID = "id"s;

json::object ParseString(std::string str){
    return json::parse(str).as_object();
}

}  // namespace infrastructure
