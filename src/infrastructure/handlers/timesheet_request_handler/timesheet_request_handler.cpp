#include "handlers/timesheet_request_handler/timesheet_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {

}  // namespace request_keys

namespace response_keys {
constexpr std::string_view STATUS{"status"};
constexpr std::string_view EMPLOYEE_ID{"employee_id"};
constexpr std::string_view EMPLOYEE_DATA{"employee_data"};
constexpr std::string_view LAST_NAME{"last_name"};
constexpr std::string_view FIRST_NAME{"first_name"};
constexpr std::string_view PATRONYMIC{"patronymic"};
constexpr std::string_view EMPLOYEE_NUMBER{"employee_number"};
constexpr std::string_view EMPLOYEES{"employees"};
constexpr std::string_view DATE{"date"};
constexpr std::string_view DAY_DATA{"employee_data"};
constexpr std::string_view WORK_TIME{"work_time"};
constexpr std::string_view NIGHT_WORK_TIME{"night_work_time"};
constexpr std::string_view LEAVE_TYPE{"leave_type"};
constexpr std::string_view COMMENT{"comment"};
constexpr std::string_view STAFF_POSITION_DESCRIPTION{"staff_position_description"};
constexpr std::string_view WORK_SCHEDULE_DESCRIPTION{"work_schedule_description"};
constexpr std::string_view DAYS_DATA{"days_data"};
}  // namespace response_keys

std::string infrastructure::TimesheetRequestHandler::makeGetDepartmentTimesheetResponse(
    std::optional<application::GetDepartmentTimesheetResponseDto> get_department_timesheet_response_dto) {
    json::object response;
    if (get_department_timesheet_response_dto.has_value()) {
        response[response_keys::STATUS] = true;

        json::array employees_array;
        const auto& employees_info_dto = get_department_timesheet_response_dto.value().employees_info_dto;
        for (const auto& [employee_id, employee_info_dto] : employees_info_dto) {
            json::object employee_data;
            employee_data[response_keys::LAST_NAME] = employee_info_dto.last_name;
            employee_data[response_keys::FIRST_NAME] = employee_info_dto.first_name;
            employee_data[response_keys::PATRONYMIC] = employee_info_dto.patronymic;
            employee_data[response_keys::EMPLOYEE_NUMBER] = employee_info_dto.employee_number;

            json::object employee_object;
            employee_object[response_keys::EMPLOYEE_ID] = employee_id;
            employee_object[response_keys::EMPLOYEE_DATA] = employee_data;

            employees_array.push_back(employee_object);
        }
        response[response_keys::EMPLOYEES] = employees_array;

        json::array employees_day_data_array;
        const auto& employees_day_dat_dto = get_department_timesheet_response_dto.value().employees_day_data_dto;
        for (const auto& [employee_id, employee_days_data_dto] : employees_day_dat_dto) {
            json::array employee_day_data_array;
            for (const auto& [date, employee_day_data] : employee_days_data_dto) {
                json::object day_data_object;
                day_data_object[response_keys::WORK_TIME] = employee_day_data.work_time
                                                                ? json::value(employee_day_data.work_time.value())
                                                                : json::value(nullptr);
                day_data_object[response_keys::NIGHT_WORK_TIME] =
                    employee_day_data.night_work_time ? json::value(employee_day_data.night_work_time.value())
                                                      : json::value(nullptr);
                day_data_object[response_keys::LEAVE_TYPE] = employee_day_data.leave_type
                                                                 ? json::value(employee_day_data.leave_type.value())
                                                                 : json::value(nullptr);
                day_data_object[response_keys::COMMENT] =
                    employee_day_data.comment ? json::value(employee_day_data.comment.value()) : json::value(nullptr);
                day_data_object[response_keys::STAFF_POSITION_DESCRIPTION] =
                    employee_day_data.staff_position_description;
                day_data_object[response_keys::WORK_SCHEDULE_DESCRIPTION] = employee_day_data.work_schedule_description;

                json::object employee_day_data_object;
                employee_day_data_object[response_keys::DATE] = date;
                employee_day_data_object[response_keys::DAY_DATA] = day_data_object;
                employee_day_data_array.push_back(employee_day_data_object);
            }
            json::object employee_days_data_object;
            employee_days_data_object[response_keys::EMPLOYEE_ID] = employee_id;
            employee_days_data_object[response_keys::DAYS_DATA] = employee_day_data_array;
            employees_day_data_array.push_back(employee_days_data_object);
        }
        response[response_keys::DAYS_DATA] = employees_day_data_array;

    } else {
        response[response_keys::STATUS] = false;
    }

    return serializeObject(response);
}

struct EmployeeInfoDto {
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    uint64_t employee_number;
};

struct EmployeeDayDataDto {
    std::optional<std::string> work_time;
    std::optional<std::string> night_work_time;
    std::optional<std::string> leave_type;
    std::optional<std::string> comment;
    std::string staff_position_description;
    std::string work_schedule_description;
};

struct GetDepartmentTimesheetResponseDto {
    std::unordered_map<uint64_t, EmployeeInfoDto> employees_info_dto;
    std::unordered_map<uint64_t, std::unordered_map<std::string, EmployeeDayDataDto>> employees_day_data_dto;
};
