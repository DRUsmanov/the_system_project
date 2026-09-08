file(GLOB_RECURSE UTILS "*.cpp")

add_library(utils STATIC ${UTILS})

target_link_libraries(utils PUBLIC
    Boost::log
    Boost::log_setup)

target_include_directories(utils PUBLIC ${SRC_ROOT}/utils)
