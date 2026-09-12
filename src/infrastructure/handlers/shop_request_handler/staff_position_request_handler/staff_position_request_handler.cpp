#include "staff_position_request_handler.h"

#include <string_view>

using namespace infrastructure;

namespace request_keys {

}  // namespace request_keys

namespace response_keys { namespace get_staff_posiiton {
constexpr std::string_view STATUS{"status"};
constexpr std::string_view DEFAULT_PROFESSION_ID{"default_profession_id"};
constexpr std::string_view ID{"id"};
constexpr std::string_view DESCRIPTION{"description"};
constexpr std::string_view STAFF_POSIITONS{"staff_positions"};
}}  // namespace response_keys::get_staff_posiiton

std::string infrastructure::StaffPositionRequestHandler::makeGetStaffPositionsResponse(
    std::optional<application::GetStaffPositionsResponseDto> get_staff_positions_response_dto) const {
    json::object response;
    if (get_staff_positions_response_dto.has_value()) {
        response[response_keys::get_staff_posiiton::STATUS] = true;
        json::array staff_positions_array;
        for (const auto& staff_position : get_staff_positions_response_dto.value().staff_positions) {
            json::object staff_position_as_object;
            staff_position_as_object[response_keys::get_staff_posiiton::ID] = staff_position.first;
            staff_position_as_object[response_keys::get_staff_posiiton::DESCRIPTION] = staff_position.second;
            staff_positions_array.push_back(staff_position_as_object);
        }
        response[response_keys::get_staff_posiiton::STAFF_POSIITONS] = staff_positions_array;
    } else {
        response[response_keys::get_staff_posiiton::STATUS] = false;
    }

    return serializeObject(response);
}
