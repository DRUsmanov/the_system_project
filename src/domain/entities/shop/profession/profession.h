#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <optional>

namespace domain {

namespace detail {
    struct Profession{};
} // namespace detail

using ProfessionId = utils::Tagged<int, detail::Profession>;
using ProfessionIdHasher = utils::TaggedHasher<ProfessionId>;

struct Profession {
    std::string name;
};
    
} // namespace domain
