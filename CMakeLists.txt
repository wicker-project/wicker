
#Version is currently a rather soft requirement
cmake_minimum_required (VERSION 3.20)

project (Wicker VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(build_tests)
add_custom_target(WickerTests COMMAND ${CMAKE_CTEST_COMMAND})
add_dependencies(WickerTests build_tests)

add_subdirectory(common)
