#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

namespace infrastructure {

namespace keys {

constexpr std::string USER_ID{"user_id"};
constexpr std::string EMPLOYEE_ID{"employee_id"};
constexpr std::string ISSUER{"The system server"};
constexpr std::string TYPE{"JWT"};

}  // namespace keys

class TokenManager {
public:
    using Payload = std::optional<std::unordered_map<std::string, uint64_t>>;
    using Token = std::optional<std::string>;

    Token createToken(uint64_t user_id, uint64_t employee_id) const;
    Payload getPayloadFromToken(std::string_view token) const;
};

}  // namespace infrastructure
