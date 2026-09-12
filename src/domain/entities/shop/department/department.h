#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct Department {};
}  // namespace detail

using DepartmentId = utils::Tagged<uint64_t, detail::Department>;
using DepartmentIdHasher = utils::TaggedHasher<DepartmentId>;

struct Department {
    DepartmentId department_id;
    std::string description;
};

using Departments = std::vector<Department>;

}  // namespace domain
