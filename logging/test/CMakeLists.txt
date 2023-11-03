#find test framework dependency
find_package(Catch2 3 REQUIRED)

# create executable for Common library tests - exclude from all builds
add_executable(WickerLogging_UT
    ${PROJECT_SOURCE_DIR}/Catch2TestMain.cpp
    LoggingService_ut.cpp
    filter/LevelFilter_ut.cpp
    filter/Filterable_ut.cpp
    target/StreamTarget_ut.cpp)

target_link_libraries(WickerLogging_UT PUBLIC 
    WickerLoggingLib
    Catch2::Catch2WithMain)

#include CTest and Catch to allow unit tests to run
include(CTest)
include(Catch)
catch_discover_tests(WickerLogging_UT)

add_test(NAME WickerLogging_UT COMMAND WickerLogging_UT)
