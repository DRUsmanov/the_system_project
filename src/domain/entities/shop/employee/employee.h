#pragma once

#include <cstdint>
#include <optional>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct Employee {};
}  // namespace detail

using EmployeeId = utils::Tagged<uint64_t, detail::Employee>;
using EmployeeIdHasher = utils::TaggedHasher<EmployeeId>;
using EmployeeNumber = uint64_t;

struct Employee {
    EmployeeId employee_id;
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    Date birth_date;
    Date employment_date;
    EmployeeNumber employee_number;
};

}  // namespace domain
