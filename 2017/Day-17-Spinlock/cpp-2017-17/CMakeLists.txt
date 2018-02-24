cmake_minimum_required(VERSION 3.5)
project(cpp_2017_17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main_part_2_2.cpp)
add_executable(cpp_2017_17 ${SOURCE_FILES})