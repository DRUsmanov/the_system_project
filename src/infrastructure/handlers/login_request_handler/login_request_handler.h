#pragma once

#include "application/application_manager_interface.h"
#include "infrastructure/json_formater/json_formater.h"
#include "application/dto/user_dto.h"
#include "infrastructure/token_manager/token_manager.h"

#include <boost/beast.hpp>
#include <string_view>
#include <memory>

namespace infrastructure{

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

const std::string LOGIN = "login"s;
const std::string PASSWORD = "password"s;

class LoginRequestHandler{
public:
    explicit LoginRequestHandler(
        const application::ApplicationManagerInterface& application_manager
        , const std::shared_ptr<TokenManager> token_manager)
    : application_manager_{application_manager}
    , token_manager_{token_manager} { }

    template <typename Body, typename Allocator, typename TextResponseMaker, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, TextResponseMaker&& text_response_maker, Send&& send){     
        std::string_view target = req.target();
        target.remove_prefix(API_V1_LOGIN.size());

        if (auto content_type_header_it = req.find(http::field::content_type);
            content_type_header_it == req.end() || content_type_header_it->value() != content_type::APP_JSON || !target.empty()) {
            auto bad_request_response = text_response_maker(http::status::bad_request, BAD_REQUEST, content_type::APP_JSON);
            bad_request_response.set(http::field::cache_control, "no-cache");
            send(std::move(bad_request_response));
            return;
        }
        
        if (auto method = req.method(); method != http::verb::post){
            auto invalid_method_response = text_response_maker(http::status::method_not_allowed, INVALID_METHOD, content_type::APP_JSON);
            invalid_method_response.set(http::field::allow, "POST");
            invalid_method_response.set(http::field::cache_control, "no-cache");
            send(std::move(invalid_method_response));
            return;
        }

        try{
            json::value request_body = ParseString(std::string(req.body));
            const json::object& request_body_as_object = request_body.as_object();

            const std::string login = std::string(request_body_as_object.at(LOGIN).as_string());
            const std::string password = std::string(request_body_as_object.at(PASSWORD).as_string());

            application::UserLoginInputDto user_login_input_dto;
            user_login_input_dto.login = login;
            user_login_input_dto.password = password;

            auto user_login_output_dto = application_manager_.Login(user_login_input_dto);
            
            if (!user_login_output_dto.has_value()) {
                auto unauthorized_response = text_response_maker(http::status::unauthorized, UNAUTHORIZED, content_type::APP_JSON);
                unauthorized_response.set(http::field::cache_control, "no-cache");
                send(std::move(unauthorized_response));
                return;
            }

            auto token = token_manager_->CreateToken(user_login_output_dto->user_id, user_login_output_dto->employee_id );

            if (!token.has_value()){
                auto unauthorized_response = text_response_maker(http::status::unauthorized, UNAUTHORIZED, content_type::APP_JSON);
                unauthorized_response.set(http::field::cache_control, "no-cache");
                send(std::move(unauthorized_response));
                return;
            }

            auto authorized_response = text_response_maker(http::status::accepted, MakeAcceptedAnswer(token), content_type::APP_JSON);
            authorized_response.set(http::field::cache_control, "no-cache");
            send(std::move(authorized_response));
            return;

        }
        catch(const std::exception& ex){
            auto server_error = text_response_maker(http::status::internal_server_error, SERVER_ERROR, content_type::APP_JSON);
            server_error.set(http::field::cache_control, "no-cache");
            send(std::move(server_error));
            return;
        }
    }
private:
    const application::ApplicationManagerInterface& application_manager_;
    const std::shared_ptr<TokenManager> token_manager_;

    static inline const std::string API_V1_LOGIN = "/api/v1/login"s;

    constexpr static std::string_view UNAUTHORIZED = "{\"code\":\"unauthorized\", \"message\":\"Bad login or password\"}"sv;
    constexpr static std::string_view BAD_REQUEST = "{\"code\":\"bad_request\", \"message\":\"Bad request\"}"sv;
    constexpr static std::string_view INVALID_METHOD = "{\"code\":\"invalid_method\", \"message\":\"Only POST method is expected\"}"sv;
    constexpr static std::string_view SERVER_ERROR = "{\"code\": \"server_error\", \"message\": \"Server error\"}"sv;
    
    std::string MakeAcceptedAnswer(const TokenManager::Token& token){
        return "{\"authToken\":\"" + *token + "\"}";
    }

};

} // namespace infrastructure

