#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <string>

namespace domain {

namespace detail {
    struct AdministratorIdTag{};
} // namespace detail

using AdministratorId = utils::Tagged<int, detail::AdministratorIdTag>;
using AdministratorIdHasher = utils::TaggedHasher<AdministratorId>;

struct Administrator {
    std::string type;
};
    
} // namespace domain
