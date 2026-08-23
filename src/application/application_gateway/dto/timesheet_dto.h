#pragma once

#include <cstdint>

namespace application {

struct GetTimesheetRequestDto {
    uint64_t department_id;
    uint64_t admin_category_id;
    uint64_t year;
    uint64_t month;
};

struct GetTimesheetResponseDto {};

}  // namespace application
