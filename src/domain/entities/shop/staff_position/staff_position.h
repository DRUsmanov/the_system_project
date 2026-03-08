#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <optional>

namespace domain {

namespace detail {
    struct StaffPosition{};
} // namespace detail

using StaffPositionId = utils::Tagged<int, detail::StaffPosition>;
using StaffPositionIdHasher = utils::TaggedHasher<StaffPositionId>;

struct StaffPosition {
    std::string name;
};
    
} // namespace domain
