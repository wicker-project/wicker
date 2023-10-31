add_library(WickerLoggingLib
    LoggingService.cpp
    filters/LevelFilter.cpp
    filters/Filterable.cpp)

target_include_directories(WickerLoggingLib PUBLIC 
    ${PROJECT_SOURCE_DIR}/logging/include
    ${PROJECT_SOURCE_DIR}/logging/include/filters
    )