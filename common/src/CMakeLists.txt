add_library(WickerCommonLib
    ThreadManagerBase.cpp
    Suspendable.cpp)

target_include_directories(WickerCommonLib PUBLIC 
    ${PROJECT_SOURCE_DIR}/common/include
    )