cmake_minimum_required(VERSION 3.16)

project(logreader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS  "-O3 -pedantic -Werror -Wall -no-pie")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
link_libraries(${GTKMM_LIBRARIES})
include_directories(
    ${GTKMM_INCLUDE_DIRS}
    include
)

add_subdirectory(src)
