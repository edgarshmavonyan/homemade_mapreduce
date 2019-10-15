cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS -std=c++17)

set(SOURCE_FILES
    shuffler.cpp
    sort_merger.cpp)

add_library(service_operations STATIC ${SOURCE_FILES})
target_include_directories(
    service_operations
    PUBLIC
    ${mapreduce_SOURCE_DIR}/src
)
target_link_libraries(
    service_operations
    PUBLIC
    internal_communication
)