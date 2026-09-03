file(GLOB_RECURSE DOMAIN "*.cpp")

add_library(domain STATIC ${DOMAIN})

target_include_directories(domain PUBLIC ${SRC_ROOT}/domain)

target_link_libraries(domain PUBLIC UTILS)
