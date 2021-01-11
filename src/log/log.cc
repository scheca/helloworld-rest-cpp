#include "log.h"

namespace logging {

spdlog::logger& logger([]() -> spdlog::logger& {
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%^%L%$] [%H:%M:%S %z] [thread %t] %v");

    return *spdlog::stdout_color_mt("console");
}());

}