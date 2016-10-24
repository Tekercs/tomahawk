cmake_minimum_required(VERSION 3.2)
project(tomahawk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib/)
FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib/core/)

add_subdirectory(tests)
add_subdirectory(src)


#set_target_properties(core main tests
#        PROPERTIES
#        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
#        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib
#        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)