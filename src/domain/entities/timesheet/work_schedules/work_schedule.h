#pragma once

#include <chrono>
#include <cstdint>

#include "tagged.h"
#include "value_data/types.h"

namespace domain {

namespace detail {
struct WorkScheduleIdTag {};
}  // namespace detail

using WorkScheduleId = utils::Tagged<uint64_t, detail::WorkScheduleIdTag>;
using WorkScheduleIdHasher = utils::TaggedHasher<WorkScheduleId>;

class WorkSchedule {
public:
    WorkSchedule() = default;  // временное решение, удалить
    struct DayData {
        std::string type;
        std::optional<Time> work_start;
        std::optional<Time> work_end;
        std::optional<Time> work_time;
        std::optional<Time> night_work_start;
        std::optional<Time> night_work_end;
        std::optional<Time> night_work_time;
        std::optional<Time> rest_start;
        std::optional<Time> rest_end;

        bool isWorkingDay() const noexcept {
            return work_time.has_value();
        }

        bool isNightWorkingDay() const noexcept {
            return night_work_time.has_value();
        }
    };

    WorkSchedule(size_t cycle_size,
                 const Date& start_cycle_date,
                 bool is_works_on_holidays,
                 const std::vector<DayData>& cycle) :
        cycle_size_{cycle_size}, start_cycle_date_{start_cycle_date}, is_works_on_holidays_{is_works_on_holidays},
        cycle_{std::move(cycle)} {}

    size_t getCycleSize() const noexcept;
    const Date& getStartCycleDate() const noexcept;
    bool isWorksOnHolidays() const noexcept;
    const DayData& getDayDataByDate(std::chrono::year_month_day date) const;
    const DayData& operator[](size_t index) const;

private:
    WorkScheduleId work_schedule_id;
    size_t cycle_size_;
    Date start_cycle_date_;
    bool is_works_on_holidays_;
    std::vector<DayData> cycle_;
};

}  // namespace domain
