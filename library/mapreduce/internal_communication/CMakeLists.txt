cmake_minimum_required(VERSION 2.8.12)

find_package(MPI REQUIRED)
set(CMAKE_CXX_FLAGS -std=c++17)

set(SOURCE_FILES
    filenames.cpp
    input_reader.cpp
    input_sender.cpp
    operation_input.cpp
    read_tsv.cpp
    output_writer.cpp
    reducer_input.cpp)

add_library(internal_communication STATIC ${SOURCE_FILES})
target_include_directories(
    internal_communication
    PUBLIC
    ${MPI_INCLUDE_PATH}
    ${mapreduce_SOURCE_DIR}
)
target_link_libraries(
    internal_communication
    PUBLIC
    ${MPI_LIBRARIES}
    util
    input_processing
)
