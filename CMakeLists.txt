#Version is currently a rather soft requirement
cmake_minimum_required (VERSION 3.20)

project (Wicker VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Professional CMake ch. 27, p.622
# use INTERFACE, BUILD_INTERFACE, and INSTALL_INTERFACE

enable_testing()

add_subdirectory(common)
add_subdirectory(logging)

