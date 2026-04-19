#pragma once

#include <string_view>

namespace infrastructure {

std::string DecodeUrl(std::string_view encoded_url);

} // namespace infrastructure