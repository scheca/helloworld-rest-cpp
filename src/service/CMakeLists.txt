add_library(service STATIC
    service_impl.cc
)

target_link_libraries(service PRIVATE
    log
)

add_subdirectory(test)