cmake_minimum_required(VERSION 2.8.12)
project(main)

set(CMAKE_CXX_FLAGS -std=c++17)

add_subdirectory(library)

add_executable(main main.cpp)
target_include_directories(
    main
    PRIVATE
    library
)
target_link_libraries(
    main
    PRIVATE
    mapreduce
)