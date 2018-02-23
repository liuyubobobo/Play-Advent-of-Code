cmake_minimum_required(VERSION 3.5)
project(cpp_2017_03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main_part_2.cpp)
add_executable(cpp_2017_03 ${SOURCE_FILES})