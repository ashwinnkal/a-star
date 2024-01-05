cmake_minimum_required(VERSION 3.27)
project(a-star)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(a_star main.cpp utility.hpp)
configure_file(${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)