cmake_minimum_required(VERSION 3.2)
project(tomahawk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_subdirectory(tests)
add_subdirectory(src)

