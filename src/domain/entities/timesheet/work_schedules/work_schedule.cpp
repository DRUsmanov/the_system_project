#include "entities/timesheet/work_schedules/work_schedule.h"

size_t domain::WorkSchedule::getCycleSize() const noexcept {
    return cycle_size_;
}

const domain::Date& domain::WorkSchedule::getStartCycleDate() const noexcept {
    return start_cycle_date_;
}

bool domain::WorkSchedule::isWorksOnHolidays() const noexcept {
    return is_works_on_holidays_;
}

const domain::WorkSchedule::DayData& domain::WorkSchedule::getDayDataByDate(std::chrono::year_month_day date) const {
    using namespace std::chrono;

    auto day_index = (sys_days{date} - sys_days{start_cycle_date_}).count() % cycle_size_;
    return cycle_.at(day_index);
}

const domain::WorkSchedule::DayData& domain::WorkSchedule::operator[](size_t index) const {
    return cycle_.at(index);
}
