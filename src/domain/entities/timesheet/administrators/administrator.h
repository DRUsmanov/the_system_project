#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <string>

namespace domain {

namespace detail {
    struct Administrator{};
} // namespace detail

using AdministratorId = utils::Tagged<int, detail::Administrator>;
using AdministratorIdHasher = utils::TaggedHasher<AdministratorId>;

struct Administrator {
    std::string type;
};
    
} // namespace domain
