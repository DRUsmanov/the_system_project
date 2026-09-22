#include "leave_types_request_handler.h"

#include <string_view>

#include "handlers/timesheet_request_handler/work_schedule_request_handler/work_schedule_request_handler.h"

using namespace infrastructure;

namespace request_keys {

}  // namespace request_keys

namespace response_keys {
constexpr std::string_view STATUS{"status"};
constexpr std::string_view LEAVE_TYPES{"leave_types"};
constexpr std::string_view ID{"id"};
constexpr std::string_view DESCRIPTION{"description"};
}  // namespace response_keys

std::string infrastructure::LeaveTypesRequestHandler::makeLeaveTypesResponse(
    application::GetLeaveTypesResponseDto get_leave_types_response_dto) const {
    json::object response;
    response[response_keys::STATUS] = true;
    json::array leave_types_array;
    for (const auto& leave_type : get_leave_types_response_dto.leave_type_desriptions) {
        json::object leave_type_as_object;
        leave_type_as_object[response_keys::ID] = leave_type.first;
        leave_type_as_object[response_keys::DESCRIPTION] = leave_type.second;
        leave_types_array.push_back(leave_type_as_object);
    }
    response[response_keys::LEAVE_TYPES] = leave_types_array;

    return serializeObject(response);
}
