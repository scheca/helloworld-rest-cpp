find_package(GTest REQUIRED NO_CMAKE_SYSTEM_PATH)

add_executable(service_test
    service_impl.cc
)

target_link_libraries(service_test PRIVATE
    service
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(service_test)
