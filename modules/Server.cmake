get_directory_property(DEPS_INSTALL_PATH EXTERNAL_INSTALL_PATH)

include(ExternalProject)

ExternalProject_Add(server
    DEPENDS drogon spdlog gtest
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/src
    CMAKE_ARGS
      -DTEST_COVERAGE=${TEST_COVERAGE}
      -DCMAKE_PREFIX_PATH=${DEPS_INSTALL_PATH}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/dist
    INSTALL_COMMAND ${CMAKE_BUILD_TOOL} install
)
