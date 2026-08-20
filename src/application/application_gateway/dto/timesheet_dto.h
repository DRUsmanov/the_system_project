#pragma once

#include <cstdint>

namespace application {

struct GetTimesheetInputDto {
    uint64_t department_id;
    uint64_t admin_category_id;
    uint64_t year;
    uint64_t month;
};

struct TimesheetOutputDto {};

}  // namespace application
