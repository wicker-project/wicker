add_library(WickerLoggingLib
    LoggingService.cpp)

target_include_directories(WickerLoggingLib PUBLIC 
    ${PROJECT_SOURCE_DIR}/logging/include
    )