#include "work_schedule.h"

size_t domain::WorkSchedule::GetCycleSize() const noexcept {
    return cycle_size_;
}

const domain::Date& domain::WorkSchedule::GetStartCycleDate() const noexcept {
    return start_cycle_date_;
}

bool domain::WorkSchedule::IsWorksOnHolidays() const noexcept {
    return is_works_on_holidays_;
}

const domain::WorkSchedule::DayData& domain::WorkSchedule::operator[](size_t index) const {
    return cycle_.at(index);
}
