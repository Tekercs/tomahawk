cmake_minimum_required(VERSION 3.3)
project(tomahawk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(main main.cpp)

include_directories(build/lib)

add_subdirectory(tests)
add_subdirectory(src)

target_link_libraries(main core)

set_target_properties(core main
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "build"
        LIBRARY_OUTPUT_DIRECTORY "build/lib"
        RUNTIME_OUTPUT_DIRECTORY "build")

