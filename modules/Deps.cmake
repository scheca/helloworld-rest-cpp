set_directory_properties(PROPERTIES EP_BASE ${CMAKE_BINARY_DIR}/external)
get_directory_property(EXTERNAL_BASE_PATH EP_BASE)

set(EXTERNAL_INSTALL_PATH ${EXTERNAL_BASE_PATH}/dist)
set_directory_properties(PROPERTIES EXTERNAL_INSTALL_PATH ${EXTERNAL_INSTALL_PATH})

include(ExternalProject)

ExternalProject_Add(c-ares
    GIT_REPOSITORY https://github.com/c-ares/c-ares.git
    GIT_TAG master
    CMAKE_ARGS
      -DCARES_STATIC=ON
      -DCARES_SHARED=OFF
      -DCARES_BUILD_TOOLS=OFF
      -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PATH}
    INSTALL_COMMAND ${CMAKE_BUILD_TOOL} install
)

ExternalProject_Add(jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG master
    CMAKE_ARGS
      -DBUILD_STATIC_LIBS=ON
      -DBUILD_SHARED_LIBS=OFF
      -DBUILD_OBJECT_LIBS=OFF
      -DJSONCPP_WITH_TESTS=OFF
      -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PATH}
    INSTALL_COMMAND ${CMAKE_BUILD_TOOL} install
)

ExternalProject_Add(brotli
    GIT_REPOSITORY https://github.com/google/brotli.git
    GIT_TAG master
    CMAKE_ARGS
      -DBROTLI_DISABLE_TESTS=ON
      -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PATH}
    INSTALL_COMMAND ${CMAKE_BUILD_TOOL} install
)

ExternalProject_Add(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG master
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PATH}
    INSTALL_COMMAND ${CMAKE_BUILD_TOOL} install
)

ExternalProject_Add(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
    CMAKE_ARGS
      -DBUILD_GMOCK=ON
      -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PATH}
    INSTALL_COMMAND ${CMAKE_BUILD_TOOL} install
)

ExternalProject_Add(drogon
    DEPENDS c-ares brotli jsoncpp
    GIT_REPOSITORY https://github.com/an-tao/drogon.git
    GIT_TAG master
    CMAKE_ARGS
      -DBUILD_CTL=OFF
      -DBUILD_EXAMPLES=OFF
      -DBUILD_ORM=OFF
      -DBUILD_DROGON_SHARED=OFF
      -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PATH}
    INSTALL_COMMAND ${CMAKE_BUILD_TOOL} install
)
