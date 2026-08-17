#pragma once

#include <string_view>

namespace infrastructure {

std::string decodeUrl(std::string_view encoded_url);

}  // namespace infrastructure