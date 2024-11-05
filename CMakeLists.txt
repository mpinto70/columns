cmake_minimum_required (VERSION 3.28)
project (columns)

set(CMAKE_CXX_STANDARD 20)
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

set (CMAKE_VERBOSE_MAKEFILE on)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UnitTest.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CppCheck.cmake)

# Recurse subdirectories
add_subdirectory (src)
add_subdirectory (mck)
add_subdirectory (test)
