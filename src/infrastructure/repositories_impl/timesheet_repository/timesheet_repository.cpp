#include "repositories_impl/timesheet_repository/timesheet_repository.h"

#include <string>

#include "connection_pool/querys.h"
#include "json_formater/json_formater.h"
#include "logger.h"

using namespace infrastructure;

namespace work_schedule_keys {
constexpr std::string CYCLE_SIZE{"cycle_size"};
constexpr std::string CYCLE{"cycle"};
constexpr std::string START_SYCLE_DATE{"start_cycle_date"};
constexpr std::string IS_WORKS_ON_HOLIDAYS{"is_works_on_holidays"};

namespace cycle_keys {
constexpr std::string TYPE{"type"};
constexpr std::string WORK_START{"work_start"};
constexpr std::string WORK_END{"work_end"};
constexpr std::string WORK_TIME{"work_time"};
constexpr std::string NIGHT_WORK_START{"night_work_start"};
constexpr std::string NIGHT_WORK_END{"night_work_end"};
constexpr std::string NIGHT_WORK_TIME{"night_work_time"};
constexpr std::string REST_START{"rest_start"};
constexpr std::string REST_END{"rest_end"};
}  // namespace cycle_keys
}  // namespace work_schedule_keys

namespace {

domain::WorkSchedule makeWorkScheduleFromJsonObject(const json::object& work_schedule_as_object) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    size_t cycle_size = work_schedule_as_object.at(work_schedule_keys::CYCLE_SIZE).as_int64();
    domain::Date start_cycle_date =
        domain::dateFromString(work_schedule_as_object.at(work_schedule_keys::START_SYCLE_DATE).as_string());
    bool is_works_on_holidays = work_schedule_as_object.at(work_schedule_keys::IS_WORKS_ON_HOLIDAYS).as_bool();

    auto cycle_as_array = work_schedule_as_object.at(work_schedule_keys::CYCLE).as_array();
    std::vector<domain::WorkSchedule::DayData> cycle;
    cycle.reserve(cycle_size);

    for (const auto& day_data_as_value : cycle_as_array) {
        auto day_data_as_object = day_data_as_value.as_object();

        domain::WorkSchedule::DayData day_data;

        day_data.type = day_data_as_object.at(work_schedule_keys::cycle_keys::TYPE).as_string();

        auto work_start = day_data_as_object.at(work_schedule_keys::cycle_keys::WORK_START);
        if (!work_start.is_null()) {
            day_data.work_start = domain::timeFromString(work_start.as_string());
        }

        auto work_end = day_data_as_object.at(work_schedule_keys::cycle_keys::WORK_END);
        if (!work_end.is_null()) {
            day_data.work_end = domain::timeFromString(work_end.as_string());
        }

        auto work_time = day_data_as_object.at(work_schedule_keys::cycle_keys::WORK_TIME);
        if (!work_time.is_null()) {
            day_data.work_time = domain::timeFromString(work_time.as_string());
        }

        auto night_work_start = day_data_as_object.at(work_schedule_keys::cycle_keys::NIGHT_WORK_START);
        if (!night_work_start.is_null()) {
            day_data.night_work_start = domain::timeFromString(night_work_start.as_string());
        }

        auto night_work_end = day_data_as_object.at(work_schedule_keys::cycle_keys::NIGHT_WORK_END);
        if (!night_work_end.is_null()) {
            day_data.night_work_end = domain::timeFromString(night_work_end.as_string());
        }

        auto night_work_time = day_data_as_object.at(work_schedule_keys::cycle_keys::NIGHT_WORK_TIME);
        if (!night_work_end.is_null()) {
            day_data.night_work_time = domain::timeFromString(night_work_time.as_string());
        }

        auto rest_start = day_data_as_object.at(work_schedule_keys::cycle_keys::REST_START);
        if (!rest_start.is_null()) {
            day_data.rest_start = domain::timeFromString(rest_start.as_string());
        }

        auto rest_end = day_data_as_object.at(work_schedule_keys::cycle_keys::REST_END);
        if (!rest_end.is_null()) {
            day_data.rest_end = domain::timeFromString(rest_end.as_string());
        }

        cycle.push_back(day_data);
    }

