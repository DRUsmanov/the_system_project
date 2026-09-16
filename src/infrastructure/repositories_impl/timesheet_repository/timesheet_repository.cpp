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
constexpr std::string IS_WORKING_ON_HOLIDAYS{"is_working_on_holidays"};

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

namespace timesheet_keys {
constexpr std::string EMPLOYEE_ID = "employee_id";
constexpr std::string DEPARTMENT_ID = "department_id";
constexpr std::string STAFF_POSITION_ID = "staff_position_id";
constexpr std::string DATE = "date";
constexpr std::string WORK_START = "work_start";
constexpr std::string WORK_END = "work_end";
constexpr std::string WORK_TIME = "work_time";
constexpr std::string NIGHT_WORK_START = "night_work_start";
constexpr std::string NIGHT_WORK_END = "night_work_end";
constexpr std::string NIGHT_WORK_TIME = "night_work_time";
constexpr std::string REST_START = "rest_start";
constexpr std::string REST_END = "rest_end";
constexpr std::string LEAVE_TYPE = "leave_type";
constexpr std::string ADMIN_CATEGORY_ID = "admin_category_id";
constexpr std::string ADMIN_EMPLOYEE_ID = "admin_employee_id";
constexpr std::string COMMENT = "comment";
}  // namespace timesheet_keys

namespace {

domain::WorkSchedule makeWorkScheduleFromJsonObject(domain::WorkScheduleId work_schedule_id,
                                                    json::object& work_schedule_as_object,
                                                    std::string description) {
    utils::logFunctionStart(utils::FUNCTION_INFO);

    size_t cycle_size = work_schedule_as_object.at(work_schedule_keys::CYCLE_SIZE).as_int64();
    domain::Date start_cycle_date =
        domain::dateFromString(work_schedule_as_object.at(work_schedule_keys::START_SYCLE_DATE).as_string());
    bool is_works_on_holidays = work_schedule_as_object.at(work_schedule_keys::IS_WORKING_ON_HOLIDAYS).as_bool();
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
        if (!night_work_time.is_null()) {
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

    return {work_schedule_id, cycle_size, start_cycle_date, is_works_on_holidays, cycle, description};
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

domain::Timesheet::DayData makeDayDataFromRow(const pqxx::row& row) {
    domain::Timesheet::DayData day_data;

    const auto& department_field = row.at(timesheet_keys::DEPARTMENT_ID);
    if (!department_field.is_null()) {
        day_data.department_id = domain::DepartmentId{department_field.as<uint64_t>()};
    }

    const auto& staff_position_field = row.at(timesheet_keys::STAFF_POSITION_ID);
    if (!staff_position_field.is_null()) {
        day_data.staff_position_id = domain::StaffPositionId{staff_position_field.as<uint64_t>()};
    }

    const auto& work_start_field = row.at(timesheet_keys::WORK_START);
    if (!work_start_field.is_null()) {
        day_data.work_start = domain::timeFromString(work_start_field.as<std::string>());
    }

    const auto& work_end_field = row.at(timesheet_keys::WORK_END);
    if (!work_end_field.is_null()) {
        day_data.work_end = domain::timeFromString(work_end_field.as<std::string>());
    }

    const auto& work_time_field = row.at(timesheet_keys::WORK_TIME);
    if (!work_time_field.is_null()) {
        day_data.work_time = domain::timeFromString(work_time_field.as<std::string>());
    }

    const auto& night_work_start_field = row.at(timesheet_keys::NIGHT_WORK_START);
    if (!night_work_start_field.is_null()) {
        day_data.night_work_start = domain::timeFromString(night_work_start_field.as<std::string>());
    }

    const auto& night_work_end_field = row.at(timesheet_keys::NIGHT_WORK_END);
    if (!night_work_end_field.is_null()) {
        day_data.night_work_end = domain::timeFromString(night_work_end_field.as<std::string>());
    }

    const auto& night_work_time_field = row.at(timesheet_keys::NIGHT_WORK_TIME);
    if (!night_work_time_field.is_null()) {
        day_data.night_work_time = domain::timeFromString(night_work_time_field.as<std::string>());
    }

    const auto& rest_start_field = row.at(timesheet_keys::REST_START);
    if (!rest_start_field.is_null()) {
        day_data.rest_start = domain::timeFromString(rest_start_field.as<std::string>());
    }

    const auto& rest_end_field = row.at(timesheet_keys::REST_END);
    if (!rest_end_field.is_null()) {
        day_data.rest_end = domain::timeFromString(rest_end_field.as<std::string>());
    }

    const auto& leave_type_field = row.at(timesheet_keys::LEAVE_TYPE);
    if (!leave_type_field.is_null()) {
        day_data.leave_type = domain::LeaveType{leave_type_field.as<uint64_t>()};
    }

    const auto& comment_field = row.at(timesheet_keys::COMMENT);
    if (!comment_field.is_null()) {
        day_data.comment = comment_field.as<std::string>();
    }

    return day_data;
}

}  // namespace

std::optional<domain::WorkSchedule> TimesheetRepository::downloadWorkScheduleById(
    domain::WorkScheduleId work_schedule_id) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_WORK_SCHEDULE, *work_schedule_id);

