#include "handlers/timesheet_request_handler/work_schedule_request_handler/work_schedule_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {

}  // namespace request_keys

namespace response_keys {
constexpr std::string_view STATUS{"status"};
constexpr std::string_view WORK_SCHEDULES{"work_schedules"};
constexpr std::string_view ID{"id"};
constexpr std::string_view DESCRIPTION{"description"};
}  // namespace response_keys

std::string infrastructure::WorkscheduleRequestHandler::makeGetWorkschedulesResponse(
    std::optional<application::GetWorkSchedulesResponseDto> get_workschedules_response_dto) const {
    json::object response;
    if (get_workschedules_response_dto.has_value()) {
        response[response_keys::STATUS] = true;
        json::array workschedules_array;
        for (const auto& workschedule : get_workschedules_response_dto.value().work_schedules) {
            json::object workschedule_as_object;
            workschedule_as_object[response_keys::ID] = workschedule.first;
            workschedule_as_object[response_keys::DESCRIPTION] = workschedule.second;
            workschedules_array.push_back(workschedule_as_object);
        }
        response[response_keys::WORK_SCHEDULES] = workschedules_array;
    } else {
        response[response_keys::STATUS] = false;
    }

    return serializeObject(response);
}
