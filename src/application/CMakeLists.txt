file(GLOB_RECURSE APPLICATION "*.cpp")

add_library(application STATIC ${APPLICATION})

target_include_directories(application PUBLIC ${SRC_ROOT}/application)

target_link_libraries(application PUBLIC domain)