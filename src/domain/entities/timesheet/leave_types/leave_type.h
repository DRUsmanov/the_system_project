#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

namespace domain {

namespace detail {
    struct LeaveType{};
} // namespace detail

using LeaveTypeId = utils::Tagged<int, detail::LeaveType>;
using LeaveTypeIdHasher = utils::TaggedHasher<LeaveTypeId>;

struct LeaveType {
    std::string type;
    std::string description;
};
    
} // namespace domain
