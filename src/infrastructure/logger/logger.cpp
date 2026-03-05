#include "logger.h"

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/date_time.hpp>
#include <boost/json.hpp>
#include <variant>

namespace logger{
    using namespace std::literals;

    BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
    BOOST_LOG_ATTRIBUTE_KEYWORD(additional_data, "AdditionalData", json::value)

    namespace logging = boost::log;
    namespace keywords = logging::keywords;
    namespace sinks = boost::log::sinks;

    void ConsoleLogFormatter(logging::record_view const& rec, logging::formatting_ostream& strm){
        auto ts = *rec[timestamp];
        strm << "{\"timestamp\":\"" << to_iso_extended_string(ts) << "\",";

        auto add_data_as_json_object = (*rec[additional_data]).as_object();
        strm << "\"data\":" << json::serialize(add_data_as_json_object) << ",";

        strm << "\"message\":\"" << rec[logging::expressions::smessage] << "\"}"; 
    }

    void InitializeBoostLogger(){
        logging::add_common_attributes();

        logging::core::get()->set_filter(
            logging::trivial::severity >= logging::trivial::info
        );

        logging::add_console_log(
            std::cout,
            keywords::format = &ConsoleLogFormatter,
            keywords::auto_flush = true
        );
    }

    void LogServerStart(const net::ip::address& address, const net::ip::port_type& port){
        json::value data = json::object();
        json::object& data_as_object = data.as_object();
        data_as_object["port"] = port;
        data_as_object["address"] = address.to_string();
        BOOST_LOG_TRIVIAL(info) << logging::add_value(additional_data, data) << "server started";
    }

    void LogServerStop(const std::optional<std::exception>& excp){
        json::value data = json::object();
        json::object& data_as_object = data.as_object();
        if (excp.has_value()){
            data_as_object["code"] = EXIT_FAILURE;
            data_as_object["exception"] = excp.value().what();
        }
        else{
            data_as_object["code"] = EXIT_SUCCESS;
        }
        BOOST_LOG_TRIVIAL(info) << logging::add_value(additional_data, data) << "server exited";
    }

    void LogNetError(const boost::system::error_code& err_code, const std::string& where){
        json::value data = json::object();
        json::object& data_as_object = data.as_object();
        data_as_object["code"] = err_code.value();
        data_as_object["text"] = err_code.message();
        data_as_object["where"] = where;
        BOOST_LOG_TRIVIAL(info) << logging::add_value(additional_data, data) << "error";
    }



} // namespace logger