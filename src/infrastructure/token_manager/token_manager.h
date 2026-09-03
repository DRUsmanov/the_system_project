#pragma once

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

namespace infrastructure {

class TokenManager {
public:
    using Payload = std::optional<std::unordered_map<std::string, uint64_t>>;
    using Token = std::optional<std::string>;

    Token createToken(uint64_t user_id, uint64_t employee_id) const;
    Payload getPayloadFromToken(std::string_view token) const;
};

}  // namespace infrastructure
