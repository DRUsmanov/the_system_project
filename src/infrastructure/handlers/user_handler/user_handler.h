#pragma once

#include "application/services/user_service/user_service_interface.h"
#include "infrastructure/json_formater/json_formater.h"

#include <boost/beast.hpp>
#include <string_view>

namespace infrastructure{

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

const std::string LOGIN = "login"s;
const std::string PASSWORD = "password"s;

class UserHandler{
public:
    explicit UserHandler(const application::UserServiceInterface& user_service)
    : user_service_{user_service}{ }

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





            std::string user_name = std::string(request_as_object.at(USER_NAME).as_string());
            if (user_name.empty()){
                auto invalid_argument_response = text_response_maker(http::status::bad_request, INVALID_ARGUMENT, content_type::APP_JSON);
                invalid_argument_response.set(http::field::cache_control, "no-cache");
                send(std::move(invalid_argument_response));
                return;
            }

            std::string map_id_as_str = std::string(request_as_object.at(MAP_ID).as_string());
            try{
                application::PlayerAuthInfo player_auth_info = application_.JoinGameOnMap(user_name, map_id_as_str);
                std::string answer = MakeAuthAnswer(player_auth_info);
                auto correct_response = text_response_maker(http::status::ok, answer, content_type::APP_JSON);
                correct_response.set(http::field::cache_control, "no-cache");
                send(std::move(correct_response));
                return;
            }
            catch(const std::invalid_argument& ex){
                auto map_not_found_response = text_response_maker(http::status::not_found, MAP_NOT_FOUND, content_type::APP_JSON);
                map_not_found_response.set(http::field::cache_control, "no-cache");
                send(std::move(map_not_found_response));
                return;
            }
        }
        catch(const std::exception& ex){
            auto invalid_parsing_response = text_response_maker(http::status::bad_request, INVALID_PARSING, content_type::APP_JSON);
            invalid_parsing_response.set(http::field::cache_control, "no-cache");
            send(std::move(invalid_parsing_response));
            return;
        }
    }
private:
    const application::UserServiceInterface& user_service_;

    static inline const std::string API_V1_LOGIN = "api/v1/login"s;

    constexpr static std::string_view BAD_REQUEST = "{\"code\":\"badRequest\", \"message\":\"Bad request\"}"sv;
    constexpr static std::string_view INVALID_METHOD = "{\"code\":\"invalidMethod\", \"message\":\"Only POST method is expected\"}"sv;
    constexpr static std::string_view INVALID_PARSING = "{\"code\": \"invalidArgument\", \"message\": \"Join game request parse error\"}"sv;
    constexpr static std::string_view INVALID_ARGUMENT = "{\"code\": \"invalidArgument\", \"message\": \"Invalid name\"}"sv;
    constexpr static std::string_view MAP_NOT_FOUND = "{\"code\": \"mapNotFound\", \"message\": \"Map not found\"}"sv;
    // std::string MakeAuthAnswer(const app::PlayerAuthInfo& player_auth_info){
    //     return "{\"authToken\":\"" + *(player_auth_info.first) + "\",\"playerId\":" + std::to_string(*(player_auth_info.second)) + "}";
    // }

};

} // namespace infrastructure

