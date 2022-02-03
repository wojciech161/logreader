project(LogReader)

cmake_minimum_required(VERSION 3.16)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wno-cpp -Wno-deprecated-declarations -no-pie")
# set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Werror -pedantic")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKSOURCEVIEWMM gtksourceviewmm-3.0)

add_subdirectory(src)
