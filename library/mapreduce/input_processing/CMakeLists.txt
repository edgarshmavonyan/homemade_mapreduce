cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS -std=c++17)

set(SOURCE_FILES
    file_processor.cpp
    input_processor_interface.cpp
    dir_processor.cpp
    process.cpp)

add_library(input_processing STATIC ${SOURCE_FILES})

target_include_directories(
    input_processing
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
    input_processing
    PUBLIC
    util
)
