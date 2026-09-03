file(GLOB_RECURSE INFRASTRUCTURE "*.h" "*.cpp")

add_library(infrastructure STATIC ${INFRASTRUCTURE})

target_include_directories(infrastructure PUBLIC ${SRC_ROOT}/infrastructure)

target_link_libraries(infrastructure PUBLIC
    application
    Boost::boost
    Boost::system
    Boost::filesystem
    Boost::log
    Boost::log_setup
    Boost::url 
    libpqxx::pqxx
    jwt-cpp::jwt-cpp
)
