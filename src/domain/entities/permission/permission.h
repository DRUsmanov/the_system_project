#pragma once

#include <bitset>
#include <cstdint>
#include <string>

namespace domain {

enum class PermissionsType : size_t { READ = 0, WRITE = 1 };

struct Permissions {
public:
    explicit Permissions(unsigned long mask) : permissions{std::bitset<8>(mask)} {}

    void addPermission(PermissionsType permission) {
        auto mask = static_cast<size_t>(permission);
        permissions.set(mask);
    }

    void removePermission(PermissionsType permission) {
        auto mask = static_cast<size_t>(permission);
        permissions.reset(mask);
    }

    bool hasPermission(PermissionsType permission) {
        auto mask = static_cast<size_t>(permission);
        return permissions.test(mask);
    }

    unsigned long toMask() const {
        return permissions.to_ulong();
    }

private:
    std::bitset<8> permissions = 0;
};

}  // namespace domain