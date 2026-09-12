#pragma once

#include <cstdint>
#include <vector>

namespace application {

// ======================================================================
// GET WORK SCHEDULE
// ======================================================================

struct GetWorkSchedulesResponseDto {
    std::vector<std::pair<uint64_t, std::string>> work_schedules;
};

}  // namespace application
