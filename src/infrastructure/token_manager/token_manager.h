#pragma once

#include <jwt-cpp/jwt.h>
#include <unordered_map>
#include <optional>

namespace infrastructure {

class TokenManager {
public:
    using Payload = std::optional<std::unordered_map<std::string, int>>;
    using Token = std::optional<std::string>;

    Token CreateToken(int user_id, int employee_id) const;
    Payload GetPayloadFromToken(std::string token) const;
};
    
} // namespace infrastructure
