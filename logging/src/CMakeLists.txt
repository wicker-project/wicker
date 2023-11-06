add_library(WickerLoggingLib
    LoggingService.cpp
    target/StreamTarget.cpp
    target/FileTarget.cpp
    filter/LevelFilter.cpp
    filter/Filterable.cpp
    )

set(LoggingLibIncludeDir logging/include/logging)

target_include_directories(WickerLoggingLib PUBLIC 
    ${PROJECT_SOURCE_DIR}/${LoggingLibIncludeDir}
    ${PROJECT_SOURCE_DIR}/${LoggingLibIncludeDir}/filter
    ${PROJECT_SOURCE_DIR}/${LoggingLibIncludeDir}/target
    )
