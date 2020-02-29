cmake_minimum_required (VERSION 2.8.11)
project (columns)

# add support for CTest
enable_testing()
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS " \
    -Wno-parentheses \
    -Werror \
    -Wall \
    -O2 \
    -finline-functions \
    -Wno-unused-local-typedefs \
    -D PROJECT_DIR=\"\\\"${CMAKE_SOURCE_DIR}\\\"\"")

# set (CMAKE_VERBOSE_MAKEFILE on)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)

###################################
# libbrasa - BEGIN ################
###################################

ExternalProject_Add(libbrasa
    GIT_REPOSITORY https://github.com/mpinto70/libbrasa.git
    GIT_TAG v0.5
    PREFIX ${CMAKE_BINARY_DIR}/brasa
    BUILD_COMMAND ""
    INSTALL_COMMAND
        make
        DESTDIR=${EXTERNAL_INSTALL_LOCATION}
        install
    LOG_INSTALL ON
    LOG_BUILD ON
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/brasa/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/brasa/lib)

###################################
# libbrasa - END   ################
###################################

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UnitTest.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CppCheck.cmake)

# Recurse subdirectories
add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (mck)
