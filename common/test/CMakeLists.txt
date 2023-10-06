#find test framework dependency
find_package(Catch2 3 REQUIRED)

# create executable for Common library tests - exclude from all builds
add_executable(WickerCommon_UT
    ${PROJECT_SOURCE_DIR}/Catch2TestMain.cpp
    ThreadManagerBase_ut.cpp
    Suspendable_ut.cpp)

# assign postfix to executable
set_target_properties(WickerCommon_UT PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(WickerCommon_UT PUBLIC 
    WickerCommonLib
    Catch2::Catch2WithMain)

#include CTest and Catch to allow unit tests to run
include(CTest)
include(Catch)
catch_discover_tests(WickerCommon_UT)

add_test(NAME ${CMAKE_CURRENT_SOURCE_DIR} COMMAND ${CMAKE_CURRENT_SOURCE_DIR})
