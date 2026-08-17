#pragma once

#include <jwt-cpp/jwt.h>
#include <optional>
#include <string_view>
#include <unordered_map>

namespace infrastructure {

class TokenManager {
public:
    using Payload = std::optional<std::unordered_map<std::string, int>>;
    using Token = std::optional<std::string>;

    Token createToken(int user_id, int employee_id) const;
    Payload getPayloadFromToken(std::string_view token) const;
};

}  // namespace infrastructure
