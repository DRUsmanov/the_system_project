#pragma once

#include "utils/tagged.h"
#include "domain/value_data/types.h"

#include <optional>

namespace domain {

namespace detail {
    struct Department{};
} // namespace detail

using DepartmentId = utils::Tagged<int, detail::Department>;
using DepartmentIdHasher = utils::TaggedHasher<DepartmentId>;

struct Department {
    std::string name;
};
    
} // namespace domain
