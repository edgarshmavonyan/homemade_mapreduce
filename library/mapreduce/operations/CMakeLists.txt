cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS -std=c++17)

set(SOURCE_FILES
    mapper_interface.cpp
    reducer_interface.cpp)

add_library(operations STATIC ${SOURCE_FILES})
target_include_directories(
    operations
    PUBLIC
    ${mapreduce_SOURCE_DIR}
)
target_link_libraries(
    operations
    PUBLIC
    internal_communication
)
