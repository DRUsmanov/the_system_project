#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "entities/shop/profession/profession.h"
#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct StaffPosition {};
}  // namespace detail

using StaffPositionId = utils::Tagged<uint64_t, detail::StaffPosition>;
using StaffPositionIdHasher = utils::TaggedHasher<StaffPositionId>;

struct StaffPosition {
    StaffPositionId staff_position_id;
    std::string description;
    ProfessionId default_profession_id;
};

using StaffPositions = std::vector<StaffPosition>;

}  // namespace domain
