#pragma once

#include <cstdint>
#include <string>

namespace application {

struct UserAccessDto {
    uint64_t user_id;
};

struct UserLoginRequestDto {
    std::string login;
    std::string password;
};

struct UserLoginResponseDto {
    uint64_t user_id;
    uint64_t employee_id;
};

}  // namespace application
