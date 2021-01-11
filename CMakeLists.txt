cmake_minimum_required(VERSION 3.18)
project(hello-world)

option(TEST_COVERAGE "Generate test coverage report" ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

include(Deps)
include(Server)
