cmake_minimum_required(VERSION 3.18)
project(server)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../modules)

set_directory_properties(PROPERTIES INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR})
set_directory_properties(PROPERTIES COMPILE_OPTIONS -std=c++17)

enable_testing()

if (TEST_COVERAGE)
    set(CMAKE_BUILD_TYPE "Debug")
    include(CodeCoverage)
    append_coverage_compiler_flags()
    include(ProcessorCount)
    ProcessorCount(N)
    if(NOT N EQUAL 0)
        set(CTEST_PARALLEL_JOBS "-j ${N}")
    endif()
    setup_target_for_coverage_lcov(
        NAME coverage
        EXECUTABLE ctest ${CTEST_PARALLEL_JOBS}
        EXCLUDE "${CMAKE_PREFIX_PATH}/*" "/usr/*" "*/test/*" "*/mock/*"
    )
endif()

add_subdirectory(api/v1)
add_subdirectory(log)
add_subdirectory(service)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE
    api
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_STRIP} ${PROJECT_NAME}
    )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME)
