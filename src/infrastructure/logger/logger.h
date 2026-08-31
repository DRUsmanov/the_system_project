#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <chrono>
#include <exception>
#include <iostream>
#include <optional>
#include <string>

namespace infrastructure {

namespace logging = boost::log;
namespace net = boost::asio;
namespace http = boost::beast::http;
namespace json = boost::json;

void initializeBoostLogger();

template <typename Body, typename Allocator>
void logRequest(http::request<Body, http::basic_fields<Allocator>>& req, const boost::beast::tcp_stream& stream) {
    json::value data = json::object();
    json::object& data_as_object = data.as_object();
    data_as_object["ip"] = stream.socket().remote_endpoint().address().to_string();
    data_as_object["URI"] = std::string(req.target());
    data_as_object["method"] = std::string(req.method_string());
    BOOST_LOG_TRIVIAL(info) << logging::add_value("AdditionalData", data) << "request received";
}

template <typename ResponseType>
void logResponse(const http::response<ResponseType>& response, int request_processing_time) {
    json::value data = json::object();
    json::object& data_as_object = data.as_object();
    data_as_object["response_time"] = request_processing_time;
    data_as_object["code"] = response.result_int();
    if (response.find(http::field::content_type) != response.end()) {
        data_as_object["content_type"] = std::string(response.at(http::field::content_type));
    } else {
        data_as_object["content_type"] = nullptr;
    }
    BOOST_LOG_TRIVIAL(info) << logging::add_value("AdditionalData", data) << "response sent";
}

void logServerStart(const net::ip::address& address, const net::ip::port_type& port);
void logServerStop(const std::optional<std::exception>& excp = std::nullopt);
void logNetError(const boost::system::error_code& err_code, const std::string& where);

}  // namespace infrastructure
