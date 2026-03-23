#pragma once

#include "infrastructure/handlers/login_handler/login_handler.h"
#include "../../logger/logger.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <chrono>
#include <variant>

namespace infrastructure {

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
using namespace std::literals;

using StringRequest = http::request<http::string_body>;
using StringResponse = http::response<http::string_body>;
using FileResponse = http::response<http::file_body>;
using Response = std::variant<std::monostate, StringResponse, FileResponse>;

template <typename SomeRequestHandler>
class LoggingRequestHandler{
public:
    LoggingRequestHandler(SomeRequestHandler& handler)
    : handler_{handler}{ }

    template <typename Body, typename Allocator, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send, const beast::tcp_stream& stream){
        logger::LogRequest(req, stream);

        auto request_processing_start_time = std::chrono::steady_clock::now();
        handler_(std::move(req), [send, request_processing_start_time](auto&& response){
            auto request_processing_end_time = std::chrono::steady_clock::now();
            auto request_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(request_processing_end_time - request_processing_start_time);
            logger::LogResponse(response, request_processing_time.count());
            send(std::move(response));
        });
    }
private:
    SomeRequestHandler& handler_;
};

class RequestHandler {
public:
    using Strand = net::strand<net::io_context::executor_type>;

    explicit RequestHandler(
        LoginHandler& login_handler
    )
        : login_handler_{login_handler} {
    }

    RequestHandler(const RequestHandler&) = delete;
    RequestHandler& operator=(const RequestHandler&) = delete;

    template <typename Body, typename Allocator, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        const auto text_response_maker = [this, version = req.version(), keep_alive = req.keep_alive()]
        (http::status status, std::string_view text, std::string_view content_type = content_type::APP_JSON){
            return MakeStringResponse(status, text, version, keep_alive, content_type);
        };

        const auto file_response_maker = [this, version = req.version(), keep_alive = req.keep_alive()]
        (http::status status, http::file_body::value_type&& file, std::string_view content_type){
            return MakeFileResponse(status, std::move(file), version, keep_alive, content_type);
        };

        std::string prepared_target = PrepareTarget(req.target());
        req.target(prepared_target);

        if (prepared_target.starts_with(API_V1_LOGIN)){
            login_handler_(std::move(req), text_response_maker, std::forward<decltype(send)>(send));
        }
        else{
            // TODO
        }
    }

private:
    std::string PrepareTarget(std::string_view target);

    StringResponse MakeStringResponse(http::status status, std::string_view body, unsigned http_version,
        bool keep_alive, std::string_view content_type);
    FileResponse MakeFileResponse(http::status status, http::file_body::value_type&& file, unsigned http_version,
        bool keep_alive, std::string_view content_type);

    LoginHandler& login_handler_;

    static inline const std::string API_V1_LOGIN = "api/v1/login"s;
};

}  // namespace infrastructure