    return {cycle_size, start_cycle_date, is_works_on_holidays, cycle};
}

struct PreparedDayDataToInsert {
    uint64_t department_id;
    uint64_t staff_position_id;
    uint64_t work_schedule_id;

    std::optional<std::string> work_start;
    std::optional<std::string> work_end;
    std::optional<std::string> work_time;
    std::optional<std::string> night_work_start;
    std::optional<std::string> night_work_end;
    std::optional<std::string> night_work_time;
    std::optional<std::string> rest_start;
    std::optional<std::string> rest_end;

    std::optional<uint64_t> leave_type;
    std::optional<std::string> comment;

    std::optional<uint64_t> admin_employee_id;
};

PreparedDayDataToInsert prepareDayDataToInsert(const domain::Timesheet::DayData& day_data,
                                               std::optional<domain::EmployeeId> admin_employee_id) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    PreparedDayDataToInsert prepared_day_data_to_insert;
    prepared_day_data_to_insert.department_id = *day_data.department_id;
    prepared_day_data_to_insert.staff_position_id = *day_data.staff_position_id;
    prepared_day_data_to_insert.work_schedule_id = *day_data.work_schedule_id;

    if (day_data.work_start.has_value()) {
        prepared_day_data_to_insert.work_start = domain::timeToString(day_data.work_start.value());
    }

    if (day_data.work_end.has_value()) {
        prepared_day_data_to_insert.work_end = domain::timeToString(day_data.work_end.value());
    }

    if (day_data.work_time.has_value()) {
        prepared_day_data_to_insert.work_time = domain::timeToString(day_data.work_time.value());
    }

    if (day_data.night_work_start.has_value()) {
        prepared_day_data_to_insert.night_work_start = domain::timeToString(day_data.night_work_start.value());
    }

    if (day_data.night_work_end.has_value()) {
        prepared_day_data_to_insert.night_work_end = domain::timeToString(day_data.night_work_end.value());
    }

    if (day_data.night_work_time.has_value()) {
        prepared_day_data_to_insert.night_work_time = domain::timeToString(day_data.night_work_time.value());
    }

    if (day_data.rest_start.has_value()) {
        prepared_day_data_to_insert.rest_start = domain::timeToString(day_data.rest_start.value());
    }

    if (day_data.rest_end.has_value()) {
        prepared_day_data_to_insert.rest_end = domain::timeToString(day_data.rest_end.value());
    }

    if (day_data.leave_type.has_value()) {
        prepared_day_data_to_insert.leave_type = static_cast<uint64_t>(day_data.leave_type.value());
    }

    if (admin_employee_id.has_value()) {
        prepared_day_data_to_insert.admin_employee_id = *admin_employee_id.value();
    }

    prepared_day_data_to_insert.comment = day_data.comment;

    return prepared_day_data_to_insert;
}

}  // namespace

std::optional<domain::WorkSchedule> TimesheetRepository::downloadWorkScheduleById(
    domain::WorkScheduleId work_schedule_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_WORK_SCHEDULE, *work_schedule_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    auto work_chedule_as_string = result.at(0).at(tables::work_schedules::WORK_SCHEDULE).as<std::string>();
    auto work_schedule_as_object = parseString(work_chedule_as_string);

    return makeWorkScheduleFromJsonObject(work_schedule_as_object);
}

std::optional<domain::PreHolidays> TimesheetRepository::downloadPreHolidaysByYear(std::chrono::year year) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_PRE_HOLIDAYS_BY_YEAR, static_cast<int>(year));

    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::PreHolidays pre_holidays;

    for (const auto& row : result) {
        auto date = domain::dateFromString(row.at(tables::pre_holidays::DATE).as<std::string>());
        pre_holidays.insert(date);
    }

    return pre_holidays;
}

std::optional<domain::Holidays> TimesheetRepository::downloadHolidaysByYear(std::chrono::year year) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_HOLIDAYS_BY_YEAR, static_cast<int>(year));

    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::Holidays holidays;

    for (const auto& row : result) {
        auto date = domain::dateFromString(row.at(tables::holidays::DATE).as<std::string>());
        holidays.insert(date);
    }

    return holidays;
}

