#pragma once

#include "application/application_manager_interface.h"
#include "infrastructure/token_manager/token_manager.h"
#include "infrastructure/handlers/shop_request_handler/employee_request_handler/employee_request_handler.h"

#include <boost/beast.hpp>
#include <string_view>

namespace infrastructure{

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

/**
 * @brief Обрабатывает запросы с сущностями подразделения
 */
class ShopRequestHandler{
public:
    explicit ShopRequestHandler(
        const application::ApplicationManagerInterface& application_manager
    )
    : employee_request_handler_{application_manager} { }

    template <typename Body, typename Allocator, typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, TokenManager::Payload payload, 
                    TextResponseMaker&& text_response_maker, FileResponseMaker&& file_response_maker, Send&& send){            
        std::string_view target = req.target();        
        target.remove_prefix(API_V1_SHOP.size());

        if (target == EMPLOYEE) {
            
        }
    }
private:
    EmployeeRequestHandler employee_request_handler_;

    constexpr static std::string_view API_V1_SHOP = "/api/v1/shop/"sv;
    constexpr static std::string_view EMPLOYEE = "employee"sv;
    
    constexpr static std::string_view UNAUTHORIZED = "{\"code\":\"unauthorized\", \"message\":\"Bad token\"}"sv;
    constexpr static std::string_view BAD_REQUEST = "{\"code\":\"bad_request\", \"message\":\"Bad request\"}"sv;
    constexpr static std::string_view INVALID_METHOD = "{\"code\":\"invalidMethod\", \"message\":\"Only POST, DELETE, PATCH method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR = "{\"code\": \"server_error\", \"message\": \"Server error\"}"sv;
};

} // namespace infrastructure

