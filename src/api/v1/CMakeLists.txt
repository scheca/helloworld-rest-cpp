set(CMAKE_FIND_LIBRARY_SUFFIXES "-static.a;.a")

find_package(Drogon REQUIRED)

add_library(api STATIC
    controller.cc
    error.cc
)

target_link_libraries(api PRIVATE
    service
    log
)

# Forwarding of DROGON_LIBRARIES is necessary as the main
# executable #includes its headers.
# An alternative would be to hide the interaction with Drogon
# behind an interface of the api library.
target_link_libraries(api PUBLIC
    ${DROGON_LIBRARIES}
)

add_subdirectory(test)