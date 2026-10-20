#include "employee_timesheet_request_handler.h"

using namespace infrastructure;

namespace request_keys {
constexpr std::string_view EMPLOYEE_ID{"employee_id"};
constexpr std::string_view START_DATE{"start_date"};
constexpr std::string_view END_DATE{"end_date"};
constexpr std::string_view WORK_START{"work_start"};
constexpr std::string_view WORK_END{"work_end"};
constexpr std::string_view WORK_TIME{"work_time"};
constexpr std::string_view NIGHT_WORK_START{"night_work_start"};
constexpr std::string_view NIGHT_WORK_END{"night_work_end"};
constexpr std::string_view NIGHT_WORK_TIME{"night_work_time"};
constexpr std::string_view REST_START{"rest_start"};
constexpr std::string_view REST_END{"rest_end"};
constexpr std::string_view COMMENT{"comment"};
}  // namespace request_keys

namespace response_keys {
constexpr std::string_view STATUS{"status"};
}  // namespace response_keys

application::UpdateEmployeeTimesheetDaysDataRequestDto
EmployeeTimesheetRequestHandler::makeUpdateEmployeeDaysDataRequestDto(
    const json::object& request_body_as_object) const {
    application::UpdateEmployeeTimesheetDaysDataRequestDto update_employee_timesheet_request_dto;
    update_employee_timesheet_request_dto.employee_id = request_body_as_object.at(request_keys::EMPLOYEE_ID).as_int64();
    update_employee_timesheet_request_dto.start_date = request_body_as_object.at(request_keys::START_DATE).as_string();
    update_employee_timesheet_request_dto.end_date = request_body_as_object.at(request_keys::END_DATE).as_string();

    if (!request_body_as_object.at(request_keys::WORK_START).is_null()) {
        update_employee_timesheet_request_dto.work_start =
            request_body_as_object.at(request_keys::WORK_START).as_string();
    }
    if (!request_body_as_object.at(request_keys::WORK_END).is_null()) {
        update_employee_timesheet_request_dto.work_end = request_body_as_object.at(request_keys::WORK_END).as_string();
    }
    if (!request_body_as_object.at(request_keys::WORK_TIME).is_null()) {
        update_employee_timesheet_request_dto.work_time =
            request_body_as_object.at(request_keys::WORK_TIME).as_string();
    }
    if (!request_body_as_object.at(request_keys::NIGHT_WORK_START).is_null()) {
        update_employee_timesheet_request_dto.night_work_start =
            request_body_as_object.at(request_keys::NIGHT_WORK_START).as_string();
    }
    if (!request_body_as_object.at(request_keys::NIGHT_WORK_END).is_null()) {
        update_employee_timesheet_request_dto.night_work_end =
            request_body_as_object.at(request_keys::NIGHT_WORK_END).as_string();
    }
    if (!request_body_as_object.at(request_keys::NIGHT_WORK_TIME).is_null()) {
        update_employee_timesheet_request_dto.night_work_time =
            request_body_as_object.at(request_keys::NIGHT_WORK_TIME).as_string();
    }
    if (!request_body_as_object.at(request_keys::REST_START).is_null()) {
        update_employee_timesheet_request_dto.rest_start =
            request_body_as_object.at(request_keys::REST_START).as_string();
    }
    if (!request_body_as_object.at(request_keys::REST_END).is_null()) {
        update_employee_timesheet_request_dto.rest_end = request_body_as_object.at(request_keys::REST_END).as_string();
    }
    if (!request_body_as_object.at(request_keys::COMMENT).is_null()) {
        update_employee_timesheet_request_dto.comment = request_body_as_object.at(request_keys::COMMENT).as_string();
    }

    return update_employee_timesheet_request_dto;
}

std::string EmployeeTimesheetRequestHandler::makeUpdateEmployeeTimesheetDaysDataResponse(
    bool is_employee_timesheet_days_data_updated) const {
    json::object response;
    response[response_keys::STATUS] = is_employee_timesheet_days_data_updated;
    return serializeObject(response);
}
