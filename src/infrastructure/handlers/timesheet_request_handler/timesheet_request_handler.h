#pragma once

#include <boost/beast.hpp>
#include <string_view>

#include "application_gateway/application_gateway_interface.h"
#include "handlers/timesheet_request_handler/work_schedule_request_handler/work_schedule_request_handler.h"
#include "token_manager/token_manager.h"

namespace infrastructure {

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

class TimesheetRequestHandler {
public:
    explicit TimesheetRequestHandler(application::ApplicationGatewayInterface& application_gateway) :
        work_schedule_request_handler_{application_gateway} {}

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req,
                    TokenManager::Payload payload,
                    TextResponseMaker&& text_response_maker,
                    FileResponseMaker&& file_response_maker,
                    Send&& send) {
        std::string_view target = req.target();
        target.remove_prefix(API_V1_TIMESHEET.size());

        if (target == WORK_SCHEDULE) {
            work_schedule_request_handler_(std::move(req),
                                           payload,
                                           text_response_maker,
                                           file_response_maker,
                                           std::forward<decltype(send)>(send));
            return;
        }
    }

private:
    WorkscheduleRequestHandler work_schedule_request_handler_;

private:
    constexpr static std::string_view API_V1_TIMESHEET = "/api/v1/timesheet/"sv;
    constexpr static std::string_view WORK_SCHEDULE = "work_schedule"sv;

    constexpr static std::string_view UNAUTHORIZED = "{\"code\":\"unauthorized\", \"message\":\"Bad token\"}"sv;
    constexpr static std::string_view BAD_REQUEST =
        "{\"code\":\"bad_request\", \"message\":\"Bad request from timesheet_request_handler\"}"sv;
    constexpr static std::string_view INVALID_METHOD =
        "{\"code\":\"invalidMethod\", \"message\":\"Only POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR = "{\"code\": \"server_error\", \"message\": \"Server error\"}"sv;
};

}  // namespace infrastructure
