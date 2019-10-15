cmake_minimum_required(VERSION 2.8.12)
project(mapreduce)

find_package(MPI REQUIRED)
set(CMAKE_CXX_FLAGS -std=c++17)

add_subdirectory(util)
add_subdirectory(input_processing)
add_subdirectory(internal_communication)
add_subdirectory(service_operations)
add_subdirectory(operations)

set(SOURCE_FILES
    interface.cpp)

add_library(mapreduce STATIC ${SOURCE_FILES})
target_include_directories(
    mapreduce
    PUBLIC
    ${MPI_INCLUDE_PATH}
)
target_link_libraries(
    mapreduce
    PUBLIC
    operations
    input_processing
    internal_communication
    service_operations
    ${MPI_LIBRARIES}
)