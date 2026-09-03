#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <chrono>
#include <iostream>
// #include <jwt-cpp/jwt.h>
// #include <jwt-cpp/traits/boost-json/defaults.h>
#include <memory>
#include <optional>
#include <random>
#include <thread>

#include "application_gateway/application_gateway.h"
#include "application_manager/application_manager.h"
#include "connection_pool/connection_pool.h"
#include "factories_impl/permission_service_factory_impl/permission_service_factory_impl.h"
#include "factories_impl/shop_service_factory_impl/shop_service_factory.h"
#include "factories_impl/timesheet_service_factory_impl/timesheet_service_factory_impl.h"
#include "factories_impl/uow_factory_impl/uow_factory_impl.h"
#include "factories_impl/user_service_factory_impl/user_service_factory_impl.h"
#include "handlers/file_sender/file_sender.h"
#include "handlers/request_handler/request_handler.h"
#include "http_server/http_server.h"
#include "logger/logger.h"
#include "sdk.h"

using namespace std::literals;
namespace net = boost::asio;
namespace sys = boost::system;

namespace {

template <typename Fn>
void runWorkers(unsigned n, const Fn& fn) {
    n = std::max(1u, n);
    std::vector<std::jthread> workers;
    workers.reserve(n - 1);
    while (--n) {
        workers.emplace_back(fn);
    }
    fn();
}

constexpr const char DB_URL_ENV_NAME[]{"SYSTEM_DATABASE"};

infrastructure::ConnectionConfig getConfigFromEnv() {
    infrastructure::ConnectionConfig config;
    if (const auto* url = std::getenv(DB_URL_ENV_NAME)) {
        config.db_url = url;
    } else {
        throw std::runtime_error(DB_URL_ENV_NAME + " environment variable not found"s);
    }
    return config;
}

}  // namespace

int main(int argc, const char* argv[]) {
    try {
        infrastructure::ConnectionFactory connection_factory{getConfigFromEnv()};
        const unsigned num_threads = std::thread::hardware_concurrency();
        infrastructure::ConnectionPool connection_pool{num_threads, connection_factory};

        infrastructure::UowFactory uow_factory(connection_pool);
        infrastructure::PermissionServiceFactory permission_service_factory;
        infrastructure::UserServiceFactory user_service_factory;
        infrastructure::TimesheetServiceFactory timesheet_service_factory;
        infrastructure::ShopServiceFactory shop_service_factory;

        application::ApplicationManager application_manager{uow_factory,
                                                            permission_service_factory,
                                                            user_service_factory,
                                                            timesheet_service_factory,
                                                            shop_service_factory};

        application::ApplicationGateway application_gateway{application_manager};

        infrastructure::FileSender file_sender{"./"};

        infrastructure::RequestHandler request_handler{application_gateway, file_sender};

        net::io_context ioc(num_threads);
        auto api_strand = net::make_strand(ioc);

        infrastructure::initializeBoostLogger();

        net::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const sys::error_code& ec, [[maybe_unused]] int signal_number) {
            if (!ec) {
                infrastructure::logServerStop();
                ioc.stop();
            }
        });

        infrastructure::LoggingRequestHandler logging_request_handler(request_handler);

        const auto address = net::ip::make_address("0.0.0.0");
        constexpr net::ip::port_type port = 8080;
        infrastructure::serveHttp(ioc,
                                  {address, port},
                                  [&logging_request_handler](auto&& req, auto&& send, auto&& stream) {
                                      logging_request_handler(std::forward<decltype(req)>(req),
                                                              std::forward<decltype(send)>(send),
                                                              std::forward<decltype(stream)>(stream));
                                  });

        infrastructure::logServerStart(address, port);
        runWorkers(std::max(1u, num_threads), [&ioc] {
            ioc.run();
        });
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
        infrastructure::logServerStop(ex);
        return EXIT_FAILURE;
    }
}
