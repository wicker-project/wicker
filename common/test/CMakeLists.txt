#find test framework dependency
find_package(Catch2 3 REQUIRED)

# create executable for Common library tests - exclude from all builds
add_executable(WickerCommon_UT
    ${PROJECT_SOURCE_DIR}/Catch2TestMain.cpp
    ThreadManagerBase_ut.cpp
    Suspendable_ut.cpp)

target_link_libraries(WickerCommon_UT PUBLIC 
    WickerCommonLib
    Catch2::Catch2WithMain)

#include CTest and Catch to allow unit tests to run
include(CTest)
include(Catch)
catch_discover_tests(WickerCommon_UT)

add_test(NAME WickerCommon_UT COMMAND WickerCommon_UT)
