#pragma once

#include <cstdint>
#include <string>

namespace application {

struct UserLoginInputDto {
    std::string login;
    std::string password;
};

struct UserIdInputDto {
    uint64_t user_id;
};

struct UserIdOutputDto {
    uint64_t user_id;
};

}  // namespace application
