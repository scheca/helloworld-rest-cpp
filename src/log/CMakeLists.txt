find_package(spdlog CONFIG REQUIRED)

add_library(log STATIC
    log.cc
)

target_link_libraries(log PUBLIC
    spdlog::spdlog
)