std::optional<domain::ExtraHolidays> TimesheetRepository::downloadExtraHolidaysByYear(std::chrono::year year) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_EXTRA_HOLIDAYS_BY_YEAR, static_cast<int>(year));

    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::ExtraHolidays extra_holidays;

    for (const auto& row : result) {
        auto date = domain::dateFromString(row.at(tables::extra_holidays::DATE).as<std::string>());
        extra_holidays.insert(date);
    }

    return extra_holidays;
}

std::optional<domain::Vacations> TimesheetRepository::downloadVacationsByYear(std::chrono::year year) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return domain::Vacations();
    // TODO
}

std::optional<domain::Vacations> TimesheetRepository::downloadVacationsByEmployeeId(
    domain::EmployeeId employee_id) const {
    return domain::Vacations();
    // TODO
}

std::optional<domain::Vacations> TimesheetRepository::downloadVacationsByEmployeeIdAndYear(
    domain::EmployeeId employee_id,
    std::chrono::year year) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_EMPLOYEE_VACATIONS_BY_YEAR, *employee_id, static_cast<int>(year));

    if (result.size() != 0) {
        return std::nullopt;
    }

    domain::Vacations employee_vacations;

    for (const auto& row : result) {
        domain::EmployeeId emlpoyee_id{row.at(tables::vacations::EMPLOYEE_ID).as<uint64_t>()};
        domain::VacationId vacation_id{row.at(tables::vacations::ID).as<uint64_t>()};
        auto start_date = domain::dateFromString(row.at(tables::vacations::START_DATE).as<std::string>());
        auto end_date = domain::dateFromString(row.at(tables::vacations::END_DATE).as<std::string>());

        domain::Vacation employee_vacation;
        employee_vacation.vacation_id = vacation_id;
        employee_vacation.start = start_date;
        employee_vacation.end = end_date;

        employee_vacations[emlpoyee_id].push_back(employee_vacation);
    }

    return employee_vacations;
}

std::optional<domain::AdminCategoryId> TimesheetRepository::downloadSystemAdministratorId() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_SYSTEM_ADMINISTRATOR_ID);

    if (result.size() != 1) {
        return std::nullopt;
    }

    return domain::AdminCategoryId{result.at(0).at(tables::admin_categorys::ID).as<uint64_t>()};
}

std::optional<domain::Timesheet> TimesheetRepository::downloadDepartmentTimesheet(
    domain::DepartmentId department_id,
    domain::AdminCategoryId admin_category_id,
    std::chrono::year_month year_month) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return std::optional<domain::Timesheet>();

    // TODO
}

bool TimesheetRepository::uploadTimesheet(const domain::Timesheet& timesheet,
                                          domain::AdminCategoryId admin_category_id,
                                          std::optional<domain::EmployeeId> admin_employee_id) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    for (auto it = timesheet.begin(); it != timesheet.end(); ++it) {
        auto employee_id = it->first;
        auto days_data = it->second;

        for (const auto& day_data : days_data) {
            auto date = day_data.first.date;
            auto admin_category_id = day_data.first.admin_category_id;
            const auto& data = day_data.second;

            auto prepared_day_data_to_insert = prepareDayDataToInsert(data, admin_employee_id);

            auto result = uow_->execParams(query::UPLOAD_TIMESHEET,
                                           *employee_id,
                                           prepared_day_data_to_insert.department_id,
                                           prepared_day_data_to_insert.staff_position_id,
                                           domain::dateToString(date),
                                           prepared_day_data_to_insert.work_start,
                                           prepared_day_data_to_insert.work_end,
                                           prepared_day_data_to_insert.work_time,
                                           prepared_day_data_to_insert.night_work_start,
                                           prepared_day_data_to_insert.night_work_end,
                                           prepared_day_data_to_insert.night_work_time,
                                           prepared_day_data_to_insert.rest_start,
                                           prepared_day_data_to_insert.rest_end,
                                           prepared_day_data_to_insert.leave_type,
                                           *admin_category_id,
                                           prepared_day_data_to_insert.admin_employee_id,
                                           prepared_day_data_to_insert.comment);

            if (result.size() != 1) {
                return false;
            }
        }
    }

    return true;
}