    if (result.size() != 1) {
        return std::nullopt;
    }

    auto description = result.at(0).at(tables::work_schedules::DESCRIPTION).as<std::string>();
    auto work_chedule_as_string = result.at(0).at(tables::work_schedules::WORK_SCHEDULE).as<std::string>();
    auto work_schedule_as_object = parseString(work_chedule_as_string);

    return makeWorkScheduleFromJsonObject(work_schedule_id, work_schedule_as_object, description);
}

std::optional<domain::WorkSchedules> TimesheetRepository::downloadWorkSchedules() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_WORK_SCHEDULES);

    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::WorkSchedules work_schedules;

    for (const auto& row : result) {
        domain::WorkScheduleId work_schedule_id{row.at(tables::work_schedules::ID).as<uint64_t>()};
        auto description = row.at(tables::work_schedules::DESCRIPTION).as<std::string>();
        auto work_schedule_as_string = row.at(tables::work_schedules::WORK_SCHEDULE).as<std::string>();
        auto work_schedule_as_object = parseString(work_schedule_as_string);
        auto work_schedule = makeWorkScheduleFromJsonObject(work_schedule_id, work_schedule_as_object, description);

        work_schedules.push_back(work_schedule);
    }

    return work_schedules;
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

std::optional<domain::EmployeeVacations> TimesheetRepository::downloadVacationsByYear(std::chrono::year year) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    return domain::EmployeeVacations();
    // TODO
}

std::optional<domain::EmployeeVacations> TimesheetRepository::downloadVacationsByEmployeeId(
    domain::EmployeeId employee_id) const {
    return domain::EmployeeVacations();
    // TODO
}

std::optional<domain::EmployeeVacations> TimesheetRepository::downloadVacationsByEmployeeIdAndYear(
    domain::EmployeeId employee_id,
    std::chrono::year year) const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_EMPLOYEE_VACATIONS_BY_YEAR, *employee_id, static_cast<int>(year));

    if (result.size() != 0) {
        return std::nullopt;
    }

    domain::EmployeeVacations employee_vacations;

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
    uint64_t year = static_cast<int>(year_month.year());
    uint64_t month = static_cast<uint>(year_month.month());
    auto result =
        uow_->execParams(query::DOWNLOAD_DEPARTMENT_TIMESHEET, year, month, *department_id, *admin_category_id);

    if (result.size() == 0) {
        return std::nullopt;
    }

    domain::Timesheet timesheet;

    for (const auto& row : result) {
        auto employee_id = domain::EmployeeId{row.at(timesheet_keys::EMPLOYEE_ID).as<uint64_t>()};
        auto date = domain::dateFromString(row.at(timesheet_keys::DATE).as<std::string>());
        auto admin_category_id = domain::AdminCategoryId{row.at(timesheet_keys::ADMIN_CATEGORY_ID).as<uint64_t>()};
        auto day_data = makeDayDataFromRow(row);
        timesheet.addEmployeeDayData(employee_id, date, admin_category_id, day_data);
    }

    return timesheet;
}

std::optional<domain::Date> infrastructure::TimesheetRepository::downloadMaxDate() const {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto result = uow_->execParams(query::DOWNLOAD_MAX_TIMESHEET_DATE);

    if (result.at(0).at(0).is_null()) {
        return std::nullopt;
    }

    return domain::dateFromString(result.at(0).at(0).as<std::string>());
}

bool infrastructure::TimesheetRepository::deleteEmployeeTimesheetFromDate(const domain::EmployeeId& employee_id,
                                                                          const domain::Date& date) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    auto ymd = std::chrono::year_month_day{date};
    int64_t year = static_cast<int>(ymd.year());
    uint64_t month = static_cast<uint>(ymd.month());
    uint64_t day = static_cast<uint>(ymd.day());
    auto result = uow_->execParams(query::DELETE_EMPLOYEE_TIMESHEET, *employee_id, year, month, day);

    if (result.affected_rows() == 0) {
        return false;
    }

    return true;
}

bool TimesheetRepository::uploadTimesheet(const domain::Timesheet& timesheet,
                                          domain::AdminCategoryId admin_category_id,
                                          std::optional<domain::EmployeeId> admin_employee_id) {
    utils::logFunctionStart(utils::FUNCTION_INFO);
    for (auto it = timesheet.begin(); it != timesheet.end(); ++it) {
        auto employee_id = it->first;
        auto days_data = it->second;

        for (const auto& [date, day_data] : days_data) {
            auto prepared_day_data_to_insert = prepareDayDataToInsert(day_data, admin_employee_id);

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
