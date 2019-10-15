cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS -std=c++17)

set(SOURCE_FILES
    argument_parser.cpp
    slice.cpp)

add_library(util STATIC ${SOURCE_FILES})
