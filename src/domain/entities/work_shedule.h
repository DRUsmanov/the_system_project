#pragma once

#include "../../utils/tagged.h"
#include "../value_data/timesheet_data.h"

#include <optional>

namespace domain {

namespace detail {
    struct WorkSchedule{};
} // namespace detail

using WorkScheduleId = utils::Tagged<int, detail::WorkSchedule>;
using WorkScheduleIdHasher = utils::TaggedHasher<WorkScheduleId>;

struct WorkScheduleDayData {
    std::string type;
    std::optional<Time> work_start;
    std::optional<Time> work_end;
    std::optional<Time> work_time;
    std::optional<Time> night_work_start;
    std::optional<Time> night_work_end;
    std::optional<Time> night_work_time;
    std::optional<Time> rest_start;
    std::optional<Time> rest_end;

    bool IsWorkingDay() {
        return work_time.has_value();
    }
};
    
} // namespace domain


