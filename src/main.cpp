// #include "sdk.h"
// #include "json_loader.h"
// #include "request_handler.h"
// #include "logger.h"
// #include "application.h"
// #include "ticker.h"
// #include "extra_data.h"
// #include "loot_generator.h"
// #include "model_serialization.h"
// #include "connection_pool.h"
// #include "game_repository.h"

// #include <boost/asio/io_context.hpp>
// #include <boost/asio/signal_set.hpp>
// #include <iostream>
// #include <thread>
// #include <memory>
// #include <chrono>
// #include <optional>
// #include <random>

// using namespace std::literals;
// namespace net = boost::asio;
// namespace sys = boost::system;

// namespace {

// template <typename Fn>
// void RunWorkers(unsigned n, const Fn& fn) {
//     n = std::max(1u, n);
//     std::vector<std::jthread> workers;
//     workers.reserve(n - 1);
//     while (--n) {
//         workers.emplace_back(fn);
//     }
//     fn();
// }

// double RandomGenerator(){
//     static std::mt19937 gen{std::random_device{}()};
//     static std::uniform_real_distribution<double> distrib(1.0, 1.0);
//     return distrib(gen);
// }

// constexpr const char DB_URL_ENV_NAME[]{"GAME_DB_URL"};

// game_repository::ConnectionConfig GetConfigFromEnv() {
//     game_repository::ConnectionConfig config;
//     if (const auto* url = std::getenv(DB_URL_ENV_NAME)) {
//         config.db_url = url;
//     } else {
//         throw std::runtime_error(DB_URL_ENV_NAME + " environment variable not found"s);
//     }
//     return config;
// }

// }  // namespace

// int main(int argc, const char* argv[]) {
//     try {
//         auto command_line_args_optional = command_line_parser::ParseCommandLine(argc, argv);
//         if (!command_line_args_optional){
//             return EXIT_SUCCESS;
//         }
        
//         auto command_line_args = command_line_args_optional.value();

//         model::Game game;
//         extra_data::ExtraData extra_data;

//         loot_gen::LootGenerator loot_generator;
//         loot_generator.SetRandomGenerator(RandomGenerator);

//         json_loader::LoadConfigData(command_line_args.config_file, game, extra_data, loot_generator);
//         game_repository::ConnectionFactory connection_factory{GetConfigFromEnv()};
//         game_repository::ConnectionPool connection_pool{1, connection_factory};
//         game_repository::GameRepository game_repository{connection_pool};
//         game.SetLootGenerator(std::move(loot_generator));

//         app::Application application(game, command_line_args.randomize_spawn_points, game_repository);
//         serialization::Serializer serializer(game, application, command_line_args);

//         const unsigned num_threads = std::thread::hardware_concurrency();
//         net::io_context ioc(num_threads);
//         auto api_strand = net::make_strand(ioc);

//         logger::InitializeBoostLogger();

//         net::signal_set signals(ioc, SIGINT, SIGTERM);
//         signals.async_wait([&ioc](const sys::error_code& ec, [[maybe_unused]] int signal_number){
//             if(!ec){
//                 logger::LogServerStop();
//                 ioc.stop();
//             }
//         });

//         http_handler::RequestHandler handler{game, command_line_args, application, api_strand, extra_data, serializer};
//         http_handler::LoggingRequestHandler logging_handler(handler);

//         std::vector<ticker::sig::scoped_connection> ticker_connection;
//         if (command_line_args.tick_period.has_value()){
//             auto tick_period = std::chrono::milliseconds{command_line_args.tick_period.value()};
//             auto ticker = std::make_shared<ticker::Ticker>(api_strand, tick_period);
//             ticker_connection.emplace_back(ticker->DoOnTick([&application](std::chrono::milliseconds delta) {application.Tick(delta);}));
//             ticker_connection.emplace_back(ticker->DoOnTick([&serializer](std::chrono::milliseconds delta) {serializer.Tick(delta);}));
//             ticker->Start();
//         }

//         const auto address = net::ip::make_address("0.0.0.0");
//         constexpr net::ip::port_type port = 8080;
//         http_server::ServeHttp(ioc, {address, port}, [&logging_handler](auto&& req, auto&& send, auto&& stream) {
//             logging_handler(std::forward<decltype(req)>(req), std::forward<decltype(send)>(send), std::forward<decltype(stream)>(stream));
//         });

//         logger::LogServerStart(address, port);
//         RunWorkers(std::max(1u, num_threads), [&ioc] {
//             ioc.run();
//         });
//         serializer.SaveState();
//     } catch (const std::exception& ex) {
//         std::cout << ex.what() << std::endl;
//         logger::LogServerStop(ex);
//         return EXIT_FAILURE;
//     }
// }
