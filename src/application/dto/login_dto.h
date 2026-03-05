#pragma once

#include <string>

namespace application {

struct InputLoginDto{
    std::string login;
    std::string password;
};

struct OutputLoginDto{
    bool acces_accepted = false;
    std::string login;
    uint64_t permisions = 0;
};

} // namespace application

