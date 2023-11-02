add_library(WickerLoggingLib
    LoggingService.cpp
    target/TargetBase.cpp
    target/
    filter/LevelFilter.cpp
    filter/Filterable.cpp
    )

target_include_directories(WickerLoggingLib PUBLIC 
    ${PROJECT_SOURCE_DIR}/logging/include/logging
    ${PROJECT_SOURCE_DIR}/logging/include/logging/filter
    ${PROJECT_SOURCE_DIR}/logging/include/logging/target
    )
