#pragma once

#include <boost/beast.hpp>
#include <string_view>

#include "application_gateway/application_gateway_interface.h"
#include "handlers/shop_request_handler/department_request_handler/department_request_handler.h"
#include "handlers/shop_request_handler/employee_request_handler/employee_request_handler.h"
#include "handlers/shop_request_handler/staff_position_request_handler/staff_position_request_handler.h"
#include "token_manager/token_manager.h"

namespace infrastructure {

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

class ShopRequestHandler {
public:
    explicit ShopRequestHandler(application::ApplicationGatewayInterface& application_gateway) :
        employee_request_handler_{application_gateway}, department_request_handler_{application_gateway},
        staff_position_request_handler_{application_gateway} {}

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req,
                    TokenManager::Payload payload,
                    TextResponseMaker&& text_response_maker,
                    FileResponseMaker&& file_response_maker,
                    Send&& send) {
        std::string_view target = req.target();
        target.remove_prefix(API_V1_SHOP.size());

        if (target.starts_with(EMPLOYEE)) {
            employee_request_handler_(std::move(req),
                                      payload,
                                      text_response_maker,
                                      file_response_maker,
                                      std::forward<decltype(send)>(send));
            return;
        }

        if (target.starts_with(DEPARTMENT)) {
            department_request_handler_(std::move(req),
                                        payload,
                                        text_response_maker,
                                        file_response_maker,
                                        std::forward<decltype(send)>(send));
            return;
        }

        if (target.starts_with(STAFF_POSITION)) {
            staff_position_request_handler_(std::move(req),
                                            payload,
                                            text_response_maker,
                                            file_response_maker,
                                            std::forward<decltype(send)>(send));
            return;
        }
    }

private:
    EmployeeRequestHandler employee_request_handler_;
    DepartmentRequestHandler department_request_handler_;
    StaffPositionRequestHandler staff_position_request_handler_;

private:
    constexpr static std::string_view API_V1_SHOP = "/api/v1/shop/"sv;
    constexpr static std::string_view EMPLOYEE = "employee"sv;
    constexpr static std::string_view DEPARTMENT = "department"sv;
    constexpr static std::string_view STAFF_POSITION = "staff_position"sv;

    constexpr static std::string_view UNAUTHORIZED = "{\"code\":\"unauthorized\", \"message\":\"Bad token\"}"sv;
    constexpr static std::string_view BAD_REQUEST =
        "{\"code\":\"bad_request\", \"message\":\"Bad request from shop_request_handler\"}"sv;
    constexpr static std::string_view INVALID_METHOD =
        "{\"code\":\"invalidMethod\", \"message\":\"Only POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR = "{\"code\": \"server_error\", \"message\": \"Server error\"}"sv;
};

}  // namespace infrastructure
