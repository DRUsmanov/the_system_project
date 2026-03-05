#pragma once

#include "../../utils/tagged.h"
#include "../value_data/timesheet_data.h"

#include <optional>

namespace domain {

namespace detail {
    struct Employee{};
} // namespace detail

using EmployeeId = utils::Tagged<int, detail::Employee>;
using EmployeeIdHasher = utils::TaggedHasher<EmployeeId>;

struct EmployeeData {
    std::string last_name;
    std::string first_name;
    std::optional<std::string> patronymic;
    Date birth_date;
    Date employment_date;
    unsigned int employee_number;
};
    
} // namespace domain
