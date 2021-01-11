find_package(GTest REQUIRED NO_CMAKE_SYSTEM_PATH)

add_executable(api_test
    controller.cc
)

target_link_libraries(api_test PRIVATE
    api
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(api_test)
